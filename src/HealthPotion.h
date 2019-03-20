//---------------------------------------------------------------------------//
//!
//! \file   HealthPotion.h
//! \author Alex Robinson
//! \brief  The health potion class declaration
//!
//---------------------------------------------------------------------------//

#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

// QtD1 Includes
#include "ConsumableInteractiveLevelObject.h"

namespace QtD1{

//! The health potion
class HealthPotion : public ConsumableInteractiveLevelObject
{
  Q_OBJECT

public:

  //! Constructor
  HealthPotion( QGraphicsObject* parent = 0 );

  //! Destructor
  ~HealthPotion()
  { /* ... */ }

  //! Check if the object is tradable
  bool isTradable() const final override;

  //! Check if the object can be placed in the belt
  bool canBePlacedInBelt() const final override;

  //! Get a description of the object when it is not owned
  QString getUnownedDescriptionText() const final override;

  //! Get a processed description of the object when it is not owned
  QPixmap getUnownedDescription() const final override;

  //! Get a description of the object when it is owned
  QString getOwnedDescriptionText() const final override;

  //! Get a processed description of the object when it is not owned
  QPixmap getOwnedDescription() const final override;

  //! Get a description of the object when shown in a trade menu
  QString getTradeMenuDescriptionText() const final override;

  //! Get a processed description of the object when shown in a trade menu
  QPixmap getTradeMenuDescription() const final override;

  //! Get the game cursor that is used when the object is clicked
  CursorDatabase::GameCursor getClickCursor() const final override;

  //! Get the gold value of the object
  int getGoldValue() const final override;

  //! Get the inventory image
  QPixmap getInventoryPixmap() const final override;

  //! Clone the object
  HealthPotion* clone() const final override;

protected:

  //! Consume the object (implementation)
  void consumeImpl() final override;

  //! Get the number of image assets used by the object
  int getNumberOfImageAssets() const final override;

  //! Get the image asset names used by the object
  void getImageAssetNames( QSet<QString>& image_asset_names ) const final override;

  //! Check if an image asset is used
  bool isImageAssetUsed( const QString& image_asset_name ) const final override;

  //! Check if the image assets have been loaded
  bool imageAssetsLoaded() const final override;

  //! Load the raw image asset
  void loadRawImageAsset( const QString& image_asset_name,
                          const QVector<QImage>& image_asset_frames ) final override;
  
  //! Load the image asset
  void loadImageAsset( const QString& image_asset_name,
                       const QVector<QPixmap>& image_asset_frames ) final override;

  //! Finalize image asset loading
  void finalizeImageAssetLoading() final override;
  
  //! Dump the image assets
  void dumpImageAssets() final override;

private:

  // Get the image asset name
  static QString getImageAssetName();

  // The health potion state game sprite map
  static std::unique_ptr<QMap<State,GameSprite> > s_state_game_sprites;

  // The state game sprites
  std::shared_ptr<StateGameSpriteMap> d_sprites;

  // Record if the image assets have been loaded
  bool d_sprites_loaded;
};
  
} // end QtD1 namespace

#endif // end HEALTH_POTION_H

//---------------------------------------------------------------------------//
// end HealthPotion.h
//---------------------------------------------------------------------------//
