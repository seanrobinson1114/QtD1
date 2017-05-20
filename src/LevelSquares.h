//---------------------------------------------------------------------------//
//!
//! \file   LevelSquares.h
//! \author Sean Robinson
//! \brief  Level squares class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_SQUARES_H
#define LEVEL_SQUARES_H

// Std Lib Includes
#include <string>
#include <vector>

// QtD1 Includes
#include "LevelPillars.h"

namespace QtD1{

//! The level pillars class
class LevelSquares
{

public:

  //! Constructor
  LevelSquares( const std::string& til_filename );

  //! Destructor
  ~LevelSquares()
  { /* ... */ }

  //! Return the number of pillars
  size_t getNumberOfSquares();

  //! Return a pillar
  const std::vector<std::vector<uint32_t> >& getSquare( size_t square_index ) const;

  //! Return the top pillar
  const std::vector<uint32_t>& getTopPillar( size_t square_index ) const;

  //! Return the right pillar
  const std::vector<uint32_t>& getRightPillar( size_t square_index ) const;

  //! Return the left pillar
  const std::vector<uint32_t>& getLeftPillar( size_t square_index ) const;

  //! Return the bottom pillar
  const std::vector<uint32_t>& getBottomPillar( size_t square_index ) const;

  //! Return the width of a square
  size_t getSquareWidth();

  //! Return the height of a square
  size_t getSquareHeight();

private:

  // Width of square
  static const size_t s_square_width = 128;

  // The squares
  // Note: A square is four pillars: top, right, left, bottom
  std::vector<std::vector<std::vector<uint32_t> > > d_squares;

  // Height of square
  size_t d_square_height;
};

} // end QtD1 namespace

#endif // end LEVEL_SQUARES_H


//---------------------------------------------------------------------------//
// end LevelSquares.h
//---------------------------------------------------------------------------//
