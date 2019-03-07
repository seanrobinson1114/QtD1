//---------------------------------------------------------------------------//
//!
//! \file   Game.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The game class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// Qt Includes
#include <QtConcurrentRun>

// QtD1 Includes
#include "Game.h"
#include "GameFrontendProxy.h"
#include "CharacterFrontendProxy.h"
#include "Town.h"
#include "Rogue.h"
#include "Sorcerer.h"
#include "Warrior.h"
#include "qtd1_config.h"
#include "AudioDevice.h"
#include "MainWindow.h"
#include "QuestManager.h"

namespace QtD1{

// Initialize static member data
Game* Game::s_instance = NULL;

// Get the singleton instance
Game* Game::getInstance()
{
  if( !s_instance )
    s_instance = new Game;

  return s_instance;
}

// Constructor
  Game::Game()
  : QWidget(),
    d_character(),
    d_game_timer_id( -1 ),
    d_game_paused( true ),
    d_loading_screen( new LoadingScreen( this ) ),
    //d_game_control_panel( new QDeclarativeView( this ) ),
    d_game_control_panel( new ControlPanel( this ) ),
    d_game_menu( new QDeclarativeView( this ) ),
    d_game_options_menu( new QDeclarativeView( this ) ),
    d_level( new Town ),
    d_level_viewer( new QGraphicsView( d_level, this ) )
{
  // Reserve the first mixer channel for dialogue
  AudioDevice::getInstance().reserveMixerChannels( NPC::getReservedMixerChannel()+1 );
    
  // Move the loading screen
  d_loading_screen->move( 0, 0 );

  // Set up the level
  d_level->createBackground();

  QPixmap level_background( d_level_viewer->size() );
  level_background.fill( Qt::black );
  d_level->setBackgroundBrush( level_background );

  // Set up the level viewer
  d_level_viewer->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
  d_level_viewer->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
  d_level_viewer->setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
  d_level_viewer->setOptimizationFlags( QGraphicsView::DontClipPainter |
                                        QGraphicsView::DontSavePainterState |
                                        QGraphicsView::DontAdjustForAntialiasing );

  // Create the menu item over sound
  d_game_menu_item_over_sound.setSource( "/sfx/items/titlemov.wav" );

  // Create the menu item click sound
  d_game_menu_item_click_sound.setSource( "/sfx/items/titlslct.wav" );

  // Create the control panel click sound
  d_control_panel_click_sound.setSource( "/sfx/items/titlemov.wav" );
}

// Destructor
Game::~Game()
{
  // Make sure that the character doesn't get deleted twice
  if( d_character )
    d_level->removeItem( d_character.get() );
}

//! Get the game menu
QDeclarativeView* Game::getGameMenu()
{
  return d_game_menu;
}

// Create a new game
void Game::create( const QString& character_name,
                   const int character_class )
{
  emit gameLoadStarted();

  // Create a new character
  switch( character_class )
  {
    case Character::Rogue:
    {
      d_character.reset( new Rogue( character_name ) );
      break;
    }
    case Character::Sorcerer:
    {
      d_character.reset( new Sorcerer( character_name ) );
      break;
    }
    case Character::Warrior:
    {
      d_character.reset( new Warrior( character_name ) );
      break;
    }
    default:
      qFatal( "Error: invalid character class! The game cannot be created." );
  }

  // Initialize the loading screen
  d_loading_screen->trackAssetLoadProgression(
                                             d_level, LoadingScreen::newGame );

  // Create the level NPCs and actors
  {
    QVector<NPC*> npcs;
    QVector<Actor*> special_actors;
    
    d_level->createNPCsAndActors( npcs, special_actors );

    for( size_t i = 0; i < npcs.size(); ++i )
      this->registerNPC( npcs[i] );

    // for( size_t i = 0; i < special_actors.size(); ++i )
    //   this->registerSpecialActors( special_actors[i] );
  }

  // Add the character to the level
  d_level->insertCharacter( d_character.get(),
                            QPointF( 0, 0 ),
                            South );

  // Load the level assets
  QObject::connect( d_level, SIGNAL(assetLoadingStarted(const int)),
                    this, SLOT(handleTownAssetLoadStarted()) );
  QObject::connect( d_level, SIGNAL(assetLoadingFinished(const int)),
                    this, SLOT(handleTownAssetLoadFinished()) );

  d_level->loadImageAssets();
}

// Restore a previous game
void Game::restore( const QString& character_name )
{
  // Game* game = Game::getInstance();

  // restored_character = Character::restore( character_name );

  // // Make sure that the restore was successful
  // if( !restored_character )
  //   qFatal( "Unable to restore character %s state!", character_name );

  // game->d_character.reset( restored_character );

  // game->connectCharacterSignalsToGameSlots();

  // // Restart the game timer
  // d_game_timer_id = this->startTimer( s_refresh_delay_time );
  // d_game_paused = false;

  // // Restore the rest of the game
}

// Pause the game
void Game::pause()
{
  if( !d_game_paused )
  {
    if( d_game_timer_id >= 0 )
    {
      this->killTimer( d_game_timer_id );
      d_game_timer_id = -1;
      d_game_paused = true;
    }
  }
}

// Resume the game
void Game::resume()
{
  if( d_game_paused )
  {
    if( d_game_timer_id < 0 )
    {
      d_game_timer_id = this->startTimer( s_refresh_delay_time );
      d_game_paused = false;
    }
  }
}

// Quit the game (and go back to main menu)
void Game::quit()
{
  this->close();
}

// Save the game
void Game::save()
{

}

// Play the game music
void Game::playGameMusic()
{
  d_level->playLevelMusic();
}

// Pause the game music
void Game::pauseGameMusic()
{
  d_level->pauseLevelMusic();
}

// Stop the game music
void Game::stopGameMusic()
{
  d_level->stopLevelMusic();
}

// Play menu item over sound
void Game::playMenuItemOverSound()
{
  d_game_menu_item_over_sound.playSound();
}

// Play menu item click sound
void Game::playMenuItemClickSound()
{
  d_game_menu_item_click_sound.playSound();
}

// Play control panel click sound
void Game::playControlPanelClickSound()
{
  d_control_panel_click_sound.playSound();
}

// Set the game music volume
void Game::setGameMusicVolume( int volume )
{
  AudioDevice::getInstance().setMusicVolume( volume );
}

void Game::setGameSoundVolume( int volume )
{
  int number_of_channels = AudioDevice::getInstance().getNumberOfChannels();

  for( int i = 0; i < number_of_channels; ++i )
    AudioDevice::getInstance().setMixerChannelVolume( i, volume );
}

// Show the loading screen
void Game::showLoadingScreen()
{
  d_loading_screen->show();
  d_loading_screen->raise();
}

// Hide the loading screen
void Game::hideLoadingScreen()
{
  d_loading_screen->hide();
}

// Show the level viewer
void Game::showLevelViewer()
{
  d_level_viewer->show();
  d_level_viewer->raise();

  emit controlPanelWidgetActivated();

  d_game_control_panel->show();
  d_game_control_panel->raise();
}

// Hide the level viewer
void Game::hideLevelViewer()
{
  d_game_control_panel->hide();

  emit controlPanelWidgetDeactivated();

  d_level_viewer->hide();
}

// Show the character inventory
void Game::showCharacterInventory()
{
  d_character->getInventory().show();
  d_character->getInventory().raise();
  d_game_control_panel->raise();
}

// Hide the character inventory
void Game::hideCharacterInventory()
{
  d_character->getInventory().hide();
}

// Show the spell book
void Game::showCharacterSpellBook()
{
  d_character->getSpellBook().show();
  d_character->getSpellBook().raise();
  d_game_control_panel->raise();
}

// Hide the spell book
void Game::hideCharacterSpellBook()
{
  d_character->getSpellBook().hide();
}

// Show the character stats
void Game::showCharacterStats()
{
  emit characterStatsWidgetActivated();

  d_character->getCharacterStats().show();
  d_character->getCharacterStats().raise();
  d_game_control_panel->raise();
}

// Hide the character stats
void Game::hideCharacterStats()
{
  d_character->getCharacterStats().hide();
}

// Show the quest log
void Game::showQuestLog()
{
  d_character->getQuestLog().show();
  d_character->getQuestLog().raise();
  d_game_control_panel->raise();
}

// Hide the quest log
void Game::hideQuestLog()
{
  d_character->getQuestLog().hide();
}

// Show the game menu
void Game::showGameMenu()
{
  this->pause();

  emit gameMenuWidgetActivated();

  d_game_menu->show();
  d_game_menu->raise();
  d_game_menu->setFocus();
}

// Hide the game menu
void Game::hideGameMenu()
{
  d_game_menu->hide();
  emit gameMenuWidgetDeactivated();

  this->setFocus();
  this->resume();
  this->hideGameOptionsMenu();
  d_game_control_panel->hideMenuButton();
}

// Show the game options menu
void Game::showGameOptionsMenu()
{
  emit gameOptionsMenuWidgetActivated();

  d_game_options_menu->show();
  d_game_options_menu->raise();
  d_game_menu->lower();
  d_game_options_menu->setFocus();
}

// Hide the game options menu
void Game::hideGameOptionsMenu()
{
  d_game_options_menu->hide();

  emit gameOptionsMenuWidgetDeactivated();

  d_game_menu->raise();
  d_game_menu->setFocus();
}

// Handle show events
void Game::showEvent( QShowEvent* event )
{
  QWidget::showEvent( event );

  // Hide the all game menu widgets
  d_game_control_panel->hide();
  d_game_menu->hide();
  d_game_options_menu->hide();
  d_loading_screen->hide();
  d_level_viewer->hide();

  if( d_character ) {
    d_character->getInventory().hide();
    d_character->getSpellBook().hide();
  }
}

// Handle hide events
void Game::hideEvent( QHideEvent* )
{

}

// Handle resize event
void Game::resizeEvent( QResizeEvent* )
{

}

// Handle the timer event
void Game::timerEvent( QTimerEvent* )
{
  d_level->advance();
}

// Handle key press events
void Game::keyPressEvent( QKeyEvent* )
{

}

// Handle key release events
void Game::keyReleaseEvent( QKeyEvent* )
{

}

// Handle mouse move events
void Game::mouseMoveEvent( QMouseEvent* )
{

}

// Handle mouse press event
void Game::mousePressEvent( QMouseEvent* )
{

}

// Handle mouse release event
void Game::mouseReleaseEvent( QMouseEvent* )
{

}

// Handle mouse double-click event
void Game::mouseDoubleClickEvent( QMouseEvent* )
{

}

// Handle the character level up
void Game::handleCharacterLevelUp( const int )
{
  // Show the level up button
}

// Handle the character death
void Game::handleCharacterDeath()
{
  // Load the game menu
}

// Handle the NPC menu activated
void Game::handleNPCMenuActivated()
{
  this->hideCharacterStats();
  this->hideQuestLog();
  this->hideCharacterInventory();
  this->hideCharacterSpellBook();

  d_game_control_panel->deactivateFocusShortcuts();
  d_level_viewer->setInteractive( false );
}

// Handle the NPC menu deactivated
void Game::handleNPCMenuDeactivated()
{
  d_game_control_panel->activateFocusShortcuts();
  d_level_viewer->setInteractive( true );
}

void Game::handleTownAssetLoadStarted()
{
  this->showLoadingScreen();
  this->update();
}

void Game::handleTownAssetLoadFinished()
{
  // Load the control panel
  d_game_control_panel->setAutoFillBackground( false );
  d_game_control_panel->setAttribute(  Qt::WA_TranslucentBackground );
  d_game_control_panel->move( 80, 456 );

  QPixmap pixmap = QPixmap::grabWidget( d_game_control_panel );
  d_game_control_panel->setMask( pixmap.createHeuristicMask() );

  // Connect the control panel signals to the game slots
  this->connectControlPanelSignalsToGameSlots();

  // Connect the level signals to the game slots
  this->connectLevelSignalsToControlPanelSlots();

  // Load the game menu
  d_game_menu->setSource( QUrl( GAME_MENU_QML_PATH ) );
  d_game_menu->setStyleSheet( QString("background: transparent") );

  GameFrontendProxy::connectToBackend( d_game_menu,
                                       SIGNAL(gameMenuWidgetActivated()),
                                       SIGNAL(gameMenuWidgetDeactivated()) );

  // Load the game options menu
  d_game_options_menu->setSource( QUrl( GAME_OPTIONS_MENU_QML_PATH ) );
  d_game_options_menu->setStyleSheet( QString("background: transparent") );

  GameFrontendProxy::connectToBackend( d_game_options_menu,
                                       SIGNAL(gameOptionsMenuWidgetActivated()),
                                       SIGNAL(gameOptionsMenuWidgetDeactivated()) );

  // Make the control panel have focus by default
  d_level_viewer->setFocusProxy( d_game_control_panel );
  this->setFocusProxy( d_game_control_panel );

  // Assign the character stats widget to the frontend widget
  d_character->getCharacterStats().setParent( this );
  d_character->getCharacterStats().move( 80, 119 );

  // Assign the inventory widget to the frontend widget
  d_character->getInventory().setParent( this );
  d_character->getInventory().move( 400, 119 );

  // Assign the spellbook widget to the frontend widget
  d_character->getSpellBook().setParent( this );
  d_character->getSpellBook().move( 400, 119 );

  // Assign the questlog widget to the frontend widget
  d_character->getQuestLog().setParent( this );
  d_character->getQuestLog().move( 80, 119 );

  // Connect the character signals to the game slots
  this->connectCharacterSignalsToGameSlots();

  // Activate the level NPCs and actors
  d_level->activateNPCsAndActors( this );

  // Activate all quests
  QuestManager::getInstance().activateQuest( Quest::Type::TheButcher );
  QuestManager::getInstance().activateQuest( Quest::Type::PoisonWater );
  QuestManager::getInstance().activateQuest( Quest::Type::KingLeoricsCurse );
  QuestManager::getInstance().activateQuest( Quest::Type::OgdensSign );
  QuestManager::getInstance().activateQuest( Quest::Type::GharbadTheWeak );
  QuestManager::getInstance().activateQuest( Quest::Type::TheMagicRock );
  QuestManager::getInstance().activateQuest( Quest::Type::ArmorOfValor );
  QuestManager::getInstance().activateQuest( Quest::Type::HallsOfTheBlind );
  QuestManager::getInstance().activateQuest( Quest::Type::ZharTheMad );
  QuestManager::getInstance().activateQuest( Quest::Type::TheBlackMushroom );
  QuestManager::getInstance().activateQuest( Quest::Type::TheAnvilOfFury );
  QuestManager::getInstance().activateQuest( Quest::Type::TheWarlordOfBlood );
  QuestManager::getInstance().activateQuest( Quest::Type::Lachdanan );
  QuestManager::getInstance().activateQuest( Quest::Type::TheChamberOfBone );
  QuestManager::getInstance().activateQuest( Quest::Type::ArchbishopLazarus );
  QuestManager::getInstance().activateQuest( Quest::Type::Diablo );

  // Activate the character
  d_character->setPos( 3248, 2444 );
  d_character->activate();
  d_character->startStateMachine();

  // Start the game timer
  d_game_timer_id = this->startTimer( s_refresh_delay_time );
  d_game_paused = false;

  // Show the level viewer and control panel
  this->hideLoadingScreen();
  this->showLevelViewer();

  // Start the game music
  this->playGameMusic();

  emit gameLoadFinished();
}

void Game::handleLevelAssetLoadStarted()
{

}

void Game::handleLevelAssetLoadFinished()
{

}

// Register NPC
void Game::registerNPC( NPC* new_npc )
{
  QObject::connect( new_npc, SIGNAL(interactionMenuActivated()),
                    this, SLOT(handleNPCMenuActivated()) );
  QObject::connect( new_npc, SIGNAL(interactionMenuDeactivated()),
                    this, SLOT(handleNPCMenuDeactivated()) );
}

// Connect the character signals to the game slots
void Game::connectCharacterSignalsToGameSlots()
{
  QObject::connect( d_character.get(), SIGNAL(levelUp(const int)),
                    this, SLOT(handleCharacterLevelUp(const int)) );
  QObject::connect( d_character.get(), SIGNAL(death()),
                    this, SLOT(handleCharacterDeath()) );
}

// Connect Control panel signals to game slots
void Game::connectControlPanelSignalsToGameSlots()
{
  QObject::connect( d_game_control_panel, SIGNAL( showCharacterStats() ),
                    this, SLOT( showCharacterStats() ) );

  QObject::connect( d_game_control_panel, SIGNAL( hideCharacterStats() ),
                    this, SLOT( hideCharacterStats() ) );

  QObject::connect( d_game_control_panel, SIGNAL( showQuestLog() ),
                    this, SLOT( showQuestLog() ) );

  QObject::connect( d_game_control_panel, SIGNAL( hideQuestLog() ),
                    this, SLOT( hideQuestLog() ) );

  QObject::connect( d_game_control_panel, SIGNAL( showGameMenu() ),
                    this, SLOT( showGameMenu() ) );

  QObject::connect( d_game_control_panel, SIGNAL( hideGameMenu() ),
                    this, SLOT( hideGameMenu() ) );

  QObject::connect( d_game_control_panel, SIGNAL( showInventory() ),
                    this, SLOT( showCharacterInventory() ) );

  QObject::connect( d_game_control_panel, SIGNAL( hideInventory() ),
                    this, SLOT( hideCharacterInventory() ) );

  QObject::connect( d_game_control_panel, SIGNAL( showSpellBook() ),
                    this, SLOT( showCharacterSpellBook() ) );

  QObject::connect( d_game_control_panel, SIGNAL( hideSpellBook() ),
                    this, SLOT( hideCharacterSpellBook() ) );
}

void Game::connectLevelSignalsToControlPanelSlots()
{
  QObject::connect( d_level, SIGNAL( interactiveLevelObjectHoveringStarted( QString ) ),
                    d_game_control_panel, SLOT( changeObjectDescriptionDisplay( QString ) ) );

  QObject::connect( d_level, SIGNAL( interactiveLevelObjectHoveringStopped( QString ) ),
                    d_game_control_panel, SLOT( changeObjectDescriptionDisplay( QString ) ) );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Game.cpp
//---------------------------------------------------------------------------//
