//---------------------------------------------------------------------------//
//!
//! \file   LevelSector.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Level sector class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_SECTOR_H
#define LEVEL_SECTOR_H

// Qt Includes
#include <QVector>

// QtD1 Includes
#include "LevelObject.h"
#include "LevelSquare.h"

namespace QtD1{

//! The level sector class
class LevelSector : public LevelObject
{

public:

  //! Constructor
  LevelSector( QVector<QVector<LevelSquare*> > level_squares );

  //! Destructor
  ~LevelSector()
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

  //! Check if the object can be attacked
  bool canBeAttacked() const override;

  //! Get the number or rows in the sector
  int getNumberOfRows() const;

  //! Return the squares that make the sector
  QList<LevelSquare*> getSquaresForRow( int row_number ) const;

  //! Check if it is a pillar
  bool isPillar() const override;

private:

  // The level square z-order map
  QMap<int,QList<LevelSquare*> > d_level_square_z_order_map;

  // The bounding rect
  QRectF d_bounding_rect;
};

} // end QtD1 namespace

#endif // end LEVEL_SECTOR_H

//---------------------------------------------------------------------------//
// end LevelSector.h
//---------------------------------------------------------------------------//
