//---------------------------------------------------------------------------//
//!
//! \file   QuestMenuPushButton.h
//! \author Alex Robinson
//! \brief  The quest menu push button class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_PUSH_MENU_BUTTON_H
#define QUEST_PUSH_MENU_BUTTON_H

// QtD1 Includes
#include "SmallPentSpinMenuPushButton.h"
#include "Quest.h"

namespace QtD1{
  
//! The quest menu push button
class QuestMenuPushButton : public SmallPentSpinMenuPushButton
{
  Q_OBJECT

public:

  //! Constructor
  QuestMenuPushButton( const Quest::Type quest,
                       const QString& bitmap_font_name,
                       QWidget* parent = 0 );

  //! Destructor
  ~QuestMenuPushButton()
  { /* ... */ }

signals:

  //! This signal is emitted when the button is pressed
  void pressedQuest( const Quest::Type quest );

  //! This signal is emitted when the button is released
  void releasedQuest( const Quest::Type quest );

private slots:

  //! Emit pressed signal with quest
  void appendQuestDataOnPress();

  //! Emit released signal with quest
  void appendQuestDataOnRelease();
  
private:

  // The quest associated with this button
  Quest::Type d_quest;
};
  
} // end QtD1 namespace

#endif // end QUEST_MENU_PUSH_BUTTON_H

//---------------------------------------------------------------------------//
// end QuestMenuPushButton.h
//---------------------------------------------------------------------------//
