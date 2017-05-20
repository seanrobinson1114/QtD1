//---------------------------------------------------------------------------//
//!
//! \file   VideoFile.cpp
//! \author Alex Robinson
//! \brief  The video file class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "VideoFile.h"

namespace QtD1{

// Constructor
VideoFile::VideoFile( const QString& filename,
                      const bool log_file_info )
  : d_custom_io(),
    d_raw_video_file( avformat_alloc_context() ),
    d_video_stream_index( -1 ),
    d_audio_stream_index( -1 ),
    d_video_codec_ctx( NULL ),
    d_audio_codec_ctx( NULL )
{
  // Initialize avcodec
  av_register_all();
  
  // Open the video file
  d_custom_io.reset( new AVIOContextWrapper( 4096, false, filename ) );
    
  d_raw_video_file->pb = d_custom_io->getRawContextPtr();

  int return_value = avformat_open_input( &d_raw_video_file,
                                          filename.toStdString().c_str(),
                                          NULL,
                                          NULL);
  if( return_value != 0 )
  {
    qFatal( "Error: Could not open the video file %s!",
            filename.toStdString().c_str() );
  }

  // Retrieve the stream info
  return_value = avformat_find_stream_info( d_raw_video_file, NULL );

  if( return_value < 0 )
  {
    qFatal( "Error: Could not find the stream info in video file %s!",
            filename.toStdString().c_str() );
  }
  
  // Log information about this file
  if( log_file_info )
  {
    av_dump_format( d_raw_video_file, 0, filename.toStdString().c_str(), 0 );
  }
  
  // Find the first video and audio stream
  this->findStreamIndices(); 
  
  // Open the video codec context
  this->openCodecContext(
                        d_raw_video_file->streams[d_video_stream_index]->codec,
                        &d_video_codec_ctx );

  // Open the audio codec context
  this->openCodecContext(
                        d_raw_video_file->streams[d_audio_stream_index]->codec,
                        &d_audio_codec_ctx );
}

// Destructor
VideoFile::~VideoFile()
{
  // Close the codecs
  avcodec_close( d_video_codec_ctx );
  avcodec_free_context( &d_video_codec_ctx );
  
  avcodec_close( d_audio_codec_ctx );
  avcodec_free_context( &d_audio_codec_ctx );
  
  // Close the raw video file
  avformat_close_input( &d_raw_video_file );
}

// Get the width of the video
int VideoFile::getWidth() const
{
  return d_video_codec_ctx->width;
}

// Get the height of the video
int VideoFile::getHeight() const
{
  return d_video_codec_ctx->height;
}

// Get the audio sample rate
int VideoFile::getAudioSampleRate() const
{
  return d_audio_codec_ctx->sample_rate;
}

// Get the number of audio channels
int VideoFile::getNumberOfAudioChannels() const
{
  return d_audio_codec_ctx->channels;
}

// Get the audio channel layout
int64_t VideoFile::getAudioChannelLayout() const
{
  return d_audio_codec_ctx->channel_layout;
}
    
// Get the audio format
AVSampleFormat VideoFile::getAudioFormat() const
{
  return d_audio_codec_ctx->sample_fmt;
}

// Get the time base (in seconds) of the audio stream
double VideoFile::getAudioStreamTimeBase() const
{
  return av_q2d( d_raw_video_file->streams[d_audio_stream_index]->time_base );
}

// Get the time base (in seconds) of the video stream (1/framerate)
double VideoFile::getVideoStreamTimeBase() const
{
  return av_q2d( d_raw_video_file->streams[d_video_stream_index]->time_base );
}

// Get the duration of the video (seconds)
double VideoFile::getDuration() const
{
  return d_raw_video_file->duration/(double)AV_TIME_BASE;
}

// Get a SWSContextWrapper
std::shared_ptr<SWSContextWrapper> VideoFile::getSWSContext(
                                                     AVPixelFormat dest_format,
                                                     int flags ) const
{
  return std::shared_ptr<SWSContextWrapper>( new SWSContextWrapper(
                                                    d_video_codec_ctx->width,
                                                    d_video_codec_ctx->height,
                                                    d_video_codec_ctx->pix_fmt,
                                                    d_video_codec_ctx->width,
                                                    d_video_codec_ctx->height,
                                                    dest_format,
                                                    flags ) );
}

// Get a SWRContextWrapper
std::shared_ptr<SWRContextWrapper> VideoFile::getSWRContext(
                                                 int64_t out_ch_layout,
                                                 AVSampleFormat out_sample_fmt,
                                                 int out_sample_rate ) const
{
  return std::shared_ptr<SWRContextWrapper>( new SWRContextWrapper(
                                            out_ch_layout,
                                            out_sample_fmt,
                                            out_sample_rate,
                                            d_audio_codec_ctx->channel_layout,
                                            d_audio_codec_ctx->sample_fmt,
                                            d_audio_codec_ctx->sample_rate ) );
}

// Get a frame from the file (will return false on EOF or bad read)
void VideoFile::getPacket( AVPacketWrapper& packet ) const
{
  // The packet will be modified. To ensure that we don't get any
  // memory leaks we will create a new packet and set the input packet
  // equel to it
  AVPacketWrapper local_packet;

  int return_value =
    av_read_frame( d_raw_video_file, local_packet.getRawPacketPtr() );

  if( return_value < 0 )
  {
    throw std::runtime_error( "Read error or EOF - stop reading packets" );
  }
  
  packet = local_packet;
}

// Check if the packet is from the video stream
bool VideoFile::isVideoPacket( const AVPacketWrapper& packet ) const
{
  return packet.getRawPacket().stream_index == d_video_stream_index;
}

// Check if the packet is from the audio stream
bool VideoFile::isAudioPacket( const AVPacketWrapper& packet ) const
{
  return packet.getRawPacket().stream_index == d_audio_stream_index;
}

// Decode the video frame (throws std::runtime_error if the decoding fails)
int VideoFile::decodeVideoFrame( AVFrameWrapper& video_frame,
                                 const AVPacketWrapper& packet ) const
{
  int successful_decode = 0;
  
  int bytes_decoded = avcodec_decode_video2( d_video_codec_ctx,
                                             video_frame.getRawFramePtr(),
                                             &successful_decode,
                                             packet.getRawPacketPtr() );

  if( !successful_decode )
    qWarning( "Warning: Could not decode the video frame!" );

  return bytes_decoded;
}

// Decode the audio frame (throws std::runtime_error if the decoding fails)
int VideoFile::decodeAudioFrame( AVFrameWrapper& audio_frame,
                                 const AVPacketWrapper& packet ) const
{
  int successful_decode = 0;
  
  int bytes_decoded = avcodec_decode_audio4( d_audio_codec_ctx,
                                             audio_frame.getRawFramePtr(),
                                             &successful_decode,
                                             packet.getRawPacketPtr() );

  if( !successful_decode )
    qFatal( "Error: Could not decode the audio frame!" );

  return bytes_decoded;
}

// Get the size of the frame data
int VideoFile::getAudioFrameDataSize( const AVFrameWrapper& audio_frame ) const
{
  return this->getAudioFrameDataSize( audio_frame.getRawFramePtr()->channels,
                                      audio_frame.getRawFramePtr()->nb_samples,
                                      d_audio_codec_ctx->sample_fmt,
                                      1 );
}

// Get the audio data size
int VideoFile::getAudioFrameDataSize( const int channels,
                                      const int number_of_samples,
                                      const AVSampleFormat audio_format,
                                      const int align ) const
{
  return av_samples_get_buffer_size( NULL,
                                     channels,
                                     number_of_samples,
                                     audio_format,
                                     align );
}

// find the stream indices
void VideoFile::findStreamIndices()
{
  d_video_stream_index = -1;
  d_audio_stream_index = -1;
  
  for( size_t i = 0; i < d_raw_video_file->nb_streams; ++i )
  {
    if( d_raw_video_file->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO &&
        d_video_stream_index < 0 )
    {
      d_video_stream_index = i;
    }
    
    if( d_raw_video_file->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO &&
        d_audio_stream_index < 0 )
    {
      d_audio_stream_index = i;
    }
  }

  // A video stream MUST be present
  if( d_video_stream_index < 0 )
  {
    qFatal( "Error: Could not find a video stream in the file!" );
  }

  // The audio stream is optional but should usually be present
  if( d_audio_stream_index < 0 )
  {
    qWarning( "Warning: Could not find an audio stream in the video file!" );
  }
}

// Open the codec context
void VideoFile::openCodecContext( AVCodecContext* codec_ctx_orig,
                                  AVCodecContext** codec_ctx_copy )
{
  AVCodec* codec = NULL;
  
  codec = avcodec_find_decoder( codec_ctx_orig->codec_id );

  if( codec == NULL )
    qFatal( "Error: Unsupported codec!" );
    
  // Copy the context
  *codec_ctx_copy = avcodec_alloc_context3( codec );
  
  int return_value = avcodec_copy_context( *codec_ctx_copy, codec_ctx_orig );

  if( return_value != 0 )
    qFatal( "Error: Couldn't copy codec context!" );
  
  // Open the codec
  return_value = avcodec_open2( *codec_ctx_copy, codec, NULL );

  if( return_value < 0 )
    qFatal( "Error: Couldn'open the codec!" );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end VideoFile.cpp
//---------------------------------------------------------------------------//
