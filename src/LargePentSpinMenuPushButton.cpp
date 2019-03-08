//---------------------------------------------------------------------------//
//!
//! \file   LargePentSpinMenuPushButton.cpp
//! \author Alex Robinson
//! \brief  The large pent spin menu push button class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "LargePentSpinMenuPushButton.h"
#include "MenuSprite.h"

namespace QtD1{

QVector<QPixmap> LargePentSpinMenuPushButton::s_pent_spin_frames;

// Constructor
LargePentSpinMenuPushButton::LargePentSpinMenuPushButton(
                                               const QString& button_text,
                                               const QString& bitmap_font_name,
                                               QWidget* parent )
  : PentSpinMenuPushButton( button_text,
                            bitmap_font_name,
                            48, 48,
                            parent )
{
  // Initialize the pent spin frames
  this->initializePentSpinFrames();
}

// Initialize the pent spint frames
void LargePentSpinMenuPushButton::initializePentSpinFrames()
{
  if( s_pent_spin_frames.empty() )
  {
    MenuSprite menu_sprite;
    menu_sprite.setSource( "/data/PentSpin.cel+levels/towndata/town.pal" );
    menu_sprite.loadSync();

    menu_sprite.getFrames( s_pent_spin_frames );
  }
}

// Get the pent spin frame
QPixmap LargePentSpinMenuPushButton::getPentSpinFrame( const int frame_index ) const
{
  if( frame_index < 0 )
    return s_pent_spin_frames.front();
  else if( frame_index < s_pent_spin_frames.size() )
    return s_pent_spin_frames[frame_index];
  else
    return s_pent_spin_frames.back();
}

// Increment pent spin frame index
void LargePentSpinMenuPushButton::incrementPentSpinFrame( int& frame_index ) const
{
  frame_index = (frame_index+1)%s_pent_spin_frames.size();
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LargePentSpinMenuPushButton.cpp
//---------------------------------------------------------------------------//
