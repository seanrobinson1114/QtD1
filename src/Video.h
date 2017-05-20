//---------------------------------------------------------------------------//
//!
//! \file   Video.h
//! \author Alex Robinson
//! \brief  The video class declaration
//!
//---------------------------------------------------------------------------//

#ifndef VIDEO_H
#define VIDEO_H

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QDeclarativeItem>
#include <QString>
#include <QElapsedTimer>
#include <QMutex>
#include <QFuture>
#include <QFutureWatcher>

// QtD1 Includes
#include "VideoFile.h"
#include "AudioStream.h"
#include "VideoStream.h"
#include "QMLRegistrationHelper.h"

namespace QtD1{

//! The video class
class Video : public QDeclarativeItem
{
  Q_OBJECT
  Q_PROPERTY(QString source READ getSource WRITE setSource)
  Q_PROPERTY(int videoWidth READ getWidth)
  Q_PROPERTY(int videoHeight READ getHeight)
  Q_PROPERTY(qreal videoDuration READ getDuration)
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Video" )
  
public:

  //! Constructor
  Video( QDeclarativeItem* parent = 0 );

  //! Destructor
  ~Video();

  //! Get the video source
  QString getSource() const;

  //! Set the video source
  void setSource( const QString& source );

  //! Get the width of the video
  int getWidth() const;

  //! Get the height of the video
  int getHeight() const;

  //! Get the duration of the video (seconds)
  qreal getDuration() const;

  //! Get the current time of the video (seconds)
  Q_INVOKABLE double getCurrentVideoTime() const;

  //! Play the video
  Q_INVOKABLE void play();

  //! Stop the video
  Q_INVOKABLE void stop();

  //! Check if the video is playing
  Q_INVOKABLE bool isPlaying() const;

  //! Load the video (asynchronous)
  Q_INVOKABLE void load();

  //! Load the video synchronously
  Q_INVOKABLE void loadSync();

  //! Paint the current sprite frame
  void paint( QPainter* painter,
              const QStyleOptionGraphicsItem* option,
              QWidget* widget = 0 ) override;

signals:

  void sourceLoaded( QString source );

  void videoStarted();

  void videoFinished();

private slots:

  // Handle source loaded
  void handleLoadingFinished();

  // Handle video play loop finished
  void handleVideoPlayLoopFinished();

  // Handle video frame changed
  void handleVideoFrameChanged();

private:

  // Load the video implementation
  static void loadImpl( Video* obj );

  // The video play loop
  static void videoPlayLoop( Video* obj );

  // Wait for load to finish
  void waitForLoadToFinish() const;

  // Wait for play loop to finish
  void waitForPlayLoopToFinish() const;

  // Clean up the video data
  void cleanUpVideoData();

  // The video filename
  QString d_filename;

  // The video timer
  std::shared_ptr<QElapsedTimer> d_timer;

  // The video file
  std::shared_ptr<VideoFile> d_video_file;

  // The audio stream
  std::unique_ptr<AudioStream> d_audio_stream;

  // The video stream
  std::unique_ptr<VideoStream> d_video_stream;

  // Tells if the video is playing
  bool d_video_playing;

  // The video load future
  QFuture<void> d_video_load_future;

  // The video load future watcher
  QFutureWatcher<void> d_video_load_future_watcher;

  // The video play loop future
  QFuture<void> d_video_play_loop_future;

  // THe video play loop future watcher
  QFutureWatcher<void> d_video_play_loop_future_watcher;
};
  
} // end QtD1 namespace

#endif // end VIDEO_H

//---------------------------------------------------------------------------//
// end Video.h
//---------------------------------------------------------------------------//
