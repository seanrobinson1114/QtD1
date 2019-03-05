//---------------------------------------------------------------------------//
//!
//! \file   MenuSprite.cpp
//! \author Alex Robinson
//! \brief  The menu sprite class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QPainter>
#include <QEventLoop>

// QtD1 Includes
#include "MenuSprite.h"
#include "CelFrameLoader.h"
#include "PCXFrameLoader.h"

namespace QtD1{

// Constructor
MenuSprite::MenuSprite( QDeclarativeItem* parent )
  : QDeclarativeItem( parent ),
    d_source(),
    d_display_policy( Viewport::StretchToFit ),
    d_background_color( Qt::transparent ),
    d_mixing_color( Qt::transparent ),
    d_source_rows( 1 ),
    d_source_cols( 1 ),
    d_displayed_frame_indices(),
    d_display_all_frames( true ),
    d_frame_loader(),
    d_starting_frame_index( 0 ),
    d_current_frame_index( 0 ),
    d_frames_ready( false ),
    d_frames()
{
  this->notReady();
}

// Get the sprite image source
QString MenuSprite::getSource() const
{
  return d_source;
}

// Set the sprite image source
void MenuSprite::setSource( const QString& source )
{
  d_source = source;

  this->dumpFrames();
}

// Get the display policy
Viewport::DisplayPolicy MenuSprite::getDisplayPolicy() const
{
  return d_display_policy;
}

// Set the display policy
void MenuSprite::setDisplayPolicy( const Viewport::DisplayPolicy policy )
{
  d_display_policy = policy;
}

// Get the sprite background color
QColor MenuSprite::getBackgroundColor() const
{
  return d_background_color;
}

// Set the background color (will be transparent)
void MenuSprite::setBackgroundColor( const QColor& background_color )
{
  d_background_color = background_color;
}

// Get the mixing color
QColor MenuSprite::getMixingColor() const
{
  return d_mixing_color;
}

// Set the mixing color
void MenuSprite::setMixingColor( const QColor& mixing_color )
{
  d_mixing_color = mixing_color;
}

// Get the number of rows in the sprite sheet
quint32 MenuSprite::getNumberOfRows() const
{
  return d_source_rows;
}

// Set the number of rows in the sprite sheet
void MenuSprite::setNumberOfRows( const quint32 num_rows )
{
  d_source_rows = num_rows;
}

// Get the number of columns in the sprite sheet
quint32 MenuSprite::getNumberOfCols() const
{
  return d_source_cols;
}

// Set the number of columns in the sprite sheet
void MenuSprite::setNumberOfCols( const quint32 num_cols )
{
  d_source_cols = num_cols;
}

// Get the indices of frames that will be displayed
QVariant MenuSprite::getDisplayedFrameIndices() const
{
  QList<QVariant> opaque_frame_indices;

  for( int i = 0; i < d_displayed_frame_indices.size(); ++i )
    opaque_frame_indices.push_back( QVariant( d_displayed_frame_indices[i] ) );

  return QVariant( opaque_frame_indices );
}

// Set the indices of frames that will be displayed
void MenuSprite::setDisplayedFrameIndices( const QVariant& frame_indices )
{
  d_displayed_frame_indices.clear();

  if( frame_indices.toString().contains( "all", Qt::CaseInsensitive ) )
  {
    d_display_all_frames = true;

    d_displayed_frame_indices.clear();
  }
  else
  {
    d_display_all_frames = false;

    for( QVariant item : frame_indices.toList() )
    {
      bool valid = false;

      int index = item.toInt( &valid );

      if( valid )
        d_displayed_frame_indices.push_back( index );
      else
      {
        qWarning( "MenuSprite Warning: invalid frame index type "
                  "encountered!" );
      }
    }
  }
}

// Get the starting frame index
quint32 MenuSprite::getStartingFrameIndex() const
{
  return d_starting_frame_index;
}

// Set the starting frame index
void MenuSprite::setStartingFrameIndex( const quint32 start_frame_index )
{
  d_starting_frame_index = start_frame_index;

  this->setCurrentFrameIndex( start_frame_index );
}

// Get the current frame index (measured from starting frame index)
quint32 MenuSprite::getCurrentFrameIndex() const
{
  return d_current_frame_index;
}

// Set the current frame index
void MenuSprite::setCurrentFrameIndex( const quint32 frame_index )
{
  if( frame_index != d_current_frame_index )
  {
    d_current_frame_index = frame_index;

    this->update();

    emit frameChanged( frame_index );
  }
}

// Get the current frame width
int MenuSprite::getCurrentFrameWidth() const
{
  if( d_frames_ready )
  {
    quint32 current_index = this->calculateBoundedFrameIndex();

    return d_frames[current_index].pixmap.width();
  }
  else
    return 0;
}

// Get the current frame height
int MenuSprite::getCurrentFrameHeight() const
{
  if( d_frames_ready )
  {
    quint32 current_index = this->calculateBoundedFrameIndex();

    return d_frames[current_index].pixmap.height();
  }
  else
    return 0;
}

// Get the number of frames
quint32 MenuSprite::getNumberOfFrames() const
{
  return d_frames.size();
}

// Load the sprite frames
void MenuSprite::load()
{
  this->dumpFrames();
  this->initializeFrameLoader();
  this->connectFrameLoaderSignalsToMenuSpriteSlots();

  if( d_display_all_frames )
    d_frame_loader->loadFrames();
  else
    d_frame_loader->loadFrames( d_displayed_frame_indices );
}

// Load the sprite frames synchronously
void MenuSprite::loadSync()
{
  this->dumpFrames();
  this->initializeFrameLoader();
  this->connectFrameLoaderSignalsToMenuSpriteSlots();

  if( d_display_all_frames )
    d_frame_loader->loadFramesSync();
  else
    d_frame_loader->loadFramesSync( d_displayed_frame_indices );
}

// Initialize the frame loader
void MenuSprite::initializeFrameLoader()
{
  if( d_source.contains( ".pcx" ) )
  {
    PCXFrameLoader* tmp_frame_loader = new PCXFrameLoader;
    tmp_frame_loader->setSource( d_source );
    tmp_frame_loader->setTransparentColor( d_background_color );
    tmp_frame_loader->setNumberOfRows( d_source_rows );
    tmp_frame_loader->setNumberOfCols( d_source_cols );

    d_frame_loader.reset( tmp_frame_loader );
  }
  else if( d_source.contains( ".cel" ) ||
           d_source.contains( ".cl2" ) )
  {
    d_frame_loader.reset( new CelFrameLoader );

    d_frame_loader->setSource( d_source );

    if( d_source_rows != 1 || d_source_cols != 1 )
    {
      qWarning( "MenuSprite Warning: source rows and cols are ignored with "
                "cel type files!" );
    }

    if( d_background_color != Qt::transparent )
    {
      qWarning( "MenuSprite Warning: the background color is ignored with "
                "cel type files!" );
    }
  }
  else
  {
    qFatal( "MenuSprite Error: Source file %s is not supported!",
            d_source.toStdString().c_str() );
  }
}

// Connect the frame loader signals to menu sprite slots
void MenuSprite::connectFrameLoaderSignalsToMenuSpriteSlots()
{
  QObject::connect( d_frame_loader.get(), SIGNAL(frameLoaded(const int, QImage)),
                    this, SLOT(handleFrameLoaded(const int, QImage)) );
  QObject::connect( d_frame_loader.get(), SIGNAL(sourceLoaded(QString)),
                    this, SLOT(handleLoadingFinished()) );
}

// Handle frame loaded
void MenuSprite::handleFrameLoaded( const int, QImage frame )
{
  // Check if color mixing needs to be done
  if( d_mixing_color.alpha() > 0 )
    this->mixFrameColors( frame );
  
  Frame new_frame;
  new_frame.pixmap.convertFromImage( frame );

  Viewport::calculateViewports( d_display_policy,
                                this->boundingRect(),
                                new_frame.pixmap,
                                new_frame.source_viewport,
                                new_frame.target_viewport );

  d_frames.push_back( new_frame );
}

// Mix frame colors
void MenuSprite::mixFrameColors( QImage& frame ) const
{
  // We need a 32-bit image
  if( frame.format() != QImage::Format_ARGB32 )
    frame = frame.convertToFormat( QImage::Format_ARGB32 );

  QRgb transparent_color = QColor(Qt::transparent).rgba();

  for( int j = 0; j < frame.height(); ++j )
  {
    QRgb* line_pixels = (QRgb*)frame.scanLine( j );

    for( int i = 0; i < frame.width(); ++i )
    {
      // Don't mix transparent colors
      if( *line_pixels != transparent_color )
      {
        QColor pixel_color = QColor::fromRgba( *line_pixels );

        int red, green, blue, alpha;
        
        red = d_mixing_color.red()*(pixel_color.red()/255.0);
        green = d_mixing_color.green()*(pixel_color.green()/255.0);
        blue = d_mixing_color.blue()*(pixel_color.blue()/255.0);
        alpha = d_mixing_color.alpha()*(pixel_color.alpha()/255.0);
        
        pixel_color.setRgb( red, green, blue, alpha );

        // Set the new color
        *line_pixels = pixel_color.rgba();
      }

      ++line_pixels;
    }
  }
}

// Handle source loaded
void MenuSprite::handleLoadingFinished()
{
  // Free the frame loader
  d_frame_loader.reset();

  this->ready();

  this->update();

  emit sourceLoaded( this->getSource() );
}

// Wait for load to finish
void MenuSprite::waitForLoadToFinish()
{
  if( d_frame_loader )
  {
    QEventLoop wait_loop;
    QObject::connect( d_frame_loader.get(), SIGNAL(sourceLoaded(QString)),
                      &wait_loop, SLOT(quit()) );
    wait_loop.exec();
  }
}

// Dump the frames
void MenuSprite::dumpFrames()
{
  d_frames.clear();

  this->notReady();
}

// The frames are ready
void MenuSprite::ready()
{
  // There are now frames to draw
  this->setFlag( QGraphicsItem::ItemHasNoContents, false );

  d_frames_ready = true;
}

// The frames are not ready
void MenuSprite::notReady()
{
  // There is nothing to draw yet
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );

