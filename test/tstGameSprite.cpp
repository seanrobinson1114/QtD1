//---------------------------------------------------------------------------//
//!
//! \file   tstGameSprite.cpp
//! \author Alex Robinson
//! \brief  Game sprite unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>
#include <QtPlugin>

// QtD1 Includes
#include "GameSprite.h"
#include "ImageAssetLoader.h"
#include "MPQHandler.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestGameSprite : public QObject
{
  Q_OBJECT

private:

  // The image asset loader
  QtD1::ImageAssetLoader t_loader;

private slots:

  void initTestCase()
  {
    // Register the MPQHandler with the file engine system
    QtD1::MPQHandler::getInstance();

    QSet<QString> image_asset_names;
    image_asset_names.insert( "/data/PentSpin.cel+levels/towndata/town.pal" );

    t_loader.setAssetsToLoad( image_asset_names );
    t_loader.loadAssetsSync();
  }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the game sprite asset can be set
void setAsset()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                               {0, 1, 2, 3, 4, 5, 6, 7} );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );
  
  QCOMPARE( sprite.getNumberOfFrames(), 8 );

  sprite.dumpAsset();

  QVector<QPixmap> pixmaps( 8 );

  for( int i = 0; i < 8; ++i )
  {
    pixmaps[i].convertFromImage(
                              t_loader.getLoadedAssets()->begin().value()[i] );
  }

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(), pixmaps );

  QCOMPARE( sprite.getNumberOfFrames(), 8 );
}

//---------------------------------------------------------------------------//
// Check if the sprite is ready
void isReady()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                               {0, 1, 2, 3, 4, 5, 6, 7} );

  QVERIFY( !sprite.isReady() );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );

  QVERIFY( sprite.isReady() );

  sprite.dumpAsset();

  QVERIFY( !sprite.isReady() );

  QVector<QPixmap> pixmaps( 8 );

  for( int i = 0; i < 8; ++i )
  {
    pixmaps[i].convertFromImage(
                              t_loader.getLoadedAssets()->begin().value()[i] );
  }

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(), pixmaps );

  QVERIFY( sprite.isReady() );
}

//---------------------------------------------------------------------------//
// Check that the duration of the sprite can be set
void setDuration()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                           {0, 1, 2, 3, 4, 5, 6, 7} );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );

  sprite.setDuration( 1 );

  QCOMPARE( sprite.getDuration(), 8 );

  sprite.setDuration( 9 );

  QCOMPARE( sprite.getDuration(), 8 );

  sprite.setDuration( 16 );

  QCOMPARE( sprite.getDuration(), 16 );

  sprite.setDuration( 23 );

  QCOMPARE( sprite.getDuration(), 16 );
}

//---------------------------------------------------------------------------//
// Check that the duration of each sprite frame can be set
void setFrameDuration()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                           {0, 1, 2, 3, 4, 5, 6, 7} );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );

  sprite.setFrameDuration( 0 );

  QCOMPARE( sprite.getFrameDuration(), 1 );
  QCOMPARE( sprite.getDuration(), 8 );

  sprite.setFrameDuration( 1 );

  QCOMPARE( sprite.getFrameDuration(), 1 );
  QCOMPARE( sprite.getDuration(), 8 );

  sprite.setFrameDuration( 2 );

  QCOMPARE( sprite.getFrameDuration(), 2 );
  QCOMPARE( sprite.getDuration(), 16 );
}

//---------------------------------------------------------------------------//
// Check that the sprite frame can be set
void setFrame()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                           {0, 1, 2, 3, 4, 5, 6, 7} );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );

  QCOMPARE( sprite.getFrame(), 0 );

  sprite.setFrame( 1 );

  QCOMPARE( sprite.getFrame(), 1 );

  sprite.setFrame( 7 );

  QCOMPARE( sprite.getFrame(), 7 );

  // Going beyond the max frame index is okay (mod operator will be used)
  sprite.setFrame( 8 );

  QCOMPARE( sprite.getFrame(), 0 );

  sprite.setFrame( 15 );

  QCOMPARE( sprite.getFrame(), 7 );
}

//---------------------------------------------------------------------------//
// Check that the sprite frame can be incremented
void incrementFrame()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                           {0, 1, 2, 3, 4, 5, 6, 7} );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );

  QCOMPARE( sprite.getFrame(), 0 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 1 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 2 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 3 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 4 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 5 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 6 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 7 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 0 );

  sprite.incrementFrame();

  QCOMPARE( sprite.getFrame(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the sprite frame can be incremented
void incrementElapsedGameTics()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                           {0, 1, 2, 3, 4, 5, 6, 7} );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );
  sprite.setFrameDuration( 2 );
  
  QCOMPARE( sprite.getFrame(), 0 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QCOMPARE( sprite.getFrame(), 0 );

  QVERIFY( sprite.incrementElapsedGameTics() );
  QCOMPARE( sprite.getFrame(), 1 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QVERIFY( sprite.incrementElapsedGameTics() );

  QCOMPARE( sprite.getFrame(), 2 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QVERIFY( sprite.incrementElapsedGameTics() );

  QCOMPARE( sprite.getFrame(), 3 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QVERIFY( sprite.incrementElapsedGameTics() );

  QCOMPARE( sprite.getFrame(), 4 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QVERIFY( sprite.incrementElapsedGameTics() );

  QCOMPARE( sprite.getFrame(), 5 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QVERIFY( sprite.incrementElapsedGameTics() );

  QCOMPARE( sprite.getFrame(), 6 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QVERIFY( sprite.incrementElapsedGameTics() );

  QCOMPARE( sprite.getFrame(), 7 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QVERIFY( sprite.incrementElapsedGameTics() );

  QCOMPARE( sprite.getFrame(), 0 );

  QVERIFY( !sprite.incrementElapsedGameTics() );
  QVERIFY( sprite.incrementElapsedGameTics() );

  QCOMPARE( sprite.getFrame(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the frame image can be returned
void getFrameImage()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                               {0, 1, 2, 3, 4, 5, 6, 7} );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );

  QPixmap image = sprite.getFrameImage( 1 );

  QCOMPARE( image.width(), 48 );
  QCOMPARE( image.height(), 48 );

  sprite.setFrame( 3 );

  image = sprite.getFrameImage();

  QCOMPARE( image.width(), 48 );
  QCOMPARE( image.height(), 48 );
}

//---------------------------------------------------------------------------//
// Check that the frame bounding rect can be returned
void boundingRect()
{
  QtD1::GameSprite sprite( t_loader.getLoadedAssets()->begin().key(),
                               {0, 1, 2, 3, 4, 5, 6, 7} );

  sprite.setAsset( t_loader.getLoadedAssets()->begin().key(),
                   t_loader.getLoadedAssets()->begin().value() );

  sprite.setFrame( 1 );

  QCOMPARE( sprite.boundingRect().left(), 0. );
  QCOMPARE( sprite.boundingRect().top(), 0. );
  QCOMPARE( sprite.boundingRect().width(), 48. );
  QCOMPARE( sprite.boundingRect().height(), 48. );
}

//---------------------------------------------------------------------------//
// End test suite
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestGameSprite )
#include "tstGameSprite.moc"

//---------------------------------------------------------------------------//
// end tstGameSprite.cpp
//---------------------------------------------------------------------------//
