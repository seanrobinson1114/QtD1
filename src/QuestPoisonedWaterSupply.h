//---------------------------------------------------------------------------//
//!
//! \file   QuestPoisonedWaterSupply.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The poisoned water supply quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_POISONED_WATER_SUPPLY_H
#define QUEST_POISONED_WATER_SUPPLY_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestPoisonedWaterSupply : public Quest
{

public:

  //! Constructor
  QuestPoisonedWaterSupply();

  //! Destructor
  ~QuestPoisonedWaterSupply();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestPoisonedWaterSupply.h
//---------------------------------------------------------------------------//
