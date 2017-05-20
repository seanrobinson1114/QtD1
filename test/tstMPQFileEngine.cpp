//---------------------------------------------------------------------------//
//!
//! \file   tstMPQFileEngine.cpp
//! \author Alex Robinson
//! \brief  The MPQ file engine unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "MPQFileEngine.h"

//---------------------------------------------------------------------------//
// Test suite.
class TestMPQFileEngine : public QObject
{
  Q_OBJECT

private slots:

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the file can be opened in the desired mode
void open()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( 100, 0 );

  QtD1::MPQFileEngine file( filenames, file_data );

  QVERIFY( !file.open( QIODevice::WriteOnly ) );
  QVERIFY( file.open( QIODevice::ReadWrite ) );
  QVERIFY( !file.open( QIODevice::Append ) );
  QVERIFY( !file.open( QIODevice::Truncate ) );
  QVERIFY( file.open( QIODevice::ReadOnly ) );
}

//---------------------------------------------------------------------------//
// Check that the file can be closed
void close()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( 100, 0 );

  QtD1::MPQFileEngine file( filenames, file_data );

  file.open( QIODevice::ReadOnly );

  QVERIFY( file.close() );
}

//---------------------------------------------------------------------------//
// Check if the device is sequential
void isSequential()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( 100, 0 );

  QtD1::MPQFileEngine file( filenames, file_data );

  // MPQ files are not sequential
  QVERIFY( !file.isSequential() );
}

//---------------------------------------------------------------------------//
// Check if the file system is case sensitive
void caseSensitive()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( 100, 0 );

  QtD1::MPQFileEngine file( filenames, file_data );

  // The MPQ file system is case sensitive
  QVERIFY( file.caseSensitive() );
}

//---------------------------------------------------------------------------//
// Check if the file has a relative path
void isRelativePath()
{
  // Single file with relative path
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( 100, 0 );

  std::unique_ptr<QtD1::MPQFileEngine>
    file( new QtD1::MPQFileEngine( filenames, file_data ) );

  QVERIFY( file->isRelativePath() );

  // Single file with absolute path
  filenames.clear();
  filenames << "/ui_art/title.pcx";

  file.reset( new QtD1::MPQFileEngine( filenames, file_data ) );

  QVERIFY( !file->isRelativePath() );

  // Two files with relative paths
  filenames.clear();
  filenames << "levels/towndata/town.cel" << "levels/towndata/town.pal";

  file.reset( new QtD1::MPQFileEngine( filenames, file_data ) );

  QVERIFY( file->isRelativePath() );

  // One file with absolute path, one file with absolute path
  filenames.clear();
  filenames << "/levels/towndata/town.cel" << "levels/towndata/town.pal";

  file.reset( new QtD1::MPQFileEngine( filenames, file_data ) );

  QVERIFY( !file->isRelativePath() );

  // Two files with absolute paths
  filenames.clear();
  filenames << "/levels/towndata/town.cel" << "/levels/towndata/town.pal";

  file.reset( new QtD1::MPQFileEngine( filenames, file_data ) );

  QVERIFY( !file->isRelativePath() );
}

//---------------------------------------------------------------------------//
// Check that the file name can be returned in the desired format
void fileName_single()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( 100, 0 );

  QtD1::MPQFileEngine file( filenames, file_data );
  
  QString file_name = file.fileName( QAbstractFileEngine::DefaultName );

  QCOMPARE( file_name, QString("ui_art/title.pcx") );

  file_name = file.fileName( QAbstractFileEngine::BaseName );

  QCOMPARE( file_name, QString("title.pcx") );

  file_name = file.fileName( QAbstractFileEngine::PathName );

  QCOMPARE( file_name, QString("ui_art") );

  file_name = file.fileName( QAbstractFileEngine::AbsoluteName );

  QCOMPARE( file_name, QString("ui_art/title.pcx") );

  file_name = file.fileName( QAbstractFileEngine::AbsolutePathName );

  QCOMPARE( file_name, QString("ui_art") );

  file_name = file.fileName( QAbstractFileEngine::LinkName );

  QCOMPARE( file_name, QString("ui_art/title.pcx") );

  file_name = file.fileName( QAbstractFileEngine::CanonicalName );

  QCOMPARE( file_name, QString("ui_art/title.pcx") );

  file_name = file.fileName( QAbstractFileEngine::CanonicalPathName );

  QCOMPARE( file_name, QString("ui_art/title.pcx") );

  file_name = file.fileName( QAbstractFileEngine::BundleName );

  QCOMPARE( file_name, QString("ui_art/title.pcx") );
}

