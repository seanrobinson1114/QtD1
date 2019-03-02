//---------------------------------------------------------------------------//
//!
//! \file   InteractiveLevelObject.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The interactive level object base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QPainter>
#include <QPen>

// QtD1 Includes
#include "InteractiveLevelObject.h"

namespace QtD1{

// Initialize static member data
QPen InteractiveLevelObject::s_hover_outline_pen =
  InteractiveLevelObject::generateHoverOutlinePen();

// Constructor
InteractiveLevelObject::InteractiveLevelObject( QGraphicsObject* parent )
  : LevelObject( parent ),
    d_paint_with_path( false ),
    d_paint_with_highlight_only( false ),
    d_highlight_color( "white" )
{ /* ... */ }

// Paint the interactive level object
void InteractiveLevelObject::paint( QPainter* painter,
                                    const QStyleOptionGraphicsItem* option,
                                    QWidget* widget )
{
  if( d_paint_with_highlight_only ) 
  {
    painter->fillPath( this->shape(), QBrush(d_highlight_color) );
  }
  else 
  {
    this->paintImpl( painter, option, widget );

    if( d_paint_with_path )
    {
      painter->strokePath( this->shape(), s_hover_outline_pen );
      painter->fillPath( this->shape(), QBrush(QColor("blue")) );
    }

    // this->paintImpl( painter, option, widget );
  }
}

// Check if the object is interactive
bool InteractiveLevelObject::isInteractive() const
{
  return true;
}

// Highlight the object
void InteractiveLevelObject::highlight( const QColor& color ) 
{
  d_paint_with_highlight_only = true;
  d_highlight_color = color;
}

// Unhighlight the object
void InteractiveLevelObject::unhighlight()
{
  d_paint_with_highlight_only = false;
}

// Activate the object
void InteractiveLevelObject::activate()
{
  this->setAcceptHoverEvents( true );
}

// Deactivate the object
void InteractiveLevelObject::deactivate()
{
  this->setAcceptHoverEvents( false );
}

// Handle being targeted by another object
void InteractiveLevelObject::handleBeingTargeted( LevelObject* targeter )
{
  if( targeter->isCharacter() )
  {
    emit targetedByCharacter( targeter );
  }
  else
  {
    emit targeted( targeter );
  }
}

// Handle hover enter events
void InteractiveLevelObject::hoverEnterEvent( QGraphicsSceneHoverEvent* )
{
  d_paint_with_path = true;

  // notify level of hover
  emit hoveringStarted( this->getDescription() );

  //this->update();
}

// Handle hover leave events
void InteractiveLevelObject::hoverLeaveEvent( QGraphicsSceneHoverEvent* )
{
  d_paint_with_path = false;

  // notify level of hover exit
  emit hoveringStopped( QString( "" ) );

  this->update();
}

// Generate the hover outline pen
QPen InteractiveLevelObject::generateHoverOutlinePen()
{
  QPen pen( Qt::yellow );
  pen.setStyle( Qt::SolidLine );
  pen.setWidth( 2 );

  return pen;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end InteractiveLevelObject.cpp
//---------------------------------------------------------------------------//
