//---------------------------------------------------------------------------//
//!
//! \file   DeckardInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The Deckard interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "DeckardInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
DeckardInteractionMenu::DeckardInteractionMenu( QWidget* parent )
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  QList<QString> extra_button_titles;
  extra_button_titles << "IDENTIFY AN ITEM";
  
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "THE TOWN ELDER",
                                      "TALK TO CAIN",
                                      extra_button_titles,
                                      "SAY GOODBYE",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "TALK TO CAIN",
                                         "BACK",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "TALK TO CAIN",
                                               discussion_submenu );
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end DeckardInteractionMenu.cpp
//---------------------------------------------------------------------------//
