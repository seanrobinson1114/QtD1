//---------------------------------------------------------------------------//
//!
//! \file   tstFileInterface.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The freeable file interface class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

// Qt Includes
#include <QtTest/QtTest>
#include <QFile>

// QtD1 Includes
#include "MPQHandler.h"
#include "qtd1_test_config.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestFileInterface : public QObject
{
  Q_OBJECT

private slots:

  void initTestCase()
  {
    // Register the MPQHandler with the file engine system
    QtD1::MPQHandler::getInstance();
  }
  
//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a regular file can be opened
void regular_file()
{
  QFile file( TEST_FILE_TXT_PATH );

  QVERIFY( file.open( QIODevice::ReadOnly ) );
  QVERIFY( file.isOpen() );
  QVERIFY( file.isReadable() );
  QCOMPARE( file.size(), 39ll );

  std::vector<char> byte_buffer( file.size() );
  qint64 bytes_read;

  try{
    bytes_read = file.read( byte_buffer.data(), byte_buffer.size() );
  }
  catch( const std::exception& exception )
  {
    std::ostringstream oss;
    oss << "Could not read file " << TEST_FILE_TXT_PATH << ": "
        << exception.what();
    
    QFAIL( oss.str().c_str() );
  }
  catch( ... )
  {
    QFAIL( "Could not read file " TEST_FILE_TXT_PATH ": No further details!" );
  }
  
  QCOMPARE( bytes_read, (qint64)byte_buffer.size() );

  QVERIFY( file.seek( 0 ) );
  QCOMPARE( file.pos(), 0ll );
  QVERIFY( file.seek( file.size()/2 ) );
  QCOMPARE( file.pos(), file.size()/2 );
  
  file.close();
}

//---------------------------------------------------------------------------//
// Check that a mpq file can be opened
void single_mpq_file()
{
  QFile file( "ui_art/title.pcx" );
  
  QVERIFY( file.open( QIODevice::ReadOnly ) );
  QVERIFY( file.isOpen() );
  QVERIFY( file.isReadable() );
  QVERIFY( !file.isSequential() );
  QCOMPARE( file.size(), 80648ll );

  std::vector<char> byte_buffer( file.size() );
  qint64 bytes_read;

  try{
    bytes_read = file.read( byte_buffer.data(), byte_buffer.size() );
  }
  catch( const std::exception& exception )
  {
    std::ostringstream oss;
    oss << "Could not read mpq file ui_art/title.pcx: "
        << exception.what();

    QFAIL( oss.str().c_str() );
  }
  catch( ... )
  {
    QFAIL( "Could not read mpq file ui_art/title.pcx: No further details!" );
  }
  
  QCOMPARE( bytes_read, (qint64)byte_buffer.size() );
  QCOMPARE( file.pos(), 80648ll );
  
  QVERIFY( file.seek( 0 ) );
  QCOMPARE( file.pos(), 0ll );
  QVERIFY( file.seek( file.size()/2 ) );
  QCOMPARE( file.pos(), file.size()/2 ); 

  file.close();
}

//---------------------------------------------------------------------------//
// Check that two mpq files can be opened simultaneously
void double_mpq_file()
{
  QFile file( "/levels/towndata/town.cel+/levels/towndata/town.pal" );

  QVERIFY( file.open( QIODevice::ReadOnly ) );
  QVERIFY( file.isOpen() );
  QVERIFY( file.isReadable() );
  QVERIFY( !file.isSequential() );
  QCOMPARE( file.size(), 2176908ll );

  std::vector<char> byte_buffer( file.size() );
  qint64 bytes_read;

  try{
    bytes_read = file.read( byte_buffer.data(), byte_buffer.size() );
  }
  catch( const std::exception& exception )
  {
    std::ostringstream oss;
    oss << "Could not read mpq file "
        << "/levels/towndata/town.cel+/levels/towndata/town.pal: "
        << exception.what();

    QFAIL( oss.str().c_str() );
  }
  catch( ... )
  {
    QFAIL( "Could not read mpq file "
           "/levels/towndata/town.cel+/levels/towndata/town.pal: "
           "No further details!" );
  }
  
  QCOMPARE( bytes_read, (qint64)byte_buffer.size() );
  QCOMPARE( file.pos(), 2176908ll );
  
  QVERIFY( file.seek( 0 ) );
  QCOMPARE( file.pos(), 0ll );
  QVERIFY( file.seek( file.size()/2 ) );
  QCOMPARE( file.pos(), file.size()/2 ); 

  file.close();
}

//---------------------------------------------------------------------------//
// Check that a file can be reopened with a new file type
void regular_to_mpq_file()
{
  QFile file( TEST_FILE_TXT_PATH );

  QVERIFY( file.open( QIODevice::ReadOnly ) );
  QVERIFY( file.isOpen() );
  QVERIFY( file.isReadable() );
  QCOMPARE( file.size(), 39ll );

  file.close();

  file.setFileName( "ui_art/title.pcx/" );

  QVERIFY( file.open( QIODevice::ReadOnly ) );
  QVERIFY( file.isOpen() );
  QVERIFY( file.isReadable() );
  QVERIFY( !file.isSequential() );
  QCOMPARE( file.size(), 80648ll );

  file.close();
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestFileInterface )
#include "tstFileInterface.moc"

//---------------------------------------------------------------------------//
// end tstFileInterface.cpp
//---------------------------------------------------------------------------//
