//---------------------------------------------------------------------------//
//!
//! \file   Quest.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The quest class declaration
//!
//---------------------------------------------------------------------------//

#ifndef QUEST_H
#define QUEST_H

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include <QString>

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
    KingLeoricsCurse,
    PoisonWater,
    TheButcher,
    OdgensSign,
    GharbadTheWeak,
    TheMagicRock,
    ArmorOfValor,
    HallsOfTheBlind,
    ZharTheMad,
    TheBlackMushroom,
    TheAnvilOfFury,
    TheWarlordOfBlood,
    Lachdanan,
    TheChamberOfBone,
    ArchbishopLazarus,
    Diablo
  };

  // Play the quest dialogue
  virtual void playQuestDialogue() = 0;
};

//! Convert the quest type to a string
QString questTypeToString( const Quest::Type quest );

} // end QtD1 namespace

namespace std{

//! Output stream operator
inline ostream& operator<<( ostream& os, const QtD1::Quest::Type quest )
{
  os << QtD1::questTypeToString( quest ).toStdString();

  return os;
}

} // end std namespace

#endif

//---------------------------------------------------------------------------//
// end Quest.h
//---------------------------------------------------------------------------//
