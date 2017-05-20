//---------------------------------------------------------------------------//
//!
//! \file   StandardImageProperties.h
//! \author Alex Robinson
//! \brief  Standard image properties base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef STANDARD_IMAGE_PROPERTIES_H
#define STANDARD_IMAGE_PROPERTIES_H

// Qt Includes
#include <QSettings>

// QtD1 Includes
#include "ImageProperties.h"

namespace QtD1{

//! The standard image properties base class
class StandardImageProperties : public ImageProperties
{

public:

  //! Constructor
  StandardImageProperties( const QString& property_file_name );

  //! Destructor
  virtual ~StandardImageProperties()
  { /* ... */ }

  //! Get the property file name
  virtual QString getPropertyFileName() const = 0;

  //! Check if the image has properties
  bool doesImageHaveProperties( const QString& file_name ) const override;

  //! Get the number of images (usually one but possibly more)
  int getNumberOfImages( const QString& file_name ) const override;

  //! Get the size of frame headers (bytes)
  int getFrameHeaderSize( const QString& file_name ) const override;

  //! Get the frame width
  int getFrameWidth( const QString& file_name,
                     const int frame_index ) const override;

  //! Get the frame height
  int getFrameHeight( const QString& file_name,
                      const int frame_index ) const override;

  //! Get the palette file names
  void getPaletteFileNames( const QString& file_name,
                            QStringList& palette_files ) const override;

  //! Check if a palette file (with path) is compatible with the image
  bool isPaletteCompatible( const QString& file_name,
                            const QString& palette_file ) const override;

  //! Check if the image has color transition data
  bool hasColorTransitionData( const QString& file_name ) const override;

  //! Get the image color transition file names
  void getColorTransitionFileNames(
                               const QString& file_name,
                               QStringList& color_trans_files ) const override;

private:

  // Extract dimension from dimension string
  int extractDimensionFromDimensionData( const QString& property_path,
                                         const int frame_index,
                                         const int default_dimension_value ) const;
  
  // The image properties file handler
  QSettings d_properties_file;
};
  
} // end QtD1 namespace

#endif // end STANDARD_IMAGE_PROPERTIES_H

//---------------------------------------------------------------------------//
// end StandardImageProperties.h
//---------------------------------------------------------------------------//
