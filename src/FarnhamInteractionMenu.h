//---------------------------------------------------------------------------//
//!
//! \file   FarnhamInteractionMenu.h
//! \author Alex Robinson
//! \brief  The Farnham interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FARNHAM_INTERACTION_MENU_H
#define FARNHAM_INTERACTION_MENU_H

// QtD1 Includes
#include "NPCInteractionMenu.h"

namespace QtD1{

//! The Farnham interaction menu
class FarnhamInteractionMenu : public NPCInteractionMenu
{
  Q_OBJECT

public:

  //! Constructor
  FarnhamInteractionMenu( QWidget* parent = 0 );

  //! Destructor
  ~FarnhamInteractionMenu()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end FARNHAM_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end FarnhamInteractionMenu.h
//---------------------------------------------------------------------------//
