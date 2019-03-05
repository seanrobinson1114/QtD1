//---------------------------------------------------------------------------//
//!
//! \file   BitmapFont.h
//! \author Alex, Sean Robinson
//! \brief  The bitmap font class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QImage>

// QtD1 includes
#include "BitmapFont.h"
#include "MenuSprite.h"

namespace QtD1{

// Default Constructor
BitmapFont::BitmapFont()
  : d_glyph_map()
{ /* ... */ }

// Construct with filename and widths
BitmapFont::BitmapFont( const QString& source, const QVector<int>& widths )
  : d_glyph_map()
{
  // Extract the frames and set the glyph map
  MenuSprite glyph_sprite;
  glyph_sprite.setSource( source );
  glyph_sprite.setBackgroundColor( "#00ff00" );
  glyph_sprite.setNumberOfRows( 256 );
  glyph_sprite.setNumberOfCols( 1 );
  glyph_sprite.loadSync();

  glyph_sprite.getFrames( d_glyph_map );
  this->resetGlyphWidths( widths );
}

// Constructor with filename, widths and orders
BitmapFont::BitmapFont( const QString& source,
                        const QVector<int>& widths,
                        const QVector<int>& order,
                        const QColor& mixing_color )
  : d_glyph_map()
{
  // Extract the frames and set the glyph map
  MenuSprite glyph_sprites;
  glyph_sprites.setSource( source );
  glyph_sprites.setDisplayedFrameIndices( "all" );
  glyph_sprites.setMixingColor( mixing_color );
  glyph_sprites.loadSync();

  QVector<QPixmap> raw_glyphs;
  glyph_sprites.getFrames( raw_glyphs );
  this->resetGlyphWidthsAndOrder( raw_glyphs, widths, order );
}

// Check if the character has an associated glyph
bool BitmapFont::doesCharHaveGlyph( const char character ) const
{
  // Convert the char to an unsigned
  uchar glyph_index = (uchar)character;

  if( d_glyph_map[glyph_index].isNull() )
    return false;
  else
    return true;
}

// Return the glyph associated with the character
QPixmap BitmapFont::getGlyph( const char character ) const
{
  // Convert the char to an unsigned
  uchar glyph_index = (uchar)character;

  return d_glyph_map[glyph_index];
}

// Return the width of the glyph associated with the character
int BitmapFont::getGlyphWidth( const char character ) const
{
  // Convert the char to an unsigned
  uchar glyph_index = (uchar)character;

  return d_glyph_map[glyph_index].width();
}

// Reset the widths of each character in the glyph map
void BitmapFont::resetGlyphWidths( const QVector<int>& widths )
{
  for( int i = 0; i < 256; ++i )
  {
    if( widths[i] > 0 )
    {
      d_glyph_map[i] =
        d_glyph_map[i].copy( 0, 0, widths[i], d_glyph_map[i].height() );
    }
    else
      d_glyph_map[i] = QPixmap();
  }
}

// Reset the glyph widths and order
void BitmapFont::resetGlyphWidthsAndOrder( const QVector<QPixmap>& raw_glyphs,
                                           const QVector<int>& widths,
                                           const QVector<int>& order )
{
  d_glyph_map.resize( 256 );

  int height = raw_glyphs.front().height();

  for( int i = 0; i < 256; ++i )
  {
    if( widths[i] > 0 )
    {
      if( order[i] >= 0 )
      {
        d_glyph_map[i] = raw_glyphs[order[i]].copy( 0, 0, widths[i], height );
      }
      // A transparent image needs to be created
      else
      {
        QPixmap trans_image( widths[i], height );
        trans_image.fill( Qt::transparent );

        d_glyph_map[i] = trans_image;
      }
    }
  }
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end BitmapFont.cpp
//---------------------------------------------------------------------------//
