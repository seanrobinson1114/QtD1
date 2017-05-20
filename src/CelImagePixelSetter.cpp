//---------------------------------------------------------------------------//
//!
//! \file   CelImagePixelSetter.cpp
//! \author Alex Robinson
//! \brief  The cel image pixel settering class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include "CelImagePixelSetter.h"

namespace QtD1{

// Constructor
CelImagePixelSetter::CelImagePixelSetter( const int width,
                                          const int height,
                                          const CelPalette& palette )
  : d_image( width, height, QImage::Format_Indexed8 ),
    d_pixel( d_image.scanLine( height - 1 ) ),
    d_x_pos( 0 ),
    d_y_pos( height - 1 ),
    d_number_of_unset_pixels( width*height )
{ 
  // Set the image palette
  d_image.setColorTable( palette.toColorTable() );
}

// Get the current pixel index
/*! \details This is with respect to the normal pixel order.
 */
int CelImagePixelSetter::getCurrentPixelIndex() const
{
  return d_image.width()*d_y_pos + d_x_pos;
}

// Get the current image position
QPoint CelImagePixelSetter::getCurrentImagePosition() const
{
  return QPoint( d_x_pos, d_y_pos );
}

// Check if all of the pixels have been set
bool CelImagePixelSetter::allPixelsSet() const
{
  return d_number_of_unset_pixels == 0;
}

// Get the number of pixels that have been set
int CelImagePixelSetter::getNumberOfSetPixels() const
{
  return d_image.width()*d_image.height() - d_number_of_unset_pixels;
}

// Get the cel image
QImage CelImagePixelSetter::getImage() const
{
  return d_image;
}

// Increment the pixel index
void CelImagePixelSetter::gotoNextPixel()
{
  // Get the scanline above the current one
  if( d_x_pos == d_image.width() - 1 )
  {
    if( d_y_pos >= 0 )
    {      
      --d_y_pos;
      d_x_pos = 0;

      --d_number_of_unset_pixels;

      if( d_y_pos >= 0 )
        d_pixel = d_image.scanLine( d_y_pos );
    }
    else
    {
      qWarning( "CelImagePixelSetter Warning: Cannot increment because all "
                "pixels have been visited!" );
    }
  }
  // Move one pixel to the right
  else
  {
    ++d_x_pos;

    --d_number_of_unset_pixels;
    
    ++d_pixel;
  }
}

// Get the current pixel
uchar* CelImagePixelSetter::pixel()
{
  return d_pixel;
}

// Get the current pixel
const uchar* CelImagePixelSetter::pixel() const
{
  return d_pixel;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CelImagePixelSetter.cpp
//---------------------------------------------------------------------------//
