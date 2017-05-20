//---------------------------------------------------------------------------//
//!
//! \file   tstLevelSquares.cpp
//! \author Sean Robinson
//! \brief  The level squares unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <memory>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// QtD1 Includes
#include "LevelSquares.h"

//---------------------------------------------------------------------------//
// Testing Structs
//---------------------------------------------------------------------------//
// This structure allows us to pass in test files/options from the command
// line to this test suite
struct CommandLineArgsFixture
{
  CommandLineArgsFixture()
  {
    if( boost::unit_test::framework::master_test_suite().argc > 1 )
    {
        std::cout << "Error: no argument should be specified!" << std::endl;
        exit( 1 );
    }
  }
};

// Register the above fixture with the test suite
BOOST_FIXTURE_TEST_SUITE( LevelSquares, CommandLineArgsFixture )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the squares can be created for each level
BOOST_AUTO_TEST_CASE( constructor )
{
  BOOST_CHECK_NO_THROW( QtD1::LevelSquares squares( "levels/towndata/town.til" ) );
  BOOST_CHECK_NO_THROW( QtD1::LevelSquares squares( "levels/l1data/l1.til" ) );
  BOOST_CHECK_NO_THROW( QtD1::LevelSquares squares( "levels/l2data/l2.til" ) );
  BOOST_CHECK_NO_THROW( QtD1::LevelSquares squares( "levels/l3data/l3.til" ) );
  BOOST_CHECK_NO_THROW( QtD1::LevelSquares squares( "levels/l4data/l4.til" ) );
}

//---------------------------------------------------------------------------//
// Check that the number of squares can be retrieved
BOOST_AUTO_TEST_CASE( getNumberOfSquares,
                      * boost::unit_test::depends_on( "LevelSquares/constructor" ) )
{
  QtD1::LevelSquares squares_town( "levels/towndata/town.til" );
  BOOST_CHECK_EQUAL( squares_town.getNumberOfSquares(), 342 );

  QtD1::LevelSquares squares_l1( "levels/l1data/l1.til" );
  BOOST_CHECK_EQUAL( squares_l1.getNumberOfSquares(), 206 );

  QtD1::LevelSquares squares_l2( "levels/l2data/l2.til" );
  BOOST_CHECK_EQUAL( squares_l2.getNumberOfSquares(), 160 );

  QtD1::LevelSquares squares_l3( "levels/l3data/l3.til" );
  BOOST_CHECK_EQUAL( squares_l3.getNumberOfSquares(), 156 );

  QtD1::LevelSquares squares_l4( "levels/l4data/l4.til" );
  BOOST_CHECK_EQUAL( squares_l4.getNumberOfSquares(), 137 );
}

//---------------------------------------------------------------------------//
// Check that a square can be returned
BOOST_AUTO_TEST_CASE( getSquare,
                      * boost::unit_test::depends_on( "LevelSquares/getNumberOfSquares" ) )
{
  QtD1::LevelSquares squares_town( "levels/towndata/town.til" );
  for( size_t i = 0; i < squares_town.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_town.getSquare( i ) );

  QtD1::LevelSquares squares_l1( "levels/l1data/l1.til" );
  for( size_t i = 0; i < squares_l1.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l1.getSquare( i ) );

  QtD1::LevelSquares squares_l2( "levels/l2data/l2.til" );
  for( size_t i = 0; i < squares_l2.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l2.getSquare( i ) );

  QtD1::LevelSquares squares_l3( "levels/l3data/l3.til" );
  for( size_t i = 0; i < squares_l3.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l3.getSquare( i ) );

  QtD1::LevelSquares squares_l4( "levels/l4data/l4.til" );
  for( size_t i = 0; i < squares_l4.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l4.getSquare( i ) );
}

//---------------------------------------------------------------------------//
// Check that the top pillar of a square can be returned
BOOST_AUTO_TEST_CASE( getTopPillar,
                      * boost::unit_test::depends_on( "LevelSquares/getSquare" ) )
{
  QtD1::LevelSquares squares_town( "levels/towndata/town.til" );
  for( size_t i = 0; i < squares_town.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_town.getTopPillar( i ) );

  QtD1::LevelSquares squares_l1( "levels/l1data/l1.til" );
  for( size_t i = 0; i < squares_l1.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l1.getTopPillar( i ) );

  QtD1::LevelSquares squares_l2( "levels/l2data/l2.til" );
  for( size_t i = 0; i < squares_l2.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l2.getTopPillar( i ) );

  QtD1::LevelSquares squares_l3( "levels/l3data/l3.til" );
  for( size_t i = 0; i < squares_l3.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l3.getTopPillar( i ) );

  QtD1::LevelSquares squares_l4( "levels/l4data/l4.til" );
  for( size_t i = 0; i < squares_l4.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l4.getTopPillar( i ) );
}

