//---------------------------------------------------------------------------//
//!
//! \file   Sound.cpp
//! \author Sean Robinson
//! \brief  The sound class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// QtD1 Includes
#include "Sound.h"
#include "AudioDevice.h"

namespace QtD1{

// Constructor
Sound::Sound( QObject* parent )
  : QObject( parent ),
    d_source(),
    d_chunk()
{ /* ... */ }

// Destructor
Sound::~Sound()
{ /* ... */ }

// Get the sound source
QString Sound::getSource() const
{
  return d_source;
}

// Set the sound source
void Sound::setSource( const QString& source )
{
  d_source = source;

  try{
    d_chunk.reset( new MixChunkWrapper( d_source ) );
  }
  catch( const std::exception& exception )
  {
    std::ostringstream oss;
    oss << "Unable to load sound file "
        << d_source.toStdString()
        << "!";

    qFatal( "%s", oss.str().c_str() );
  }
}

// Play the sound
Q_INVOKABLE void Sound::playSound()
{
  AudioDevice& audio_device = AudioDevice::getInstance();

  // Check if the audio device is open
  if( audio_device.isOpen() )
    audio_device.playChunk( *d_chunk );
}

QML_REGISTER_TYPE( Sound );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Sound.cpp
//---------------------------------------------------------------------------//
