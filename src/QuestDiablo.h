//---------------------------------------------------------------------------//
//!
//! \file   QuestDiablo.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The diablo quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_DIABLO_H
#define QUEST_DIABLO_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestDiablo : public Quest
{

public:

  //! Constructor
  QuestDiablo();

  //! Destructor
  ~QuestDiablo();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestDiablo.h
//---------------------------------------------------------------------------//