//---------------------------------------------------------------------------//
// Check that the file name can be returned in the desired format
void fileName_multiple()
{
  QStringList filenames;
  filenames << "levels/towndata/town.cel" << "levels/towndata/town.pal";

  QByteArray file_data( 100, 0 );

  QtD1::MPQFileEngine file( filenames, file_data );

  QString file_name = file.fileName( QAbstractFileEngine::DefaultName );

  QCOMPARE( file_name,
            QString("levels/towndata/town.cel+levels/towndata/town.pal") );

  file_name = file.fileName( QAbstractFileEngine::BaseName );

  QCOMPARE( file_name, QString("town.cel+town.pal") );

  file_name = file.fileName( QAbstractFileEngine::PathName );

  QCOMPARE( file_name,
            QString("levels/towndata+levels/towndata") );

  file_name = file.fileName( QAbstractFileEngine::AbsoluteName );

  QCOMPARE( file_name,
            QString("levels/towndata/town.cel+levels/towndata/town.pal") );

  file_name = file.fileName( QAbstractFileEngine::AbsolutePathName );

  QCOMPARE( file_name,
            QString("levels/towndata+levels/towndata") );

  file_name = file.fileName( QAbstractFileEngine::LinkName );

  QCOMPARE( file_name,
            QString("levels/towndata/town.cel+levels/towndata/town.pal") );

  file_name = file.fileName( QAbstractFileEngine::CanonicalName );

  QCOMPARE( file_name,
            QString("levels/towndata/town.cel+levels/towndata/town.pal") );

  file_name = file.fileName( QAbstractFileEngine::CanonicalPathName );

  QCOMPARE( file_name,
            QString("levels/towndata/town.cel+levels/towndata/town.pal") );

  file_name = file.fileName( QAbstractFileEngine::BundleName );

  QCOMPARE( file_name,
            QString("levels/towndata/town.cel+levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// Check that the file name can be set
void setFileName()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( 100, 0 );

  QtD1::MPQFileEngine file( filenames, file_data );

  // The file name can only be set in the constructor
  file.setFileName( "dummy" );

  QString file_name = file.fileName();

  QCOMPARE( file_name, QString("ui_art/title.pcx") );
}

//---------------------------------------------------------------------------//
// Check that the size of the file can be returned
void size()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( 100, 0 );

  QtD1::MPQFileEngine file( filenames, file_data );

  QCOMPARE( file.size(), 100ll );
}

//---------------------------------------------------------------------------//
// Check that the file can be read
void read()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( "This is test data" );

  QtD1::MPQFileEngine file( filenames, file_data );

  // Read the file into a byte buffer
  QByteArray buffer( file.size(), 0 );
  qint64 bytes_read = file.read( buffer.data(), buffer.size() );

  QCOMPARE( bytes_read, 17ll );
  QCOMPARE( buffer.size(), 17 );
  QCOMPARE( QString( buffer ), QString("This is test data") );
}

//---------------------------------------------------------------------------//
// Check that a line of the file can be read
void readLine()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( "This is test data" );

  QtD1::MPQFileEngine file( filenames, file_data );

  // Read the file into a byte buffer
  QByteArray buffer( file.size(), 0 );
  qint64 bytes_read = file.readLine( buffer.data(), buffer.size() );

  QCOMPARE( bytes_read, 17ll );
  QCOMPARE( buffer.size(), 17 );
  QCOMPARE( QString( buffer ), QString("This is test data") );
}

//---------------------------------------------------------------------------//
// Check that the current file position can be returned
void pos()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( "This is test data" );

  QtD1::MPQFileEngine file( filenames, file_data );

  QCOMPARE( file.pos(), 0ll );

  // Read the first half of the file into a byte buffer
  QByteArray buffer( 4, 0 );

  file.read( buffer.data(), buffer.size() );
  QCOMPARE( file.pos(), 4ll );
  QCOMPARE( QString( buffer ), QString("This") );

  file.read( buffer.data(), buffer.size() );
  QCOMPARE( file.pos(), 8ll );
  QCOMPARE( QString( buffer ), QString(" is ") );

  file.read( buffer.data(), buffer.size() );
  QCOMPARE( file.pos(), 12ll );
  QCOMPARE( QString( buffer ), QString("test") );

  file.read( buffer.data(), buffer.size() );
  QCOMPARE( file.pos(), 16ll );
  QCOMPARE( QString( buffer ), QString(" dat") );

  buffer.fill( '-' );
  file.read( buffer.data(), buffer.size() );
  QCOMPARE( file.pos(), 17ll );
  QCOMPARE( QString( buffer ), QString("a---") );
}

//---------------------------------------------------------------------------//
// Check that a position in the file can be set
void seek()
{
  QStringList filenames;
  filenames << "ui_art/title.pcx";

  QByteArray file_data( "This is test data" );

  QtD1::MPQFileEngine file( filenames, file_data );

  char pos_value;
  
  // Go to index 4
  QVERIFY( file.seek( 4 ) );
  QCOMPARE( file.pos(), 4ll );

  file.read( &pos_value, 1 );

  QCOMPARE( pos_value, ' ' );

  // Go to index 8
  QVERIFY( file.seek( 8 ) );
  QCOMPARE( file.pos(), 8ll );
  
  file.read( &pos_value, 1 );

  QCOMPARE( pos_value, 't' );

  // Go to index 12
  QVERIFY( file.seek( 12 ) );
  QCOMPARE( file.pos(), 12ll );

  file.read( &pos_value, 1 );

  QCOMPARE( pos_value, ' ' );

  // Go to index 16
  QVERIFY( file.seek( 16 ) );
  QCOMPARE( file.pos(), 16ll );

  file.read( &pos_value, 1 );

  QCOMPARE( pos_value, 'a' );
  
  // Go to the end of the file
  QVERIFY( file.seek( file.size() ) );
  QCOMPARE( file.pos(), file.size() );

  // Go to the beginning of the file
  QVERIFY( file.seek( 0 ) );
  QCOMPARE( file.pos(), 0ll );

  file.read( &pos_value, 1 );

  QCOMPARE( pos_value, 'T' );
}

//---------------------------------------------------------------------------//
// End test suite
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestMPQFileEngine )
#include "tstMPQFileEngine.moc"

//---------------------------------------------------------------------------//
// end tstMPQFileEngine.cpp
//---------------------------------------------------------------------------//
