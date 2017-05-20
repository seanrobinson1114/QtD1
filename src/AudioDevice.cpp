//---------------------------------------------------------------------------//
//!
//! \file   AudioDevice.cpp
//! \author Alex, Sean Robinson
//! \brief  The sdl_mixer api wrapper definition
//!
//---------------------------------------------------------------------------//

// QtD1 includes
#include "AudioDevice.h"

namespace QtD1{

// Initialize static member data
std::unique_ptr<AudioDevice> AudioDevice::s_instance;
const int AudioDevice::s_first_free_unreserved_channel = -1;
const int AudioDevice::s_infinite_looping = -1;

// Get the singleton instance
AudioDevice& AudioDevice::getInstance()
{
  if( !s_instance )
    s_instance.reset( new AudioDevice );

  return *s_instance;
}

// Get the first free unreserved channel
int AudioDevice::getFirstFreeUnreservedChannel()
{
  return s_first_free_unreserved_channel;
}

// Set infinite looping
int AudioDevice::infiniteLooping()
{
  return s_infinite_looping;
}

// Constructor
AudioDevice::AudioDevice()
  : d_device_open( false ),
    d_frequency( 0 ),
    d_format( AUDIO_S16SYS ),
    d_number_of_audio_channels( 0 ),
    d_chunksize( 0 ),
    d_number_of_mixer_channels( 0 )
{ /* ... */ }

// Destructor
AudioDevice::~AudioDevice()
{
  if( d_device_open )
  {
    this->close();
  }
}

// Check if the device is open
bool AudioDevice::isOpen()
{
  return d_device_open;
}

// Open the audio device
void AudioDevice::open( int frequency,
                        SDL_AudioFormat format,
                        int audio_channels,
                        int chunksize,
                        int mix_channels )
{
  if( !d_device_open )
  {
    // Open the audio device with the requested specs
    int return_value = Mix_OpenAudio( frequency,
                                      format,
                                      audio_channels,
                                      chunksize );

    // Make sure the return value == 0
    if( return_value != 0 )
      qFatal( "Error: could not open audio device!" );

    // Cache the specs that the audio device is actually using
    d_chunksize = chunksize;

    return_value = Mix_QuerySpec( &d_frequency,
                                  &d_format,
                                  &d_number_of_audio_channels );

    // Make sure the return value != 0
    if( return_value == 0 )
      qFatal( "Error: could not query specs audio device is using!" );

    // Allocate the requested number of mixing channels
    d_number_of_mixer_channels = Mix_AllocateChannels( mix_channels );

    d_device_open = true;
  }
}

// Open the audio device with default settings
void AudioDevice::open()
{
  this->open( 44100, AUDIO_S16SYS, 2, 2048, 10 );
}

// Close the audio device
void AudioDevice::close()
{
  if( d_device_open )
  {
    Mix_CloseAudio();

    d_device_open = false;
  }
}

// Get the device frequency
int AudioDevice::getFrequency() const
{
  return d_frequency;
}

// Get the device format
SDL_AudioFormat AudioDevice::getFormat() const
{
  return d_format;
}

// Get the number of device channels
int AudioDevice::getNumberOfChannels() const
{
  return d_number_of_audio_channels;
}

// Get the chunk size
int AudioDevice::getChunkSize() const
{
  return d_chunksize;
}

// Get the number of mixer channels
int AudioDevice::getNumberOfMixerChannels() const
{
  return d_number_of_mixer_channels;
}

// Reserve mixer channels (0 - num_of_reserved_channels-1)
int AudioDevice::reserveMixerChannels( int number_of_reserved_channels )
{
  return Mix_ReserveChannels( number_of_reserved_channels );
}

// Remove all channel reservations
void AudioDevice::removeAllChannelReservations()
{
  Mix_ReserveChannels( 0 );
}

// Set the volume of a mixer channel (returns the current channel volume)
int AudioDevice::setMixerChannelVolume( int channel, int volume )
{
  return Mix_Volume( channel, volume );
}

// Check if a mixer channel is paused
bool AudioDevice::isMixerChannelPaused( int channel ) const
{
  return Mix_Paused( channel ) == 1;
}

// Get the number of paused mixer channels
int AudioDevice::getNumberOfPausedChannels() const
{
  return Mix_Paused( -1 );
}

// Check if a mixer channel is playing
bool AudioDevice::isMixerChannelPlaying( int channel ) const
{
  return Mix_Playing( channel ) == 1;
}

// Get the number of playing mixer channels
int AudioDevice::getNumberOfPlayingChannels() const
{
  return Mix_Playing( -1 );
}

// Check if a mixer channl is fading
Mix_Fading AudioDevice::isMixerChannelFading( int channel ) const
{
  return Mix_FadingChannel( channel );
}

// Pause a mixer channel
void AudioDevice::pauseMixerChannel( int channel )
{
  Mix_Pause( channel );
}

// Pause all mixer channels
void AudioDevice::pauseAllMixerChannels()
{
  Mix_Pause( -1 );
}

// Resume playing a mixer channel
void AudioDevice::resumePlayingMixerChannel( int channel )
{
  Mix_Resume( channel );
}

// Resume playing all mixer channels
void AudioDevice::resumePlayingAllMixerChannels()
{
  Mix_Resume( -1 );
}

// Halt playing a mixer channel
void AudioDevice::haltMixerChannel( int channel )
{
  Mix_HaltChannel( channel );
}

// Halt a mixer channel after the desired time
void AudioDevice::haltMixerChannelAfterTime(
                              int channel,
                              std::chrono::duration<int,std::milli> play_time )
{
  Mix_ExpireChannel( channel, play_time.count() );
}

// Halt a mixer channel with fade-out effect
void AudioDevice::haltMixerChannelWithFadeOut(
                          int channel,
                          std::chrono::duration<int,std::milli> fade_out_time )
{
  Mix_FadeOutChannel( channel, fade_out_time.count() );
}

// Halt all mixer channels
void AudioDevice::haltAllMixerChannels()
{
  Mix_HaltChannel( -1 );
}

// Halt all mixer channels after the desired time
void AudioDevice::haltAllMixerChannelsAfterTime(
                              std::chrono::duration<int,std::milli> play_time )
{
  Mix_ExpireChannel( -1, play_time.count() );
}

// Halt all mixer channels with fade-out effect
void AudioDevice::haltAllMixerChannelsWithFadeOut(
                          std::chrono::duration<int,std::milli> fade_out_time )
{
  Mix_FadeOutChannel( -1, fade_out_time.count() );
}

// Set the halt channel callback
void AudioDevice::setHaltChannelCallback(
                                   std::function<void(int channel)>& callback )
{
  d_halt_channel_callback = callback;

  Mix_ChannelFinished( *d_halt_channel_callback.target<void(int)>() );
}

// Play a mix chunk
/*! \details Returns the channel that the chunk is playing on.
 */
int AudioDevice::playChunk( MixChunkWrapper& mix_chunk,
                            int channel,
                            int loops )
{
  return Mix_PlayChannel( channel, mix_chunk.getRawMixChunkPtr(), loops );
}

// Play a mix chunk (with time cutoff)
/*! \details Returns the channel that the chunk is playing on.
 */
int AudioDevice::playTimedChunk(
                               MixChunkWrapper& mix_chunk,
                               std::chrono::duration<int,std::milli> play_time,
                               int channel,
                               int loops )
{
  return Mix_PlayChannelTimed( channel,
                               mix_chunk.getRawMixChunkPtr(),
                               loops,
                               play_time.count() );
}

// Play a mix chunk with a fade-in effect
/*! \details Returns the channel that the chunk is playing on.
 */
int AudioDevice::playChunkWithFadeIn(
                            MixChunkWrapper& mix_chunk,
                            std::chrono::duration<int,std::milli> fade_in_time,
                            int channel,
                            int loops )
{
  return Mix_FadeInChannel( channel,
                            mix_chunk.getRawMixChunkPtr(),
                            loops,
                            fade_in_time.count() );
}

// Play a mix chunk with a fade-in effect (and time cutoff)
/*! \details Returns the channel that the chunk is playing on.
 */
int AudioDevice::playTimedChunkWithFadeIn(
                            MixChunkWrapper& mix_chunk,
                            std::chrono::duration<int,std::milli> fade_in_time,
                            std::chrono::duration<int,std::milli> play_time,
                            int channel,
                            int loops )
{
  return Mix_FadeInChannelTimed( channel,
                                 mix_chunk.getRawMixChunkPtr(),
                                 loops,
                                 fade_in_time.count(),
                                 play_time.count() );
}

// Check if music is playing
bool AudioDevice::isMusicPlaying() const
{
  return Mix_PlayingMusic() == 1;
}

// Check if music is paused
bool AudioDevice::isMusicPaused() const
{
  return Mix_PausedMusic() == 1;
}

// Check if music is fading
Mix_Fading AudioDevice::isMusicFading() const
{
  return Mix_FadingMusic();
}

// Set the music volume
void AudioDevice::setMusicVolume( int volume )
{
  Mix_VolumeMusic( volume );
}

// Play the music
void AudioDevice::playMusic( MixMusicWrapper& music, int loops )
{
  int return_value = Mix_PlayMusic( music.getRawMusicPtr(), loops );

  // Make sure the return value == 0
  if( return_value != 0 )
    qFatal( "Error: could not play music!" );
}

// Play the music with a fade-in effect
void AudioDevice::playMusicWithFadeIn(
                            MixMusicWrapper& music,
                            std::chrono::duration<int,std::milli> fade_in_time,
                            int loops )
{
  int return_value = Mix_FadeInMusic( music.getRawMusicPtr(),
                                      loops,
                                      fade_in_time.count() );

  // Make sure the return value == 0
  if( return_value != 0 )
    qFatal( "Error: could not fade in music!" );
}

// Pause the music
void AudioDevice::pauseMusic()
{
  Mix_PauseMusic();
}

// Resume the music
void AudioDevice::resumeMusic()
{
  Mix_ResumeMusic();
}

// Rewind the music
void AudioDevice::rewindMusic()
{
  Mix_RewindMusic();
}

// Halt the music
void AudioDevice::haltMusic()
{
  Mix_HaltMusic();
}

// Halt the music with a fade-out effect
void AudioDevice::haltMusicWithFadeOut(
                          std::chrono::duration<int,std::milli> fade_out_time )
{
  int return_value = Mix_FadeOutMusic( fade_out_time.count() );

  // Make sure the return value == 1
  if( return_value != 1 )
    qFatal( "Error: could not fade out music" );
}

// Set the halt music callback
void AudioDevice::setHaltMusicCallback( std::function<void(void)>& callback )
{
  d_halt_music_callback = callback;

  Mix_HookMusicFinished( *d_halt_music_callback.target<void(void)>() );
}

// Stop the custom music player (haltMusic will not work)
void AudioDevice::haltCustomMusicPlayer()
{
  d_custom_music_player_callback = std::function<void(void*,Uint8*,int)>();

  Mix_HookMusic( NULL, NULL );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end AudioDevice.cpp
//---------------------------------------------------------------------------//
