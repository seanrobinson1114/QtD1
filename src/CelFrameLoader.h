//---------------------------------------------------------------------------//
//!
//! \file   CelFrameLoader.h
//! \author Alex Robinson
//! \brief  The cel frame loader class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CEL_FRAME_LOADER_H
#define CEL_FRAME_LOADER_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QImageReader>

// QtD1 Includes
#include "FrameLoader.h"

namespace QtD1{

//! The cel frame loader
class CelFrameLoader : public FrameLoader
{
  Q_OBJECT

public:

  //! Constructor
  CelFrameLoader( QObject* parent = 0 );

  //! Destructor
  ~CelFrameLoader()
  { /* ... */ }

private:

  // Get ready for frame loading
  int getReadyForFrameLoading() override;
  
  // Load the frame of interest
  QImage loadFrame( const int frame_index ) override;

  // Finish frame loading
  void finishFrameLoading() override;

  // The source image reader
  std::unique_ptr<QImageReader> d_source_image_reader;
};
  
} // end QtD1 namespace

#endif // end CEL_FRAME_LOADER_H

//---------------------------------------------------------------------------//
// end CelFrameLoader.h
//---------------------------------------------------------------------------//
