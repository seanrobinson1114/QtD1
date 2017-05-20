//---------------------------------------------------------------------------//
//!
//! \file   LoadingScreen.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The loading screen class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

// Qt Includes
#include <QWidget>
#include <QLabel>

// QtD1 Includes
#include "Level.h"

namespace QtD1{

//! The loading screen class
class LoadingScreen : public QWidget
{
  Q_OBJECT

public:

  //! The loading screen types
  enum Type{
    newGame,
    cathedral,
    cathedralStairs,
    catacombStairs,
    caveStairs,
    hellStairs,
    diabloLair,
    townPortal,
    redPortal
  };
  Q_ENUMS( Type )

  //! Constructor
  LoadingScreen( QWidget* parent = 0 );

  //! Destructor
  ~LoadingScreen()
  { /* ... */ }

  //! Tracking the asset load progression for the new level
  void trackAssetLoadProgression( const Level* level,
                                  const Type loading_screen ); 

protected:

  //! Handle show events
  void showEvent( QShowEvent* event ) override;

  //! Handle hide events
  void hideEvent( QHideEvent* event ) override;

private slots:

  // Start tracking the asset load progression
  void startTrackingAssetLoadProgression( const int number_of_assets );

  // Update the load status
  void updateAssetLoadProgression( const int number_of_assets_loaded );

  // Finish tracking the asset load progression
  void finishTrackingAssetLoadProgression();

private:

  // Initialize the desired label
  void initializeBackground( const QString& source, QLabel* background );

  // The new game load background
  QLabel* d_new_game_load_background;

  // The cathedral load background
  QLabel* d_cathedral_load_background;

  // The cathedral stairs load background
  QLabel* d_cathedral_stairs_load_background;

  // The catacomb stairs load background
  QLabel* d_catacomb_stairs_load_background;

  // The cave stairs load background
  QLabel* d_cave_stairs_load_background;

  // The hell stairs load background
  QLabel* d_hell_stairs_load_background;

  // The diablo lair load background
  QLabel* d_diablo_lair_load_background;

  // The town portal load background
  QLabel* d_town_portal_load_background;

  // The red portal load background
  QLabel* d_red_portal_load_background;

  // The active load background
  QLabel* d_active_load_background;

  // The status bar
  QLabel* d_status_bar;

  // The number of assets to track
  int d_number_of_assets_to_track;

  // The number of assets that have been loaded
  int d_number_of_assets_loaded;
};
  
} // end QtD1 namespace

#endif // end LOADING_SCREEN_H

//---------------------------------------------------------------------------//
// end LoadingScreen.h
//---------------------------------------------------------------------------//
