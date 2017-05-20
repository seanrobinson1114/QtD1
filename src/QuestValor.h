//---------------------------------------------------------------------------//
//!
//! \file   QuestValor.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The valor quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_VALOR_H
#define QUEST_VALOR_H

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

class QuestValor : public Quest
{

public:

  //! Constructor
  QuestValor();

  //! Destructor
  ~QuestValor();

  // Play the quest dialogue
  void playQuestDialogue() override;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end QuestValor.h
//---------------------------------------------------------------------------//
