//---------------------------------------------------------------------------//
//!
//! \file   QuestAnvilOfFury.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The anvil of fury quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_ANVIL_OF_FURY_H
#define QUEST_ANVIL_OF_FURY_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestAnvilOfFury : public Quest
{

public:

  //! Constructor
  QuestAnvilOfFury();

  //! Destructor
  ~QuestAnvilOfFury();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestAnvilOfFury.h
//---------------------------------------------------------------------------//
