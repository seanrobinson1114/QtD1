//---------------------------------------------------------------------------//
//!
//! \file   Music.cpp
//! \author Alex Robinson
//! \brief  The music class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// QtD1 Includes
#include "Music.h"
#include "AudioDevice.h"

namespace QtD1{

// Constructor
Music::Music( QObject* parent )
  : QObject( parent ),
    d_source(),
    d_music()
{ /* ... */ }

// Get the music source
QString Music::getSource() const
{
  return d_source;
}

// Set the music source
void Music::setSource( const QString& source )
{
  d_source = source;

  try{
    d_music.reset( new MixMusicWrapper( d_source ) );
  }
  catch( const std::exception& exception )
  {
    std::ostringstream oss;
    oss << "Unable to load music file "
        << d_source.toStdString()
        << "!";

    qFatal( "%s", oss.str().c_str() );
  }
}

// Play the music
Q_INVOKABLE void Music::playMusic()
{
  AudioDevice& audio_device = AudioDevice::getInstance();

  // Check if the audio device is open
  if( audio_device.isOpen() )
  {
    if( audio_device.isMusicPaused() )
      audio_device.resumeMusic();
    else
      audio_device.playMusic( *d_music );
  }
}

// Pause the music
Q_INVOKABLE void Music::pauseMusic()
{
  AudioDevice& audio_device = AudioDevice::getInstance();

  // Check if the audio device is open
  if( audio_device.isOpen() && audio_device.isMusicPlaying() )
    audio_device.pauseMusic();
}

// Stop the music
Q_INVOKABLE void Music::stopMusic()
{
  AudioDevice& audio_device = AudioDevice::getInstance();

  // Check if the audio device is open
  if( audio_device.isOpen() )
    audio_device.haltMusic();
}

QML_REGISTER_TYPE( Music );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Music.cpp
//---------------------------------------------------------------------------//
