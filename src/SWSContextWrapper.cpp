//---------------------------------------------------------------------------//
//!
//! \file   SWSContextWrapper.cpp
//! \author Alex, Sean Robinson
//! \brief  The SWSContext c struct wrapper definition
//!
//---------------------------------------------------------------------------//

// QtD1 includes
#include "SWSContextWrapper.h"

namespace QtD1{

// Constructor
SWSContextWrapper::SWSContextWrapper( int source_width,
                                      int source_height,
                                      AVPixelFormat source_format,
                                      int dest_width,
                                      int dest_height,
                                      AVPixelFormat dest_format,
                                      int flags )
  : d_raw_sws_ctx( sws_getContext( source_width,
                                   source_height,
                                   source_format,
                                   dest_width,
                                   dest_height,
                                   dest_format,
                                   flags,
                                   NULL,
                                   NULL,
                                   NULL ) )
{ /* ... */ }

// Destructor
SWSContextWrapper::~SWSContextWrapper()
{
  sws_freeContext( d_raw_sws_ctx );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SWSContextWrapper.cpp
//---------------------------------------------------------------------------//
