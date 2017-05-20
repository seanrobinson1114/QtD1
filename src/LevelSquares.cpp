//---------------------------------------------------------------------------//
//!
//! \file   LevelSquares.cpp
//! \author Sean Robinson
//! \brief  Level squares class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "LevelSquares.h"
#include "LevelPillars.h"
#include "MPQHandler.h"
#include "SDLRWOpsWrapper.h"
#include "ExceptionCatchMacros.h"

namespace QtD1{

// Constructor
LevelSquares::LevelSquares( const std::string& til_filename )
  : d_squares(),
    d_square_height( 0 )
{
  // Extract the til file
  std::shared_ptr<std::vector<uint8_t> > buffer( new std::vector<uint8_t> );

  MPQHandler::getInstance()->extractFile( til_filename, *buffer );
  
  SDLRWOpsWrapper buffer_stream( buffer );

  // Convert the file name to a file path
  boost::filesystem::path file_path( til_filename );

  // Get the file name without a path
  const std::string filename_without_path = file_path.filename().string();

  // All squares are four pillars
  size_t square_size = 4;

  // Get corresponding min file
  size_t extension_start = til_filename.find_last_of( "." );
  std::string min_filename = til_filename.substr( 0, extension_start ) + ".min";


  std::unique_ptr<LevelPillars> pillars;

  // Create pillars from corresponding .min file
  pillars.reset( new LevelPillars( min_filename ) );
  
  while( buffer_stream.tell() <= buffer_stream.size() - 1 )
  {
    std::vector<uint16_t> raw_square( square_size );

    buffer_stream.read<LittleToNative>( raw_square, square_size );

    std::vector<std::vector<uint32_t> > square( square_size );

    // The order of pillars: top, right, left, bottom
    for( size_t i = 0; i < square_size; ++i )
    {
      // Get the corresponding pillar
      uint32_t pillar_number = (uint32_t)(raw_square[i]);
      square[i] = pillars->getPillar( pillar_number );
    }

    d_squares.push_back( square );
  }

  // Calculate and set the square Height
  d_square_height = pillars->getPillarHeight() + 32;
}

// Return the number of squares
size_t LevelSquares::getNumberOfSquares()
{
  return d_squares.size();
}

// Return a square
const std::vector<std::vector<uint32_t> >& LevelSquares::getSquare( size_t square_index ) const
{
  return d_squares[square_index];
}

// Return the top pillar in a square
const std::vector<uint32_t>& LevelSquares::getTopPillar( size_t square_index ) const
{
  return d_squares[square_index][0];
}

// Return the right pillar in a square
const std::vector<uint32_t>& LevelSquares::getRightPillar( size_t square_index ) const
{
  return d_squares[square_index][1];
}

// Return the left pillar in a square
const std::vector<uint32_t>& LevelSquares::getLeftPillar( size_t square_index ) const
{
  return d_squares[square_index][2];
}

// Return the bottom pillar in a square
const std::vector<uint32_t>& LevelSquares::getBottomPillar( size_t square_index ) const
{
  return d_squares[square_index][3];
}

//! Return the width of a square
size_t LevelSquares::getSquareWidth()
{
  return s_square_width;
}

//! Return the height of a square
size_t LevelSquares::getSquareHeight()
{
  return d_square_height;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelSquares.cpp
//---------------------------------------------------------------------------//
