//---------------------------------------------------------------------------//
//!
//! \file   BitmapFont.h
//! \author Alex, Sean Robinson
//! \brief  The bitmap font class declaration
//!
//---------------------------------------------------------------------------//

#ifndef BITMAP_FONT_H
#define BITMAP_FONT_H

// Qt Includes
#include <QPixmap>
#include <QVector>
#include <QString>
#include <QColor>

namespace QtD1{

//! The bitmap font class
class BitmapFont
{

public:

  //! Default Constructor
  BitmapFont();

  //! Constructor which takes filename and vector of widths
  BitmapFont( const QString& source, const QVector<int>& widths );

  //! Constructor which takes filename, vector of widths and vector of orders
  BitmapFont( const QString& source,
              const QVector<int>& widths,
              const QVector<int>& order );

  //! Destructor
  ~BitmapFont()
  { /* ... */ }

  //! Get the font name
  virtual QString getName() const = 0;

  //! Return the font size
  virtual int getSize() const = 0;

  //! Check if the character has an associated glyph
  bool doesCharHaveGlyph( const char character ) const;

  //! Return the glyph associated with the character
  QPixmap getGlyph( const char character ) const;

  //! Return the width of the glyph associated with the character
  int getGlyphWidth( const char character ) const;

private:

  // Reset the widths of each character in the glyph map
  void resetGlyphWidths( const QVector<int>& widths );

  // Reset the glyph widths and order
  void resetGlyphWidthsAndOrder( const QVector<QPixmap>& raw_glyphs,
                                 const QVector<int>& widths,
                                 const QVector<int>& order );

  // The glyph map
  QVector<QPixmap> d_glyph_map;
};

} // end QtD1 namespace

#endif // end BITMAP_FONT_H

//---------------------------------------------------------------------------//
// end BitmapFont.h
//---------------------------------------------------------------------------//
