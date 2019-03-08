//---------------------------------------------------------------------------//
//!
//! \file   PentSpinMenuPushButton.cpp
//! \author Alex Robinson
//! \brief  The pent spin menu push button class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "PentSpinMenuPushButton.h"

namespace QtD1{

// Constructor
PentSpinMenuPushButton::PentSpinMenuPushButton(
                                               const QString& button_text,
                                               const QString& bitmap_font_name,
                                               const int pent_width,
                                               const int pent_height,
                                               QWidget* parent )
  : MenuPushButton( button_text, bitmap_font_name, parent ),
    d_pent_spin_timer_id( -1 ),
    d_pent_spin_frame_index( 0 ),
    d_left_pent_spin( NULL ),
    d_right_pent_spin( NULL ),
    d_up_button( this ),
    d_down_button( this )
{
  // Create pent spin regions
  d_left_pent_spin = new QLabel( this );
  d_left_pent_spin->resize( QSize(pent_width, pent_height) );
  
  d_right_pent_spin = new QLabel( this );
  d_right_pent_spin->resize( QSize(pent_width, pent_height) );

  // Resize the button
  int width = this->width()+pent_width*4;
  int height = this->height();

  if( height < pent_height )
    height = pent_height;
  
  this->resize( QSize(width, height) );

  // Move the pent spin regions to the correct locations
  int y_position = (this->height() - pent_height)/2;

  if( y_position < 0 )
    y_position *= -1;
  
  d_left_pent_spin->move( 0, y_position );
  d_right_pent_spin->move( this->width() - pent_width, y_position );
}

// Activate the button
void PentSpinMenuPushButton::activate()
{
  d_pent_spin_frame_index = 0;
  
  // Show the pent spins
  d_left_pent_spin->setPixmap( this->getPentSpinFrame( d_pent_spin_frame_index ) );
  d_left_pent_spin->show();
  d_left_pent_spin->raise();

  d_left_pent_spin->setPixmap( this->getPentSpinFrame( d_pent_spin_frame_index ) );
  d_right_pent_spin->show();
  d_right_pent_spin->raise();

  // Start the pent spin animation timer
  d_pent_spin_timer_id = this->startTimer( 37 );
}

// Deactivate the button
void PentSpinMenuPushButton::deactivate()
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
void PentSpinMenuPushButton::setUpButton( PentSpinMenuPushButton* up_button )
{
  d_up_button = up_button;
}

// Get the "up" (above) button
PentSpinMenuPushButton* PentSpinMenuPushButton::getUpButton() const
{
  return d_up_button;
}

// Set the "down" (below) button
void PentSpinMenuPushButton::setDownButton( PentSpinMenuPushButton* down_button )
{
  d_down_button = down_button;
}

// Get the "down" (below) button
PentSpinMenuPushButton* PentSpinMenuPushButton::getDownButton() const
{
  return d_down_button;
}

// Handle hide events
void PentSpinMenuPushButton::hideEvent( QHideEvent* event )
{
  this->deactivate();
}

// Handle the timer event
void PentSpinMenuPushButton::timerEvent( QTimerEvent* event )
{
  this->incrementPentSpinFrame( d_pent_spin_frame_index );

  d_left_pent_spin->setPixmap( this->getPentSpinFrame( d_pent_spin_frame_index ) );
  d_right_pent_spin->setPixmap( this->getPentSpinFrame( d_pent_spin_frame_index ) );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end PentSpinMenuPushbutton.cpp
//---------------------------------------------------------------------------//
