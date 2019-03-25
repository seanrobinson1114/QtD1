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
std::unique_ptr<QMap<HealthPotion::State,GameSprite> > HealthPotion::s_state_game_sprites;
std::unique_ptr<QPixmap> HealthPotion::s_unowned_description_text;
std::unique_ptr<QPixmap> HealthPotion::s_owned_description_text;
std::unique_ptr<QPixmap> HealthPotion::s_trade_menu_description_text;

// Constructor
HealthPotion::HealthPotion( QGraphicsObject* parent )
  : Potion( parent ),
    d_sprites(),
    d_sprites_loaded( false )
{ 
  if( s_state_game_sprites )
    this->finalizeImageAssetLoading();
}

// Copy constructor
HealthPotion::HealthPotion( const HealthPotion& other )
  : Potion( other ),
    d_sprites( other.d_sprites ),
    d_sprites_loaded( other.d_sprites_loaded )
{
  if( d_sprites_loaded )
    this->setSprites( d_sprites );

  if( other.isStateMachineRunning() )
    this->startStateMachine();
}

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
  return "Potion of Healing";
}

// Get a processed description of the object when it is not owned
QPixmap HealthPotion::getUnownedDescription() const
{
  if( !s_unowned_description_text )
  {
    s_unowned_description_text.reset( new QPixmap );
    *s_unowned_description_text =
      this->processDescriptionText( this->getUnownedDescriptionText(),
                                    "QtD1White11",
                                    false,
                                    false );
  }

  return *s_unowned_description_text;
}

// Get a description of the object when it is owned
QString HealthPotion::getOwnedDescriptionText() const
{
  return "Potion of Healing\nRecover Health\nRight Click To Use";
}

// Get a processed description of the object when it is not owned
QPixmap HealthPotion::getOwnedDescription() const
{
  if( !s_owned_description_text )
  {
    s_owned_description_text.reset( new QPixmap );
    *s_owned_description_text =
      this->processDescriptionText( this->getOwnedDescriptionText(),
                                    "QtD1White11",
                                    true,
                                    false );
  }

  return *s_owned_description_text;
}

// Get a description of the object when shown in a trade menu
QString HealthPotion::getTradeMenuDescriptionText() const
{
  return "Potion of Healing\nNo Required Attributes";
}

// Get a processed description of the object when shown in a trade menu
QPixmap HealthPotion::getTradeMenuDescription() const
{
  if( !s_trade_menu_description_text )
  {
    s_trade_menu_description_text.reset( new QPixmap );
    *s_trade_menu_description_text =
      this->processDescriptionText( this->getTradeMenuDescriptionText(),
                                    "QtD1White11",
                                    false,
                                    true );
  }

  return *s_trade_menu_description_text;
}

// Get the game cursor that is used when the object is clicked
Cursor::GameCursor HealthPotion::getClickCursor() const
{
  return Cursor::GameCursor::SmallHealthPostionGameCursor;
}

// Get the gold value of the object
int HealthPotion::getGoldValue() const
{
  return 50;
}

// Get the inventory image
QPixmap HealthPotion::getInventoryPixmap() const
{
  return Cursor::getInstance()->getCursorPixmap( this->getClickCursor() );
}

// Clone the object
HealthPotion* HealthPotion::clone() const
{
  return new HealthPotion( *this );
}

// Consume the object (implementation)
void HealthPotion::consumeImpl()
{
  Character* owner = this->getOwner();

  if( owner )
    owner->addHealth( 20 );
}

// Get the number of image assets used by the object
int HealthPotion::getNumberOfImageAssets() const
{
  return 1;
}

// Get the image asset name
QString HealthPotion::getImageAssetName()
{
  return "/items/fbttle.cel+levels/towndata/town.pal";
}

// Get the image asset names used by the object
void HealthPotion::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( this->getImageAssetName() );
}

// Check if an image asset is used
bool HealthPotion::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == this->getImageAssetName();
}

// Check if the image assets have been loaded
bool HealthPotion::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the raw image asset
void HealthPotion::loadRawImageAsset( const QString& image_asset_name,
                                      const QVector<QImage>& image_asset_frames )
{
  if( !s_state_game_sprites )
  {
    s_state_game_sprites.reset( new QMap<State,GameSprite> );

    // Pull out the slipping game sprites
    QVector<int> source_frame_indices( 8 );
    GameSprite& flipping_game_sprite = (*s_state_game_sprites)[Flipping];

    // This is a new game sprite - initialize it
    if( flipping_game_sprite.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
        source_frame_indices[i] = i + 8;

      flipping_game_sprite = GameSprite( image_asset_name, source_frame_indices );
    }

    flipping_game_sprite.setAsset( image_asset_name, image_asset_frames );
    flipping_game_sprite.setFrameDuration( 15 );

    // Pull out the on floor game sprite
    GameSprite& on_floor_game_sprite = (*s_state_game_sprites)[OnFloor];

    if( on_floor_game_sprite.getNumberOfFrames() == 0 )
    {
      source_frame_indices.resize( 1 );
      source_frame_indices[0] = 0;

      on_floor_game_sprite = GameSprite( image_asset_name, source_frame_indices );
      on_floor_game_sprite.setAsset( image_asset_name, image_asset_frames );
      on_floor_game_sprite.setFrameDuration( 15 );
    }
  }
}

// Load the image asset
void HealthPotion::loadImageAsset( const QString& image_asset_name,
                                   const QVector<QPixmap>& image_asset_frames )
{
  qWarning( "HealthPotion Warning: Image assets should never be loaded this way!" );
}

// Finalize image asset loading
void HealthPotion::finalizeImageAssetLoading()
{
  d_sprites.reset( new QMap<State,GameSprite>( *s_state_game_sprites ) );

  this->setSprites( d_sprites );
  
  d_sprites_loaded = true;
}
  
// Dump the image assets
void HealthPotion::dumpImageAssets()
{
  if( s_state_game_sprites )
    s_state_game_sprites.reset();
  
  d_sprites_loaded = false;
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end HealthPotion.cpp
//---------------------------------------------------------------------------//
