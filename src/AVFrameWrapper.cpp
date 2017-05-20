//---------------------------------------------------------------------------//
//!
//! \file   AVFrameWrapper.cpp
//! \author Alex, Sean Robinson
//! \brief  The AVFrame c struct wrapper definition
//!
//---------------------------------------------------------------------------//

// QtD1 includes
#include "AVFrameWrapper.h"

namespace QtD1{

// Constructor
AVFrameWrapper::AVFrameWrapper()
  : d_raw_frame( av_frame_alloc() )
{ 
  // Make sure the allocation was successful
}

// Copy Constructor
AVFrameWrapper::AVFrameWrapper( const AVFrameWrapper& frame )
  : d_raw_frame( av_frame_clone( frame.d_raw_frame ) )
{ /* ... */ }

// Destructor
AVFrameWrapper::~AVFrameWrapper()
{
  av_frame_free( &d_raw_frame );
}

// Assignment operator
AVFrameWrapper& AVFrameWrapper::operator=( const AVFrameWrapper& that )
{
  if( this != &that )
  {
    av_frame_free( &d_raw_frame );

    d_raw_frame = av_frame_clone( that.d_raw_frame );
  }

  return *this;
}

// Get the raw frame data
const uint8_t** AVFrameWrapper::getRawData() const
{
  return (const uint8_t**)d_raw_frame->data;
}

// Get the raw frame data
uint8_t** AVFrameWrapper::getRawData()
{
  return d_raw_frame->data;
}

// Get the linesize
const int* AVFrameWrapper::getLinesize() const
{
  return d_raw_frame->linesize;
}

// Get the linesize
int* AVFrameWrapper::getLinesize()
{
  return d_raw_frame->linesize;
}

// Get the pixel format
int AVFrameWrapper::getFormat() const
{
  return d_raw_frame->format;
}

// Get the width
int AVFrameWrapper::getWidth() const
{
  return d_raw_frame->width;
}

// Get the height
int AVFrameWrapper::getHeight() const
{
  return d_raw_frame->height;
}

// Get the raw frame pointer
const AVFrame* AVFrameWrapper::getRawFramePtr() const
{
  return d_raw_frame;
}

// Get the raw frame pointer
AVFrame* AVFrameWrapper::getRawFramePtr()
{
  return d_raw_frame;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end AVFrameWrapper.cpp
//---------------------------------------------------------------------------//
