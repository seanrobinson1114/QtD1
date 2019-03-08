//---------------------------------------------------------------------------//
//!
//! \file   QuestPentSpinMenuPushButtonBox.h
//! \author Alex Robinson
//! \brief  The quest pent spin menu push button box class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_PENT_SPIN_MENU_PUSH_BUTTON_BOX_H
#define QUEST_PENT_SPIN_MENU_PUSH_BUTTON_BOX_H

// Std Lib Includes
#include <map>

// QtD1 Includes
#include "PentSpinMenuPushButtonBox.h"
#include "Quest.h"

namespace QtD1{

//! The quest pent spin menu push button box
class QuestPentSpinMenuPushButtonBox : public PentSpinMenuPushButtonBox
{
  Q_OBJECT

public:

  //! Constructor
  QuestPentSpinMenuPushButtonBox( QWidget* parent = 0 );

  //! Destructor
  ~QuestPentSpinMenuPushButtonBox()
  { /* ... */ }

signals:
  
  //! A quest has been selected
  void questSelected( const Quest::Type );

public slots:
  
  //! Activate a quest
  void activateQuest( const Quest::Type quest );

  //! Deactivate a quest
  void deactivateQuest( const Quest::Type quest );

private:

  // The quest discussion buttons
  std::map<Quest::Type,PentSpinMenuPushButton*> d_quest_buttons;
};
  
} // end QtD1 namespace

#endif // end QUEST_PENT_SPIN_MENU_PUSH_BUTTON_BOX_H

//---------------------------------------------------------------------------//
// end QuestPentSpinMenuPushButtonBox.h
//---------------------------------------------------------------------------//
