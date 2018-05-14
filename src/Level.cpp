//---------------------------------------------------------------------------//
//!
//! \file   Level.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The level class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Qt Includes
#include <QImageReader>

// QtD1 Includes
#include "Level.h"
#include "LevelPillarFactory.h"

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
    d_ready( false ),
    d_grid()
{ /* ... */ }

// Constructor
Level::Level( QObject* parent, const QString& level_music_file_name )
  : Level( parent )
{
  // Set the level music
  d_music->setSource( level_music_file_name );
}

// Set the music
void Level::setMusic( const std::shared_ptr<Music>& music )
{
  d_music = music;
}

// Set the grid
void Level::setGrid( const std::shared_ptr<const Grid>& grid )
{
  d_grid = grid;
}

// Create the level background
void Level::createBackground()
{
  this->createSectors( d_level_sectors );
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

  // Notify game instance if object is interactive
  if( level_object->isInteractive() )
    this->connectInteractiveLevelObjectSignalsToLevelSignals( level_object );
}

// Add an actor
void Level::addActor( Actor* actor,
                      const QPointF& location,
                      const Direction direction )
{
  d_level_objects << actor;

  this->addItem( actor );

  actor->setPos( location );
  actor->setDirection( direction );
}

// Insert the character
void Level::insertCharacter( Character* character,
                             const QPointF& location,
                             const Direction direction )
{
  d_character = character;

  this->addItem( character );

  this->connectCharacterSignalsToLevelSlots();

  character->setPos( location );
  character->setDirection( direction );

  character->setGrid( d_grid );

  this->handleCharacterPositionChanged();

  // Check that character is interactive
  if( character->isInteractive() )
    this->connectInteractiveLevelObjectSignalsToLevelSignals( character );
}

// Remove the character
void Level::removeCharacter()
{
  this->disconnectCharacterSignalsFromLevelSlots();

  this->removeItem( d_character );
}

// Initialize the grid
void Level::initializeGrid( int rows, int columns, QList<LevelPillar*> pillars )
{
  d_grid.reset( new Grid( rows, columns, pillars ) );
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
  // Add the sector assets
  assets_to_load.insert( this->getImageAssetName() );

  QList<LevelSector*>::const_iterator level_sector_it, level_sector_end;
  level_sector_it = d_level_sectors.begin();
  level_sector_end = d_level_sectors.end();

  while( level_sector_it != level_sector_end )
  {
    this->assignLevelObjectToAssetNames( assets_to_load, *level_sector_it );

    ++level_sector_it;
  }

  // Add the externally added object assets
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

  QList<LevelSector*>::const_iterator level_sector_it, level_sector_end;
  level_sector_it = d_level_sectors.begin();
  level_sector_end = d_level_sectors.end();

  while( level_sector_it != level_sector_end )
  {
    (*level_sector_it)->loadRawImageAssets( *d_image_asset_loader->getLoadedAssets() );
    (*level_sector_it)->finalizeImageAssetLoading();

    ++level_sector_it;
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

// Handle character position changed
void Level::handleCharacterPositionChanged()
{
  // Re-center the character in the view
  QList<QGraphicsView*> views = this->views();

  QPointF character_pos = d_character->pos();

  // There should only be a single view but just to be safe we will loop over
  // the entire list
  for( int i = 0; i < views.size(); ++i )
    views[i]->centerOn( character_pos.x()+320, character_pos.y()+110 );
    //views[i]->centerOn( d_character );
}

// Handle z value change
void Level::updateInteractiveLevelObjectZValue() 
{
  // Get the signal sender
  QObject* sender = QObject::sender();
  LevelObject* level_object_sender = dynamic_cast<LevelObject*>( sender );
  
  if( level_object_sender )
  {
    d_grid->updateLevelObjectZValue( level_object_sender );
    std::cout << "level object z value changed: " << d_character->zValue() << std::endl;
  }
}

// Handle mouse press events in a custom way
void Level::mousePressEvent( QGraphicsSceneMouseEvent* mouse_event )
{
  if( d_character )
  {
    //std::cout << "character z order: " << d_character->zValue() << std::endl;
    // Check if there is a level object where the mouse was pressed
    LevelObject* object = NULL;

    {
      QGraphicsItem* raw_object = this->itemAt( mouse_event->scenePos() );

      if( raw_object )
        object = dynamic_cast<LevelObject*>( raw_object );
    }

    if( object )
    {
      if( mouse_event->button() == Qt::LeftButton )
      {
        d_character->setTarget( object, mouse_event->scenePos() );
      }
      else if( mouse_event->button() == Qt::RightButton )
      {
        if( d_character->inTown() )
        {
          //d_character->playICantSound();
          std::cout << "can't cast a spell in town!" << std::endl;
        }
        else
          d_character->castSpellAt( object );
      }
    }
  }
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

// Connect character signals to level slots
void Level::connectCharacterSignalsToLevelSlots() const
{
  QObject::connect( d_character, SIGNAL(xChanged()),
                    this, SLOT(handleCharacterPositionChanged()) );
  QObject::connect( d_character, SIGNAL(yChanged()),
                    this, SLOT(handleCharacterPositionChanged()) );
}

// Connect character signals from level slots
void Level::disconnectCharacterSignalsFromLevelSlots() const
{
  QObject::disconnect( d_character, SIGNAL(xChanged()),
                       this, SLOT( handleCharacterPositionChanged()) );
  QObject::disconnect( d_character, SIGNAL(yChanged()),
                       this, SLOT( handleCharacterPositionChanged()) );
}

void Level::connectInteractiveLevelObjectSignalsToLevelSignals( LevelObject* level_object ) const
{
  QObject::connect( level_object, SIGNAL( hoveringStarted( QString ) ),
                    this, SIGNAL( interactiveLevelObjectHoveringStarted( QString ) ) );

  QObject::connect( level_object, SIGNAL( hoveringStopped( QString ) ),
                    this, SIGNAL( interactiveLevelObjectHoveringStopped( QString ) ) );

  QObject::connect( level_object, SIGNAL( yChanged() ),
                    this, SLOT( updateInteractiveLevelObjectZValue() ) );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Level.cpp
//---------------------------------------------------------------------------//
