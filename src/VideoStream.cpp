//---------------------------------------------------------------------------//
//!
//! \file   VideoStream.cpp
//! \author Alex Robinson
//! \brief  The video stream class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cstring>
#include <thread>

// Qt Includes
#include <QMutexLocker>
#include <QtConcurrentRun>
#include <QPainter>

// QtD1 Includes
#include "VideoStream.h"

namespace QtD1{

// Initialize static member data
bool VideoStream::s_stop_waits = false;
std::chrono::duration<double> VideoStream::s_delay_threshold( 0.005 );

// Stop waiting conditions
void VideoStream::stopWaits()
{
  s_stop_waits = true;

  FramePacketQueue::stopWaits();
  DecodedVideoFrameQueue::stopWaits();
}

// Set the delay threshold (seconds)
void VideoStream::setDelayThreshold( const double threshold )
{
  s_delay_threshold = std::chrono::duration<double>( threshold );
}

// Constructor (for best efficiency, provide a streaming texture)
VideoStream::VideoStream(
                       const std::shared_ptr<const VideoFile>& video_file,
                       const std::shared_ptr<const QElapsedTimer>& sync_timer )
  : d_stop_waits( false ),
    d_video_file( video_file ),
    d_sync_timer( sync_timer ),
    d_sws_ctx( video_file->getSWSContext( AV_PIX_FMT_RGB565LE, SWS_BILINEAR ) ),
    d_decode_video_packets_future(),
    d_update_current_video_picture_future(),
    d_first_frame_update_completed( false ),
    d_current_video_picture_usage_mutex(),
    d_current_video_picture(),
    d_video_packets(),
    d_decoded_frames()
{
  // Initiate the extra threads
  d_decode_video_packets_future =
    QtConcurrent::run( VideoStream::decodeVideoPackets, this );

  d_update_current_video_picture_future =
    QtConcurrent::run( VideoStream::updateCurrentVideoPicture, this );
}

// Destructor
VideoStream::~VideoStream()
{
  d_video_packets.purge();
  d_decoded_frames.purge();
  
  this->purge();
}

// Present the current video frame
void VideoStream::presentCurrentFrame( QPainter* painter,
                                       const QRectF& viewport )
{
  QMutexLocker lock( &d_current_video_picture_usage_mutex );

  if( !d_current_video_picture.isNull() )
    painter->drawImage( viewport, d_current_video_picture );
}

// Add a packet to the stream
void VideoStream::addVideoPacket( const AVPacketWrapper& packet )
{
  d_video_packets.pushBack( packet );
}

// Check if the video stream is finished
bool VideoStream::isEmpty() const
{
  return d_video_packets.empty() && d_decoded_frames.empty();
}

// Purge threads from this queue
void VideoStream::purge()
{
  d_stop_waits = true;

  d_decode_video_packets_future.waitForFinished();
  d_update_current_video_picture_future.waitForFinished();
}

// Update the current video picture
void VideoStream::updateCurrentVideoPicture( VideoStream* stream )
{
  while( true )
  {
    if( s_stop_waits || stream->d_stop_waits )
      break;

    DecodedVideoImage video_picture = stream->d_decoded_frames.getTop();
    stream->d_decoded_frames.popTop();

    // Calculate the delay time (seconds)
    std::chrono::duration<double> delay_time =
      video_picture.second -
      std::chrono::duration<double>( stream->d_sync_timer->elapsed()/1000.0 );
    
    // Delay then update the current video picture
    // Note: if behind the sync clock then skip this frame (unless this is
    //       the first frame, which always needs to be used)
    if( (delay_time > s_delay_threshold ||
         !stream->d_first_frame_update_completed) &&
        !s_stop_waits && !stream->d_stop_waits)
    {
      std::this_thread::sleep_for( delay_time );

      stream->d_current_video_picture_usage_mutex.lock();
      
      stream->d_current_video_picture = video_picture.first;

      stream->d_current_video_picture_usage_mutex.unlock();

      emit stream->frameChanged();

      if( !stream->d_first_frame_update_completed )
          stream->d_first_frame_update_completed = true;
    }
  }
}

// Decode a video packet
void VideoStream::decodeVideoPackets( VideoStream* stream )
{
  while( true )
  {
    if( s_stop_waits || stream->d_stop_waits )
      break;
    
    AVPacketWrapper video_packet = stream->d_video_packets.getTop();
    stream->d_video_packets.popTop();
    
    AVFrameWrapper video_frame;
    
    try{
      stream->d_video_file->decodeVideoFrame( video_frame, video_packet );
    }
    // If there was a decoding error - continue
    catch( const std::runtime_error& exception )
    {
      //qWarning( "Caught video decoding exception: %s", exception.what() );

      continue;
    }

    // Convert the frame to an image
    QImage frame_image = stream->convertToImage( video_frame );

    // Calculate the expected display time of the video picture
    int64_t presentation_time_stamp =
      av_frame_get_best_effort_timestamp( video_frame.getRawFramePtr() );
    
    std::chrono::duration<double> expected_display_time( 
      presentation_time_stamp*stream->d_video_file->getVideoStreamTimeBase() );
    
    stream->d_decoded_frames.pushBack(
                        std::make_pair( frame_image, expected_display_time ) );
  }
}

// Convert AVFrameWrapper to QImage
QImage VideoStream::convertToImage( const AVFrameWrapper& av_frame ) const
{
  // Convert the frame from its native format to RGB
  // AVPictureWrapper av_pict( AV_PIX_FMT_RGB565LE,
  //                           d_video_file->getWidth(),
  //                           d_video_file->getHeight() );
  // d_sws_ctx->scale( av_frame, av_pict );
  
  // Create the new image that will store the frame data
  QImage frame_image( d_video_file->getWidth(),
                      d_video_file->getHeight(),
                      QImage::Format_RGB16 );

  d_sws_ctx->scale( av_frame, frame_image );

  // Copy the frame data into the frame image
  // for( int y = 0; y < d_video_file->getHeight(); ++y )
  // {
  //   memcpy( frame_image.scanLine(y),
  //           av_pict.getRawData()[0] + y*av_pict.getLinesize()[0],
  //           av_pict.getLinesize()[0] );
  // }

  return frame_image;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end VideoStream.cpp
//---------------------------------------------------------------------------//
