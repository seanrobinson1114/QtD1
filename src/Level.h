//---------------------------------------------------------------------------//
//!
//! \file   Level.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The level base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef LEVEL_H
#define LEVEL_H

// Qt Includes
#include <QGraphicsScene>
#include <QList>
#include <QFuture>
#include <QFutureWatcher>

// QtD1 Includes
#include "LevelObject.h"
#include "LevelPillar.h"
#include "LevelSector.h"
#include "ImageAssetLoader.h"
#include "Character.h"
#include "Music.h"
#include "Grid.h"

namespace QtD1{

//! The level base class declaration
class Level : public QGraphicsScene
{
  Q_OBJECT

public:

  //! The level types
  enum Type{
    Town = 0,
    Cathedral,
    SkeletonKingLair,
    Catacomb,
    Cave,
    Hell,
    LazarusLair,
    DiabloLair
  };

  //! Destructor
  virtual ~Level()
  { /* ... */ }

  //! Get the type
  virtual Type getType() const = 0;

  //! Get the number
  virtual int getNumber() const = 0;

  //! Get the image asset name
  virtual QString getImageAssetName() const = 0;

  //! Create the level background
  void createBackground();

  //! Add a level object
  void addLevelObject( LevelObject* level_object, const QPointF& location );

  //! Add an actor
  void addActor( Actor* actor,
                 const QPointF& location,
                 const Direction direction = South );

  //! Insert the character
  virtual void insertCharacter( Character* character,
                                const QPointF& location,
                                const Direction direction );

  //! Remove the character
  virtual void removeCharacter();

  //! Create the grid
  void initializeGrid( int, int, QList<LevelPillar*> );

  //! Get the character
  Character* getCharacter();

  //! Check if the level image assets need to be restored
  bool needsRestore();

  //! Check if the level is ready
  bool isReady();

signals:

  //! Asset loading started
  void assetLoadingStarted( const int number_of_assets );

  //! Asset loaded
  void assetLoaded( const int number_of_assets_loaded );

  //! Asset loading finished
  void assetLoadingFinished( const int number_of_assets_loaded );

  //! Interactive object is being hovered on
  void interactiveLevelObjectHoveringStarted( QString object_description );

  //! Interactive level object is no longer being hovered on
  void interactiveLevelObjectHoveringStopped( QString empty_string );

public slots:

  //! Load the level image assets
  void loadImageAssets();

  //! Load the level image assets synchronously
  void loadImageAssetsSync();

  //! Dump the level image assets
  void dumpImageAssets();

  //! Restore the level image assets
  void restoreImageAssets();

  //! Restore the image assets synchronously
  void restoreImageAssetsSync();

  //! Play the level music
  void playLevelMusic();

  //! Pause the level music
  void pauseLevelMusic();

  //! Stop the level music
  void stopLevelMusic();

protected:

  //! Constructor
  Level( QObject* parent = 0 );

  //! Constructor
  Level( QObject* parent, const QString& level_music_file_name );

  //! Set the music
  void setMusic( const std::shared_ptr<Music>& music );

  //! Set the grid
  void setGrid( const std::shared_ptr<Grid>& grid );

  //! Create the level sectors
  virtual void createSectors( QList<LevelSector*>& sectors ) = 0;

  // Connect interactiveLevelObject signals to Level signals
  void connectInteractiveLevelObjectSignalsToLevelSignals( LevelObject* level_object ) const;

private slots:

  // Handle image asset loading started
  void handleImageAssetLoadingStarted( const int number_of_assets );

  // Handle image asset loaded
  void handleImageAssetLoaded( const int number_of_assets_loaded,
                               const QString asset_name,
                               const QVector<QImage> asset );

  // Handle image asset loading finished
  void handleImageAssetLoadingFinished( const int number_of_assets_loaded );

  // Handle character position changed
  void handleCharacterPositionChanged();

  // Handle z value change
  void updateInteractiveLevelObjectZValue();

private:

  // Reset the asset data
  void resetAssetData();

  // Gather image assets to load
  void gatherImageAssetsToLoad( QSet<QString>& assets_to_load );

  // Assign the level object to the asset name
  void assignLevelObjectToAssetNames( const QSet<QString>& asset_name,
                                      LevelObject* object );

  // Notify level objects of impending asset load
  void notifyLevelObjectsOfImpendingAssetLoad();

  // Handle mouse press events in a custom way
  void mousePressEvent( QGraphicsSceneMouseEvent* mouse_event ) override;

  // Connect the image asset loader signals to the level slots
  void connectImageAssetLoaderSignalsToLevelSlots() const;

  // Connect character signals to level slots
  void connectCharacterSignalsToLevelSlots() const;

  // Disconnect character signals from level slots
  void disconnectCharacterSignalsFromLevelSlots() const;

  // The character
  Character* d_character;

  // The level objects (externally added)
  QList<LevelObject*> d_level_objects;

  // The level sectors
  QList<LevelSector*> d_level_sectors;

  // The level object asset map (all objects)
  QMap<QString,QList<LevelObject*> > d_level_object_asset_map;

  // The level music
  std::shared_ptr<Music> d_music;

  // The image asset loader
  std::unique_ptr<ImageAssetLoader> d_image_asset_loader;

  // Records if the image assets need to be restored
  bool d_needs_restore;

  // Records if the image assets are ready
  bool d_ready;

  // the grid used for pathfinding
  std::shared_ptr<Grid> d_grid;
};

} // end QtD1 namespace

#endif // end LEVEL_H

//---------------------------------------------------------------------------//
// end Level.h
//---------------------------------------------------------------------------//
