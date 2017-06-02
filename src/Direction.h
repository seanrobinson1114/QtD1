//---------------------------------------------------------------------------//
//!
//! \file   Direction.h
//! \author Alex Robinson
//! \brief  The direction enum declaration
//!
//---------------------------------------------------------------------------//

#ifndef DIRECTION_H
#define DIRECTION_H

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QString>
#include <QPointF>
#include <QMetaType>

namespace QtD1{

/*! The direction enum
 * \details The directions are listed in the same order that direction sprites
 * found in the mpq file are given in. The integer that each direction maps
 * to is the corresponding location on the unit sphere (in units of pi/8).
 */
enum Direction{
  South = 12,
  SouthSouthwest = 11,
  Southwest = 10,
  WestSouthwest = 9,
  West = 8,
  WestNorthwest = 7,
  Northwest = 6,
  NorthNorthwest = 5,
  North = 4,
  NorthNortheast = 3,
  Northeast = 2,
  EastNortheast = 1,
  East = 0,
  EastSoutheast = 15,
  Southeast = 14,
  SouthSoutheast = 13,
};

//! Convert the direction to a string
QString directionToString( const Direction direction );

//! Calculate the nearest discrete direction
Direction calculateNearestDiscreteDirection(
                   const QPointF start_pos,
                   const QPointF end_pos,
                   const bool use_secondary_intercardinal_directions = false );

//! Get the direction vector corresponding to the direction enum
QPointF getDirectionVector( const Direction direction );

//! Output stream operator
inline std::ostream& operator<<( std::ostream& os, const Direction direction )
{
  os << directionToString( direction ).toStdString();

  return os;
}
  
} // end QtD1 namespace

Q_DECLARE_METATYPE( QtD1::Direction )

#endif // end DIRECTION_H

//---------------------------------------------------------------------------//
// end Direction.h
//---------------------------------------------------------------------------//
