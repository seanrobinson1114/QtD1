//---------------------------------------------------------------------------//
//!
//! \file   CelDecoder.cpp
//! \author Alex Robinson
//! \brief  The cel decoder definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// Qt Includes
#include <QFile>

// QtD1 Includes
#include "CelDecoder.h"
#include "CelImageProperties.h"
#include "Cl2ImageProperties.h"
#include "CelFrameDecoder.h"

namespace QtD1{

// Constructor (file name)
CelDecoder::CelDecoder( const QString& file_name_with_path )
  : d_file_name(),
    d_file_extension(),
    d_file_path(),
    d_file_data(),
    d_image_buffer_stream( d_file_data ),
    d_image_properties( NULL )
{
  // Extract the file properties
  this->extractFileProperties( file_name_with_path );
  
  // Load the image properties
  this->loadImageProperties();

  // Assign the required getImageFrameData method
  this->assignGetImageFrameDataMethod();

  // Extract the file data
  QFile file( file_name_with_path );

  d_file_data.resize( file.size() );

  if( !file.read( d_file_data.data(), d_file_data.size() ) )
  {
    qFatal( "Error: could not read file %s!",
            file_name_with_path.toStdString().c_str() );
  }

  // Initialize the buffer stream
  this->initializeBufferStream();
}

// Constructor (file name with extracted data)
CelDecoder::CelDecoder( const QString& file_name_with_path,
                        QByteArray& file_data )
  : d_file_name(),
    d_file_extension(),
    d_file_path(),
    d_file_data( file_data ),
    d_image_buffer_stream( d_file_data ),
    d_image_properties( NULL )
{
  // Extract the file properties
  this->extractFileProperties( file_name_with_path );
  
  // Load the image properties
  this->loadImageProperties();

  // Assign the required getImageFrameData method
  this->assignGetImageFrameDataMethod();

  // Initialize the buffer stream
  this->initializeBufferStream();
}

// Extract file properties
void CelDecoder::extractFileProperties( const QString& file_name_with_path )
{
  int last_slash_pos = file_name_with_path.lastIndexOf( '/' );
  int file_name_without_path_size =
    file_name_with_path.size() - last_slash_pos - 1;
  int file_path_size = last_slash_pos + 1;

  d_file_path = file_name_with_path.mid( 0, file_path_size );
  d_file_name =
    file_name_with_path.mid( last_slash_pos + 1, file_name_without_path_size );

  int last_period_pos = d_file_name.lastIndexOf( '.' );
  int extension_size = d_file_name.size() - last_period_pos;

  d_file_extension = d_file_name.mid( last_period_pos, extension_size );
}

// Load the image properties
void CelDecoder::loadImageProperties()
{
  if( d_file_extension == ".cel" )
    d_image_properties = CelImageProperties::getInstance();
  else if( d_file_extension == ".cl2" )
    d_image_properties = Cl2ImageProperties::getInstance();
  else
  {
    qFatal( "CelDecoder Error: Cannot decode file %s because it has an "
            "unsupported extension (%s)!",
            this->getImageFileNameWithPath().toStdString().c_str(),
            d_file_extension.toStdString().c_str() );
  }

  // Make sure that the image has properties
  if( !d_image_properties->doesImageHaveProperties( d_file_name ) )
  {
    qFatal( "CelDecoder Error: Cannot decode file %s because there is no "
            "metadata!",
            this->getImageFileNameWithPath().toStdString().c_str() );
  }
}

// Assign getImageFrameData method
void CelDecoder::assignGetImageFrameDataMethod()
{
  // Image archive extraction methods
  if( d_image_properties->getNumberOfImages( d_file_name ) > 1 )
  {
    if( d_file_extension == ".cel" )
    {
      d_get_image_frame_data =
        std::bind<void>( &CelDecoder::getCelImageArchiveFrameData,
                         std::cref( *this ),
                         std::placeholders::_1 );
    }
    else // ".cl2"
    {
      d_get_image_frame_data =
        std::bind<void>( &CelDecoder::getCl2ImageArchiveFrameData,
                         std::cref( *this ),
                         std::placeholders::_1 );
    }
  }
  // Standard extraction method
  else
  {
    d_get_image_frame_data =
      std::bind<void>( &CelDecoder::getImageFrameData,
                       std::cref( *this ),
                       std::placeholders::_1 );
  }
}

// Initialize the buffer stream
void CelDecoder::initializeBufferStream()
{
  // Set the byte order in the buffer stream
  d_image_buffer_stream.setByteOrder( QDataStream::LittleEndian );
}

// Get the frame data
void CelDecoder::getFrameData( const QString& image_alias,
                               const QVector<quint32>& frame_offsets,
                               FrameData& frame_data ) const
{
  frame_data.resize( frame_offsets.size() - 1 );

  // Load the cached header size
  size_t frame_header_size =
    d_image_properties->getFrameHeaderSize( image_alias );

  // Read in the data for each frame
  for( int i = 0; i < frame_data.size(); ++i )
  {
    const int frame_start = frame_offsets[i] + frame_header_size;

    frame_data[i].resize( frame_offsets[i+1] - frame_start );
    
    if( frame_header_size > 0 )
      this->getImageBufferStream().skipRawData( frame_header_size );
    
    this->getImageBufferStream().readRawData( frame_data[i].data(),
                                              frame_data[i].size() );
  }
}

// Get the image frame data
void CelDecoder::getImageFrameData( ImageFrameData& image_frame_data ) const
{
  // Load the frame offsets
  QVector<quint32> frame_offsets;

  this->getFrameOffsets( frame_offsets );

  QString image_name = d_file_name;

  // Get the frame data for this image
  this->getFrameData( image_name,
                      frame_offsets,
                      image_frame_data[image_name] );
}

// Get the cel image archive frame data
void CelDecoder::getCelImageArchiveFrameData(
                                       ImageFrameData& image_frame_data ) const
{
  // Load the image offsets
  QVector<quint32> image_offsets;

  this->getImageOffsets( image_offsets );

  // Load each image
  for( int i = 0; i < image_offsets.size(); ++i )
  {
    // Get the image alias
    QString image_alias =
      this->getArchiveImageAlias( i, image_offsets.size() );
        
    // Load the frame offsets
    QVector<quint32> frame_offsets;

    this->getFrameOffsets( frame_offsets );

    // Get the frame data for this image
    this->getFrameData( image_alias,
                        frame_offsets,
                        image_frame_data[image_alias] );
  }
}

// Get the cl2 image archive frame data
void CelDecoder::getCl2ImageArchiveFrameData(
                                       ImageFrameData& image_frame_data ) const
{
  // Load the image offsets
  QVector<quint32> image_offsets;

  this->getImageOffsets( image_offsets );

  // Load the frame offsets - these are part of the header in cl2 image
  // archives
  QVector<QVector<quint32> > frame_offsets( image_offsets.size() );

  for( int i = 0; i < image_offsets.size(); ++i )
    this->getFrameOffsets( frame_offsets[i] );

  // Load each image
  for( int i = 0; i < image_offsets.size(); ++i )
  {
    // Get the image alias
    QString image_alias =
      this->getArchiveImageAlias( i, image_offsets.size() );

    // Get the frame data for this image
    this->getFrameData( image_alias,
                        frame_offsets[i],
                        image_frame_data[image_alias] );
  }
}

// Load the image offsets
void CelDecoder::getImageOffsets( QVector<quint32>& image_offsets ) const
{
  // Load the number of images
  int number_of_images = d_image_properties->getNumberOfImages( d_file_name );

  // The offsets are implicit if there is only a single image
  if( number_of_images == 1 )
  {
    image_offsets.resize( 1 );
    image_offsets[0] = 0;
  }
  else
  {
    image_offsets.resize( number_of_images );

    for( int i = 0; i < number_of_images; ++i )
      this->getImageBufferStream() >> image_offsets[i];
  }
}

// Load the frame offsets from the image header
void CelDecoder::getFrameOffsets( QVector<quint32>& frame_offsets ) const
{
  // Load the number of frames
  quint32 num_frames;

  this->getImageBufferStream() >> num_frames;

  // Load the frame offsets
  frame_offsets.resize( num_frames + 1 );
  
  for( size_t i = 0; i < num_frames+1; ++i )
    this->getImageBufferStream() >> frame_offsets[i];
}

// Get the archive image alias
QString CelDecoder::getArchiveImageAlias( const int archive_image_index,
                                          const int num_archive_files ) const
{
  if( num_archive_files > 1 )
  {
    int period_position = d_file_name.indexOf( "." );

    QString file_name_root = d_file_name.mid( 0, period_position );

    return file_name_root + QString::number( archive_image_index ) + d_file_extension;
  }
  else
    return d_file_name;
}

// Decode the image data
void CelDecoder::decode( QVector<QImage>& frames,
                         const CelPalette& palette ) const
{
  // Check if the palette is compatible
  if( !this->isPaletteCompatible( palette ) )
  {
    qFatal( "CelDecoder Error: The requested palette %s is not compatible "
            "with the image %s!",
            palette.getName().toStdString().c_str(),
            this->getImageFileNameWithPath().toStdString().c_str() );
  }
  
  // Load the image frame data
  ImageFrameData image_frame_data;

  d_get_image_frame_data( image_frame_data );

  // Decode each image
  ImageFrameData::const_iterator image_frame_data_it, image_frame_data_end;
  image_frame_data_it = image_frame_data.begin();
  image_frame_data_end = image_frame_data.end();

  while( image_frame_data_it != image_frame_data_end )
  {
    const FrameData& frame_data = image_frame_data_it->second;

    // Decode each frame of this image
    for( int i = 0; i < frame_data.size(); ++i )
    {
      // Get the frame decoder
      CelFrameDecoder::DecodeFunctor decode_frame =
        CelFrameDecoder::getDecoder( image_frame_data_it->first,
                                     i,
                                     frame_data[i] );

      frames.push_back( decode_frame( palette ) );
    }

    ++image_frame_data_it;
  }

  // Reset the stream
  this->getImageBufferStream().resetStatus();
}

// Check palette compatibility
bool CelDecoder::isPaletteCompatible( const CelPalette& palette ) const
{
  return d_image_properties->isPaletteCompatible(
                                              d_file_name, palette.getName() );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CelDecoder.cpp
//---------------------------------------------------------------------------//
