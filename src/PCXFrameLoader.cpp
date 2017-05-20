//---------------------------------------------------------------------------//
//!
//! \file   PCXFrameLoader.cpp
//! \author Alex Robinson
//! \brief  The pcx frame loader class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "PCXFrameLoader.h"

namespace QtD1{

// Constructor
PCXFrameLoader::PCXFrameLoader( QObject* parent )
  : FrameLoader( parent ),
    d_transparent_color( Qt::transparent ),
    d_source_rows( 1 ),
    d_source_cols( 1 ),
    d_source_image(),
    d_frame_width( 0 ),
    d_frame_height( 0 )
{ /* ... */ }

// Get the color that will be made transparent
QColor PCXFrameLoader::getTransparentColor() const
{
  return d_transparent_color;
}

// Set the color that will be made transparent
void PCXFrameLoader::setTransparentColor( const QColor& background_color )
{
  d_transparent_color = background_color;
}

// Get the number of rows in the sprite sheet
int PCXFrameLoader::getNumberOfRows() const
{
  return d_source_rows;
}

// Set the number of rows in the sprite sheet
void PCXFrameLoader::setNumberOfRows( const int num_rows )
{
  if( num_rows <= 0 )
    qFatal( "PCXFrameLoader Error: The number of rows must be >= 1." );
  
  d_source_rows = num_rows;
}

// Get the number of columns in the sprite sheet
int PCXFrameLoader::getNumberOfCols() const
{
  return d_source_cols;
}

// Set the number of columns in the sprite sheet
void PCXFrameLoader::setNumberOfCols( const int num_cols )
{
  if( num_cols <= 0 )
    qFatal( "PCXFrameLoader Error: The number of columns must be >= 1." );
  
  d_source_cols = num_cols;
}

// Get ready for frame loading
int PCXFrameLoader::getReadyForFrameLoading()
{
  if( !this->getSource().contains( ".pcx" ) )
  {
    qFatal( "PCXFrameLoader Error: Image source %s is not a pcx file!",
            this->getSource().toStdString().c_str() );
  }
  
  d_source_image.load( this->getSource() );

  // We need a 32-bit image
  if( d_source_image.format() != QImage::Format_ARGB32 )
    d_source_image = d_source_image.convertToFormat( QImage::Format_ARGB32 );

  // Convert the transparent color to transparent
  if( d_transparent_color != Qt::transparent )
    this->convertTransparentColorToTransparent();

  // Calculate the frame dimensions
  d_frame_width = d_source_image.width()/d_source_cols;
  d_frame_height = d_source_image.height()/d_source_rows;

  return d_source_rows*d_source_cols;
}

// Load the frame of interest
QImage PCXFrameLoader::loadFrame( const int frame_index )
{
  // Frames will be extracted from the top left across
  const int row = frame_index/d_source_cols;
  const int col = frame_index - row*d_source_cols;

  const int x_pos = d_frame_width*col;
  const int y_pos = d_frame_height*row;

  return d_source_image.copy( x_pos, y_pos, d_frame_width, d_frame_height );
}

// Finish frame loading
void PCXFrameLoader::finishFrameLoading()
{
  d_source_image = QImage();
  d_frame_width = 0;
  d_frame_height = 0;
}

// Convert the transparent color in the source image to transparent
void PCXFrameLoader::convertTransparentColorToTransparent()
{
  QRgb color_to_make_transparent = d_transparent_color.rgb();
  QRgb transparent_color = QColor(Qt::transparent).rgba();

  for( int j = 0; j < d_source_image.height(); ++j )
  {
    QRgb* line_pixels = (QRgb*)d_source_image.scanLine( j );

    for( int i = 0; i < d_source_image.width(); ++i )
    {
      if( *line_pixels == color_to_make_transparent )
        *line_pixels = transparent_color;

      ++line_pixels;
    }
  }
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end PCXFrameLoader.cpp
//---------------------------------------------------------------------------//
