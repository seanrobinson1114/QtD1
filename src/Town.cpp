//---------------------------------------------------------------------------//
//!
//! \file   Town.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The town class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Town.h"

namespace QtD1{

//! Constructor
Town::Town( QObject* parent )
  : Level( parent, "/music/dtowne.wav" )
{ /* ... */ }

// Get the type
Level::Type Town::getType() const
{
  return Level::Town;
}

// Get the number
int Town::getNumber() const
{
  return -1;
}

// Insert the character
void Town::insertCharacter( Character* character,
                            const QPointF& location,
                            const Direction direction )
{
  Level::insertCharacter( character, location, direction );

  character->enterTown();
}

// Remove the character
void Town::removeCharacter()
{
  this->getCharacter()->exitTown();
  
  Level::removeCharacter();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Town.cpp
//---------------------------------------------------------------------------//
