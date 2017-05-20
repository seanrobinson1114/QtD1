//---------------------------------------------------------------------------//
//!
//! \file   QuestLog
//! \author Alex Robinson, Sean Robinson
//! \brief  The quest log class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_LOG_H
#define QUEST_LOG_H

// QtD1 Includes
#include "Quest.h"

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QGraphicsObject>
#include <QLabel>

namespace QtD1{

//! The quest log class
class QuestLog : public QWidget
{
  Q_OBJECT

public:

  //! Constructor
  QuestLog( QWidget* parent = 0 );

  //! Destructor
  ~QuestLog()
  { /* ... */ }

  //! Clone the spell book
  QuestLog* clone( QWidget* parent = 0 ) const;

  //! Display the currently active quests
  void displayActiveQuests();

public slots:

  void beginQuest( Quest::Type );
  //void advanceQuest( Quest::Type );
  //void completeQuest( Quest::Type );

private:

  // The quest log image
  QLabel* d_questlog_image;
};

} // end QtD1 namespace

#endif // end QUEST_LOG_H

//---------------------------------------------------------------------------//
// end QuestLog.h
//---------------------------------------------------------------------------//
