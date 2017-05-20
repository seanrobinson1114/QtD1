//---------------------------------------------------------------------------//
//!
//! \file   tstLevelPillars.cpp
//! \author Sean Robinson
//! \brief  The level pillars unit tests
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
#include "LevelPillars.h"

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
BOOST_FIXTURE_TEST_SUITE( LevelPillars, CommandLineArgsFixture )

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that pillars can be created for each level
BOOST_AUTO_TEST_CASE( constructor )
{
  BOOST_CHECK_NO_THROW( QtD1::LevelPillars pillars( "levels/towndata/town.min" ) );
  BOOST_CHECK_NO_THROW( QtD1::LevelPillars pillars( "levels/l1data/l1.min" ) );
  BOOST_CHECK_NO_THROW( QtD1::LevelPillars pillars( "levels/l2data/l2.min" ) );
  BOOST_CHECK_NO_THROW( QtD1::LevelPillars pillars( "levels/l3data/l3.min" ) );
  BOOST_CHECK_NO_THROW( QtD1::LevelPillars pillars( "levels/l4data/l4.min" ) );
}

//---------------------------------------------------------------------------//
// Check that number of pillars can be retrieved
BOOST_AUTO_TEST_CASE( getNumberOfPillars,
                      * boost::unit_test::depends_on( "LevelPillars/constructor" ) )
{
  QtD1::LevelPillars pillars_town( "levels/towndata/town.min" );
  BOOST_CHECK_EQUAL( pillars_town.getNumberOfPillars(), 1258 );

  QtD1::LevelPillars pillars_l1( "levels/l1data/l1.min" );
  BOOST_CHECK_EQUAL( pillars_l1.getNumberOfPillars(), 453 );

  QtD1::LevelPillars pillars_l2( "levels/l2data/l2.min" );
  BOOST_CHECK_EQUAL( pillars_l2.getNumberOfPillars(), 559 );

  QtD1::LevelPillars pillars_l3( "levels/l3data/l3.min" );
  BOOST_CHECK_EQUAL( pillars_l3.getNumberOfPillars(), 560 );

  QtD1::LevelPillars pillars_l4( "levels/l4data/l4.min" );
  BOOST_CHECK_EQUAL( pillars_l4.getNumberOfPillars(), 456 );
}

//---------------------------------------------------------------------------//
// Check that a pillar can be returned
BOOST_AUTO_TEST_CASE( getPillar,
                      * boost::unit_test::depends_on( "LevelPillars/getNumberOfPillars" ) )
{
  QtD1::LevelPillars pillars_town( "levels/towndata/town.min" );
  for( size_t i = 0; i < pillars_town.getNumberOfPillars(); ++i )
    BOOST_CHECK_NO_THROW( pillars_town.getPillar( i ) );

  QtD1::LevelPillars pillars_l1( "levels/l1data/l1.min" );
  for( size_t i = 0; i < pillars_l1.getNumberOfPillars(); ++i )
    BOOST_CHECK_NO_THROW( pillars_l1.getPillar( i ) );

  QtD1::LevelPillars pillars_l2( "levels/l2data/l2.min" );
  for( size_t i = 0; i < pillars_l2.getNumberOfPillars(); ++i )
    BOOST_CHECK_NO_THROW( pillars_l2.getPillar( i ) );

  QtD1::LevelPillars pillars_l3( "levels/l3data/l3.min" );
  for( size_t i = 0; i < pillars_l3.getNumberOfPillars(); ++i )
    BOOST_CHECK_NO_THROW( pillars_l3.getPillar( i ) );

  QtD1::LevelPillars pillars_l4( "levels/l4data/l4.min" );
  for( size_t i = 0; i < pillars_l4.getNumberOfPillars(); ++i )
    BOOST_CHECK_NO_THROW( pillars_l4.getPillar( i ) );
}

//---------------------------------------------------------------------------//
// Check that a pillar width can be returned
BOOST_AUTO_TEST_CASE( getPillarWidth,
                      * boost::unit_test::depends_on( "LevelPillars/getPillar" ) )
{
  QtD1::LevelPillars pillars_town( "levels/towndata/town.min" );
  BOOST_CHECK_EQUAL( pillars_town.getPillarWidth(), 64 );

  QtD1::LevelPillars pillars_l1( "levels/l1data/l1.min" );
  BOOST_CHECK_EQUAL( pillars_l1.getPillarWidth(), 64 );

  QtD1::LevelPillars pillars_l2( "levels/l2data/l2.min" );
  BOOST_CHECK_EQUAL( pillars_l2.getPillarWidth(), 64 );

  QtD1::LevelPillars pillars_l3( "levels/l3data/l3.min" );
  BOOST_CHECK_EQUAL( pillars_l3.getPillarWidth(), 64 );

  QtD1::LevelPillars pillars_l4( "levels/l4data/l4.min" );
  BOOST_CHECK_EQUAL( pillars_l4.getPillarWidth(), 64 );
}

//---------------------------------------------------------------------------//
// Check that a pillar height can be returned
BOOST_AUTO_TEST_CASE( getPillarHeigth,
                      * boost::unit_test::depends_on( "LevelPillars/getPillar" ) )
{
  QtD1::LevelPillars pillars_town( "levels/towndata/town.min" );
  BOOST_CHECK_EQUAL( pillars_town.getPillarHeight(), 256 );

  QtD1::LevelPillars pillars_l1( "levels/l1data/l1.min" );
  BOOST_CHECK_EQUAL( pillars_l1.getPillarHeight(), 160 );

  QtD1::LevelPillars pillars_l2( "levels/l2data/l2.min" );
  BOOST_CHECK_EQUAL( pillars_l2.getPillarHeight(), 160 );

  QtD1::LevelPillars pillars_l3( "levels/l3data/l3.min" );
  BOOST_CHECK_EQUAL( pillars_l3.getPillarHeight(), 160 );

  QtD1::LevelPillars pillars_l4( "levels/l4data/l4.min" );
  BOOST_CHECK_EQUAL( pillars_l4.getPillarHeight(), 256 );
}

BOOST_AUTO_TEST_SUITE_END()

//---------------------------------------------------------------------------//
// end tstLevelPillars.cpp
//---------------------------------------------------------------------------//
