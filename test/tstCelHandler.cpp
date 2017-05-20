//---------------------------------------------------------------------------//
//!
//! \file   tstCelHandler.cpp
//! \author Alex Robinson
//! \brief  The cel handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>
#include <QFile>
#include <QBuffer>
#include <QImage>
#include <QtPlugin>

// QtD1 Includes
#include "CelHandler.h"
#include "CelImageProperties.h"
#include "Cl2ImageProperties.h"
#include "MPQProperties.h"
#include "MPQHandler.h"
#include "qtd1_test_config.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestCelHandler : public QObject
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
// Check that the handler can read a cel file
void canRead_static()
{
  const QtD1::MPQProperties properties;

  // Check all .cel files
  QStringList cel_files = properties.getFilePaths( ".*\\.cel" );

  for( int i = 0; i < cel_files.size(); ++i )
  {
    QFile cel_file( cel_files[i] );

    QVERIFY( QtD1::CelHandler::canRead( &cel_file ) );
  }

  // Check all .cl2 files
  QStringList cl2_files = properties.getFilePaths( ".*\\.cl2" );
  
  for( int i = 0; i < cl2_files.size(); ++i )
  {
    QFile cl2_file( cl2_files[i] );

    QVERIFY( QtD1::CelHandler::canRead( &cl2_file ) );
  }

  // Check that it cannot read a non-cel files
  QFile txt_file( TEST_FILE_TXT_PATH );

  QVERIFY( !QtD1::CelHandler::canRead( &txt_file ) );

  QByteArray dummy_data( 10, 0 );
  QBuffer dummy_buffer( &dummy_data );

  QVERIFY( !QtD1::CelHandler::canRead( &dummy_buffer ) );
}

//---------------------------------------------------------------------------//
// Check that the handler can read a cel file
void canRead()
{
  const QtD1::MPQProperties properties;

  std::unique_ptr<QImageIOHandler> handler( new QtD1::CelHandler );

  // Check all .cel files
  QStringList cel_files = properties.getFilePaths( ".*\\.cel" );

  for( int i = 0; i < cel_files.size(); ++i )
  {
    QFile cel_file( cel_files[i] );

    handler->setDevice( &cel_file );

    QVERIFY( handler->canRead() );
  }

  // Check all .cl2 files
  QStringList cl2_files = properties.getFilePaths( ".*\\.cl2" );

  for( int i = 0; i < cl2_files.size(); ++i )
  {
    QFile cl2_file( cl2_files[i] );

    handler->setDevice( &cl2_file );

    QVERIFY( handler->canRead() );
  }

  // Check that it cannot read a non-cel files
  QFile txt_file( TEST_FILE_TXT_PATH );

  handler->setDevice( &txt_file );

  QVERIFY( !handler->canRead() );

  QByteArray dummy_data( 10, 0 );
  QBuffer dummy_buffer( &dummy_data );

  handler->setDevice( &dummy_buffer );

  QVERIFY( !handler->canRead() );
}

//---------------------------------------------------------------------------//
// Check that the image frames can be loaded
void loadImageFrames_cel()
{
  const QtD1::MPQProperties properties;

  // Load all .cel files
  QStringList cel_files = properties.getFilePaths( ".*\\.cel" );

  std::unique_ptr<QtD1::CelHandler> handler( new QtD1::CelHandler );

  for( int i = 0; i < cel_files.size(); ++i )
  {
    // Get the palettes for this file
    QStringList file_name_components = cel_files[i].split( '/' );
    
    QStringList palette_files;
    QtD1::CelImageProperties::getInstance()->getPaletteFileNames(
                                  file_name_components.back(), palette_files );

    // Construct the cel file name with palette file name
    QString concatenated_file_name =
      cel_files[i] + "+" + palette_files.front();

    std::cout << i << ": " << concatenated_file_name.toStdString() << std::endl;

    QFile cel_file( concatenated_file_name );

    handler->setDevice( &cel_file );

    // Check that the image frames can be loaded - failure will result in
    // a qFatal message
    handler->loadImageFrames();
    
    QVERIFY( handler->imageCount() >= 1 );

    handler.reset( new QtD1::CelHandler );
  }
}

//---------------------------------------------------------------------------//
// Check that the image frames can be loaded
void loadImageFrames_cl2()
{
  const QtD1::MPQProperties properties;

  // Load all .cl2 files
  QStringList cl2_files = properties.getFilePaths( ".*\\.cl2" );

  std::unique_ptr<QtD1::CelHandler> handler( new QtD1::CelHandler );

  for( int i = 0; i < cl2_files.size(); ++i )
  {
    // Get the palettes for this file
    QStringList file_name_components = cl2_files[i].split( '/' );
    
    QStringList palette_files;
    QtD1::CelImageProperties::getInstance()->getPaletteFileNames(
                                  file_name_components.back(), palette_files );

    // Construct the cel file name with palette file name
    QString concatenated_file_name =
      cl2_files[i] + "+" + palette_files.front();

    QFile cl2_file( concatenated_file_name );
    
    handler->setDevice( &cl2_file );

    // Check that the image frames can be loaded - failure will result in
    // a qFatal message
    handler->loadImageFrames();
    
    QVERIFY( handler->imageCount() >= 1 );
  }
}

//---------------------------------------------------------------------------//
// Check that cel images can be read from the handler
void read()
{
  // Load PentSpin.cel
  std::unique_ptr<QtD1::CelHandler> handler( new QtD1::CelHandler );

  QFile file( "data/PentSpin.cel+levels/towndata/town.pal" );

  handler->setDevice( &file );
  handler->loadImageFrames();

  QCOMPARE( handler->imageCount(), 8 );

  for( int i = 0; i < handler->imageCount(); ++i )
  {
    QImage image;
    
    handler->read( &image );

    if( i < handler->imageCount() - 1 )
      QVERIFY( handler->jumpToNextImage() );
    else
      QVERIFY( !handler->jumpToNextImage() );

    QCOMPARE( image.width(), 48 );
    QCOMPARE( image.height(), 48 );
  }

  QVERIFY( handler->jumpToImage( 0 ) );
  QVERIFY( handler->jumpToImage( 7 ) );
  QVERIFY( !handler->jumpToImage( 8 ) );
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestCelHandler )
#include "tstCelHandler.moc"

//---------------------------------------------------------------------------//
// end tstCelHandler.cpp
//---------------------------------------------------------------------------//
