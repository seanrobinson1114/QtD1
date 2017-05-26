//---------------------------------------------------------------------------//
//!
//! \file   LevelPillarData.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar data class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_PILLAR_DATA_H
#define LEVEL_PILLAR_DATA_H

// Qt Includes
#include <QVector>
#include <QPixmap>
#include <QPainterPath>

// QtD1 Includes
#include "LevelPillar.h"

namespace QtD1{

//! The level pillar data class
class LevelPillarData
{

public:

  //! Constructor
  LevelPillarData();

  //! Destructor
  ~LevelPillarData()
  { /* ... */ }

  //! Set the pillar blocks
  void setBlocks( const QVector<LevelPillar::Block>& pillar_blocks );

  //! Load the image asset
  void loadImageAsset( const QVector<QPixmap>& image_asset_frames );

  //! Dump the image assets
  void dumpImageAssets();

  //! Check if the image assets have been loaded
  bool imageAssetsLoaded() const;

  //! Get the bounding rect of the pillar
  QRectF boundingRect() const;

  //! Get the shape of the pillar
  QPainterPath shape() const;

  //! Get the level pillar image
  QPixmap image() const;

private:

  // Create a pillar column
  void createPillarColumn( QPainter& pillar_painer,
                           const QVector<QPixmap>& image_asset_frames,
                           const int start_index );

  // The level image blocks
  QVector<LevelPillar::Block> d_pillar_blocks;
  
  // The just-in-time images that make up this pillar
  QPixmap d_pillar_image;

  // The pillar bounding rect
  QRectF d_pillar_bounding_rect;

  // The pillar shape
  QPainterPath d_pillar_shape;
};
  
} // end QtD1 namespace

#endif // end LEVEL_PILLAR_DATA_H

//---------------------------------------------------------------------------//
// end LevelPillarData.h
//---------------------------------------------------------------------------//
