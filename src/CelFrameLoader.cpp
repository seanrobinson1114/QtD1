//---------------------------------------------------------------------------//
//!
//! \file   CelFrameLoader.cpp
//! \author Alex Robinson
//! \brief  The cel frame loader class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "CelFrameLoader.h"

namespace QtD1{

// Constructor
CelFrameLoader::CelFrameLoader( QObject* parent )
  : FrameLoader( parent ),
    d_source_image_reader()
{ /* ... */ }

// Get ready for frame loading
int CelFrameLoader::getReadyForFrameLoading()
{
  if( !this->getSource().contains( ".cel" ) &&
      !this->getSource().contains( ".cl2" ) )
  {
    qFatal( "CelFrameLoader Error: Image source %s is not a cel file!",
            this->getSource().toStdString().c_str() );
  }
  
  d_source_image_reader.reset( new QImageReader( this->getSource() ) );

  return d_source_image_reader->imageCount();
}
  
// Load the frame of interest
QImage CelFrameLoader::loadFrame( const int frame_index )
{
  d_source_image_reader->jumpToImage( frame_index );

  return d_source_image_reader->read();
}

// Finish frame loading
void CelFrameLoader::finishFrameLoading()
{
  d_source_image_reader.reset();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CelFrameLoader.cpp
//---------------------------------------------------------------------------//
