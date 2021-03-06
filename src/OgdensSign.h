//---------------------------------------------------------------------------//
//!
//! \file   QuestOdgensSign.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The ogdens sign quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_OGDENS_SIGN_H
#define QUEST_OGDENS_SIGN_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestOdgensSign : public Quest
{

public:

  //! Constructor
  QuestOdgensSign();

  //! Destructor
  ~QuestOdgensSign();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestOdgensSign.h
//---------------------------------------------------------------------------//
