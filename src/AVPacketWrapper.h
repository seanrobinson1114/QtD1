//---------------------------------------------------------------------------//
//!
//! \file   AVPacketWrapper.h
//! \author Alex, Sean Robinson
//! \brief  The AVPacket c struct wrapper declaration
//!
//---------------------------------------------------------------------------//

#ifndef AV_PACKET_WRAPPER_H
#define AV_PACKET_WRAPPER_H

// lib avcodec includes
extern "C"{
#include <libavcodec/avcodec.h>
}

namespace QtD1{

//! The AVPacket wrapper class
class AVPacketWrapper
{

public:

  //! Constructor
  AVPacketWrapper();

  //! Copy Constructor
  AVPacketWrapper( const AVPacketWrapper& packet );

  //! Destructor
  ~AVPacketWrapper();

  //! Assignment operator
  AVPacketWrapper& operator=( const AVPacketWrapper& that );

  //! Get the raw packet
  const AVPacket& getRawPacket() const;

  //! Get the raw packet
  AVPacket& getRawPacket();

  //! Get the raw packet pointer
  const AVPacket* getRawPacketPtr() const;

  //! Get the raw packet pointer
  AVPacket* getRawPacketPtr();

private:

  // The raw AVPacket
  AVPacket d_raw_packet;
};

} // end QtD1 namespace

#endif // end AV_PACKET_WRAPPER_H

//---------------------------------------------------------------------------//
// end AVPacketWrapper.h
//---------------------------------------------------------------------------//
