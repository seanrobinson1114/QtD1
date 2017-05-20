//---------------------------------------------------------------------------//
//!
//! \file   Level.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Level.h"

namespace QtD1{

// Constructor
Level::Level( QObject* parent )
  : QGraphicsScene( parent ),
    d_character( NULL ),
    d_level_objects(),
    d_level_object_asset_map(),
    d_music( new Music ),
    d_image_asset_loader(),
    d_needs_restore( false ),
    d_ready( false )
{ /* ... */ }

// Constructor
Level::Level( QObject* parent, const QString& level_music_file_name )
  : Level( parent )
{
  d_music->setSource( level_music_file_name );
}

// Set the music
void Level::setMusic( const std::shared_ptr<Music>& music )
{
  d_music = music;
}

// Get the character
Character* Level::getCharacter()
{
  return d_character;
}

// Add a level object
void Level::addLevelObject( LevelObject* level_object,
                            const QPointF& location )
{
  d_level_objects << level_object;

  this->addItem( level_object );

  level_object->setPos( location );
}

// Add an actor
void Level::addActor( Actor* actor,
                      const QPointF& location,
                      const Actor::State state,
                      const Direction direction )
{
  d_level_objects << actor;

  this->addItem( actor );

  actor->setPos( location );
  actor->setStateAndDirection( state, direction );
}

// Insert the character
void Level::insertCharacter( Character* character,
                             const QPointF& location,
                             const Direction direction )
{
  d_character = character;

  this->addItem( character );

  character->setPos( location );
  character->setStateAndDirection( Actor::Standing, direction );
}

// Remove the character
void Level::removeCharacter()
{
  this->removeItem( d_character );
}

// Check if the level image assets need to be restored
bool Level::needsRestore()
{
  return d_needs_restore;
}

// Check if the level is ready
bool Level::isReady()
{
  return d_ready;
}

// Load the level image assets
void Level::loadImageAssets()
{
  this->resetAssetData();
  
  // Gather the assets that must be loaded
  QSet<QString> assets_to_load;
  this->gatherImageAssetsToLoad( assets_to_load );

  this->notifyLevelObjectsOfImpendingAssetLoad();

  d_image_asset_loader->setAssetsToLoad( assets_to_load );

  // Connect the image asset loader signals to the level slots
  this->connectImageAssetLoaderSignalsToLevelSlots();
  
  d_image_asset_loader->loadAssets();
}

// Load the level image assets synchronously
void Level::loadImageAssetsSync()
{
  this->resetAssetData();
  
  // Gather the assets that must be loaded
  QSet<QString> assets_to_load;
  this->gatherImageAssetsToLoad( assets_to_load );

  this->notifyLevelObjectsOfImpendingAssetLoad();

  d_image_asset_loader->setAssetsToLoad( assets_to_load );

  // Connect the image asset loader signals to the level slots
  this->connectImageAssetLoaderSignalsToLevelSlots();

  d_image_asset_loader->loadAssetsSync();
}

// Reset the asset data
void Level::resetAssetData()
{
  d_ready = false;
  d_needs_restore = false;

  d_level_object_asset_map.clear();
  
  d_image_asset_loader.reset( new ImageAssetLoader );
}

// Gather image assets to load
void Level::gatherImageAssetsToLoad( QSet<QString>& assets_to_load )
{
  QSet<QString> object_assets;
  
  if( !d_character->imageAssetsLoaded() )
  {
    d_character->getImageAssetNames( object_assets );

    assets_to_load.unite( object_assets );
    object_assets.clear();
  }

  QList<LevelObject*>::const_iterator level_object_it, level_object_end;
  level_object_it = d_level_objects.begin();
  level_object_end = d_level_objects.end();

  while( level_object_it != level_object_end )
  {
    (*level_object_it)->getImageAssetNames( object_assets );

    this->assignLevelObjectToAssetNames( object_assets, *level_object_it );

    assets_to_load.unite( object_assets );
    object_assets.clear();

    ++level_object_it;
  }
}

// Assign the level object to the asset name
void Level::assignLevelObjectToAssetNames( const QSet<QString>& asset_names,
                                           LevelObject* object )
{
  QSet<QString>::const_iterator asset_name_it, asset_name_end;
  asset_name_it = asset_names.begin();
  asset_name_end = asset_names.end();

  while( asset_name_it != asset_name_end )
  {
    d_level_object_asset_map[*asset_name_it] << object;

    ++asset_name_it;
  }
}

// Notify level objects of impending asset load
void Level::notifyLevelObjectsOfImpendingAssetLoad()
{
  if( !d_character->imageAssetsLoaded() )
  {
    d_character->getReadyForImageAssetLoading();
  }
  
  QList<LevelObject*>::const_iterator level_object_it, level_object_end;
  level_object_it = d_level_objects.begin();
  level_object_end = d_level_objects.end();

  while( level_object_it != level_object_end )
  {
    (*level_object_it)->getReadyForImageAssetLoading();

    ++level_object_it;
  }
}

// Dump the level image assets
/*! \details The character assets will not be dumped.
 */
void Level::dumpImageAssets()
{
  QList<LevelObject*>::const_iterator level_object_it, level_object_end;
  level_object_it = d_level_objects.begin();
  level_object_end = d_level_objects.end();

  while( level_object_it != level_object_end )
  {
    (*level_object_it)->dumpImageAssets();

    ++level_object_it;
  }

  d_needs_restore = true;
}

// Restore the level image assets
void Level::restoreImageAssets()
{
  if( this->needsRestore() )
    d_image_asset_loader->dummyLoadAssets();
  else
  {
    qWarning( "Level Warning: The level does not require a restore of its "
              "image assets!" );
  }
}

// Restore the image assets synchronously
void Level::restoreImageAssetsSync()
{
  if( this->needsRestore() )
    d_image_asset_loader->dummyLoadAssetsSync();
  else
  {
    qWarning( "Level Warning: The level does not require a restore of its "
              "image assets!" );
  }
}

// Play the level music
void Level::playLevelMusic()
{
  d_music->playMusic();
}

// Pause the level music
void Level::pauseLevelMusic()
{
  d_music->pauseMusic();
}

// Stop the level music
void Level::stopLevelMusic()
{
  d_music->stopMusic();
}

// Handle image asset loading started
void Level::handleImageAssetLoadingStarted( const int number_of_assets )
{
  emit assetLoadingStarted( number_of_assets );
}

// Handle image asset loaded
void Level::handleImageAssetLoaded( const int number_of_assets_loaded,
                                    const QString asset_name,
                                    const QVector<QImage> asset )
{
  std::cout << asset_name.toStdString() << ": " << asset.size() << std::endl;
    
  emit assetLoaded( number_of_assets_loaded );
}

// Handle image asset loading finished
void Level::handleImageAssetLoadingFinished( const int number_of_assets_loaded )
{
  // Check if the character needs this asset
  if( !d_character->imageAssetsLoaded() )
  {
    d_character->loadRawImageAssets( *d_image_asset_loader->getLoadedAssets() );
    d_character->finalizeImageAssetLoading();
  }

  QList<LevelObject*>::const_iterator level_object_it, level_object_end;
  level_object_it = d_level_objects.begin();
  level_object_end = d_level_objects.end();

  while( level_object_it != level_object_end )
  {
    (*level_object_it)->loadRawImageAssets( *d_image_asset_loader->getLoadedAssets() );
    (*level_object_it)->finalizeImageAssetLoading();

    ++level_object_it;
  }
  
  d_ready = true;
  d_needs_restore = false;
  
  emit assetLoadingFinished( number_of_assets_loaded );
}

// Connect the image asset loader signals to the level slots
void Level::connectImageAssetLoaderSignalsToLevelSlots() const
{
  QObject::connect( d_image_asset_loader.get(), SIGNAL(assetLoadingStarted(const int)),
                    this, SLOT(handleImageAssetLoadingStarted(const int)) );
  QObject::connect( d_image_asset_loader.get(), SIGNAL(assetLoaded(const int, const QString, const QVector<QImage>)),
                    this, SLOT(handleImageAssetLoaded(const int, const QString, const QVector<QImage>)) );
  QObject::connect( d_image_asset_loader.get(), SIGNAL(assetLoadingFinished(const int)),
                    this, SLOT(handleImageAssetLoadingFinished(const int)) );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Level.cpp
//---------------------------------------------------------------------------//
