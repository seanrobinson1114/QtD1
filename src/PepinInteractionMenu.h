//---------------------------------------------------------------------------//
//!
//! \file   PepinInteractionMenu.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Pepin interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PEPIN_INTERACTION_MENU_H
#define PEPIN_INTERACTION_MENU_H

// QtD1 Includes
#include "NPCInteractionMenu.h"

namespace QtD1{

//! The Pepin interaction menu
class PepinInteractionMenu : public NPCInteractionMenu
{
  Q_OBJECT

public:

  //! Constructor
  PepinInteractionMenu( QWidget* parent = 0 );

  //! Destructor
  ~PepinInteractionMenu()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end PEPIN_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end PepinInteractionMenu.h
//---------------------------------------------------------------------------//
