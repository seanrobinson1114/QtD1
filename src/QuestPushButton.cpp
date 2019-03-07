//---------------------------------------------------------------------------//
//!
//! \file   QuestPushButton.cpp
//! \author Alex Robinson
//! \brief  The quest push button class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "QuestPushButton.h"

namespace QtD1{

// Constructor
QuestPushButton::QuestPushButton( const Quest::Type quest, QWidget* parent )
  : QPushButton( parent ),
    d_quest( quest )
{
  QObject::connect( this, SIGNAL(pressed()),
                    this, SLOT(appendQuestDataOnPress()) );
}

// Emit pressed signal with quest
void QuestPushButton::appendQuestDataOnPress()
{
  emit pressedQuest( d_quest );
}
  
} // end QtD1

//---------------------------------------------------------------------------//
// end QuestPushButton.cpp
//---------------------------------------------------------------------------//
