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

protected:

//! Constructor
LevelPillar( const QVector<int>& level_image_frame_indices,
             const QRectF bounding_rect );

private:

  // The level image frame indices
  QVector<int> d_level_image_frame_indices;
  
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
