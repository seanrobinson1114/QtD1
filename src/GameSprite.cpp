//---------------------------------------------------------------------------//
//!
//! \file   GameSprite.cpp
//! \author Alex Robinson
//! \brief  The game sprite base class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QPainter>

// QtD1 Includes
#include "GameSprite.h"
#include "GameSpriteData.h"

namespace QtD1{

// Constructor
GameSprite::GameSprite( QGraphicsItem* parent )
  : QGraphicsItem( parent ),
    d_asset_data( new GameSpriteData ),
    d_current_frame( 0 )
{ /* ... */ }
  
// Constructor
GameSprite::GameSprite( const QString& source,
                        const QVector<int>& source_frame_indices,
                        QGraphicsItem* parent )
  : QGraphicsItem( parent ),
    d_asset_data( new GameSpriteData ),
    d_current_frame( 0 )
{
  d_asset_data->setSource( source );
  d_asset_data->setFrameIndices( source_frame_indices );
}

// Copy Constructor
GameSprite::GameSprite( const GameSprite& that )
  : QGraphicsItem( that.parentItem() ),
    d_asset_data( that.d_asset_data ),
    d_current_frame( that.d_current_frame )
{ /* ... */ }

// Assignment Operator
GameSprite& GameSprite::operator=( const GameSprite& that )
{
  if( this != &that )
  {
    this->setParentItem( that.parentItem() );
    d_asset_data = that.d_asset_data;
    d_current_frame = that.d_current_frame;
  }

  return *this;
}

// Clone the game sprite
/*! \details The returned game sprite point will be heap allocated.
 */
GameSprite* GameSprite::clone( QGraphicsItem* parent ) const
{
  GameSprite* new_game_sprite = new GameSprite( parent );

  *new_game_sprite->d_asset_data = *this->d_asset_data;
  new_game_sprite->d_current_frame = this->d_current_frame;

  return new_game_sprite;
}

// Set the asset
void GameSprite::setAsset( const QString& source,
                           const QVector<QImage>& source_frames )
{
  if( source != d_asset_data->getSource() )
  {
    qFatal( "GameSprite Error: Asset %s is required (not %s)!",
            d_asset_data->getSource().toStdString().c_str(),
            source.toStdString().c_str() );
  }

  const QVector<int>& frame_indices = d_asset_data->getFrameIndices();
  QVector<QPixmap> extracted_frames( frame_indices.size() );
  
  for( int i = 0; i < frame_indices.size(); ++i )
  {
    if( frame_indices[i] < 0 || frame_indices[i] >= source_frames.size() )
    {
      qFatal( "GameSprite Error: Invalid source frame indices set - cannot "
              "load image asset!" );
    }

    extracted_frames[i].convertFromImage( source_frames[frame_indices[i]] );
  }
  
  d_asset_data->setFrames( extracted_frames );
  this->ready();
}

// Set the asset
void GameSprite::setAsset( const QString& source,
                           const QVector<QPixmap>& source_frames )
{
  if( source != d_asset_data->getSource() )
  {
    qFatal( "GameSprite Error: Asset %s is required (not %s)!",
            d_asset_data->getSource().toStdString().c_str(),
            source.toStdString().c_str() );
  }

  const QVector<int>& frame_indices = d_asset_data->getFrameIndices();
  QVector<QPixmap> extracted_frames( frame_indices.size() );
  
  for( int i = 0; i < frame_indices.size(); ++i )
  {
    if( frame_indices[i] < 0 || frame_indices[i] >= source_frames.size() )
    {
      qFatal( "GameSprite Error: Invalid source frame indices set - cannot "
              "load image asset!" );
    }

    extracted_frames[i] = source_frames[frame_indices[i]];
  }
  
  d_asset_data->setFrames( extracted_frames );
  this->ready();
}

// Dump the game sprite asset
void GameSprite::dumpAsset()
{
  d_asset_data->clearFrames();
  this->notReady();
}

// Check if the game sprite is ready
bool GameSprite::isReady() const
{
  return d_asset_data->isReady();
}
  
// Set the sprite frame
void GameSprite::setFrame( const int frame )
{
  d_current_frame = frame % d_asset_data->getNumberOfFrames();
}

// Increment the sprite frame
void GameSprite::incrementFrame()
{
  d_current_frame = (d_current_frame+1) % d_asset_data->getNumberOfFrames();
}

// Get the sprite frame
int GameSprite::getFrame() const
{
  return d_current_frame;
}

// Get the number of frames
int GameSprite::getNumberOfFrames() const
{
  return d_asset_data->getFrameIndices().size();
}

// Get the frame image
QPixmap GameSprite::getFrameImage( const int frame ) const
{
  if( frame < 0 )
    return d_asset_data->getFrameImage( d_current_frame );
  else if( frame < d_asset_data->getNumberOfFrames() )
    return d_asset_data->getFrameImage( frame );
  else
    return QPixmap();
}

// Get the bounding rect of the current frame
QRectF GameSprite::boundingRect() const
{
  return d_asset_data->getFrameBoundingRect( d_current_frame );
}

// Get the shape of the current frame
QPainterPath GameSprite::shape() const
{
  return d_asset_data->getFrameShape( d_current_frame );
  }

// Paint the current frame
void GameSprite::paint( QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget* )
{
  // Note: Painting occurs in local coordinates, hence the 0, 0 position.
  if( this->isReady() )
    painter->drawPixmap( 0, 0, this->getFrameImage() );
}

// The data is ready
void GameSprite::ready()
{
  // There are now frames to draw
  this->setFlag( QGraphicsItem::ItemHasNoContents, false );
}

// The data is not ready
void GameSprite::notReady()
{
  // There is nothing to draw yet
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end GameSprite.cpp
//---------------------------------------------------------------------------//
