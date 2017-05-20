//---------------------------------------------------------------------------//
//!
//! \file   RogueSpellBook
//! \author Alex Robinson, Sean Robinson
//! \brief  The rogue spell book class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "RogueSpellBook.h"

namespace QtD1{

// Constructor
RogueSpellBook::RogueSpellBook( QWidget* parent )
  : SpellBook( parent )
{ /* ... */ }

// Clone the inventory
/*! \details The returned rogue spell book is heap allocated.
 */
RogueSpellBook* RogueSpellBook::clone( QWidget* parent ) const
{
  return new RogueSpellBook( parent );
}

// Return the rogue skill
Spell::Type RogueSpellBook::getClassSkill()
{
  return Spell::DisarmTrap;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end RogueSpellBook.cpp
//---------------------------------------------------------------------------//
