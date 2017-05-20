//---------------------------------------------------------------------------//
//!
//! \file   tstMPQHandler.cpp
//! \author Alex Robinson
//! \brief  The MPQHandler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "MPQHandler.h"
#include "MPQProperties.h"
#include "CustomMPQFileHeader.h"
#include "qtd1_config.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestMPQHandler : public QObject
{
  Q_OBJECT

private slots:

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the MPQHandler can be initialized (just-in-time)
void constructor()
{
  try{
    QtD1::MPQHandler::getInstance();
  }
  catch( const std::exception& exception )
  {
    std::ostringstream oss;
    oss << "Could not load the mpq handler: "
        << exception.what();

    QFAIL( oss.str().c_str() );
  }
  catch( ... )
  {
    QFAIL( "Could not load the mpq handler: No further details!" );
  }

  QVERIFY( true );
}

//---------------------------------------------------------------------------//
// Check for file existance with the MPQHandler
void doesFileExist()
{
  QtD1::MPQProperties mpq_properties;
  
  QStringList files = mpq_properties.getFilePaths();

  const QtD1::MPQHandler* mpq_handler =
    QtD1::MPQHandler::getInstance();

  const char* basic_error_message = "The mpq file does not contain file ";

  for( int i = 0; i < files.size(); ++i )
  {
    QString detailed_error_message( basic_error_message );
    detailed_error_message += files[i];
    
    QVERIFY2( mpq_handler->doesFileExist( files[i] ),
              detailed_error_message.toStdString().c_str() );
  }
}

//---------------------------------------------------------------------------//
// Check that file engines can be created
void createWithCheck_single()
{
  const QtD1::MPQHandler* mpq_handler =
    QtD1::MPQHandler::getInstance();

  QAbstractFileEngine* archived_file;

  // Check that a relative path can be used
  try{
    archived_file = mpq_handler->createWithCheck( "ui_art/title.pcx" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 80648ll );

  // Check that there is no header
  QByteArray buffer( archived_file->size(), 0 );
  archived_file->read( buffer.data(), buffer.size() );

  qint64 data_start_index;
  QtD1::CustomMPQFileHeader header =
    QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );
  QCOMPARE( header.getNumElements(), 0 );
  QCOMPARE( data_start_index, 0ll );

  delete archived_file;
  
  // Check that a relative path with trailing '/' can be used
  try{
    archived_file = mpq_handler->createWithCheck( "ui_art/title.pcx/" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }

  QCOMPARE( archived_file->size(), 80648ll );

  // Check that there is no header
  buffer.fill( 0, archived_file->size() );
  archived_file->read( buffer.data(), buffer.size() );

  header = QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );
  QCOMPARE( header.getNumElements(), 0 );
  QCOMPARE( data_start_index, 0ll );

  delete archived_file;
  
  // Check that an absolute path can be used
  try{
    archived_file = mpq_handler->createWithCheck( "/ui_art/title.pcx" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }

  QCOMPARE( archived_file->size(), 80648ll );

  // Check that there is no header
  buffer.fill( 0, archived_file->size() );
  archived_file->read( buffer.data(), buffer.size() );

  header = QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );
  QCOMPARE( header.getNumElements(), 0 );
  QCOMPARE( data_start_index, 0ll );

  delete archived_file;

  // Check that an absolute path with trailing '/' can be used
  try{
    archived_file = mpq_handler->createWithCheck( "/ui_art/title.pcx/" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 80648ll );

  // Check that there is no header
  buffer.fill( 0, archived_file->size() );
  archived_file->read( buffer.data(), buffer.size() );

  header = QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );
  QCOMPARE( header.getNumElements(), 0 );
  QCOMPARE( data_start_index, 0ll );

  delete archived_file;

  // Check that an invalid file will cause an exception to be thrown
  bool exception_thrown = false;
  
  try{
    archived_file = mpq_handler->createWithCheck( "dummy" );
  }
  catch( const std::runtime_error& error )
  {
    exception_thrown = true;
  }

  QVERIFY( exception_thrown );
}

//---------------------------------------------------------------------------//
// Check that file engines can be created
void createWithCheck_multiple()
{
  const QtD1::MPQHandler* mpq_handler =
    QtD1::MPQHandler::getInstance();

  QAbstractFileEngine* archived_file;

  // Check that relative paths can be used
  try{
    archived_file = mpq_handler->createWithCheck( "levels/towndata/town.cel+levels/towndata/town.pal" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 2176916ll );

  // Check that there is a header
  QByteArray buffer( archived_file->size(), 0 );
  archived_file->read( buffer.data(), buffer.size() );

  qint64 data_start_index;
  QtD1::CustomMPQFileHeader header =
    QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );
  QCOMPARE( header.getNumElements(), 2 );
  QCOMPARE( header[0].filename, QString("levels/towndata/town.cel") );
  QCOMPARE( header[0].start_location, 0ll );
  QCOMPARE( header[1].filename, QString("levels/towndata/town.pal") );
  QCOMPARE( header[1].start_location, 2176004ll );
  QCOMPARE( data_start_index, 144ll );

  delete archived_file;

  // Check that relative paths with trailing '/' can be used
  try{
    archived_file = mpq_handler->createWithCheck( "levels/towndata/town.cel/+levels/towndata/town.pal/" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 2176916ll );

  // Check that there is a header
  buffer.fill( 0, archived_file->size() );
  archived_file->read( buffer.data(), buffer.size() );
  header = QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );

  QCOMPARE( header.getNumElements(), 2 );
  QCOMPARE( header[0].filename, QString("levels/towndata/town.cel") );
  QCOMPARE( header[0].start_location, 0ll );
  QCOMPARE( header[1].filename, QString("levels/towndata/town.pal") );
  QCOMPARE( header[1].start_location, 2176004ll );
  QCOMPARE( data_start_index, 144ll );

  delete archived_file;

  // Check that absolute paths can be used
  try{
    archived_file = mpq_handler->createWithCheck( "/levels/towndata/town.cel+/levels/towndata/town.pal" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 2176916ll );

  // Check that there is a header
  buffer.fill( 0, archived_file->size() );
  archived_file->read( buffer.data(), buffer.size() );
  header = QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );

  QCOMPARE( header.getNumElements(), 2 );
  QCOMPARE( header[0].filename, QString("levels/towndata/town.cel") );
  QCOMPARE( header[0].start_location, 0ll );
  QCOMPARE( header[1].filename, QString("levels/towndata/town.pal") );
  QCOMPARE( header[1].start_location, 2176004ll );
  QCOMPARE( data_start_index, 144ll );

  delete archived_file;

  // Check that absolute paths with trailing '/' can be used
  try{
    archived_file = mpq_handler->createWithCheck( "/levels/towndata/town.cel/+/levels/towndata/town.pal/" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 2176916ll );

  // Check that there is a header
  buffer.fill( 0, archived_file->size() );
  archived_file->read( buffer.data(), buffer.size() );
  header = QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );

  QCOMPARE( header.getNumElements(), 2 );
  QCOMPARE( header[0].filename, QString("levels/towndata/town.cel") );
  QCOMPARE( header[0].start_location, 0ll );
  QCOMPARE( header[1].filename, QString("levels/towndata/town.pal") );
  QCOMPARE( header[1].start_location, 2176004ll );
  QCOMPARE( data_start_index, 144ll );

  delete archived_file;

  // Check that mixed paths can be used
  try{
    archived_file = mpq_handler->createWithCheck( "levels/towndata/town.cel//+//levels/towndata/town.pal" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 2176916ll );

  // Check that there is a header
  buffer.fill( 0, archived_file->size() );
  archived_file->read( buffer.data(), buffer.size() );
  header = QtD1::CustomMPQFileHeader::extractFromBuffer( buffer, data_start_index );

  QCOMPARE( header.getNumElements(), 2 );
  QCOMPARE( header[0].filename, QString("levels/towndata/town.cel") );
  QCOMPARE( header[0].start_location, 0ll );
  QCOMPARE( header[1].filename, QString("levels/towndata/town.pal") );
  QCOMPARE( header[1].start_location, 2176004ll );
  QCOMPARE( data_start_index, 144ll );

  delete archived_file;

  // Check that an invalid file will cause an exception to be thrown
  bool exception_thrown = false;
  
  try{
    archived_file = mpq_handler->createWithCheck( "dummy+levels/towndata/town.pal" );
  }
  catch( const std::runtime_error& error )
  {
    exception_thrown = true;
  }

  QVERIFY( exception_thrown );

  exception_thrown = false;

  try{
    archived_file = mpq_handler->createWithCheck( "levels/towndata/town.cel+dummy" );
  }
  catch( const std::runtime_error& error )
  {
    exception_thrown = true;
  }

  QVERIFY( exception_thrown );
}

//---------------------------------------------------------------------------//
// Check that file engines can be created
void create()
{
  const QtD1::MPQHandler* mpq_handler =
    QtD1::MPQHandler::getInstance();

  QAbstractFileEngine* archived_file =
    mpq_handler->create( "ui_art/title.pcx" );
  
  QVERIFY( archived_file != NULL );
  QCOMPARE( archived_file->size(), 80648ll );
  
  delete archived_file;

  archived_file = mpq_handler->create( "levels/towndata/town.cel+levels/towndata/town.pal" );
  QVERIFY( archived_file != NULL );
  QCOMPARE( archived_file->size(), 2176916ll );

  // Failure to create an engine should result in a null pointer return
  archived_file = mpq_handler->create( "dummy" );
  
  QVERIFY( archived_file == NULL );
}

//---------------------------------------------------------------------------//
// Check that file engines can be created safely
void createSafeWithCheck()
{
  const QtD1::MPQHandler* mpq_handler =
    QtD1::MPQHandler::getInstance();

  std::shared_ptr<QtD1::MPQFileEngine> archived_file;

  try{
    archived_file = mpq_handler->createSafeWithCheck( "ui_art/title.pcx" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 80648ll );

  try{
    archived_file = mpq_handler->createSafeWithCheck( "levels/towndata/town.cel+levels/towndata/town.pal" );
  }
  catch( ... )
  {
    QFAIL( "The abstract file engine could not be created!" );
  }
  
  QCOMPARE( archived_file->size(), 2176916ll );

  // Failure to create an engine should result in an exception
  bool exception_thrown = false;
  
  try{
    archived_file = mpq_handler->createSafeWithCheck( "dummy" );
  }
  catch( const std::runtime_error& error )
  {
    exception_thrown = true;
  }

  QVERIFY( exception_thrown );
}

//---------------------------------------------------------------------------//
// Check that archived files can be extracted
void extractFile()
{
  QtD1::MPQProperties mpq_properties;
  
  QStringList files = mpq_properties.getFilePaths();

  const QtD1::MPQHandler* mpq_handler =
    QtD1::MPQHandler::getInstance();

  QByteArray file_buffer;

  for( int i = 0; i < files.size(); ++i )
  {
    if( i % 100 == 0 )
      std::cout << "." << std::flush;

    try{
      mpq_handler->extractFile( files[i], file_buffer );
    }
    catch( const std::exception& exception )
    {
      std::ostringstream oss;
      oss << "Could not extract the mpq file: " << exception.what();

      QFAIL( oss.str().c_str() );
    }
    catch( ... )
    {
      QFAIL( "Could not extract the mpq file: No further details!" );
    }

    QString fail_message( "File " );
    fail_message += files[i];
    fail_message += " is empty!";
  
    QVERIFY2( file_buffer.size() > 0, fail_message.toStdString().c_str() );
    file_buffer.clear();
  }
  std::cout << std::endl;
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestMPQHandler )
#include "tstMPQHandler.moc"


//---------------------------------------------------------------------------//
// end tstMPQHandler.cpp
//---------------------------------------------------------------------------//
