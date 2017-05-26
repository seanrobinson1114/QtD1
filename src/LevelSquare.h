//---------------------------------------------------------------------------//
//!
//! \file   LevelSquare.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Level square class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_SQUARE_H
#define LEVEL_SQUARE_H

// Qt Includes
#include <QVector>

// QtD1 Includes
#include "LevelObject.h"
#include "LevelPillar.h"

namespace QtD1{

//! The level square class
class LevelSquare : public LevelObject
{

public:

  //! Constructor
  LevelSquare( LevelPillar* top_pillar,
               LevelPillar* right_pillar,
               LevelPillar* left_pillar,
               LevelPillar* bottom_pillar );

  //! Destructor
  ~LevelSquare()
  { /* ... */ }

  //! Get the number of image assets used by the object
  int getNumberOfImageAssets() const override;

  //! Get the image asset names used by the object
  void getImageAssetNames( QSet<QString>& image_asset_names ) const override;

  //! Check if the image asset is used by the object
  bool isImageAssetUsed( const QString& image_asset_name ) const override;

  //! Check if the image assets have been loaded
  bool imageAssetsLoaded() const override;

  //! Load the image asset
  void loadImageAsset( const QString& image_asset_name,
                       const QVector<QPixmap>& image_asset_frames ) override;

  //! Dump the image assets
  void dumpImageAssets() override;

  //! Get the bounding rect of the level square
  QRectF boundingRect() const override;

  //! Paint the level square
  void paint( QPainter* painter,
              const QStyleOptionGraphicsItem* option,
              QWidget* widget ) override;

  //! Clone the level square
  LevelSquare* clone();

private:

  // The pillars
  LevelPillar* d_top_pillar;
  LevelPillar* d_right_pillar;
  LevelPillar* d_left_pillar;
  LevelPillar* d_bottom_pillar;

  // The bounding rect
  QRectF d_bounding_rect;
};

} // end Qtd1 namespace

#endif // end LEVEL_SQUARE_H

//---------------------------------------------------------------------------//
// end LevelSquare.h
//---------------------------------------------------------------------------//
