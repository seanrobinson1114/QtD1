//---------------------------------------------------------------------------//
//!
//! \file   AVPictureWrapper.cpp
//! \author Alex, Sean Robinson
//! \brief  The AVPicture c struct wrapper definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QObject>

// QtD1 includes
#include "AVPictureWrapper.h"

namespace QtD1{

// Constructor
AVPictureWrapper::AVPictureWrapper()
  : d_raw_picture(),
    d_format( AV_PIX_FMT_NONE ),
    d_width( 0 ),
    d_height( 0 )
{ /* ... */ }

// Constructor
AVPictureWrapper::AVPictureWrapper( AVPixelFormat format,
                                    int width,
                                    int height )
  : d_raw_picture(),
    d_format( format ),
    d_width( width ),
    d_height( height )
{
  // Make sure the format is valid (not AV_PIX_FMT_NONE)
  int return_value =
    avpicture_alloc( &d_raw_picture, format, width, height );

  // Make sure the return value is 0
  if( return_value != 0 )
    qFatal( "Error: could not allocate AVPicture!" );
}

// Copy Constructor
AVPictureWrapper::AVPictureWrapper( const AVPictureWrapper& that )
  : d_raw_picture(),
    d_format( that.d_format ),
    d_width( that.d_width ),
    d_height( that.d_height )
{
  av_picture_copy( &d_raw_picture,
                   &that.d_raw_picture,
                   that.d_format,
                   that.d_width,
                   that.d_height );
}

// Destructor
AVPictureWrapper::~AVPictureWrapper()
{
  avpicture_free( &d_raw_picture );
}

// Assignment operator
AVPictureWrapper& AVPictureWrapper::operator=( const AVPictureWrapper& that )
{
  if( this != &that )
  {
    // Make sure the current picture data is freed to avoid mem. leaks
    avpicture_free( &d_raw_picture );

    av_picture_copy( &d_raw_picture,
                     &that.d_raw_picture,
                     that.d_format,
                     that.d_width,
                     that.d_height );
  }

  return *this;
}

// Get the raw frame data
const uint8_t** AVPictureWrapper::getRawData() const
{
  return (const uint8_t**)d_raw_picture.data;
}

// Get the raw frame data
uint8_t** AVPictureWrapper::getRawData()
{
  return d_raw_picture.data;
}

// Get the linesize
const int* AVPictureWrapper::getLinesize() const
{
  return d_raw_picture.linesize;
}

// Get the linesize
int* AVPictureWrapper::getLinesize()
{
  return d_raw_picture.linesize;
}

// Get the raw picture
const AVPicture& AVPictureWrapper::getRawPicture() const
{
  return d_raw_picture;
}

// Get the raw picture
AVPicture& AVPictureWrapper::getRawPicture()
{
  return d_raw_picture;
}

// Get the raw picture pointer
const AVPicture* AVPictureWrapper::getRawPicturePtr() const
{
  return &d_raw_picture;
}

// Get the raw picture pointer
AVPicture* AVPictureWrapper::getRawPicturePtr()
{
  return &d_raw_picture;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end AVPictureWrapper.cpp
//---------------------------------------------------------------------------//
