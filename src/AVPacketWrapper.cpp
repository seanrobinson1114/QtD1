//---------------------------------------------------------------------------//
//!
//! \file   AVPacketWrapper.cpp
//! \author Alex, Sean Robinson
//! \brief  The AVPacket c struct wrapper definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QObject>

// QtD1 includes
#include "AVPacketWrapper.h"

namespace QtD1{

// Constructor
AVPacketWrapper::AVPacketWrapper()
  : d_raw_packet()
{
  av_init_packet( &d_raw_packet );
}

// Copy Constructor
AVPacketWrapper::AVPacketWrapper( const AVPacketWrapper& packet )
  : d_raw_packet()
{
  // Free the old packet
  av_free_packet( &d_raw_packet );
    
  int return_value = av_copy_packet( &d_raw_packet, &packet.d_raw_packet );
  
  // Make sure the return value is 0
  if( return_value != 0 )
    qFatal( "Error: could not allocate AVPacket!" );
}

// Destructor
AVPacketWrapper::~AVPacketWrapper()
{
  av_free_packet( &d_raw_packet );
}

// Assignment operator
AVPacketWrapper& AVPacketWrapper::operator=( const AVPacketWrapper& that )
{
  if( this != &that )
  {
    // Free the old packet
    av_free_packet( &d_raw_packet );

    // Make sure the return value is 0
    av_copy_packet( &d_raw_packet, &that.d_raw_packet );
  }
  
  return *this;
}

// Get the raw packet 
const AVPacket& AVPacketWrapper::getRawPacket() const
{
  return d_raw_packet;
}

// Get the raw packet
AVPacket& AVPacketWrapper::getRawPacket()
{
  return d_raw_packet;
}

// Get the raw packet pointer
const AVPacket* AVPacketWrapper::getRawPacketPtr() const
{
  return &d_raw_packet;
}

// Get the raw packet pointer
AVPacket* AVPacketWrapper::getRawPacketPtr()
{
  return &d_raw_packet;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end AVPacketWrapper.cpp
//---------------------------------------------------------------------------//
