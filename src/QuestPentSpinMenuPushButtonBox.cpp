//---------------------------------------------------------------------------//
//!
//! \file   QuestPentSpinMenuPushButtonBox.cpp
//! \author Alex Robinson
//! \brief  The quest pent spin menu push button box class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "QuestPentSpinMenuPushButtonBox.h"
#include "QuestMenuPushButton.h"

namespace QtD1{

// Constructor
QuestPentSpinMenuPushButtonBox::QuestPentSpinMenuPushButtonBox( QWidget* parent )
  : PentSpinMenuPushButtonBox( parent ),
    d_quest_buttons()
{ /* ... */ }

// Activate a quest
void QuestPentSpinMenuPushButtonBox::activateQuest( const Quest::Type quest )
{
  auto quest_buttons_it = d_quest_buttons.find( quest );
  
  if( quest_buttons_it == d_quest_buttons.end() )
  {
    QuestMenuPushButton* quest_button =
      new QuestMenuPushButton( quest, "QtD1White11", this );
    
    quest_button->setStyleSheet( QString( "background: transparent" ) );

    this->addButton( quest_button );

    QObject::connect( quest_button, SIGNAL(releasedQuest(const Quest::Type)),
                      this, SIGNAL(questSelected(const Quest::Type)) );

    d_quest_buttons[quest] = quest_button;
  }
}

// Deactivate a quest
void QuestPentSpinMenuPushButtonBox::deactivateQuest( const Quest::Type quest )
{
  auto quest_buttons_it = d_quest_buttons.find( quest );
  
  if( quest_buttons_it != d_quest_buttons.end() )
  {
    this->removeButton( quest_buttons_it->second );

    // Destroy the button
    delete quest_buttons_it->second;

    d_quest_buttons.erase( quest_buttons_it );
  }
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end QuestPentSpinMenuPushButtonBox.cpp
//---------------------------------------------------------------------------//
