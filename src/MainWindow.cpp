//---------------------------------------------------------------------------//
//!
//! \file   MainWindow.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The main window widget class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QFontDatabase>
#include <QtDeclarative/QDeclarativeView>

// QtD1 Includes
#include "MainWindow.h"
#include "MainWindowFrontendProxy.h"
#include "MPQHandler.h"
#include "AudioDevice.h"
#include "BitmapText.h"
#include "Cursor.h"
#include "Game.h"
#include "qtd1_config.h"

namespace QtD1{

// Initialize static member data
MainWindow* MainWindow::s_instance;

// Get the main window instance
MainWindow* MainWindow::getInstance()
{
  if( !s_instance )
    s_instance = new MainWindow;

  return s_instance;
}

// Constructor
MainWindow::MainWindow()
  : QMainWindow(),
    d_active_widget()
{
  // Force this to delete when closed
  this->setAttribute( Qt::WA_DeleteOnClose );
  
  // Register the MPQHandler with the file engine system
  QtD1::MPQHandler::getInstance();

  // Open the audio device
  QtD1::AudioDevice::getInstance().open();

  // Register freemono fonts
  QFontDatabase::addApplicationFont( FREE_MONO_TTF_PATH );
  QFontDatabase::addApplicationFont( FREE_MONO_BOLD_TTF_PATH );
  QFontDatabase::addApplicationFont( FREE_MONO_OBLIQUE_TTF_PATH );
  QFontDatabase::addApplicationFont( FREE_MONO_BOLD_OBLIQUE_TTF_PATH );

  // Load qtd1 bitmap fonts
  QtD1::BitmapText::loadStandardFonts();

  // Tell the main window to use the custom UI cursor
  QtD1::Cursor::getInstance()->setWidgetToManage( this );
  QtD1::Cursor::getInstance()->activateUICursor();

  // Create the menu item over sound
  d_menu_item_over_sound.setSource( "/sfx/items/titlemov.wav" );

  // Create the menu item click sound
  d_menu_item_click_sound.setSource( "/sfx/items/titlslct.wav" );

  // Create the menu music
  d_menu_music.setSource( "/music/dintro.wav" );
  d_menu_music_playing = false;
}

// Destructor
MainWindow::~MainWindow()
{ /* ... */ }

// Load the widgets
void MainWindow::loadWidgets()
{
  // Create the background widget
  QWidget* background = new QWidget( this );
  {
    QPalette palette;
    palette.setColor( background->backgroundRole(), Qt::black );
    background->setPalette(palette);
    background->setFixedSize( 800, 600 );
    background->show();

    this->setCentralWidget( background );
  }

  // Create the intro screen widget
  {
    QDeclarativeView* intro_screen_view =
      new QDeclarativeView( QUrl(INTRO_SCREEN_QML_PATH), background );

    MainWindowFrontendProxy::connectToBackend(
                                            intro_screen_view,
                                            SIGNAL(introScreenActivated()),
                                            SIGNAL(introScreenDeactivated()) );

    d_intro_screen = intro_screen_view;
  }

  // Create the title screen widget
  {
    QDeclarativeView* title_screen_view =
      new QDeclarativeView( QUrl(TITLE_SCREEN_QML_PATH), background );

    MainWindowFrontendProxy::connectToBackend(
                                            title_screen_view,
                                            SIGNAL(titleScreenActivated()),
                                            SIGNAL(titleScreenDeactivated()) );

    d_title_screen = title_screen_view;
  }

  // Create the main menu widget
  {
    QDeclarativeView* main_menu_view =
      new QDeclarativeView( QUrl(MAIN_MENU_QML_PATH), background );

    MainWindowFrontendProxy::connectToBackend( main_menu_view,
                                               SIGNAL(mainMenuActivated()),
                                               SIGNAL(mainMenuDeactivated()) );

    // Connect the main menu quit button to the close slot
    QObject::connect( main_menu_view->engine(), SIGNAL(quit()),
                      this, SLOT(close()) );

    d_main_menu = main_menu_view;
  }

  // Create the credits screen widget
  {
    QDeclarativeView* credits_screen_view =
      new QDeclarativeView( QUrl(CREDITS_SCREEN_QML_PATH), background );

    MainWindowFrontendProxy::connectToBackend(
                                          credits_screen_view,
                                          SIGNAL(creditsScreenActivated()),
                                          SIGNAL(creditsScreenDeactivated()) );

    d_credits_screen = credits_screen_view;
  }

  // Create the multi player menu widget
  d_multi_player_menu = new QWidget( background );

  // Create the single player menu widget
  {
    QDeclarativeView* single_player_menu_view =
      new QDeclarativeView( QUrl(SINGLE_PLAYER_MENU_QML_PATH), background );

    MainWindowFrontendProxy::connectToBackend(
                                       single_player_menu_view,
                                       SIGNAL(singlePlayerMenuActivated()),
                                       SIGNAL(singlePlayerMenuDeactivated()) );

    d_single_player_menu = single_player_menu_view;
  }

  // Create the game widget
  {
    d_game = Game::getInstance();
    d_game->setParent( background );

    // Connect the main menu quit button to the close slot
    QObject::connect( d_game->getGameMenu()->engine(), SIGNAL(quit()),
                      this, SLOT(close()) );
  }

  // Create the image viewer widget
  {
    QDeclarativeView* image_viewer_view =
      new QDeclarativeView( QUrl(IMAGE_VIEWER_QML_PATH), background );

    MainWindowFrontendProxy::connectToBackend(
                                            image_viewer_view,
                                            SIGNAL(imageViewerActivated()),
                                            SIGNAL(imageViewerDeactivated()) );

    d_image_viewer = image_viewer_view;
  }
}

// Show the main window
void MainWindow::customShow()
{
  // This call to show will show all of the child widgets (not what we want)
  this->show();

  // Deactive all of the widgets that we manage separately
  d_intro_screen->hide();
  d_title_screen->hide();
  d_main_menu->hide();
  d_credits_screen->hide();
  d_multi_player_menu->hide();
  d_single_player_menu->hide();
  d_game->hide();
  d_image_viewer->hide();
}

// Check if the menu music is playing
bool MainWindow::isMenuMusicPlaying()
{
  return MainWindow::getInstance()->d_menu_music_playing;
}

// Go to the intro screen
void MainWindow::gotoIntroScreen()
{
  this->activateWidget( d_intro_screen,
                        &MainWindow::introScreenActivated,
                        &MainWindow::introScreenDeactivated );
}

// Go to the title screen
void MainWindow::gotoTitleScreen()
{
  this->activateWidget( d_title_screen,
                        &MainWindow::titleScreenActivated,
                        &MainWindow::titleScreenDeactivated );
}

// Go to the main menu
void MainWindow::gotoMainMenu()
{
  this->activateWidget( d_main_menu,
                        &MainWindow::mainMenuActivated,
                        &MainWindow::mainMenuDeactivated );
}

// Go to the credits screen
void MainWindow::gotoCreditsScreen()
{
  this->activateWidget( d_credits_screen,
                        &MainWindow::creditsScreenActivated,
                        &MainWindow::creditsScreenDeactivated );
}

// Go to the multi player menu
void MainWindow::gotoMultiPlayerMenu()
{
  this->activateWidget( d_multi_player_menu,
                        &MainWindow::multiPlayerMenuActivated,
                        &MainWindow::multiPlayerMenuDeactivated );
}

// Go to the single player menu
void MainWindow::gotoSinglePlayerMenu()
{
  this->activateWidget( d_single_player_menu,
                        &MainWindow::singlePlayerMenuActivated,
                        &MainWindow::singlePlayerMenuDeactivated );
}

// Go to the game
void MainWindow::gotoGame( const QString& character_name,
                           const int character_class )
{
  this->activateWidget( d_game,
                        &MainWindow::gameActivated,
                        &MainWindow::gameDeactivated );
  
  this->d_game->create( character_name, character_class );
}

// Go to the image viewer
void MainWindow::gotoImageViewer()
{
  this->activateWidget( d_image_viewer,
                        &MainWindow::imageViewerActivated,
                        &MainWindow::imageViewerDeactivated );
}

// Activate the desired widget
void MainWindow::activateWidget( QWidget* widget,
                                 ActivatedSignalPointer activated_signal,
                                 DeactivatedSignalPointer deactivated_signal )
{
  if( d_active_widget.first )
  {
    d_active_widget.first->hide();
    emit (this->*d_active_widget.second)();
  }

  d_active_widget.first = widget;
  d_active_widget.second = deactivated_signal;

  d_active_widget.first->show();
  d_active_widget.first->setFocus();
  emit (this->*activated_signal)();
}

// Play menu item over sound
void MainWindow::playMenuItemOverSound()
{
  d_menu_item_over_sound.playSound();
}

// Play menu item click sound
void MainWindow::playMenuItemClickSound()
{
  d_menu_item_click_sound.playSound();
}

// Play menu music
void MainWindow::playMenuMusic()
{
  d_menu_music.playMusic();
  d_menu_music_playing = true;
}

// Pause menu music
void MainWindow::pauseMenuMusic()
{
  d_menu_music.pauseMusic();
  d_menu_music_playing = false;
}

// Stop menu music
void MainWindow::stopMenuMusic()
{
  d_menu_music.stopMusic();
  d_menu_music_playing = false;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MainWindow.cpp
//---------------------------------------------------------------------------//
