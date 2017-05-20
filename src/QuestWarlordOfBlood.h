//---------------------------------------------------------------------------//
//!
//! \file   QuestWarlordOfBlood.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The warlord of blood quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_WARLORD_OF_BLOOD_H
#define QUEST_WARLORD_OF_BLOOD_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestWarlordOfBlood : public Quest
{

public:

  //! Constructor
  QuestWarlordOfBlood();

  //! Destructor
  ~QuestWarlordOfBlood();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestWarlordOfBlood.h
//---------------------------------------------------------------------------//
