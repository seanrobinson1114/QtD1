//---------------------------------------------------------------------------//
//!
//! \file   FrameLoader.h
//! \author Alex Robinson
//! \brief  The frame loader class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FRAME_LOADER_H
#define FRAME_LOADER_H

// Qt Includes
#include <QObject>
#include <QImage>
#include <QString>
#include <QList>
#include <QFuture>
#include <QFutureWatcher>

namespace QtD1{

//! The frame loader
class FrameLoader : public QObject
{
  Q_OBJECT

public:

  //! Constructor
  FrameLoader( QObject* parent  = 0 );

  //! Destructor
  virtual ~FrameLoader()
  { /* ... */ }

  //! Set the source
  void setSource( const QString& source );

  //! Get the source
  QString getSource() const;

signals:

  void frameLoaded( const int frame_index, QImage frame );
  void sourceLoaded( QString source );

public slots:

  //! Load all of the frames from the source
  void loadFrames();

  //! Load the selected frames from the source
  void loadFrames( const QList<int>& frame_indices );

  //! Load all of the frames from the source synchronously
  void loadFramesSync();

  //! Load the selected frames from the source synchronously
  void loadFramesSync( const QList<int>& frame_indices );

  //! Wait for load to finish
  void waitForLoadToFinish();

protected:

  //! Get ready for frame loading (returns the total number of frames)
  virtual int getReadyForFrameLoading() = 0;

  //! Load the frame of interest
  virtual QImage loadFrame( const int frame_index ) = 0;

  //! Finish frame loading
  virtual void finishFrameLoading()
  { /* ... */ }

private slots:

  // Handle asynchronous frame loading finished
  void handleAsyncFrameLoadingFinished();

private:

  // Load the frames from the source implementation
  static void loadAllFramesImpl( FrameLoader* obj );

  // Load the frames from the source implementation
  static void loadFramesImpl( QList<int> frame_indices,
                              FrameLoader* obj );

  // Load the frames
  static void loadFramesLoop( const QList<int>& frame_indices,
                              const int total_frames,
                              FrameLoader* obj );

  // The source
  QString d_source;

  // The frame load future
  QFuture<void> d_frame_load_future;

  // The frame load future watcher
  QFutureWatcher<void> d_frame_load_future_watcher;
};
  
} // end QtD1 namespace

#endif // end FRAME_LOADER_H

//---------------------------------------------------------------------------//
// end FrameLoader.h
//---------------------------------------------------------------------------//
