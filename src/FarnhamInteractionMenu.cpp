//---------------------------------------------------------------------------//
//!
//! \file   FarnhamInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The Farnham interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "FarnhamInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
FarnhamInteractionMenu::FarnhamInteractionMenu( QWidget* parent )
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "Farnham The Drunk",
                                      "Talk To Farnham",
                                      QList<QString>(),
                                      "Say Goodbye",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "Talk To Farnham",
                                         "Back",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "Talk To Farnham",
                                               discussion_submenu );
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end FarnhamInteractionMenu.cpp
//---------------------------------------------------------------------------//
