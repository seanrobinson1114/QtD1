//---------------------------------------------------------------------------//
//!
//! \file   QuestHallsOfTheBlind.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The halls of the blind quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_HALLS_OF_THE_BLIND_H
#define QUEST_HALLS_OF_THE_BLIND_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestHallsOfTheBlind : public Quest
{

public:

  //! Constructor
  QuestHallsOfTheBlind();

  //! Destructor
  ~QuestHallsOfTheBlind();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestHallsOfTheBlind.h
//---------------------------------------------------------------------------//
