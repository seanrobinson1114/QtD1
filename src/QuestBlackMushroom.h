//---------------------------------------------------------------------------//
//!
//! \file   QuestBlackMushroom.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The black mushroom quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_BLACK_MUSHROOM_H
#define QUEST_BLACK_MUSHROOM_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestBlackMushroom : public Quest
{

public:

  //! Constructor
  QuestBlackMushroom();

  //! Destructor
  ~QuestBlackMushroom();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestBlackMushroom.h
//---------------------------------------------------------------------------//
