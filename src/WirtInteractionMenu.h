//---------------------------------------------------------------------------//
//!
//! \file   WirtInteractionMenu.h
//! \author Alex Robinson
//! \brief  The Wirt interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef WIRT_INTERACTION_MENU_H
#define WIRT_INTERACTION_MENU_H

// QtD1 Includes
#include "NPCInteractionMenu.h"

namespace QtD1{

//! The Wirt interaction menu
class WirtInteractionMenu : public NPCInteractionMenu
{
  Q_OBJECT

public:

  //! Constructor
  WirtInteractionMenu( QWidget* parent = 0 );

  //! Destructor
  ~WirtInteractionMenu()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end WIRT_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end WirtInteractionMenu.h
//---------------------------------------------------------------------------//
