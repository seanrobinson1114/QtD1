//---------------------------------------------------------------------------//
//!
//! \file   tstLevelPillarFactory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level pillar factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QtTest/QtTest>
#include <QImage>
#include <QtPlugin>

// QtD1 Includes
#include "LevelPillarFactory.h"
#include "MPQHandler.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)
Q_IMPORT_PLUGIN(pcx)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestLevelPillarFactory : public QObject
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
// Check that level pillars can be constructed
void createLevelPillars()
{
  QtD1::LevelPillarFactory pillar_factory( "/levels/towndata/town.min" );

  QList<QtD1::LevelPillar*> pillars = pillar_factory.createLevelPillars();

  QCOMPARE( pillars.size(), 1258 );
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestLevelPillarFactory )
#include "tstLevelPillarFactory.moc"

//---------------------------------------------------------------------------//
// end tstLevelPillarFactory.cpp
//---------------------------------------------------------------------------//
