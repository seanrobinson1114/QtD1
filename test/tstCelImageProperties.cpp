//---------------------------------------------------------------------------//
//!
//! \file   tstCelImageProperties.cpp
//! \author Sean Robinson
//! \brief  The cel image properties unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "CelImageProperties.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestCelImageProperties : public QObject
{
  Q_OBJECT

private slots:

  void initTestCase()
  {
    // Construct the image properties
    QtD1::CelImageProperties::getInstance();
  }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that existence of image properties can be determined
void doesImageHaveProperties()
{
  QtD1::CelImageProperties* cip =
    QtD1::CelImageProperties::getInstance();

  // PentSpin.cel should return true
  QVERIFY( cip->doesImageHaveProperties( "PentSpin.cel" ) );

  // fakename.cel should return false
  QVERIFY( !cip->doesImageHaveProperties( "fakename.cel" ) );
}

//---------------------------------------------------------------------------//
// Check that the number of images for a specific file can be returned
void getNumberOfImages()
{
  QtD1::CelImageProperties* cip =
    QtD1::CelImageProperties::getInstance();

  // Check that all 5 images with this property return correct values
  QCOMPARE( cip->getNumberOfImages( "unravw.cel" ), 8 );
  QCOMPARE( cip->getNumberOfImages( "cow.cel" ), 8 );
  QCOMPARE( cip->getNumberOfImages( "smithw.cel" ), 8 );
  QCOMPARE( cip->getNumberOfImages( "wmnw.cel" ), 8 );
  QCOMPARE( cip->getNumberOfImages( "twnfw.cel" ), 8 );

  // Check that images without this property defined return the correct value
  QCOMPARE( cip->getNumberOfImages( "golddrop.cel" ), 1 );
}

//---------------------------------------------------------------------------//
// Check that the frame header size can be returned
void getFrameHeaderSize()
{
  QtD1::CelImageProperties* cip =
    QtD1::CelImageProperties::getInstance();

  // Check that image with property is correctly returned
  QCOMPARE( cip->getFrameHeaderSize( "unravw4.cel" ), 10 );

  // Check that image without property is correctly returned
  QCOMPARE( cip->getFrameHeaderSize( "PentSpin.cel" ), 0 );
}

//---------------------------------------------------------------------------//
// Check that the frame width can be returned
void getFrameWidth()
{
  QtD1::CelImageProperties* cip =
    QtD1::CelImageProperties::getInstance();

  // Check a file that only has width property
  QCOMPARE( cip->getFrameWidth( "quest.cel", 0 ), 320 );

  // Check a file that has frame_widths property with a single element
  QCOMPARE( cip->getFrameWidth( "charbut.cel", 0 ), 95 );
  QCOMPARE( cip->getFrameWidth( "charbut.cel", 1 ), 41 );

  // Check a file that has frame_widths property with multiple elements
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 0 ), 33 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 1 ), 32 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 5 ), 32 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 9 ), 32 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 10 ), 23 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 11 ), 28 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 50 ), 28 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 85 ), 28 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 86 ), 56 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 100 ), 56 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 110 ), 56 );
  QCOMPARE( cip->getFrameWidth( "objcurs.cel", 111 ), 56 );
}

//---------------------------------------------------------------------------//
// Check that the frame height can be returned
void getFrameHeight()
{
  QtD1::CelImageProperties* cip =
    QtD1::CelImageProperties::getInstance();

  // Check a file that only has heigth property
  QCOMPARE( cip->getFrameHeight( "quest.cel", 0 ), 352 );

  // Check a file that has frame_heights property with a single element
  QCOMPARE( cip->getFrameHeight( "charbut.cel", 0 ), 22 );
  QCOMPARE( cip->getFrameHeight( "charbut.cel", 1 ), 22 );

  // Check a file that has frame_heights property with multiple elements
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 0 ), 29 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 1 ), 32 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 5 ), 32 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 9 ), 32 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 10 ), 35 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 11 ), 28 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 50 ), 28 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 60 ), 28 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 61 ), 56 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 66 ), 56 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 67 ), 84 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 85 ), 84 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 86 ), 56 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 100 ), 56 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 110 ), 56 );
  QCOMPARE( cip->getFrameHeight( "objcurs.cel", 111 ), 84 );
}

//---------------------------------------------------------------------------//
// Check that the image palettes can be retrieved
void getPaletteFileNames()
{
  QtD1::CelImageProperties* cip =
    QtD1::CelImageProperties::getInstance();
  
  QStringList palettes;

  // Check that town.pal is return for images with no palette specified
  cip->getPaletteFileNames( "PentSpin.cel", palettes );
  QCOMPARE( palettes.size(), 1 );
  QCOMPARE( palettes[0], QString("levels/towndata/town.pal") );
  palettes.clear();

  // Check that image with specific palettes
  cip->getPaletteFileNames( "l1s.cel", palettes );
  QCOMPARE( palettes.size(), 6 );
  QCOMPARE( palettes[0], QString("levels/l1data/l1_1.pal") );
  QCOMPARE( palettes[2], QString("levels/l1data/l1_3.pal") );
  QCOMPARE( palettes[5], QString("levels/l1data/l1palg.pal") );
}

//---------------------------------------------------------------------------//
// Check that palette compatibility can be determined
void isPaletteCompatible()
{
  QtD1::CelImageProperties* cip =
    QtD1::CelImageProperties::getInstance();

  // Check image with no pal specified
  QVERIFY( cip->isPaletteCompatible( "PentSpin.cel", "levels/towndata/town.pal" ) );
  QVERIFY( !cip->isPaletteCompatible( "PentSpin.cel", "gendata/cut3.pal" ) );
  
  // Check image with pal specified
  QVERIFY( cip->isPaletteCompatible( "cut3.cel", "gendata/cut3.pal" ) );
  QVERIFY( !cip->isPaletteCompatible( "cut3.cel", "levels/towndata/town.pal" ) );

  // Check image with multiple pals specified
  QVERIFY( cip->isPaletteCompatible( "l1s.cel", "levels/l1data/l1_1.pal" ) );
  QVERIFY( cip->isPaletteCompatible( "l1s.cel", "levels/l1data/l1_2.pal" ) );
  QVERIFY( cip->isPaletteCompatible( "l1s.cel", "levels/l1data/l1_3.pal" ) );
  QVERIFY( cip->isPaletteCompatible( "l1s.cel", "levels/l1data/l1_4.pal" ) );
  QVERIFY( cip->isPaletteCompatible( "l1s.cel", "levels/l1data/l1_5.pal" ) );
  QVERIFY( cip->isPaletteCompatible( "l1s.cel", "levels/l1data/l1palg.pal" ) );
  QVERIFY( !cip->isPaletteCompatible( "l1s.cel", "levels/towndata/town.pal" ) );
}

//---------------------------------------------------------------------------//
// Check that that existence of transitions can be determined
void hasColorTransitionData()
{
  QtD1::CelImageProperties* cip =
    QtD1::CelImageProperties::getInstance();
  
  // No cel images have color transition data
  QVERIFY( !cip->hasColorTransitionData( "PentSpin.cel" ) );
  QVERIFY( !cip->hasColorTransitionData( "l1s.cel" ) );
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestCelImageProperties )
#include "tstCelImageProperties.moc"

//---------------------------------------------------------------------------//
// end tstCelImageProperties.cpp
//---------------------------------------------------------------------------//
