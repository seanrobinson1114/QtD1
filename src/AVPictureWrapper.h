//---------------------------------------------------------------------------//
//!
//! \file   AVPictureWrapper.h
//! \author Alex, Sean Robinson
//! \brief  The AVPicture c struct wrapper declaration
//!
//---------------------------------------------------------------------------//

#ifndef AV_PICTURE_WRAPPER_H
#define AV_PICTURE_WRAPPER_H

// lib avcodec includes
extern "C" {
#include <libavcodec/avcodec.h>
}

namespace QtD1{
  
//! The AVPicture wrapper class
class AVPictureWrapper
{

public:

  //! Constructor
  AVPictureWrapper();

  //! Constructor
  AVPictureWrapper( AVPixelFormat format, int width, int height );

  //! Copy Constructor
  AVPictureWrapper( const AVPictureWrapper& that );

  //! Destructor
  ~AVPictureWrapper();

  //! Assignment operator
  AVPictureWrapper& operator=( const AVPictureWrapper& that );

  //! Get the raw frame data
  const uint8_t** getRawData() const;

  //! Get the raw frame data
  uint8_t** getRawData();

  //! Get the linesize
  const int* getLinesize() const;

  //! Get the linesize
  int* getLinesize();

  //! Get the pixel format
  AVPixelFormat getFormat() const;

  //! Get the width
  int getWidth() const;

  //! Get the height
  int getHeight() const;

  //! Get the raw picture
  const AVPicture& getRawPicture() const;

  //! Get the raw picture
  AVPicture& getRawPicture();

  //! Get the raw picture pointer
  const AVPicture* getRawPicturePtr() const;

  //! Get the raw picture pointer
  AVPicture* getRawPicturePtr();

private:

  // The raw picture
  AVPicture d_raw_picture;

  // The picture format
  AVPixelFormat d_format;

  // The picture width
  int d_width;

  // The picture height
  int d_height;
};

} // end QtD1 namespace

#endif // end AV_PICTURE_WRAPPER_H

//---------------------------------------------------------------------------//
// end AVPictureWrapper.h
//---------------------------------------------------------------------------//
