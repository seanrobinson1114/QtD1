//---------------------------------------------------------------------------//
//!
//! \file   TownLevelPillar.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The town level pillar class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TOWN_LEVEL_PILLAR_H
#define TOWN_LEVEL_PILLAR_H

// QtD1 Includes
#include "LevelPillar.h"

namespace QtD1{

//! The town level pillar
class TownLevelPillar : public LevelPillar
{

public:

  //! Constructor
  TownLevelPillar( const QVector<LevelPillar::Block>& level_image_blocks );

  //! Destructor
  ~TownLevelPillar()
  { /* ... */ }
  
  //! Get the number of image assets used by the object
  int getNumberOfImageAssets() const override;

  //! Get the image asset names used by the object
  void getImageAssetNames( QSet<QString>& image_asset_names ) const override;

  //! Check if the image asset is used by the object
  bool isImageAssetUsed( const QString& image_asset_name ) const override;
};
  
} // end QtD1 namespace

#endif // end TOWN_LEVEL_PILLAR_H

//---------------------------------------------------------------------------//
// end TownLevelPillar.h
//---------------------------------------------------------------------------//
