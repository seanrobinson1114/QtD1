//---------------------------------------------------------------------------//
//!
//! \file   GrabbableInteractiveLevelObject.cpp
//! \author Alex Robinson
//! \brief  The grabbable interactive level object class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "GrabbableInteractiveLevelObject.h"

namespace QtD1{

// Constructor
GrabbableInteractiveLevelObject::GrabbableInteractiveLevelObject( QGraphicsObject* parent )
  : InteractiveLevelObject( parent ),
    d_owner( NULL ),
    d_sprites(),
    d_active_sprite( NULL ),
    d_state_machine()
{ /* ... */ }

// Check if the object is owned
bool GrabbableInteractiveLevelObject::isOwned() const
{
  return d_owner != NULL;
}

// Get a processed description of the object when it is not owned
QPixmap GrabbableInteractiveLevelObject::getUnownedDescription() const
{
  return this->processDescriptionText( this->getUnownedDescriptionText(),
                                       "QtD1White11",
                                       true,
                                       false );
}

// Get a processed description of the object when it is not owned
QPixmap GrabbableInteractiveLevelObject::getOwnedDescription() const
{
  return this->processDescriptionText( this->getOwnedDescriptionText(),
                                       "QtD1White11",
                                       true,
                                       false );
}

// Get a processed description of the object when shown in a trade menu
QPixmap GrabbableInteractiveLevelObject::getTradeMenuDescription() const
{
  return this->processDescriptionText( this->getTradeMenuDescriptionText(),
                                       "QtD1White11",
                                       false,
                                       true );
}

// Get a description of the object
QString GrabbableInteractiveLevelObject::getDescriptionText() const
{
  if( this->isOwned() )
    return this->getOwnedDescriptionText();
  else
    return this->getUnownedDescriptionText();
}

// Get a processed description of the object
QPixmap GrabbableInteractiveLevelObject::getDescription() const
{
  if( this->isOwned() )
    return this->getOwnedDescription();
  else
    return this->getUnownedDescription();
}

// Get the bounding rect of the basic actor
QRectF GrabbableInteractiveLevelObject::boundingRect() const
{
  if( d_active_sprite )
    return d_active_sprite->boundingRect();
  else
    return QRectF();
}

// Get the shape of the basic actor
QPainterPath GrabbableInteractiveLevelObject::shape() const
{
  if( d_active_sprite )
    return d_active_sprite->shape();
  else
    return QPainterPath();
}

// Advance the basic actor state (if time dependent)
void GrabbableInteractiveLevelObject::advance( int phase )
{
  // Phase 0: about to advance
  // Phase 1: advancing
  if( phase == 1 )
  {
    if( d_active_sprite )
    {
      bool screen_update_required =
        d_active_sprite->incrementElapsedGameTics();

      if( screen_updated_required )
      {
        if( d_active_sprite->getFrame() == 0 )
          emit allActiveFramesShown();

        // Only request a screen update if it is necessary
        this->update( d_active_sprite->boundingRect() );
      }
    }
    else
      std::cout << "An empty sprite sheet was found!" << std::endl;
  }
}

// Start the actor state machine
void GrabbableInteractiveLevelObject::startStateMachine()
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
    // Set up the state machine here
    QState* parent_state = new QState;

    // Create the on floor state
    QState* on_floor_state = new QState( parent_state );

    // Create the flipping state
    QState* flipping_state = new QState( parent_state );

    // Set the state transitions
    on_floor_state->addTransition( this,
                                   SIGNAL(noCurrentOwner()),
                                   flipping_state );

    flipping_state->addTransition( this,
                                   SIGNAL(allActiveFramesShown()),
                                   on_floor_state );

    parent_state->addInitialState( on_floor_state );

    // Connect the state signals to grabbable object slots
    QObject::connect( on_floor_state, SIGNAL(entered()),
                      this, SLOT(handleOnFloorStateEntered()) );
    QObject::connect( flipping_state, SIGNAL(entered()),
                      this, SLOT(handleFlippingStateEntered()) );
    QObject::connect( flipping_state, SIGNAL(exited()),
                      this, SLOT(handleFlippingStateExited()) );

    // Add the states to the state machines
    d_state_machine->addSate( parent_state );
    d_state_machine->setInitialState( parent_state );
    
    d_state_machine->start();
  }
}

// Set the sprites
void GrabbableInteractiveLevelObject::setSprites( const std::shared_ptr<StateGameSpriteMap>& sprites )
{
  if( sprites )
  {
    d_sprites = sprites;

    d_active_sprite = &(*d_sprites)[OnFloor];
  }
}

// The paint implementation
void GrabbableInteractiveLevelObject::paintImpl( QPainter* painter,
                                                 const QStyleOptionGraphicsItem* option,
                                                 QWidget* widget )
{
  if( d_active_sprite )
    d_active_sprite->paint( painter, option, widget );
  else
    std::cout << "empty sprite sheet detected!" << std::endl;
}

// Set the owner
void GrabbableInteractiveLevelObject::setOwner( Character* character )
{
  d_owner = character;
}

// Set as unowned
void GrabbableInteractiveLevelObject::setAsUnowned()
{
  d_owner = NULL;

  emit noCurrentOwner();
}

// Identify the object
void GrabbableInteractiveLevelObject::identify()
{ /* ... */ }

// Handler being targeted by another object
void GrabbableInteractiveLevelObject::handleBeingTargeted( LevelObject* targeter )
{

}

// Handle standing state entered
void GrabbableInteractiveLevelObject::handleOnFloorStateEntered()
{
  d_active_sprite = &(d_active_sprite)[OnFloor];

  this->update( this->boundingRect() );
}

// Handle walking state entered
void GrabbableInteractiveLevelObject::handleFlippingStateEntered()
{
  d_active_sprite = &(d_active_sprite)[Flipping];

  this->update( this->boundingRect() );
}

// Handle walking state exited
void GrabbableInteractiveLevelObject::handleFlippingStateExited()
{
  if( d_active_sprite )
    d_active_sprite->setFrame( 0 );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end GrabbableInteractiveLevelObject.cpp
//---------------------------------------------------------------------------//
