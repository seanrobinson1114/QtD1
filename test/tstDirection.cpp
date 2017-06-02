//---------------------------------------------------------------------------//
//!
//! \file   tstDirection.cpp
//! \author Alex Robinson
//! \brief  The direction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
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
// Check that a direction can be converted to a string
void directionToString_data()
{
  QTest::addColumn<QtD1::Direction>( "direction" );
  QTest::addColumn<QString>( "name" );

  QTest::newRow( "South" ) << QtD1::South << "South";
  QTest::newRow( "SouthSouthwest" ) << QtD1::SouthSouthwest << "South-southwest";
  QTest::newRow( "Southwest" ) << QtD1::Southwest << "Southwest";
  QTest::newRow( "WestSouthwest" ) << QtD1::WestSouthwest << "West-southwest";
  QTest::newRow( "West" ) << QtD1::West << "West";
  QTest::newRow( "WestNorthwest" ) << QtD1::WestNorthwest << "West-northwest";
  QTest::newRow( "Northwest" ) << QtD1::Northwest << "Northwest";
  QTest::newRow( "NorthNorthwest" ) << QtD1::NorthNorthwest << "North-northwest";
  QTest::newRow( "North" ) << QtD1::North << "North";
  QTest::newRow( "NorthNortheast" ) << QtD1::NorthNortheast << "North-northeast";
  QTest::newRow( "Northeast" ) << QtD1::Northeast << "Northeast";
  QTest::newRow( "EastNortheast" ) << QtD1::EastNortheast << "East-northeast";
  QTest::newRow( "East" ) << QtD1::East << "East";
  QTest::newRow( "EastSoutheast" ) << QtD1::EastSoutheast << "East-southeast";
  QTest::newRow( "Southeast" ) << QtD1::Southeast << "Southeast";
  QTest::newRow( "SouthSoutheast" ) << QtD1::SouthSoutheast << "South-southeast";
}
  
void directionToString()
{
  QFETCH(QtD1::Direction, direction);
  QFETCH(QString, name);

  QCOMPARE( QtD1::directionToString(direction), name );
}

//---------------------------------------------------------------------------//
// Check that a direction can be placed in an output stream
void ostream_operator_data()
{
  QTest::addColumn<QtD1::Direction>( "direction" );
  QTest::addColumn<QString>( "name" );

  QTest::newRow( "South" ) << QtD1::South << "South";
  QTest::newRow( "SouthSouthwest" ) << QtD1::SouthSouthwest << "South-southwest";
  QTest::newRow( "Southwest" ) << QtD1::Southwest << "Southwest";
  QTest::newRow( "WestSouthwest" ) << QtD1::WestSouthwest << "West-southwest";
  QTest::newRow( "West" ) << QtD1::West << "West";
  QTest::newRow( "WestNorthwest" ) << QtD1::WestNorthwest << "West-northwest";
  QTest::newRow( "Northwest" ) << QtD1::Northwest << "Northwest";
  QTest::newRow( "NorthNorthwest" ) << QtD1::NorthNorthwest << "North-northwest";
  QTest::newRow( "North" ) << QtD1::North << "North";
  QTest::newRow( "NorthNortheast" ) << QtD1::NorthNortheast << "North-northeast";
  QTest::newRow( "Northeast" ) << QtD1::Northeast << "Northeast";
  QTest::newRow( "EastNortheast" ) << QtD1::EastNortheast << "East-northeast";
  QTest::newRow( "East" ) << QtD1::East << "East";
  QTest::newRow( "EastSoutheast" ) << QtD1::EastSoutheast << "East-southeast";
  QTest::newRow( "Southeast" ) << QtD1::Southeast << "Southeast";
  QTest::newRow( "SouthSoutheast" ) << QtD1::SouthSoutheast << "South-southeast";
}

void ostream_operator()
{
  QFETCH(QtD1::Direction, direction);
  QFETCH(QString, name);

  std::ostringstream oss;
  oss << direction;
  QString name_from_oss( oss.str().c_str() );
  
  QCOMPARE( name_from_oss, name );
}
  
