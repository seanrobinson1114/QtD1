//---------------------------------------------------------------------------//
//!
//! \file   TownLevelPillar.cpp
//! \author Alex Robinson
//! \brief  The town level pillar class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "TownLevelPillar.h"

namespace QtD1{

// Constructor
TownLevelPillar::TownLevelPillar(
                        const QVector<LevelPillar::Block>& level_image_blocks )
  : LevelPillar( level_image_blocks )
{ /* ... */ }

// Get the image asset required by this level pillar
QString TownLevelPillar::getRequiredImageAssetName() const
{
  return "/levels/towndata/town.cel+levels/towndata/town.pal";
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end TownLevelPillar.cpp
//---------------------------------------------------------------------------//
