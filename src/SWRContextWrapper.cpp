//---------------------------------------------------------------------------//
//!
//! \file   SWRContextWrapper.cpp
//! \author Alex, Sean Robinson
//! \brief  The SWRContext c struct wrapper definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QObject>

// QtD1 includes
#include "SWRContextWrapper.h"

namespace QtD1{

// Constructor
SWRContextWrapper::SWRContextWrapper( int64_t out_ch_layout,
                                      AVSampleFormat out_sample_fmt,
                                      int out_sample_rate,
                                      int64_t in_ch_layout,
                                      AVSampleFormat in_sample_fmt,
                                      int in_sample_rate )
  : d_raw_swr_ctx( swr_alloc_set_opts( NULL,
                                       out_ch_layout,
                                       out_sample_fmt,
                                       out_sample_rate,
                                       in_ch_layout,
                                       in_sample_fmt,
                                       in_sample_rate,
                                       0,
                                       NULL ) )
{
  if( d_raw_swr_ctx == NULL )
    qFatal( "Error: the SwrContext is null!" );

  swr_init( d_raw_swr_ctx );
}

// Destructor
SWRContextWrapper::~SWRContextWrapper()
{
  swr_free( &d_raw_swr_ctx );
}

// Convert the input sample to the output sample
int SWRContextWrapper::convert( uint8_t** out,
                                int out_count,
                                const uint8_t** in,
                                int in_count )
{
  int return_value = swr_convert( d_raw_swr_ctx,
                                  out,
                                  out_count,
                                  in,
                                  in_count );

  // Make sure the return value is >= 0
  if( return_value < 0 )
    qFatal( "Error: could not convert input sample to output sample!");

  return return_value;
}

// Set the resampling compensation
void SWRContextWrapper::setCompensation( int sample_delta,
                                         int compensation_distance )
{
  int return_value = swr_set_compensation( d_raw_swr_ctx,
                                           sample_delta,
                                           compensation_distance );

  // Make sure the return value is >= 0
  if( return_value < 0 )
    qFatal( "Error: could not set the resampling compensation!" );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SWRContextWrapper.cpp
//---------------------------------------------------------------------------//
