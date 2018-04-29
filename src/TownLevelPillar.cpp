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

// Default Constructor
TownLevelPillar::TownLevelPillar()
{ /* ... */ }

// Constructor
TownLevelPillar::TownLevelPillar(
                         const QVector<LevelPillar::Block>& level_image_blocks,
                         const LevelPillar::Properties& properties,
                         const QPainterPath& clickable_region )
  : LevelPillar( level_image_blocks, properties, clickable_region )
{ /* ... */ }

// Copy constructor
TownLevelPillar::TownLevelPillar( const TownLevelPillar& other_pillar )
  : LevelPillar( other_pillar )
{ /* ... */ }

// Assignment operator
TownLevelPillar& TownLevelPillar::operator=(
                                          const TownLevelPillar& other_pillar )
{
  if( this != &other_pillar )
    LevelPillar::operator=( other_pillar );

  return *this;
}

// Clone the level pillar
TownLevelPillar* TownLevelPillar::clone() const
{
  TownLevelPillar* new_pillar = new TownLevelPillar( *this );

  return new_pillar;
}

// Get the image asset required by this level pillar
QString TownLevelPillar::getRequiredImageAssetName() const
{
  return "/levels/towndata/town.cel+levels/towndata/town.pal";
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end TownLevelPillar.cpp
//---------------------------------------------------------------------------//
