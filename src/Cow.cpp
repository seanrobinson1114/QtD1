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
std::unique_ptr<QMap<Direction,GameSprite> > Cow::s_direction_game_sprites;

// Constructor
Cow::Cow( const Direction direction,
          QGraphicsObject* parent )
  : InteractiveLevelObject( parent ),
    d_direction( direction ),
    d_sprites()
{
  this->setHoverOutlineColor( QColor::fromRgb(244, 66, 101) );
}

// Get the image asset names used by the object
void Cow::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  image_asset_names.insert( this->getImageAssetName() );
}

// Get a description of the object
QString Cow::getDescriptionText() const
{
  return QString( "Cow" );
}

// Get the direction
Direction Cow::getDirection() const
{
  return d_direction;
}

// Check if the image asset is used by the object
bool Cow::isImageAssetUsed( const QString& image_asset_name ) const
{
  return image_asset_name == this->getImageAssetName();
}

// Get the number of image assets used by the object
int Cow::getNumberOfImageAssets() const
{
  return 1;
}

// Check if the image assets have been loaded
bool Cow::imageAssetsLoaded() const
{
  return d_sprites.isReady();
}

// Load the raw image asset
void Cow::loadRawImageAsset( const QString& image_asset_name,
                             const QVector<QImage>& image_asset_frames )
{
  if( !s_direction_game_sprites )
  {
    s_direction_game_sprites.reset( new QMap<Direction,GameSprite> );
    
    // Pull out the sprite frames for each direction

    // South facing cow
    QVector<int> source_frame_indices( 12 );
    GameSprite& game_sprite_south = (*s_direction_game_sprites)[South];

    // This is a new game sprite - initialize it
    if( game_sprite_south.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
        source_frame_indices[i] = i;

      game_sprite_south = GameSprite( image_asset_name, source_frame_indices );
    }


    game_sprite_south.setAsset( image_asset_name, image_asset_frames );
    game_sprite_south.setFrameDuration( 15 );

    // Southwest facing cow
    GameSprite& game_sprite_southwest = (*s_direction_game_sprites)[Southwest];

    // This is a new game sprite - initialize it
    if( game_sprite_southwest.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
          source_frame_indices[i] = i+12;

      game_sprite_southwest = GameSprite( image_asset_name, source_frame_indices );
    }

    game_sprite_southwest.setAsset( image_asset_name, image_asset_frames );
    game_sprite_southwest.setFrameDuration( 15 );


    // West facing cow
    GameSprite& game_sprite_west = (*s_direction_game_sprites)[West];

    // This is a new game sprite - initialize it
    if( game_sprite_west.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
          source_frame_indices[i] = i+24;

      game_sprite_west = GameSprite( image_asset_name, source_frame_indices );
    }

    game_sprite_west.setAsset( image_asset_name, image_asset_frames );
    game_sprite_west.setFrameDuration( 15 );


    // Northwest facing cow
    GameSprite& game_sprite_northwest = (*s_direction_game_sprites)[Northwest];

    // This is a new game sprite - initialize it
    if( game_sprite_northwest.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
          source_frame_indices[i] = i+36;

      game_sprite_northwest = GameSprite( image_asset_name, source_frame_indices );
    }

    game_sprite_northwest.setAsset( image_asset_name, image_asset_frames );
    game_sprite_northwest.setFrameDuration( 15 );
    

    // North facing cow
    GameSprite& game_sprite_north = (*s_direction_game_sprites)[North];

    // This is a new game sprite - initialize it
    if( game_sprite_north.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
          source_frame_indices[i] = i+48;

      game_sprite_north = GameSprite( image_asset_name, source_frame_indices );
    }

    game_sprite_north.setAsset( image_asset_name, image_asset_frames );
    game_sprite_north.setFrameDuration( 15 );
    

    // Northeast facing cow
    GameSprite& game_sprite_northeast = (*s_direction_game_sprites)[Northeast];

    // This is a new game sprite - initialize it
    if( game_sprite_northeast.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
          source_frame_indices[i] = i+60;

      game_sprite_northeast = GameSprite( image_asset_name, source_frame_indices );
    }

    game_sprite_northeast.setAsset( image_asset_name, image_asset_frames );
    game_sprite_northeast.setFrameDuration( 15 );
    

    // East facing cow
    GameSprite& game_sprite_east = (*s_direction_game_sprites)[East];

    // This is a new game sprite - initialize it
    if( game_sprite_east.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
          source_frame_indices[i] = i+72;

      game_sprite_east = GameSprite( image_asset_name, source_frame_indices );
    }

    game_sprite_east.setAsset( image_asset_name, image_asset_frames );
    game_sprite_east.setFrameDuration( 15 );
    

    // Southeast facing cow
    GameSprite& game_sprite_southeast = (*s_direction_game_sprites)[Southeast];

    // This is a new game sprite - initialize it
    if( game_sprite_southeast.getNumberOfFrames() == 0 )
    {
      for( int i = 0; i < source_frame_indices.size(); ++i )
          source_frame_indices[i] = i+84;

      game_sprite_southeast = GameSprite( image_asset_name, source_frame_indices );
    }

    game_sprite_southeast.setAsset( image_asset_name, image_asset_frames );
    game_sprite_southeast.setFrameDuration( 15 );
  }
}

// Load the image asset
void Cow::loadImageAsset( const QString&,
                          const QVector<QPixmap>& )
{
  qWarning( "Cow Warning: Image assets should never be loaded this way!" );
}

// Finalize image asset loading
void Cow::finalizeImageAssetLoading()
{
  d_sprites = (*s_direction_game_sprites)[d_direction];
}

// Dump the image assets
void Cow::dumpImageAssets()
{
  if( s_direction_game_sprites )
    s_direction_game_sprites.reset();

  d_sprites.dumpAsset();
}

// Check if the object can be attacked
bool Cow::canBeAttacked() const
{
  return false;
}

// Get the bounding rect of the basic actor
QRectF Cow::boundingRect() const
{
  if( d_sprites.isReady() )
    return d_sprites.boundingRect();
  else
    return QRectF();
}

// Get the shape of the basic actor
QPainterPath Cow::shape() const
{
  if( d_sprites.isReady() )
    return d_sprites.shape();
  else
    return QPainterPath();
}

// Advance the basic actor state (if time dependent)
void Cow::advance( int phase )
{
  // Phase 0: about to advance
  // Phase 1: advancing
  if( phase == 1 )
  {
    if( d_sprites.isReady() )
    {
      bool screen_update_required =
        d_sprites.incrementElapsedGameTics();

      if( screen_update_required )
      {
        // Only request a screen update if it is necessary
        this->update( d_sprites.boundingRect() );
      }
    }
    else
      std::cout << "An empty sprite sheet was found!" << std::endl;
  }
}

// The paint implementation
void Cow::paintImpl( QPainter* painter,
                        const QStyleOptionGraphicsItem* option,
                        QWidget* widget )
{
  if( d_sprites.isReady() )
    d_sprites.paint( painter, option, widget );
  else
    std::cout << "empty sprite sheet detected!" << std::endl;
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
  return "/towners/animals/cow.cel+levels/towndata/town.pal";
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Cow.cpp
//---------------------------------------------------------------------------//
