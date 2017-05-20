//---------------------------------------------------------------------------//
//!
//! \file   MainWindowFrontendProxy.cpp
//! \author Alex Robinson
//! \brief  The main window frontend proxy class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "MainWindowFrontendProxy.h"
#include "MainWindow.h"

namespace QtD1{

// Constructor
MainWindowFrontendProxy::MainWindowFrontendProxy( QObject* parent )
  : QObject( parent )
{ 
  this->setObjectName( this->objectName() );
}

// Check if the menu music is playing
bool MainWindowFrontendProxy::isMenuMusicPlaying()
{
  return MainWindow::getInstance()->isMenuMusicPlaying();
}

// Connect to the backend
void MainWindowFrontendProxy::connectToBackend(
                                       QDeclarativeView* frontend,
                                       const char* activated_backend_signal,
                                       const char* deactivated_backend_signal )
{
  QObject* root_object = frontend->rootObject();

  QList<MainWindowFrontendProxy*> main_window_frontends = root_object->findChildren<MainWindowFrontendProxy*>( MainWindowFrontendProxy::objectName() );

  if( main_window_frontends.size() != 1 )
  {
    qFatal( "Error: QtD1 frontend %s has been improperly set up!",
            frontend->source().toString().toStdString().c_str() );
  }
  else
  {
    MainWindowFrontendProxy* main_window_frontend = main_window_frontends[0];

    QObject::connect( MainWindow::getInstance(), activated_backend_signal,
                      main_window_frontend, SLOT(activateScreen()) );
    QObject::connect( MainWindow::getInstance(), deactivated_backend_signal,
                      main_window_frontend, SLOT(deactivateScreen()) );
  }
}

// Get the object name
QString MainWindowFrontendProxy::objectName()
{
  return "MainWindowFrontendProxy";
}

// Activate the screen
void MainWindowFrontendProxy::activateScreen()
{
  emit screenActivated();
}
  
// Deactivate the screen
void MainWindowFrontendProxy::deactivateScreen()
{
  emit screenDeactivated();
}

// Go to the intro screen
void MainWindowFrontendProxy::gotoIntroScreen()
{
  MainWindow::getInstance()->gotoIntroScreen();
}
  
// Go to the title screen
void MainWindowFrontendProxy::gotoTitleScreen()
{
  MainWindow::getInstance()->gotoTitleScreen();
}
  
// Go to the main menu
void MainWindowFrontendProxy::gotoMainMenu()
{
  MainWindow::getInstance()->gotoMainMenu();
}
  
// Go to the credits screen
void MainWindowFrontendProxy::gotoCreditsScreen()
{
  MainWindow::getInstance()->gotoCreditsScreen();
}
  
// Go to the multi player menu
void MainWindowFrontendProxy::gotoMultiPlayerMenu()
{
  MainWindow::getInstance()->gotoMultiPlayerMenu();
}
  
// Go to the single player menu
void MainWindowFrontendProxy::gotoSinglePlayerMenu()
{
  MainWindow::getInstance()->gotoSinglePlayerMenu();
}
  
// Go to the game
void MainWindowFrontendProxy::gotoGame( const QString& character_name,
                                        const int character_class )
{
  MainWindow::getInstance()->gotoGame( character_name, character_class );
}
  
// Go to the image viewer
void MainWindowFrontendProxy::gotoImageViewer()
{
  MainWindow::getInstance()->gotoImageViewer();
}
  
// Play menu item over sound
void MainWindowFrontendProxy::playMenuItemOverSound()
{
  MainWindow::getInstance()->playMenuItemOverSound();
}
  
// Play menu item click sound
void MainWindowFrontendProxy::playMenuItemClickSound()
{
  MainWindow::getInstance()->playMenuItemClickSound();
}
  
// Play menu music
void MainWindowFrontendProxy::playMenuMusic()
{
  MainWindow::getInstance()->playMenuMusic();
}
  
// Pause menu music
void MainWindowFrontendProxy::pauseMenuMusic()
{
  MainWindow::getInstance()->pauseMenuMusic();
}
  
// Stop menu music
void MainWindowFrontendProxy::stopMenuMusic()
{
  MainWindow::getInstance()->stopMenuMusic();
}

QML_REGISTER_TYPE( MainWindowFrontendProxy );
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MainWindowFrontendProxy.cpp
//---------------------------------------------------------------------------//
