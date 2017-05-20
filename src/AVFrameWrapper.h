//---------------------------------------------------------------------------//
//!
//! \file   AVFrameWrapper.h
//! \author Alex, Sean Robinson
//! \brief  The AVFrame c struct wrapper declaration
//!
//---------------------------------------------------------------------------//

#ifndef AV_FRAME_WRAPPER_H
#define AV_FRAME_WRAPPER_H

// std lib includes
#include <stdlib.h>

// lib avcodec includes
extern "C" {
#include <libavcodec/avcodec.h>
}

namespace QtD1{

//! The AVFrame wrapper class
class AVFrameWrapper
{

public:

  //! Constructor
  AVFrameWrapper();

  //! Copy Constructor
  AVFrameWrapper( const AVFrameWrapper& frame );

  //! Destructor
  ~AVFrameWrapper();

  //! Assignment operator
  AVFrameWrapper& operator=( const AVFrameWrapper& that );

  //! Get the raw frame data
  const uint8_t** getRawData() const;

  //! Get the raw frame data
  uint8_t** getRawData();

  //! Get the linesize
  const int* getLinesize() const;

  //! Get the linesize
  int* getLinesize();

  //! Get the pixel format
  int getFormat() const;

  //! Get the width
  int getWidth() const;

  //! Get the height
  int getHeight() const;

  //! Get the raw frame pointer
  const AVFrame* getRawFramePtr() const;

  //! Get the raw frame pointer
  AVFrame* getRawFramePtr();

private:

  AVFrame* d_raw_frame;
};

} // end QtD1 namespace

#endif // end AV_FRAME_WRAPPER_H

//---------------------------------------------------------------------------//
// end AVFrameWrapper.h
//---------------------------------------------------------------------------//
