//---------------------------------------------------------------------------//
//!
//! \file   QuestZharTheMad.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The zhar the mad quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_ZHAR_THE_MAD_H
#define QUEST_ZHAR_THE_MAD_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestZharTheMad : public Quest
{

public:

  //! Constructor
  QuestZharTheMad();

  //! Destructor
  ~QuestZharTheMad();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestZharTheMad.h
//---------------------------------------------------------------------------//
