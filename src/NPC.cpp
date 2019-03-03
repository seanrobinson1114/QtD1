//---------------------------------------------------------------------------//
//!
//! \file   NPC.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The NPC base class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "NPC.h"
#include "BasicActorStandingByTargetTransition.h"

namespace QtD1{

// Constructor
NPC::NPC( QGraphicsObject* parent,
          const bool has_walking_state )
  : BasicActor( parent ),
    d_has_walking_state( has_walking_state ),
    d_sprites(),
    d_active_state( Standing )
{ /* ... */ }

// Check if the object can be attacked
bool NPC::canBeAttacked() const
{
  return false;
}

// Handle being targeted by another object
void NPC::handleBeingTargeted( LevelObject* object )
{
  if( object->isCharacter() )
  {
    emit targetedByCharacter( object );

    this->greet();
  }
}

// Set the NPC sprites
void NPC::setNPCSprites(
                  const std::shared_ptr<StateDirectionGameSpriteMap>& sprites )
{
  if( sprites )
  {
    d_sprites = sprites;

    // There will always be a standing sprite
    if( d_sprites->find( d_active_state ) == d_sprites->end() )
      d_active_state = Standing;

    this->setActiveSprites( (*d_sprites)[d_active_state] );
  }
}

// Initialize the state machine
void NPC::initializeStateMachine( QStateMachine& state_machine )
{
  QState* parent_state = new QState;

  // Create the standing state
  QState* standing_state = new QState( parent_state );

  QState* walking_state;

  // Create the walking state
  if( d_has_walking_state )
  {
    walking_state = new QState( parent_state );

    standing_state->addTransition( this,
                                   SIGNAL(targetSet(LevelObject*,LevelObject*)),
                                   walking_state );

    QAbstractTransition* to_standing_state_transition =
      new BasicActorStandingByTargetTransition( this );
    to_standing_state_transition->setTargetState( standing_state );

    walking_state->addTransition( to_standing_state_transition );

    walking_state->addTransition( this,
                                  SIGNAL(targetedByCharacter(LevelObject*)),
                                  standing_state );
  }

  // Set the initial state
  parent_state->setInitialState( standing_state );

  // Connect state signals to NPC slots
  QObject::connect( standing_state, SIGNAL(entered()),
                    this, SLOT(handleStandingStateEntered()) );

  if( d_has_walking_state )
  {
    QObject::connect( walking_state, SIGNAL(entered()),
                      this, SLOT(handleWalkingStateEntered()) );
    QObject::connect( walking_state, SIGNAL(exited()),
                      this, SLOT(handleWalkingStateExited()) );
  }

  // Add states to the state machine
  state_machine.addState( parent_state );
  state_machine.setInitialState( parent_state );
}

// Handle standing state entered
void NPC::handleStandingStateEntered()
{
  std::cout << "npc standing state entered" << std::endl;
  d_active_state = Standing;

  this->setActiveSprites( (*d_sprites)[Standing] );

  this->update( this->boundingRect() );
}

// Handle walking state entered
void NPC::handleWalkingStateEntered()
{
  std::cout << "npc walking state entered" << std::endl;
  d_active_state = Walking;

  this->setActiveSprites( (*d_sprites)[Walking] );

  this->update( this->boundingRect() );
}

// Handle walking state exited
void NPC::handleWalkingStateExited()
{
  this->restartActiveSprite();
}

// Update the time dependent states
bool NPC::updateTimeDependentStates()
{
  return this->updateTimeDependentStatesImpl( false );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end NPC.cpp
//---------------------------------------------------------------------------//
