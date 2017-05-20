//---------------------------------------------------------------------------//
//!
//! \file   VideoStream.h
//! \author Alex Robinson
//! \brief  The video stream class declaration
//!
//---------------------------------------------------------------------------//

#ifndef VIDEO_STREAM_H
#define VIDEO_STREAM_H

// Std Lib Includes
#include <memory>
#include <thread>
#include <utility>
#include <chrono>

// Qt Includes
#include <QObject>
#include <QElapsedTimer>
#include <QMutex>
#include <QRectF>

// QtD1 Includes
#include "ThreadSafeQueue.h"
#include "VideoFile.h"
#include "AVPacketWrapper.h"
#include "AVPictureWrapper.h"

namespace QtD1{

//! The video stream class
class VideoStream : public QObject
{
  Q_OBJECT
  
public:

  //! Stop waiting conditions
  static void stopWaits();

  //! Set the delay threshold (seconds)
  static void setDelayThreshold( const double threshold );

  //! Constructor (for best efficiency, provide a streaming texture)
  VideoStream( const std::shared_ptr<const VideoFile>& video_file,
               const std::shared_ptr<const QElapsedTimer>& sync_timer );

  //! Destructor
  ~VideoStream();

  //! Present the current video frame
  void presentCurrentFrame( QPainter* painter, const QRectF& viewport );

  //! Add a packet to the stream
  void addVideoPacket( const AVPacketWrapper& packet );
  
  //! Check if the video stream is finished
  bool isEmpty() const;

  //! Purge threads from this queue
  void purge();

signals:

  void frameChanged();

private:

  // Decode a video packet
  static void decodeVideoPackets( VideoStream* stream );

  // Update the current video picture
  static void updateCurrentVideoPicture( VideoStream* stream );

  // Copy constructor
  VideoStream( const VideoStream& );

  // Convert AVFrameWrapper to QImage
  QImage convertToImage( const AVFrameWrapper& av_frame ) const;

  // Assignment operator
  VideoStream& operator=( const VideoStream& );

  // Stop threads that are waiting for data
  static bool s_stop_waits;

  // The delay threshold
  static std::chrono::duration<double> s_delay_threshold;

  // Stop waits in the stream
  bool d_stop_waits;

  // The video file that contains the video data
  std::shared_ptr<const VideoFile> d_video_file;

  // The sync timer
  std::shared_ptr<const QElapsedTimer> d_sync_timer;

  // The sws context
  std::shared_ptr<SWSContextWrapper> d_sws_ctx;

  // The decode video packets future
  QFuture<void> d_decode_video_packets_future;

  // The update current video picture future
  QFuture<void> d_update_current_video_picture_future;

  // Records if the first frame update is still needed 
  bool d_first_frame_update_completed;

  // The texture picture usage mutex
  QMutex d_current_video_picture_usage_mutex;

  // The current video picture
  QImage d_current_video_picture;

  // The queue of video frame packets
  typedef ThreadSafeQueue<AVPacketWrapper> FramePacketQueue;
  FramePacketQueue d_video_packets;

  // The queue of decoded video frames
  typedef std::pair<QImage,std::chrono::duration<double> > DecodedVideoImage;
  typedef ThreadSafeQueue<DecodedVideoImage> DecodedVideoFrameQueue;
  DecodedVideoFrameQueue d_decoded_frames;
};
  
} // end QtD1 namespace

#endif // end VIDEO_STREAM_H

//---------------------------------------------------------------------------//
// end VideoStream.h
//---------------------------------------------------------------------------//
