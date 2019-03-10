//---------------------------------------------------------------------------//
//!
//! \file   AdriaInteractionMenu.h
//! \author Alex Robinson
//! \brief  The Adria interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ADRIA_INTERACTION_MENU_H
#define ADRIA_INTERACTION_MENU_H

// QtD1 Includes
#include "NPCInteractionMenu.h"

namespace QtD1{

//! The Adria interaction menu
class AdriaInteractionMenu : public NPCInteractionMenu
{
  Q_OBJECT

public:

  //! Constructor
  AdriaInteractionMenu( QWidget* parent = 0 );

  //! Destructor
  ~AdriaInteractionMenu()
  { /* ... */ }
};
  
} // end QtD1 namespace

#endif // end ADRIA_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end AdriaInteractionMenu.h
//---------------------------------------------------------------------------//
