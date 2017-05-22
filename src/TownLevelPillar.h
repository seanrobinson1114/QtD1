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

private:

  // Get the image asset required by this level pillar
  QString getRequiredImageAssetName() const override;
};
  
} // end QtD1 namespace

#endif // end TOWN_LEVEL_PILLAR_H

//---------------------------------------------------------------------------//
// end TownLevelPillar.h
//---------------------------------------------------------------------------//
