//---------------------------------------------------------------------------//
//!
//! \file   PepinInteractionMenu.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The Pepin interaction menu class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "PepinInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"
#include "Character.h"

namespace QtD1{

// Constructor
PepinInteractionMenu::PepinInteractionMenu( Character* character,
                                            QWidget* parent )
                                            
  : NPCInteractionMenu( parent )
{
  // Create the primary interaction submenu
  QList<QString> extra_button_titles;
  extra_button_titles << "Receive Healing";
  extra_button_titles << "Buy Items";
  
  PrimaryNPCInteractionSubmenu* primary_submenu =
    new PrimaryNPCInteractionSubmenu( "Welcome To The\nHealer's Home",
                                      "Talk To Pepin",
                                      extra_button_titles,
                                      "Leave Healer's Home",
                                      this );

  // Create the discussion interaction submenu
  DiscussionNPCInteractionSubmenu* discussion_submenu =
    new DiscussionNPCInteractionSubmenu( "Talk To Pepin",
                                         "Back",
                                         this );

  // Set the button connections
  primary_submenu->assignSubmenuToNamedButton( "Talk To Pepin",
                                               discussion_submenu );
  primary_submenu->assignActionToNamedButton( "Receive Healing",
                                              character,
                                              SLOT(restoreHealth()) );
  primary_submenu->assignActionToNamedButton( "Receive Healing",
                                              character,
                                              SLOT(restoreMana()) );
  
  discussion_submenu->assignBackSubmenu( primary_submenu );

  this->setPrimarySubmenu( primary_submenu );
  this->setDiscussionSubmenu( discussion_submenu );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end PepinInteractionMenu.cpp
//---------------------------------------------------------------------------//