//---------------------------------------------------------------------------//
//!
//! \file   tstCelDecoder.cpp
//! \author Sean Robinson
//! \brief  The cel decoder unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "CelDecoder.h"
#include "CelPalette.h"
#include "CelImageProperties.h"
#include "Cl2ImageProperties.h"
#include "MPQProperties.h"
#include "MPQHandler.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestCelDecoder : public QObject
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
// Check that a cel decoder can be constructed with all .cel files
void constructor_cel()
{
  QtD1::MPQProperties properties;

  // Load all .cel files
  QStringList cel_files = properties.getFilePaths( ".*\\.cel" );

  for( int i = 0; i < cel_files.size(); ++i )
  {
    // Make sure CelDecoder can be constructed with each file - failure
    // will result in a qFatal message.
    QtD1::CelDecoder decoder( cel_files[i] );

    QVERIFY( true );
  }
}

//---------------------------------------------------------------------------//
// Check image data can be decoded
void decode_cel()
{
  QtD1::MPQProperties properties;

  
  // Load all .cel files
  QStringList cel_files = properties.getFilePaths( ".*\\.cel" );

  QVector<QImage> frames;

  for( int i = 0; i < cel_files.size(); ++i )
  {
    std::cout << i << ": " << cel_files[i].toStdString() << std::endl;
    
    // Get the decoder for this file
    QtD1::CelDecoder decoder( cel_files[i] );

    // Get the palettes for this file
    QStringList file_name_components = cel_files[i].split( '/' );
    
    QStringList palette_files;
    QtD1::CelImageProperties::getInstance()->getPaletteFileNames(
                                  file_name_components.back(), palette_files );

    QtD1::CelPalette palette( palette_files.front() );

    // Make sure that the image can be decoded - failure will result in
    // a qFatal message.
    decoder.decode( frames, palette );

    QVERIFY( true );

    frames.clear();
  }
}

//---------------------------------------------------------------------------//
// Check that a cel decoder can be constructed with all .cl2 cels
void constructor_cl2()
{
  QtD1::MPQProperties properties;

  // Load all .cl2 files
  QStringList cl2_files = properties.getFilePaths( ".*\\.cl2" );

  for( int i = 0; i < cl2_files.size(); ++i )
  {
    // Make sure CelDecoder can be constructed with each file - failure
    // will result in a qFatal message.
    QtD1::CelDecoder decoder( cl2_files[i] );
    
    QVERIFY( true );
  }
}

//---------------------------------------------------------------------------//
// Check image data can be decoded without specifying a palette
void decode_cl2()
{
  const QtD1::MPQProperties properties;

  // Load all .cl2 files
  QStringList cl2_files = properties.getFilePaths( ".*\\.cl2" );

  QVector<QImage> frames;

  for( int i = 0; i < cl2_files.size(); ++i )
  {
    std::cout << i << ": " << cl2_files[i].toStdString() << std::endl;
    
    // Get the decoder for this file
    QtD1::CelDecoder decoder( cl2_files[i] );

    // Get the palettes for this file
    QStringList file_name_components = cl2_files[i].split( '/' );
    
    QStringList palette_files;
    QtD1::Cl2ImageProperties::getInstance()->getPaletteFileNames(
                                  file_name_components.back(), palette_files );

    QtD1::CelPalette palette( palette_files.front() );

    // Make sure that the image can be decoded - failure will result in
    // a qFatal message.
    decoder.decode( frames, palette );

    QVERIFY( true );
    
    frames.clear();
  }
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestCelDecoder )
#include "tstCelDecoder.moc"

//---------------------------------------------------------------------------//
// end tstCelDecoder.cpp
//---------------------------------------------------------------------------//
