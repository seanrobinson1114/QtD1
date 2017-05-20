//---------------------------------------------------------------------------//
//!
//! \file   MenuSprite.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The menu sprite class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MENU_SPRITE_H
#define MENU_SPRITE_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QDeclarativeItem>
#include <QVector>
#include <QPixmap>
#include <QColor>
#include <QList>
#include <QVariant>

// QtD1 Includes
#include "Viewport.h"
#include "FrameLoader.h"
#include "QMLRegistrationHelper.h"

namespace QtD1{

//! The menu sprite class
class MenuSprite : public QDeclarativeItem
{
  Q_OBJECT
  Q_PROPERTY(QString source READ getSource WRITE setSource)
  Q_PROPERTY(QtD1::Viewport::DisplayPolicy display READ getDisplayPolicy WRITE setDisplayPolicy)
  Q_PROPERTY(QColor background READ getBackgroundColor WRITE setBackgroundColor)
  Q_PROPERTY(quint32 sourceRows READ getNumberOfRows WRITE setNumberOfRows NOTIFY spriteDimensionChanged )
  Q_PROPERTY(quint32 sourceCols READ getNumberOfCols WRITE setNumberOfCols NOTIFY spriteDimensionChanged )
  Q_PROPERTY(QVariant displayFrames READ getDisplayedFrameIndices WRITE setDisplayedFrameIndices NOTIFY displayedFrameIndicesChanged)
  Q_PROPERTY(quint32 startFrame READ getStartingFrameIndex WRITE setStartingFrameIndex)
  Q_PROPERTY(quint32 frame READ getCurrentFrameIndex WRITE setCurrentFrameIndex)
  Q_PROPERTY(quint32 numFrames READ getNumberOfFrames)
  Q_PROPERTY(int frameWidth READ getCurrentFrameWidth)
  Q_PROPERTY(int frameHeight READ getCurrentFrameHeight)
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "MenuSprite" )

public:

  //! Constructor
  MenuSprite( QDeclarativeItem* parent = 0 );

  //! Destructor
  virtual ~MenuSprite()
  { /* ... */ }

  //! Get the sprite image source
  QString getSource() const;

  //! Set the sprite image source
  void setSource( const QString& source );

  //! Get the stretch type
  Viewport::DisplayPolicy getDisplayPolicy() const;

  //! Set the display policy
  void setDisplayPolicy( const Viewport::DisplayPolicy policy );

  //! Get the sprite background color
  QColor getBackgroundColor() const;

  //! Set the background color (will be transparent)
  void setBackgroundColor( const QColor& background_color );

  //! Get the number of rows in the sprite sheet
  quint32 getNumberOfRows() const;

  //! Set the number of rows in the sprite sheet
  void setNumberOfRows( const quint32 num_rows );

  //! Get the number of columns in the sprite sheet
  quint32 getNumberOfCols() const;

  //! Set the number of columns in the sprite sheet
  void setNumberOfCols( const quint32 num_cols );

  //! Get the indices of frames that will be displayed
  QVariant getDisplayedFrameIndices() const;

  //! Set the indices of frames that will be displayed
  void setDisplayedFrameIndices( const QVariant& frame_indices );

  //! Get the starting frame index
  quint32 getStartingFrameIndex() const;

  //! Set the starting frame index
  void setStartingFrameIndex( const quint32 start_frame_index );

  //! Get the current frame index
  quint32 getCurrentFrameIndex() const;

  //! Set the current frame index
  void setCurrentFrameIndex( const quint32 frame_index );

  //! Get the current frame width
  int getCurrentFrameWidth() const;

  //! Get the current frame height
  int getCurrentFrameHeight() const;

  //! Get the number of frames
  quint32 getNumberOfFrames() const;

  //! Get the frames
  void getFrames( QVector<QPixmap>& frames ) const;

  //! Get the frame
  QPixmap getFrame( const int index ) const;

  //! Paint the current sprite frame
  void paint( QPainter* painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget = 0 ) override;

signals:

  void sourceLoaded( QString source );
  void frameChanged( quint32 new_frame );
  void spriteDimensionChanged( int new_dimension_value );
  void displayedFrameIndicesChanged( const QVariant& frame_indices );

public slots:

  //! Load the sprite frames (asynchronous)
  void load();

  //! Load the sprite frames synchronously
  void loadSync();

  //! Wait for load to finish
  void waitForLoadToFinish();

private slots:

  //! Handle frame loaded
  void handleFrameLoaded( const int frame_index, QImage frame );

  //! Handle source loaded
  void handleLoadingFinished();

private:

  // Dump the frames
  void dumpFrames();

  // The frames are ready
  void ready();

  // The frames are not ready
  void notReady();

  // Calculate the frame index within the range [0,d_sprite_frames.size())
  quint32 calculateBoundedFrameIndex() const;

  // Initialize the frame loader
  void initializeFrameLoader();

  // Connect the frame loader signals to menu sprite slots
  void connectFrameLoaderSignalsToMenuSpriteSlots();

  struct Frame{
    QPixmap pixmap;
    QRectF source_viewport;
    QRectF target_viewport;
  };

  // The sprite image source
  QString d_source;

  // The display policy
  Viewport::DisplayPolicy d_display_policy;

  // The sprite sheet background color
  QColor d_background_color;

  // The number of rows in the sprite sheet
  quint32 d_source_rows;

  // The number of cols in the sprite sheet
  quint32 d_source_cols;

  // The indices of frames that will be displayed
  QList<int> d_displayed_frame_indices;

  // Diplay all frames
  bool d_display_all_frames;

  // The frame loader
  std::unique_ptr<FrameLoader> d_frame_loader;

  // The starting frame index
  quint32 d_starting_frame_index;

  // The current frame index
  quint32 d_current_frame_index;

  // Records if the sprite frames are ready
  bool d_frames_ready;

  // The sprite frames
  QVector<Frame> d_frames;
};

} // end QtD1 namespace

#endif // end MENU_SPRITE_H

//---------------------------------------------------------------------------//
// end MenuSprite.h
//---------------------------------------------------------------------------//
