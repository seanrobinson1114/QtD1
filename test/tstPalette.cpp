//---------------------------------------------------------------------------//
//!
//! \file   tstPalette.h
//! \author Alex Robinson
//! \brief  The palette unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <memory>

// Boost Includes
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// Rocket Includes
#include <Rocket/Core.h>

// QtD1 Includes
#include "Palette.h"
#include "FileInterface.h"
#include "GlobalSDLSession.h"
#include "RuntimeSettings.h"

//---------------------------------------------------------------------------//
// Testing Structures
//---------------------------------------------------------------------------//
struct GlobalInitFixture
{
  GlobalInitFixture()
    : session()
  {
    std::shared_ptr<const QtD1::RuntimeSettings>
      settings( new QtD1::RuntimeSettings );
    
    QtD1::FileInterface* file_interface =
      QtD1::FileInterface::getInstance( settings );

    Rocket::Core::SetFileInterface( file_interface );
  }

private:

  QtD1::GlobalSDLSession session;
};

// Register the global fixture
BOOST_GLOBAL_FIXTURE( GlobalInitFixture );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an instance of a palette can be constructed
BOOST_AUTO_TEST_CASE( constructor )
{
  Rocket::Core::FileInterface* file_interface =
    Rocket::Core::GetFileInterface();

  // Load a file into a byte buffer
  Rocket::Core::FileHandle file = file_interface->Open( "levels/towndata/town.pal" );
  std::vector<uint8_t> buffer( file_interface->Length( file ) );
  file_interface->Read( &buffer[0], buffer.size(), file );

  // Create a new palette from the file buffer
  BOOST_CHECK_NO_THROW( QtD1::Palette palette( buffer ) );

  // Close the file
  file_interface->Close( file );
}

//---------------------------------------------------------------------------//
// Check that the color can be returned
BOOST_AUTO_TEST_CASE( getColor,
                      * boost::unit_test::depends_on( "constructor" ) )
{
  Rocket::Core::FileInterface* file_interface =
    Rocket::Core::GetFileInterface();

  // Load a file into a byte buffer
  Rocket::Core::FileHandle file = file_interface->Open( "levels/towndata/town.pal" );
  std::vector<uint8_t> buffer( file_interface->Length( file ) );
  file_interface->Read( &buffer[0], buffer.size(), file );

  // Create a new palette from the file buffer
  QtD1::Palette palette( buffer );

  // Get colors from the palette
  SDL_Color color = palette.getColor( 0 );

  BOOST_CHECK_EQUAL( color.r, 0 );
  BOOST_CHECK_EQUAL( color.g, 0 );
  BOOST_CHECK_EQUAL( color.b, 0 );
  BOOST_CHECK_EQUAL( color.a, 255 );

  color = palette.getColor( 1 );

  BOOST_CHECK_EQUAL( color.r, 181 );
  BOOST_CHECK_EQUAL( color.g, 93 );
  BOOST_CHECK_EQUAL( color.b, 27 );
  BOOST_CHECK_EQUAL( color.a, 255 );

  color = palette.getColor( 2 );

  BOOST_CHECK_EQUAL( color.r, 165 );
  BOOST_CHECK_EQUAL( color.g, 93 );
  BOOST_CHECK_EQUAL( color.b, 54 );
  BOOST_CHECK_EQUAL( color.a, 255 );

  // Close the file
  file_interface->Close( file );
}

//---------------------------------------------------------------------------//
// Check that the color can be returned
BOOST_AUTO_TEST_CASE( get_operator,
                      * boost::unit_test::depends_on( "constructor" ) )
{
  Rocket::Core::FileInterface* file_interface =
    Rocket::Core::GetFileInterface();

  // Load a file into a byte buffer
  Rocket::Core::FileHandle file = file_interface->Open( "levels/towndata/town.pal" );
  std::vector<uint8_t> buffer( file_interface->Length( file ) );
  file_interface->Read( &buffer[0], buffer.size(), file );

  // Create a new palette from the file buffer
  QtD1::Palette palette( buffer );

  // Get colors from the palette
  BOOST_CHECK_EQUAL( palette[0].r, 0 );
  BOOST_CHECK_EQUAL( palette[0].g, 0 );
  BOOST_CHECK_EQUAL( palette[0].b, 0 );
  BOOST_CHECK_EQUAL( palette[0].a, 255 );

  BOOST_CHECK_EQUAL( palette[1].r, 181 );
  BOOST_CHECK_EQUAL( palette[1].g, 93 );
  BOOST_CHECK_EQUAL( palette[1].b, 27 );
  BOOST_CHECK_EQUAL( palette[1].a, 255 );

  BOOST_CHECK_EQUAL( palette[2].r, 165 );
  BOOST_CHECK_EQUAL( palette[2].g, 93 );
  BOOST_CHECK_EQUAL( palette[2].b, 54 );
  BOOST_CHECK_EQUAL( palette[2].a, 255 );

  // Close the file
  file_interface->Close( file );
}

//---------------------------------------------------------------------------//
// end tstPalette.h
//---------------------------------------------------------------------------//
