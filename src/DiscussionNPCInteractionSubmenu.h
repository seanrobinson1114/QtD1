//---------------------------------------------------------------------------//
//!
//! \file   DiscussionNPCInteractionSubmenu.h
//! \author Alex Robinson
//! \brief  The discussion NPC interaction submenu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DISCUSSION_NPC_INTERACTION_SUBMENU_H
#define DISCUSSION_NPC_INTERACTION_SUBMENU_H

// QtD1 Includes
#include "NPCInteractionSubmenu.h"
#include "Quest.h"

namespace QtD1{

class QuestPentSpinMenuPushButtonBox;

//! The discussion NPC interaction submenu
class DiscussionNPCInteractionSubmenu : public NPCInteractionSubmenu
{
  Q_OBJECT

public:
  
  //! Constructor
  DiscussionNPCInteractionSubmenu( const QString& title_text,
                                   const QString& back_button_name,
                                   QWidget* parent = 0 );

  //! Destructor
  ~DiscussionNPCInteractionSubmenu()
  { /* ... */ }

  //! Get the submenu type
  Type getType() const final override;

signals:

  //! A quest has been selected
  void questSelected( const Quest::Type );

  //! Gossip has been selected
  void gossipSelected();

public slots:

  //! Activate a quest
  void activateQuest( const Quest::Type quest );

  //! Deactivate a quest
  void deactivateQuest( const Quest::Type quest );

  //! Move the active button up
  void moveActiveButtonUp() final override;

  //! Move the active button down
  void moveActiveButtonDown() final override;
  
  //! Click the active button
  void clickActiveButton() final override;

  //! Reset active button (set to first)
  void resetActiveButton() final override;

private:

  // Recenter the button box
  void recenterButtonBox();

  // The button box
  QuestPentSpinMenuPushButtonBox* d_button_box;
};
  
} // end QtD1 namespace

#endif // end DISCUSSION_NPC_INTERACTION_SUBMENU_H

//---------------------------------------------------------------------------//
// end DiscussionNPCInteractionSubmenu.h
//---------------------------------------------------------------------------//
