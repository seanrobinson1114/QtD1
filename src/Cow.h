//---------------------------------------------------------------------------//
//!
//! \file   Cow.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The cow class declaration
//!
//---------------------------------------------------------------------------//

#ifndef COW_H
#define COW_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "InteractiveLevelObject.h"
#include "Direction.h"
#include "GameSprite.h"

namespace QtD1{

//! The cow class
class Cow : public InteractiveLevelObject
{
  Q_OBJECT

public:

  //! Constructor
  Cow( const Direction direction,
       QGraphicsObject* parent = 0 );

  //! Destructor
  ~Cow()
  { /* ... */ }

  //! Get a description of the object
  QString getDescriptionText() const final override;

  //! Get the direction
  Direction getDirection() const;

  //! Check if the image asset is used by the object
  bool isImageAssetUsed( const QString& image_asset_name ) const final override;

  //! Get the image asset names used by the object
  void getImageAssetNames( QSet<QString>& image_asset_names ) const final override;

  //! Get the number of image assets used by the object
  int getNumberOfImageAssets() const final override;

  //! Check if the image assets have been loaded
  bool imageAssetsLoaded() const final override;

  //! Load the raw image asset
  void loadRawImageAsset( const QString& image_asset_name,
                          const QVector<QImage>& image_asset_frames ) final override;

  //! Load the image asset
  void loadImageAsset( const QString& image_asset_name,
                       const QVector<QPixmap>& image_asset_frames ) final override;

  //! Finalize image asset loading
  void finalizeImageAssetLoading() final override;

  //! Dump the image assets
  void dumpImageAssets() final override;

  //! Check if the object can be attacked
  bool canBeAttacked() const final override;

  //! Get the bounding rect of the basic actor
  QRectF boundingRect() const override;

  //! Get the shape of the basic actor
  QPainterPath shape() const override;

  //! Advance the basic actor state (if time dependent)
  void advance( int phase ) override;

protected:

  //! The paint implementation
  virtual void paintImpl( QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget ) final override;

protected slots:

  //! Handle being targeted by another object
  void handleBeingTargeted( LevelObject* targeter ) final override;

private:

  // The image asset name
  static QString getImageAssetName();

  // The cow direction game sprite map
  static std::unique_ptr<QMap<Direction,GameSprite> > s_direction_game_sprites;

  // The cow direction
  Direction d_direction;
  
  // The cow game sprite
  GameSprite d_sprites;
};

} // end QtD1 namespace

#endif // end COW_H

//---------------------------------------------------------------------------//
// end Cow.h
//---------------------------------------------------------------------------//