  d_frames_ready = false;
}

// Calculate the frame index within the range [0,d_frames.size())
quint32 MenuSprite::calculateBoundedFrameIndex() const
{
  return d_current_frame_index%d_frames.size();
}

// Get the frames
void MenuSprite::getFrames( QVector<QPixmap>& frames ) const
{
  if( d_frames_ready )
  {
    frames.resize( d_frames.size() );

    for( int i = 0; i < d_frames.size(); ++i )
      frames[i] = d_frames[i].pixmap;
  }
  else
  {
    qWarning( "MenuSprite Warning: There are no frames to return!" );
  }
}

// Get the frame
QPixmap MenuSprite::getFrame( const int index ) const
{
  if( d_frames_ready )
  {
    if( index >= 0 && index < d_frames.size() )
      return d_frames[index].pixmap;
    else
    {
      qWarning( "MenuSprite Warning: There is no frame for index %i", index );
      return QPixmap();
    }
  }
  else
  {
    qWarning( "MenuSprite Warning: There are no frames to return" );
    return QPixmap();
  }
}

// Paint the sprite banner
void MenuSprite::paint( QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget* )
{
  // Get the current sprite frame index
  quint32 current_index = this->calculateBoundedFrameIndex();

  const Frame& current_frame = d_frames[current_index];

  painter->drawPixmap( current_frame.target_viewport,
                       current_frame.pixmap,
                       current_frame.source_viewport );
}

QML_REGISTER_TYPE( MenuSprite );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MenuSprite.cpp
//---------------------------------------------------------------------------//
