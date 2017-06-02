//---------------------------------------------------------------------------//
//!
//! \file   Direction.cpp
//! \author Alex Robinson
//! \brief  The direction enum declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>

// QtD1 Includes
#include "Direction.h"

#define PI_OVER_8 0.39269908169872414
#define PI_OVER_16 0.19634954084936207
#define TWO_PI 6.283185307179586
#define ROUNDING_TOL 1e-14

namespace QtD1{

// Convert the direction to a string
QString directionToString( const Direction direction )
{
  switch( direction )
  {
    case South: return "South";
    case SouthSouthwest: return "South-southwest";
    case Southwest: return "Southwest";
    case WestSouthwest: return "West-southwest";
    case West: return "West";
    case WestNorthwest: return "West-northwest";
    case Northwest: return "Northwest";
    case NorthNorthwest: return "North-northwest";
    case North: return "North";
    case NorthNortheast: return "North-northeast";
    case Northeast: return "Northeast";
    case EastNortheast: return "East-northeast";
    case East: return "East";
    case EastSoutheast: return "East-southeast";
    case Southeast: return "Southeast";
    case SouthSoutheast: return "South-southeast";
    default:
    {
      qFatal( "Error: unsupported direction %i cannot be converted to a "
              "string!", direction );
      return QString();
    }
  }
}

// Calculate the discrete direction
Direction calculateNearestDiscreteDirection(
                            const QPointF start_pos,
                            const QPointF end_pos,
                            const bool use_secondary_intercardinal_directions )
{
  // Calculate the true angle (in radians) of the direction
  // Note: The negative of the y component of the dirction will be used since
  //       moving up the screen is actually moving down in the screen
  //       coordinate system.
  double direction_angle =
    atan2( start_pos.y()-end_pos.y(), end_pos.x()-start_pos.x() );

  if( direction_angle < 0.0 )
    direction_angle += TWO_PI;

  // We want the discrete direction that is closest to the true direction. To
  // do this we will divide the unit circle into twice as many sections as
  // there are discrete directions. If the sub-discrete direction is an odd
  // number, we know that we should choose the next discrete direction that is
  // greater than the sub-discrete direction (integer division will always
  // result in a rounding down to the nearest integer).
  double raw_sub_discrete_direction;

  if( use_secondary_intercardinal_directions )
    raw_sub_discrete_direction = direction_angle/PI_OVER_16;
  else
    raw_sub_discrete_direction = direction_angle/PI_OVER_8;

  // Fix rounding errors
  if( 1.0 - modf( raw_sub_discrete_direction, &raw_sub_discrete_direction ) < ROUNDING_TOL )
    raw_sub_discrete_direction += 1;

  int sub_discrete_direction = raw_sub_discrete_direction;
  
  if( sub_discrete_direction % 2 == 1 )
    ++sub_discrete_direction;

  if( use_secondary_intercardinal_directions )
    return static_cast<Direction>( (sub_discrete_direction%32)/2 );
  else
    return static_cast<Direction>( (sub_discrete_direction%16) );
}

// Get the direction vector corresponding to the direction enum
QPointF getDirectionVector( const Direction direction )
                                  
{
  double discrete_direction_angle = direction*PI_OVER_8;

  // Note: The negative of the sine will be used since moving up the screen
  //       is actually moving down in the screen coordinate system.
  return QPointF(cos(discrete_direction_angle), -sin(discrete_direction_angle));
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Direction.cpp
//---------------------------------------------------------------------------//
