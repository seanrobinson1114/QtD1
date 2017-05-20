//---------------------------------------------------------------------------//
//!
//! \file   QuestLog.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The quest log class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "QuestLog.h"

namespace QtD1{

// Constructor
QuestLog::QuestLog( QWidget* parent )
  : QWidget( parent ),
  d_questlog_image( NULL )
{
  // Load the QuestLog image
  QImage background_image( "/data/quest.cel+levels/towndata/town.pal" );
  d_questlog_image = new QLabel( this );
  d_questlog_image->setPixmap( QPixmap::fromImage( background_image ) );
  d_questlog_image->setFixedSize( background_image.size() );
  this->setFixedSize( d_questlog_image->size() );
}

// Clone the quest log
QuestLog* QuestLog::clone( QWidget* parent ) const
{
  return new QuestLog( parent );
}

// Display the currently active quests
void QuestLog::displayActiveQuests()
{

}

// Begin a quests
void QuestLog::beginQuest( Quest::Type )
{
  
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end QuestLog.cpp
//---------------------------------------------------------------------------//
