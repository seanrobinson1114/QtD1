//---------------------------------------------------------------------------//
//!
//! \file   Quest.cpp
//! \author Alex Robinson
//! \brief  The quest enum helper function defintions
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Quest.h"

namespace QtD1{

// Convert the quest to a string
QString questTypeToString( const Quest::Type quest )
{
  switch( quest )
  {
    case Quest::Type::KingLeoricsCurse: return "King Leorics Curse";
    case Quest::Type::PoisonWater: return "Poison Water";
    case Quest::Type::TheButcher: return "The Butcher";
    case Quest::Type::OgdensSign: return "Ogdens Sign";
    case Quest::Type::GharbadTheWeak: return "Gharbad The Weak";
    case Quest::Type::TheMagicRock: return "The Magic Rock";
    case Quest::Type::ArmorOfValor: return "Armor Of Valor";
    case Quest::Type::HallsOfTheBlind: return "Halls Of The Blind";
    case Quest::Type::ZharTheMad: return "Zhar The Mad";
    case Quest::Type::TheBlackMushroom: return "The Black Mushroom";
    case Quest::Type::TheAnvilOfFury: return "The Anvil Of Fury";
    case Quest::Type::TheWarlordOfBlood: return "The Warlord Of Blood";
    case Quest::Type::Lachdanan: return "Lachdanan";
    case Quest::Type::TheChamberOfBone: return "The Chamber Of Bone";
    case Quest::Type::ArchbishopLazarus: return "Archbishop Lazarus";
    case Quest::Type::Diablo: return "Diablo";
  }
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Quest.cpp
//---------------------------------------------------------------------------//
