//---------------------------------------------------------------------------//
//!
//! \file   LevelPillar.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillar class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QPainter>

// QtD1 Includes
#include "LevelPillar.h"

namespace QtD1{

// Constructor
LevelPillar::LevelPillar( const QVector<int>& level_image_frame_indices,
                          const QRectF bounding_rect )
  : d_level_image_frame_indices( level_image_frame_indices ),
    d_pillar_image(),
    d_pillar_bounding_rect( bounding_rect ),
    d_pillar_shape()
{ /* ... */ }

// Check if the image assets have been loaded
bool LevelPillar::imageAssetsLoaded() const
{
  return !d_pillar_image.isNull();
}

// Load the image asset
void LevelPillar::loadImageAsset( const QString& image_asset_name,
                                  const QVector<QPixmap>& image_asset_frames )
{
  // Initialize the pillar image
  QSize pillar_size = this->getImageSize();

  d_pillar_image = QPixmap( pillar_size );

  // Use a painter to fill the pillar image with the blocks
  QPainter pillar_painter( &d_pillar_image );

  // Note: All even indices will form the left column of the pillar starting
  //       from the top. All odd indices will form the right column of the
  //       pillar starting from the top.
  QRect pillar_painter_viewport( 0, 0, 32, 32 );
  
  for( int i = 0; i < d_level_image_frame_indices.size(); ++i )
  {
    // Left column
    if( i % 2 == 0 )
    {
      pillar_painter_viewport.setLeft( 0 );
      pillar_painter_viewport.setTop( (i/2)*32 );
    }
    // Right column
    else
      pillar_painter_viewport.setLeft( 32 );

    // Get the block image
    int frame_index = d_level_image_frame_indices[i];
    QPixmap block = image_asset_frames[frame_index];

    // Draw the block
    pillar_painter.drawPixmap( pillar_painter_viewport, block, block.rect() );
  }

  // Get the pillar shape
  d_pillar_shape.addRegion( d_pillar_image.createHeuristicMask() );
}

// Dump the image assets
void LevelPillar::dumpImageAssets()
{
  d_pillar_image = QPixmap();
  d_pillar_bounding_rect = QRectF();
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
  return d_pillar_shape();
}

// Paint the level pillar
void LevelPillar::paint( QPainter* painter,
                         const QStyleOptionGraphicsItem*,
                         QWidget* )
{
  if( !d_pillar_image.isNull() )
  {
    // Note: Painting occurs in local coordinates, hence the 0, 0 position.
    painter->drawPixmap( 0, 0, d_pillar_image );
  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelPillar.cpp
//---------------------------------------------------------------------------//
