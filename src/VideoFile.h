//---------------------------------------------------------------------------//
//!
//! \file   VideoFile.h
//! \author Alex Robinson
//! \brief  The video file class declaration
//!
//---------------------------------------------------------------------------//

#ifndef VIDEO_FILE_H
#define VIDEO_FILE_H

// Std Lib Includes
#include <memory>
#include <iostream>

// AVCodec includes
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

// Qt Includes
#include <QString>

// QtD1 Includes
#include "SWSContextWrapper.h"
#include "SWRContextWrapper.h"
#include "AVIOContextWrapper.h"
#include "AVPacketWrapper.h"
#include "AVFrameWrapper.h"

namespace QtD1{

//! The video file handler class
class VideoFile
{

public:

  //! Constructor
  VideoFile( const QString& filename,
             const bool log_file_info = true );

  //! Destructor
  ~VideoFile();

  //! Get the width of the video
  int getWidth() const;

  //! Get the height of the video
  int getHeight() const;

  //! Get the audio sample rate
  int getAudioSampleRate() const;

  //! Get the number of audio channels
  int getNumberOfAudioChannels() const;

  //! Get the audio channel layout
  int64_t getAudioChannelLayout() const;

  //! Get the audio format
  AVSampleFormat getAudioFormat() const;

  //! Get the time base (in seconds) of the audio stream
  double getAudioStreamTimeBase() const;

  //! Get the time base (in seconds) of the video stream
  double getVideoStreamTimeBase() const;

  //! Get the duration of the video (seconds)
  double getDuration() const;

  //! Get a SWSContextWrapper
  std::shared_ptr<SWSContextWrapper> getSWSContext( AVPixelFormat dest_format,
                                                    int flags ) const;

  //! Get a SWRContextWrapper
  std::shared_ptr<SWRContextWrapper> getSWRContext(
                                                 int64_t out_ch_layout,
                                                 AVSampleFormat out_sample_fmt,
                                                 int out_sample_rate ) const;

  //! Get a frame from the file (will return false on EOF or bad read)
  void getPacket( AVPacketWrapper& packet ) const;

  //! Check if the packet is from the video stream
  bool isVideoPacket( const AVPacketWrapper& packet ) const;

  //! Check if the packet is from the audio stream
  bool isAudioPacket( const AVPacketWrapper& packet ) const;

  //! Decode the video frame (throws std::runtime_error if the decoding fails)
  int decodeVideoFrame( AVFrameWrapper& video_frame,
                        const AVPacketWrapper& packet ) const;

  //! Decode the audio frame (throws std::runtime_error if the decoding fails)
  int decodeAudioFrame( AVFrameWrapper& audio_frame,
                        const AVPacketWrapper& packet ) const;

  //! Get the size of the frame data
  int getAudioFrameDataSize( const AVFrameWrapper& audio_frame ) const;

  //! Get the audio data size
  int getAudioFrameDataSize( const int channels,
                             const int number_of_samples,
                             const AVSampleFormat audio_format,
                             const int align = 0 ) const;

private:

  // find the stream indices
  void findStreamIndices();

  // Open the codec context
  void openCodecContext( AVCodecContext* codec_ctx_orig,
                         AVCodecContext** codec_ctx_copy );

  // Constructor
  VideoFile();
  
  // Copy Constructor
  VideoFile( const VideoFile& that );

  // Assignment operator
  VideoFile& operator=( const VideoFile& that );

  // The custom io
  std::unique_ptr<AVIOContextWrapper> d_custom_io;

  // The raw video file
  AVFormatContext* d_raw_video_file;

  // The video stream index
  int d_video_stream_index;

  // The audio stream index
  int d_audio_stream_index;

  // The video codec context
  AVCodecContext* d_video_codec_ctx;

  // The audio codec context
  AVCodecContext* d_audio_codec_ctx;
};
  
} // end QtD1 namespace

#endif // end VIDEO_FILE_H

//---------------------------------------------------------------------------//
// end VideoFile.h
//---------------------------------------------------------------------------//
