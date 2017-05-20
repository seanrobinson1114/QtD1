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
                                const QVector<int>& level_image_frame_indices )
  : LevelPillar( level_image_frame_indices, QRectF( 0, 0, 64, 256 ) )
{ /* ... */ }

// Get the number of image assets used by the object
int TownLevelPillar::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void TownLevelPillar::getImageAssetNames(
                                       QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( "/levels/towndata/town.cel+levels/towndata/town.pal" );
}

// Check if the image asset is used by the object
bool TownLevelPillar::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == "/levels/towndata/town.cel+levels/towndata/town.pal";
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end TownLevelPillar.cpp
//---------------------------------------------------------------------------//
