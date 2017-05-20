//---------------------------------------------------------------------------//
//!
//! \file   MPQHandler.cpp
//! \author Alex Robinson
//! \brief  MPQ handler class definition
//!
//---------------------------------------------------------------------------//

// Storm Lib Includes
#include <StormLib.h>

// Qt Includes
#include <QBuffer>

// QtD1 Includes
#include "MPQHandler.h"
#include "CustomMPQFileHeader.h"
#include "qtd1_config.h"

namespace QtD1{

// Initialize static member data
std::unique_ptr<MPQHandler> MPQHandler::s_instance;

// Get the singleton instance
MPQHandler* MPQHandler::getInstance()
{
  // Just-in-time initialization
  if( !s_instance )
    s_instance.reset( new MPQHandler );

  return s_instance.get();
}

// Constructor
MPQHandler::MPQHandler()
  : QAbstractFileEngineHandler(),
    d_mpq_file( 0 )
{
  // Open the MPQ file
  HANDLE mpq_file_handle;
  
  const bool mpq_file_opened = SFileOpenArchive( DIABDAT_MPQ_PATH,
                                                 0,
                                                 STREAM_FLAG_READ_ONLY,
                                                 &mpq_file_handle );

  // Make sure the MPQ file opened successfully
  if( !mpq_file_opened )
  {
    qFatal( "Error: The MPQ file (%s) could not be opened!\n"
            "StormLib error code: %i",
            DIABDAT_MPQ_PATH,
            GetLastError() );
  }

  d_mpq_file = reinterpret_cast<uintptr_t>( mpq_file_handle );
}

// Destructor
MPQHandler::~MPQHandler()
{
  HANDLE mpq_file_handle = reinterpret_cast<HANDLE>( d_mpq_file );
  
  SFileCloseArchive( mpq_file_handle );

  d_mpq_file = 0;
}

// Check if the file (with path) exists in the mpq file
bool MPQHandler::doesFileExist( const QString& file_name_with_path ) const
{
  QString compatible_file_name_with_path = file_name_with_path;

  this->cleanFilePath( compatible_file_name_with_path );
  this->convertPathStyleToMPQPathStyle( compatible_file_name_with_path );

  return this->doesFileWithMPQPathStyleExist( compatible_file_name_with_path );
}

// Check if the concatenated files (with paths) exist in the mpq file
bool MPQHandler::doFilesExist( const QString& file_names_with_paths ) const
{
  QStringList extracted_file_names_with_paths;

  this->extractFileNamesWithCleanPaths( file_names_with_paths,
                                        extracted_file_names_with_paths );

  for( int i = 0; i < extracted_file_names_with_paths.size(); ++i )
  {
    this->convertPathStyleToMPQPathStyle( extracted_file_names_with_paths[i] );
    
    if( !this->doesFileWithMPQPathStyleExist( extracted_file_names_with_paths[i] ) )
      return false;
  }
    
  return true;
}

// Check if the file (with mpq path style) exists in the mpq file
bool MPQHandler::doesFileWithMPQPathStyleExist(
                                     const QString& file_name_with_path ) const
{
  return SFileHasFile( (HANDLE)d_mpq_file,
                       file_name_with_path.toStdString().c_str() );
}

// Open a file (automatic garbage collection = safe)
/*! \details If the file(s) does(do) not exist a std::exception will be thrown.
 * If multiple files are present their contents will be concatenated and
 * a header will be added that indicates where each file begins in the
 * file buffer. 
 */
std::shared_ptr<MPQFileEngine> MPQHandler::createSafeWithCheck(
                                   const QString& file_names_with_paths ) const
{
  return std::shared_ptr<MPQFileEngine>(
                              this->createWithCheck( file_names_with_paths ) );
}

// Open a file 
/*! \details The caller will take ownership of the returned pointer and
 * must free it when it is no longer needed to prevent a memory leak. If the
 * file(s) does(do) not exist a std::exception will be thrown. If multiple 
 * files are present their contents will be concatenated and a header will be 
 * added that indicates where each file begins in the file buffer.
 */
MPQFileEngine* MPQHandler::createWithCheck(
                                   const QString& file_names_with_paths ) const
{
  QByteArray combined_file_data;
  QBuffer file_buffer( &combined_file_data );
  file_buffer.open( QIODevice::WriteOnly );

  CustomMPQFileHeader header;
  
  QStringList extracted_file_names_with_paths;

  this->extractFileNamesWithCleanPaths( file_names_with_paths,
                                        extracted_file_names_with_paths );

  for( int i = 0; i < extracted_file_names_with_paths.size(); ++i )
  {
    header.addElement( extracted_file_names_with_paths[i],
                       file_buffer.pos() );
    
    QByteArray file_data;

    this->extractFile( extracted_file_names_with_paths[i], file_data );

    file_buffer.write( file_data );
  }

  file_buffer.close();

  // Only add the header if there is more than one file present
  if( extracted_file_names_with_paths.size() > 1 )
    header.addToBuffer( combined_file_data );

  return new MPQFileEngine( extracted_file_names_with_paths,
                            combined_file_data );
}

// Open a file
/*! \details If the file does not exist a null pointer will be returned 
 * (required by Qt interface).
 */
MPQFileEngine* MPQHandler::create( const QString &file_name_with_path ) const
{
  try{
    return this->createWithCheck( file_name_with_path );
  }
  catch( const std::exception& exception )
  {
    return NULL;
  }
}

// Extract a file
/*! \details This method can only extract a single file. Do not pass in 
 * a concatenated file string.
 */
void MPQHandler::extractFile( const QString& file_name_with_path,
                              QByteArray& file_data ) const
{
  QString compatible_file_name_with_path = file_name_with_path;

  this->cleanFilePath( compatible_file_name_with_path );
  this->convertPathStyleToMPQPathStyle( compatible_file_name_with_path );

  if( !this->doesFileWithMPQPathStyleExist(compatible_file_name_with_path) )
  {
    throw std::runtime_error( "Error: file %s does not exist!" + 
                              file_name_with_path.toStdString() );
  }

  HANDLE raw_archived_file;

  // Open the file
  const bool archived_file_opened =
    SFileOpenFileEx( (HANDLE)d_mpq_file,
                     compatible_file_name_with_path.toStdString().c_str(),
                     0,
                     &raw_archived_file );

  // Make sure that the archived file opened successfully
  if( !archived_file_opened )
  {
    qFatal( "Error: The archived file (%s) in the MPQ file could not be "
            "opened!",
            file_name_with_path.toStdString().c_str() );
  }

  // Resize the file
  file_data.resize( SFileGetFileSize( raw_archived_file, NULL ) );
    
  // Read the file
  SFileReadFile( raw_archived_file,
                 file_data.data(),
                 file_data.size(),
                 NULL,
                 NULL );

  // Close the raw file
  SFileCloseFile( raw_archived_file );
}

// Extract file names with clean paths
void MPQHandler::extractFileNamesWithCleanPaths(
                                   const QString& file_names_with_paths_string,
                                   QStringList& file_names_with_paths ) const
{
  file_names_with_paths =
    file_names_with_paths_string.split( MPQFileEngine::getFileConcatChar(),
                                        QString::SkipEmptyParts );

  for( int i = 0; i < file_names_with_paths.size(); ++i )
    this->cleanFilePath( file_names_with_paths[i] );
}

// Clean the file path
void MPQHandler::cleanFilePath( QString& file_name_with_path )
{
  // Remove any starting '/' characters
  while( file_name_with_path.startsWith( '/' ) )
    file_name_with_path.remove( 0, 1 );

  // Remove any trailing '/' characters
  while( file_name_with_path.endsWith( '/' ) )
    file_name_with_path.chop( 1 );
}

// Convert the path style to mpq path style
void MPQHandler::convertPathStyleToMPQPathStyle( QString& file_name_with_path )
{
  // Replace any occurance of '/' with '\'
  file_name_with_path.replace( "/", "\\", Qt::CaseSensitive );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end MPQHandler.cpp
//---------------------------------------------------------------------------//
