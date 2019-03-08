//---------------------------------------------------------------------------//
//!
//! \file   QuestMenuPushButton.cpp
//! \author Alex Robinson
//! \brief  The quest menu push button class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "QuestMenuPushButton.h"

namespace QtD1{

// Constructor
QuestMenuPushButton::QuestMenuPushButton( const Quest::Type quest,
                                          const QString& bitmap_font_name,
                                          QWidget* parent )
  : SmallPentSpinMenuPushButton( QtD1::questTypeToString( quest ),
                                 bitmap_font_name,
                                 parent ),
    d_quest( quest )
{
  QObject::connect( this, SIGNAL(pressed()),
                    this, SLOT(appendQuestDataOnPress()) );
  QObject::connect( this, SIGNAL(released()),
                    this, SLOT(appendQuestDataOnRelease()) );
}

// Emit pressed signal with quest
void QuestMenuPushButton::appendQuestDataOnPress()
{
  emit pressedQuest( d_quest );
}

// Emit released signal with quest
void QuestMenuPushButton::appendQuestDataOnRelease()
{
  emit releasedQuest( d_quest );
}
  
} // end QtD1

//---------------------------------------------------------------------------//
// end QuestMenuPushButton.cpp
//---------------------------------------------------------------------------//
