//---------------------------------------------------------------------------//
//!
//! \file   InteractiveLevelObject.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The interactive level object base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef INTERACTIVE_LEVEL_OBJECT_H
#define INTERACTIVE_LEVEL_OBJECT_H

// QtD1 Includes
#include "LevelObject.h"

namespace QtD1{

//! The interactive level object base class
class InteractiveLevelObject: public LevelObject
{
  Q_OBJECT

public:

  //! Constructor
  InteractiveLevelObject( QGraphicsObject* parent = 0 );

  //! Destructor
  ~InteractiveLevelObject()
  { /* ... */ }

  //! Paint the interactive level object
  void paint( QPainter* painter,
              const QStyleOptionGraphicsItem* option,
              QWidget* widget ) override;

public slots:
  
  //! Activate the object
  void activate();

  //! Deactivate the object
  void deactivate();

protected:

  //! The paint implementation
  virtual void paintImpl( QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget ) = 0;

  //! Handle hover enter events
  void hoverEnterEvent( QGraphicsSceneHoverEvent* event ) override;

  //! Handle hover leave events
  void hoverLeaveEvent( QGraphicsSceneHoverEvent* event ) override;

  //! Handle mouse press events
  void mousePressEvent( QGraphicsSceneMouseEvent* event ) override;

  //! Handle mouse release events
  void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

private:

  // Generate the hover outline pen
  static QPen generateHoverOutlinePen();

  // The hover outline pen
  static QPen s_hover_outline_pen;

  // Records if the object should be painted with its path
  bool d_paint_with_path;
};
  
} // end QtD1 namespace

#endif // end INTERACTIVE_LEVEL_OBJECT_H

//---------------------------------------------------------------------------//
// end InteractiveLevelObject.h
//---------------------------------------------------------------------------//
