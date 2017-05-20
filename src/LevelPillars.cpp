//---------------------------------------------------------------------------//
//!
//! \file   LevelPillars.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillars class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "LevelPillars.h"
#include "MPQHandler.h"
#include "SDLRWOpsWrapper.h"

namespace QtD1{

// Constructor
LevelPillars::LevelPillars( const std::string& min_filename )
  : d_pillars()
{
  // Extract the min file
  std::shared_ptr<std::vector<uint8_t> > buffer( new std::vector<uint8_t> );

  MPQHandler::getInstance()->extractFile( min_filename, *buffer );
  
  SDLRWOpsWrapper buffer_stream( buffer );

  // Convert the file name to a file path
  boost::filesystem::path file_path( min_filename );

  // Get the file name without a path
  const std::string filename_without_path = file_path.filename().string();

  // Get the pillar size
  size_t pillar_size;

  if( filename_without_path == "l1.min" ||
      filename_without_path == "l2.min" ||
      filename_without_path == "l3.min" )
    pillar_size = 10;
  else if( filename_without_path == "l4.min" ||
           filename_without_path == "town.min" )
    pillar_size = 16;

  while( buffer_stream.tell() <= buffer_stream.size() - 1 )
  {
    std::vector<uint16_t> raw_pillar( pillar_size );

    buffer_stream.read<LittleToNative>( raw_pillar, pillar_size );

    std::vector<uint32_t> pillar( pillar_size );

    for( size_t i = 0; i < pillar_size; ++i )
    {
      uint32_t frame_number = (uint32_t)(raw_pillar[i] & 0x0FFF);

      // check if its a valid frame
      if( frame_number != 0 )
        pillar[i] = frame_number;

      pillar[i] -= 1; // start indices from 0 not 1
    }

    d_pillars.push_back( pillar );
  }

  // Calculate and set the pillar height
  pillar_height = 32 * d_pillars[0].size() / 2;
}

// Return the number of pillars
size_t LevelPillars::getNumberOfPillars()
{
  return d_pillars.size();
}

// Return a pillar
const std::vector<uint32_t>& LevelPillars::getPillar( size_t pillar_index ) const
{
  return d_pillars[pillar_index];
}

// Return the width of a pillar
size_t LevelPillars::getPillarWidth()
{
  return pillar_width;
}

// Return the height of a pillar
size_t LevelPillars::getPillarHeight()
{
  return pillar_height;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelPillars.cpp
//---------------------------------------------------------------------------//
