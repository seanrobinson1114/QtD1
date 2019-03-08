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
#include <QLabel>
#include <QPushButton>

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class PentSpinMenuPushButtonBox;
class QuestPentSpinMenuPushButtonBox;

//! The NPC interaction menu class
class NPCInteractionMenu : public QWidget
{
  Q_OBJECT

public:

  //! Constructor
  NPCInteractionMenu( const QString& npc_name,
                      const QString& interaction_menu_title_text,
                      const QString& exit_menu_text,
                      QWidget* parent = 0 );

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

  //! Show the talk menu
  void showTalkMenu();

  //! Show the primary menu
  void showPrimaryMenu();
  
protected:

  //! Handle key press events
  void keyPressEvent( QKeyEvent* event ) final override;  
  
private:

  // Re-center the talk menu button box
  void recenterTalkMenuButtonBox();

  // The primary menu
  QLabel* d_primary_menu;

  // The primary menu button box
  PentSpinMenuPushButtonBox* d_primary_menu_button_box;

  // The exit button
  QPushButton* d_exit_button;

  // The talk menu
  QLabel* d_talk_menu;

  // The talk button box
  QuestPentSpinMenuPushButtonBox* d_talk_menu_button_box;

  // The go back button
  QPushButton* d_go_back_button;
};

} // end QtD1 namespace

#endif // end NPC_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end NPCInteractionMenu.h
//---------------------------------------------------------------------------//
