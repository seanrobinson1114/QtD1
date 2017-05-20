//---------------------------------------------------------------------------//
//!
//! \file   CelImagePixelSetter.h
//! \author Alex Robinson
//! \brief  The cel image pixel setter class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CEL_IMAGE_PIXEL_SETTER_H
#define CEL_IMAGE_PIXEL_SETTER_H

// Qt Includes
#include <QImage>

// QtD1 Includes
#include "CelPalette.h"

namespace QtD1{

//! The cel image pixel setter class
class CelImagePixelSetter
{

public:

  //! Constructor
  CelImagePixelSetter( const int width,
                       const int height,
                       const CelPalette& palette );

  //! Destructor
  ~CelImagePixelSetter()
  { /* ... */ }

  //! Get the current pixel index
  int getCurrentPixelIndex() const;

  //! Get the current image position
  QPoint getCurrentImagePosition() const;

  //! Check if all of the pixels have been set
  bool allPixelsSet() const;

  //! Get the number of pixels that have been set
  int getNumberOfSetPixels() const;

  //! Get the cel image
  QImage getImage() const;

  //! Go to the next frame pixel
  void gotoNextPixel();

  //! Get the current pixel
  uchar* pixel();

  //! Get the current pixel
  const uchar* pixel() const;

private:

  // The cel image
  QImage d_image;

  // The current pixel data
  uchar* d_pixel;

  // The current pixel location
  int d_x_pos;
  int d_y_pos;

  // The number of pixels that are unset
  int d_number_of_unset_pixels;
};
  
} // end QtD1 namespace

#endif // end CEL_IMAGE_PIXEL_SETTER_H

//---------------------------------------------------------------------------//
// end CelImagePixelSetter.h
//---------------------------------------------------------------------------//
