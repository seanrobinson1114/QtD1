//---------------------------------------------------------------------------//
//!
//! \file   Quest.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_H
#define QUEST_H

namespace QtD1{

class Quest
{

public:

  //! Constructor
  Quest()
  { /* ... */ }

  //! Destructor
  virtual ~Quest()
  { /* ... */ }

  // The quests
  enum Type{
    TheButcher = 0,
    PoisonedWaterSupply = 1,
    TheCurseOfKingLeoric = 2,
    GharbadTheWeak = 3,
    OgdensSign = 4,
    TheMagicRock = 5,
    Valor = 6,
    TheChamberOfBone = 7,
    HallsOfTheBlind = 8,
    ZharTheMad = 9,
    BlackMushroom = 10,
    AnvilOfFury = 11,
    WarlordOfBlood = 12,
    Lachdanan = 13,
    ArchbishopLazarus = 14,
    Diablo = 15
  };

  // Play the quest dialogue
  virtual void playQuestDialogue() = 0;
};

} // end QtD1 namespace

#endif

//---------------------------------------------------------------------------//
// end Quest.h
//---------------------------------------------------------------------------//
