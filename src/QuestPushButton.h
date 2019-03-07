//---------------------------------------------------------------------------//
//!
//! \file   QuestPushButton.h
//! \author Alex Robinson
//! \brief  The quest push button class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_PUSH_BUTTON_H
#define QUEST_PUSH_BUTTON_H

// Qt Includes
#include <QPushButton>

// QtD1 Includes
#include "Quest.h"

namespace QtD1{
  
//! The quest push button
class QuestPushButton : public QPushButton
{
  Q_OBJECT

public:

  //! Constructor
  QuestPushButton( const Quest::Type quest,
                   QWidget* parent = 0 );

  //! Destructor
  ~QuestPushButton()
  { /* ... */ }

signals:

  //! This signal is emitted when the button is pressed
  void pressedQuest( const Quest::Type quest );

private slots:

  //! Emit pressed signal with quest
  void appendQuestDataOnPress();
  
private:

  // The quest associated with this button
  Quest::Type d_quest;
};
  
} // end QtD1 namespace

#endif // end QUEST_PUSH_BUTTON_H

//---------------------------------------------------------------------------//
// end QuestPushButton.h
//---------------------------------------------------------------------------//
