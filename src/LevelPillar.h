//---------------------------------------------------------------------------//
//!
//! \file   LevelPillar.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_PILLAR_H
#define LEVEL_PILLAR_H

// Qt Includes
#include <QVector>

// QtD1 Includes
#include "LevelObject.h"

namespace QtD1{

//! The level pillar class
class LevelPillar : public LevelObject
{

public:

  //! The level pillar block
  struct Block{
    bool transparent;
    int frame_index;
    int type;
  };

  //! Constructor
  LevelPillar( const QVector<Block>& level_image_blocks );

  //! Destructor
  virtual ~LevelPillar()
  { /* ... */ }

  //! Check if the image assets have been loaded
  bool imageAssetsLoaded() const override;

  //! Load the image asset
  void loadImageAsset( const QString& image_asset_name,
                       const QVector<QPixmap>& image_asset_frames ) override;

  //! Dump the image assets
  void dumpImageAssets() override;

  //! Get the bounding rect of the pillar
  QRectF boundingRect() const override;

  //! Get the shape of the pillar
  QPainterPath shape() const override;

  //! Paint the level pillar
  void paint( QPainter* painter,
              const QStyleOptionGraphicsItem* option,
              QWidget* widget ) override;

private:

  // Create a pillar column
  void createPillarColumn( QPainter& pillar_painer,
                           const QVector<QPixmap>& image_asset_frames,
                           const int start_index );

  // The level image blocks
  QVector<Block> d_level_image_blocks;
  
  // The just-in-time images that make up this pillar
  QPixmap d_pillar_image;

  // The pillar bounding rect
  QRectF d_pillar_bounding_rect;

  // The pillar shape
  QPainterPath d_pillar_shape;
};
  
} // end QtD1 namespace

#endif // end LEVEL_PILLAR_H

//---------------------------------------------------------------------------//
// end LevelPillar.h
//---------------------------------------------------------------------------//
