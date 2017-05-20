//---------------------------------------------------------------------------//
//!
//! \file   QuestGharbadTheWeak.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The gharbad the weak quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_GHARBAD_THE_WEAK_H
#define QUEST_GHARBAD_THE_WEAK_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestGharbadTheWeak : public Quest
{

public:

  //! Constructor
  QuestGharbadTheWeak();

  //! Destructor
  ~QuestGharbadTheWeak();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestGharbadTheWeak.h
//---------------------------------------------------------------------------//
