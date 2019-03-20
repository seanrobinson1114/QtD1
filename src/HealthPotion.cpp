//---------------------------------------------------------------------------//
//!
//! \file   HealthPotion.cpp
//! \author Alex Robinson
//! \brief  The health potion class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "HealthPotion.h"

namespace QtD1{

// Initialize static member data
std::unique_ptr<QMap<State,GameSprite> > HealthPotion::s_state_game_sprites;

// Constructor
HealthPotion::HealthPotion( QGraphicsObject* parent )
  : ConsumableInteractiveLevelObject( parent ),
    d_sprites(),
    d_sprites_loaded( false )
{ /* ... */ }

// Check if the object is tradable
bool HealthPotion::isTradable() const
{
  return true;
}

// Check if the object can be placed in the belt
bool HealthPotion::canBePlacedInBelt() const
{
  return true;
}

// Get a description of the object when it is not owned
QString HealthPotion::getUnownedDescriptionText() const
{
  return "Potion of Healing"
}

// Get a processed description of the object when it is not owned
QPixmap HealthPotion::getUnownedDescription() const
{

}

// Get a description of the object when it is owned
QString HealthPotion::getOwnedDescriptionText() const
{
  return "Potion of Healing\nRecover Health\nRight Click To Use";
}

// Get a processed description of the object when it is not owned
QPixmap HealthPotion::getOwnedDescription() const
{

}

// Get a description of the object when shown in a trade menu
QString HealthPotion::getTradeMenuDescriptionText() const
{
  return "Potion of Healing\nNo Required Attributes";
}

// Get a processed description of the object when shown in a trade menu
QPixmap HealthPotion::getTradeMenuDescription() const
{

}

// Get the game cursor that is used when the object is clicked
CursorDatabase::GameCursor HealthPotion::getClickCursor() const
{
  return CursorDatabase::GameCursor::SmallHealthPostionGameCursor;
}

// Get the gold value of the object
int HealthPotion::getGoldValue() const
{
  return 50;
}

// Get the inventory image
QPixmap HealthPotion::getInventoryPixmap() const
{
  return CursorDatabase::getInstance()->getCursorPixmap( this->getClickCursor() );
}

// Clone the object
HealthPotion* HealthPotion::clone() const
{
  return new HealthPotion( *this );
}

// Consume the object (implementation)
void HealthPotion::consumeImpl()
{

}

// Get the number of image assets used by the object
int getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset name
QString getImageAssetName()
{
  return "/items/fbttle.cel+levels/towndata/town.pal";
}

// Get the image asset names used by the object
void getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( this->getImageAssetName() );
}

// Check if an image asset is used
bool isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == this->getImageAssetName();
}

// Check if the image assets have been loaded
bool imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the raw image asset
void loadRawImageAsset( const QString& image_asset_name,
                        const QVector<QImage>& image_asset_frames )
{
  if( !s_direction_game_sprites )
  {
    
  }
}

// Load the image asset
void loadImageAsset( const QString& image_asset_name,
                     const QVector<QPixmap>& image_asset_frames )
{
  qWarning( "HealthPotion Warning: Image assets should never be loaded this way!" );
}

// Finalize image asset loading
void finalizeImageAssetLoading()
{
  d_sprites.reset( new QMap<State,GameSprite>( *s_state_game_sprite ) );

  this->setSprites( d_sprites );
  
  d_sprites_loaded = true;
}
  
// Dump the image assets
void dumpImageAssets()
{
  if( s_direction_game_sprites )
    s_direction_game_sprites.reset();
  
  d_sprites_loaded = false;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end HealthPotion.cpp
//---------------------------------------------------------------------------//
