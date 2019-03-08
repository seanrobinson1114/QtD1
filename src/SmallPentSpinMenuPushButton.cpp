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
  : PentSpinMenuPushButton( button_text,
                            bitmap_font_name,
                            12, 12,
                            parent )
{
  // Initialize the pent spin frames
  this->initializePentSpinFrames();
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

// Get the pent spin frame
QPixmap SmallPentSpinMenuPushButton::getPentSpinFrame( const int frame_index ) const
{
  if( frame_index < 0 )
    return s_pent_spin_frames.front();
  else if( frame_index < s_pent_spin_frames.size() )
    return s_pent_spin_frames[frame_index];
  else
    return s_pent_spin_frames.back();
}

// Increment pent spin frame index
void SmallPentSpinMenuPushButton::incrementPentSpinFrame( int& frame_index ) const
{
  frame_index = (frame_index+1)%s_pent_spin_frames.size();
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SmallPentSpinMenuPushButton.cpp
//---------------------------------------------------------------------------//
