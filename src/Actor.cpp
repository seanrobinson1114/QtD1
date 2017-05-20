//---------------------------------------------------------------------------//
//!
//! \file   Actor.cpp
//! \author Alex Robinson
//! \brief  The actor base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// QtD1 Includes
#include "Actor.h"
#include "ActorData.h"

namespace QtD1{

// Constructor
Actor::Actor( QGraphicsObject* parent )
  : InteractiveLevelObject( parent ),
    d_data( new ActorData )
{
  this->connectActorDataSignalsToActorSlots();
}

// Copy constructor
Actor::Actor( const Actor& other_actor )
  : InteractiveLevelObject( other_actor.parentObject() ),
    d_data( other_actor.d_data )
{
  this->connectActorDataSignalsToActorSlots();
}

// Constructor
Actor::Actor( ActorData* data, QGraphicsObject* parent )
  : InteractiveLevelObject( parent ),
    d_data( data )
{
  this->connectActorDataSignalsToActorSlots();
}

// Assignment operator
Actor& Actor::operator=( const Actor& other_actor )
{
  if( this != &other_actor )
  {
    this->setParentItem( other_actor.parentObject() );
    
    this->disconnectActorSlotsFromActorDataSignals();

    d_data = other_actor.d_data;

    this->connectActorDataSignalsToActorSlots();
  }

  return *this;
}

// Set the state of the actor
void Actor::setState( const State state )
{
  // Set the default sprite
  d_data->setActiveState( state );
}

// Get the state of the actor
Actor::State Actor::getState() const
{
  return d_data->getActiveState();
}

// Set the direction of the actor
void Actor::setDirection( const Direction direction )
{
  d_data->setActiveDirection( direction );
}

// Get the direction of the actor
Direction Actor::getDirection() const
{
  return d_data->getActiveDirection();
}

// Set the level
void Actor::setLevel( const int level )
{
  d_data->setLevel( level );
}

// Set the state and direction of the actor
void Actor::setStateAndDirection( const State state, const Direction direction )
{
  d_data->setActiveStateAndDirection( state, direction );
}

// Get the level
int Actor::getLevel() const
{
  return d_data->getLevel();
}

// Set the kill experience
void Actor::setKillExperience( const int kill_experience )
{
  d_data->setKillExperience( kill_experience );
}

// Get the kill experience
int Actor::getKillExperience() const
{
  return d_data->getKillExperience();
}

// Set the base strength
void Actor::setBaseStrength( const int strength )
{
  d_data->setBaseStrength( strength );
}

// Get the base strength
int Actor::getBaseStrength() const
{
  return d_data->getBaseStrength();
}

// Get the strength
int Actor::getStrength() const
{
  return d_data->getStrength();
}

// Set the base magic
void Actor::setBaseMagic( const int magic )
{
  d_data->setBaseMagic( magic );
}

// Get the base magic
int Actor::getBaseMagic() const
{
  return d_data->getBaseMagic();
}

// Get the magic
int Actor::getMagic() const
{
  return d_data->getMagic();
}

// Set the base dexterity
void Actor::setBaseDexterity( const int dexterity )
{
  d_data->setBaseDexterity( dexterity );
}

// Get the base dexterity
int Actor::getBaseDexterity() const
{
  return d_data->getBaseDexterity();
}

// Get the dexterity
int Actor::getDexterity() const
{
  return d_data->getDexterity();
}

// Set the base vitality
void Actor::setBaseVitality( const int vitality )
{
  d_data->setBaseVitality( vitality );
}

// Get the base vitality
int Actor::getBaseVitality() const
{
  return d_data->getBaseVitality();
}

// Get the vitality
int Actor::getVitality() const
{
  return d_data->getVitality();
}

// Get the base health
int Actor::getBaseHealth() const
{
  return d_data->getBaseHealth();
}

// Get the max health
int Actor::getMaxHealth() const
{
  return d_data->getMaxHealth();
}

// Set the health
void Actor::setHealth( const int health )
{
  d_data->setHealth( health );
}

// Add health
void Actor::addHealth( const int health )
{
  if( health > 0 )
    d_data->setHealth( d_data->getHealth() + health );
}

// Remove health
void Actor::removeHealth( const int health )
{
  if( health > 0 )
    d_data->setHealth( d_data->getHealth() - health );
}

// Restore health
void Actor::restoreHealth()
{
  d_data->setHealth( d_data->getMaxHealth() );
}

// Get the health
int Actor::getHealth() const
{
  return d_data->getHealth();
}

// Get the base mana
int Actor::getBaseMana() const
{
  return d_data->getBaseMana();
}

// Get the max mana
int Actor::getMaxMana() const
{
  return d_data->getMaxMana();
}

// Set the mana
void Actor::setMana( const int mana )
{
  d_data->setMana( mana );
}

// Add mana
void Actor::addMana( const int mana )
{
  if( mana > 0 )
    d_data->setMana( d_data->getMana() + mana );
}

// Remove mana
void Actor::removeMana( const int mana )
{
  if( mana > 0 )
    d_data->setMana( d_data->getMana() - mana );
}

// Restore mana
void Actor::restoreMana()
{
  d_data->setMana( this->getMaxMana() );
}

// Get the mana
int Actor::getMana() const
{
  return d_data->getMana();
}

// Set the base magic resistance
void Actor::setBaseMagicResistance( const qreal resist_fraction )
{
  d_data->setBaseMagicResistance( resist_fraction );
}

// Get the base magic resistance
qreal Actor::getBaseMagicResistance() const
{
  return d_data->getBaseMagicResistance();
}

// Get the magic resistance
qreal Actor::getMagicResistance() const
{
  return d_data->getMagicResistance();
}

// Set the base fire resistance
void Actor::setBaseFireResistance( const qreal resist_fraction )
{
  d_data->setBaseFireResistance( resist_fraction );
}

// Get the base fire resistance
qreal Actor::getBaseFireResistance() const
{
  return d_data->getBaseFireResistance();
}

// Get the fire resistance
qreal Actor::getFireResistance() const
{
  return d_data->getFireResistance();
}

// Set the base lightning resistance
void Actor::setBaseLightningResistance( const qreal resist_fraction )
{
  d_data->setBaseLightningResistance( resist_fraction );
}

// Get the base lightning resistance
qreal Actor::getBaseLightningResistance() const
{
  return d_data->getBaseLightningResistance();
}

// Get the lightning resistance
qreal Actor::getLightningResistance() const
{
  return d_data->getLightningResistance();
}

// Get the armor class
int Actor::getBaseArmorClass() const
{
  return d_data->getBaseArmorClass();
}

// Get the armor class
int Actor::getArmorClass() const
{
  return d_data->getArmorClass();
}

// Get the base damage
int Actor::getBaseDamage() const
{
  return d_data->getBaseDamage();
}

int Actor::getMinimumDamage() const
{
  return d_data->getMinimumDamage();
}

// Get the maximum damage
int Actor::getMaximumDamage() const
{
  return d_data->getMaximumDamage();
}

// Get the percent chance to hit with melee
qreal Actor::getChanceToHitWithMeleeWeapon() const
{
  return d_data->getChanceToHitWithMeleeWeapon();
}

// Get the percent chance to hit with ranged
qreal Actor::getChanceToHitWithRangedWeapon() const
{
  return d_data->getChanceToHitWithRangedWeapon();
}

// Get the percent chance to hit with spell
qreal Actor::getChanceToHitWithSpell() const
{
  return d_data->getChanceToHitWithSpell();
}

// Get the bounding rect of the actor
QRectF Actor::boundingRect() const
{
  if( d_data->getActiveSprite() )
    return d_data->getActiveSprite()->boundingRect();
  else
    return QRectF();
}

// Get the shape of the actor
QPainterPath Actor::shape() const
{
  if( d_data->getActiveSprite() )
    return d_data->getActiveSprite()->shape();
  else
    return QPainterPath();
}

// Advance the actor state
void Actor::advance( int phase )
{
  // Phase 0: actor state is about to advance
  // Phase 1: actor state is advancing
  if( phase == 1 )
  {
    if( d_data->getActiveSprite() )
    {
      d_data->getActiveSprite()->incrementFrame();
      this->moveBy( d_data->getXVelocity(), d_data->getYVelocity() );
      this->update( d_data->getActiveSprite()->boundingRect() );
    }    
  }
}

// Paint the actor
void Actor::paintImpl( QPainter* painter,
                       const QStyleOptionGraphicsItem* option,
                       QWidget* widget )
{
  if( d_data->getActiveSprite() )
  {
    d_data->getActiveSprite()->paint( painter, option, widget );
  }
}

// Increment the base strength
void Actor::incrementBaseStrength()
{
  d_data->incrementBaseStrength();
}

void Actor::incrementBaseMagic()
{
  d_data->incrementBaseMagic();
}

void Actor::incrementBaseDexterity()
{
  d_data->incrementBaseDexterity();
}

void Actor::incrementBaseVitality()
{
  d_data->incrementBaseVitality();
}

// Forward health changed signal in actor data to health changed signal
void Actor::handleHealthChangedInActorData( const int current_health )
{
  emit healthChanged( current_health );
}

// Forward mana changed signal in actor data to mana changed signal
void Actor::handleManaChangedInActorData( const int current_mana )
{
  emit manaChanged( current_mana );
}

// Forward core stat incremented signal in actor data to base stats changed
// signal
void Actor::handleCoreStatIncrementedInActorData()
{
  emit baseStatsChanged();
}

// Forward health depeleted signal in actor data to death signal
void Actor::handleHealthDepletedInActorData()
{
  emit death();
}

// Get the actor data
ActorData* Actor::getActorData()
{
  return d_data.get();
}

// Get the actor data
const ActorData* Actor::getActorData() const
{
  return d_data.get();
}

// Set the actor sprites
void Actor::setActorSprites(
                  const std::shared_ptr<StateDirectionGameSpriteMap>& sprites )
{
  d_data->getSprites() = sprites;
  d_data->updateActiveSprite();
}

// Connect actor data signals to actor slots
void Actor::connectActorDataSignalsToActorSlots()
{
  QObject::connect( d_data.get(), SIGNAL(healthChanged(const int)),
                    this, SLOT(handleHealthChangedInActorData(const int)) );
  QObject::connect( d_data.get(), SIGNAL(manaChanged(const int)),
                    this, SLOT(handleManaChangedInActorData(const int)) );
  QObject::connect( d_data.get(), SIGNAL(coreStatIncremented()),
                    this, SLOT(handleCoreStatIncrementedInActorData()) );
  QObject::connect( d_data.get(), SIGNAL(healthDepleted()),
                    this, SLOT(handleHealthDepletedInActorData()) );
}

// Disconnect actor slots from actor data signals
void Actor::disconnectActorSlotsFromActorDataSignals()
{
  QObject::disconnect( d_data.get(), SIGNAL(healthChanged(const int)),
                       this, SLOT(handleHealthChangedInActorData(const int)) );
  QObject::disconnect( d_data.get(), SIGNAL(manaChanged(const int)),
                       this, SLOT(handleManaChangedInActorData(const int)) );
  QObject::disconnect( d_data.get(), SIGNAL(coreStatIncremented()),
                       this, SLOT(handleCoreStatIncrementedInActorData()) );
  QObject::disconnect( d_data.get(), SIGNAL(healthDepleted()),
                       this, SLOT(handleHealthDepletedInActorData()) );
}

QML_REGISTER_BASE_TYPE( Actor );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Actor.cpp
//---------------------------------------------------------------------------//
