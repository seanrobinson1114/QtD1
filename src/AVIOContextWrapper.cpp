//---------------------------------------------------------------------------//
//!
//! \file   AVIOContextWrapper.cpp
//! \author Alex Robinson
//! \brief  The AVIOContext wrapper class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QObject>

// QtD1 Includes
#include "AVIOContextWrapper.h"

namespace QtD1{

// Constructor (set buffer size to packet size)
AVIOContextWrapper::AVIOContextWrapper( int buffer_size,
                                        const bool writable,
                                        const QString& filename )
  : d_input_file( filename ),
    d_raw_context( NULL )
{
  // Try to open the requested file
  bool open_success = false;

  if( writable )
    open_success = d_input_file.open( QIODevice::ReadWrite );
  else
    open_success = d_input_file.open( QIODevice::ReadOnly );
  
  if( !open_success )
  {
    qFatal( "Error: Could not load file %s!",
            filename.toStdString().c_str() );
  }
  
  uint8_t* buffer = (uint8_t*)av_malloc( buffer_size );

  if( buffer == NULL )
    qFatal( "Error: Could not allocate the AVIOContext buffer!" );

  d_raw_context = avio_alloc_context( buffer,
                                      buffer_size,
                                      (writable ? 1 : 0),
                                      this,
                                      AVIOContextWrapper::readCallback,
                                      NULL,
                                      NULL );

  // Make sure the raw context != NULL
  if( d_raw_context == NULL )
    qFatal( "Error: The AVIOContext could not be allocated!" );
}

// Destructor
AVIOContextWrapper::~AVIOContextWrapper()
{
  av_free( d_raw_context->buffer );
  av_free( d_raw_context );
}

// Get the raw AVIOContext pointer
AVIOContext* AVIOContextWrapper::getRawContextPtr()
{
  return d_raw_context;
}

// Get the raw AVIOContext pointer
const AVIOContext* AVIOContextWrapper::getRawContextPtr() const
{
  return d_raw_context;
}

// Read callback
int AVIOContextWrapper::readCallback( void* opaque,
                                      uint8_t* buffer,
                                      int buffer_size )
{
  return ((AVIOContextWrapper*)opaque)->read( buffer, buffer_size );
}

// Read
int AVIOContextWrapper::read( uint8_t* buffer, int buffer_size )
{
  return d_input_file.read( (char*)buffer, buffer_size );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end AVIOContextWrappper.cpp
//---------------------------------------------------------------------------//
