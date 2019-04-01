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
#include "BitmapText.h"

namespace QtD1{

// Constructor
InteractiveLevelObject::InteractiveLevelObject( QGraphicsObject* parent )
  : LevelObject( parent ),
    d_paint_with_path( false ),
    d_paint_with_highlight_only( false ),
    d_highlight_color( "white" ),
    d_hover_outline_pen()
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
    if( d_paint_with_path )
    {
      if( d_hover_outline_pen )
      {
        painter->strokePath( this->shape(), *d_hover_outline_pen );
      }
      else
      {
        qWarning( "QPen for interactive level object hover outline is NULL: can't paint" );
      }
      // painter->fillPath( this->shape(), QBrush(QColor("blue")) );
    }

    this->paintImpl( painter, option, widget );
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

// Get a processed description of the object
QPixmap InteractiveLevelObject::getDescription() const
{
  return this->processDescriptionText( this->getDescriptionText(),
                                       "QtD1White11",
                                       false,
                                       false );
}

// Process the description text
QPixmap InteractiveLevelObject::processDescriptionText(
                                                   const QString& text,
                                                   const QString& font_name,
                                                   const bool add_line_spacing,
                                                   const bool right_tab )
{
  QStringList raw_text_lines = text.split( '\n' );
  const int font_size = BitmapText::getRegisteredFont( font_name )->getSize();
  
  // Render each line of text separately
  QVector<QPixmap> text_lines( raw_text_lines.size() );
  int width = 0;
  int height = 0;
  int line = 0;
  
  for( auto&& raw_text_line : raw_text_lines )
  {
    BitmapText text_line;
    text_line.setFontName( font_name );
    text_line.setContainerWidth( 640 );
    text_line.setTextWithNoWrap( raw_text_line );
    text_line.load();

    if( width == 0 )
      width = text_line.getPixmap().width();
    else
    {
      if( right_tab )
      {
        if( text_line.getPixmap().width() + 2*font_size > width )
          width = text_line.getPixmap().width() + 2*font_size;
      }
      else
      {
        if( text_line.getPixmap().width() > width )
          width = text_line.getPixmap().width();
      }
    }

    height += text_line.getPixmap().height();

    if( add_line_spacing )
      height += text_line.getPixmap().height();

    text_lines[line] = text_line.getPixmap();
    ++line;
  }

  if( add_line_spacing )
    height -= text_lines.back().height();

  // Create a pixmap that will hold all of the text lines
  QPixmap text_pixmap( width, height );
  text_pixmap.fill( Qt::transparent );
  
  // Paint the lines onto the new pixmap
  QPainter painter( &text_pixmap );
  
  int y = 0;
  int x;

  if( right_tab )
    x = 0;
  else
    x = (width - text_lines.front().width())/2;

  for( int i = 0; i < text_lines.size(); ++i )
  {
    painter.drawPixmap( QPoint( x, y ), text_lines[i] );
    
    // Update the draw position
    if( i < text_lines.size()-1 )
    {
      if( right_tab )
        x = 2*font_size;
      else
        x = (width - text_lines[i+1].width())/2;
      
      y += text_lines[i].height();

      if( add_line_spacing )
        y += text_lines[i].height();
    }
  }

  return text_pixmap;
}

// Set the hover outline color
void InteractiveLevelObject::setHoverOutlineColor( const QColor& outline_color )
{
  d_hover_outline_pen.reset( new QPen( outline_color ) );
  d_hover_outline_pen->setStyle( Qt::SolidLine );
  d_hover_outline_pen->setWidth( 2 );
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

  // this->update();
}

// Handle hover leave events
void InteractiveLevelObject::hoverLeaveEvent( QGraphicsSceneHoverEvent* )
{
  d_paint_with_path = false;

  // notify level of hover exit
  emit hoveringStopped( QPixmap() );

  this->update();
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end InteractiveLevelObject.cpp
//---------------------------------------------------------------------------//
