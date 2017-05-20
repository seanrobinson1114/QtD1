//---------------------------------------------------------------------------//
//!
//! \file   LoadingScreen.cpp
//! \author Alex Robinson
//! \brief  The loading screen class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include "LoadingScreen.h"

namespace QtD1{

// Constructor
LoadingScreen::LoadingScreen( QWidget* parent )
  : QWidget( parent ),
    d_new_game_load_background( new QLabel( this ) ),
    d_cathedral_load_background( new QLabel( this ) ),
    d_cathedral_stairs_load_background( new QLabel( this ) ),
    d_catacomb_stairs_load_background( new QLabel( this ) ),
    d_cave_stairs_load_background( new QLabel( this ) ),
    d_hell_stairs_load_background( new QLabel( this ) ),
    d_diablo_lair_load_background( new QLabel( this ) ),
    d_town_portal_load_background( new QLabel( this ) ),
    d_red_portal_load_background( new QLabel( this ) ),
    d_active_load_background( d_new_game_load_background ),
    d_status_bar( new QLabel( this ) ),
    d_number_of_assets_to_track( 0 ),
    d_number_of_assets_loaded( 0 )
{
  // Set the size of this widget
  this->setFixedSize( 800, 600 );
  
  // Load the backgrounds
  this->initializeBackground( "/gendata/cutstart.cel+gendata/cutstart.pal",
                              d_new_game_load_background );
  this->initializeBackground( "/gendata/cuttt.cel+gendata/cuttt.pal",
                              d_cathedral_load_background );
  this->initializeBackground( "/gendata/cutl1d.cel+gendata/cutl1d.pal",
                              d_cathedral_stairs_load_background );
  this->initializeBackground( "/gendata/cut2.cel+gendata/cut2.pal",
                              d_catacomb_stairs_load_background );
  this->initializeBackground( "/gendata/cut3.cel+gendata/cut3.pal",
                              d_cave_stairs_load_background );
  this->initializeBackground( "/gendata/cut4.cel+gendata/cut4.pal",
                              d_hell_stairs_load_background );
  this->initializeBackground( "/gendata/cutgate.cel+gendata/cutgate.pal",
                              d_diablo_lair_load_background );
  this->initializeBackground( "/gendata/cutportl.cel+gendata/cutportl.pal",
                              d_town_portal_load_background );
  this->initializeBackground( "/gendata/cutportr.cel+gendata/cutportr.pal",
                              d_red_portal_load_background );

  // Initialize the status bar
  QPixmap status_bar_background( QSize( 10, 10 ) );
  status_bar_background.fill( Qt::red );
  
  d_status_bar->setPixmap( status_bar_background );
  d_status_bar->setScaledContents( true );
  d_status_bar->setFixedHeight( 30 );
  d_status_bar->setMaximumWidth( 671 );
  d_status_bar->resize( 0, 30 );
  d_status_bar->move( 65, 525 );
}

// Initialize the desired label
void LoadingScreen::initializeBackground( const QString& source,
                                          QLabel* background )
{
  QImage background_image( source );

  background->setPixmap( QPixmap::fromImage(background_image) );
  background->setFixedSize( this->size() );
  background->setScaledContents( true );
}

// Tracking the asset load progression
void LoadingScreen::trackAssetLoadProgression( const Level* level,
                                               const Type loading_screen )
{
  // Activate the requested loading screen
  switch( loading_screen )
  {
    case newGame:
    {
      d_active_load_background = d_new_game_load_background;
      break;
    }
    case cathedral:
    {
      d_active_load_background = d_cathedral_load_background;
      break;
    }
    case cathedralStairs:
    {
      d_active_load_background = d_cathedral_stairs_load_background;
      break;
    }
    case catacombStairs:
    {
      d_active_load_background = d_catacomb_stairs_load_background;
      break;
    }
    case caveStairs:
    {
      d_active_load_background = d_cave_stairs_load_background;
      break;
    }
    case hellStairs:
    {
      d_active_load_background = d_hell_stairs_load_background;
      break;
    }
    case diabloLair:
    {
      d_active_load_background = d_diablo_lair_load_background;
      break;
    }
    case townPortal:
    {
      d_active_load_background = d_town_portal_load_background;
      break;
    }
    case redPortal:
    {
      d_active_load_background = d_red_portal_load_background;
      break;
    }
    default:
    {
      qWarning( "Unknown loading screen requested! The red portal loading "
                "screen will be used." );
      d_active_load_background = d_red_portal_load_background;
    }
  }

  // Connect the level signals to the loading screen slots
  QObject::connect( level, SIGNAL(assetLoadingStarted(const int)),
                    this, SLOT(startTrackingAssetLoadProgression(const int)) );
  QObject::connect( level, SIGNAL(assetLoaded(const int)),
                    this, SLOT(updateAssetLoadProgression(const int)) );
  QObject::connect( level, SIGNAL(assetLoadingFinished(const int)),
                    this, SLOT(finishTrackingAssetLoadProgression()) );
}

// Start tracking the asset load progression
void LoadingScreen::startTrackingAssetLoadProgression(
                                                   const int number_of_assets )
{
  d_number_of_assets_to_track = number_of_assets;
  d_number_of_assets_loaded = 0;
}

// Update the load status
void LoadingScreen::updateAssetLoadProgression(
                                            const int number_of_assets_loaded )
{
  // Increment the number of assets loaded
  d_number_of_assets_loaded = number_of_assets_loaded;

  double fraction_loaded =
    std::min( d_number_of_assets_loaded/(double)d_number_of_assets_to_track,
              1.0 );

  // Update the status bar width
  int width;

  if( fraction_loaded > 0.0 && fraction_loaded < 1.0 )
    width = d_status_bar->maximumWidth()*fraction_loaded;
  else if( fraction_loaded <= 0.0 )
    width = 0;
  else
    width = d_status_bar->maximumWidth();

  d_status_bar->resize( width, d_status_bar->height() );

  // Schedule a screen update
  this->update();
}

// Finish tracking the asset load progression
void LoadingScreen::finishTrackingAssetLoadProgression()
{
  d_number_of_assets_to_track = 0;
  d_number_of_assets_loaded = 0;

  // Disconnect the level signals to the loading screen slots
  QObject::disconnect( this, SLOT(startTrackingAssetLoadProgression(const int)) );
  QObject::disconnect( this, SLOT(updateAssetLoadProgression(const int)) );
  QObject::disconnect( this, SLOT(finishTrackingAssetLoadProgression()) );
}

// Handle show events
void LoadingScreen::showEvent( QShowEvent* event )
{
  QWidget::showEvent( event );
  
  // Hide all of the backgrounds
  d_new_game_load_background->hide();
  d_cathedral_load_background->hide();
  d_cathedral_stairs_load_background->hide();
  d_catacomb_stairs_load_background->hide();
  d_cave_stairs_load_background->hide();
  d_hell_stairs_load_background->hide();
  d_diablo_lair_load_background->hide();
  d_town_portal_load_background->hide();
  d_red_portal_load_background->hide();

  // Show the active background and bring it to the front
  d_active_load_background->show();
  d_active_load_background->raise();

  // Show the status bar and bring it to the front
  d_status_bar->show();
  d_status_bar->raise();
}

// Handle hide events
void LoadingScreen::hideEvent( QHideEvent* event )
{
  QWidget::hideEvent( event );

  // Reset the status bar
  d_status_bar->resize( 0, d_status_bar->height() );
}

  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LoadingScreen.cpp
//---------------------------------------------------------------------------//
