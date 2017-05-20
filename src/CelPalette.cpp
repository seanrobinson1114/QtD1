//---------------------------------------------------------------------------//
//!
//! \file   CelPalette.cpp
//! \author Alex Robinson
//! \brief  The palette class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QDataStream>
#include <QFile>
#include <QBuffer>

// QtD1 Includes
#include "CelPalette.h"
#include "MPQHandler.h"

namespace QtD1{

// Constructor
/*! \details Palettes extracted from .pal files will always have 256 
 * entries
 */
CelPalette::CelPalette( const QString& file_name )
  : d_file_name( file_name ),
    d_palette_colors( 256 ),
    d_palette_rgbs( 256 ),
    d_transparent_color_key( 0 )
{
  // Open the palette
  QFile palette_file( "/" + file_name );
  palette_file.open( QIODevice::ReadOnly );

  this->extractPalette( palette_file );
}

// Constructor (file name and extracted data)
CelPalette::CelPalette( const QString& file_name,
                        const QByteArray& palette_data )
  : d_file_name( file_name ),
    d_palette_colors( 256 ),
    d_palette_rgbs( 256 )
{
  QBuffer buffer;
  buffer.setData( palette_data );
  buffer.open( QIODevice::ReadOnly );

  this->extractPalette( buffer );
}

// Validate the palette file name
void CelPalette::validatePaletteFileName( const QString& file_name )
{
  // Make sure that the file name is valid
  if( !file_name.contains( ".pal" ) )
  {
    qFatal( "CelPalette Error: The requested file (%s) is not a palette file!",
            file_name.toStdString().c_str() );
  }
  
  if( !MPQHandler::getInstance()->doesFileExist( file_name ) )
  {
    qFatal( "CelPalette Error: The requested palette file (%s) does not "
            "exist!",
            file_name.toStdString().c_str() );
  }
}

// Extract the palette from the device
void CelPalette::extractPalette( QIODevice& device )
{
  // Check if the palette buffer is valid
  if( device.size() != 256*3 )
  {
    qFatal( "CelPalette Error: Palette file (%s) has an invalid size "
            "(%lld != 256*3)!",
            d_file_name.toStdString().c_str(),
            device.size() );
  }

  // Extract the palette colors
  QDataStream stream( &device );
  stream.setByteOrder( QDataStream::LittleEndian );

  bool trans_color_found = false;
  
  for( int i = 0; i < 256; ++i )
  {
    quint8 r, g, b;

    stream >> r >> g >> b;

    if( r == 255 && g == 255 && b == 255 )
    {
      d_palette_colors[i] = Qt::transparent;
      d_transparent_color_key = i;
      trans_color_found = true;
    }
    else
      d_palette_colors[i] = QColor( r, g, b );
    
    d_palette_rgbs[i] = d_palette_colors[i].rgba();
  }

  if( !trans_color_found )
  {
    qWarning( "CelPalette Warning: no transparent pixel was found in "
              " palette (%s)!", d_file_name.toStdString().c_str() );
  }
}
  
// Get the palette name
const QString& CelPalette::getName() const
{
  return d_file_name;
}

// Get the transparent color key
int CelPalette::getTransparentColorKey() const
{
  return d_transparent_color_key;
}

// Get the color corresponding to the key
const QColor& CelPalette::getColor( const int key ) const
{
  if( key < 0 || key >= d_palette_colors.size() )
    qFatal( "CelPalette Error: The requested color key is invalid!" );
  
  return d_palette_colors[key];
}

// Get the rgba corresponding to the key
const QRgb& CelPalette::getRgba( const int key ) const
{
  if( key < 0 || key >= d_palette_rgbs.size() )
    qFatal( "CelPalette Error: The requested color key is invalid!" );
  
  return d_palette_rgbs[key];
}

// Get the color corresponding to the key
const QColor& CelPalette::operator[]( const int key ) const
{
  if( key < 0 || key >= d_palette_colors.size() )
    qFatal( "CelPalette Error: The requested color key is invalid!" );

  return d_palette_colors[key];
}

// Get a QImage compatible color table
const QVector<QRgb>& CelPalette::toColorTable() const
{
  return d_palette_rgbs;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CelPalette.cpp
//---------------------------------------------------------------------------//
