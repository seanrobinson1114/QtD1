//---------------------------------------------------------------------------//
//!
//! \file   MPQProperties.cpp
//! \author Alex Robinson
//! \brief  MPQ Properties definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include "MPQProperties.h"
#include "qtd1_config.h"

namespace QtD1{

// Constructor
MPQProperties::MPQProperties()
  : d_properties_file( MPQ_PROPERTIES_PATH, QSettings::IniFormat )
{ /* ... */ }

// Check if the file has properties
bool MPQProperties::doesFileHaveProperties( const QString& file_name ) const
{
  return d_properties_file.contains( file_name + "/path" );
}

// Get the file path in the MPQ file
QString MPQProperties::getFilePath( const QString& file_name ) const
{
  return d_properties_file.value( file_name + "/path" ).toString();
}

// Get all of the file paths (file path plus file
/*! \details To get all file paths associated with cel files a valid 
 * regular expression would be ".*.cel".
 */
QStringList MPQProperties::getFilePaths( const QRegExp& regex ) const
{
  QStringList file_names = d_properties_file.allKeys();

  QStringList::const_iterator file_name_it, file_name_end;
  file_name_it = file_names.begin();
  file_name_end = file_names.end();
  
  // Get all of the sections
  QStringList file_names_with_paths;

  while( file_name_it != file_name_end )
  {
    QString file_name_with_path =
      d_properties_file.value( *file_name_it ).toString();
    
    if( file_name_with_path.contains( regex ) )
      file_names_with_paths.push_back( file_name_with_path );
    
    ++file_name_it;
  }

  return file_names_with_paths;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MPQProperties.cpp
//---------------------------------------------------------------------------//
