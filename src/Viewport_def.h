//---------------------------------------------------------------------------//
//!
//! \file   Viewport_def.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The viewport class definition
//!
//---------------------------------------------------------------------------//

#ifndef VIEWPORT_DEF_H
#define VIEWPORT_DEF_H

namespace QtD1{

// Calculate the source and target viewports given an image
template<typename ImageType>
void Viewport::calculateViewports( const DisplayPolicy policy,
                                   const QRectF& element_bounding_rect,
                                   const ImageType& source_image,
                                   QRectF& source_viewport,
                                   QRectF& target_viewport )
{
  switch( policy )
  {
    case NoStretch_AlignSourceTopLeftWithElementTopLeft:
    {
      Viewport::calculateViewportsImpl(
                                    &Viewport::calculateViewportDataStartAlign,
                                    &Viewport::calculateViewportDataStartAlign,
                                    element_bounding_rect,
                                    source_image,
                                    source_viewport,
                                    target_viewport );
      break;
    }
    case NoStretch_AlignSourceTopCenterWithElementTopCenter:
    {
      Viewport::calculateViewportsImpl(
                                   &Viewport::calculateViewportDataStartAlign,
                                   &Viewport::calculateViewportDataCenterAlign,
                                   element_bounding_rect,
                                   source_image,
                                   source_viewport,
                                   target_viewport );
      break;
    }
    case NoStretch_AlignSourceCenterLeftWithElementCenterLeft:
    {
      Viewport::calculateViewportsImpl(
                                   &Viewport::calculateViewportDataCenterAlign,
                                   &Viewport::calculateViewportDataStartAlign,
                                   element_bounding_rect,
                                   source_image,
                                   source_viewport,
                                   target_viewport );
      break;
    }
    case NoStretch_AlignSourceCenterWithElementCenter:
    {
      Viewport::calculateViewportsImpl(
                                   &Viewport::calculateViewportDataCenterAlign,
                                   &Viewport::calculateViewportDataCenterAlign,
                                   element_bounding_rect,
                                   source_image,
                                   source_viewport,
                                   target_viewport );
      break;
    }
    case StretchToFit:
    {
      Viewport::calculateViewportsImpl(
                                  &Viewport::calculateViewportDataStretchToFit,
                                  &Viewport::calculateViewportDataStretchToFit,
                                  element_bounding_rect,
                                  source_image,
                                  source_viewport,
                                  target_viewport );
      break;
    }
    default:
    {
      qFatal( "The requested display policy is not supported!" );
    }
  }
}

// Calculate viewports without stretching source
template<typename ImageType>
void Viewport::calculateViewportsImpl(
            const CalculateViewportDimensionFunction& calculate_viewport_y_dim,
            const CalculateViewportDimensionFunction& calculate_viewport_x_dim,
            const QRectF& element_bounding_rect,
            const ImageType& source_image,
            QRectF& source_viewport,
            QRectF& target_viewport )
{
  // Calculate the position of the left side of the viewport and its width
  qreal viewport_source_left, viewport_source_width;
  qreal viewport_target_left, viewport_target_width;

  calculate_viewport_x_dim( element_bounding_rect.left(),
                            element_bounding_rect.width(),
                            source_image.width(),
                            viewport_source_left,
                            viewport_source_width,
                            viewport_target_left,
                            viewport_target_width );

  // Calculate the position of the top side of the viewport and its height
  qreal viewport_source_top, viewport_source_height;
  qreal viewport_target_top, viewport_target_height;

  calculate_viewport_y_dim( element_bounding_rect.top(),
                            element_bounding_rect.height(),
                            source_image.height(),
                            viewport_source_top,
                            viewport_source_height,
                            viewport_target_top,
                            viewport_target_height );
  
  // Set the source viewport
  source_viewport.moveTo( viewport_source_left, viewport_source_top );
  source_viewport.setWidth( viewport_source_width );
  source_viewport.setHeight( viewport_source_height );
  
  // Set the target viewport
  target_viewport.moveTo( viewport_target_left, viewport_target_top );
  target_viewport.setWidth( viewport_target_width );
  target_viewport.setHeight( viewport_target_height );
}
  
} // end QtD1 namespace

#endif // end VIEWPORT_DEF_H

//---------------------------------------------------------------------------//
// end Viewport_def.h
//---------------------------------------------------------------------------//
