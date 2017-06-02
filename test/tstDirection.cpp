//---------------------------------------------------------------------------//
//!
//! \file   tstDirection.cpp
//! \author Alex Robinson
//! \brief  The direction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>
#include <QImage>
#include <QPixmap>

// QtD1 Includes
#include "Direction.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestDirection : public QObject
{
  Q_OBJECT

private slots:

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a discrete direction can be calculated
void calculateDiscreteDirection()
{

}

//---------------------------------------------------------------------------//
// Check that the direction vector corresponding to the direction enum can
// be returned
void getDirectionVector()
{

}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestDirection )
#include "tstDirection.moc"

//---------------------------------------------------------------------------//
// end tstDirection.cpp
//---------------------------------------------------------------------------//
