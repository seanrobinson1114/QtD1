//---------------------------------------------------------------------------//
//!
//! \file   BitmapText.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The bitmap text class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QPainter>

// QtD1 Includes
#include "BitmapText.h"
#include "White11BitmapFont.h"
#include "Gold16BitmapFont.h"
#include "Silver16BitmapFont.h"
#include "Gold22BitmapFont.h"
#include "Gold24BitmapFont.h"
#include "Silver24BitmapFont.h"
#include "Gold30BitmapFont.h"
#include "Silver30BitmapFont.h"
#include "Gold42BitmapFont.h"
#include "Silver42BitmapFont.h"
#include "Gold45BitmapFont.h"

namespace QtD1{

// Initialize static member data
std::map<QString,BitmapFont*> BitmapText::s_registered_fonts;

// Constructor
BitmapText::BitmapText( QDeclarativeItem* parent )
  : QDeclarativeItem( parent ),
    d_text_lines(),
    d_text_image(),
    d_display_policy( Viewport::NoStretch_AlignSourceCenterWithElementCenter ),
    d_text_source_viewport(),
    d_text_target_viewport(),
    d_font_name(),
    d_font( NULL )
{
  // This flag has to be disabled so that drawing can be done
  this->setFlag( QGraphicsItem::ItemHasNoContents, false );
}

// Get the text
QString BitmapText::getText() const
{
  QString text;

  for( int i = 0; i < d_text_lines.size(); ++i )
  {
    text.append( d_text_lines[i] );

    if( i != d_text_lines.size() - 1 )
      text.append( "\n" );
  }

  return text;
}

// Set the text
void BitmapText::setText( const QString& text )
{
  if( d_text_behavior == NoTextWrap )
  {
    this->setTextWithNoWrap( text );
  }
  else if( d_text_behavior == TextWrap )
  {
    this->setTextWithTextWrap( text );
  }
  else if( d_text_behavior == WordWrap )
  {
    this->setTextWithWordWrap( text );
  }
}

// Set the text without wrapping
void BitmapText::setTextWithNoWrap( const QString& text )
{
  d_text_lines = text.split( '\n' );
}

// Set the text with text wrapping
void BitmapText::setTextWithTextWrap( const QString& text )
{
  QString current_line;
  int current_line_width = 0;

  for( int i = 0; i < text.size(); ++i )
  {
    // Check if character fits on current line
    if( current_line_width + d_font->getGlyphWidth( text.at(i).toAscii() ) < d_container_width )
    {
      current_line.append( text.at(i) );
      current_line_width += d_font->getGlyphWidth( text.at(i).toAscii() );
    }
    else
    {
      // Doesn't fit, Move character to next line
      d_text_lines.append( current_line );
      current_line.clear();
      current_line_width = 0;
      current_line.append( text.at(i ) );
      current_line_width += d_font->getGlyphWidth( text.at(i).toAscii() );
    }
  }
  // Append the last line
  d_text_lines.append( current_line );
}

// Set the text with word wrapping
void BitmapText::setTextWithWordWrap( const QString& text )
{
  QStringList words = text.split( " " );

  QString current_line;
  int current_line_width = 0;
  int current_word_width = 0;

  for( int i = 0; i < words.size(); ++i )
  {
    current_word_width = 0;
    for( int j = 0; j < words[i].size(); ++j )
    {
      // Calculate the width of the word
      current_word_width += d_font->getGlyphWidth( words[i].at(j).toAscii() );
    }
    // Check if the word fits on the current line
    if( current_line_width + current_word_width < d_container_width )
    {
      current_line.append( words[i] );
      current_line.append( " " );
      current_line_width += d_font->getGlyphWidth( 32 );
      current_line_width += current_word_width;
    }
    // Word doesn't fit, move to next line
    else
    {
      d_text_lines.append( current_line );
      current_line.clear();
      current_line_width = 0;
      current_line.append( words[i] );
      current_line.append( " " );
      current_line_width += d_font->getGlyphWidth( 32 );
      current_line_width += current_word_width;
    }
  }
  // Append last line
  d_text_lines.append( current_line );
}

// Get the font name
QString BitmapText::getFontName() const
{
  return d_font_name;
}

// Set the font name
void BitmapText::setFontName( const QString& font_name )
{
  // Check if the font name has been registered
  if( s_registered_fonts.find( font_name ) !=
      s_registered_fonts.end() )
  {
    d_font_name = font_name;

    d_font = s_registered_fonts.find( font_name )->second;
  }
  else
  {
    qWarning( "BitmapText::setFontName cannot use font %s!", (const char*)font_name.data() );
  }
}

// Get the text behavior
BitmapText::TextBehavior BitmapText::getTextBehavior() const
{
  return d_text_behavior;
}

// Set the text behavior
void BitmapText::setTextBehavior( const BitmapText::TextBehavior behavior )
{
  d_text_behavior = behavior;
}

// Get the display policy
Viewport::DisplayPolicy BitmapText::getDisplayPolicy() const
{
  return d_display_policy;
}

// Set the display policy
void BitmapText::setDisplayPolicy( const Viewport::DisplayPolicy policy )
{
  d_display_policy = policy;
}

// Get the number of lines
int BitmapText::getLineCount() const
{
  return d_text_lines.size();
}

// Get the painted line height
qreal BitmapText::getPaintedLineHeight() const
{
  return d_text_image.height();
}

// Get the line height
int BitmapText::getLineHeight() const
{
  return d_font->getSize();
}

// Get the painted line width
qreal BitmapText::getPaintedLineWidth() const
{
  return d_text_image.width();
}

// Get the line width
int BitmapText::getLineWidth() const
{
  return d_text_image.width();
}

// Get the container width
int BitmapText::getContainerWidth() const
{
  return d_container_width;
}

// Set the container width
void BitmapText::setContainerWidth( const int width )
{
  d_container_width = width;
}

// Load the text bitmap
void BitmapText::load()
{
  if( d_font )
  {
    // Calculate the width of the text image
    int width = 0;

    for( int line = 0; line < d_text_lines.size(); ++line )
    {
      int line_width = 0;

      for( int i = 0; i < d_text_lines[line].size(); ++i )
        line_width += d_font->getGlyphWidth( d_text_lines[line].at(i).toAscii() );

      width = std::max( width, line_width );
    }

    // Calculate the height of the text image
    int height = d_font->getSize()*d_text_lines.size();

    // Initialize the text image
    d_text_image = QPixmap( width, height );
    d_text_image.fill( Qt::transparent );

    // Add the glyphs to the text image
    QPainter text_image_painter( &d_text_image );
    text_image_painter.setCompositionMode( QPainter::CompositionMode_Source );

    int y_pos = 0;

    for( int line = 0; line < d_text_lines.size(); ++line )
    {
      int x_pos = 0;

      for( int i = 0; i < d_text_lines[line].size(); ++i )
      {
        text_image_painter.drawPixmap(
          x_pos, y_pos, d_font->getGlyph(d_text_lines[line].at(i).toAscii() ));

        x_pos += d_font->getGlyphWidth( d_text_lines[line].at(i).toAscii() );
      }
      y_pos += d_font->getSize();
    }

    // Close the painter
    text_image_painter.end();

    // Calculate the viewports
    Viewport::calculateViewports( d_display_policy,
                                  this->boundingRect(),
                                  d_text_image,
                                  d_text_source_viewport,
                                  d_text_target_viewport );

    this->update();
  }
}

// Get the text pixmap
QPixmap BitmapText::getPixmap() const
{
  return d_text_image;
}

// Paint the text bitmap
void BitmapText::paint( QPainter* painter,
                        const QStyleOptionGraphicsItem*,
                        QWidget* )
{
  if( !d_text_image.isNull() )
  {
    painter->drawPixmap( d_text_target_viewport,
                         d_text_image,
                         d_text_source_viewport );
  }
}

// Load standard fonts
void BitmapText::loadStandardFonts()
{
  QtD1::BitmapText::registerFont<QtD1::White11BitmapFont>( "QtD1White11" );
  QtD1::BitmapText::registerFont<QtD1::Gold16BitmapFont>( "QtD1Gold16" );
  QtD1::BitmapText::registerFont<QtD1::Silver16BitmapFont>( "QtD1Silver16" );
  QtD1::BitmapText::registerFont<QtD1::Gold22BitmapFont>( "QtD1Gold22" );
  QtD1::BitmapText::registerFont<QtD1::Gold24BitmapFont>( "QtD1Gold24" );
  QtD1::BitmapText::registerFont<QtD1::Silver24BitmapFont>( "QtD1Silver24" );
  QtD1::BitmapText::registerFont<QtD1::Gold30BitmapFont>( "QtD1Gold30" );
  QtD1::BitmapText::registerFont<QtD1::Silver30BitmapFont>( "QtD1Silver30" );
  QtD1::BitmapText::registerFont<QtD1::Gold42BitmapFont>( "QtD1Gold42" );
  QtD1::BitmapText::registerFont<QtD1::Silver42BitmapFont>( "QtD1Silver42" );
  QtD1::BitmapText::registerFont<QtD1::Gold45BitmapFont>( "QtD1Gold45" );
}

QML_REGISTER_TYPE( BitmapText );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end BitmapText.cpp
//---------------------------------------------------------------------------//
