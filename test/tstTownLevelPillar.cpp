//---------------------------------------------------------------------------//
//!
//! \file   tstTownLevelPillar.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The town level pillar unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QtTest/QtTest>
#include <QImageReader>
#include <QImageWriter>
#include <QPainter>
#include <QtPlugin>

// QtD1 Includes
#include "TownLevelPillar.h"
#include "MPQHandler.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)
Q_IMPORT_PLUGIN(pcx)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestTownLevelPillar : public QObject
{
  Q_OBJECT

private:

  // The pillar blocks
  QVector<QtD1::LevelPillar::Block> t_pillar_blocks;

  // The image asset frames
  QVector<QPixmap> t_image_asset_frames;

private slots:

  void initTestCase()
  {
    // Register the MPQHandler with the file engine system
    QtD1::MPQHandler::getInstance();

    // These blocks correspond to pillar 127
    t_pillar_blocks.resize( 16 );
    t_pillar_blocks[0].transparent = true;
    t_pillar_blocks[1].transparent = true;
    t_pillar_blocks[2].transparent = true;
    t_pillar_blocks[3].transparent = true;
    t_pillar_blocks[4].transparent = true;
    t_pillar_blocks[5].transparent = true;
    t_pillar_blocks[6].transparent = true;
    t_pillar_blocks[7].transparent = true;
    
    t_pillar_blocks[8].transparent = false;
    t_pillar_blocks[8].frame_index = 256;
    t_pillar_blocks[8].type = 1;
  
    t_pillar_blocks[9].transparent = false;
    t_pillar_blocks[9].frame_index = 257;
    t_pillar_blocks[9].type = 1;
    
    t_pillar_blocks[10].transparent = false;
    t_pillar_blocks[10].frame_index = 258;
    t_pillar_blocks[10].type = 1;

    t_pillar_blocks[11].transparent = false;
    t_pillar_blocks[11].frame_index = 259;
    t_pillar_blocks[11].type = 1;

    t_pillar_blocks[12].transparent = false;
    t_pillar_blocks[12].frame_index = 260;
    t_pillar_blocks[12].type = 1;

    t_pillar_blocks[13].transparent = false;
    t_pillar_blocks[13].frame_index = 261;
    t_pillar_blocks[13].type = 1;

    t_pillar_blocks[14].transparent = false;
    t_pillar_blocks[14].frame_index = 262;
    t_pillar_blocks[14].type = 1;

    t_pillar_blocks[15].transparent = false;
    t_pillar_blocks[15].frame_index = 263;
    t_pillar_blocks[15].type = 1;

    // Load the image asset frames
    QImageReader asset_reader( "/levels/towndata/town.cel+levels/towndata/town.pal" );

    t_image_asset_frames.resize( asset_reader.imageCount() );
    
    for( int i = 0; i < asset_reader.imageCount(); ++i )
    {
      t_image_asset_frames[i].convertFromImage( asset_reader.read() );

      asset_reader.jumpToNextImage();
    }
  }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a level pillar can be constructed
void constructor()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );
  QRectF pillar_rect = pillar.boundingRect();
  
  QCOMPARE( pillar_rect.width(), 64. );
  QCOMPARE( pillar_rect.height(), 256. );
}

//---------------------------------------------------------------------------//
// Check that the number of image assets used can be returned
void getNumberOfImageAssets()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );

  QCOMPARE( pillar.getNumberOfImageAssets(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the image assets used by the pillar can be returned
void getImageAssetNames()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );

  QSet<QString> image_asset_names;

  pillar.getImageAssetNames( image_asset_names );

  QCOMPARE( image_asset_names.size(), 1 );
  QVERIFY( image_asset_names.contains( "/levels/towndata/town.cel+levels/towndata/town.pal" ) );
}

//---------------------------------------------------------------------------//
// Check if the image asset is used by the pillar
void isImageAssetUsed()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );

  QVERIFY( pillar.isImageAssetUsed( "/levels/towndata/town.cel+levels/towndata/town.pal" ) );
  QVERIFY( !pillar.isImageAssetUsed( "/dummy_file" ) );
}

//---------------------------------------------------------------------------//
// Check that the image asset can be loaded by the pillar
void loadImageAsset()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );

  QVERIFY( !pillar.imageAssetsLoaded() );
  
  pillar.loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                         t_image_asset_frames );

  QVERIFY( pillar.imageAssetsLoaded() );
}

//---------------------------------------------------------------------------//
// Check that the image asset can be dumped by the pillar
void dumpImageAssets()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );

  QVERIFY( !pillar.imageAssetsLoaded() );
  
  pillar.loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                         t_image_asset_frames );

  QVERIFY( pillar.imageAssetsLoaded() );

  pillar.dumpImageAssets();

  QVERIFY( !pillar.imageAssetsLoaded() );
}

//---------------------------------------------------------------------------//
// Check that the pillar can be cloned
void clone()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );

  pillar.loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                         t_image_asset_frames );

  QtD1::TownLevelPillar* pillar_clone = pillar.clone();

  QCOMPARE( pillar.boundingRect(), pillar_clone->boundingRect() );
  QCOMPARE( pillar.shape(), pillar_clone->shape() );
  QVERIFY( &pillar != pillar_clone );
  QVERIFY( pillar_clone->isImageAssetUsed( "/levels/towndata/town.cel+levels/towndata/town.pal" ) );

  delete pillar_clone;
}

//---------------------------------------------------------------------------//
// Check that the shape of the pillar is valid
void shape()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );

  pillar.loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                         t_image_asset_frames );

  QVERIFY( !pillar.shape().isEmpty() );
}

//---------------------------------------------------------------------------//
// Check that the pillar can be painted
void paint()
{
  QtD1::TownLevelPillar pillar( t_pillar_blocks,
                                QtD1::LevelPillar::Properties() );

  pillar.loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                         t_image_asset_frames );
  
  QImage pillar_image( pillar.boundingRect().size().toSize(),
                       QImage::Format_ARGB32 );
  QPainter pillar_painter( &pillar_image );

  pillar.paint( &pillar_painter, NULL, NULL );

  // Save the pillar image for visual inspection
  QImageWriter image_writer( "pillar_0127.png" );
  image_writer.write( pillar_image );
}
  
//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestTownLevelPillar )
#include "tstTownLevelPillar.moc"

//---------------------------------------------------------------------------//
// end tstTownLevelPillar.cpp
//---------------------------------------------------------------------------//
