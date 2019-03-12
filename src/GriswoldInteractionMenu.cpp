//---------------------------------------------------------------------------//
//!
//! \file   GriswoldInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The Griswold interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "GriswoldInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
GriswoldInteractionMenu::GriswoldInteractionMenu( QWidget* parent )
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  QList<QString> extra_button_titles;
  extra_button_titles << "Buy Basic Items";
  extra_button_titles << "Buy Premium Items";
  extra_button_titles << "Sell Items";
  extra_button_titles << "Repair Items";
  
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "Welcome To The\nBlacksmith's Shop",
                                      "Talk To Griswold",
                                      extra_button_titles,
                                      "Leave The Shop",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "Talk To Griswold",
                                         "Back",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "Talk To Griswold",
                                               discussion_submenu );
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end GriswoldInteractionMenu.cpp
//---------------------------------------------------------------------------//
