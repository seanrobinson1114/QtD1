//---------------------------------------------------------------------------//
//!
//! \file   LevelObject.cpp
//! \author Alex Robinson
//! \brief  The level object base class declaration
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QtConcurrentRun>

// QtD1 Includes
#include "LevelObject.h"
#include "ImageAssetLoader.h"

namespace QtD1{

// Constructor
LevelObject::LevelObject( QGraphicsObject* parent )
  : QGraphicsObject( parent )
{ /* ... */ }

// Load the raw image asset
void LevelObject::loadRawImageAsset( const QString& image_asset_name,
                                     const QVector<QImage>& image_asset_frames )
{
  QVector<QPixmap> image_asset_pixmaps( image_asset_frames.size() );

  for( int i = 0; i < image_asset_frames.size(); ++i )
    image_asset_pixmaps[i].convertFromImage( image_asset_frames[i] );

  this->loadImageAsset( image_asset_name, image_asset_pixmaps );
}

// Load the raw image assets
void LevelObject::loadRawImageAssets(
                           const QMap<QString,QVector<QImage> >& image_assets )
{
  QSet<QString> image_asset_names;
  this->getImageAssetNames( image_asset_names );

  QSet<QString>::const_iterator image_asset_name_it, image_asset_name_end;
  image_asset_name_it = image_asset_names.begin();
  image_asset_name_end = image_asset_names.end();

  while( image_asset_name_it != image_asset_name_end )
  {
    QMap<QString,QVector<QImage> >::const_iterator asset_map_it =
      image_assets.find( *image_asset_name_it );
    
    if( asset_map_it == image_assets.end() )
    {
      qFatal( "LevelObject Error: Required image asset %s is not present in "
              "the image assets map!",
              image_asset_name_it->toStdString().c_str() );
    }

    this->loadRawImageAsset( asset_map_it.key(), asset_map_it.value() );
    
    ++image_asset_name_it;
  }
}

// Load the image assets
void LevelObject::loadImageAssets(
                          const QMap<QString,QVector<QPixmap> >& image_assets )
{
  QSet<QString> image_asset_names;
  this->getImageAssetNames( image_asset_names );

  QSet<QString>::const_iterator image_asset_name_it, image_asset_name_end;
  image_asset_name_it = image_asset_names.begin();
  image_asset_name_end = image_asset_names.end();

  while( image_asset_name_it != image_asset_name_end )
  {
    QMap<QString,QVector<QPixmap> >::const_iterator asset_map_it =
      image_assets.find( *image_asset_name_it );
    
    if( asset_map_it == image_assets.end() )
    {
      qFatal( "LevelObject Error: Required image asset %s is not present in "
              "the image assets map!",
              image_asset_name_it->toStdString().c_str() );
    }

    this->loadImageAsset( asset_map_it.key(), asset_map_it.value() );
    
    ++image_asset_name_it;
  }
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end LevelObject.cpp
//---------------------------------------------------------------------------//
