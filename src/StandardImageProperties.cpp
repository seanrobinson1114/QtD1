//---------------------------------------------------------------------------//
//!
//! \file   StandardImageProperties.cpp
//! \author Alex Robinson
//! \brief  Standard image properties base class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "StandardImageProperties.h"

namespace QtD1{

// Constructor
StandardImageProperties::StandardImageProperties(
                                            const QString& property_file_name )
  : d_properties_file( property_file_name, QSettings::IniFormat )
{ /* ... */ }

// Check if the image has properties
bool StandardImageProperties::doesImageHaveProperties(
                                               const QString& file_name ) const
{
  return d_properties_file.contains( file_name + "/width" ) ||
    d_properties_file.contains( file_name + "/image_count" );
}

// Get the number of images (usually one but possibly more)
int StandardImageProperties::getNumberOfImages(
                                               const QString& file_name ) const
{
  return d_properties_file.value( file_name + "/image_count", 1 ).toInt();
}

// Get the size of frame headers (bytes)
int StandardImageProperties::getFrameHeaderSize(
                                               const QString& file_name ) const
{
  return d_properties_file.value( file_name + "/header_size", 0 ).toInt();
}

// Get the frame width
int StandardImageProperties::getFrameWidth( const QString& file_name,
                                            const int frame_index ) const
{
  if( d_properties_file.contains( file_name + "/frame_widths" ) )
  {
    
    return this->extractDimensionFromDimensionData(
                     file_name + "/frame_widths",
                     frame_index,
                     d_properties_file.value( file_name + "/width" ).toInt() );
  }
  else
    return d_properties_file.value( file_name + "/width" ).toInt();
}

// Get the frame height
int StandardImageProperties::getFrameHeight( const QString& file_name,
                                             const int frame_index ) const
{
  if( d_properties_file.contains( file_name + "/frame_heights" ) )
  {
    return this->extractDimensionFromDimensionData(
                    file_name + "/frame_heights",
                    frame_index,
                    d_properties_file.value( file_name + "/height" ).toInt() );
  }
  else
    return d_properties_file.value( file_name + "/height" ).toInt();
}

// Get the palette paths
void StandardImageProperties::getPaletteFileNames(
                                             const QString& file_name,
                                             QStringList& palette_files ) const
{
  QString palette_string = 
    d_properties_file.value( file_name + "/pals" ).toString();

  if( palette_string.size() > 0 )
    palette_files << palette_string;
  else
  {
    QList<QVariant> palette_data = 
      d_properties_file.value( file_name + "/pals" ).toList();

    if( palette_data.size() > 0 )
    {
      for( int i = 0; i < palette_data.size(); ++i )
        palette_files << palette_data[i].toString();
    }
    else
      palette_files << "levels/towndata/town.pal";
  }
}

// Check if a palette file (with path) is compatible with the image
bool StandardImageProperties::isPaletteCompatible(
                                            const QString& file_name,
                                            const QString& palette_file ) const
{
  QStringList palette_files;

  this->getPaletteFileNames( file_name, palette_files );
  
  for( int i = 0; i < palette_files.size(); ++i )
  {
    if( palette_files[i] == palette_file )
      return true;
  }

  return false;
}

// Check if an image has color transition data
bool StandardImageProperties::hasColorTransitionData(
                                               const QString& file_name ) const
{
  return d_properties_file.contains( file_name + "/trns" );
}

// Get the image color transition data file names
void StandardImageProperties::getColorTransitionFileNames(
                                         const QString& file_name,
                                         QStringList& color_trans_files ) const
{
  if( this->hasColorTransitionData( file_name ) )
  {
    QString color_trans_string = 
      d_properties_file.value( file_name + "/trns" ).toString();

    if( color_trans_string.size() > 0 )
      color_trans_files << color_trans_string;
    else
    {
      QList<QVariant> color_trans_data = 
        d_properties_file.value( file_name + "/trns" ).toList();

      for( int i = 0; i < color_trans_data.size(); ++i )
        color_trans_files << color_trans_data[i].toString();
    }
  }
}

// Extract dimension from dimension string
int StandardImageProperties::extractDimensionFromDimensionData(
                                      const QString& property_path,
                                      const int frame_index,
                                      const int default_dimension_value ) const
{
  QList<QVariant> dimension_data =
    d_properties_file.value( property_path ).toList();

  if( dimension_data.size() == 0 )
  {
    QString dimension_data_string =
      d_properties_file.value( property_path ).toString();

    dimension_data << dimension_data_string;
  }
  
  for( int i = 0; i < dimension_data.size(); ++i )
  {
    QStringList element_data = dimension_data[i].toString().split( ':' );
    
    // This is a range element
    if( element_data.front().contains( '-' ) )
    {
      QStringList range_bounds = element_data.front().split( '-' );
      
      if( range_bounds.front().toInt() <= frame_index &&
          range_bounds.back().toInt() >= frame_index )
        return element_data.back().toInt();
    }
    // There is a single frame index
    else
    {
      if( element_data.front().toInt() == frame_index )
        return element_data.back().toInt();
    }
  }

  // The frame uses the default dimension value
  return default_dimension_value;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end ImageProperties.cpp
//---------------------------------------------------------------------------//
