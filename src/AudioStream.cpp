//---------------------------------------------------------------------------//
//!
//! \file   AudioStream.cpp
//! \author Alex Robinson
//! \brief  The audio stream class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <vector>

// SDL Includes
#include <SDL.h>

// QtD1 Includes
#include "AudioStream.h"
#include "AudioDevice.h"

namespace QtD1{

// Initialize static member data
bool AudioStream::s_stop_waits = false;
const std::chrono::duration<double> AudioStream::AudioSyncData::s_audio_sync_threshold( 0.010 );
// Note: this is the same weight factor used by ffplay.c
const double AudioStream::AudioSyncData::s_weight_factor = exp(log(0.01)/20);
const uint32_t AudioStream::AudioSyncData::s_min_number_of_data_points_needed = 20;

// Stop waiting conditions
void AudioStream::stopWaits()
  {
    s_stop_waits = true;

    AudioPacketQueue::stopWaits();
  }

// Constructor (chunck size must be a multiple of 2)
AudioStream::AudioStream(
                        const std::shared_ptr<const VideoFile>& video_file,

                        const std::shared_ptr<const QElapsedTimer>& sync_timer,
                        uint16_t chunk_size )
  : d_stop_waits( false ),
    d_video_file( video_file ),
    d_sync_timer( sync_timer ),
    d_audio_sync_data(),
    d_source_frame_info(),
    d_target_frame_info(),
    d_audio_converter(),
    d_audio_buffer(),
    d_audio_packets()
{
  // Open the audio device with the desired specs
  AudioDevice& audio_device = AudioDevice::getInstance();

  if( audio_device.isOpen() )
    audio_device.close();

  audio_device.open( video_file->getAudioSampleRate(),
                     AUDIO_S16SYS,
                     video_file->getNumberOfAudioChannels(),
                     chunk_size );

  // Set up a custom music player that will play the audio stream
  audio_device.setCustomMusicPlayerCallback(&AudioStream::audioCallback, this);

  // Set the target frame info
  d_target_frame_info.frequency = audio_device.getFrequency();
  d_target_frame_info.channels = audio_device.getNumberOfChannels();
  d_target_frame_info.channel_layout =
    av_get_default_channel_layout( audio_device.getNumberOfChannels() );
  d_target_frame_info.format = AV_SAMPLE_FMT_S16;
  d_target_frame_info.frame_size =
    av_samples_get_buffer_size( NULL,
                                d_target_frame_info.channels,
                                1,
                                d_target_frame_info.format,
                                1 );
  d_target_frame_info.bytes_per_sec =
    av_samples_get_buffer_size( NULL,
                                d_target_frame_info.channels,
                                d_target_frame_info.frequency,
                                d_target_frame_info.format,
                                1 );

  // Set the audio converter
  d_audio_converter =
    d_video_file->getSWRContext( d_target_frame_info.channel_layout,
                                 d_target_frame_info.format,
                                 d_target_frame_info.frequency );

  // Set the source frame info
  d_source_frame_info.frequency = d_video_file->getAudioSampleRate();
  d_source_frame_info.channels = d_video_file->getNumberOfAudioChannels();
  d_source_frame_info.channel_layout = d_video_file->getAudioChannelLayout();
  d_source_frame_info.format = d_video_file->getAudioFormat();
  d_source_frame_info.frame_size =
    av_samples_get_buffer_size( NULL,
                                d_source_frame_info.channels,
                                1,
                                d_source_frame_info.format,
                                1 );
  d_target_frame_info.bytes_per_sec =
    av_samples_get_buffer_size( NULL,
                                d_source_frame_info.channels,
                                d_source_frame_info.frequency,
                                d_source_frame_info.format,
                                1 );

  // Initialize the audio sync data
  d_audio_sync_data.time_diff_threshold =
    audio_device.getChunkSize()/d_target_frame_info.bytes_per_sec;
  d_audio_sync_data.weighted_time_diff = 0.0;
  d_audio_sync_data.number_of_data_points = 0;
}

//! Destructor
AudioStream::~AudioStream()
{
  d_audio_packets.purge();

  this->purge();

  // Stop the custom music player
  AudioDevice::getInstance().haltCustomMusicPlayer();

  // Reopen the audio device with the default settings
  AudioDevice::getInstance().close();
  AudioDevice::getInstance().open();
}

// Add a packet to the stream
void AudioStream::addAudioPacket( const AVPacketWrapper& packet )
{
  d_audio_packets.pushBack( packet );
}

// Purge threads from this queue
void AudioStream::purge()
{
  d_stop_waits = true;
}

// Get an audio chunck from the stream
void AudioStream::getAudioChunk( Uint8* stream, int stream_size )
{
  size_t bytes_to_copy;

  std::deque<uint8_t>::iterator buffer_start, buffer_end;
  
  while( stream_size > 0 )
  {
    if( s_stop_waits || d_stop_waits )
      break;
    
    // Decode more data
    if( d_audio_buffer.empty() )
    {
      this->fillAudioBuffer();
      
      // Go back to the top in case the audio buffer failed to be filled
      continue;
    }
    
    // Determine the number of bytes to copy to the requested stream
    bytes_to_copy = std::min( d_audio_buffer.size(), (size_t)stream_size );
    
    // Copy the audio chunk to the stream
    buffer_start = d_audio_buffer.begin();
    buffer_end = buffer_start;
    std::advance( buffer_end, bytes_to_copy );
    
    std::copy( buffer_start, buffer_end, stream );
    
    stream_size -= bytes_to_copy;
    stream += bytes_to_copy;
    
    d_audio_buffer.erase( buffer_start, buffer_end );
  }
}

// The callback used with SDL_AudioSpec
void AudioStream::audioCallback( void* userdata, Uint8* stream, int len )
{
  ((AudioStream*)userdata)->getAudioChunk( stream, len );
}

// Fill the stored audio buffer with data (called when the buffer is empty)
void AudioStream::fillAudioBuffer()
{
  AVPacketWrapper audio_packet = d_audio_packets.getTop();
  d_audio_packets.popTop();
  
  AVFrameWrapper audio_frame;
  int decoded_bytes = 0;
  
  // Note: an audio packet can have multiple frames so we will continue
  //       to read in frames from the packet until the number of bytes
  //       that have been read in is equal to the packet size
  while( decoded_bytes < audio_packet.getRawPacket().size )
  {
    if( s_stop_waits || d_stop_waits )
      break;
    
    try{
      decoded_bytes +=
        d_video_file->decodeAudioFrame( audio_frame, audio_packet );
    }
    // If there was a decoding error - break;
    catch( const std::runtime_error& exception )
    {
      std::cerr << "Caught audio decoding exception: "
                << exception.what() << std::endl;
      break;
    }
    
    this->convertAudioData( audio_frame );
  }
}

// Convert audio data
void AudioStream::convertAudioData( const AVFrameWrapper& frame )
{
  const uint8_t** input_data =
    (const uint8_t**)frame.getRawFramePtr()->extended_data;

  int required_samples = this->getRequiredNumberOfSamples( frame );
  
  int number_of_output_samples = required_samples;
  
  int output_size =
    d_video_file->getAudioFrameDataSize( d_target_frame_info.channels,
                                         number_of_output_samples,
                                         d_target_frame_info.format,
                                         1 );

  std::vector<uint8_t> output_data( output_size );
  
  if( required_samples != frame.getRawFramePtr()->nb_samples )
  {
    int sample_delta =
      (required_samples - frame.getRawFramePtr()->nb_samples)*
      d_target_frame_info.frequency/frame.getRawFramePtr()->sample_rate;
    
    int compensation_distance = required_samples*
      d_target_frame_info.frequency/frame.getRawFramePtr()->sample_rate;
    
    d_audio_converter->setCompensation( sample_delta, compensation_distance );
  }

  uint8_t* output_data_head = &output_data[0];
  
  d_audio_converter->convert( (uint8_t**)&output_data_head,
                              number_of_output_samples,
                              input_data,
                              frame.getRawFramePtr()->nb_samples );
  
  d_audio_buffer.insert( d_audio_buffer.end(),
                         output_data.begin(),
                         output_data.end() );
}

// Get the required number of samples (takes synching into account)
int AudioStream::getRequiredNumberOfSamples( const AVFrameWrapper& frame )
{
  int required_number_of_samples = frame.getRawFramePtr()->nb_samples;
  
  int64_t presentation_time_stamp =
    av_frame_get_best_effort_timestamp( frame.getRawFramePtr() );

  std::chrono::duration<double> expected_display_time(
              presentation_time_stamp*d_video_file->getAudioStreamTimeBase() );

  // Calculate the time difference (seconds)
  std::chrono::duration<double> time_diff =
    expected_display_time -
    std::chrono::duration<double>(d_sync_timer->elapsed()/1000.0);

  // Check if the time difference is small enough to recalculate the samples
  if( fabs( time_diff.count() ) < d_audio_sync_data.s_audio_sync_threshold.count() )
  {
    d_audio_sync_data.weighted_time_diff = time_diff.count() +
      d_audio_sync_data.s_weight_factor*d_audio_sync_data.weighted_time_diff;

    ++d_audio_sync_data.number_of_data_points;

    if( d_audio_sync_data.number_of_data_points >=
        d_audio_sync_data.s_min_number_of_data_points_needed )
    {
      // Estimate the average time difference
      double average_time_diff = d_audio_sync_data.weighted_time_diff*
        (1.0 - d_audio_sync_data.s_weight_factor);

      // Correct if larger than the difference threshold
      if( fabs(average_time_diff) >= d_audio_sync_data.time_diff_threshold )
      {
        required_number_of_samples = frame.getRawFramePtr()->nb_samples +
          (int)(time_diff.count()*d_source_frame_info.frequency );

        int min_number_of_samples = frame.getRawFramePtr()->nb_samples*0.9;

        int max_number_of_samples = frame.getRawFramePtr()->nb_samples*1.1;

        required_number_of_samples = av_clip( required_number_of_samples,
                                              min_number_of_samples,
                                              max_number_of_samples );
      }
    }
  }
  // A large difference was encountered - reset the audio sync data
  else
  {
    d_audio_sync_data.weighted_time_diff = 0.0;
    d_audio_sync_data.number_of_data_points = 0;
  }
  
  return required_number_of_samples;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end AudioStream.cpp
//---------------------------------------------------------------------------//

