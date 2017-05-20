//---------------------------------------------------------------------------//
//!
//! \file   Viewport.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The viewport class declaration
//!
//---------------------------------------------------------------------------//

#ifndef VIEWPORT_H
#define VIEWPORT_H

// Std Lib Includes
#include <functional>

// Qt Includes
#include <QObject>
#include <QImage>
#include <QRectF>

// QtD1 Includes
#include "QMLRegistrationHelper.h"

namespace QtD1{

//! The viewport class
class Viewport : public QObject
{
  Q_OBJECT
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Viewport" )
  
public:
  
  //! The display policy enum
  enum DisplayPolicy{
    NoStretch_AlignSourceTopLeftWithElementTopLeft,
    NoStretch_AlignSourceTopCenterWithElementTopCenter,
    NoStretch_AlignSourceCenterLeftWithElementCenterLeft,
    NoStretch_AlignSourceCenterWithElementCenter,
    StretchToFit
  };
  Q_ENUMS(DisplayPolicy)

  //! Calculate the source and target viewports given an image
  template<typename ImageType>
  static void calculateViewports( const DisplayPolicy policy,
                                  const QRectF& element_bounding_rect,
                                  const ImageType& source_image,
                                  QRectF& source_viewport,
                                  QRectF& target_viewport );

private:

  // The viewport dimension calculation method
  typedef std::function<void(const qreal,const qreal,const qreal,qreal&,qreal&,qreal&,qreal&)> CalculateViewportDimensionFunction;

  // Calculate viewports without stretching source
  template<typename ImageType>
  static void calculateViewportsImpl(
            const CalculateViewportDimensionFunction& calculate_viewport_y_dim,
            const CalculateViewportDimensionFunction& calculate_viewport_x_dim,
            const QRectF& element_bounding_rect,
            const ImageType& source_image,
            QRectF& source_viewport,
            QRectF& target_viewport );

  // Calculate viewport data with start alignment
  static void calculateViewportDataStartAlign(
                                   const qreal element_bounding_rect_start_pos,
                                   const qreal element_bounding_rect_extent,
                                   const qreal source_image_extent,
                                   qreal& source_viewport_start_pos,
                                   qreal& source_viewport_extent,
                                   qreal& target_viewport_start_pos,
                                   qreal& target_viewport_extent );

  // Calculate viewport data with center alignment
  static void calculateViewportDataCenterAlign(
                                   const qreal element_bounding_rect_start_pos,
                                   const qreal element_bounding_rect_extent,
                                   const qreal source_image_extent,
                                   qreal& source_viewport_start_pos,
                                   qreal& source_viewport_extent,
                                   qreal& target_viewport_start_pos,
                                   qreal& target_viewport_extent );
  
  // Calculate viewport data with stretch to bounding rect
  static void calculateViewportDataStretchToFit(
                                   const qreal element_bounding_rect_start_pos,
                                   const qreal element_bounding_rect_extent,
                                   const qreal source_image_extent,
                                   qreal& source_viewport_start_pos,
                                   qreal& source_viewport_extent,
                                   qreal& target_viewport_start_pos,
                                   qreal& target_viewport_extent );

  // Calculate the midpoint
  static qreal calculateMidpoint( const qreal lower_point,
                                  const qreal upper_point );
};
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Viewport_def.h"

//---------------------------------------------------------------------------//

#endif // end VIEWPORT_H

//---------------------------------------------------------------------------//
// end Viewport.h
//---------------------------------------------------------------------------//
