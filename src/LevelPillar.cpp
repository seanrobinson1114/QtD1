//---------------------------------------------------------------------------//
//!
//! \file   LevelPillar.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QPainter>
#include <QBitmap>

// QtD1 Includes
#include "LevelPillar.h"

namespace QtD1{

// Constructor
LevelPillar::LevelPillar( const QVector<Block>& level_image_blocks )
  : d_level_image_blocks( level_image_blocks ),
    d_pillar_image(),
    d_pillar_bounding_rect(),
    d_pillar_shape()
{
  // Calculate the bounding rect
  if( level_image_blocks.size() != 10 && level_image_blocks.size() != 16 )
  {
    qFatal( "LevelPillar Error: A level pillar can only have 10 or 16 blocks "
            "(not %i)!", level_image_blocks.size() );
  }

  if( level_image_blocks.size() == 10 )
    d_pillar_bounding_rect = QRectF( 0, 0, 64, 160 );
  else // level_image_blocks.size() == 16
    d_pillar_bounding_rect = QRectF( 0, 0, 64, 256 );

  // There is nothing to draw until the image asset has been loaded
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Constructor
LevelPillar::LevelPillar()
{ /* ... */ }

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
  return !d_pillar_image.isNull();
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

  d_pillar_image = QPixmap( d_pillar_bounding_rect.size().toSize() );
  d_pillar_image.fill( Qt::transparent );

  // Use a painter to fill the pillar image with the blocks
  QPainter pillar_painter( &d_pillar_image );

  // Create the left column of the pillar
  this->createPillarColumn( pillar_painter,
                            image_asset_frames,
                            d_level_image_blocks.size()-2 );

  // Create the right column of the pillar
  this->createPillarColumn( pillar_painter,
                            image_asset_frames,
                            d_level_image_blocks.size()-1 );

  // Get the pillar shape
  d_pillar_shape.addRegion( d_pillar_image.createHeuristicMask() );

  this->setFlag( QGraphicsItem::ItemHasNoContents, false );
}

// Create a pillar column
void LevelPillar::createPillarColumn(
                                    QPainter& pillar_painter,
                                    const QVector<QPixmap>& image_asset_frames,
                                    const int start_index )
{
  // Note: All even indices will form the left column of the pillar starting
  //       from the top. All odd indices will form the right column of the
  //       pillar starting from the top.
  QRect pillar_painter_viewport( (start_index % 2)*32,
                                 (start_index/2)*32,
                                 32,
                                 32 );
  bool first_block = true;
  bool move_block_up = false;

  for( int i = start_index; i >= 0; i -= 2 )
  {
    const Block& block = d_level_image_blocks[i];

    // Check if the block is transparent - do nothing
    if( block.transparent )
      first_block = true;
    else
    {
      // A block of type 4 or 5 must be moved up. All blocks above it in the
      // same section of the column must also be moved up.
      if( block.type == 4 || block.type == 5 )
        move_block_up = true;
      else
      {
        if( first_block )
        {
          // If the first block in a section is of type 1, the entire section
          // of blocks should move up.
          if( block.type == 1 )
            move_block_up = true;
          else
            move_block_up = false;
        }
      }

      if( move_block_up )
      {
        pillar_painter_viewport.moveTop( pillar_painter_viewport.top() - 1 );
        move_block_up = false;
      }

      // Draw the block
      pillar_painter.drawPixmap( pillar_painter_viewport,
                                 image_asset_frames[block.frame_index],
                                 image_asset_frames[block.frame_index].rect() );
      first_block = false;
    }

    // Move the viewport
    pillar_painter_viewport.moveTop( pillar_painter_viewport.top() - 32 );
  }
}

// Dump the image assets
void LevelPillar::dumpImageAssets()
{
  d_pillar_image = QPixmap();
  d_pillar_shape = QPainterPath();
}

// Get the bounding rect of the actor
QRectF LevelPillar::boundingRect() const
{
  return d_pillar_bounding_rect;
}

// Get the shape of the actor
QPainterPath LevelPillar::shape() const
{
  return d_pillar_shape;
}

// Paint the level pillar
void LevelPillar::paint( QPainter* painter,
                         const QStyleOptionGraphicsItem*,
                         QWidget* )
{
  // Note: Painting occurs in local coordinates, hence the 0, 0 position.
  painter->drawPixmap( 0, 0, d_pillar_image );
}

// Deep copy pillar data
void LevelPillar::deepCopyPillarData( LevelPillar& pillar ) const
{
  pillar.d_level_image_blocks = d_level_image_blocks;
  pillar.d_pillar_bounding_rect = d_pillar_bounding_rect;

  if( !d_pillar_image.isNull() )
  {
    pillar.d_pillar_image = d_pillar_image.copy();
    pillar.d_pillar_shape = d_pillar_shape;
  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelPillar.cpp
//---------------------------------------------------------------------------//
