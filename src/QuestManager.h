//---------------------------------------------------------------------------//
//!
//! \file   QuestManager.h
//! \author Alex Robinson
//! \brief  The quest manager class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_MANAGER_H
#define QUEST_MANAGER_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QObject>
#include <QList>
#include <QSet>

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

//! The QuestManager class
class QuestManager : public QObject
{
  Q_OBJECT

public:

  //! Get the quest manager instance
  static QuestManager& getInstance();

  //! Destructor
  ~QuestManager()
  { /* ... */ }

  //! Get the possible quests
  const QSet<Quest::Type>& getPossibleQuests() const;

  //! Get the active quests
  const QList<Quest::Type>& getActiveQuests() const;

  //! Get the finished quests
  const QList<Quest::Type>& getFinishedQuests() const;

signals:

  //! A quest has been activated
  void questActivated( const Quest::Type quest );

  //! A quest has been finished
  void questFinished( const Quest::Type quest );

public slots:
  
  //! Activate a quest
  void activateQuest( const Quest::Type quest );

  //! Finish a quest
  void finishQuest( const Quest::Type quest );
  
private:
  
  // Constructor
  QuestManager();

  // The singleton instance
  static std::unique_ptr<QuestManager> s_instance;

  // The possible quests
  QSet<Quest::Type> d_possible_quests;

  // The active quests
  QList<Quest::Type> d_active_quests;

  // The finished quests
  QList<Quest::Type> d_finished_quests;
};
  
} // end QtD1 namespace

#endif // end QUEST_MANAGER_H

//---------------------------------------------------------------------------//
// end QuestManager.h
//---------------------------------------------------------------------------//
