//---------------------------------------------------------------------------//
//!
//! \file   AudioStream.h
//! \author Alex Robinson
//! \brief  The audio stream class declaration
//!
//---------------------------------------------------------------------------//

#ifndef AUDIO_STREAM_H
#define AUDIO_STREAM_H

// Std Lib Includes
#include <memory>
#include <chrono>

// SDL Includes
#include <SDL_mixer.h>

// Qt Includes
#include <QElapsedTimer>

// QtD1 Includes
#include "ThreadSafeQueue.h"
#include "AVPacketWrapper.h"
#include "AVFrameWrapper.h"
#include "SWSContextWrapper.h"
#include "VideoFile.h"

namespace QtD1{

//! The audio stream class
class AudioStream
{

public:

  //! Stop waiting conditions
  static void stopWaits();

  //! Constructor (chunck size must be a multiple of 2)
  AudioStream( const std::shared_ptr<const VideoFile>& video_file,
               const std::shared_ptr<const QElapsedTimer>& sync_timer,
               uint16_t chunk_size );

  //! Destructor
  ~AudioStream();

  //! Play the audio in the stream
  void play() const;

  //! Add a packet to the stream
  void addAudioPacket( const AVPacketWrapper& packet );

  //! Purge threads from this queue
  void purge();

private:

  // Struct for storing audio info
  struct AudioFrameInfo
  {
    int frequency;
    int channels;
    int64_t channel_layout;
    AVSampleFormat format;
    int frame_size;
    int bytes_per_sec;
  };

  // Struct for audio syncing
  struct AudioSyncData
  {
    // The audio sync threshold
    static const std::chrono::duration<double> s_audio_sync_threshold;

    // The weight factor used to accumulated time differences
    static const double s_weight_factor;

    // The number of data points needed before corrections can be made
    static const uint32_t s_min_number_of_data_points_needed;

    double time_diff_threshold;
    double weighted_time_diff;
    uint32_t number_of_data_points;
  };

  // The callback used with SDL_AudioSpec
  static void audioCallback( void* userdata, Uint8* stream, int len );

  //! Get an audio chunck from the stream
  void getAudioChunk( Uint8* stream, int stream_size );

  // Fill the stored audio buffer with data (called when the buffer is empty)
  void fillAudioBuffer();

  // Convert audio data
  void convertAudioData( const AVFrameWrapper& frame );

  // Get the required number of samples (takes synching into account)
  int getRequiredNumberOfSamples( const AVFrameWrapper& frame );

  // Copy constructor
  AudioStream( const AudioStream& );

  // Assignment operator
  AudioStream& operator=( const AudioStream& );

  // Stop threads that are waiting for data
  static bool s_stop_waits;

  // Stop waits in the stream
  bool d_stop_waits;

  // The video file that contains the audio data
  std::shared_ptr<const VideoFile> d_video_file;

  // The sync timer
  std::shared_ptr<const QElapsedTimer> d_sync_timer;

  // The audio sync data
  AudioSyncData d_audio_sync_data;

  // The audio specifications
  AudioFrameInfo d_source_frame_info;
  AudioFrameInfo d_target_frame_info;

  // The audio converter
  std::shared_ptr<SWRContextWrapper> d_audio_converter;

  // The buffer that stores decoded audio frame data
  std::deque<uint8_t> d_audio_buffer;

  // The queue of audio frame packets
  typedef ThreadSafeQueue<AVPacketWrapper> AudioPacketQueue;
  AudioPacketQueue d_audio_packets;
};
  
} // end QtD1 namespace

#endif // end AUDIO_STREAM_H

//---------------------------------------------------------------------------//
// end AudioStream.h
//---------------------------------------------------------------------------//
