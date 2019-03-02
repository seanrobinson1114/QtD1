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

  //! Check if object is interactive
  bool isInteractive() const override;

  //! Highlight the object
  void highlight( const QColor& color );

  //! Unhighlight the object
  void unhighlight();

  //! Get a description of the object
  virtual QString getDescription() const = 0;

signals:

  //! Object is being hovered over
  void hoveringStarted( QString object_description );

  //! Object is no longer being hovered over
  void hoveringStopped( QString empty_string );

  //! The object has been targeted by the character
  void targetedByCharacter( LevelObject* targeter );

  //! The object has been targeted by another object
  void targeted( LevelObject* targeter );

public slots:

  //! Activate the object
  void activate();

  //! Deactivate the object
  void deactivate();

protected slots:

  //! Handle being targeted by another object
  void handleBeingTargeted( LevelObject* targeter ) override;

protected:

  //! The paint implementation
  virtual void paintImpl( QPainter* painter,
                          const QStyleOptionGraphicsItem* option,
                          QWidget* widget ) = 0;

  //! Handle hover enter events
  void hoverEnterEvent( QGraphicsSceneHoverEvent* event ) override;

  //! Handle hover leave events
  void hoverLeaveEvent( QGraphicsSceneHoverEvent* event ) override;

private:

  // Generate the hover outline pen
  static QPen generateHoverOutlinePen();

  // The hover outline pen
  static QPen s_hover_outline_pen;

  // Records if the object should be painted with its path
  bool d_paint_with_path;

  // Record if the object should be highlighted
  bool d_paint_with_highlight_only;

  // Record the highlight color
  QColor d_highlight_color;
};

} // end QtD1 namespace

#endif // end INTERACTIVE_LEVEL_OBJECT_H

//---------------------------------------------------------------------------//
// end InteractiveLevelObject.h
//---------------------------------------------------------------------------//
