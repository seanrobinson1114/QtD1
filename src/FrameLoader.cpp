//---------------------------------------------------------------------------//
//!
//! \file   FrameLoader.cpp
//! \author Alex Robinson
//! \brief  The frame loader class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QtConcurrentRun>

// QtD1 Includes
#include "FrameLoader.h"

namespace QtD1{

// Constructor
FrameLoader::FrameLoader( QObject* parent )
  : QObject( parent ),
    d_source(),
    d_frame_load_future(),
    d_frame_load_future_watcher()
{ 
  // Connect the frame load future watcher signal to the handle async frame
  // load finished slot
  QObject::connect( &d_frame_load_future_watcher, SIGNAL(finished()),
                    this, SLOT(handleAsyncFrameLoadingFinished()) );
}

// Set the source
void FrameLoader::setSource( const QString& source )
{
  d_source = source;
}

// Get the source
QString FrameLoader::getSource() const
{
  return d_source;
}

// Load the frames from the source
void FrameLoader::loadFrames()
{
  d_frame_load_future =
    QtConcurrent::run( FrameLoader::loadAllFramesImpl, this );

  d_frame_load_future_watcher.setFuture( d_frame_load_future );
}

// Load the frames from the source
void FrameLoader::loadFrames( const QList<int>& frame_indices )
{
  d_frame_load_future =
    QtConcurrent::run( FrameLoader::loadFramesImpl, frame_indices, this );

  d_frame_load_future_watcher.setFuture( d_frame_load_future );
}

// Load the frames synchronously
void FrameLoader::loadFramesSync()
{
  FrameLoader::loadAllFramesImpl( this );
}

// Load the frames from the source synchronously
void FrameLoader::loadFramesSync( const QList<int>& frame_indices )
{
  FrameLoader::loadFramesImpl( frame_indices, this );
}

// Wait for load to finish
void FrameLoader::waitForLoadToFinish()
{
  if( d_frame_load_future.isRunning() )
    d_frame_load_future.waitForFinished();
}

// Handle asynchronous frame loading finished
void FrameLoader::handleAsyncFrameLoadingFinished()
{ 
  d_frame_load_future = QFuture<void>();
  d_frame_load_future_watcher.setFuture( d_frame_load_future );
}

// Load the frames from the source implementation
void FrameLoader::loadAllFramesImpl( FrameLoader* obj )
{
  int number_of_frames = obj->getReadyForFrameLoading();

  QList<int> frame_indices;
  
  for( int i = 0; i < number_of_frames; ++i )
    frame_indices << i;

  FrameLoader::loadFramesLoop( frame_indices, number_of_frames, obj );
}

// Load the frames from the source implementation
void FrameLoader::loadFramesImpl( QList<int> frame_indices,
                                  FrameLoader* obj )
{
  int number_of_frames = obj->getReadyForFrameLoading();

  FrameLoader::loadFramesLoop( frame_indices, number_of_frames, obj );
}

// Load the frames
void FrameLoader::loadFramesLoop( const QList<int>& frame_indices,
                                  const int total_frames,
                                  FrameLoader* obj )
{
  // Load all of the frames in the source
  for( int i = 0; i < frame_indices.size(); ++i )
  {
    int frame_index = frame_indices[i];

    if( frame_index >= 0 && frame_index < total_frames )
    {
      QImage frame = obj->loadFrame( i );
    
      emit obj->frameLoaded( frame_index, frame );
    }
    else
    {
      qWarning( "FrameLoader Warning: Encountered an invalid frame index: "
                "%i not in [0,%i]", frame_index, total_frames-1 );
    }
  }

  obj->finishFrameLoading();

  emit obj->sourceLoaded( obj->getSource() );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end FrameLoader.cpp
//---------------------------------------------------------------------------//
