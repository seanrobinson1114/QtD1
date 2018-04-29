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
  TownLevelPillar();

  //! Constructor
  TownLevelPillar( const QVector<LevelPillar::Block>& level_image_blocks,
                   const LevelPillar::Properties& properties,
                   const QPainterPath& clickable_region );

  //! Copy constructor
  TownLevelPillar( const TownLevelPillar& other_pillar );

  //! Assignment operator
  TownLevelPillar& operator=( const TownLevelPillar& other_pillar );

  //! Destructor
  ~TownLevelPillar()
  { /* ... */ }

  //! Clone the level pillar
  TownLevelPillar* clone() const override;

  //! Get a description of the object
  QString getDescription() const override;

private:

  // Get the image asset required by this level pillar
  QString getRequiredImageAssetName() const override;
};

} // end QtD1 namespace

#endif // end TOWN_LEVEL_PILLAR_H

//---------------------------------------------------------------------------//
// end TownLevelPillar.h
//---------------------------------------------------------------------------//
