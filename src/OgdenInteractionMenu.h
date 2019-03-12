//---------------------------------------------------------------------------//
//!
//! \file   OgdenInteractionMenu.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Ogden interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef OGDEN_INTERACTION_MENU_H
#define OGDEN_INTERACTION_MENU_H

// QtD1 Includes
#include "NPCInteractionMenu.h"

namespace QtD1{

//! The Ogden interaction menu
class OgdenInteractionMenu : public NPCInteractionMenu
{
  Q_OBJECT

public:

  //! Constructor
  OgdenInteractionMenu( QWidget* parent = 0 );

  //! Destructor
  ~OgdenInteractionMenu()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end OGDEN_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end OgdenInteractionMenu.h
//---------------------------------------------------------------------------//
