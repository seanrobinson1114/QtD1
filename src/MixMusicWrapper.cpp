//---------------------------------------------------------------------------//
//!
//! \file   MixMusicWrapper.cpp
//! \author Alex Robinson
//! \brief  Mix_Music wrapper class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QFile>

// QtD1 Includes
#include "MixMusicWrapper.h"

namespace QtD1{

// Constructor (from file)
MixMusicWrapper::MixMusicWrapper( const QString& filename )
  : d_raw_mix_music( NULL ),
    d_raw_music_data()
{
  QFile file( filename );
  this->loadFromDevice( file );
}

// Constructor (from device)
MixMusicWrapper::MixMusicWrapper( QIODevice& device )
  : d_raw_mix_music( NULL ),
    d_raw_music_data()
{
  this->loadFromDevice( device );
}

// Constructor (from buffer)
/*! \details The buffer must be cached since this is apparently not being
 * done in the Mix_music object. 
 */
MixMusicWrapper::MixMusicWrapper( const QByteArray& data )
  : d_raw_mix_music( NULL ),
    d_raw_music_data( data )
{
  SDL_RWops* sdl_stream =
    SDL_RWFromConstMem( d_raw_music_data.data(), data.size() );

  d_raw_mix_music = Mix_LoadMUS_RW( sdl_stream, true );

  if( d_raw_mix_music == NULL )
    qFatal( "Error: Could not load the music file from memory!" );
}

// Destructor
MixMusicWrapper::~MixMusicWrapper()
{
  Mix_FreeMusic( d_raw_mix_music );

  d_raw_mix_music = NULL;
}

// Load from the device
void MixMusicWrapper::loadFromDevice( QIODevice& device)
{
  // Make sure that the device is open
  device.open( QIODevice::ReadOnly );

  // Read in the file data
  d_raw_music_data.resize( device.size() );

  // Read the file data
  device.read( d_raw_music_data.data(), d_raw_music_data.size() );

  // Close the device
  device.close();

  SDL_RWops* sdl_stream =
    SDL_RWFromConstMem( d_raw_music_data.data(), d_raw_music_data.size() );

  d_raw_mix_music = Mix_LoadMUS_RW( sdl_stream, true );
  
  // Make sure the raw mix music pointer != NULL
  if( d_raw_mix_music == NULL )
    qFatal( "Error: Could not load the music file!" );
}

// Get the raw music pointer
Mix_Music* MixMusicWrapper::getRawMusicPtr()
{
  return d_raw_mix_music;
}

// Get the raw music pointer
const Mix_Music* MixMusicWrapper::getRawMusicPtr() const
{
  return d_raw_mix_music;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MixMusicWrapper.cpp
//---------------------------------------------------------------------------//
