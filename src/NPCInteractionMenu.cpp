//---------------------------------------------------------------------------//
//!
//! \file   NPCInteractionMenu.cpp
//! \author Alex Robinson
//! \brief  The NPC interaction menu class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QKeyEvent>

// QtD1 Includes
#include "NPCInteractionMenu.h"
#include "PrimaryNPCInteractionSubmenu.h"
#include "DiscussionNPCInteractionSubmenu.h"

namespace QtD1{

// Constructor
NPCInteractionMenu::NPCInteractionMenu( QWidget* parent )
  : QWidget( parent ),
    d_primary_submenu( NULL ),
    d_discussion_submenu( NULL ),
    d_extra_submenus(),
    d_active_submenu( NULL )
{ /* ... */ }

// Activate a quest
void NPCInteractionMenu::activateQuest( const Quest::Type quest )
{
  d_discussion_submenu->activateQuest( quest );
}

// Deactivate a quest
void NPCInteractionMenu::deactivateQuest( const Quest::Type quest )
{
  d_discussion_submenu->deactivateQuest( quest );
}

// Show the submenu
void NPCInteractionMenu::showSubmenu( NPCInteractionSubmenu* submenu )
{
  // Hide the currently active submenu
  d_active_submenu->hide();

  // Show the newly active submenu
  submenu->show();
  submenu->raise();

  // Cache the active submenu
  d_active_submenu = submenu;
}

// Set the primary submenu
void NPCInteractionMenu::setPrimarySubmenu( PrimaryNPCInteractionSubmenu* submenu )
{
  if( submenu )
  {
    d_primary_submenu = submenu;
    d_active_submenu = submenu;
    d_active_submenu->show();

    QObject::connect( d_primary_submenu, SIGNAL(exit()),
                      this, SIGNAL(exit()) );
    QObject::connect( d_primary_submenu, SIGNAL(showSubmenu(NPCInteractionSubmenu*)),
                      this, SLOT(showSubmenu(NPCInteractionSubmenu*)) );
  }
}

// Set the discussion submenu
void NPCInteractionMenu::setDiscussionSubmenu( DiscussionNPCInteractionSubmenu* submenu )
{
  if( submenu )
  {
    d_discussion_submenu = submenu;
    d_discussion_submenu->hide();

    QObject::connect( d_discussion_submenu, SIGNAL(gossipSelected()),
                      this, SIGNAL(gossip()) );
    QObject::connect( d_discussion_submenu, SIGNAL(questSelected(const Quest::Type)),
                      this, SIGNAL(discussQuest(const Quest::Type)) );
    QObject::connect( d_discussion_submenu, SIGNAL(showSubmenu(NPCInteractionSubmenu*)),
                      this, SLOT(showSubmenu(NPCInteractionSubmenu*)) );
  }
}

// Set the extra submenus
void NPCInteractionMenu::setExtraSubmenus( QList<NPCInteractionSubmenu*> extra_submenus )
{
  d_extra_submenus = extra_submenus;
  
  for( auto&& submenu : extra_submenus )
  {
    if( submenu )
    {
      submenu->hide();
      
      QObject::connect( submenu, SIGNAL(showSubmenu(NPCInteractionSubmenu*)),
                        this, SLOT(showSubmenu(NPCInteractionSubmenu*)) );
    }
  }
}

// Handle key press events
void NPCInteractionMenu::keyPressEvent( QKeyEvent* event )
{
  if( event->key() == Qt::Key_Up )
  {
    d_active_submenu->moveActiveButtonUp();
  }
  else if( event->key() == Qt::Key_Down )
  {
    d_active_submenu->moveActiveButtonDown();
  }
  else if( event->key() == Qt::Key_Enter ||
           event->key() == Qt::Key_Return )
  {
    d_active_submenu->clickActiveButton();
  }
  else if( event->key() == Qt::Key_Escape )
  {
    d_active_submenu->clickBackButton();
  }
  else
    QWidget::keyPressEvent( event );
}

} // end QtD1 includes

//---------------------------------------------------------------------------//
// end NPCInteractionMenu.cpp
//---------------------------------------------------------------------------//
