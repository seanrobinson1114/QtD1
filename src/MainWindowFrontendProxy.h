//---------------------------------------------------------------------------//
//!
//! \file   MainWindowFrontendProxy.h
//! \author Alex Robinson
//! \brief  The main window frontend proxy class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MAIN_WINDOW_FRONTEND_PROXY
#define MAIN_WINDOW_FRONTEND_PROXY

// Qt Includes
#include <QObject>

// QtD1 Includes
#include "QMLRegistrationHelper.h"

namespace QtD1{

//! Main window frontend proxy class
class MainWindowFrontendProxy : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool menuMusicPlaying READ isMenuMusicPlaying)
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "UIBackend" )
  
public:

  //! Constructor
  MainWindowFrontendProxy( QObject* parent = 0 );

  //! Destructor
  ~MainWindowFrontendProxy()
  { /* ... */ }

  //! Check if the menu music is playing
  bool isMenuMusicPlaying();

  //! Connect to the backend
  static void connectToBackend( QDeclarativeView* frontend,
                                const char* activated_backend_signal,
                                const char* deactivated_backend_signal );

signals:

  void screenActivated();
  void screenDeactivated();

public slots:

  //! Go to the intro screen
  void gotoIntroScreen();
  
  //! Go to the title screen
  void gotoTitleScreen();
  
  //! Go to the main menu
  void gotoMainMenu();
  
  //! Go to the credits screen
  void gotoCreditsScreen();
  
  //! Go to the multi player menu
  void gotoMultiPlayerMenu();
  
  //! Go to the single player menu
  void gotoSinglePlayerMenu();
  
  //! Go to the game
  void gotoGame( const QString& character_name,
                 const int character_class );
  
  //! Go to the image viewer
  void gotoImageViewer();
  
  //! Play menu item over sound
  void playMenuItemOverSound();
  
  //! Play menu item click sound
  void playMenuItemClickSound();
  
  //! Play menu music
  void playMenuMusic();
  
  //! Pause menu music
  void pauseMenuMusic();
  
  //! Stop menu music
  void stopMenuMusic();

  // These slots should only be used by the backend
  void activateScreen();
  void deactivateScreen();

private:

  // Get the object name
  static QString objectName();
};

} // end QtD1 namespace

#endif // end MAIN_WINDOW_FRONTEND_PROXY

//---------------------------------------------------------------------------//
// end MainWindowFrontendProxy.h
//---------------------------------------------------------------------------//
