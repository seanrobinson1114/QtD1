//---------------------------------------------------------------------------//
//!
//! \file   tstCl2ImageProperties.cpp
//! \author Sean Robinson
//! \brief  The cel image properties unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "Cl2ImageProperties.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestCl2ImageProperties : public QObject
{
  Q_OBJECT

private slots:

  void initTestCase()
  {
    // Construct the image properties
    QtD1::Cl2ImageProperties::getInstance();
  }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that existence of image properties can be determined
void doesImageHaveProperties()
{
  QtD1::Cl2ImageProperties* cl2ip =
    QtD1::Cl2ImageProperties::getInstance();

  // PentSpin.cel should return true
  QVERIFY( cl2ip->doesImageHaveProperties( "rhaas.cl2" ) );

  // fakename.cel should return false
  QVERIFY( !cl2ip->doesImageHaveProperties( "fakename.cl2" ) );
}

//---------------------------------------------------------------------------//
// Check that the Diablo.exe filename (with path) can be set
void getNumberOfImages()
{
  QtD1::Cl2ImageProperties* cl2ip =
    QtD1::Cl2ImageProperties::getInstance();

  QCOMPARE( cl2ip->getNumberOfImages( "thinlght.cl2" ), 1 );
  
  QCOMPARE( cl2ip->getNumberOfImages( "acida.cl2" ), 8 );
  QCOMPARE( cl2ip->getNumberOfImages( "bata.cl2" ), 8 );
  QCOMPARE( cl2ip->getNumberOfImages( "blacka.cl2" ), 8 );
  QCOMPARE( cl2ip->getNumberOfImages( "demskld.cl2" ), 8 );
  QCOMPARE( cl2ip->getNumberOfImages( "diablod.cl2" ), 8 );
}

//---------------------------------------------------------------------------//
// Check that the frame header size can be returned
void getFrameHeaderSize()
{
  QtD1::Cl2ImageProperties* cl2ip =
    QtD1::Cl2ImageProperties::getInstance();

  // Check that image with property is correctly returned
  QCOMPARE( cl2ip->getFrameHeaderSize( "acidbf13.cl2" ), 10 );
  QCOMPARE( cl2ip->getFrameHeaderSize( "rhdlm4.cl2" ), 10 );
}

//---------------------------------------------------------------------------//
// Check that the frame width can be returned
void getFrameWidth()
{
  QtD1::Cl2ImageProperties* cl2ip =
    QtD1::Cl2ImageProperties::getInstance();

  // Frame index is irrelevant because all frames in a cl2 image have the
  // same width
  QCOMPARE( cl2ip->getFrameWidth( "rhalm7.cl2", 0 ), 96 );
  QCOMPARE( cl2ip->getFrameWidth( "wltat0.cl2", 0 ), 128 );
}

//---------------------------------------------------------------------------//
// Check that the frame height can be returned
void getFrameHeight()
{
  QtD1::Cl2ImageProperties* cl2ip =
    QtD1::Cl2ImageProperties::getInstance();

  // Frame index is irrelevant because all frames in a cl2 image have the
  // same height
  QCOMPARE( cl2ip->getFrameHeight( "rhalm7.cl2", 0 ), 96 );
  QCOMPARE( cl2ip->getFrameHeight( "wltat0.cl2", 0 ), 128 );
}

//---------------------------------------------------------------------------//
// Check that the image palettes can be retrieved
void getPaletteFileNames()
{
  QtD1::Cl2ImageProperties* cl2ip =
    QtD1::Cl2ImageProperties::getInstance();

  QStringList palettes;

  // Check that town.pal is returned for any image
  cl2ip->getPaletteFileNames( "fallw7.cl2", palettes );
  
  QCOMPARE( palettes.size(), 1 );
  QCOMPARE( palettes[0], QString("levels/towndata/town.pal") );
  palettes.clear();

  cl2ip->getPaletteFileNames( "smuht7.cl2", palettes );
  
  QCOMPARE( palettes.size(), 1 );
  QCOMPARE( palettes[0], QString("levels/towndata/town.pal") );
  palettes.clear();
}

//---------------------------------------------------------------------------//
// Check that palette compatibility can be determined
void isPaletteCompatible()
{
  QtD1::Cl2ImageProperties* cl2ip =
    QtD1::Cl2ImageProperties::getInstance();

  // Check that town.pal is compatible with any image
  QVERIFY( cl2ip->isPaletteCompatible( "wmubl6.cl2", "levels/towndata/town.pal" ) );
  QVERIFY( cl2ip->isPaletteCompatible( "gargoa5.cl2", "levels/towndata/town.pal" ) );
  QVERIFY( !cl2ip->isPaletteCompatible( "gargoa5.cl2", "gendata/cut3.pal" ) );
}

//---------------------------------------------------------------------------//
// Check that that existence of transition data can be determined
void hasColorTransitionData()
{
 QtD1::Cl2ImageProperties* cl2ip =
   QtD1::Cl2ImageProperties::getInstance();

 // Check image that has specified transition data
 QVERIFY( cl2ip->hasColorTransitionData( "goatbw2.cl2" ) );

 // Check image with no specified transition data
 QVERIFY( !cl2ip->hasColorTransitionData( "acidbf1.cl2" ) );
}

//---------------------------------------------------------------------------//
// Check that that transition file names can be returned
void getColorTransitionFileNames()
{
  QtD1::Cl2ImageProperties* cl2ip =
    QtD1::Cl2ImageProperties::getInstance();
  
  QStringList transitions;

  // Check an image that has specified transition data
  cl2ip->getColorTransitionFileNames( "goatbw2.cl2", transitions );
  
  QCOMPARE( transitions.size(), 8 );
  QCOMPARE( transitions[0], QString("monsters/goatbow/beige.trn") );
  QCOMPARE( transitions[7], QString("plrgfx/stone.trn") );
  transitions.clear();

  // Check image with no specified transition data
  cl2ip->getColorTransitionFileNames( "acidbf1.cl2", transitions );
  
  QVERIFY( transitions.empty() );
  transitions.clear();
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestCl2ImageProperties )
#include "tstCl2ImageProperties.moc"

//---------------------------------------------------------------------------//
// end tstCl2ImageProperties.cpp
//---------------------------------------------------------------------------//
