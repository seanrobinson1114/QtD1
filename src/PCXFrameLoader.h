//---------------------------------------------------------------------------//
//!
//! \file   PCXFrameLoader.h
//! \author Alex Robinson
//! \brief  The pcx frame loader class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PCX_FRAME_LOADER_H
#define PCX_FRAME_LOADER_H

// Qt Includes
#include <QColor>

// QtD1 Includes
#include "FrameLoader.h"

namespace QtD1{

//! The pcx frame loader
class PCXFrameLoader : public FrameLoader
{
  Q_OBJECT

public:

  //! Constructor
  PCXFrameLoader( QObject* parent = 0 );

  //! Destructor
  ~PCXFrameLoader()
  { /* ... */ }

  //! Get the color that will be made transparent
  QColor getTransparentColor() const;

  //! Set the color that will be made transparent
  void setTransparentColor( const QColor& transparent_color );

  //! Get the number of rows in the sprite sheet
  int getNumberOfRows() const;

  //! Set the number of rows in the sprite sheet
  void setNumberOfRows( const int num_rows );

  //! Get the number of columns in the sprite sheet
  int getNumberOfCols() const;

  //! Set the number of columns in the sprite sheet
  void setNumberOfCols( const int num_cols );

private:

  // Get ready for frame loading
  int getReadyForFrameLoading() override;
  
  // Load the frame of interest
  QImage loadFrame( const int frame_index ) override;

  // Finish frame loading
  void finishFrameLoading() override;

  // Convert the transparent color in the source image to transparent
  void convertTransparentColorToTransparent();
  
  // The transparent color
  QColor d_transparent_color;

  // The number of rows to extract from the source
  int d_source_rows;

  // The number of cols to extract from the source
  int d_source_cols;

  // The source image
  QImage d_source_image;

  // The frame width
  int d_frame_width;

  // The frame height
  int d_frame_height;
};
  
} // end QtD1 namespace

#endif // end PCX_FRAME_LOADER_H

//---------------------------------------------------------------------------//
// end PCXFrameLoader.h
//---------------------------------------------------------------------------//
