//---------------------------------------------------------------------------//
//!
//! \file   LevelPillar.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QPainter>
#include <QBitmap>

// QtD1 Includes
#include "LevelPillar.h"
#include "LevelPillarData.h"

namespace QtD1{

// Constructor
LevelPillar::LevelPillar()
{ /* ... */ }

// Constructor
LevelPillar::LevelPillar( const QVector<Block>& level_image_blocks )
  : LevelObject(),
    d_data( new LevelPillarData )
{
  d_data->setBlocks( level_image_blocks );
}

// Copy constructor
LevelPillar::LevelPillar( const LevelPillar& other_pillar )
  : LevelObject(),
    d_data( other_pillar.d_data )
{ /* ... */ }

// Assignment operator
LevelPillar& LevelPillar::operator=( const LevelPillar& other_pillar )
{
  if( this != &other_pillar )
  {
    d_data = other_pillar.d_data;
  }

  return *this;
}

// Deep copy the pillar data
void LevelPillar::deepCopyPillarData( const LevelPillar& other_pillar ) const
{
  *other_pillar.d_data = *d_data;
}

// Get the number of image assets used by the object
int LevelPillar::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset names used by the object
void LevelPillar::getImageAssetNames(
                                       QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( this->getRequiredImageAssetName() );
}

// Check if the image asset is used by the object
bool LevelPillar::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == this->getRequiredImageAssetName();
}

// Check if the image assets have been loaded
bool LevelPillar::imageAssetsLoaded() const
{
  return d_data->imageAssetsLoaded();
}

// Load the image asset
void LevelPillar::loadImageAsset( const QString& image_asset_name,
                                  const QVector<QPixmap>& image_asset_frames )
{
  if( image_asset_name != this->getRequiredImageAssetName() )
  {
    qFatal( "LevelPillar Error: Image asset %s is not used by the level "
            "pillar (%s required)!",
            image_asset_name.toStdString().c_str(),
            this->getRequiredImageAssetName().toStdString().c_str() );
  }

  if( !d_data->imageAssetsLoaded() )
    d_data->loadImageAsset( image_asset_frames );
}

// Dump the image assets
void LevelPillar::dumpImageAssets()
{
  if( d_data->imageAssetsLoaded() )
    d_data->dumpImageAssets();
}

// Get the bounding rect of the pillar
QRectF LevelPillar::boundingRect() const
{
  return d_data->boundingRect();
}

// // Get the shape of the actor
// QPainterPath LevelPillar::shape() const
// {
//   return d_data->shape();
// }

// Paint the level pillar
void LevelPillar::paint( QPainter* painter,
                         const QStyleOptionGraphicsItem*,
                         QWidget* )
{
  // Note: Painting occurs in local coordinates, hence the 0, 0 position.
  painter->drawPixmap( 0, 0, d_data->image() );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelPillar.cpp
//---------------------------------------------------------------------------//
