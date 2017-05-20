//---------------------------------------------------------------------------//
//!
//! \file   tstCelImagePixelSetter.cpp
//! \author Alex Robinson
//! \brief  The cel image pixel setter unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "CelImagePixelSetter.h"
#include "CelPalette.h"
#include "MPQHandler.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestCelImagePixelSetter : public QObject
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
// Check that the pixel setter can be constructed
void constructor()
{
  QtD1::CelPalette palette( "/levels/towndata/town.pal" );
  
  QtD1::CelImagePixelSetter pixel_setter( 2, 2, palette );

  QCOMPARE( pixel_setter.getImage().width(), 2 );
  QCOMPARE( pixel_setter.getImage().height(), 2 );
}

//---------------------------------------------------------------------------//
// Check that pixels can be set in the correct order
void set_pixels()
{
  QtD1::CelPalette palette( "/levels/towndata/town.pal" );
  
  QtD1::CelImagePixelSetter pixel_setter( 2, 2, palette );

  QVERIFY( !pixel_setter.allPixelsSet() );
  QCOMPARE( pixel_setter.getNumberOfSetPixels(), 0 );
  QCOMPARE( pixel_setter.getCurrentPixelIndex(), 2 );
  QCOMPARE( pixel_setter.getCurrentImagePosition(), QPoint( 0, 1 ) );

  // Set lower left pixel to black
  *pixel_setter.pixel() = 0;
  pixel_setter.gotoNextPixel();

  QVERIFY( !pixel_setter.allPixelsSet() );
  QCOMPARE( pixel_setter.getNumberOfSetPixels(), 1 );
  QCOMPARE( pixel_setter.getCurrentPixelIndex(), 3 );
  QCOMPARE( pixel_setter.getCurrentImagePosition(), QPoint( 1, 1 ) );

  // Set the lower right pixel to transparent
  *pixel_setter.pixel() = 255;
  pixel_setter.gotoNextPixel();

  QVERIFY( !pixel_setter.allPixelsSet() );
  QCOMPARE( pixel_setter.getNumberOfSetPixels(), 2 );
  QCOMPARE( pixel_setter.getCurrentPixelIndex(), 0 );
  QCOMPARE( pixel_setter.getCurrentImagePosition(), QPoint( 0, 0 ) );

  // Set the upper left pixel to r=20, g=11, b=0, a=255
  *pixel_setter.pixel() = 207;
  pixel_setter.gotoNextPixel();

  QVERIFY( !pixel_setter.allPixelsSet() );
  QCOMPARE( pixel_setter.getNumberOfSetPixels(), 3 );
  QCOMPARE( pixel_setter.getCurrentPixelIndex(), 1 );
  QCOMPARE( pixel_setter.getCurrentImagePosition(), QPoint( 1, 0 ) );

  // Set the upper right pixel to r=89, g=89, b=89, a=255
  *pixel_setter.pixel() = 249;
  pixel_setter.gotoNextPixel();

  QVERIFY( pixel_setter.allPixelsSet() );

  // Make sure that the underlying image is correct
  QImage image = pixel_setter.getImage();
  uchar* pixels = image.scanLine( 0 );

  QCOMPARE( (int)pixels[0], 207 );
  QCOMPARE( (int)pixels[1], 249 );

  pixels = image.scanLine( 1 );

  QCOMPARE( (int)pixels[0], 0 );
  QCOMPARE( (int)pixels[1], 255 );  
}
  
//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestCelImagePixelSetter )
#include "tstCelImagePixelSetter.moc"

//---------------------------------------------------------------------------//
// end tstCelImagePixelSetter.cpp
//---------------------------------------------------------------------------//
