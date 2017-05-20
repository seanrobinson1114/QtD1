//---------------------------------------------------------------------------//
//!
//! \file   RogueSpellBook.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Rogue spell book class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ROGUE_SPELLBOOK_H
#define ROGUE_SPELLBOOK_H

// QtD1 Includes
#include "SpellBook.h"
#include "Spell.h"

namespace QtD1{

//! The rogue inventory
class RogueSpellBook : public SpellBook
{

public:

  //! Constructor
  RogueSpellBook( QWidget* parent = 0 );

  //! Destructor
  ~RogueSpellBook()
  { /* ... */ }

  //! Clone the inventory
  RogueSpellBook* clone( QWidget* parent = 0 ) const override;

private:

  // Return the rogue skill spell enum
  Spell::Type getClassSkill() override;
};

} // end QtD1 namespace

#endif // end ROGUE_SPELLBOOK_H

//---------------------------------------------------------------------------//
// end RogueSpellBook.h
//---------------------------------------------------------------------------//
