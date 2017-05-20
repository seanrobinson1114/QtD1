//---------------------------------------------------------------------------//
//!
//! \file   CelDecoder.h
//! \author Alex Robinson
//! \brief  The cel decoder class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CEL_DECODER_H
#define CEL_DECODER_H

// Std Lib Includes
#include <memory>
#include <utility>
#include <map>
#include <functional>

// Qt Includes
#include <QString>
#include <QVector>
#include <QByteArray>
#include <QImage>
#include <QVector>

// QtD1 Includes
#include "ImageProperties.h"
#include "CelPalette.h"

namespace QtD1{

/*! The cel decoder base class
 * \details Cel, cel archive, cl2 and cl2 archive files can all be decoded.
 */
class CelDecoder
{

public:

  //! Constructor (file name)
  CelDecoder( const QString& file_name_with_path );

  //! Constructor (file name with extracted data)
  CelDecoder( const QString& file_name_with_path,
              QByteArray& file_data );

  //! Destructor
  ~CelDecoder()
  { /* ... */ }

  //! Decode the image data
  void decode( QVector<QImage>& frames, const CelPalette& palette ) const;

protected:

  // The frame data type
  typedef QVector<QByteArray> FrameData;

  // The image frame data type
  typedef std::map<QString,FrameData> ImageFrameData;

private:

  // Extract file properties
  void extractFileProperties( const QString& file_name_with_path );
    
  // Load the image properties
  void loadImageProperties();

  // Assign getImageFrameData method
  void assignGetImageFrameDataMethod();

  // Initialize the buffer stream
  void initializeBufferStream();

  // Check palette compatibility
  bool isPaletteCompatible( const CelPalette& palette ) const;

  // Load the image offsets
  void getImageOffsets( QVector<quint32>& image_offsets ) const;

  // Load the frame offsets from the image header
  void getFrameOffsets( QVector<quint32>& frame_offsets ) const;

  // Get the archive image alias
  QString getArchiveImageAlias( const int archive_image_index,
                                const int num_archive_files ) const;
  
  // Get the frame data
  void getFrameData( const QString& image_alias,
                     const QVector<quint32>& frame_offsets,
                     FrameData& frame_data ) const;

  // Get the image frame data
  void getImageFrameData( ImageFrameData& image_frame_data ) const;

  // Get the cel image archive frame data
  void getCelImageArchiveFrameData( ImageFrameData& image_frame_data ) const;

  // Get the cl2 image archive frame data
  void getCl2ImageArchiveFrameData( ImageFrameData& image_frame_data ) const;

  // Get the image file name with path
  QString getImageFileNameWithPath() const;

  // Get the image buffer stream
  QDataStream& getImageBufferStream() const;
  
  // The file name (without path)
  QString d_file_name;

  // The file extension
  QString d_file_extension;

  // The file path
  QString d_file_path;

  // The file data
  QByteArray d_file_data;

  // The image buffer stream
  QDataStream d_image_buffer_stream;

  // The image properties
  ImageProperties* d_image_properties;

  // The getImageFrameData method
  std::function<void(ImageFrameData&)> d_get_image_frame_data;
};

// Get the image file name with path
inline QString CelDecoder::getImageFileNameWithPath() const
{
  return d_file_path + d_file_name;
}
  
// Get the image buffer stream
// Note: this is a little hack that gives us non-const access to the image
//       stream. This is desired because no changes will be made to the
//       stream data even though the stream location will change.
inline QDataStream& CelDecoder::getImageBufferStream() const
{
  return const_cast<QDataStream&>( d_image_buffer_stream );
}

} // end QtD1 namespace

#endif // end CEL_DECODER_H

//---------------------------------------------------------------------------//
// end CelDecoder.h
//---------------------------------------------------------------------------//
