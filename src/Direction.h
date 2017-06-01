//---------------------------------------------------------------------------//
//!
//! \file   Direction.h
//! \author Alex Robinson
//! \brief  The direction enum declaration
//!
//---------------------------------------------------------------------------//

#ifndef DIRECTION_H
#define DIRECTION_H

// Qt Includes
#include <QPointF>

namespace QtD1{

//! The direction enum
enum Direction{
  South = 12,
  SouthSouthwest = 11,
  Southwest = 10,
  WestSouthwest = 9,
  West = 8,
  WestNorthwest = 7,
  Northwest = 6,
  NorthNortwest = 5,
  North = 4,
  NorthNortheast = 3,
  Northeast = 2,
  EastNortheast = 1,
  East = 0,
  EastSoutheast = 15,
  Southeast = 14,
  SouthSoutheast = 13,
};

//! Calculate the discrete direction
Direction calculateDiscreteDirection(
                   const QPointF start_pos,
                   const QPointF end_pos,
                   const bool use_secondary_intercardinal_directions = false );

//! Get the direction vector corresponding to the direction enum
QPointF getDirectionVector( const Direction direction );
  
} // end QtD1 namespace

#endif // end DIRECTION_H

//---------------------------------------------------------------------------//
// end Direction.h
//---------------------------------------------------------------------------//
