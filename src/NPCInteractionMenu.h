//---------------------------------------------------------------------------//
//!
//! \file   NPCInteractionMenu.h
//! \author Alex Robinson
//! \brief  The NPC interaction menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NPC_INTERACTION_MENU_H
#define NPC_INTERACTION_MENU_H

// Qt Includes
#include <QWidget>

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class NPCInteractionSubmenu;
class PrimaryNPCInteractionSubmenu;
class DiscussionNPCInteractionSubmenu;

//! The NPC interaction menu class
class NPCInteractionMenu : public QWidget
{
  Q_OBJECT

public:

  //! Destructor
  ~NPCInteractionMenu()
  { /* ... */ }

signals:

  //! Exit the menu
  void exit();

  //! Gossip
  void gossip();

  //! Discuss quest
  void discussQuest( const Quest::Type );

public slots:

  //! Activate a quest
  void activateQuest( const Quest::Type quest );

  //! Deactivate a quest
  void deactivateQuest( const Quest::Type quest );

protected slots:

  //! Show the submenu
  void showSubmenu( NPCInteractionSubmenu* submenu );
  
protected:

  //! Constructor
  NPCInteractionMenu( QWidget* parent = 0 );

  //! Set the primary submenu
  void setPrimarySubmenu( PrimaryNPCInteractionSubmenu* submenu );

  //! Set the discussion submenu
  void setDiscussionSubmenu( DiscussionNPCInteractionSubmenu* submenu );

  //! Set the extra submenus
  void setExtraSubmenus( QList<NPCInteractionSubmenu*> extra_submenus );

  //! Handle key press events
  void keyPressEvent( QKeyEvent* event ) final override;  
  
private:

  // The primary submenu
  PrimaryNPCInteractionSubmenu* d_primary_submenu;

  // The discussion submenu
  DiscussionNPCInteractionSubmenu* d_discussion_submenu;

  // The submenus
  QList<NPCInteractionSubmenu*> d_extra_submenus;
  
  // The active submenu
  NPCInteractionSubmenu* d_active_submenu;
};

} // end QtD1 namespace

#endif // end NPC_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end NPCInteractionMenu.h
//---------------------------------------------------------------------------//
