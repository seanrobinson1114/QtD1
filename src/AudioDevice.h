//---------------------------------------------------------------------------//
//!
//! \file   AVFrameWrapper.h
//! \author Alex, Sean Robinson
//! \brief  The sdl_mixer api wrapper declaration
//!
//---------------------------------------------------------------------------//

#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

// std lib includes
#include <chrono>
#include <functional>
#include <memory>

// SDL Includes
#include <SDL_mixer.h>

// QtD1 includes
#include "MixChunkWrapper.h"
#include "MixMusicWrapper.h"

namespace QtD1{

//! The audio device class (singleton wrapper around SDL_Mixer API)
class AudioDevice
{

public:

  //! Get the singleton instance
  static AudioDevice& getInstance();

  //! Get the first free unreserved channel
  static int getFirstFreeUnreservedChannel();

  //! Set infinite looping
  static int infiniteLooping();

  //! Destructor
  ~AudioDevice();

  //! Check if the device is open
  bool isOpen();

  //! Open the audio device
  void open( int frequency,
             SDL_AudioFormat format,
             int audio_channels,
             int chunksize,
             int mix_channels = 8 );

  //! Open the audio device with default settings
  void open();

  //! Close the audio device
  void close();

  //! Get the device frequency
  int getFrequency() const;

  //! Get the device format
  SDL_AudioFormat getFormat() const;

  //! Get the number of device channels
  int getNumberOfChannels() const;

  //! Get the chunk size
  int getChunkSize() const;

  //! Get the number of mixer channels
  int getNumberOfMixerChannels() const;

  //! Reserve mixer channels (0 - num_of_reserved_channels-1)
  int reserveMixerChannels( int number_of_reserved_channels );

  //! Remove all channel reservations
  void removeAllChannelReservations();

  //! Set the volume of a mixer channel
  int setMixerChannelVolume( int channel, int volume );

  //! Check if a mixer channel is paused
  bool isMixerChannelPaused( int channel ) const;

  //! Get the number of paused mixer channels
  int getNumberOfPausedChannels() const;

  //! Check if a mixer channel is playing
  bool isMixerChannelPlaying( int channel ) const;

  //! Get the number of playing mixer channels
  int getNumberOfPlayingChannels() const;

  //! Check if a mixer channl is fading
  Mix_Fading isMixerChannelFading( int channel ) const;
  
  //! Pause a mixer channel
  void pauseMixerChannel( int channel );

  //! Pause all mixer channels
  void pauseAllMixerChannels();

  //! Resume playing a mixer channel
  void resumePlayingMixerChannel( int channel );

  //! Resume playing all mixer channels
  void resumePlayingAllMixerChannels();

  //! Halt playing a mixer channel
  void haltMixerChannel( int channel );

  //! Halt a mixer channel after the desired time
  void haltMixerChannelAfterTime(
                             int channel,
                             std::chrono::duration<int,std::milli> play_time );

  //! Halt a mixer channel with fade-out effect
  void haltMixerChannelWithFadeOut(
                         int channel,
                         std::chrono::duration<int,std::milli> fade_out_time );

  //! Halt all mixer channels
  void haltAllMixerChannels();

  //! Halt all mixer channels after the desired time
  void haltAllMixerChannelsAfterTime(
                             std::chrono::duration<int,std::milli> play_time );
  
  //! Halt all mixer channels with fade-out effect
  void haltAllMixerChannelsWithFadeOut(
                         std::chrono::duration<int,std::milli> fade_out_time );
  
  //! Set the halt channel callback
  void setHaltChannelCallback( std::function<void(int channel)>& callback );
  
  //! Play a mix chunk
  int playChunk( MixChunkWrapper& mix_chunk,
                 int channel = AudioDevice::getFirstFreeUnreservedChannel(),
                 int loops = 0 );
  
  //! Play a mix chunk (with time cutoff)
  int playTimedChunk(
                    MixChunkWrapper& mix_chunk,
                    std::chrono::duration<int,std::milli> play_time,
                    int channel = AudioDevice::getFirstFreeUnreservedChannel(),
                    int loops = 0 );
  
