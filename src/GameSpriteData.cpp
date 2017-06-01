//---------------------------------------------------------------------------//
//!
//! \file   GameSpriteData.cpp
//! \author Alex Robinson
//! \brief  The game sprite data class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QBitmap>
#include <QPainter>

// QtD1 Includes
#include "GameSpriteData.h"

namespace QtD1{

// Constructor
GameSpriteData::GameSpriteData()
  : d_source(),
    d_source_frame_indices(),
    d_frames(),
    d_game_tics_per_frame( 1 )
{ /* ... */ }

// Set the source
void GameSpriteData::setSource( const QString source )
{
  d_source = source;
}

// Get the source
QString GameSpriteData::getSource() const
{
  return d_source;
}

// Set the frame indices
void GameSpriteData::setFrameIndices( const QVector<int>& source_frame_indices )
{
  d_source_frame_indices = source_frame_indices;
}

// Get the frame indices
const QVector<int>& GameSpriteData::getFrameIndices() const
{
  return d_source_frame_indices;
}

// Set the frames
void GameSpriteData::setFrames( const QVector<QPixmap>& source_frames )
{
  d_frames.resize( source_frames.size() );

  for( int i = 0; i < source_frames.size(); ++i )
  {
    Frame& frame = d_frames[i];
    
    frame.pixmap = source_frames[i];
    frame.shape.addRegion( frame.pixmap.createHeuristicMask() );
    frame.bounding_rect = frame.pixmap.rect();
  }
}

// Clear the frames
void GameSpriteData::clearFrames()
{
  d_frames.clear();
}

// Check if the data is ready
bool GameSpriteData::isReady() const
{
  return d_frames.size() > 0;
}

// Set the duration of the sprite (in game tics)
void GameSpriteData::setDuration( const int duration )
{
  d_game_tics_per_frame = std::max( duration/d_frames.size(), 1 );
}

// Get the duration of the sprite (in game tics)
int GameSpriteData::getDuration() const
{
  return d_game_tics_per_frame*d_frames.size();
}

// Set the duration of each sprite frame (in game tics)
void GameSpriteData::setFrameDuration( const int duration )
{
  d_game_tics_per_frame = std::max( duration, 1 );
}

// Get the duration of each sprite frame (in game tics)
int GameSpriteData::getFrameDuration() const
{
  return d_game_tics_per_frame;
}
  
// Get the number of frames
int GameSpriteData::getNumberOfFrames() const
{
  return d_frames.size();
}

// Get the frame image
QPixmap GameSpriteData::getFrameImage( const int frame ) const
{
  if( frame < d_frames.size() && frame >= 0 )
    return d_frames[frame].pixmap;
  else
    return QPixmap();
}

// Get the bounding rect of the frame
QRectF GameSpriteData::getFrameBoundingRect( const int frame ) const
{
  if( frame < d_frames.size() && frame >= 0 )
    return d_frames[frame].bounding_rect;
  else
    return QRectF();
}

// Get the shape of the frame
QPainterPath GameSpriteData::getFrameShape( const int frame ) const
{
  if( frame < d_frames.size() && frame >= 0 )
    return d_frames[frame].shape;
  else
    return QPainterPath();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end GameSpriteData.cpp
//---------------------------------------------------------------------------//
