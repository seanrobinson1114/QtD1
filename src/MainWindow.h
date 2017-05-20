//---------------------------------------------------------------------------//
//!
//! \file   MainWindow.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The main window widget class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

// Std Lib Includes
#include <utility>

// Qt Includes
#include <QMainWindow>

// QtD1 Includes
#include "Sound.h"
#include "Music.h"
#include "Game.h"

namespace QtD1{

//! The main window class
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:

  //! Get the main window instance
  static MainWindow* getInstance();

  //! Destructor
  ~MainWindow();

  //! Load the widgets
  void loadWidgets();

  //! Show the main window
  void customShow();

  //! Check if the menu music is playing
  bool isMenuMusicPlaying();

signals:

  // These should only be used by the backend
  void introScreenActivated();
  void introScreenDeactivated();
  void titleScreenActivated();
  void titleScreenDeactivated();
  void mainMenuActivated();
  void mainMenuDeactivated();
  void creditsScreenActivated();
  void creditsScreenDeactivated();
  void multiPlayerMenuActivated();
  void multiPlayerMenuDeactivated();
  void singlePlayerMenuActivated();
  void singlePlayerMenuDeactivated();
  void gameActivated();
  void gameDeactivated();
  void gameMenuActivated();
  void gameMenuDeactivated();
  void imageViewerActivated();
  void imageViewerDeactivated();

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

private:

  // Typedef for activated signal pointer
  typedef void(MainWindow::*ActivatedSignalPointer)();

  // Typedef for deactivated signal pointer
  typedef ActivatedSignalPointer DeactivatedSignalPointer;

  //! Constructor
  MainWindow();

  // Activate the desired widget
  void activateWidget( QWidget* widget,
                       ActivatedSignalPointer activated_signal,
                       DeactivatedSignalPointer deactivated_signal );

  // The singleton instance
  // Note: the singleton instance is not encapsulated in a unique_ptr
  // because the default widget behavior is to delete-on-close.
  static MainWindow* s_instance;

  // The active widget
  std::pair<QWidget*,DeactivatedSignalPointer> d_active_widget;

  // The intro screen widget
  QWidget* d_intro_screen;

  // The title screen widget
  QWidget* d_title_screen;

  // The main menu widget
  QWidget* d_main_menu;

  // The credits screen widget
  QWidget* d_credits_screen;

  // The multi player menu widget
  QWidget* d_multi_player_menu;

  // The single player menu widget
  QWidget* d_single_player_menu;

  // The game widget
  Game* d_game;

  // The image viewer widget
  QWidget* d_image_viewer;

  // The menu item over sound
  Sound d_menu_item_over_sound;

  // The menu item click sound
  Sound d_menu_item_click_sound;

  // The menu music
  Music d_menu_music;

  // Tracks if the menu music is playing
  bool d_menu_music_playing;
};

} // end QtD1 namespace

#endif // end MAIN_WINDOW_H

//---------------------------------------------------------------------------//
// end MainWindow.h
//---------------------------------------------------------------------------//
