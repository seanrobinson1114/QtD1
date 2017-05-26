//---------------------------------------------------------------------------//
//!
//! \file   tstLevelSectorFactory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level sector factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QtTest/QtTest>
#include <QImage>
#include <QtPlugin>

// QtD1 Includes
#include "LevelSectorFactory.h"
#include "LevelSquareFactory.h"
#include "MPQHandler.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)
Q_IMPORT_PLUGIN(pcx)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestLevelSectorFactory : public QObject
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
// Check that the level sector can be constructed
void createLevelSector()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );

  QtD1::LevelSector* sector = sector_factory.createLevelSector();

  QVERIFY( sector != NULL );

  // Delete the sector
  delete sector;
}

//---------------------------------------------------------------------------//
// Check that the level sector can be constructed from cached squares
void createLevelSector_cached_squares()
{
  QtD1::LevelSquareFactory square_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.til" );

  QList<std::shared_ptr<QtD1::LevelSquare> > squares =
    square_factory.createLevelSquares();

  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );

  QtD1::LevelSector* sector = sector_factory.createLevelSector( squares );

  QVERIFY( sector != NULL );
  
  // Delete the sector
  delete sector;
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestLevelSectorFactory )
#include "tstLevelSectorFactory.moc"

//---------------------------------------------------------------------------//
// end tstLevelSectorFactory.cpp
//---------------------------------------------------------------------------//
