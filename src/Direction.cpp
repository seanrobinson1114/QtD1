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

namespace QtD1{

// Calculate the discrete direction
Direction calculateDiscreteDirection(
                            const QPointF start_pos,
                            const QPointF end_pos,
                            const bool use_secondary_intercardinal_directions )
{
  // Calculate the true angle (in radians) of the direction
  double direction_angle =
    atan2( end_pos.y()-start_pos.y(), end_pos.x()-start_pos.x() );

  // We want the discrete direction that is closest to the true direction. To
  // do this we will divide the unit circle into twice as many sections as
  // there are discrete directions. If the sub-discrete direction is an odd
  // number, we know that we should choose the next discrete direction that is
  // greater than the sub-discrete direction (integer division will always
  // result in a rounding down to the nearest integer).
  int sub_discrete_direction;

  if( use_secondary_intercardinal_directions )
    sub_discrete_direction = direction_angle/PI_OVER_16;
  else
    sub_discrete_direction = direction_angle/PI_OVER_8;

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
  
  return QPointF(cos(discrete_direction_angle), sin(discrete_direction_angle));
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Direction.cpp
//---------------------------------------------------------------------------//
