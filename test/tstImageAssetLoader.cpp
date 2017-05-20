//---------------------------------------------------------------------------//
//!
//! \file   tstImageAssetLoader.cpp
//! \author Alex Robinson
//! \brief  Image asset loader unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Qt Includes
#include <QtTest/QtTest>
#include <QtPlugin>
#include <QSignalSpy>

// QtD1 Includes
#include "ImageAssetLoader.h"
#include "MPQHandler.h"

// Import custom plugins
Q_IMPORT_PLUGIN(pcx)
Q_IMPORT_PLUGIN(cel)

//---------------------------------------------------------------------------//
// Test suite.
//---------------------------------------------------------------------------//
class TestImageAssetLoader : public QObject
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
// Check that the source can be set
void setAssetsToLoad()
{
  QtD1::ImageAssetLoader loader;

  QSet<QString> image_asset_names;
  image_asset_names.insert( "/ui_art/logo.pcx" );
  image_asset_names.insert( "/data/PentSpin.cel+levels/towndata/town.pal" );

  loader.setAssetsToLoad( image_asset_names );

  QCOMPARE( loader.getNumberOfAssets(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the assets can be loaded asynchronously
void loadAssets()
{
  QtD1::ImageAssetLoader loader;

  {
    QSet<QString> image_asset_names;
    image_asset_names.insert( "/ui_art/logo.pcx" );
    image_asset_names.insert( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.setAssetsToLoad( image_asset_names );
  }

  QSignalSpy asset_load_started_spy( &loader, SIGNAL(assetLoadingStarted(const int)) );
  QSignalSpy asset_loaded_spy( &loader, SIGNAL(assetLoaded(const int, const QString, const QVector<QImage>)) );
  QSignalSpy asset_load_finished_spy( &loader, SIGNAL(assetLoadingFinished(const int)) );

  loader.loadAssets();
  loader.waitForLoadToFinish();

  // Check that the loading started signal was emitted
  QCOMPARE( asset_load_started_spy.size(), 1 );
  QCOMPARE( asset_load_started_spy[0].size(), 1 );
  QCOMPARE( asset_load_started_spy[0][0].toInt(), 2 );

  // Check that all assets have been loaded
  QCOMPARE( asset_loaded_spy.size(), 2 );
  QCOMPARE( asset_loaded_spy[0].size(), 3 );
  QCOMPARE( asset_loaded_spy[0][0].toInt(), 1 );
  QCOMPARE( asset_loaded_spy[0][1].toString(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal" ) );

  QVector<QImage> asset_frames =
    asset_loaded_spy[0][2].value<QVector<QImage> >();
  
  QCOMPARE( asset_frames.size(), 8 );

  for( int i = 0; i < asset_frames.size(); ++i )
  {
    QCOMPARE( asset_frames[i].width(), 48 );
    QCOMPARE( asset_frames[i].height(), 48 );
  }
  
  QCOMPARE( asset_loaded_spy[1].size(), 3 );
  QCOMPARE( asset_loaded_spy[1][0].toInt(), 2 );
  QCOMPARE( asset_loaded_spy[1][1].toString(), QString("/ui_art/logo.pcx") );

 asset_frames = asset_loaded_spy[1][2].value<QVector<QImage> >();
  
  QCOMPARE( asset_frames.size(), 1 );
  QCOMPARE( asset_frames[0].width(), 550 );
  QCOMPARE( asset_frames[0].height(), 3240 );
}

//---------------------------------------------------------------------------//
// Check that the assets can be loaded synchronously
void loadAssetsSync()
{
  QtD1::ImageAssetLoader loader;

  {
    QSet<QString> image_asset_names;
    image_asset_names.insert( "/ui_art/logo.pcx" );
    image_asset_names.insert( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.setAssetsToLoad( image_asset_names );
  }

  QSignalSpy asset_load_started_spy( &loader, SIGNAL(assetLoadingStarted(const int)) );
  QSignalSpy asset_loaded_spy( &loader, SIGNAL(assetLoaded(const int, const QString, const QVector<QImage>)) );
  QSignalSpy asset_load_finished_spy( &loader, SIGNAL(assetLoadingFinished(const int)) );

  loader.loadAssetsSync();

  // Check that the loading started signal was emitted
  QCOMPARE( asset_load_started_spy.size(), 1 );
  QCOMPARE( asset_load_started_spy[0].size(), 1 );
  QCOMPARE( asset_load_started_spy[0][0].toInt(), 2 );

  // Check that all assets have been loaded
  QCOMPARE( asset_loaded_spy.size(), 2 );
  QCOMPARE( asset_loaded_spy[0].size(), 3 );
  QCOMPARE( asset_loaded_spy[0][0].toInt(), 1 );
  QCOMPARE( asset_loaded_spy[0][1].toString(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal" ) );

  QVector<QImage> asset_frames =
    asset_loaded_spy[0][2].value<QVector<QImage> >();
  
  QCOMPARE( asset_frames.size(), 8 );

  for( int i = 0; i < asset_frames.size(); ++i )
  {
    QCOMPARE( asset_frames[i].width(), 48 );
    QCOMPARE( asset_frames[i].height(), 48 );
  }
  
  QCOMPARE( asset_loaded_spy[1].size(), 3 );
  QCOMPARE( asset_loaded_spy[1][0].toInt(), 2 );
  QCOMPARE( asset_loaded_spy[1][1].toString(), QString("/ui_art/logo.pcx") );

 asset_frames = asset_loaded_spy[1][2].value<QVector<QImage> >();
  
  QCOMPARE( asset_frames.size(), 1 );
  QCOMPARE( asset_frames[0].width(), 550 );
  QCOMPARE( asset_frames[0].height(), 3240 );
}

//---------------------------------------------------------------------------//
// Check that a dummy asset load can be done asynchronously
void dummyLoadAssets()
{
  QtD1::ImageAssetLoader loader;

  {
    QSet<QString> image_asset_names;
    image_asset_names.insert( "/ui_art/logo.pcx" );
    image_asset_names.insert( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.setAssetsToLoad( image_asset_names );
  }

  loader.loadAssetsSync();

  QSignalSpy asset_load_started_spy( &loader, SIGNAL(assetLoadingStarted(const int)) );
  QSignalSpy asset_loaded_spy( &loader, SIGNAL(assetLoaded(const int, const QString, const QVector<QImage>)) );
  QSignalSpy asset_load_finished_spy( &loader, SIGNAL(assetLoadingFinished(const int)) );

  loader.dummyLoadAssets();
  loader.waitForLoadToFinish();

  // Check that the loading started signal was emitted
  QCOMPARE( asset_load_started_spy.size(), 1 );
  QCOMPARE( asset_load_started_spy[0].size(), 1 );
  QCOMPARE( asset_load_started_spy[0][0].toInt(), 2 );

  // Check that all assets have been loaded
  QCOMPARE( asset_loaded_spy.size(), 2 );
  QCOMPARE( asset_loaded_spy[0].size(), 3 );
  QCOMPARE( asset_loaded_spy[0][0].toInt(), 1 );
  QCOMPARE( asset_loaded_spy[0][1].toString(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal" ) );

  QVector<QImage> asset_frames =
    asset_loaded_spy[0][2].value<QVector<QImage> >();
  
  QCOMPARE( asset_frames.size(), 8 );

  for( int i = 0; i < asset_frames.size(); ++i )
  {
    QCOMPARE( asset_frames[i].width(), 48 );
    QCOMPARE( asset_frames[i].height(), 48 );
  }
  
  QCOMPARE( asset_loaded_spy[1].size(), 3 );
  QCOMPARE( asset_loaded_spy[1][0].toInt(), 2 );
  QCOMPARE( asset_loaded_spy[1][1].toString(), QString("/ui_art/logo.pcx") );

 asset_frames = asset_loaded_spy[1][2].value<QVector<QImage> >();
  
  QCOMPARE( asset_frames.size(), 1 );
  QCOMPARE( asset_frames[0].width(), 550 );
  QCOMPARE( asset_frames[0].height(), 3240 );
}

//---------------------------------------------------------------------------//
// Check that a dummy asset load can be done synchronously
void dummyLoadAssetsSync()
{
  QtD1::ImageAssetLoader loader;

  {
    QSet<QString> image_asset_names;
    image_asset_names.insert( "/ui_art/logo.pcx" );
    image_asset_names.insert( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.setAssetsToLoad( image_asset_names );
  }

  loader.loadAssetsSync();

  QSignalSpy asset_load_started_spy( &loader, SIGNAL(assetLoadingStarted(const int)) );
  QSignalSpy asset_loaded_spy( &loader, SIGNAL(assetLoaded(const int, const QString, const QVector<QImage>)) );
  QSignalSpy asset_load_finished_spy( &loader, SIGNAL(assetLoadingFinished(const int)) );

  loader.dummyLoadAssetsSync();

  // Check that the loading started signal was emitted
  QCOMPARE( asset_load_started_spy.size(), 1 );
  QCOMPARE( asset_load_started_spy[0].size(), 1 );
  QCOMPARE( asset_load_started_spy[0][0].toInt(), 2 );

  // Check that all assets have been loaded
  QCOMPARE( asset_loaded_spy.size(), 2 );
  QCOMPARE( asset_loaded_spy[0].size(), 3 );
  QCOMPARE( asset_loaded_spy[0][0].toInt(), 1 );
  QCOMPARE( asset_loaded_spy[0][1].toString(),
            QString("/data/PentSpin.cel+levels/towndata/town.pal" ) );

  QVector<QImage> asset_frames =
    asset_loaded_spy[0][2].value<QVector<QImage> >();
  
  QCOMPARE( asset_frames.size(), 8 );

  for( int i = 0; i < asset_frames.size(); ++i )
  {
    QCOMPARE( asset_frames[i].width(), 48 );
    QCOMPARE( asset_frames[i].height(), 48 );
  }
  
  QCOMPARE( asset_loaded_spy[1].size(), 3 );
  QCOMPARE( asset_loaded_spy[1][0].toInt(), 2 );
  QCOMPARE( asset_loaded_spy[1][1].toString(), QString("/ui_art/logo.pcx") );

 asset_frames = asset_loaded_spy[1][2].value<QVector<QImage> >();
  
  QCOMPARE( asset_frames.size(), 1 );
  QCOMPARE( asset_frames[0].width(), 550 );
  QCOMPARE( asset_frames[0].height(), 3240 );
}

//---------------------------------------------------------------------------//
// Check that loaded assets can be returned
void getLoadedAssets()
{
  QtD1::ImageAssetLoader loader;

  {
    QSet<QString> image_asset_names;
    image_asset_names.insert( "/ui_art/logo.pcx" );
    image_asset_names.insert( "/data/PentSpin.cel+levels/towndata/town.pal" );

    loader.setAssetsToLoad( image_asset_names );
  }

  loader.loadAssetsSync();

  std::shared_ptr<const QMap<QString,QVector<QImage> > > assets =
    loader.getLoadedAssets();

  QVERIFY( assets.get() != NULL );
  QCOMPARE( assets->size(), 2 );
  QVERIFY( assets->find( "/ui_art/logo.pcx" ) != assets->end() );
  QVERIFY( assets->find( "/data/PentSpin.cel+levels/towndata/town.pal" ) != assets->end() );

  QMap<QString,QVector<QImage> >::const_iterator asset_it =
    assets->find( "/ui_art/logo.pcx" );

  QCOMPARE( asset_it.value().size(), 1 );
  QCOMPARE( asset_it.value()[0].width(), 550 );
  QCOMPARE( asset_it.value()[0].height(), 3240 );

  asset_it = assets->find( "/data/PentSpin.cel+levels/towndata/town.pal" );

  QCOMPARE( asset_it.value().size(), 8 );

  for( int i = 0; i < 8; ++i )
  {
    QCOMPARE( asset_it.value()[i].width(), 48 );
    QCOMPARE( asset_it.value()[i].height(), 48 );
  }
}
  
//---------------------------------------------------------------------------//
// End test suite
//---------------------------------------------------------------------------//
};

//---------------------------------------------------------------------------//
// Test Main
//---------------------------------------------------------------------------//
QTEST_MAIN( TestImageAssetLoader )
#include "tstImageAssetLoader.moc"

//---------------------------------------------------------------------------//
// end tstImageAssetLoader.cpp
//---------------------------------------------------------------------------//
