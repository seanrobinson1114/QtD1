//---------------------------------------------------------------------------//
//!
//! \file   GameSpriteData.h
//! \author Alex Robinson
//! \brief  The game sprite data class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GAME_SPRITE_DATA_H
#define GAME_SPRITE_DATA_H

// Qt Includes
#include <QPixmap>
#include <QPainterPath>
#include <QMap>
#include <QString>
#include <QVector>

namespace QtD1{

//! The game sprite data class
class GameSpriteData
{

public:

  //! Constructor
  GameSpriteData();

  //! Destructor
  ~GameSpriteData()
  { /* ... */ }

  //! Set the source
  void setSource( const QString source );

  //! Get the source
  QString getSource() const;

  //! Set the frame indices
  void setFrameIndices( const QVector<int>& source_frame_indices );

  //! Get the frame indices
  const QVector<int>& getFrameIndices() const;

  //! Set the frames
  void setFrames( const QVector<QPixmap>& source_frames );

  //! Clear the frames
  void clearFrames();

  //! Check if the data is ready
  bool isReady() const;

  //! Get the number of frames
  int getNumberOfFrames() const;

  //! Get the frame image
  QPixmap getFrameImage( const int frame ) const;

  //! Get the bounding rect of the frame
  QRectF getFrameBoundingRect( const int frame ) const;

  //! Get the shape of the frame
  QPainterPath getFrameShape( const int frame ) const;

private:

  struct Frame{
    QPixmap pixmap;
    QPainterPath shape;
    QRectF bounding_rect;
  };

  // The source
  QString d_source;

  // The source frame indices
  QVector<int> d_source_frame_indices;

  // The sprite frames
  QVector<Frame> d_frames;
};
  
} // end QtD1 namespace

#endif // end GAME_SPRITE_DATA_H

//---------------------------------------------------------------------------//
// end GameSpriteData.h
//---------------------------------------------------------------------------//
