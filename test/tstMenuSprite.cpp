//---------------------------------------------------------------------------//
//!
//! \file   tstMenuSprite.cpp
//! \author Alex Robinson
//! \brief  The bitmap font class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QtTest/QtTest>

// QtD1 Includes
#include "MenuSprite.h"
#include "MPQHandler.h"
#include "Viewport.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)
Q_IMPORT_PLUGIN(pcx)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestMenuSprite : public QObject
{
  Q_OBJECT

private slots:

  void initTestCase()
  {
    // Register the MPQHandler with the file engine system
    QtD1::MPQHandler::getInstance();
  }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a menu sprite can be created
void createSprite_pcx()
{
  // Test will throw a qFatal if contructor fails
  QtD1::MenuSprite sprite;
  sprite.getSource();
  QCOMPARE( sprite.getSource(), QString( "" ) );
}

// Check that a menu sprites source can be set
void setSource_pcx()
{
  QtD1::MenuSprite sprite;
  // Will throw qFatal if not successful
  sprite.setSource( "/ui_art/heros.pcx" );
}

// Check that source can be returned
void getSource()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/ui_art/heros.pcx" );
  QCOMPARE( sprite.getSource(), QString( "/ui_art/heros.pcx" ) );
}

// Check that a display policy can be set
void setDisplayPolicy()
{
  QtD1::MenuSprite sprite;
  // Will throw qFatal if not successful
  sprite.setDisplayPolicy( QtD1::Viewport::StretchToFit );
}

// Check that display policy can be returned
void getDisplayPolicy()
{
  QtD1::MenuSprite sprite;
  sprite.setDisplayPolicy( QtD1::Viewport::StretchToFit );
  QCOMPARE( sprite.getDisplayPolicy(), QtD1::Viewport::StretchToFit );
}

// Check that background color can be set
void setBackgroundColor()
{
  QtD1::MenuSprite sprite;
  // Will throw qFatal if not successful
  sprite.setBackgroundColor( QColor( "black" ) );
}

// Check that the background color can be returned
void getBackgroundColor()
{
  QtD1::MenuSprite sprite;
  sprite.setBackgroundColor( QColor( "black" ) );
  QCOMPARE( sprite.getBackgroundColor(), QColor( "black" ) );
}

// Check that number of rows can be set
void setNumberOfRows()
{
  QtD1::MenuSprite sprite;
  // Will throw qFatal if not successful
  sprite.setNumberOfRows( 4 );
}

// Check that number of rows can be returned
void getNumberOfRows()
{
  QtD1::MenuSprite sprite;
  sprite.setNumberOfRows( 4 );
  QCOMPARE( sprite.getNumberOfRows(), quint32( 4 ) );
}

// Check that the number of columns can be setDisplayedFrameIndices
void setNumberofColumns()
{
  QtD1::MenuSprite sprite;
  // Will throw qFatal if not successful
  sprite.setNumberOfCols( 23 );
}

// Check that the number of columns can be retrieved
void getNumberOfColumns()
{
  QtD1::MenuSprite sprite;
  sprite.setNumberOfCols( 3443 );
  QCOMPARE( sprite.getNumberOfCols(), quint32( 3443 ) );
}

// Check that the indices of frames to display can be set
void setIndicesOfDisplayFrames()
{
  QtD1::MenuSprite sprite;
  QVariant list( QVariant::List );
  list.setValue( 5 );
  // Will throw error if not successful
  sprite.setDisplayedFrameIndices( list );
}

// Check that the indices of frames to display can be returned
void getIndicesOfDisplayFrames()
{
  // QtD1::MenuSprite sprite;
  // QVariant list( QVariant::List );
  // list.setValue( 5 );
  // sprite.setDisplayedFrameIndices( list );
}

// Check that the starting frame cant be set
void setStartFrame()
{
  QtD1::MenuSprite sprite;
  // Will throw error is not successful
  sprite.setStartingFrameIndex( quint32( 1 ) );
}

// Check that the starting frame can be retrieved
void getStartFrame()
{
  QtD1::MenuSprite sprite;
  sprite.setStartingFrameIndex( quint32( 1 ) );
  QCOMPARE( sprite.getStartingFrameIndex(), quint32( 1 ) );
}

// Check that the frame can be setCurrentFrameIndex
void setFrame()
{
  QtD1::MenuSprite sprite;

  QSignalSpy frame_changed_spy( &sprite, SIGNAL( frameChanged( quint32 ) ) );
  // Will throw error if not successful
  sprite.setCurrentFrameIndex( quint32( 10 ) );
  QCOMPARE( frame_changed_spy[0][0].toInt(), 10 );
}

// Check that the frame can be retrieved
void getFrame()
{
  QtD1::MenuSprite sprite;
  sprite.setCurrentFrameIndex( quint32( 10 ) );
  QCOMPARE( sprite.getCurrentFrameIndex(), quint32( 10 ) );
}

