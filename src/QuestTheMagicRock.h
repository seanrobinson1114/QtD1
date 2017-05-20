//---------------------------------------------------------------------------//
//!
//! \file   QuestTheMagicRock.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The magic rock quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_THE_MAGIC_ROCK_H
#define QUEST_THE_MAGIC_ROCK_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestTheMagicRock : public Quest
{

public:

  //! Constructor
  QuestTheMagicRock();

  //! Destructor
  ~QuestTheMagicRock();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestTheMagicRock.h
//---------------------------------------------------------------------------//
