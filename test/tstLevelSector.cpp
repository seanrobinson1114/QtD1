//---------------------------------------------------------------------------//
//!
//! \file   tstLevelSector.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level sector unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>
#include <QImageReader>
#include <QImageWriter>
#include <QPainter>
#include <QGraphicsScene>
#include <QtPlugin>

// QtD1 Includes
#include "LevelSector.h"
#include "LevelSectorFactory.h"
#include "MPQHandler.h"

// Import custom plugins
Q_IMPORT_PLUGIN(cel)
Q_IMPORT_PLUGIN(pcx)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestLevelSector : public QObject
{
  Q_OBJECT

private:

  // The image asset frames
  QVector<QPixmap> t_image_asset_frames;

private slots:

  void initTestCase()
  {
    // Register the MPQHandler with the file engine system
    QtD1::MPQHandler::getInstance();

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
// Check that a level sector can be constructed. Construction of a level
// sector is complicated so we will rely on the factory, which will call
// the constructor
void constructor()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();

  QCOMPARE( sector->boundingRect().width(), 3200. );
  QCOMPARE( sector->boundingRect().height(), 1824. );

  delete sector;
}

//---------------------------------------------------------------------------//
// Check that the number of image assets can be returned
void getNumberOfImageAssets()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();

  QCOMPARE( sector->getNumberOfImageAssets(), 1 );

  delete sector;
}

//---------------------------------------------------------------------------//
// Check that the image assets used by the sector can be retrieved
void getImageAssetNames()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();

  QSet<QString> image_asset_names;

  sector->getImageAssetNames( image_asset_names );

  QCOMPARE( image_asset_names.size(), 1 );
  QVERIFY( image_asset_names.contains( "/levels/towndata/town.cel+levels/towndata/town.pal" ) );

  delete sector;
}

//---------------------------------------------------------------------------//
// Check if the image asset is used by the sector
void isImageAssetUsed()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();

  QVERIFY( sector->isImageAssetUsed( "/levels/towndata/town.cel+levels/towndata/town.pal" ) );
  QVERIFY( !sector->isImageAssetUsed( "/dummy/dummy.cel" ) );

  delete sector;
}

//---------------------------------------------------------------------------//
// Check that an image asset can be loaded
void loadImageAsset()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();

  QVERIFY( !sector->imageAssetsLoaded() );
  
  sector->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                          t_image_asset_frames );

  QVERIFY( sector->imageAssetsLoaded() );

  delete sector;
}

//---------------------------------------------------------------------------//
// Check that image assets can be dumped
void dumpImageAssets()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();

  QVERIFY( !sector->imageAssetsLoaded() );
  
  sector->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                          t_image_asset_frames );

  QVERIFY( sector->imageAssetsLoaded() );

  sector->dumpImageAssets();

  QVERIFY( !sector->imageAssetsLoaded() );

  delete sector;
}

//---------------------------------------------------------------------------//
// Check that the sector can be painted
void paint_1()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector1s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();
  
  sector->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                          t_image_asset_frames );
  
  QGraphicsScene sector_scene( sector->boundingRect() );
  sector_scene.addItem( sector );
  
  QImage sector_image( sector->boundingRect().size().toSize(),
                       QImage::Format_ARGB32 );
  sector_image.fill( Qt::blue );

  QPainter sector_painter( &sector_image );

  sector_scene.render( &sector_painter );
  
  // Save the square image for visual inspection
  QImageWriter image_writer( "sector_1.png" );
  image_writer.write( sector_image );
}

//---------------------------------------------------------------------------//
// Check that the sector can be painted
void paint_2()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector2s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();
  
  sector->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                          t_image_asset_frames );
  
  QGraphicsScene sector_scene( sector->boundingRect() );
  sector_scene.addItem( sector );
  
  QImage sector_image( sector->boundingRect().size().toSize(),
                       QImage::Format_ARGB32 );
  sector_image.fill( Qt::blue );

  QPainter sector_painter( &sector_image );

  sector_scene.render( &sector_painter );
  
  // Save the square image for visual inspection
  QImageWriter image_writer( "sector_2.png" );
  image_writer.write( sector_image );
}

//---------------------------------------------------------------------------//
// Check that the sector can be painted
void paint_3()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector3s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();
  
  sector->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                          t_image_asset_frames );
  
  QGraphicsScene sector_scene( sector->boundingRect() );
  sector_scene.addItem( sector );
  
  QImage sector_image( sector->boundingRect().size().toSize(),
                       QImage::Format_ARGB32 );
  sector_image.fill( Qt::blue );

  QPainter sector_painter( &sector_image );

  sector_scene.render( &sector_painter );
  
  // Save the square image for visual inspection
  QImageWriter image_writer( "sector_3.png" );
  image_writer.write( sector_image );
}

//---------------------------------------------------------------------------//
// Check that the sector can be painted
void paint_4()
{
  QtD1::LevelSectorFactory sector_factory( "/levels/towndata/town.min",
                                           "/levels/towndata/town.sol",
                                           "/levels/towndata/town.til",
                                           "/levels/towndata/sector4s.dun" );
  QtD1::LevelSector* sector = sector_factory.createLevelSector();
  
  sector->loadImageAsset( "/levels/towndata/town.cel+levels/towndata/town.pal",
                          t_image_asset_frames );
  
  QGraphicsScene sector_scene( sector->boundingRect() );
  sector_scene.addItem( sector );
  
  QImage sector_image( sector->boundingRect().size().toSize(),
                       QImage::Format_ARGB32 );
  sector_image.fill( Qt::blue );

  QPainter sector_painter( &sector_image );

  sector_scene.render( &sector_painter );
  
  // Save the square image for visual inspection
  QImageWriter image_writer( "sector_4.png" );
  image_writer.write( sector_image );
}

//---------------------------------------------------------------------------//
// End test suite.
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestLevelSector )
#include "tstLevelSector.moc"

//---------------------------------------------------------------------------//
// end tstLevelSector.cpp
//---------------------------------------------------------------------------//
