//---------------------------------------------------------------------------//
//!
//! \file   GameFrontendProxy.h
//! \author Alex Robinson
//! \brief  The game frontend proxy class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GAME_FRONTEND_PROXY
#define GAME_FRONTEND_PROXY

// Qt Includes
#include <QObject>

// QtD1 Includes
#include "QMLRegistrationHelper.h"
#include "LoadingScreen.h"
#include "Character.h"

namespace QtD1{

//! The game frontend proxy class
class GameFrontendProxy : public QObject
{
  Q_OBJECT
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "GameBackend" )

public:

  //! Constructor
  GameFrontendProxy( QObject* parent = 0 );

  //! Destructor
  ~GameFrontendProxy()
  { /* ... */ }

  //! Connect to the backend
  static void connectToBackend( QDeclarativeView* frontend_widget,
                                const char* activated_backend_signal,
                                const char* deactivated_backend_signal );

signals:

  void widgetActivated();
  void widgetDeactivated();

  void gameLoadStarted();
  void gameLoadFinished();
  void gameSaveStarted();
  void gameSaveFinished();
  void characterDead();
  void characterLeveledUp();
  void characterStatsChanged();

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

  void redirectGameLoadStartedSignalToFrontend();
  void redirectGameLoadFinishedSignalToFrontend();
  void redirectGameSaveStartedSignalToFrontend();
  void redirectGameSaveFinishedSignalToFrontend();
  void redirectCharacterDeadSignalToFrontend();
  void redirectCharacterLeveledUpSignalToFrontend();
  void activateWidget();
  void deactivateWidget();

private:

  // Get the object name
  static QString objectName();
};

} // end QtD1 namespace

#endif // end GAME_FRONTEND_PROXY

//---------------------------------------------------------------------------//
// end GameFrontendProxy.h
//---------------------------------------------------------------------------//
