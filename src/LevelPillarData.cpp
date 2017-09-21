//---------------------------------------------------------------------------//
//!
//! \file   LevelPillarData.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar data class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QPainter>
#include <QBitmap>

// QtD1 Includes
#include "LevelPillarData.h"
#include "LevelPillar.h"

namespace QtD1{

// Constructor
LevelPillarData::LevelPillarData()
{ /* ... */ }

// Copy constructor
LevelPillarData::LevelPillarData( const LevelPillarData& other_data )
  : d_pillar_blocks( other_data.d_pillar_blocks ),
    d_pillar_properties( other_data.d_pillar_properties ),
    d_pillar_image( other_data.d_pillar_image.copy() ),
    d_pillar_bounding_rect( other_data.d_pillar_bounding_rect ),
    d_pillar_shape( other_data.d_pillar_shape )
{ /* ... */ }

// Assignment operator
LevelPillarData& LevelPillarData::operator=( const LevelPillarData& other_data )
{
  if( this != &other_data )
  {
    d_pillar_blocks = other_data.d_pillar_blocks;
    d_pillar_properties = other_data.d_pillar_properties;
    d_pillar_image = other_data.d_pillar_image.copy();
    d_pillar_bounding_rect = other_data.d_pillar_bounding_rect;
    d_pillar_shape = other_data.d_pillar_shape;
  }

  return *this;
}

// Set the pillar blocks
void LevelPillarData::setBlocks(
                             const QVector<LevelPillar::Block>& pillar_blocks )
{
  // Calculate the bounding rect
  if( pillar_blocks.size() != 10 && pillar_blocks.size() != 16 )
  {
    qFatal( "LevelPillarData Error: A level pillar can only have 10 or 16 "
            "blocks (not %i)!", pillar_blocks.size() );
  }

  if( pillar_blocks.size() == 10 )
    d_pillar_bounding_rect = QRectF( 0, 0, 64, 160 );
  else // pillar_blocks.size() == 16
    d_pillar_bounding_rect = QRectF( 0, 0, 64, 256 );

  // Cache the pillar blocks
  d_pillar_blocks = pillar_blocks;
}

// Set the pillar properties
void LevelPillarData::setProperties(
                                   const LevelPillar::Properties& properties )
{
  d_pillar_properties = properties;
}

// Get the pillar properties
const LevelPillar::Properties& LevelPillarData::getProperties() const
{
  return d_pillar_properties;
}

//! Set the shape of the clickable region on the pillar
void LevelPillarData::setShape( const QPainterPath& clickable_region )
{
  d_pillar_shape = clickable_region;
}

// Load the image asset
void LevelPillarData::loadImageAsset(
                                   const QVector<QPixmap>& image_asset_frames )
{
  d_pillar_image = QPixmap( d_pillar_bounding_rect.size().toSize() );
  d_pillar_image.fill( Qt::transparent );

  // Use a painter to fill the pillar image with the blocks
  QPainter pillar_painter( &d_pillar_image );

  // Create the left column of the pillar
  this->createPillarColumn( pillar_painter,
                            image_asset_frames,
                            d_pillar_blocks.size()-2 );

  // Create the right column of the pillar
  this->createPillarColumn( pillar_painter,
                            image_asset_frames,
                            d_pillar_blocks.size()-1 );

  // // Get the pillar shape
  // d_pillar_shape.addRegion( d_pillar_image.createHeuristicMask() );
}

// Create a pillar column
void LevelPillarData::createPillarColumn(
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
    const LevelPillar::Block& block = d_pillar_blocks[i];

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
void LevelPillarData::dumpImageAssets()
{
  d_pillar_image = QPixmap();
  d_pillar_shape = QPainterPath();
}

// Check if the image assets have been loaded
bool LevelPillarData::imageAssetsLoaded() const
{
  return !d_pillar_image.isNull();
}

// Get the bounding rect of the pillar
QRectF LevelPillarData::boundingRect() const
{
  return d_pillar_bounding_rect;
}

// Get the shape of the pillar
QPainterPath LevelPillarData::shape() const
{
  return d_pillar_shape;
}

// Get the level pillar image
QPixmap LevelPillarData::image() const
{
  return d_pillar_image;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelPillarData.cpp
//---------------------------------------------------------------------------//
