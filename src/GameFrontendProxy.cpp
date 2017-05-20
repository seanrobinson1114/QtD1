//---------------------------------------------------------------------------//
//!
//! \file   GameFrontendProxy.cpp
//! \author Alex Robinson
//! \brief  The game frontend proxy class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "GameFrontendProxy.h"
#include "Game.h"

namespace QtD1{

// Constructor
GameFrontendProxy::GameFrontendProxy( QObject* parent )
  : QObject( parent )
{
  // Set the object name so that we can find it later
  this->setObjectName( this->objectName() );
}

// Connect to the backend
void GameFrontendProxy::connectToBackend(
                                       QDeclarativeView* frontend_widget,
                                       const char* activated_backend_signal,
                                       const char* deactivated_backend_signal )
{
  QObject* root_object = frontend_widget->rootObject();

  // Connect the backend signals to the frontend slots
  QList<GameFrontendProxy*> game_frontends =
    root_object->findChildren<GameFrontendProxy*>( GameFrontendProxy::objectName() );

  if( game_frontends.size() != 1 )
  {
    qFatal( "Error: QtD1 game frontend %s has been improperly set up!",
            frontend_widget->source().toString().toStdString().c_str() );
  }
  else
  {
    GameFrontendProxy* game_frontend = game_frontends[0];

    QObject::connect( Game::getInstance(), SIGNAL(gameSaveStarted()),
                      game_frontend, SLOT(redirectGameSaveStartedSignalToFrontend()) );
    QObject::connect( Game::getInstance(), SIGNAL(gameSaveFinished()),
                      game_frontend, SLOT(redirectGameSaveFinishedSignalToFrontend()) );
    QObject::connect( Game::getInstance(), SIGNAL(gameLoadStarted()),
                      game_frontend, SLOT(redirectGameLoadStartedSignalToFrontend()) );
    QObject::connect( Game::getInstance(), SIGNAL(gameLoadFinished()),
                      game_frontend, SLOT(redirectGameLoadFinishedSignalToFrontend()) );
    QObject::connect( Game::getInstance(), activated_backend_signal,
                      game_frontend, SLOT(activateWidget()) );
    QObject::connect( Game::getInstance(), deactivated_backend_signal,
                      game_frontend, SLOT(deactivateWidget()) );
  }
}

// Create a new game
void GameFrontendProxy::create( const QString& character_name,
                                const int character_class )
{
  Game::getInstance()->create( character_name, character_class );
}

// Restore a previous game
void GameFrontendProxy::restore( const QString& character_name )
{
  Game::getInstance()->restore( character_name );
}

// Pause the game
void GameFrontendProxy::pause()
{
  Game::getInstance()->pause();
}

// Resume the game
void GameFrontendProxy::resume()
{
  Game::getInstance()->resume();
}

// Quit the game (and go back to main menu)
void GameFrontendProxy::quit()
{
  Game::getInstance()->quit();
}

// Save the game
void GameFrontendProxy::save()
{
  Game::getInstance()->save();
}

// Play the game music
void GameFrontendProxy::playGameMusic()
{
  Game::getInstance()->playGameMusic();
}

// Pause game music
void GameFrontendProxy::pauseGameMusic()
{
  Game::getInstance()->pauseGameMusic();
}

// Stop game music
void GameFrontendProxy::stopGameMusic()
{
  Game::getInstance()->stopGameMusic();
}

// Play menu item over sound
void GameFrontendProxy::playMenuItemOverSound()
{
  Game::getInstance()->playMenuItemOverSound();
}

// Play menu item click sound
void GameFrontendProxy::playMenuItemClickSound()
{
  Game::getInstance()->playMenuItemClickSound();
}

// Play control panel click sound
void GameFrontendProxy::playControlPanelClickSound()
{
  Game::getInstance()->playMenuItemOverSound();
}

// Set the game music volume
void GameFrontendProxy::setGameMusicVolume( int volume )
{
  Game::getInstance()->setGameMusicVolume( volume );
}

// Set the game sounds volume
void GameFrontendProxy::setGameSoundVolume( int volume )
{
  Game::getInstance()->setGameSoundVolume( volume );
}

// Show the character inventory
void GameFrontendProxy::showCharacterInventory()
{
  Game::getInstance()->showCharacterInventory();
}

// Hide the character inventory
void GameFrontendProxy::hideCharacterInventory()
{
  Game::getInstance()->hideCharacterInventory();
}

// Show the spell book
void GameFrontendProxy::showCharacterSpellBook()
{
  Game::getInstance()->showCharacterSpellBook();
}

// Hide the spell book
void GameFrontendProxy::hideCharacterSpellBook()
{
  Game::getInstance()->hideCharacterSpellBook();
}

// Show the character stats
void GameFrontendProxy::showCharacterStats()
{
  Game::getInstance()->showCharacterStats();
}

// Hide the character stats
void GameFrontendProxy::hideCharacterStats()
{
  Game::getInstance()->hideCharacterStats();
}

// Show the quest log
void GameFrontendProxy::showQuestLog()
{
  Game::getInstance()->showQuestLog();
}

// Hide the quest log
void GameFrontendProxy::hideQuestLog()
{
  Game::getInstance()->hideQuestLog();
}

// Show the game menu
void GameFrontendProxy::showGameMenu()
{
  Game::getInstance()->showGameMenu();
}

// Hide the game menu
void GameFrontendProxy::hideGameMenu()
{
  Game::getInstance()->hideGameMenu();
}

// Show the game options menu
void GameFrontendProxy::showGameOptionsMenu()
{
  Game::getInstance()->showGameOptionsMenu();
}

// Hide the game options menu
void GameFrontendProxy::hideGameOptionsMenu()
{
  Game::getInstance()->hideGameOptionsMenu();
}

void GameFrontendProxy::redirectGameLoadStartedSignalToFrontend()
{
  emit gameLoadStarted();
}

void GameFrontendProxy::redirectGameLoadFinishedSignalToFrontend()
{
  emit gameLoadFinished();
}

void GameFrontendProxy::redirectGameSaveStartedSignalToFrontend()
{
  emit gameSaveStarted();
}

void GameFrontendProxy::redirectGameSaveFinishedSignalToFrontend()
{
  emit gameSaveFinished();
}

void GameFrontendProxy::redirectCharacterDeadSignalToFrontend()
{
  emit characterDead();
}

void GameFrontendProxy::redirectCharacterLeveledUpSignalToFrontend()
{
  emit characterLeveledUp();
}

void GameFrontendProxy::activateWidget()
{
  emit widgetActivated();
}

void GameFrontendProxy::deactivateWidget()
{
  emit widgetDeactivated();
}

// Get the object name
QString GameFrontendProxy::objectName()
{
  return "GameFrontendProxy";
}

QML_REGISTER_TYPE( GameFrontendProxy );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end GameFrontendProxy.cpp
//---------------------------------------------------------------------------//
