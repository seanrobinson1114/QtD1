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
#include <QMap>

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class MenuPushButton;
class SmallPentSpinMenuPushButton;

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

  //! Handle show events
  void showEvent( QShowEvent* event ) final override;

  //! Handle hide events
  void hideEvent( QHideEvent* event ) final override;

private slots:

  // Handle a menu push button pressed
  void handleMenuPushButtonPressed();
  
private:

  // Re-center the talk buttons box
  void recenterTalkButtonsBox();

  // Re-center the talk buttons
  void recenterTalkButtons();

  // The primary menu
  QLabel* d_primary_menu;

  // The talk menu
  QLabel* d_talk_menu;

  // The talk menu button
  SmallPentSpinMenuPushButton* d_talk_menu_button;

  // The talk buttons box
  QLabel* d_talk_buttons_box;

  // The talk button order
  QList<SmallPentSpinMenuPushButton*> d_talk_button_order;

  // The gossip button
  SmallPentSpinMenuPushButton* d_gossip_button;

  // The quest discussion buttons
  std::map<Quest::Type,SmallPentSpinMenuPushButton*> d_quest_discussion_buttons;

  // The active talk button
  SmallPentSpinMenuPushButton* d_active_menu_button;

  // The go back button
  MenuPushButton* d_go_back_button;
  
  // The exit button
  MenuPushButton* d_exit_button;
};

} // end QtD1 namespace

#endif // end NPC_INTERACTION_MENU_H

//---------------------------------------------------------------------------//
// end NPCInteractionMenu.h
//---------------------------------------------------------------------------//
