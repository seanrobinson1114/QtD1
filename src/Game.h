//---------------------------------------------------------------------------//
//!
//! \file   Game.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The game class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GAME_H
#define GAME_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QWidget>
#include <QGraphicsView>
#include <QString>

// QtD1 Includes
#include "Level.h"
#include "LoadingScreen.h"
#include "Character.h"
#include "Sound.h"

namespace QtD1{

//! The game class
class Game : public QWidget
{
  Q_OBJECT

public:

  //! Get the game instance
  static Game* getInstance();

  //! Destructor
  ~Game();

  //! Get the game menu
  QDeclarativeView* getGameMenu();

signals:

  void gameLoadStarted();
  void gameLoadFinished();
  void gameSaveStarted();
  void gameSaveFinished();
  void characterDead();
  void characterLeveledUp();
  void characterStatsChanged();

  void gameRunning();
  void gamePaused();
  void gameQuit();
  void controlPanelWidgetActivated();
  void controlPanelWidgetDeactivated();
  void characterStatsWidgetActivated();
  void characterStatsWidgetDeactivated();
  void inventoryWidgetActivated();
  void inventoryWidgetDeactivated();
  void spellBookWidgetActivated();
  void spellBookWidgetDeactivated();
  void gameMenuWidgetActivated();
  void gameMenuWidgetDeactivated();
  void gameOptionsMenuWidgetActivated();
  void gameOptionsMenuWidgetDeactivated();

public slots:

  //! Create a new game
  void create( const QString& character_name,
               const int character_class );

  //! Restore a previous game
  void restore( const QString& character_name );

  //! Pause the game
  void pause();

  //! Resume the game
  void resume();

  //! Quit the game (and go back to main menu)
  void quit();

  //! Save the game
  void save();

  //! Play the game music
  void playGameMusic();

  //! Pause game music
  void pauseGameMusic();

  //! Stop game music
  void stopGameMusic();

  //! Play menu item over sound
  void playMenuItemOverSound();

  //! Play menu item click sound
  void playMenuItemClickSound();

  //! Play control panel click sound
  void playControlPanelClickSound();

  //! Set the game music volume
  void setGameMusicVolume( int volume );

  //! Set the game sound volume
  void setGameSoundVolume( int volume );

  //! Show the loading screen
  void showLoadingScreen();

  //! Hide the loading screen
  void hideLoadingScreen();

  //! Show the level viewer
  void showLevelViewer();

  //! Hide the level viewer
  void hideLevelViewer();

  //! Show the character inventory
  void showCharacterInventory();

  //! Hide the character inventory
  void hideCharacterInventory();

  //! Show the spell book
  void showCharacterSpellBook();

  //! Hide the spell book
  void hideCharacterSpellBook();

  //! Show the character stats
  void showCharacterStats();

  //! Hide the character stats
  void hideCharacterStats();

  //! Show the quest log
  void showQuestLog();

  //! Hide the quest log
  void hideQuestLog();

  //! Show the game menu
  void showGameMenu();

  //! Hide the game menu
  void hideGameMenu();

  //! Show the game options menu
  void showGameOptionsMenu();

  //! Hide the game options menu
  void hideGameOptionsMenu();

private slots:

  // Game event slots
  void handleCharacterLevelUp( const int new_level );
  void handleCharacterDeath();

  void handleTownAssetLoadStarted();
  void handleTownAssetLoadFinished();
  void handleLevelAssetLoadStarted();
  void handleLevelAssetLoadFinished();

protected:

  //! Handle show events
  void showEvent( QShowEvent* event ) override;

  //! Handle hide events
  void hideEvent( QHideEvent* event ) override;

  //! Handle resize event
  void resizeEvent( QResizeEvent* event ) override;

  //! Handle the timer event
  void timerEvent( QTimerEvent* event ) override;

  //! Handle key press events
  void keyPressEvent( QKeyEvent* event ) override;

  //! Handle key release events
  void keyReleaseEvent( QKeyEvent* event ) override;

  //! Handle mouse move events
  void mouseMoveEvent( QMouseEvent* event ) override;

  //! Handle mouse press event
  void mousePressEvent( QMouseEvent* event ) override;

  //! Handle mouse release event
  void mouseReleaseEvent( QMouseEvent* event ) override;

  //! Handle mouse double-click event
  void mouseDoubleClickEvent( QMouseEvent* event ) override;

private:

  // Typedef for activated widget signal pointer
  typedef void(Game::*ActivatedWidgetSignalPointer)();

  // Typedef for deactivated widget signal pointer
  typedef ActivatedWidgetSignalPointer DeactivatedWidgetSignalPointer;

  // Constructor
  Game();

  // Connect the character signals to the game slots
  void connectCharacterSignalsToGameSlots();

  // Connect the frontend to the backend
  void connectFrontendToBackend( QDeclarativeView* frontend_widget,
                                 const char* activated_signal,
                                 const char* deactivated_signal );

  // The game state refresh delay time (ms)
  static const int s_refresh_delay_time = 10;

  // The singleton instance
  static Game* s_instance;

  // The character
  std::unique_ptr<Character> d_character;

  // The game timer id
  int d_game_timer_id;

  // Check if the game is paused
  bool d_game_paused;

  // The game loading screen
  LoadingScreen* d_loading_screen;

  // The game control panel
  QDeclarativeView* d_game_control_panel;

  // The character stats
  QDeclarativeView* d_character_stats;

  // The game menu
  QDeclarativeView* d_game_menu;

  // The game options menu
  QDeclarativeView* d_game_options_menu;

  // The level
  Level* d_level;

  // The level viewer
  QGraphicsView* d_level_viewer;

  // The menu item over sound
  Sound d_game_menu_item_over_sound;

  // The menu item click sound
  Sound d_game_menu_item_click_sound;

  // The control panel click sound
  Sound d_control_panel_click_sound;
};

} // end QtD1 namespace

#endif // end GAME_H

//---------------------------------------------------------------------------//
// end Game.h
//---------------------------------------------------------------------------//
