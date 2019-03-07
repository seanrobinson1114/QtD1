//---------------------------------------------------------------------------//
//!
//! \file   MixChunkWrapper.cpp
//! \author Alex Robinson
//! \brief  Mix_Chunk wrapper class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QFile>

// QtD1 Includes
#include "MixChunkWrapper.h"
#include "AudioDevice.h"

namespace QtD1{

// Constructor (from file)
MixChunkWrapper::MixChunkWrapper( const QString& filename )
  : d_raw_mix_chunk( NULL ),
    d_raw_chunk_data()
{
  QFile file( filename );
  
  this->loadFromDevice( file );
  this->calculateDuration();
}

// Constructor (from device)
MixChunkWrapper::MixChunkWrapper( QIODevice& device )
  : d_raw_mix_chunk( NULL ),
    d_raw_chunk_data()
{
  this->loadFromDevice( device );
  this->calculateDuration();
}

// Constructor (from buffer)
/*! \details The buffer must be cached since this is apparently not being
 * done in the Mix_chunk object. 
 */
MixChunkWrapper::MixChunkWrapper( const QByteArray& data )
  : d_raw_mix_chunk( NULL ),
    d_raw_chunk_data( data )
{
  SDL_RWops* sdl_stream =
    SDL_RWFromConstMem( d_raw_chunk_data.data(), data.size() );

  d_raw_mix_chunk = Mix_LoadWAV_RW( sdl_stream, true );

  if( d_raw_mix_chunk == NULL )
    qFatal( "Error: Could not load the sound from memory!" );

  this->calculateDuration();
}

// Destructor
MixChunkWrapper::~MixChunkWrapper()
{
  Mix_FreeChunk( d_raw_mix_chunk );

  d_raw_mix_chunk = NULL;
}

// Load from the desired device
void MixChunkWrapper::loadFromDevice( QIODevice& device )
{
  // Make sure that the defice is open
  device.open( QIODevice::ReadOnly );
  
  d_raw_chunk_data.resize( device.size() );

  // Read the file data
  device.read( d_raw_chunk_data.data(), d_raw_chunk_data.size() );

  // Close the device
  device.close();

  // Create the mix chunk
  SDL_RWops* sdl_stream =
    SDL_RWFromConstMem( d_raw_chunk_data.data(), d_raw_chunk_data.size() );

  d_raw_mix_chunk = Mix_LoadWAV_RW( sdl_stream, true );
  
  // Make sure the mix chunk is valid
  if( d_raw_mix_chunk == NULL )
    qFatal( "Error: Could not load the sound from file!" );
}

// Calculate duration
void MixChunkWrapper::calculateDuration()
{
  AudioDevice& audio_device = AudioDevice::getInstance();
  
  if( !audio_device.isOpen() )
    qFatal( "Error: The audio device must be open before loading sounds!" );

  // Chunks are converted to audio device format...
  // bytes / samplesize == sample points
  Uint32 points = d_raw_mix_chunk->alen/((audio_device.getFormat() & 0xFF)/8);

  // sample points / channels == sample frames
  Uint32 frames = points/audio_device.getNumberOfChannels();

  // (sample frames) / frequency == play length in s */
  d_duration = (double)frames/audio_device.getFrequency();
}

// Get the raw chunk data
Uint8* MixChunkWrapper::getRawData()
{
  return d_raw_mix_chunk->abuf;
}

// Get the raw chunk data
const Uint8* MixChunkWrapper::getRawData() const
{
  return d_raw_mix_chunk->abuf;
}

// Get the size of the chunk (used with raw data)
Uint32 MixChunkWrapper::getSize() const
{
  return d_raw_mix_chunk->alen;
}

// Get the volume of the chunk
Uint8 MixChunkWrapper::getVolume() const
{
  return d_raw_mix_chunk->volume;
}

// Set the volume of the chunk
void MixChunkWrapper::setVolume( int volume )
{
  Mix_VolumeChunk( d_raw_mix_chunk, volume );
}

// Get the duration of the chunk (in seconds)
double MixChunkWrapper::getDuration() const
{
  return d_duration;
}

// Get the raw chunk pointer
Mix_Chunk* MixChunkWrapper::getRawMixChunkPtr()
{
  return d_raw_mix_chunk;
}

// Get the raw chunk pointer
const Mix_Chunk* MixChunkWrapper::getRawMixChunkPtr() const
{
  return d_raw_mix_chunk;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MixChunkWrapper.cpp
//---------------------------------------------------------------------------//
