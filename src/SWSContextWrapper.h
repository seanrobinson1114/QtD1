//---------------------------------------------------------------------------//
//!
//! \file   SWSContextWrapper.h
//! \author Alex, Sean Robinson
//! \brief  The SWSContext c struct wrapper declaration
//!
//---------------------------------------------------------------------------//

#ifndef SWS_CONTEXT_WRAPPER_H
#define SWS_CONTEXT_WRAPPER_H

extern "C"{
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

// Qt Includes
#include <QImage>

namespace QtD1{

//! The SwsContext wrapper class
class SWSContextWrapper
{

public:

  //! Constructor
  SWSContextWrapper( int source_width,
                     int source_height,
                     AVPixelFormat source_format,
                     int dest_width,
                     int dest_height,
                     AVPixelFormat dest_format,
                     int flags );

  //! Destructor
  ~SWSContextWrapper();

  //! Scale a slice and store it in the desired location
  template<typename Source, typename Destination>
  int scale( const Source& source,
             int src_slice_y,
             int src_slice_h,
             Destination& dest );

  //! Scale a slice and store it in the desired location
  template<typename Source, typename Destination>
  int scale( const Source& source,
             Destination& dest );

  //! Scale a slice and store it in the desired QImage
  template<typename Source>
  int scale( const Source& source, QImage& dest );

private:

  // These constructors and the assignment operator must remain private since
  // SwScale does not provide methods form copying sws contexts. 
  SWSContextWrapper();
  SWSContextWrapper( const SWSContextWrapper& );
  SWSContextWrapper& operator=( const SWSContextWrapper& that );
  
  SwsContext* d_raw_sws_ctx;
};

// Scale a slice and store it in the desired location
template<typename Source, typename Destination>
int SWSContextWrapper::scale( const Source& source,
                              int src_slice_y,
                              int src_slice_h,
                              Destination& dest )
{
  return sws_scale( d_raw_sws_ctx,
                    (const uint8_t* const*)source.getRawData(),
                    source.getLinesize(),
                    src_slice_y,
                    src_slice_h,
                    dest.getRawData(),
                    dest.getLinesize() );
}

// Scale a slice and store it in the desired QImage
template<typename Source>
int SWSContextWrapper::scale( const Source& source, QImage& dest )
{
  uchar* dest_data = dest.scanLine(0);
  int dest_linesize = dest.bytesPerLine();
  
  return sws_scale( d_raw_sws_ctx,
                    (const uint8_t* const*)source.getRawData(),
                    source.getLinesize(),
                    0,
                    source.getHeight(),
                    &dest_data,
                    &dest_linesize );
}

// Scale a slice and store it in the desired location
template<typename Source, typename Destination>
inline int SWSContextWrapper::scale( const Source& source,
                                     Destination& dest )
{
  return this->scale( source, 0, source.getHeight(), dest );
}

} // end QtD1 namespace

#endif // end SWS_CONTEXT_WRAPPER_H


//---------------------------------------------------------------------------//
// end SWSContextWrapper.h
//---------------------------------------------------------------------------//
