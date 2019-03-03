//---------------------------------------------------------------------------//
//!
//! \file   Actor.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The actor base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// Qt Includes
#include <QFinalState>

// QtD1 Includes
#include "Actor.h"
#include "BasicActorStandingByTargetTransition.h"
#include "ActorAttackingTargetTransition.h"

namespace QtD1{

// Constructor
Actor::Actor( QGraphicsObject* parent )
  : BasicActor( parent ),
    d_level( 1 ),
    d_kill_experience( 0 ),
    d_base_strength( 0 ),
    d_base_magic( 0 ),
    d_base_dexterity( 0 ),
    d_base_vitality( 0 ),
    d_health( 1 ),
    d_mana( 1 ),
    d_base_magic_resistance_fraction( 0.0 ),
    d_base_fire_resistance_fraction( 0.0 ),
    d_base_lightning_resistance_fraction( 0.0 ),
    d_sprites(),
    d_active_state( Standing )
{ /* ... */ }

// Copy constructor
/*! \details The sprites will not be copied.
 */
Actor::Actor( const Actor& other_actor )
  : BasicActor( other_actor ),
    d_level( other_actor.d_level ),
    d_kill_experience( other_actor.d_kill_experience ),
    d_base_strength( other_actor.d_base_strength ),
    d_base_magic( other_actor.d_base_magic ),
    d_base_dexterity( other_actor.d_base_dexterity ),
    d_base_vitality( other_actor.d_base_vitality ),
    d_health( other_actor.d_health ),
    d_mana( other_actor.d_mana ),
    d_base_magic_resistance_fraction( other_actor.d_base_magic_resistance_fraction ),
    d_base_fire_resistance_fraction( other_actor.d_base_fire_resistance_fraction ),
    d_base_lightning_resistance_fraction( other_actor.d_base_lightning_resistance_fraction ),
    d_sprites(),
    d_active_state( Standing )
{ /* ... */ }

// Assignment operator
/*! \details The sprites will not be copied.
 */
Actor& Actor::operator=( const Actor& other_actor )
{
  if( this != &other_actor )
  {
    BasicActor::operator=( other_actor );
    
    d_level = other_actor.d_level;
    d_kill_experience = other_actor.d_kill_experience;
    d_base_strength = other_actor.d_base_strength;
    d_base_magic = other_actor.d_base_magic;
    d_base_dexterity = other_actor.d_base_dexterity;
    d_base_vitality = other_actor.d_base_vitality;
    d_health = other_actor.d_health;
    d_mana = other_actor.d_mana;
    d_base_magic_resistance_fraction = other_actor.d_base_magic_resistance_fraction;
    d_base_fire_resistance_fraction = other_actor.d_base_fire_resistance_fraction;
    d_base_lightning_resistance_fraction = other_actor.d_base_lightning_resistance_fraction;
    d_sprites.reset();
    d_active_state = Standing;
  }

  return *this;
}

// Set the level
void Actor::setLevel( const int level )
{
  d_level = std::max( level, 1 );
}

// Get the level
int Actor::getLevel() const
{
  return d_level;
}

// Set the kill experience
void Actor::setKillExperience( const int kill_experience )
{
  d_kill_experience = std::max( kill_experience, 0 );
}

// Get the kill experience
int Actor::getKillExperience() const
{
  return d_kill_experience;
}

// Set the base strength
void Actor::setBaseStrength( const int strength )
{
  d_base_strength = std::max( strength, 0 );
}

// Get the base strength
int Actor::getBaseStrength() const
{
  return d_base_strength;
}

// Get the strength
int Actor::getStrength() const
{
  return d_base_strength;
}

// Set the base magic
void Actor::setBaseMagic( const int magic )
{
  d_base_magic = std::max( magic, 0 );
}

// Get the base magic
int Actor::getBaseMagic() const
{
  return d_base_magic;
}

// Get the magic
int Actor::getMagic() const
{
  return d_base_magic;
}

// Set the base dexterity
void Actor::setBaseDexterity( const int dexterity )
{
  d_base_dexterity = std::max( dexterity, 0 );
}

// Get the base dexterity
int Actor::getBaseDexterity() const
{
  return d_base_dexterity;
}

// Get the dexterity
int Actor::getDexterity() const
{
  return d_base_dexterity;
}

// Set the base vitality
void Actor::setBaseVitality( const int vitality )
{
  d_base_vitality = std::max( vitality, 0 );
}

// Get the base vitality
int Actor::getBaseVitality() const
{
  return d_base_vitality;
}

// Get the vitality
int Actor::getVitality() const
{
  return this->getBaseVitality();
}

// Get the base health
int Actor::getBaseHealth() const
{
  return 1;
}

// Get the max health
int Actor::getMaxHealth() const
{
  return this->getBaseHealth();
}

// Set the health
void Actor::setHealth( const int health )
{
  if( d_health != health )
  {
    if( health <= 0 )
      d_health = 0;
    else
      d_health = std::min( health, this->getMaxHealth() );

    emit healthChanged( d_health );

    if( d_health == 0 )
      emit healthDepleted();
  }
}

// Add health
void Actor::addHealth( const int health )
{
  if( health > 0 )
    this->setHealth( this->getHealth() + health );
}

// Remove health
void Actor::removeHealth( const int health )
{
  if( health > 0 )
    this->setHealth( this->getHealth() - health );
}

// Restore health
void Actor::restoreHealth()
{
  this->setHealth( this->getMaxHealth() );
}

// Get the health
int Actor::getHealth() const
{
  return d_health;
}

// Get the base mana
int Actor::getBaseMana() const
{
  return 1;
}

// Get the max mana
int Actor::getMaxMana() const
{
  return this->getBaseMana();
}

// Set the mana
void Actor::setMana( const int mana )
{
  if( d_mana != mana )
  {
    if( mana <= 0 )
      d_mana = 0;
    else
      d_mana = std::min( mana, this->getMaxMana() );

    emit manaChanged( d_mana );
  }
}

// Add mana
void Actor::addMana( const int mana )
{
  if( mana > 0 )
    this->setMana( this->getMana() + mana );
}

// Remove mana
void Actor::removeMana( const int mana )
{
  if( mana > 0 )
    this->setMana( this->getMana() - mana );
}

// Restore mana
void Actor::restoreMana()
{
  this->setMana( this->getMaxMana() );
}

// Get the mana
int Actor::getMana() const
{
  return d_mana;
}

// Set the base magic resistance
void Actor::setBaseMagicResistance( const qreal resist_fraction )
{
  if( resist_fraction > 0.0 )
    d_base_magic_resistance_fraction = std::min( resist_fraction, 1.0 );
  else
    d_base_magic_resistance_fraction = 0.0;
}

// Get the base magic resistance
qreal Actor::getBaseMagicResistance() const
{
  return d_base_magic_resistance_fraction;
}

// Get the magic resistance
qreal Actor::getMagicResistance() const
{
  return d_base_magic_resistance_fraction;
}

// Set the base fire resistance
void Actor::setBaseFireResistance( const qreal resist_fraction )
{
  if( resist_fraction > 0.0 )
    d_base_fire_resistance_fraction = std::min( resist_fraction, 1.0 );
  else
    d_base_fire_resistance_fraction = 0.0;
}

// Get the base fire resistance
qreal Actor::getBaseFireResistance() const
{
  return d_base_fire_resistance_fraction;
}

// Get the fire resistance
qreal Actor::getFireResistance() const
{
  return d_base_fire_resistance_fraction;
}

// Set the base lightning resistance
void Actor::setBaseLightningResistance( const qreal resist_fraction )
{
  if( resist_fraction > 0.0 )
    d_base_lightning_resistance_fraction = std::min( resist_fraction, 1.0 );
  else
    d_base_lightning_resistance_fraction = 0.0;
}

// Get the base lightning resistance
qreal Actor::getBaseLightningResistance() const
{
  return d_base_lightning_resistance_fraction;
}

// Get the lightning resistance
qreal Actor::getLightningResistance() const
{
  return d_base_lightning_resistance_fraction;
}

// Get the armor class
int Actor::getBaseArmorClass() const
{
  return 0;
}

// Get the armor class
int Actor::getArmorClass() const
{
  return this->getBaseArmorClass();
}

// Get the base damage
int Actor::getBaseDamage() const
{
  return 0;
}

int Actor::getMinimumDamage() const
{
  return this->getBaseDamage();
}

// Get the maximum damage
int Actor::getMaximumDamage() const
{
  return this->getBaseDamage();
}

// Get the base percent chance to hit with melee weapon
qreal Actor::getBaseChanceToHitWithMeleeWeapon() const
{
  return 0.0;
}

// Get the percent chance to hit with melee weapon
qreal Actor::getChanceToHitWithMeleeWeapon() const
{
  return this->getBaseChanceToHitWithMeleeWeapon();
}

// Get the base percent chance to hit with ranged weapon
qreal Actor::getBaseChanceToHitWithRangedWeapon() const
{
  return 0.0;
}

// Get the percent chance to hit with ranged weapon
qreal Actor::getChanceToHitWithRangedWeapon() const
{
  return this->getBaseChanceToHitWithRangedWeapon();
}

// Get the base percent chance to hit with a spell
qreal Actor::getBaseChanceToHitWithSpell() const
{
  return 0.0;
}

// Get the percent chance to hit with a spell
qreal Actor::getChanceToHitWithSpell() const
{
  return this->getBaseChanceToHitWithSpell();
}

// The actor can be attacked
bool Actor::canBeAttacked() const
{
  return true;
}

// Increment the base strength
void Actor::incrementBaseStrength()
{
  ++d_base_strength;

  emit baseStatsChanged();
}

void Actor::incrementBaseMagic()
{
  ++d_base_magic;

  emit baseStatsChanged();
}

void Actor::incrementBaseDexterity()
{
  ++d_base_dexterity;

  emit baseStatsChanged();
}

void Actor::incrementBaseVitality()
{
  ++d_base_vitality;

  emit baseStatsChanged();
}

// Set the target
void Actor::setTarget( LevelObject* target, QPointF target_coord )
{
  if( target )
  {
    d_target = target;

    // Get approximate position of Actors feet
    QPointF lower_center_point( this->boundingRect().left() + this->boundingRect().width()/2, this->boundingRect().height() - 20 );

    this->setPath( this->getGrid().constructPath( this, target, target_coord, this->mapToScene( lower_center_point ) ) );
    
    emit targetSet( target );
  }
}

// Cast a spell at the target
void Actor::castSpellAt( LevelObject* target )
{
  emit spellCastAt( target );
}

// Update time dependent states
/*! \details If the actor direction or position changes this method will
 * return true indicating that the screen update is required.
 */
bool Actor::updateTimeDependentStates()
{
  return this->updateTimeDependentStatesImpl( d_active_state == Walking );
}

// Set the actor sprites
void Actor::setActorSprites(
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
void Actor::initializeStateMachine( QStateMachine& state_machine )
{
  // Create the action states
  QState* action_states_parent = new QState;

  this->createActionStates( action_states_parent );
  
  state_machine.addState( action_states_parent );
  state_machine.setInitialState( action_states_parent );
}

// Create the action states
void Actor::createActionStates( QState* parent_state )
{
  // Create the alive states
  QState* alive_states_parent = new QState( parent_state );
  this->createAliveStates( alive_states_parent );

  // Create the dying state
  QState* dying_state = new QState( parent_state );

  // Create the dead state
  QFinalState* dead_state = new QFinalState( parent_state );

  // Create the transitions
  alive_states_parent->addTransition( this,
                                      SIGNAL(healthDepleted()),
                                      dying_state );
  dying_state->addTransition( this,
                              SIGNAL(allActiveFramesShown()),
                              dead_state );

  // Set the alive states parent as the initial state
  parent_state->setInitialState( alive_states_parent );

  // Connect the state signals to actor slots
  QObject::connect( dying_state, SIGNAL(entered()),
                    this, SLOT(handleDyingStateEntered()) );
  QObject::connect( dead_state, SIGNAL(entered()),
                    this, SLOT(handleDeadStateEntered()) );
}

// Create the alive states
void Actor::createAliveStates( QState* alive_parent_state )
{
  // Create the non-recoiling state parent
  QState* non_recoiling_state_parent = new QState( alive_parent_state );

  // Create the non-casting state parent
  QState* non_casting_state_parent = new QState( non_recoiling_state_parent );

  // Create the standing state
  QState* standing_state = new QState( non_casting_state_parent );

  // Create the walking state
  QState* walking_state = new QState( non_casting_state_parent );

  // Create the attacking state
  QState* attacking_state = new QState( non_casting_state_parent );

  // Create the casting state
  QState* casting_state = new QState( non_recoiling_state_parent );

  // Create the recoiling state
  QState* recoiling_state = new QState( alive_parent_state );

  // Create the recoiling transitions
  non_recoiling_state_parent->addTransition( this,
                                             SIGNAL(hit()),
                                             recoiling_state );
  recoiling_state->addTransition( this,
                                  SIGNAL(allActiveFramesShown()),
                                  standing_state );

  // Create the spell casting transitions
  non_casting_state_parent->addTransition( this,
                                           SIGNAL(spellCastAt(LevelObject*)),
                                           casting_state );

  casting_state->addTransition( this,
                                SIGNAL(allActiveFramesShown()),
                                standing_state );

  // Create the attacking transitions
  QAbstractTransition* to_attacking_state_transition =
    new ActorAttackingTargetTransition( this );
  to_attacking_state_transition->setTargetState( attacking_state );
  
  walking_state->addTransition( to_attacking_state_transition );
  attacking_state->addTransition( this,
                                  SIGNAL(allActiveFramesShown()),
                                  standing_state );

  // Create the walking transitions
  standing_state->addTransition( this,
                                 SIGNAL(targetSet(LevelObject*,LevelObject*)),
                                 walking_state );

  QAbstractTransition* to_standing_state_transition =
    new BasicActorStandingByTargetTransition( this );
  to_standing_state_transition->setTargetState( standing_state );

  walking_state->addTransition( to_standing_state_transition );

  // Set the initial states
  alive_parent_state->setInitialState( non_recoiling_state_parent );
  non_recoiling_state_parent->setInitialState( non_casting_state_parent );
  non_casting_state_parent->setInitialState( standing_state );

  // Connect the state signals to actor slots
  QObject::connect( standing_state, SIGNAL(entered()),
                    this, SLOT(handleStandingStateEntered()) );
  QObject::connect( walking_state, SIGNAL(entered()),
                    this, SLOT(handleWalkingStateEntered()) );
  QObject::connect( walking_state, SIGNAL(exited()),
                    this, SLOT(handleWalkingStateExited()) );
  QObject::connect( attacking_state, SIGNAL(entered()),
                    this, SLOT(handleAttackingStateEntered()) );
  QObject::connect( attacking_state, SIGNAL(exited()),
                    this, SLOT(handleAttackingStateExited()) );
  QObject::connect( casting_state, SIGNAL(entered()),
                    this, SLOT(handleCastingStateEntered()) );
  QObject::connect( casting_state, SIGNAL(exited()),
                    this, SLOT(handleCastingStateExited()) );
  QObject::connect( recoiling_state, SIGNAL(entered()),
                    this, SLOT(handleRecoilingStateEntered()) );
}

// Handle standing state entered
void Actor::handleStandingStateEntered()
{
  std::cout << "standing state entered" << std::endl;
  d_active_state = Standing;
  
  this->setActiveSprites( (*d_sprites)[Standing] );

  this->update( this->boundingRect() );
}

// Handle walking state entered
void Actor::handleWalkingStateEntered()
{
  std::cout << "walking state entered" << std::endl;
  d_active_state = Walking;

  this->setActiveSprites( (*d_sprites)[Walking] );

  this->update( this->boundingRect() );
}

// Handle walking state exited
void Actor::handleWalkingStateExited()
{
  this->restartActiveSprite();
}

// Handle attacking state entered
void Actor::handleAttackingStateEntered()
{
  d_active_state = Attacking;

  this->setActiveSprites( (*d_sprites)[Attacking] );

  this->update( this->boundingRect() );
}

// Handle attacking state exited
void Actor::handleAttackingStateExited()
{
  this->restartActiveSprite();
}

// Handle casting state entered
void Actor::handleCastingStateEntered()
{
  d_active_state = CastingSpell;

  this->setActiveSprites( (*d_sprites)[CastingSpell] );
  this->restartActiveSprite();

  this->update( this->boundingRect() );
}

// Handle recoiling state entered
void Actor::handleRecoilingStateEntered()
{
  d_active_state = RecoilingFromHit;

  this->setActiveSprites( (*d_sprites)[RecoilingFromHit] );

  this->update( this->boundingRect() );
}

// Handle casting state exited
void Actor::handleCastingStateExited()
{
  this->restartActiveSprite();
}

// Handle dying state entered
void Actor::handleDyingStateEntered()
{
  d_active_state = Dying;
  
  this->setActiveSprites( (*d_sprites)[Dying] );

  this->update( this->boundingRect() );
}
  
// Handle dead state entered
void Actor::handleDeadStateEntered()
{
  d_active_state = Dead;

  this->setActiveSprites( (*d_sprites)[Dead] );

  this->update( this->boundingRect() );
  
  emit dead();
}

QML_REGISTER_BASE_TYPE( Actor );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Actor.cpp
//---------------------------------------------------------------------------//
