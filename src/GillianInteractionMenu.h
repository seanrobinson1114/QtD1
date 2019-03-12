//---------------------------------------------------------------------------//
//!
//! \file   GillianInteractionMenu.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Gillian interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GILLIAN_INTERACTION_MENU_H
#define GILLIAN_INTERACTION_MENU_H

// QtD1 Includes
#include "NPCInteractionMenu.h"

namespace QtD1{

//! The Gillian interaction menu
class GillianInteractionMenu : public NPCInteractionMenu
{
  Q_OBJECT

public:

  //! Constructor
  GillianInteractionMenu( QWidget* parent = 0 );

  //! Destructor
  ~GillianInteractionMenu()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end GILLIAN_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end GillianInteractionMenu.h
//---------------------------------------------------------------------------//
