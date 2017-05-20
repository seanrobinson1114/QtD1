//---------------------------------------------------------------------------//
//!
//! \file   ImageAssetLoader.cpp
//! \author Alex Robinson
//! \brief  The image asset loader class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QImageReader>
#include <QtConcurrentRun>
#include <QFile>

// QtD1 Includes
#include "ImageAssetLoader.h"

namespace QtD1{

// Constructor
ImageAssetLoader::ImageAssetLoader( QObject* parent )
  : QObject( parent ),
    d_assets(),
    d_asset_load_future(),
    d_asset_load_future_watcher()
{
  // The assetLoaded signal sends a QVector<QImage> type, which is not
  // registered with the MetaObject system by default. We will do it here.
  qRegisterMetaType<QVector<QImage> >( "QVector<QImage>" );
  
  // Connect the asset load future watcher signal to the handle async asset
  // load finished slot
  QObject::connect( &d_asset_load_future_watcher, SIGNAL(finished()),
                    this, SLOT(handleAsyncAssetLoadingFinished()) );
}

// Set the image asset names to load
void ImageAssetLoader::setAssetsToLoad( const QSet<QString>& image_asset_names )
{
  // Clear the current assets
  d_assets.reset( new QMap<QString,QVector<QImage> > );

  // Assign the new asset names
  QSet<QString>::const_iterator asset_name_it, asset_name_end;
  asset_name_it = image_asset_names.begin();
  asset_name_end = image_asset_names.end();

  while( asset_name_it != asset_name_end )
  {
    (*d_assets)[*asset_name_it];
    
    ++asset_name_it;
  }
}

// Get the number of image assets
int ImageAssetLoader::getNumberOfAssets()
{
  if( d_assets )
    return d_assets->size();
  else
    return 0;
}

// Get the loaded image assets
std::shared_ptr<const QMap<QString,QVector<QImage> > >
ImageAssetLoader::getLoadedAssets() const
{
  return d_assets;
}

// Load the image assets
void ImageAssetLoader::loadAssets()
{
  d_asset_load_future =
    QtConcurrent::run( ImageAssetLoader::loadAssetsImpl, this );

  d_asset_load_future_watcher.setFuture( d_asset_load_future );
}

// Load the image assets synchronously
void ImageAssetLoader::loadAssetsSync()
{
  ImageAssetLoader::loadAssetsImpl( this );
}

// Load the image assets implementation
void ImageAssetLoader::loadAssetsImpl( ImageAssetLoader* obj )
{
  QMap<QString,QVector<QImage> >::iterator asset_it, asset_end;
  asset_it = obj->d_assets->begin();
  asset_end = obj->d_assets->end();

  int assets_loaded = 0;
  
  // Start loading assets
  emit obj->assetLoadingStarted( obj->d_assets->size() );
  
  QImageReader image_reader;
  while( asset_it != asset_end )
  {
    image_reader.setFileName( asset_it.key() );
    
    QVector<QImage>& asset_images = asset_it.value();
    asset_images.resize( image_reader.imageCount() );

    for( int i = 0; i < asset_images.size(); ++i )
    {
      asset_images[i] = image_reader.read();

      image_reader.jumpToNextImage();
    }
    
    // The asset has been loaded
    ++assets_loaded;
    emit obj->assetLoaded( assets_loaded, asset_it.key(), asset_it.value() );
    
    ++asset_it;
  }

  emit obj->assetLoadingFinished( obj->d_assets->size() );
}

// Dummy load the previously loaded image assets
void ImageAssetLoader::dummyLoadAssets()
{
  d_asset_load_future =
    QtConcurrent::run( ImageAssetLoader::dummyLoadAssetsImpl, this );

  d_asset_load_future_watcher.setFuture( d_asset_load_future );
}

// Dummy load the previously loaded image assets synchronously
void ImageAssetLoader::dummyLoadAssetsSync()
{
  ImageAssetLoader::dummyLoadAssetsImpl( this );
}

// Dummy load the previously loaded image assets implementation
void ImageAssetLoader::dummyLoadAssetsImpl( ImageAssetLoader* obj )
{
  QMap<QString,QVector<QImage> >::iterator asset_it, asset_end;
  asset_it = obj->d_assets->begin();
  asset_end = obj->d_assets->end();

  int assets_loaded = 0;

  // Start loading assets
  emit obj->assetLoadingStarted( obj->d_assets->size() );

  while( asset_it != asset_end )
  {
    ++assets_loaded;

    emit obj->assetLoaded( assets_loaded, asset_it.key(), asset_it.value() );
        
    ++asset_it;
  }

  emit obj->assetLoadingFinished( obj->d_assets->size() );
}

// Handle asynchronous asset loading finished
void ImageAssetLoader::handleAsyncAssetLoadingFinished()
{ /* ... */ }

// Wait for load to finish
void ImageAssetLoader::waitForLoadToFinish()
{
  if( d_asset_load_future.isRunning() )
    d_asset_load_future_watcher.waitForFinished();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end ImageAssetLoader.cpp
//---------------------------------------------------------------------------//
