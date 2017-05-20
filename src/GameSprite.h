//---------------------------------------------------------------------------//
//!
//! \file   GameSprite.h
//! \author Alex Robinson
//! \brief  The game sprite class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QGraphicsItem>
#include <QVector>
#include <QPixmap>

namespace QtD1{

class GameSpriteData;
  
//! The game sprite class
class GameSprite : public QGraphicsItem
{

public:

  //! Constructor
  GameSprite( QGraphicsItem* parent = 0 );

  //! Constructor
  GameSprite( const QString& source,
              const QVector<int>& source_frame_indices,
              QGraphicsItem* parent = 0 );

  //! Copy Constructor
  GameSprite( const GameSprite& that );

  //! Assignment Operator
  GameSprite& operator=( const GameSprite& that );

  //! Clone the game sprite
  GameSprite* clone( QGraphicsItem* parent = 0 ) const;

  //! Destructor
  ~GameSprite()
  { /* ... */ }

  //! Set the asset
  void setAsset( const QString& source,
                 const QVector<QImage>& source_frames );

  //! Set the asset
  void setAsset( const QString& source,
                 const QVector<QPixmap>& source_frames );

  //! Dump the game sprite asset
  void dumpAsset();

  //! Check if the game sprite is ready
  bool isReady() const;

  //! Set the sprite frame
  void setFrame( const int frame );

  //! Increment the sprite frame
  void incrementFrame();

  //! Get the sprite frame
  int getFrame() const;

  //! Get the number of frames
  int getNumberOfFrames() const;

  //! Get the frame image
  QPixmap getFrameImage( const int frame = -1 ) const;

  //! Get the bounding rect of the current frame
  QRectF boundingRect() const override;

  //! Get the shape of the current frame
  QPainterPath shape() const override;

  //! Paint the current frame
  void paint( QPainter* painter,
              const QStyleOptionGraphicsItem* option,
              QWidget* widget ) override;
  
private:

  // The data is ready
  void ready();

  // The data is not ready
  void notReady();

  // The game sprite asset data
  std::shared_ptr<GameSpriteData> d_asset_data;

  // The current frame
  int d_current_frame;
};
  
} // end QtD1 namespace

#endif // end GAME_SPRITE_H

//---------------------------------------------------------------------------//
// end GameSprite.h
//---------------------------------------------------------------------------//
