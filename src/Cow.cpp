//---------------------------------------------------------------------------//
//!
//! \file   Cow.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The cow class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Cow.h"

namespace QtD1{

// Initialize static member data
std::unique_ptr<QMap<Direction,GameSprite> Cow::s_direction_game_sprites;

// Constructor
Cow::Cow( const Direction direction,
          QGraphicsItem* parent )
  : InteractiveLevelObject( parent ),
    d_direction( direction ),
    d_sprites()
{ /* ... */ }

// Get a description of the object
QString Cow::getDescription() const
{

}

// Get the number of image assets used by the object
int Cow::getNumberOfImageAssets() const
{

}

// Get the image asset names used by the object
void Cow::getImageAssetNames( QSet<QString>& image_asset_names ) const
{

}

// Check if the image asset is used by the object
bool Cow::isImageAssetUsed( const QString& image_asset_name ) const
{

}

// Check if the image assets have been loaded
bool Cow::imageAssetsLoaded() const
{
  
}

// Load the raw image asset
void Cow::loadRawImageAsset( const QString& image_asset_name,
                             const QVector<QImage>& image_asset_frames )
{
  if( !s_direction_game_sprites )
  {
    s_direction_game_sprites.reset( new QMap<Direction,GameSprite> );
    
    // Pull out the sprite frames for each direction
  }
}

// Load the image asset
void Cow::loadImageAsset( const QString& image_asset_name,
                          const QVector<QPixmap>& image_asset_frames )
{
  qWarning( "Cow Warning: Image assets should never be loaded this way!" );
}

// Finalize image asset loading
void finalizeImageAssetLoading()
{
  d_sprites = s_direction_game_sprites[d_direction] );
}

// Dump the image assets
void dumpImageAssets()
{
  if( s_direction_game_sprites )
    s_direction_game_sprites.reset();

  d_sprites.dumpAsset();
}

// Check if the object can be attacked
bool canBeAttacked() const
{
  return false;
}

// Handle being targeted by another object
void Cow::handleBeingTargeted( LevelObject* object )
{
  if( object->isCharacter() )
  {
    emit targetedByCharacter( object );

    // Play a sound
  }
}

// The image asset name
QString Cow::getImageAssetName()
{
  return "/towners/animals/cow.cel+levels/towndata/town.pal"
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Cow.cpp
//---------------------------------------------------------------------------//
