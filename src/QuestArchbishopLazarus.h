//---------------------------------------------------------------------------//
//!
//! \file   QuestArchbishopLazarus.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Archbishop Lazarus quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_ARCHBISHOP_LAZARUS_H
#define QUEST_ARCHBISHOP_LAZARUS_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestArchbishopLazarus : public Quest
{

public:

  //! Constructor
  QuestArchbishopLazarus();

  //! Destructor
  ~QuestArchbishopLazarus();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestArchbishopLazarus.h
//---------------------------------------------------------------------------//
