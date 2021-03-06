//---------------------------------------------------------------------------//
//!
//! \file   LevelSquare.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Level square class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include "LevelSquare.h"

namespace QtD1{

// Constructor
/*! \details Level squares will alwyas have the following dimensions:
 * (2*pillar_width, pillar_height+32).
 */
LevelSquare::LevelSquare( LevelPillar* top_pillar,
                          LevelPillar* right_pillar,
                          LevelPillar* left_pillar,
                          LevelPillar* bottom_pillar )
  : d_top_pillar( top_pillar ),
    d_right_pillar( right_pillar ),
    d_left_pillar( left_pillar ),
    d_bottom_pillar( bottom_pillar ),
    d_bounding_rect(
               QRectF( 0, 0, 2*top_pillar->boundingRect().width(), top_pillar->boundingRect().height()+32 ) )
{
  // Make this the parent of the pillars
  d_top_pillar->setParentItem( this );
  d_right_pillar->setParentItem( this );
  d_left_pillar->setParentItem( this );
  d_bottom_pillar->setParentItem( this );

  // Reposition the pillars
  d_top_pillar->setPos( 32, 0 );
  d_right_pillar->setPos( 64, 16 );
  d_left_pillar->setPos( 0, 16 );
  d_bottom_pillar->setPos( 32, 32 );

  // There is nothing to draw (all drawing is done by the pillars)
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Get the number of image assets used by the object
int LevelSquare::getNumberOfImageAssets() const
{
  QSet<QString> image_asset_names;

  d_top_pillar->getImageAssetNames( image_asset_names );
  d_right_pillar->getImageAssetNames( image_asset_names );
  d_left_pillar->getImageAssetNames( image_asset_names );
  d_bottom_pillar->getImageAssetNames( image_asset_names );

  return image_asset_names.size();
}

// Get the image asset names used by the object
void LevelSquare::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  d_top_pillar->getImageAssetNames( image_asset_names );
  d_right_pillar->getImageAssetNames( image_asset_names );
  d_left_pillar->getImageAssetNames( image_asset_names );
  d_bottom_pillar->getImageAssetNames( image_asset_names );
}

// Check if the image asset is used by the object
bool LevelSquare::isImageAssetUsed( const QString& image_asset_name ) const
{
  return d_top_pillar->isImageAssetUsed( image_asset_name ) ||
    d_right_pillar->isImageAssetUsed( image_asset_name ) ||
    d_left_pillar->isImageAssetUsed( image_asset_name ) ||
    d_bottom_pillar->isImageAssetUsed( image_asset_name );
}

// Check if the image assets have been loaded
bool LevelSquare::imageAssetsLoaded() const
{
  return d_top_pillar->imageAssetsLoaded() &&
    d_right_pillar->imageAssetsLoaded() &&
    d_left_pillar->imageAssetsLoaded() &&
    d_bottom_pillar->imageAssetsLoaded();
}

// Load the image asset
void LevelSquare::loadImageAsset( const QString& image_asset_name,
                                  const QVector<QPixmap>& image_asset_frames )
{
  d_top_pillar->loadImageAsset( image_asset_name, image_asset_frames );
  d_right_pillar->loadImageAsset( image_asset_name, image_asset_frames );
  d_left_pillar->loadImageAsset( image_asset_name, image_asset_frames );
  d_bottom_pillar->loadImageAsset( image_asset_name, image_asset_frames );
}

// Dump the image assets
void LevelSquare::dumpImageAssets()
{
  d_top_pillar->dumpImageAssets();
  d_right_pillar->dumpImageAssets();
  d_left_pillar->dumpImageAssets();
  d_bottom_pillar->dumpImageAssets();
}

// Get the bounding rect of the level square
QRectF LevelSquare::boundingRect() const
{
  return d_bounding_rect;
}

// Paint the level square
/*! \details The level square has nothing to paint. All painting is done by
 * the pillars.
 */
void LevelSquare::paint( QPainter*,
                         const QStyleOptionGraphicsItem*,
                         QWidget* )
{ /* ... */ }

// Clone the level square
LevelSquare* LevelSquare::clone()
{
  LevelSquare* square_clone = new LevelSquare( d_top_pillar->clone(),
                                               d_right_pillar->clone(),
                                               d_left_pillar->clone(),
                                               d_bottom_pillar->clone() );
  
  return square_clone;
}

}// end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelSquare.cpp
//---------------------------------------------------------------------------//
