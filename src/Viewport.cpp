//---------------------------------------------------------------------------//
//!
//! \file   Viewport.cpp
//! \author Alex Robinson
//! \brief  The viewport class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Viewport.h"

namespace QtD1{

// Calculate viewport data with start alignment
void Viewport::calculateViewportDataStartAlign(
                                   const qreal element_bounding_rect_start_pos,
                                   const qreal element_bounding_rect_extent,
                                   const qreal source_image_extent,
                                   qreal& source_viewport_start_pos,
                                   qreal& source_viewport_extent,
                                   qreal& target_viewport_start_pos,
                                   qreal& target_viewport_extent )
{
  source_viewport_start_pos = 0;
  target_viewport_start_pos = element_bounding_rect_start_pos;

  if( source_image_extent >= element_bounding_rect_extent )
  {
    source_viewport_extent = element_bounding_rect_extent;
    target_viewport_extent = source_viewport_extent;
  }
  else
  {
    source_viewport_extent = source_image_extent;
    target_viewport_extent = source_viewport_extent;
  }
}

// Calculate viewport data
void Viewport::calculateViewportDataCenterAlign(
                                   const qreal element_bounding_rect_start_pos,
                                   const qreal element_bounding_rect_extent,
                                   const qreal source_image_extent,
                                   qreal& source_viewport_start_pos,
                                   qreal& source_viewport_extent,
                                   qreal& target_viewport_start_pos,
                                   qreal& target_viewport_extent )
{
  if( source_image_extent >= element_bounding_rect_extent )
  {
    source_viewport_extent = element_bounding_rect_extent;
    target_viewport_extent = source_viewport_extent;
    target_viewport_start_pos = element_bounding_rect_start_pos;

    qreal mid_pos = Viewport::calculateMidpoint( 0, source_image_extent );

    source_viewport_start_pos = mid_pos - source_viewport_extent/2.0;
  }
  else
  {
    source_viewport_extent = source_image_extent;
    target_viewport_extent = source_viewport_extent;
    source_viewport_start_pos = 0;
    
    qreal mid_pos = Viewport::calculateMidpoint(
              element_bounding_rect_start_pos,
              element_bounding_rect_start_pos + element_bounding_rect_extent );
    
    target_viewport_start_pos = mid_pos - target_viewport_extent/2.0;
  }
}

// Calculate viewport data with stretch to bounding rect
void Viewport::calculateViewportDataStretchToFit(
                                   const qreal element_bounding_rect_start_pos,
                                   const qreal element_bounding_rect_extent,
                                   const qreal source_image_extent,
                                   qreal& source_viewport_start_pos,
                                   qreal& source_viewport_extent,
                                   qreal& target_viewport_start_pos,
                                   qreal& target_viewport_extent )
{
  source_viewport_start_pos = 0;
  source_viewport_extent = source_image_extent;

  target_viewport_start_pos = element_bounding_rect_start_pos;
  target_viewport_extent = element_bounding_rect_extent;
}

// Calculate the midpoint
qreal Viewport::calculateMidpoint( const qreal lower_point,
                                   const qreal upper_point )
{
  return (lower_point + upper_point)/2.0;
}

QML_REGISTER_TYPE( Viewport );
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Viewport.cpp
//---------------------------------------------------------------------------//
