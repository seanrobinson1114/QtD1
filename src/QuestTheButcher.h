//---------------------------------------------------------------------------//
//!
//! \file   QuestTheButcher.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The butcher class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_THE_BUTCHER_H
#define QUEST_THE_BUTCHER_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestTheButcher : public Quest
{

public:

  //! Constructor
  QuestTheButcher();

  //! Destructor
  ~QuestTheButcher();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestTheButcher.h
//---------------------------------------------------------------------------//