// Check that a pcx image can be loaded synchronously
void loadImage_pcx()
{
  QtD1::MenuSprite sprite;

  QSignalSpy source_loaded_spy( &sprite, SIGNAL( sourceLoaded( QString ) ) );

  sprite.setSource( "/ui_art/heros.pcx" );
  sprite.loadSync();
  QCOMPARE( source_loaded_spy[0][0].toString(), QString( "/ui_art/heros.pcx" ) );
}

// Check that a pcx image can be loaded asynchronously
void loadImageAsync_pcx()
{
  QtD1::MenuSprite sprite;

  sprite.setSource( "/ui_art/heros.pcx" );
  sprite.load();
  sprite.waitForLoadToFinish();
}

// Check that a cel image can be loaded synchronously
void loadImage_cel()
{
  QtD1::MenuSprite sprite;

  QSignalSpy source_loaded_spy( &sprite, SIGNAL( sourceLoaded( QString ) ) );

  sprite.setSource( "/data/char.cel+levels/towndata/town.pal" );
  sprite.loadSync();
  QCOMPARE( source_loaded_spy[0][0].toString(), QString( "/data/char.cel+levels/towndata/town.pal" ) );
}

// Check that a cel image can be loaded asynchronously
void loadImageAsync_cel()
{
  QtD1::MenuSprite sprite;

  sprite.setSource( "/data/char.cel+levels/towndata/town.pal" );
  sprite.load();
  sprite.waitForLoadToFinish();
}

// Check that a cl2 image can be loaded synchronously
void loadImage_cl2()
{
  QtD1::MenuSprite sprite;

  QSignalSpy source_loaded_spy( &sprite, SIGNAL( sourceLoaded( QString ) ) );

  sprite.setSource( "/monsters/diablo/diabloa.cl2+levels/towndata/town.pal" );
  sprite.loadSync();
  QCOMPARE( source_loaded_spy[0][0].toString(), QString( "/monsters/diablo/diabloa.cl2+levels/towndata/town.pal" ) );
}

// Check that a cl2 image can be loaded asynchronously
void loadImageAsync_cl2()
{
  QtD1::MenuSprite sprite;

  sprite.setSource( "/monsters/diablo/diabloa.cl2+levels/towndata/town.pal" );
  sprite.load();
  sprite.waitForLoadToFinish();
}

// Check that the number of frames can be returned for a pcx image
void getNumberOfFrames_pcx()
{
  QtD1::MenuSprite sprite;

  sprite.setSource( "/ui_art/heros.pcx" );
  sprite.loadSync();
  QCOMPARE( sprite.getNumberOfFrames(), quint32( 1 ) );
}

// Check that the number of frames can be returned for a cel image
void getNumberOfFrames_cel()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/ctrlpan/panel8bu.cel+levels/towndata/town.pal" );
  sprite.loadSync();
  QCOMPARE( sprite.getNumberOfFrames(), quint32( 9 ) );
}

// Check that the number of frames can be returned for a cl2 image
void getNumberOfFrames_cl2()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/monsters/diablo/diabloa.cl2+levels/towndata/town.pal" );
  sprite.loadSync();
  QCOMPARE( sprite.getNumberOfFrames(), quint32( 128 ) );
}


// Check that the current frame width can be returned for a pcx image
void getCurrentFrameWidth_pcx()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/ui_art/heros.pcx" );
  sprite.loadSync();
  QCOMPARE( sprite.getCurrentFrameWidth(), 180 );
}

// Check that the current frame width can be returned for a cel image
void getCurrentFrameWidth_cel()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/ctrlpan/panel8bu.cel+levels/towndata/town.pal" );
  sprite.loadSync();
  QCOMPARE( sprite.getCurrentFrameWidth(), 71 );
}

// Check that the current frame width can be returned for a cl2 image
void getCurrentFrameWidth_cl2()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/monsters/diablo/diabloa.cl2+levels/towndata/town.pal" );
  sprite.loadSync();
  QCOMPARE( sprite.getCurrentFrameWidth(), 160 );
}

// Check that the current frame height can be returned for a pcx image
void getCurrentFrameHeight_pcx()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/ui_art/heros.pcx" );
  sprite.loadSync();
  QCOMPARE( sprite.getCurrentFrameHeight(), 304 );
}

// Check that the current frame height can be returned for a cel image
void getCurrentFrameHeight_cel()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/ctrlpan/panel8bu.cel+levels/towndata/town.pal" );
  sprite.loadSync();
  QCOMPARE( sprite.getCurrentFrameHeight(), 19 );
}

// Check that the current frame height can be returned for a cl2 image
void getCurrentFrameHeight_cl2()
{
  QtD1::MenuSprite sprite;
  sprite.setSource( "/monsters/diablo/diabloa.cl2+levels/towndata/town.pal" );
  sprite.loadSync();
  QCOMPARE( sprite.getCurrentFrameHeight(), 160 );
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestMenuSprite )
#include "tstMenuSprite.moc"

//---------------------------------------------------------------------------//
// end tstMenuSprite.cpp
//---------------------------------------------------------------------------//
