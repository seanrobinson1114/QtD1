//---------------------------------------------------------------------------//
//!
//! \file   WarriorSpellBook
//! \author Alex Robinson, Sean Robinson
//! \brief  The warrior spell book class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "WarriorSpellBook.h"

namespace QtD1{

// Constructor
WarriorSpellBook::WarriorSpellBook( QWidget* parent )
  : SpellBook( parent )
{ /* ... */ }

// Clone the inventory
/*! \details The returned warrior spell book is heap allocated.
 */
WarriorSpellBook* WarriorSpellBook::clone( QWidget* parent ) const
{
  return new WarriorSpellBook( parent );
}

// Return the warrior skill
Spell::Type WarriorSpellBook::getClassSkill()
{
  return Spell::RepairItem;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end WarriorSpellBook.cpp
//---------------------------------------------------------------------------//
