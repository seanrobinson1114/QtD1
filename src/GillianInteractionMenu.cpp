//---------------------------------------------------------------------------//
//!
//! \file   GillianInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The Gillian interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "GillianInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
GillianInteractionMenu::GillianInteractionMenu( QWidget* parent )
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "Gillian",
                                      "Talk To Gillian",
                                      QList<QString>(),
                                      "Say Goodbye",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "Talk To Gillian",
                                         "Back",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "Talk To Gillian",
                                               discussion_submenu );
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end GillianInteractionMenu.cpp
//---------------------------------------------------------------------------//
