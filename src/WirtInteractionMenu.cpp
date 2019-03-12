//---------------------------------------------------------------------------//
//!
//! \file   WirtInteractionMenu.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The Wirt interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "WirtInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
WirtInteractionMenu::WirtInteractionMenu( QWidget* parent )
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  QList<QString> extra_button_titles;
  extra_button_titles << "WHAT HAVE YOU GOT?";
  
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "WIRT THE PEG-LEGGED BOY",
                                      "TALK TO WIRT",
                                      extra_button_titles,
                                      "SAY GOODBYE",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "TALK TO WIRT",
                                         "Back",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "TALK TO WIRT",
                                               discussion_submenu );
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end WirtInteractionMenu.cpp
//---------------------------------------------------------------------------//
