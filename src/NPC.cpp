//---------------------------------------------------------------------------//
//!
//! \file   NPC.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The NPC base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include <QPushButton>

// QtD1 Includes
#include "NPC.h"
#include "NPCInteractionMenu.h"
#include "BasicActorStandingByTargetTransition.h"
#include "QuestManager.h"

namespace QtD1{

// Constructor
NPC::NPC( QGraphicsObject* parent,
          const bool has_walking_state )
  : BasicActor( parent ),
    d_has_walking_state( has_walking_state ),
    d_sprites(),
    d_active_state( Standing ),
    d_interaction_menu( NULL )
{ 
  // Connect the QuestManager signals to the NPC slots
  QObject::connect( &QuestManager::getInstance(), SIGNAL( questActivated(const Quest::Type) ),
                    this, SLOT(activateQuest(const Quest::Type)) );
  QObject::connect( &QuestManager::getInstance(), SIGNAL( questFinished(const Quest::Type) ),
                    this, SLOT(deactivateQuest(const Quest::Type)) );
}

// Check if the object can be attacked
bool NPC::canBeAttacked() const
{
  return false;
}

// Activate a quest
void NPC::activateQuest( const Quest::Type quest )
{
  
}

// Deactivate a quest
void NPC::deactivateQuest( const Quest::Type quest )
{

}

// Stop playing dialogue
void NPC::stopTalking()
{
  
}

// Show interaction menu
void NPC::showInteractionMenu()
{
  emit interactionMenuActivated();
  
  d_interaction_menu->show();
  d_interaction_menu->raise();
  d_interaction_menu->setFocus();
}

// Hide the interaction menu
void NPC::hideInteractionMenu()
{
  this->stopTalking();
    
  d_interaction_menu->hide();
  d_interaction_menu->clearFocus();

  emit interactionMenuDeactivated();
}

// Handle being targeted by another object
void NPC::handleBeingTargeted( LevelObject* object )
{
  if( object->isCharacter() )
  {
    emit targetedByCharacter( object );

    this->greet();

    this->showInteractionMenu();
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

// Load the interaction menu
void NPC::loadInteractionMenu( QWidget* parent )
{
  // Only load the menu once
  if( !d_interaction_menu )
  {
    d_interaction_menu = new NPCInteractionMenu( "Farnham",
                                                 "Farnham The Drunk",
                                                 "Say Goodbye",
                                                 parent );

    QObject::connect( d_interaction_menu, SIGNAL(exit()),
                      this, SLOT(hideInteractionMenu()) );
    QObject::connect( d_interaction_menu, SIGNAL(gossip()),
                      this, SLOT(gossip()) );
    QObject::connect( d_interaction_menu, SIGNAL(discussQuest(const Quest::Type)),
                      this, SLOT(discussQuest(const Quest::Type)) );
  }
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
