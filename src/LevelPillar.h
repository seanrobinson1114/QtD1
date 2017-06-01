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

class LevelPillarData;

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
  LevelPillar();

  //! Constructor
  LevelPillar( const QVector<Block>& level_image_blocks );

  //! Copy constructor
  LevelPillar( const LevelPillar& other_pillar );

  //! Assignment operator
  LevelPillar& operator=( const LevelPillar& other_pillar );

  //! Destructor
  virtual ~LevelPillar()
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

  //! Get the bounding rect of the pillar
  QRectF boundingRect() const override;

  //! Get the shape of the pillar
  //QPainterPath shape() const override;

  //! Paint the level pillar
  void paint( QPainter* painter,
              const QStyleOptionGraphicsItem* option,
              QWidget* widget ) override;

  //! Check if the object can be attacked
  bool canBeAttacked() const override;

  //! Clone the level pillar
  virtual LevelPillar* clone() const = 0;

protected:

  //! Get the image asset required by this level pillar
  virtual QString getRequiredImageAssetName() const = 0;

  //! Deep copy the pillar data
  void deepCopyPillarData( const LevelPillar& other_pillar ) const;

private:

  // Create a pillar column
  void createPillarColumn( QPainter& pillar_painer,
                           const QVector<QPixmap>& image_asset_frames,
                           const int start_index );

  // The level pillar data
  std::shared_ptr<LevelPillarData> d_data;
};
  
} // end QtD1 namespace

#endif // end LEVEL_PILLAR_H

//---------------------------------------------------------------------------//
// end LevelPillar.h
//---------------------------------------------------------------------------//
