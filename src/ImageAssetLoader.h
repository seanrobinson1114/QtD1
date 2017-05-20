//---------------------------------------------------------------------------//
//!
//! \file   ImageAssetLoader.h
//! \author Alex Robinson
//! \brief  The image asset loader class declaration
//!
//---------------------------------------------------------------------------//

#ifndef IMAGE_ASSET_LOADER_H
#define IMAGE_ASSET_LOADER_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QObject>
#include <QSet>
#include <QMap>
#include <QVector>
#include <QString>
#include <QFuture>
#include <QFutureWatcher>
#include <QMetaType>

namespace QtD1{

//! The image asset loader
class ImageAssetLoader : public QObject
{
  Q_OBJECT
  
public:

  //! Constructor
  ImageAssetLoader( QObject* parent = 0 );

  //! Destructor
  ~ImageAssetLoader()
  { /* ... */ }

  //! Set the image asset names to load
  void setAssetsToLoad( const QSet<QString>& image_asset_names );

  //! Get the number of image assets
  int getNumberOfAssets();

  //! Get the loaded image assets
  std::shared_ptr<const QMap<QString,QVector<QImage> > >
  getLoadedAssets() const;

signals:

  //! Asset loading started
  void assetLoadingStarted( const int number_of_assets );

  //! Asset loaded
  void assetLoaded( const int number_of_assets_loaded,
                    const QString asset_name,
                    const QVector<QImage> asset );

  //! Asset loading finished
  void assetLoadingFinished( const int number_of_assets_loaded );

public slots:

  //! Load the image assets
  void loadAssets();

  //! Load the image assets synchronously
  void loadAssetsSync();

  //! Dummy load the previously loaded image assets
  void dummyLoadAssets();

  //! Dummy load the previously loaded image assets synchronously
  void dummyLoadAssetsSync();

  //! Wait for load to finish
  void waitForLoadToFinish();

private slots:

  // Handle asynchronous asset loading finished
  void handleAsyncAssetLoadingFinished();

private:

  // Load the image assets implementation
  static void loadAssetsImpl( ImageAssetLoader* obj );

  // Dummy load the previously loaded image assets implementation
  static void dummyLoadAssetsImpl( ImageAssetLoader* obj );

  // The assets
  std::shared_ptr<QMap<QString,QVector<QImage> > > d_assets;

  // The asset load future
  QFuture<void> d_asset_load_future;

  // The asset load future watcher
  QFutureWatcher<void> d_asset_load_future_watcher;
};
  
} // end QtD1 namespace

Q_DECLARE_METATYPE(QVector<QImage>)

#endif // end IMAGE_ASSET_LOADER_H

//---------------------------------------------------------------------------//
// end ImageAssetLoader.h
//---------------------------------------------------------------------------//

