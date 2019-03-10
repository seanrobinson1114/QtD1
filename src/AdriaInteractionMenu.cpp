//---------------------------------------------------------------------------//
//!
//! \file   AdriaInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The Adria interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "AdriaInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
AdriaInteractionMenu::AdriaInteractionMenu( QWidget* parent )
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  QList<QString> extra_button_names;
  extra_button_names << "Buy Items"
                     << "Sell Items"
                     << "Recharge Staves";
  
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "Witch's Shack",
                                      "Talk To Adria",
                                      extra_button_names,
                                      "Leave The Shack",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "Talk To Adria",
                                         "Back",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "Talk To Adria",
                                               discussion_submenu );
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end AdriaInteractionMenu.cpp
//---------------------------------------------------------------------------//
