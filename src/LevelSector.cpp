//---------------------------------------------------------------------------//
//!
//! \file   LevelSector.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Level sector class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "LevelSector.h"

#include <iostream>

namespace QtD1{

// Constructor
LevelSector::LevelSector( QVector<QVector<LevelSquare*> > level_squares )
  : d_level_square_z_order_map(),
    d_bounding_rect()
{
  // Make sure that the rows are valid
  int num_cols = level_squares.front().size();

  if( num_cols == 0 )
    qFatal( "LevelSector Error: There are zero columns in the sector!" );

  for( int i = 1; i < level_squares.size(); ++i )
  {
    if( level_squares[i].size() != num_cols )
    {
      qFatal( "LevelSector Error: The number of columns differs between "
              "rows!" );
    }
  }

  // Calculate the sector dimensions
  int num_rows = level_squares.size();

  int sector_width = (num_cols+num_rows)*64;
  int sector_height = (num_cols+num_cols)*32 +
    (level_squares.front().front()->boundingRect().height() - 64);

  d_bounding_rect = QRectF( 0, 0, sector_width, sector_height );

  // Create the level square z-order map
  int max_y_pos = 0;

  for( int j = 0; j < level_squares.size(); ++j )
  {
    for( int i = 0; i < level_squares[j].size(); ++i )
    {
      LevelSquare* square = level_squares[j][i];
      
      // The y position gives us the z-order
      int y_pos = (i+j)*32;
      int x_pos = (int)d_bounding_rect.width()/2 + (i-j-1)*64;

      if( y_pos > max_y_pos )
        max_y_pos = y_pos;

      // Null square pointers are treated as transparent regions
      if( square )
      {
        d_level_square_z_order_map[y_pos] << square;

        // This will have to be set again once the parent has been assigned
        square->setPos( x_pos, y_pos );
      }
    }
  }

  // Assign the level squares to this in order of the z-order
  for( int i = 0; i <= max_y_pos; i += 32 )
  {
    QList<LevelSquare*>& level_squares =
      d_level_square_z_order_map[i];
    
    QList<LevelSquare*>::iterator level_squares_it, level_squares_end;
    level_squares_it = level_squares.begin();
    level_squares_end = level_squares.end();

    while( level_squares_it != level_squares_end )
    {
      QPointF position = (*level_squares_it)->pos();

      (*level_squares_it)->setParentItem( this );
      
      // Set the position again so that it is w.r.t. the sector coordinate sys.
      (*level_squares_it)->setPos( position );

      ++level_squares_it;
    }
  }

  // There is nothing to draw (all drawing is done by the pillars)
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Get the number of image assets used by the object
int LevelSector::getNumberOfImageAssets() const
{
  QSet<QString> image_asset_names;

  for( int j = 0; j < d_level_square_z_order_map.size(); ++j )
  {
    for( int i = 0; i < d_level_square_z_order_map[j].size(); ++i )
      d_level_square_z_order_map[j][i]->getImageAssetNames( image_asset_names );
  }

  return image_asset_names.size();
}

// Get the image asset names used by the object
void LevelSector::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  for( int j = 0; j < d_level_square_z_order_map.size(); ++j )
  {
    for( int i = 0; i < d_level_square_z_order_map[j].size(); ++i )
      d_level_square_z_order_map[j][i]->getImageAssetNames( image_asset_names );
  }
}

// Check if the image asset is used by the object
bool LevelSector::isImageAssetUsed( const QString& image_asset_name ) const
{
  for( int j = 0; j < d_level_square_z_order_map.size(); ++j )
  {
    for( int i = 0; i < d_level_square_z_order_map[j].size(); ++i )
    {
      if( d_level_square_z_order_map[j][i]->isImageAssetUsed( image_asset_name ) )
        return true;
    }
  }

  return false;
}

// Check if the image assets have been loaded
bool LevelSector::imageAssetsLoaded() const
{
  for( int j = 0; j < d_level_square_z_order_map.size(); ++j )
  {
    for( int i = 0; i < d_level_square_z_order_map[j].size(); ++i )
    {
      if( !d_level_square_z_order_map[j][i]->imageAssetsLoaded() )
        return false;
    }
  }

  return true;
}

// Load the image asset
void LevelSector::loadImageAsset( const QString& image_asset_name,
                                  const QVector<QPixmap>& image_asset_frames )
{
  for( int j = 0; j < d_level_square_z_order_map.size(); ++j )
  {
    QList<LevelSquare*>& row_level_squares = d_level_square_z_order_map[j];
    
    for( int i = 0; i < row_level_squares.size(); ++i )
    {
      if( !row_level_squares[i]->imageAssetsLoaded() )
      {
        row_level_squares[i]->loadImageAsset( image_asset_name,
                                              image_asset_frames );
      }
    }
  }
}

// Dump the image assets
void LevelSector::dumpImageAssets()
{
  for( int j = 0; j < d_level_square_z_order_map.size(); ++j )
  {
    QList<LevelSquare*>& row_level_squares = d_level_square_z_order_map[j];
    
    for( int i = 0; i < row_level_squares.size(); ++i )
    {
      if( row_level_squares[i]->imageAssetsLoaded() )
        row_level_squares[i]->dumpImageAssets();
    }
  }
}

// Get the bounding rect of the level square
QRectF LevelSector::boundingRect() const
{
  return d_bounding_rect;
}

// Paint the level square
/*! \details The level sector has nothing to paint. All painting is done by
 * the pillars.
 */
void LevelSector::paint( QPainter*,
                         const QStyleOptionGraphicsItem*,
                         QWidget* )
{ /* ... */ }

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelSector.cpp
//---------------------------------------------------------------------------//
