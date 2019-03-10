//---------------------------------------------------------------------------//
//!
//! \file   OgdenInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The Ogden interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "OgdenInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
OgdenInteractionMenu::OgdenInteractionMenu( QWidget* parent )
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "Tavern of the Rising Sun",
                                      "Talk To Ogden",
                                      QList<QString>(),
                                      "Leave The Tavern",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "Talk To Ogden",
                                         "Back",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "Talk To Ogden",
                                               discussion_submenu );
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end OgdenInteractionMenu.cpp
//---------------------------------------------------------------------------//
