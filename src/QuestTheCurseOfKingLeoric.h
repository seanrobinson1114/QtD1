//---------------------------------------------------------------------------//
//!
//! \file   QuestTheCurseOfKingLeoric.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The curse of king leoric quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_THE_CURSE_OF_KING_LEORIC_H
#define QUEST_THE_CURSE_OF_KING_LEORIC_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestTheCurseOfKingLeoric : public Quest
{

public:

  //! Constructor
  QuestTheCurseOfKingLeoric();

  //! Destructor
  ~QuestTheCurseOfKingLeoric();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestTheCurseOfKingLeoric.h
//---------------------------------------------------------------------------//
