//---------------------------------------------------------------------------//
//!
//! \file   LevelPillars.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Level pillars class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_PILLARS_H
#define LEVEL_PILLARS_H

// Std Lib Includes
#include <string>
#include <vector>

namespace QtD1{

//! The level pillars class
class LevelPillars
{

public:

  //! Constructor
  LevelPillars( const std::string& min_filename );

  //! Destructor
  ~LevelPillars()
  { /* ... */ }

  //! Return the number of pillars
  size_t getNumberOfPillars();

  //! Return a pillar
  const std::vector<uint32_t>& getPillar( size_t pillar_index ) const;

  //! Return the width of a pillar
  size_t getPillarWidth();

  //! Return the height of a pillar
  size_t getPillarHeight();

private:

  // The pillars
  // Note: A pillar is simply an array of unsigned integers that correspond to
  //       cel frame indices.
  std::vector<std::vector<uint32_t> > d_pillars;

  // Width of pillar
  const size_t pillar_width = 64;

  // Height of pillar
  size_t pillar_height;
};

} // end QtD1 namespace

#endif // end LEVEL_PILLARS_H


//---------------------------------------------------------------------------//
// end LevelPillars.h
//---------------------------------------------------------------------------//
