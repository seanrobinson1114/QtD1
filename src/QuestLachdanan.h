//---------------------------------------------------------------------------//
//!
//! \file   QuestLachdanan.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The lachdanan quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_LACHDANAN_H
#define QUEST_LACHDANAN_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestLachdanan : public Quest
{

public:

  //! Constructor
  QuestLachdanan();

  //! Destructor
  ~QuestLachdanan();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestLachdanan.h
//---------------------------------------------------------------------------//
