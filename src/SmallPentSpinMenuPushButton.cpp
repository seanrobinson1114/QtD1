//---------------------------------------------------------------------------//
//!
//! \file   SmallPentSpinMenuPushButton.cpp
//! \author Alex Robinson
//! \brief  The small pent spin menu push button class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "SmallPentSpinMenuPushButton.h"
#include "MenuSprite.h"

namespace QtD1{

QVector<QPixmap> SmallPentSpinMenuPushButton::s_pent_spin_frames;

// Constructor
SmallPentSpinMenuPushButton::SmallPentSpinMenuPushButton(
                                               const QString& button_text,
                                               const QString& bitmap_font_name,
                                               QWidget* parent )
  : MenuPushButton( button_text, bitmap_font_name, parent ),
    d_pent_spin_timer_id( -1 ),
    d_pent_spin_frame_index( 0 ),
    d_left_pent_spin( NULL ),
    d_right_pent_spin( NULL ),
    d_up_button( this ),
    d_down_button( this )
{
  // Initialize the pent spin frames
  this->initializePentSpinFrames();

  // Create pent spin regions
  d_left_pent_spin = new QLabel( this );
  d_left_pent_spin->resize( QSize(12, 12) );
  
  d_right_pent_spin = new QLabel( this );
  d_right_pent_spin->resize( QSize(12, 12) );

  // Resize the button
  int width = this->width()+48;
  int height = this->height();

  if( height < 12 )
    height = 12;
  
  this->resize( QSize(width, height) );

  // Move the pent spin regions to the correct locations
  int y_position = (this->height() - d_left_pent_spin->height())/2;

  if( y_position < 0 )
    y_position *= -1;
  
  d_left_pent_spin->move( 0, y_position );
  d_right_pent_spin->move( this->width() - 12, y_position );
}

// Initialize the pent spint frames
void SmallPentSpinMenuPushButton::initializePentSpinFrames()
{
  if( s_pent_spin_frames.empty() )
  {
    MenuSprite menu_sprite;
    menu_sprite.setSource( "/data/pentspn2.cel+levels/towndata/town.pal" );
    menu_sprite.loadSync();

    menu_sprite.getFrames( s_pent_spin_frames );
  }
}

// Activate the button
void SmallPentSpinMenuPushButton::activate()
{
  // Show the pent spins
  d_left_pent_spin->setPixmap( s_pent_spin_frames.front() );
  d_left_pent_spin->show();
  d_left_pent_spin->raise();

  d_left_pent_spin->setPixmap( s_pent_spin_frames.front() );
  d_right_pent_spin->show();
  d_right_pent_spin->raise();

  d_pent_spin_frame_index = 0;

  // Start the pent spin animation timer
  d_pent_spin_timer_id = this->startTimer( 37 );
}

// Deactivate the button
void SmallPentSpinMenuPushButton::deactivate()
{
  // Hide the pent spins
  d_left_pent_spin->hide();
  d_right_pent_spin->hide();
  
  d_pent_spin_frame_index = 0;

  // Stop the pent spin animation timer
  this->killTimer( d_pent_spin_timer_id );
  d_pent_spin_timer_id = -1;
}

// Set the "up" (above) button 
void SmallPentSpinMenuPushButton::setUpButton( SmallPentSpinMenuPushButton* up_button )
{
  d_up_button = up_button;
}

// Get the "up" (above) button
SmallPentSpinMenuPushButton* SmallPentSpinMenuPushButton::getUpButton() const
{
  return d_up_button;
}

// Set the "down" (below) button
void SmallPentSpinMenuPushButton::setDownButton( SmallPentSpinMenuPushButton* down_button )
{
  d_down_button = down_button;
}

// Get the "down" (below) button
SmallPentSpinMenuPushButton* SmallPentSpinMenuPushButton::getDownButton() const
{
  return d_down_button;
}

// Handle hide events
void SmallPentSpinMenuPushButton::hideEvent( QHideEvent* event )
{
  this->deactivate();
}

// Handle the timer event
void SmallPentSpinMenuPushButton::timerEvent( QTimerEvent* event )
{
  this->incrementPentSpinFrame();
}

// Increment pent spin frame
void SmallPentSpinMenuPushButton::incrementPentSpinFrame()
{
  d_pent_spin_frame_index = (d_pent_spin_frame_index+1)%s_pent_spin_frames.size();

  d_left_pent_spin->setPixmap( s_pent_spin_frames[d_pent_spin_frame_index] );
  d_right_pent_spin->setPixmap( s_pent_spin_frames[d_pent_spin_frame_index] );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SmallPentSpinMenuPushButton.cpp
//---------------------------------------------------------------------------//
