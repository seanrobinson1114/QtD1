//---------------------------------------------------------------------------//
//!
//! \file   QuestTheChamberOfBone.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The chamber of bone quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_THE_CHAMBER_OF_BONE_H
#define QUEST_THE_CHAMBER_OF_BONE_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestTheChamberOfBone : public Quest
{

public:

  //! Constructor
  QuestTheChamberOfBone();

  //! Destructor
  ~QuestTheChamberOfBone();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestTheChamberOfBone.h
//---------------------------------------------------------------------------//
