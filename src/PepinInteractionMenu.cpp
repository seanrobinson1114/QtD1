//---------------------------------------------------------------------------//
//!
//! \file   PepinInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The Pepin interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "PepinInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
PepinInteractionMenu::PepinInteractionMenu( QWidget* parent )
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "Pepin",
                                      "Talk To Pepin",
                                      QList<QString>(),
                                      "Say Goodbye",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "Talk To Pepin",
                                         "Back",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "Talk To Pepin",
                                               discussion_submenu );
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end PepinInteractionMenu.cpp
//---------------------------------------------------------------------------//
