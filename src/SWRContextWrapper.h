//---------------------------------------------------------------------------//
//!
//! \file   SWRContextWrapper.h
//! \author Alex, Sean Robinson
//! \brief  The SWRContext c struct wrapper declaration
//!
//---------------------------------------------------------------------------//

#ifndef SWR_CONTEXT_WRAPPER_H
#define SWR_CONTEXT_WRAPPER_H

extern "C"{
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
}

namespace QtD1{

//! The SwrContext wrapper class
class SWRContextWrapper
{

public:

  //! Constructor
  SWRContextWrapper( int64_t out_ch_layout,
                     AVSampleFormat out_sample_fmt,
                     int out_sample_rate,
                     int64_t in_ch_layout,
                     AVSampleFormat in_sample_fmt,
                     int in_sample_rate );

  //! Destructor
  ~SWRContextWrapper();

  //! Convert the input sample to the output sample
  int convert( uint8_t** out,
               int out_count,
               const uint8_t** in,
               int in_count );

  //! Set the resampling compensation
  void setCompensation( int sample_delta, int compensation_distance );

private:

  // These constructors and the assignment operator must remain private since
  // SwrContext does not provide methods for copying swr contexts.
  SWRContextWrapper();
  SWRContextWrapper( const SWRContextWrapper& that );
  SWRContextWrapper& operator=( const SWRContextWrapper& that );

  SwrContext* d_raw_swr_ctx;
};

} // end QtD1 namespace

#endif // end SWR_CONTEXT_WRAPPER_H

//---------------------------------------------------------------------------//
// end SWRContextWrapper.h
//---------------------------------------------------------------------------//

