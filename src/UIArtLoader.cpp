//---------------------------------------------------------------------------//
//!
//! \file   UIArtLoader.cpp
//! \author Alex Robinson
//! \brief  The ui art loader class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "UIArtLoader.h"

namespace QtD1{

// Constructor
UIArtLoader::UIArtLoader()
  : d_frame_loader(),
    d_loaded_frames()
{
  QObject::connect( &d_frame_loader, SIGNAL(frameLoaded(const int, QImage)),
                    this, SLOT(handleFrameLoaded(const int, QImage)) );
}

// Set the source
void UIArtLoader::setSource( const QString& source )
{
  d_frame_loader.setSource( source );
}

// Set the color that will be made transparent
void UIArtLoader::setTransparentColor( const QColor& transparent_color )
{
  d_frame_loader.setTransparentColor( transparent_color );
}

// Set the number of rows
void UIArtLoader::setNumberOfRows( const int num_rows )
{
  d_frame_loader.setNumberOfRows( num_rows );
}

// Load the ui art
void UIArtLoader::loadFrames()
{
  d_loaded_frames.clear();
  d_frame_loader.loadFramesSync();
}

// Get the loaded frames
QList<QImage>& UIArtLoader::getLoadedFrames()
{
  return d_loaded_frames;
}

// Handle frame loaded
void UIArtLoader::handleFrameLoaded( const int, QImage frame )
{
  d_loaded_frames << frame;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end UIArtLoader.cpp
//---------------------------------------------------------------------------//
