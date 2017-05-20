//---------------------------------------------------------------------------//
//!
//! \file   MPQFileEngine.cpp
//! \author Alex Robinson
//! \brief  MPQ file engine class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <iostream>
#include <cstring>

// Qt Includes
#include <QLatin1String>

// QtD1 Includes
#include "MPQFileEngine.h"
#include "MPQHandler.h"

namespace QtD1{

// Constructor
MPQFileEngine::MPQFileEngine( const QStringList& filenames,
                              const QByteArray& file_data )
  : d_file_names( filenames ),
    d_file_data( file_data ),
    d_file_data_pos( 0 )
{ /* ... */ }

// Destructor
MPQFileEngine::~MPQFileEngine()
{ /* ... */ }

// Get the file concatenation character
char MPQFileEngine::getFileConcatChar()
{
  return '+';
}

// Open the file in the desired mode
bool MPQFileEngine::open( QIODevice::OpenMode open_mode )
{
  if( !(open_mode & QIODevice::ReadOnly) )
  {
    qWarning( "MPQFileEngine::open: only QIODevice::ReadOnly supported!" );
    this->setError( QFile::OpenError, QLatin1String( "Invalid open mode" ) );
    
    return false;
  }

  return true;
}

// Close the file
/*! \details The file data is cached - there is nothing to actually close.
 */
bool MPQFileEngine::close()
{
  return true;
}
  
// Return the size of the file
qint64 MPQFileEngine::size() const
{
  return d_file_data.size();
}

// Return the current file position
qint64 MPQFileEngine::pos() const
{
  return d_file_data_pos;
}

// Set the file position to the given offset (from the beginning of the file)
bool MPQFileEngine::seek( qint64 offset )
{
  if( offset <= d_file_data.size() )
  {
    d_file_data_pos = offset;

    return true;
  }
  else
    return false;
}

// This device is not sequential
bool MPQFileEngine::isSequential() const
{
  return false;
}

// This file system is case sensitive
bool MPQFileEngine::caseSensitive() const
{
  return true;
}

// Check if the file has a relative path
/*! \details All of the paths must be relative for this to return true
 */
bool MPQFileEngine::isRelativePath() const
{
  for( int i = 0; i < d_file_names.size(); ++i )
  {
    if( d_file_names[i][0] == '/' )
      return false;
  }

  return true;
}

// Return the file name in the desired format
/*! \details All of the file names will be returned as a concatenated list
 * in the desired format.
 */
QString MPQFileEngine::fileName( FileName file ) const
{
  QString concatenated_file_names;

  for( int i = 0; i < d_file_names.size(); ++i )
  {
    QStringList file_components =
      d_file_names[i].split( '/', QString::SkipEmptyParts );
    
    if( file == BaseName )
      concatenated_file_names.append( file_components.back() );
    else if( file == PathName || file == AbsolutePathName )
    {
      QString all_but_name;
      
      for( int i = 0; i < file_components.size()-1; ++i )
      {
        all_but_name += file_components[i];
        
        if( i < file_components.size()-2 )
          all_but_name += '/';
      }
      
      concatenated_file_names.append( all_but_name );
    }
    else
      concatenated_file_names.append( d_file_names[i] );

    if( i < d_file_names.size() - 1 )
      concatenated_file_names.append( this->getFileConcatChar() );
  }
    
  return concatenated_file_names;
}

// Set the file name that will be used by the engine
/*! \details The file name cannot be reset.
 */
void MPQFileEngine::setFileName( const QString& )
{
  qWarning( "MPQFileEngine::setFileName: cannot set the filename "
            "outside of the constructor!" );
  this->setError( QFile::AbortError,
                  QLatin1String( "Cannot reset filename" ) );
}

// Get the file handle used by this engine
/*! \details The handle type can't be cast to an int so the handle will not
 * be returned by this method.
 */
int MPQFileEngine::handle() const
{
  return 0;
}

// Read data from the file
qint64 MPQFileEngine::read( char* data, qint64 maxlen )
{
  // Calculate the number of bytes to read
  qint64 bytes_to_read =
    std::min( maxlen, d_file_data.size() - d_file_data_pos );

  if( bytes_to_read > 0 )
    memcpy( data, d_file_data.constData()+d_file_data_pos, bytes_to_read );

  // Set the position
  d_file_data_pos += bytes_to_read;

  return bytes_to_read;
}

// Read a line of data from the file
qint64 MPQFileEngine::readLine( char* data, qint64 maxlen )
{
  return this->read( data, maxlen );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MPQFileEngine.cpp
//---------------------------------------------------------------------------//
