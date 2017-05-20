//---------------------------------------------------------------------------//
//!
//! \file   SorcererSpellBook
//! \author Alex Robinson, Sean Robinson
//! \brief  The sorcerer spell book class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "SorcererSpellBook.h"

namespace QtD1{

// Constructor
SorcererSpellBook::SorcererSpellBook( QWidget* parent )
  : SpellBook( parent )
{ /* ... */ }

// Clone the inventory
/*! \details The returned sorcerer spell book is heap allocated.
 */
SorcererSpellBook* SorcererSpellBook::clone( QWidget* parent ) const
{
  return new SorcererSpellBook( parent );
}

// Return the sorcerer skill
Spell::Type SorcererSpellBook::getClassSkill()
{
  return Spell::RechargeStaff;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SorcererSpellBook.cpp
//---------------------------------------------------------------------------//
