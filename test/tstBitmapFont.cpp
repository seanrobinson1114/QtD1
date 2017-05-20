//---------------------------------------------------------------------------//
//!
//! \file   tstBitmapFont.cpp
//! \author Alex Robinson
//! \brief  The bitmap font class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "MPQHandler.h"
#include "Gold16BitmapFont.h"
#include "Gold22BitmapFont.h"
#include "Gold24BitmapFont.h"
#include "Gold30BitmapFont.h"
#include "Gold42BitmapFont.h"
#include "Gold45BitmapFont.h"
#include "Silver16BitmapFont.h"
#include "Silver24BitmapFont.h"
#include "Silver30BitmapFont.h"
#include "Silver42BitmapFont.h"
#include "White11BitmapFont.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)
Q_IMPORT_PLUGIN(pcx)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestBitmapFont : public QObject
{
  Q_OBJECT

private slots:

  void initTestCase()
  {
    // Register the MPQHandler with the file engine system
    QtD1::MPQHandler::getInstance();

    // Load the bitmap fonts
    QtD1::Gold16BitmapFont::getInstance();
    QtD1::Gold22BitmapFont::getInstance();
    QtD1::Gold24BitmapFont::getInstance();
    QtD1::Gold30BitmapFont::getInstance();
    QtD1::Gold42BitmapFont::getInstance();
    QtD1::Gold45BitmapFont::getInstance();
    QtD1::Silver16BitmapFont::getInstance();
    QtD1::Silver24BitmapFont::getInstance();
    QtD1::Silver30BitmapFont::getInstance();
    QtD1::Silver42BitmapFont::getInstance();
    QtD1::White11BitmapFont::getInstance();
  }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the gold 16 name is correct
void getName_gold16()
{
  QCOMPARE( QtD1::Gold16BitmapFont::getInstance()->getName(),
            QString("/ui_art/font16g.pcx") );
}

//---------------------------------------------------------------------------//
// Check that the gold 16 size is correct
void getSize_gold16()
{
  QCOMPARE( QtD1::Gold16BitmapFont::getInstance()->getSize(), 16 );
}

//---------------------------------------------------------------------------//
// Check that the gold 16 font has the expected glyphs defined
void doesCharHaveGlyph_gold16()
{
  QtD1::BitmapFont* font = QtD1::Gold16BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i < 224 )
      QVERIFY( font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( !font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 16 font has the expected glyph widths
void getGlyphWidth_gold16()
{
  QtD1::BitmapFont* font = QtD1::Gold16BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i < 224 )
      QVERIFY( font->getGlyphWidth( i ) > 0 );
    else
      QCOMPARE( font->getGlyphWidth( i ), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 16 font can return character glyphs
void getGlyph_gold16()
{
  QtD1::BitmapFont* font = QtD1::Gold16BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i < 224 )
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 16 );
    }
    else
      QVERIFY( glyph.isNull() );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 22 name is correct
void getName_gold22()
{
  QCOMPARE( QtD1::Gold22BitmapFont::getInstance()->getName(),
            QString("/data/medtexts.cel+/levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// Check that the gold 22 size is correct
void getSize_gold22()
{
  QCOMPARE( QtD1::Gold22BitmapFont::getInstance()->getSize(), 22 );
}

//---------------------------------------------------------------------------//
// Check that the gold 22 font has the expected glyphs defined
void doesCharHaveGlyph_gold22()
{
  QtD1::BitmapFont* font = QtD1::Gold22BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '$' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '<' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '>' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '@' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '\\' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '^' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '_' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '`' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '|' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i >= 126 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 22 font has the expected glyph widths
void getGlyphWidth_gold22()
{
  QtD1::BitmapFont* font = QtD1::Gold22BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '$' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '<' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '>' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '@' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '\\' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '^' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '_' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '`' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '|' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i >= 126 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else
      QVERIFY( font->getGlyphWidth( i ) > 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 22 font can return character glyphs
void getGlyph_gold22()
{
  QtD1::BitmapFont* font = QtD1::Gold22BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i == '$' )
      QVERIFY( glyph.isNull() );
    else if( i == '<' )
      QVERIFY( glyph.isNull() );
    else if( i == '>' )
      QVERIFY( glyph.isNull() );
    else if( i == '@' )
      QVERIFY( glyph.isNull() );
    else if( i == '\\' )
      QVERIFY( glyph.isNull() );
    else if( i == '^' )
      QVERIFY( glyph.isNull() );
    else if( i == '_' )
      QVERIFY( glyph.isNull() );
    else if( i == '`' )
      QVERIFY( glyph.isNull() );
    else if( i == '|' )
      QVERIFY( glyph.isNull() );
    else if( i >= 126 )
      QVERIFY( glyph.isNull() );
    else
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 22 );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 24 name is correct
void getName_gold24()
{
  QCOMPARE( QtD1::Gold24BitmapFont::getInstance()->getName(),
            QString("/ui_art/font24g.pcx") );
}

//---------------------------------------------------------------------------//
// Check that the gold 24 size is correct
void getSize_gold24()
{
  QCOMPARE( QtD1::Gold24BitmapFont::getInstance()->getSize(), 24 );
}

//---------------------------------------------------------------------------//
// Check that the gold 24 font has the expected glyphs defined
void doesCharHaveGlyph_gold24()
{
  QtD1::BitmapFont* font = QtD1::Gold24BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i < 224 )
      QVERIFY( font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( !font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 24 font has the expected glyph widths
void getGlyphWidth_gold24()
{
  QtD1::BitmapFont* font = QtD1::Gold24BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i < 224 )
      QVERIFY( font->getGlyphWidth( i ) > 0 );
    else
      QCOMPARE( font->getGlyphWidth( i ), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 24 font can return character glyphs
void getGlyph_gold24()
{
  QtD1::BitmapFont* font = QtD1::Gold24BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i < 224 )
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 26 );
    }
    else
      QVERIFY( glyph.isNull() );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 30 name is correct
void getName_gold30()
{
  QCOMPARE( QtD1::Gold30BitmapFont::getInstance()->getName(),
            QString("/ui_art/font30g.pcx") );
}

//---------------------------------------------------------------------------//
// Check that the gold 30 size is correct
void getSize_gold30()
{
  QCOMPARE( QtD1::Gold30BitmapFont::getInstance()->getSize(), 30 );
}

//---------------------------------------------------------------------------//
// Check that the gold 30 font has the expected glyphs defined
void doesCharHaveGlyph_gold30()
{
  QtD1::BitmapFont* font = QtD1::Gold30BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i < 224 )
      QVERIFY( font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( !font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 30 font has the expected glyph widths
void getGlyphWidth_gold30()
{
  QtD1::BitmapFont* font = QtD1::Gold30BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i < 224 )
      QVERIFY( font->getGlyphWidth( i ) > 0 );
    else
      QCOMPARE( font->getGlyphWidth( i ), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 30 font can return character glyphs
void getGlyph_gold30()
{
  QtD1::BitmapFont* font = QtD1::Gold30BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i < 224 )
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 31 );
    }
    else
      QVERIFY( glyph.isNull() );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 42 name is correct
void getName_gold42()
{
  QCOMPARE( QtD1::Gold42BitmapFont::getInstance()->getName(),
            QString("/ui_art/font42g.pcx") );
}

//---------------------------------------------------------------------------//
// Check that the gold 42 size is correct
void getSize_gold42()
{
  QCOMPARE( QtD1::Gold42BitmapFont::getInstance()->getSize(), 42 );
}

//---------------------------------------------------------------------------//
// Check that the gold 42 font has the expected glyphs defined
void doesCharHaveGlyph_gold42()
{
  QtD1::BitmapFont* font = QtD1::Gold42BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i < 224 )
      QVERIFY( font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( !font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 42 font has the expected glyph widths
void getGlyphWidth_gold42()
{
  QtD1::BitmapFont* font = QtD1::Gold42BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i < 224 )
      QVERIFY( font->getGlyphWidth( i ) > 0 );
    else
      QCOMPARE( font->getGlyphWidth( i ), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 42 font can return character glyphs
void getGlyph_gold42()
{
  QtD1::BitmapFont* font = QtD1::Gold42BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i < 224 )
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 42 );
    }
    else
      QVERIFY( glyph.isNull() );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 45 name is correct
void getName_gold45()
{
  QCOMPARE( QtD1::Gold45BitmapFont::getInstance()->getName(),
            QString("/data/bigtgold.cel+/levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// Check that the gold 45 size is correct
void getSize_gold45()
{
  QCOMPARE( QtD1::Gold45BitmapFont::getInstance()->getSize(), 45 );
}

//---------------------------------------------------------------------------//
// Check that the gold 45 font has the expected glyphs defined
void doesCharHaveGlyph_gold45()
{
  QtD1::BitmapFont* font = QtD1::Gold45BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '$' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '<' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '>' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '@' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '\\' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '^' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '_' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '`' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '|' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i >= 126 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 45 font has the expected glyph widths
void getGlyphWidth_gold45()
{
  QtD1::BitmapFont* font = QtD1::Gold45BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '$' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '<' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '>' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '@' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '\\' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '^' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '_' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '`' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '|' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i >= 126 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else
      QVERIFY( font->getGlyphWidth( i ) > 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the gold 45 font can return character glyphs
void getGlyph_gold45()
{
  QtD1::BitmapFont* font = QtD1::Gold45BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i == '$' )
      QVERIFY( glyph.isNull() );
    else if( i == '<' )
      QVERIFY( glyph.isNull() );
    else if( i == '>' )
      QVERIFY( glyph.isNull() );
    else if( i == '@' )
      QVERIFY( glyph.isNull() );
    else if( i == '\\' )
      QVERIFY( glyph.isNull() );
    else if( i == '^' )
      QVERIFY( glyph.isNull() );
    else if( i == '_' )
      QVERIFY( glyph.isNull() );
    else if( i == '`' )
      QVERIFY( glyph.isNull() );
    else if( i == '|' )
      QVERIFY( glyph.isNull() );
    else if( i >= 126 )
      QVERIFY( glyph.isNull() );
    else
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 45 );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 16 name is correct
void getName_silver16()
{
  QCOMPARE( QtD1::Silver16BitmapFont::getInstance()->getName(),
            QString("/ui_art/font16s.pcx") );
}

//---------------------------------------------------------------------------//
// Check that the silver 16 size is correct
void getSize_silver16()
{
  QCOMPARE( QtD1::Silver16BitmapFont::getInstance()->getSize(), 16 );
}

//---------------------------------------------------------------------------//
// Check that the silver 16 font has the expected glyphs defined
void doesCharHaveGlyph_silver16()
{
  QtD1::BitmapFont* font = QtD1::Silver16BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i < 224 )
      QVERIFY( font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( !font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 16 font has the expected glyph widths
void getGlyphWidth_silver16()
{
  QtD1::BitmapFont* font = QtD1::Silver16BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i < 224 )
      QVERIFY( font->getGlyphWidth( i ) > 0 );
    else
      QCOMPARE( font->getGlyphWidth( i ), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 16 font can return character glyphs
void getGlyph_silver16()
{
  QtD1::BitmapFont* font = QtD1::Silver16BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i < 224 )
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 16 );
    }
    else
      QVERIFY( glyph.isNull() );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 24 name is correct
void getName_silver24()
{
  QCOMPARE( QtD1::Silver24BitmapFont::getInstance()->getName(),
            QString("/ui_art/font24s.pcx" ) );
}

//---------------------------------------------------------------------------//
// Check that the silver 24 size is correct
void getSize_silver24()
{
  QCOMPARE( QtD1::Silver24BitmapFont::getInstance()->getSize(), 24 );
}

//---------------------------------------------------------------------------//
// Check that the silver 24 font has the expected glyphs defined
void doesCharHaveGlyph_silver24()
{
  QtD1::BitmapFont* font = QtD1::Silver24BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i < 224 )
      QVERIFY( font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( !font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 24 font has the expected glyph widths
void getGlyphWidth_silver24()
{
  QtD1::BitmapFont* font = QtD1::Silver24BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i < 224 )
      QVERIFY( font->getGlyphWidth( i ) > 0 );
    else
      QCOMPARE( font->getGlyphWidth( i ), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 24 font can return character glyphs
void getGlyph_silver24()
{
  QtD1::BitmapFont* font = QtD1::Silver24BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i < 224 )
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 26 );
    }
    else
      QVERIFY( glyph.isNull() );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 30 name is correct
void getName_silver30()
{
  QCOMPARE( QtD1::Silver30BitmapFont::getInstance()->getName(),
            QString("/ui_art/font30s.pcx" ) );
}

//---------------------------------------------------------------------------//
// Check that the silver 30 size is correct
void getSize_silver30()
{
  QCOMPARE( QtD1::Silver30BitmapFont::getInstance()->getSize(), 30 );
}

//---------------------------------------------------------------------------//
// Check that the silver 30 font has the expected glyphs defined
void doesCharHaveGlyph_silver30()
{
  QtD1::BitmapFont* font = QtD1::Silver30BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i < 224 )
      QVERIFY( font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( !font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 30 font has the expected glyph widths
void getGlyphWidth_silver30()
{
  QtD1::BitmapFont* font = QtD1::Silver30BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i < 224 )
      QVERIFY( font->getGlyphWidth( i ) > 0 );
    else
      QCOMPARE( font->getGlyphWidth( i ), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 30 font can return character glyphs
void getGlyph_silver30()
{
  QtD1::BitmapFont* font = QtD1::Silver30BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i < 224 )
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 31 );
    }
    else
      QVERIFY( glyph.isNull() );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 42 name is correct
void getName_silver42()
{
  QCOMPARE( QtD1::Silver42BitmapFont::getInstance()->getName(),
            QString("/ui_art/font42y.pcx" ) );
}

//---------------------------------------------------------------------------//
// Check that the silver 42 size is correct
void getSize_silver42()
{
  QCOMPARE( QtD1::Silver42BitmapFont::getInstance()->getSize(), 42 );
}

//---------------------------------------------------------------------------//
// Check that the silver 42 font has the expected glyphs defined
void doesCharHaveGlyph_silver42()
{
  QtD1::BitmapFont* font = QtD1::Silver42BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i < 224 )
      QVERIFY( font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( !font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 42 font has the expected glyph widths
void getGlyphWidth_silver42()
{
   QtD1::BitmapFont* font = QtD1::Silver42BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i < 224 )
      QVERIFY( font->getGlyphWidth( i ) > 0 );
    else
      QCOMPARE( font->getGlyphWidth( i ), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the silver 42 font can return character glyphs
void getGlyph_silver42()
{
  QtD1::BitmapFont* font = QtD1::Silver42BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i < 224 )
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 42 );
    }
    else
      QVERIFY( glyph.isNull() );
  }
}

//---------------------------------------------------------------------------//
// Check that the white 11 name is correct
void getName_white11()
{
  QCOMPARE( QtD1::White11BitmapFont::getInstance()->getName(),
            QString("/ctrlpan/smaltext.cel+/levels/towndata/town.pal") );
}

//---------------------------------------------------------------------------//
// Check that the white 11 size is correct
void getSize_white11()
{
  QCOMPARE( QtD1::White11BitmapFont::getInstance()->getSize(), 11 );
}

//---------------------------------------------------------------------------//
// Check that the white 11 font has the expected glyphs defined
void doesCharHaveGlyph_white11()
{
  QtD1::BitmapFont* font = QtD1::White11BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '<' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '>' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '@' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i == '|' )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else if( i >= 126 )
      QVERIFY( !font->doesCharHaveGlyph( i ) );
    else
      QVERIFY( font->doesCharHaveGlyph( i ) );
  }
}

//---------------------------------------------------------------------------//
// Check that the white 11 font has the expected glyph widths
void getGlyphWidth_white11()
{
  QtD1::BitmapFont* font = QtD1::White11BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    if( i < 32 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '<' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '>' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '@' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i == '|' )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else if( i >= 126 )
      QCOMPARE( font->getGlyphWidth( i ), 0 );
    else
      QVERIFY( font->getGlyphWidth( i ) > 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the white 11 font can return character glyphs
void getGlyph_white11()
{
  QtD1::BitmapFont* font = QtD1::White11BitmapFont::getInstance();

  for( int i = 0; i < 256; ++i )
  {
    QPixmap glyph = font->getGlyph( i );
    
    if( i < 32 )
      QVERIFY( glyph.isNull() );
    else if( i == '<' )
      QVERIFY( glyph.isNull() );
    else if( i == '>' )
      QVERIFY( glyph.isNull() );
    else if( i == '@' )
      QVERIFY( glyph.isNull() );
    else if( i == '|' )
      QVERIFY( glyph.isNull() );
    else if( i >= 126 )
      QVERIFY( glyph.isNull() );
    else
    {
      QVERIFY( !glyph.isNull() );
      QCOMPARE( glyph.height(), 11 );
    }
  }
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestBitmapFont )
#include "tstBitmapFont.moc"

//---------------------------------------------------------------------------//
// end tstBitmapFont.cpp
//---------------------------------------------------------------------------//
