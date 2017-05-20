//---------------------------------------------------------------------------//
//!
//! \file   WarriorSpellBook.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Warrior spell book class declaration
//!
//---------------------------------------------------------------------------//

#ifndef WARRIOR_SPELLBOOK_H
#define WARRIOR_SPELLBOOK_H

// QtD1 Includes
#include "SpellBook.h"

namespace QtD1{

//! The warrior inventory
class WarriorSpellBook : public SpellBook
{

public:

  //! Constructor
  WarriorSpellBook( QWidget* parent = 0 );

  //! Destructor
  ~WarriorSpellBook()
  { /* ... */ }

  //! Clone the inventory
  WarriorSpellBook* clone( QWidget* parent = 0 ) const override;

private:

  // Return the warrior skill spell enum
  Spell::Type getClassSkill() override;
};

} // end QtD1 namespace

#endif // end WARRIOR_SPELLBOOK_H

//---------------------------------------------------------------------------//
// end WarriorSpellBook.h
//---------------------------------------------------------------------------//
