//---------------------------------------------------------------------------//
//!
//! \file   DeckardInteractionMenu.h
//! \author Alex Robinson
//! \brief  The Deckard interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DECKARD_INTERACTION_MENU_H
#define DECKARD_INTERACTION_MENU_H

// QtD1 Includes
#include "NPCInteractionMenu.h"

namespace QtD1{

//! The Deckard interaction menu
class DeckardInteractionMenu : public NPCInteractionMenu
{
  Q_OBJECT

public:

  //! Constructor
  DeckardInteractionMenu( QWidget* parent = 0 );

  //! Destructor
  ~DeckardInteractionMenu()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end DECKARD_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end DeckardInteractionMenu.h
//---------------------------------------------------------------------------//
