//---------------------------------------------------------------------------//
//!
//! \file   CelHandler.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Cel handler class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <functional>
#include <vector>

// Qt Includes
#include <QColor>
#include <QDataStream>
#include <QImage>

// QtD1 Includes
#include "CelHandler.h"
#include "MPQHandler.h"
#include "CustomMPQFileHeader.h"
#include "CelDecoder.h"
#include "CelPalette.h"

namespace QtD1{

// Constructor
CelHandler::CelHandler()
  : d_image_frames(),
    d_frame_index( 0 )
{ /* ... */ }

// Check if the handler can read from the assigned device
bool CelHandler::canRead() const
{
  if( this->canRead(this->device()) )
  {
    this->setFormat( "cel" );
    return true;
  }

  return false;
}

// Read from the device and load the image
bool CelHandler::read( QImage* image )
{
  *image = d_image_frames[d_frame_index];
  return true;
}

// Write the image
/*! \details No image writing will be supported
 */
bool CelHandler::write( const QImage& image )
{
  Q_UNUSED(image);
  
  return false;
}

// Get the number of images in the device
int CelHandler::imageCount() const
{
  return d_image_frames.size();
}

// Get the number of times that the animation should loop
/*! \details The image should loop infinitely
 */
int CelHandler::loopCount() const
{
  return -1;
}

// Get the number of milliseconds to wait before reading next image
int CelHandler::nextImageDelay() const
{
  return 100;
}

// Jump to the desired image
bool CelHandler::jumpToImage( int image_number )
{
  if( image_number < d_image_frames.size() )
  {
    d_frame_index = image_number;

    return true;
  }
  else
    return false;
}

// Jump to the next image
bool CelHandler::jumpToNextImage()
{
  if( d_frame_index < d_image_frames.size() - 1 )
  {
    ++d_frame_index;

    return true;
  }
  else
    return false;
}

// Load the image frames from the device
void CelHandler::loadImageFrames()
{
  // Open the device
  if( !this->device()->isOpen() )
    this->device()->open( QIODevice::ReadOnly );
  
  // Load the file data
  QByteArray file_data( this->device()->size(), 0 );

  this->device()->read( file_data.data(), file_data.size() );

  // Extract the header from the file data
  qint64 image_data_start_index;
  
  CustomMPQFileHeader header =
    CustomMPQFileHeader::extractFromBuffer( file_data,
                                            image_data_start_index );

  if( header.getNumElements() != 2 )
  {
    qFatal( "CelHandler Error: an invalid custom cel header was encountered "
            "(num elements = %i != 2)!",
            header.getNumElements() );
  }

  // Extract the cel image data and palette data
  QString cel_file_name, palette_file_name;
  qint64 cel_data_start_index, palette_data_start_index;
  qint64 cel_file_size, palette_file_size;

  if( header[0].filename.contains( ".cel" ) ||
      header[0].filename.contains( ".cl2" ) )
  {
    cel_file_name = header[0].filename;
    cel_data_start_index = header[0].start_location + image_data_start_index;

    palette_file_name = header[1].filename;
    palette_data_start_index =
      header[1].start_location + image_data_start_index;

    cel_file_size = palette_data_start_index - cel_data_start_index;
    palette_file_size = file_data.size() - palette_data_start_index;
  }
  else
  {
    cel_file_name = header[1].filename;
    cel_data_start_index = header[1].start_location + image_data_start_index;

    palette_file_name = header[0].filename;
    palette_data_start_index =
      header[0].start_location + image_data_start_index;

    cel_file_size = file_data.size() - cel_data_start_index;
    palette_file_size = cel_data_start_index - palette_data_start_index;
  }
  
  QByteArray cel_image_data( file_data.data()+cel_data_start_index,
                             cel_file_size );
  QByteArray palette_data( file_data.data()+palette_data_start_index,
                           palette_file_size );
  
  // Decode the cel image data
  CelPalette palette( palette_file_name, palette_data );

  CelDecoder decoder( cel_file_name, cel_image_data );

  decoder.decode( d_image_frames, palette );
}

// Check if the handler can read from the device
bool CelHandler::canRead( QIODevice* device )
{
  if( !device )
  {
    qWarning("CelHandler::canRead() called with no device");
    return false;
  }

  QFile* file_device = dynamic_cast<QFile*>( device );

  if( !file_device )
    return false;

  return MPQHandler::getInstance()->doFilesExist( file_device->fileName() );
}

// Return the capabilities of the plugin
auto CelPlugin::capabilities( QIODevice* device, const QByteArray& format ) const
  -> Capabilities
{
  if( format == "cel" || format == "cl2" )
    return Capabilities(CanRead);
  if( !format.isEmpty() )
    return nullptr;

  if( !device->isOpen() )
    return nullptr;

  Capabilities cap;
  if( device->isReadable() && CelHandler::canRead(device) )
    cap |= CanRead;

  return cap;
}

// Return the list of image keys this plugin supports
QStringList CelPlugin::keys() const
{
  return QStringList() << "cel" << "cl2";
}

// Create a handler for the cel image data
QImageIOHandler* CelPlugin::create( QIODevice* device, const QByteArray& format ) const
{
  CelHandler* handler = new CelHandler;
  handler->setDevice(device);
  handler->setFormat(format);

  handler->loadImageFrames();

  return handler;
}
  
} // end QtD1 namespace

// Export the plugin
Q_EXPORT_PLUGIN2(cel, QtD1::CelPlugin)

//---------------------------------------------------------------------------//
// end CelHandler.cpp
//---------------------------------------------------------------------------//
