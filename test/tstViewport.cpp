//---------------------------------------------------------------------------//
//!
//! \file   tstViewport.cpp
//! \author Alex Robinson
//! \brief  The viewport unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>
#include <QImage>
#include <QPixmap>

// QtD1 Includes
#include "Viewport.h"

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestViewport : public QObject
{
  Q_OBJECT

private slots:

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the viewport can be calculated for top left alignment
void calculateViewports_topleft()
{
  QImage image( 200, 100, QImage::Format_ARGB32 );
  QRectF element_bounding_rect( 0, 0, 300., 200. );
  
  QRectF source_viewport, target_viewport;

  QtD1::Viewport::calculateViewports(
            QtD1::Viewport::NoStretch_AlignSourceTopLeftWithElementTopLeft,
            element_bounding_rect,
            image,
            source_viewport,
            target_viewport );

  QCOMPARE( source_viewport.left(), 0. );
  QCOMPARE( source_viewport.top(), 0. );
  QCOMPARE( source_viewport.width(), 200. );
  QCOMPARE( source_viewport.height(), 100. );

  QCOMPARE( target_viewport.left(), 0. );
  QCOMPARE( target_viewport.top(), 0. );
  QCOMPARE( target_viewport.width(), 200. );
  QCOMPARE( target_viewport.height(), 100. );
  
  QPixmap pixmap( 400, 300 );
  element_bounding_rect = QRectF( 200., 100., 300., 200. );

  QtD1::Viewport::calculateViewports(
            QtD1::Viewport::NoStretch_AlignSourceTopLeftWithElementTopLeft,
            element_bounding_rect,
            pixmap,
            source_viewport,
            target_viewport );

  QCOMPARE( source_viewport.left(), 0. );
  QCOMPARE( source_viewport.top(), 0. );
  QCOMPARE( source_viewport.width(), 300. );
  QCOMPARE( source_viewport.height(), 200. );

  QCOMPARE( target_viewport.left(), 200. );
  QCOMPARE( target_viewport.top(), 100. );
  QCOMPARE( target_viewport.width(), 300. );
  QCOMPARE( target_viewport.height(), 200. );
}

//---------------------------------------------------------------------------//
// Check that the viewport can be calculated for top center alignment
void calculateViewports_topCenter()
{
  QImage image( 200, 100, QImage::Format_ARGB32 );
  QRectF element_bounding_rect( 0, 0, 300., 200. );
  
  QRectF source_viewport, target_viewport;

  QtD1::Viewport::calculateViewports(
        QtD1::Viewport::NoStretch_AlignSourceTopCenterWithElementTopCenter,
        element_bounding_rect,
        image,
        source_viewport,
        target_viewport );

  QCOMPARE( source_viewport.left(), 0. );
  QCOMPARE( source_viewport.top(), 0. );
  QCOMPARE( source_viewport.width(), 200. );
  QCOMPARE( source_viewport.height(), 100. );

  QCOMPARE( target_viewport.left(), 50. );
  QCOMPARE( target_viewport.top(), 0. );
  QCOMPARE( target_viewport.width(), 200. );
  QCOMPARE( target_viewport.height(), 100. );
  
  QPixmap pixmap( 400, 300 );
  element_bounding_rect = QRectF( 200., 100., 300., 200. );

  QtD1::Viewport::calculateViewports(
        QtD1::Viewport::NoStretch_AlignSourceTopCenterWithElementTopCenter,
        element_bounding_rect,
        pixmap,
        source_viewport,
        target_viewport );

  QCOMPARE( source_viewport.left(), 50. );
  QCOMPARE( source_viewport.top(), 0. );
  QCOMPARE( source_viewport.width(), 300. );
  QCOMPARE( source_viewport.height(), 200. );

  QCOMPARE( target_viewport.left(), 200. );
  QCOMPARE( target_viewport.top(), 100. );
  QCOMPARE( target_viewport.width(), 300. );
  QCOMPARE( target_viewport.height(), 200. );
}

//---------------------------------------------------------------------------//
// Check that the viewport can be calculated for center left alignment
void calculateViewports_centerLeft()
{
  QImage image( 200, 100, QImage::Format_ARGB32 );
  QRectF element_bounding_rect( 0, 0, 300., 200. );
  
  QRectF source_viewport, target_viewport;

  QtD1::Viewport::calculateViewports(
      QtD1::Viewport::NoStretch_AlignSourceCenterLeftWithElementCenterLeft,
      element_bounding_rect,
      image,
      source_viewport,
      target_viewport );

  QCOMPARE( source_viewport.left(), 0. );
  QCOMPARE( source_viewport.top(), 0. );
  QCOMPARE( source_viewport.width(), 200. );
  QCOMPARE( source_viewport.height(), 100. );

  QCOMPARE( target_viewport.left(), 0. );
  QCOMPARE( target_viewport.top(), 50. );
  QCOMPARE( target_viewport.width(), 200. );
  QCOMPARE( target_viewport.height(), 100. );
  
  QPixmap pixmap( 400, 300 );
  element_bounding_rect = QRectF( 200., 100., 300., 200. );

  QtD1::Viewport::calculateViewports(
      QtD1::Viewport::NoStretch_AlignSourceCenterLeftWithElementCenterLeft,
      element_bounding_rect,
      pixmap,
      source_viewport,
      target_viewport );

  QCOMPARE( source_viewport.left(), 0. );
  QCOMPARE( source_viewport.top(), 50. );
  QCOMPARE( source_viewport.width(), 300. );
  QCOMPARE( source_viewport.height(), 200. );

  QCOMPARE( target_viewport.left(), 200. );
  QCOMPARE( target_viewport.top(), 100. );
  QCOMPARE( target_viewport.width(), 300. );
  QCOMPARE( target_viewport.height(), 200. );
}

//---------------------------------------------------------------------------//
// Check that the viewport can be calculated for center alignment
void calculateViewports_center()
{
  QImage image( 200, 100, QImage::Format_ARGB32 );
  QRectF element_bounding_rect( 0, 0, 300., 200. );
  
  QRectF source_viewport, target_viewport;

  QtD1::Viewport::calculateViewports(
              QtD1::Viewport::NoStretch_AlignSourceCenterWithElementCenter,
              element_bounding_rect,
              image,
              source_viewport,
              target_viewport );

  QCOMPARE( source_viewport.left(), 0. );
  QCOMPARE( source_viewport.top(), 0. );
  QCOMPARE( source_viewport.width(), 200. );
  QCOMPARE( source_viewport.height(), 100. );

  QCOMPARE( target_viewport.left(), 50. );
  QCOMPARE( target_viewport.top(), 50. );
  QCOMPARE( target_viewport.width(), 200. );
  QCOMPARE( target_viewport.height(), 100. );
  
  QPixmap pixmap( 400, 300 );
  element_bounding_rect = QRectF( 200., 100., 300., 200. );

  QtD1::Viewport::calculateViewports(
              QtD1::Viewport::NoStretch_AlignSourceCenterWithElementCenter,
              element_bounding_rect,
              pixmap,
              source_viewport,
              target_viewport );

  QCOMPARE( source_viewport.left(), 50. );
  QCOMPARE( source_viewport.top(), 50. );
  QCOMPARE( source_viewport.width(), 300. );
  QCOMPARE( source_viewport.height(), 200. );

  QCOMPARE( target_viewport.left(), 200. );
  QCOMPARE( target_viewport.top(), 100. );
  QCOMPARE( target_viewport.width(), 300. );
  QCOMPARE( target_viewport.height(), 200. );
}

//---------------------------------------------------------------------------//
// Check that the viewport can be calculated for a stretch-to-fit
void calculateViewports_stretchToFit()
{
  QImage image( 200, 100, QImage::Format_ARGB32 );
  QRectF element_bounding_rect( 0, 0, 300., 200. );
  
  QRectF source_viewport, target_viewport;

  QtD1::Viewport::calculateViewports(
                                    QtD1::Viewport::StretchToFit,
                                    element_bounding_rect,
                                    image,
                                    source_viewport,
                                    target_viewport );

  QCOMPARE( source_viewport.left(), 0. );
  QCOMPARE( source_viewport.top(), 0. );
  QCOMPARE( source_viewport.width(), 200. );
  QCOMPARE( source_viewport.height(), 100. );

  QCOMPARE( target_viewport.left(), 0. );
  QCOMPARE( target_viewport.top(), 0. );
  QCOMPARE( target_viewport.width(), 300. );
  QCOMPARE( target_viewport.height(), 200. );

  QPixmap pixmap( 400, 300 );
  element_bounding_rect = QRectF( 200., 100., 300., 200. );

  QtD1::Viewport::calculateViewports(
                                    QtD1::Viewport::StretchToFit,
                                    element_bounding_rect,
                                    pixmap,
                                    source_viewport,
                                    target_viewport );

  QCOMPARE( source_viewport.left(), 0. );
  QCOMPARE( source_viewport.top(), 0. );
  QCOMPARE( source_viewport.width(), 400. );
  QCOMPARE( source_viewport.height(), 300. );

  QCOMPARE( target_viewport.left(), 200. );
  QCOMPARE( target_viewport.top(), 100. );
  QCOMPARE( target_viewport.width(), 300. );
  QCOMPARE( target_viewport.height(), 200. );
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestViewport )
#include "tstViewport.moc"

//---------------------------------------------------------------------------//
// end tstViewport.cpp
//---------------------------------------------------------------------------//