  //! Play a mix chunk with a fade-in effect
  int playChunkWithFadeIn(
                    MixChunkWrapper& mix_chunk,
                    std::chrono::duration<int,std::milli> fade_in_time,
                    int channel = AudioDevice::getFirstFreeUnreservedChannel(),
                    int loops = 0  );
  
  //! Play a mix chunk with a fade-in effect (and time cutoff)
  int playTimedChunkWithFadeIn(
                    MixChunkWrapper& mix_chunk,
                    std::chrono::duration<int,std::milli> fade_in_time,
                    std::chrono::duration<int,std::milli> play_time,
                    int channel = AudioDevice::getFirstFreeUnreservedChannel(),
                    int loops = 0  );

  //! Check if music is playing
  bool isMusicPlaying() const;

  //! Check if music is paused
  bool isMusicPaused() const;

  //! Check if music is fading
  Mix_Fading isMusicFading() const;
  
  //! Set the music volume
  void setMusicVolume( int volume );
  
  //! Play the music
  void playMusic( MixMusicWrapper& music,
                  int loops = AudioDevice::infiniteLooping() );
  
  //! Play the music with a fade-in effect
  void playMusicWithFadeIn( MixMusicWrapper& music,
                            std::chrono::duration<int,std::milli> fade_in_time,
                            int loops = AudioDevice::infiniteLooping() );
  
  //! Pause the music
  void pauseMusic();

  //! Resume the music
  void resumeMusic();

  //! Rewind the music
  void rewindMusic();

  //! Halt the music
  void haltMusic();

  //! Halt the music with a fade-out effect
  void haltMusicWithFadeOut(
                         std::chrono::duration<int,std::milli> fade_out_time );

  //! Set the halt music callback
  void setHaltMusicCallback( std::function<void(void)>& callback );
  
  //! Set the custom music player callback
  template<typename T>
  void setCustomMusicPlayerCallback(
                               std::function<void(void*,Uint8*,int)>& callback,
                               T* user_data );

  //! Set the custom music player callback
  template<typename T>
  void setCustomMusicPlayerCallback( void (*callback)(void*,Uint8*,int),
                                     T* user_data );

  //! Stop the custom music player (haltMusic will not work)
  void haltCustomMusicPlayer();
  
private:

  // All constructors and the equality operator must be private (singleton)
  AudioDevice();
  AudioDevice( const AudioDevice& that );
  AudioDevice& operator=( const AudioDevice& that );

  // The singleton instance
  static std::unique_ptr<AudioDevice> s_instance;

  // Use to indicate the first free unreserved channel
  static const int s_first_free_unreserved_channel;

  // Use to indicate infinite looping
  static const int s_infinite_looping;

  // Is the device open?
  bool d_device_open;

  // The audio frequency
  int d_frequency;

  // The audio format
  SDL_AudioFormat d_format;

  // The number of audio channels
  int d_number_of_audio_channels;

  // The audio chunk size
  int d_chunksize;

  // The number mixer channels
  int d_number_of_mixer_channels;

  // The halt channel callback (cached to ensure function permanence)
  std::function<void(int channel)> d_halt_channel_callback;

  // The halt music callback (cached to ensure function permanence)
  std::function<void(void)> d_halt_music_callback;

  // The custom music player callback (cached to ensure function permanence)
  std::function<void(void*,Uint8*,int)> d_custom_music_player_callback;
};

// Set the custom music player callback
template<typename T>
void AudioDevice::setCustomMusicPlayerCallback(
                               std::function<void(void*,Uint8*,int)>& callback,
                               T* user_data )
{
  d_custom_music_player_callback = callback;

  Mix_HookMusic(
              *d_custom_music_player_callback.target<void(void*,Uint8*,int)>(),
              user_data );
}

// Set the custom music player callback
template<typename T>
void AudioDevice::setCustomMusicPlayerCallback(
                                            void (*callback)(void*,Uint8*,int),
                                            T* user_data )
{
  Mix_HookMusic( callback, user_data );
}

} // end QtD1 namespace

#endif // end AUDIO_DEVICE_H

//---------------------------------------------------------------------------//
// end AudioDevice.h
//---------------------------------------------------------------------------//