//---------------------------------------------------------------------------//
// Check that the right pillar of a square can be returned
BOOST_AUTO_TEST_CASE( getRightPillar,
                      * boost::unit_test::depends_on( "LevelSquares/getSquare" ) )
{
  QtD1::LevelSquares squares_town( "levels/towndata/town.til" );
  for( size_t i = 0; i < squares_town.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_town.getRightPillar( i ) );

  QtD1::LevelSquares squares_l1( "levels/l1data/l1.til" );
  for( size_t i = 0; i < squares_l1.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l1.getRightPillar( i ) );

  QtD1::LevelSquares squares_l2( "levels/l2data/l2.til" );
  for( size_t i = 0; i < squares_l2.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l2.getRightPillar( i ) );

  QtD1::LevelSquares squares_l3( "levels/l3data/l3.til" );
  for( size_t i = 0; i < squares_l3.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l3.getRightPillar( i ) );

  QtD1::LevelSquares squares_l4( "levels/l4data/l4.til" );
  for( size_t i = 0; i < squares_l4.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l4.getRightPillar( i ) );
}

//---------------------------------------------------------------------------//
// Check that the left pillar of a square can be returned
BOOST_AUTO_TEST_CASE( getLeftPillar,
                      * boost::unit_test::depends_on( "LevelSquares/getSquare" ) )
{
  QtD1::LevelSquares squares_town( "levels/towndata/town.til" );
  for( size_t i = 0; i < squares_town.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_town.getLeftPillar( i ) );

  QtD1::LevelSquares squares_l1( "levels/l1data/l1.til" );
  for( size_t i = 0; i < squares_l1.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l1.getLeftPillar( i ) );

  QtD1::LevelSquares squares_l2( "levels/l2data/l2.til" );
  for( size_t i = 0; i < squares_l2.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l2.getLeftPillar( i ) );

  QtD1::LevelSquares squares_l3( "levels/l3data/l3.til" );
  for( size_t i = 0; i < squares_l3.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l3.getLeftPillar( i ) );

  QtD1::LevelSquares squares_l4( "levels/l4data/l4.til" );
  for( size_t i = 0; i < squares_l4.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l4.getLeftPillar( i ) );
}

//---------------------------------------------------------------------------//
// Check that the bottom pillar of a square can be returned
BOOST_AUTO_TEST_CASE( getBottomPillar,
                      * boost::unit_test::depends_on( "LevelSquares/getSquare" ) )
{
  QtD1::LevelSquares squares_town( "levels/towndata/town.til" );
  for( size_t i = 0; i < squares_town.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_town.getBottomPillar( i ) );

  QtD1::LevelSquares squares_l1( "levels/l1data/l1.til" );
  for( size_t i = 0; i < squares_l1.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l1.getBottomPillar( i ) );

  QtD1::LevelSquares squares_l2( "levels/l2data/l2.til" );
  for( size_t i = 0; i < squares_l2.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l2.getBottomPillar( i ) );

  QtD1::LevelSquares squares_l3( "levels/l3data/l3.til" );
  for( size_t i = 0; i < squares_l3.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l3.getBottomPillar( i ) );

  QtD1::LevelSquares squares_l4( "levels/l4data/l4.til" );
  for( size_t i = 0; i < squares_l4.getNumberOfSquares(); ++i )
    BOOST_CHECK_NO_THROW( squares_l4.getBottomPillar( i ) );
}

//---------------------------------------------------------------------------//
// Check that a square width can be returned
BOOST_AUTO_TEST_CASE( getSquareWidth,
                      * boost::unit_test::depends_on( "LevelSquares/getSquare" ) )
{
  QtD1::LevelSquares squares_town( "levels/towndata/town.til" );
  BOOST_CHECK_EQUAL( squares_town.getSquareWidth(), 128 );

  QtD1::LevelSquares squares_l1( "levels/l1data/l1.til" );
  BOOST_CHECK_EQUAL( squares_l1.getSquareWidth(), 128 );

  QtD1::LevelSquares squares_l2( "levels/l2data/l2.til" );
  BOOST_CHECK_EQUAL( squares_l2.getSquareWidth(), 128 );

  QtD1::LevelSquares squares_l3( "levels/l3data/l3.til" );
  BOOST_CHECK_EQUAL( squares_l3.getSquareWidth(), 128 );

  QtD1::LevelSquares squares_l4( "levels/l4data/l4.til" );
  BOOST_CHECK_EQUAL( squares_l4.getSquareWidth(), 128 );
}

//---------------------------------------------------------------------------//
// Check that a square height can be returned
BOOST_AUTO_TEST_CASE( getSquareHeigth,
                      * boost::unit_test::depends_on( "LevelSquares/getSquare" ) )
{
  QtD1::LevelSquares squares_town( "levels/towndata/town.til" );
  BOOST_CHECK_EQUAL( squares_town.getSquareHeight(), 288 );

  QtD1::LevelSquares squares_l1( "levels/l1data/l1.til" );
  BOOST_CHECK_EQUAL( squares_l1.getSquareHeight(), 192 );

  QtD1::LevelSquares squares_l2( "levels/l2data/l2.til" );
  BOOST_CHECK_EQUAL( squares_l2.getSquareHeight(), 192 );

  QtD1::LevelSquares squares_l3( "levels/l3data/l3.til" );
  BOOST_CHECK_EQUAL( squares_l3.getSquareHeight(), 192 );

  QtD1::LevelSquares squares_l4( "levels/l4data/l4.til" );
  BOOST_CHECK_EQUAL( squares_l4.getSquareHeight(), 288 );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstLevelSquares.cpp
//---------------------------------------------------------------------------//
