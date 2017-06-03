//---------------------------------------------------------------------------//
//!
//! \file   BasicActor.cpp
//! \author Alex Robinson
//! \brief  The basic actor base class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "BasicActor.h"

namespace QtD1{

// Constructor
BasicActor::BasicActor( QGraphicsObject* parent )
  : InteractiveLevelObject( parent ),
    d_active_sprites(),
    d_active_direction_sprite( std::make_pair( South, (GameSprite*)0 ) ),
    d_state_machine()
{ /* ... */ }

// Set the direction of the basic actor
void BasicActor::setDirection( const Direction direction )
{
  if( direction != d_active_direction_sprite.first )
  {
    d_active_direction_sprite.first = direction;
    d_active_direction_sprite.second = &(*d_active_sprites)[direction];
  }
}

// Get the direction of the basic actor
Direction BasicActor::getDirection() const
{
  return d_active_direction_sprite.first;
}

// Get the bounding rect of the basic actor
QRectF BasicActor::boundingRect() const
{
  if( d_active_direction_sprite.second )
    return d_active_direction_sprite.second->boundingRect();
  else
    return QRectF();
}

// Get the shape of the basic actor
QPainterPath BasicActor::shape() const
{
  if( d_active_direction_sprite.second )
    return d_active_direction_sprite.second->shape();
  else
    return QPainterPath();
}

// Advance the basic actor state (if time dependent)
void BasicActor::advance( int phase )
{
  // Phase 0: about to advance
  // Phase 1: advancing
  if( phase == 1 )
  {
    if( d_active_direction_sprite.second )
    {
      bool screen_update_required = 
        d_active_direction_sprite.second->incrementElapsedGameTics();

      if( screen_update_required )
      {
        if( d_active_direction_sprite.second->getFrame() == 0 )
          emit allActiveFramesShown();
        
        // Only update time dependent states when the sprite frame changes
        this->updateTimeDependentStates();

        // Only request a screen update if it is necessary
        this->update( d_active_direction_sprite.second->boundingRect() );
      }
    }    
  }
}

// Paint the actor
void BasicActor::paintImpl( QPainter* painter,
                            const QStyleOptionGraphicsItem* option,
                            QWidget* widget )
{
  if( d_active_direction_sprite.second )
  {
    d_active_direction_sprite.second->paint( painter, option, widget );
  }
}

// Start the actor state machine
void BasicActor::startStateMachine()
{
  bool needs_start = false;
  
  if( !d_state_machine )
  {
    d_state_machine.reset( new QStateMachine( this ) );
    
    needs_start = true;
  }
  else if( !d_state_machine->isRunning() )
  {
    d_state_machine.reset( new QStateMachine( this ) );

    needs_start = true;
  }

  if( needs_start )
  {
    this->initializeStateMachine( *d_state_machine );
    d_state_machine->start();
  }
}

// Set the active sprites
void BasicActor::setActiveSprites(
                const std::shared_ptr<DirectionGameSpriteMap>& active_sprites )
{
  if( active_sprites )
  {
    d_active_sprites = active_sprites;

    d_active_direction_sprite.second =
      &(*d_active_sprites)[d_active_direction_sprite.first];
  }
}

// Restart active sprite
void BasicActor::restartActiveSprite()
{
  if( d_active_direction_sprite.second )
    d_active_direction_sprite.second->setFrame( 0 );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end BasicActor.cpp
//---------------------------------------------------------------------------//
