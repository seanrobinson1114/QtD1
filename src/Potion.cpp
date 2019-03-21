//---------------------------------------------------------------------------//
//!
//! \file   Potion.cpp
//! \author Alex Robinson
//! \brief  The potion class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Potion.h"

namespace QtD1{

// Initialize static member data
std::unique_ptr<Sound> Potion::s_flip_sound;

// Constructor
Potion::Potion( QGraphicsObject* parent )
  : ConsumableInteractiveLevelObject( parent )
{ /* ... */ }

// Copy constructor
Potion::Potion( const Potion& other )
  : ConsumableInteractiveLevelObject( other )
{ /* ... */ }

// Play the flipping sound
void Potion::playFlippingSound()
{
  if( !s_flip_sound )
  {
    s_flip_sound.reset( new Sound );
    s_flip_sound->setSource( "/sfx/items/flippot.wav" );
  }

  s_flip_sound->playSound();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Potion.cpp
//---------------------------------------------------------------------------//
