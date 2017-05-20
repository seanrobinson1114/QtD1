//---------------------------------------------------------------------------//
//!
//! \file   ImageProperties.h
//! \author Alex Robinson
//! \brief  Image properties base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef IMAGE_PROPERTIES_H
#define IMAGE_PROPERTIES_H

// Qt Includes
#include <QString>
#include <QStringList>
#include <QVector>

namespace QtD1{

//! The image properties base class
class ImageProperties
{

public:

  //! Constructor
  ImageProperties()
  { /* ... */ }

  //! Destructor
  virtual ~ImageProperties()
  { /* ... */ }

  //! Check if the image has properties
  virtual bool doesImageHaveProperties( const QString& file_name ) const = 0;

  //! Get the number of images (at least one but possibly more)
  virtual int getNumberOfImages( const QString& file_name ) const = 0;

  //! Get the size of frame headers (bytes)
  virtual int getFrameHeaderSize( const QString& file_name ) const = 0;

  //! Get the frame width
  virtual int getFrameWidth( const QString& file_name,
                             const int frame_index ) const = 0;

  //! Get the frame height
  virtual int getFrameHeight( const QString& file_name,
                              const int frame_index ) const = 0;

  //! Get the compatible palette file names
  virtual void getPaletteFileNames( const QString& file_name,
                                    QStringList& palette_file_names ) const = 0;

  //! Check if a palette file (with path) is compatible with the image
  virtual bool isPaletteCompatible(
                                  const QString& file_name,
                                  const QString& palette_file_name ) const = 0;

  //! Check if the image has color transition data
  virtual bool hasColorTransitionData( const QString& file_name ) const = 0;

  //! Get the image color transition file names
  virtual void getColorTransitionFileNames(
                                    const QString& file_name,
                                    QStringList& color_trans_files ) const = 0;
};
  
} // end QtD1 namespace

#endif // end IMAGE_PROPERTIES_H

//---------------------------------------------------------------------------//
// end ImageProperties.h
//---------------------------------------------------------------------------//
