//---------------------------------------------------------------------------//
//!
//! \file   AVIOContextWrapper.h
//! \author Alex Robinson
//! \brief  The AVIOContext wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef AVIO_CONTEXT_WRAPPER_H
#define AVIO_CONTEXT_WRAPPER_H

// AVCodec Includes
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

// Qt Includes
#include <QString>
#include <QFile>

namespace QtD1{

//! The AVIOContext wrapper class
class AVIOContextWrapper
{

public:

  //! Constructor (set buffer size to packet size)
  AVIOContextWrapper( int buffer_size,
                      const bool writable,
                      const QString& filename );

  //! Destructor
  ~AVIOContextWrapper();

  //! Get the raw AVIOContext pointer
  AVIOContext* getRawContextPtr();

  //! Get the raw AVIOContext pointer
  const AVIOContext* getRawContextPtr() const;

private:

  // Read callback
  static int readCallback( void* opaque, uint8_t* buffer, int buffer_size );

  // Read
  int read( uint8_t* buffer, int buffer_size );

  // Constructors and assignment operator
  AVIOContextWrapper();
  AVIOContextWrapper( const AVIOContextWrapper& that );
  AVIOContextWrapper& operator=( const AVIOContextWrapper& that );

  // The input file
  QFile d_input_file;

  // The raw AVIOContext pointer
  AVIOContext* d_raw_context;
};
  
} // end QtD1 namespace

#endif // end AVIO_CONTEXT_WRAPPER_H

//---------------------------------------------------------------------------//
// end AVIOContextWrapper.h
//---------------------------------------------------------------------------//
