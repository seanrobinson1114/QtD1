//---------------------------------------------------------------------------//
//!
//! \file   SorcererSpellBook.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The sorcerer spell book class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SORCERER_SPELLBOOK_H
#define SORCERER_SPELLBOOK_H

// QtD1 Includes
#include "SpellBook.h"

namespace QtD1{

//! The sorcerer inventory
class SorcererSpellBook : public SpellBook
{

public:

  //! Constructor
  SorcererSpellBook( QWidget* parent = 0 );

  //! Destructor
  ~SorcererSpellBook()
  { /* ... */ }

  //! Clone the inventory
  SorcererSpellBook* clone( QWidget* parent = 0 ) const override;

private:

  // Return the sorcerer skill spell enum
  Spell::Type getClassSkill() override;
};

} // end QtD1 namespace

#endif // end SORCERER_SPELLBOOK_H

//---------------------------------------------------------------------------//
// end SorcererSpellBook.h
//---------------------------------------------------------------------------//
