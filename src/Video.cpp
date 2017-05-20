//---------------------------------------------------------------------------//
//!
//! \file   Video.cpp
//! \author Alex Robinson
//! \brief  The video class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QtConcurrentRun>

// QtD1 Includes
#include "Video.h"

namespace QtD1{

// Constructor
Video::Video( QDeclarativeItem* parent )
  : QDeclarativeItem( parent ),
    d_filename(),
    d_timer( new QElapsedTimer ),
    d_video_file(),
    d_audio_stream(),
    d_video_stream(),
    d_video_playing( false ),
    d_video_load_future(),
    d_video_load_future_watcher(),
    d_video_play_loop_future(),
    d_video_play_loop_future_watcher()
{
  // This flag has to be disabled so that drawing can be done
  this->setFlag( QGraphicsItem::ItemHasNoContents, false );

  connect( &d_video_load_future_watcher, SIGNAL(finished()),
           this, SLOT(handleLoadingFinished()) );
  connect( &d_video_play_loop_future_watcher, SIGNAL(finished()),
           this, SLOT(handleVideoPlayLoopFinished()) );
}

// Destructor
Video::~Video()
{
  this->stop();
}

// Get the video source
QString Video::getSource() const
{
  return d_filename;
}

// Set the video source
void Video::setSource( const QString& source )
{
  d_filename = source;
}

// Get the width of the video
int Video::getWidth() const
{
  if( d_video_file )
    return d_video_file->getWidth();
  else
    return 0;
}

// Get the height of the video
int Video::getHeight() const
{
  if( d_video_file )
    return d_video_file->getHeight();
  else
    return 0;
}

// Get the duration of the video (seconds)
double Video::getDuration() const
{
  if( d_video_file )
    return d_video_file->getDuration();
  else
    return 0.0;
}

// Get the current time of the video (seconds)
Q_INVOKABLE qreal Video::getCurrentVideoTime() const
{
  if( d_timer->isValid() )
    return d_timer->elapsed()/1000.0;
  else
    return 0.0;
}

// Play the video
Q_INVOKABLE void Video::play()
{
  // Check if the video is already playing
  if( !d_video_playing )
  {
    if( !d_video_file )
    {
      qWarning( "Video::play: the video has not been loaded yet! It will be "
                "loaded now. For better performance, load before playing." );

      this->loadSync();
    }

    d_video_playing = true;

    d_video_play_loop_future = QtConcurrent::run( Video::videoPlayLoop, this );

    d_video_play_loop_future_watcher.setFuture( d_video_play_loop_future );

    emit videoStarted();
  }
}

// Stop the video
Q_INVOKABLE void Video::stop()
{
  // By setting this to false the play loop should exit - wait to be safe
  if( d_video_playing )
  {
    d_video_playing = false;

    this->waitForPlayLoopToFinish();

    this->cleanUpVideoData();
  }
}

// Check if the video is playing
Q_INVOKABLE bool Video::isPlaying() const
{
  if( d_video_playing )
    return true;
  else
    return false;
}

// Load the video (asynchronous)
Q_INVOKABLE void Video::load()
{
  d_video_load_future =
    QtConcurrent::run( Video::loadImpl, this );

  d_video_load_future_watcher.setFuture( d_video_load_future );
}

// Load the video synchronously
Q_INVOKABLE void Video::loadSync()
{
  Video::loadImpl( this );

  this->handleLoadingFinished();
}

// Load the video implementation
void Video::loadImpl( Video* obj )
{
  if( obj->d_video_playing )
    obj->stop();

  // Reset the timer
  obj->d_timer.reset( new QElapsedTimer );

  // Load the video file
  try{
    obj->d_video_file.reset( new VideoFile( obj->d_filename, true ) );
  }
  catch( const std::exception& exception )
  {
    qFatal( "Could not open video file %s! Here are the details: \n%s",
            obj->d_filename.toStdString().c_str(),
            exception.what() );
  }

  // Create the audio stream
  obj->d_audio_stream.reset(
                    new AudioStream( obj->d_video_file, obj->d_timer, 1024 ) );

  // Create the video stream
  obj->d_video_stream.reset(
                          new VideoStream( obj->d_video_file, obj->d_timer ) );
}

// Paint the current sprite frame
void Video::paint( QPainter* painter,
                   const QStyleOptionGraphicsItem*,
                   QWidget* )
{
  if( d_video_playing && d_video_stream != NULL )
    d_video_stream->presentCurrentFrame( painter, this->boundingRect() );
}

// The video play loop
void Video::videoPlayLoop( Video* obj )
{
  // Reset the timer
  obj->d_timer->restart();

  // Create a packet
  AVPacketWrapper packet;

  // Check if all packets have been read
  bool all_packets_read = false;

  while( obj->d_video_playing )
  {
    // Get a packet from the video file
    if( !all_packets_read )
    {
      try{
        obj->d_video_file->getPacket( packet );
      }
      catch( const std::runtime_error& exception )
      {
        //qWarning( "Caught packet read exception: %s", exception.what() );

        all_packets_read = true;
      }

      // Determine the type of packet
      if( obj->d_video_file->isVideoPacket( packet ) )
        obj->d_video_stream->addVideoPacket( packet );
      else if( obj->d_video_file->isAudioPacket( packet ) )
        obj->d_audio_stream->addAudioPacket( packet );
      else
        qWarning( "Encountered a packet of unknown type!");
    }

    // Exit the loop once all packets have been read the the video stream
    // has finished processing/displaying all decoded packets.
    if( obj->d_video_stream->isEmpty() && all_packets_read )
      break;
  }
  
  // Stop the timer
  obj->d_timer->invalidate();

  obj->d_video_playing = false;
}

// Handle source loaded
void Video::handleLoadingFinished()
{
  this->update();

  // Connect the video stream signals to the video slots
  QObject::connect( d_video_stream.get(), SIGNAL(frameChanged()),
                    this, SLOT(handleVideoFrameChanged()) );
  
  emit sourceLoaded( this->getSource() );
}

// Handle video play loop finished
void Video::handleVideoPlayLoopFinished()
{
  this->cleanUpVideoData();
  
  emit videoFinished();
}

// Handle video frame changed
void Video::handleVideoFrameChanged()
{
  this->update();
}

// Wait for load to finish
void Video::waitForLoadToFinish() const
{
  // Remove the const from our future so that we can call this wait method
  // from const member functions
  const_cast<QFuture<void>&>( d_video_load_future ).waitForFinished();
}

// Wait for play loop to finish
void Video::waitForPlayLoopToFinish() const
{
  // Remove the const from our future so that we can call this wait method
  // from const member functions
  const_cast<QFuture<void>&>( d_video_play_loop_future ).waitForFinished();
}

// Clean up the video data
void Video::cleanUpVideoData()
{
  // Close the streams
  d_audio_stream.reset();
  d_video_stream.reset();

  // Close the video file
  d_video_file.reset();
}

QML_REGISTER_TYPE( Video );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Video.cpp
//---------------------------------------------------------------------------//