//---------------------------------------------------------------------------//
// Check that the nearest discrete direction can be calculated
void calculateNearestDiscreteDirection_data()
{
  QTest::addColumn<QPointF>( "start_pos" );
  QTest::addColumn<QPointF>( "end_pos" );
  QTest::addColumn<bool>( "use_all_directions" );
  QTest::addColumn<QtD1::Direction>( "nearest_discrete_direction" );

  QTest::newRow( "East lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9807852804032304, 0.19509032201612825 ) << true << QtD1::East;
  QTest::newRow( "East below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9951847266721969, 0.0980171403295606 ) << true << QtD1::East;
  QTest::newRow( "East (all dirs)" ) << QPointF( 10.0, 100.0 ) << QPointF( 20.0, 100.0 ) << true << QtD1::East;
  QTest::newRow( "East above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9807852804034255, -0.19509032201514748 ) << true << QtD1::East;

  QTest::newRow( "EastNortheast lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9807852804032304, -0.19509032201612825 ) << true << QtD1::EastNortheast;
  QTest::newRow( "EastNortheast below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9569403357322088, -0.29028467725446233 ) << true << QtD1::EastNortheast;
  QTest::newRow( "EastNortheast (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9238795325112867, -0.3826834323650898 ) << true << QtD1::EastNortheast;
  QTest::newRow( "EastNortheast above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.8314696123031008, -0.5555702330187707 ) << true << QtD1::EastNortheast;

  QTest::newRow( "Northeast lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.8314696123025452, -0.5555702330196022 ) << true << QtD1::Northeast;
  QTest::newRow( "Northeast below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.773010453362737, -0.6343932841636455 ) << true << QtD1::Northeast;
  QTest::newRow( "Northeast (all dirs)" ) << QPointF( 10.0, 20.0 ) << QPointF( 20.0, 10.0 ) << true << QtD1::Northeast;
  QTest::newRow( "Northeast above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.5555702330204337, -0.8314696123019897 ) << true << QtD1::Northeast;

  QTest::newRow( "NorthNortheast lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.5555702330196023, -0.8314696123025452 ) << true << QtD1::NorthNortheast;
  QTest::newRow( "NorthNortheast below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.4713967368259978, -0.8819212643483549 ) << true << QtD1::NorthNortheast;
  QTest::newRow( "NorthNortheast (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.38268343236508984, -0.9238795325112867 ) << true << QtD1::NorthNortheast;
  QTest::newRow( "NorthNortheast above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.19509032201710919, -0.9807852804030354 ) << true << QtD1::NorthNortheast;

  QTest::newRow( "North lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.19509032201612833, -0.9807852804032304 ) << true << QtD1::North;
  QTest::newRow( "North below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.09801714032956077, -0.9951847266721968 ) << true << QtD1::North;
  QTest::newRow( "North (all dirs)" ) << QPointF( -2.0, -50.0 ) << QPointF( -2.0, -60.0 ) << true << QtD1::North;
  QTest::newRow( "North above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.19509032201514734, -0.9807852804034256 ) << true << QtD1::North;

  QTest::newRow( "NorthNorthwest lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.1950903220161282, -0.9807852804032304 ) << true << QtD1::NorthNorthwest;
  QTest::newRow( "NorthNorthwest below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.29028467725446216, -0.9569403357322089 ) << true << QtD1::NorthNorthwest;
  QTest::newRow( "NorthNorthwest (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.3826834323650897, -0.9238795325112867 ) << true << QtD1::NorthNorthwest;
  QTest::newRow( "NorthNorthwest above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.5555702330187704, -0.831469612303101 ) << true << QtD1::NorthNorthwest;
  
  QTest::newRow( "Northwest lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.555570233019602, -0.8314696123025455 ) << true << QtD1::Northwest;
  QTest::newRow( "Nortwest below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.6343932841636454, -0.7730104533627371 ) << true << QtD1::Northwest;
  QTest::newRow( "Nortwest (all dirs)" ) << QPointF( -30.0, 40.0 ) << QPointF( -40.0, 30.0 ) << true << QtD1::Northwest;
  QTest::newRow( "Northwest above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.8314696123019897, -0.5555702330204336 ) << true << QtD1::Northwest;

  QTest::newRow( "WestNorthwest lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.8314696123025453, -0.5555702330196022 ) << true << QtD1::WestNorthwest;
  QTest::newRow( "WestNorthwest below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.8819212643483549, -0.47139673682599786 ) << true << QtD1::WestNorthwest;
  QTest::newRow( "WestNorthwest (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9238795325112867, -0.3826834323650899 ) << true << QtD1::WestNorthwest;
  QTest::newRow( "WestNorthwest above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9807852804030353, -0.19509032201710946 ) << true << QtD1::WestNorthwest;

  QTest::newRow( "West lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9807852804032304, -0.1950903220161286 ) << true << QtD1::West;
  QTest::newRow( "West below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9951847266721968, -0.09801714032956083 ) << true << QtD1::West;
  QTest::newRow( "West (all dirs)" ) << QPointF( -100.0, 100.0 ) << QPointF( -200.0, 100.0 ) << true << QtD1::West;
  QTest::newRow( "West above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9807852804034255, 0.19509032201514748 ) << true << QtD1::West;

  QTest::newRow( "WestSouthwest lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9807852804032304, 0.19509032201612836 ) << true << QtD1::WestSouthwest;
  QTest::newRow( "WestSouthwest below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9569403357322089, 0.2902846772544621 ) << true << QtD1::WestSouthwest;
  QTest::newRow( "WestSouthwest (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9238795325112868, 0.38268343236508967 ) << true << QtD1::WestSouthwest;
  QTest::newRow( "WestSouthwest above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.831469612303101, 0.5555702330187704 ) << true << QtD1::WestSouthwest;
  
  QTest::newRow( "Southwest lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.8314696123025455, 0.555570233019602 ) << true << QtD1::Southwest;
  QTest::newRow( "Soutwest below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.7730104533627371, 0.6343932841636453 ) << true << QtD1::Southwest;
  QTest::newRow( "Southwest (all dirs)" ) << QPointF( 20.0, 155.0 ) << QPointF( 19.0, 156.0 ) << true << QtD1::Southwest;
  QTest::newRow( "Southwest above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.5555702330204337, 0.8314696123019897 ) << true << QtD1::Southwest;

  QTest::newRow( "SouthSouthwest lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.5555702330196022, 0.8314696123025452 ) << true << QtD1::SouthSouthwest;
  QTest::newRow( "SouthSouthwest below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.47139673682599786, 0.8819212643483549 ) << true << QtD1::SouthSouthwest;
  QTest::newRow( "SouthSouthwest (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.38268343236509034, 0.9238795325112865 ) << true << QtD1::SouthSouthwest;
  QTest::newRow( "SouthSouthwest above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.19509032201710952, 0.9807852804030353 ) << true << QtD1::SouthSouthwest;

  QTest::newRow( "South lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.19509032201612866, 0.9807852804032303 ) << true << QtD1::South;
  QTest::newRow( "South below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.09801714032956045, 0.9951847266721969 ) << true << QtD1::South;
  QTest::newRow( "South (all dirs)" ) << QPointF( -12.0, -26.1 ) << QPointF( -12.0, -26.0 ) << true << QtD1::South;
  QTest::newRow( "South above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.19509032201514742, 0.9807852804034255 ) << true << QtD1::South;

  QTest::newRow( "SouthSoutheast lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.1950903220161283, 0.9807852804032304 ) << true << QtD1::SouthSoutheast;
  QTest::newRow( "SouthSoutheast below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.29028467725446294, 0.9569403357322087 ) << true << QtD1::SouthSoutheast;
  QTest::newRow( "SouthSoutheast (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.38268343236509, 0.9238795325112866 ) << true << QtD1::SouthSoutheast;
  QTest::newRow( "SouthSoutheast above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.5555702330187711, 0.8314696123031006 ) << true << QtD1::SouthSoutheast;

  QTest::newRow( "Southeast lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.5555702330196026, 0.831469612302545 ) << true << QtD1::Southeast;
  QTest::newRow( "Southeast below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.6343932841636456, 0.7730104533627369 ) << true << QtD1::Southeast;
  QTest::newRow( "Southeast (all dirs)" ) << QPointF( 1.0, 101.0 ) << QPointF( 2.0, 102.0 ) << true << QtD1::Southeast;
  QTest::newRow( "Southeast above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.8314696123019896, 0.5555702330204337 ) << true << QtD1::Southeast;

  QTest::newRow( "EastSoutheast lower boundary (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.8314696123025452, 0.5555702330196022 ) << true << QtD1::EastSoutheast;
  QTest::newRow( "EastSoutheast below (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.8819212643483548, 0.4713967368259979 ) << true << QtD1::EastSoutheast;
  QTest::newRow( "EastSoutheast (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9238795325112865, 0.3826834323650904 ) << true << QtD1::EastSoutheast;
  QTest::newRow( "EastSoutheast above (all dirs)" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9807852804030353, 0.1950903220171096 ) << true << QtD1::EastSoutheast;

  QTest::newRow( "East lower boundary" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9238795325112867, 0.3826834323650898 ) << false << QtD1::East;
  QTest::newRow( "East below" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9807852804032304, 0.19509032201612825 ) << false << QtD1::East;
  QTest::newRow( "East" ) << QPointF( 0.0, 0.0 ) << QPointF( 1.0, 0.0 ) << false << QtD1::East;
  QTest::newRow( "East above" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9238795325116694, -0.3826834323641659 ) << false << QtD1::East;

  QTest::newRow( "Northeast lower boundary" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9238795325112867, -0.3826834323650898 ) << false << QtD1::Northeast;
  QTest::newRow( "Northeast below" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.8314696123025452, -0.5555702330196022 ) << false << QtD1::Northeast;
  QTest::newRow( "Northeast" ) << QPointF( 0.0, 0.0 ) << QPointF( 1.0, -1.0 ) << false << QtD1::Northeast;
  QTest::newRow( "Northeast above" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.38268343236601376, -0.923879532510904 ) << false << QtD1::Northeast;

  QTest::newRow( "North lower boundary" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.38268343236508984, -0.9238795325112867 ) << false << QtD1::North;
  QTest::newRow( "North below" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.19509032201612833, -0.9807852804032304 ) << false << QtD1::North;
  QTest::newRow( "North" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.0, -1.0 ) << false << QtD1::North;
  QTest::newRow( "North above" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.38268343236416574, -0.9238795325116695 ) << false << QtD1::North;

  QTest::newRow( "Northwest lower boundary" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.3826834323650897, -0.9238795325112867 ) << false << QtD1::Northwest;
  QTest::newRow( "Northwest below" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.555570233019602, -0.8314696123025455 ) << false << QtD1::Northwest;
  QTest::newRow( "Northwest" ) << QPointF( 0.0, 0.0 ) << QPointF( -1.0, -1.0 ) << false << QtD1::Northwest;
  QTest::newRow( "Northwest above" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.923879532510904, -0.3826834323660138 ) << false << QtD1::Northwest;

  QTest::newRow( "West lower boundary" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9238795325112867, -0.3826834323650899 ) << false << QtD1::West;
  QTest::newRow( "West below" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9807852804032304, -0.1950903220161286 ) << false << QtD1::West;
  QTest::newRow( "West" ) << QPointF( 0.0, 0.0 ) << QPointF( -1.0, 0.0 ) << false << QtD1::West;
  QTest::newRow( "West above" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9238795325116695, 0.3826834323641657 ) << false << QtD1::West;

  QTest::newRow( "Southwest lower boundary" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.9238795325112868, 0.38268343236508967 ) << false << QtD1::Southwest;
  QTest::newRow( "Southwest below" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.8314696123025455, 0.555570233019602 ) << false << QtD1::Southwest;
  QTest::newRow( "Southwest" ) << QPointF( 0.0, 0.0 ) << QPointF( -1.0, 1.0 ) << false << QtD1::Southwest;
  QTest::newRow( "Southwest above" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.3826834323660143, 0.9238795325109038 ) << false << QtD1::Southwest;

  QTest::newRow( "South lower boundary" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.38268343236509034, 0.9238795325112865 ) << false << QtD1::South;
  QTest::newRow( "South below" ) << QPointF( 0.0, 0.0 ) << QPointF( -0.19509032201612866, 0.9807852804032303 ) << false << QtD1::South;
  QTest::newRow( "South" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.0, 1.0 ) << false << QtD1::South;
  QTest::newRow( "South above" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.382683432364166, 0.9238795325116694 ) << false << QtD1::South;

  QTest::newRow( "Southeast lower boundary" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.38268343236509, 0.9238795325112866 ) << false << QtD1::Southeast;
  QTest::newRow( "Southeast below" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.5555702330196018, 0.8314696123025455 ) << false << QtD1::Southeast;
  QTest::newRow( "Southeast" ) << QPointF( 0.0, 0.0 ) << QPointF( 1.0, 1.0 ) << false << QtD1::Southeast;
  QTest::newRow( "Southeast above" ) << QPointF( 0.0, 0.0 ) << QPointF( 0.9238795325109038, 0.3826834323660144 ) << false << QtD1::Southeast;
}
  
void calculateNearestDiscreteDirection()
{
  QFETCH(QPointF, start_pos );
  QFETCH(QPointF, end_pos );
  QFETCH(bool, use_all_directions);
  QFETCH(QtD1::Direction, nearest_discrete_direction);

  QtD1::Direction direction;

  if( use_all_directions )
  {
    direction = QtD1::calculateNearestDiscreteDirection(
                                                    start_pos, end_pos, true );
  }
  else
    direction = QtD1::calculateNearestDiscreteDirection( start_pos, end_pos );
  
  QCOMPARE( direction, nearest_discrete_direction );
}

//---------------------------------------------------------------------------//
// Check that the direction vector corresponding to the direction enum can
// be returned
void getDirectionVector_data()
{
  QTest::addColumn<QtD1::Direction>( "direction" );
  QTest::addColumn<QPointF>( "direction_vector" );

  QTest::newRow( "South" ) << QtD1::South << QPointF( 0., 1. );
  QTest::newRow( "SouthSouthwest" ) << QtD1::SouthSouthwest << QPointF( -0.38268343236509, 0.9238795325112866 );
  QTest::newRow( "Southwest" ) << QtD1::Southwest << QPointF( -0.7071067811865477, 0.7071067811865477 );
  QTest::newRow( "WestSouthwest" ) << QtD1::WestSouthwest << QPointF( -0.9238795325112868, 0.38268343236508967 );
  QTest::newRow( "West" ) << QtD1::West << QPointF( -1.0, 0.0 );
  QTest::newRow( "WestNorthwest" ) << QtD1::WestNorthwest << QPointF( -0.9238795325112868, -0.38268343236508967 );
  QTest::newRow( "Northwest" ) << QtD1::Northwest << QPointF( -0.7071067811865477, -0.7071067811865477 );
  QTest::newRow( "NorthNorthwest" ) << QtD1::NorthNorthwest << QPointF( -0.38268343236508984, -0.9238795325112867 );
  QTest::newRow( "North" ) << QtD1::North << QPointF( 0.0, -1.0 );
  QTest::newRow( "NorthNortheast" ) << QtD1::NorthNortheast << QPointF( 0.38268343236508984, -0.9238795325112867 );
  QTest::newRow( "Northeast" ) << QtD1::Northeast << QPointF( 0.7071067811865477, -0.7071067811865477 );
  QTest::newRow( "EastNortheast" ) << QtD1::EastNortheast << QPointF( 0.9238795325112867, -0.3826834323650898 );
  QTest::newRow( "East" ) << QtD1::East << QPointF( 1.0, 0.0 );
  QTest::newRow( "EastSoutheast" ) << QtD1::EastSoutheast << QPointF( 0.9238795325112867, 0.38268343236508984 );
  QTest::newRow( "Southeast" ) << QtD1::Southeast << QPointF( 0.7071067811865477, 0.7071067811865477 );
  QTest::newRow( "SouthSoutheast" ) << QtD1::SouthSoutheast << QPointF( 0.38268343236508984, 0.9238795325112867 );
}
  
void getDirectionVector()
{
  QFETCH(QtD1::Direction, direction);
  QFETCH(QPointF, direction_vector);

  QCOMPARE( QtD1::getDirectionVector(direction), direction_vector );
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
