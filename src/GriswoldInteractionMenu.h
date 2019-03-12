//---------------------------------------------------------------------------//
//!
//! \file   GriswoldInteractionMenu.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Griswold interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GRISWOLD_INTERACTION_MENU_H
#define GRISWOLD_INTERACTION_MENU_H

// QtD1 Includes
#include "NPCInteractionMenu.h"

namespace QtD1{

//! The Griswold interaction menu
class GriswoldInteractionMenu : public NPCInteractionMenu
{
  Q_OBJECT

public:

  //! Constructor
  GriswoldInteractionMenu( QWidget* parent = 0 );

  //! Destructor
  ~GriswoldInteractionMenu()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end GRISWOLD_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end GriswoldInteractionMenu.h
//---------------------------------------------------------------------------//
