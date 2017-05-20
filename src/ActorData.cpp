//---------------------------------------------------------------------------//
//!
//! \file   ActorData.cpp
//! \author Alex Robinson
//! \brief  The actor data class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "ActorData.h"

namespace QtD1{

//! Constructor
ActorData::ActorData( QObject* parent )
  : QObject( parent ),
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
    d_x_velocity( 0.0 ),
    d_y_velocity( 0.0 ),
    d_sprites(),
    d_active_sprite()
{ /* ... */ }

// Assignment operator
ActorData& ActorData::operator=( const ActorData& other )
{
  if( this != &other )
  {
    d_level = other.d_level;
    d_kill_experience = other.d_kill_experience;
    d_base_strength = other.d_base_strength;
    d_base_magic = other.d_base_magic;
    d_base_dexterity = other.d_base_dexterity;
    d_base_vitality = other.d_base_vitality;
    d_health = other.d_health;
    d_mana = other.d_mana;
    d_base_magic_resistance_fraction = other.d_base_magic_resistance_fraction;
    d_base_fire_resistance_fraction = other.d_base_fire_resistance_fraction;
    d_base_lightning_resistance_fraction = other.d_base_lightning_resistance_fraction;
    d_x_velocity = other.d_x_velocity;
    d_y_velocity = other.d_y_velocity;

    // Need to do a deep copy of the sprites
    d_sprites = other.d_sprites;
    d_active_sprite = other.d_active_sprite;
  }

  return *this;
}

// Set the level
void ActorData::setLevel( const int level )
{
  d_level = std::max( level, 1 );
}

// Get the level
int ActorData::getLevel() const
{
  return d_level;
}

// Set the kill experience
void ActorData::setKillExperience( const int kill_experience )
{
  d_kill_experience = std::max( kill_experience, 0 );
}

// Get the kill experience
int ActorData::getKillExperience() const
{
  return d_kill_experience;
}

// Set the base strength
void ActorData::setBaseStrength( const int strength )
{
  d_base_strength = std::max( strength, 0 );
}

// Get the base strength
int ActorData::getBaseStrength() const
{
  return d_base_strength;
}

// Get the strength
int ActorData::getStrength() const
{
  return d_base_strength;
}

// Set the base magic
void ActorData::setBaseMagic( const int magic )
{
  d_base_magic = std::max( magic, 0 );
}

// Get the base magic
int ActorData::getBaseMagic() const
{
  return d_base_magic;
}

// Get the magic
int ActorData::getMagic() const
{
  return d_base_magic;
}

// Set the base dexterity
void ActorData::setBaseDexterity( const int dexterity )
{
  d_base_dexterity = std::max( dexterity, 0 );
}

// Get the base dexterity
int ActorData::getBaseDexterity() const
{
  return d_base_dexterity;
}

// Get the dexterity
int ActorData::getDexterity() const
{
  return d_base_dexterity;
}

// Set the base vitality
void ActorData::setBaseVitality( const int vitality )
{
  d_base_vitality = std::max( vitality, 0 );
}

// Get the base vitality
int ActorData::getBaseVitality() const
{
  return d_base_vitality;
}

// Get the vitality
int ActorData::getVitality() const
{
  return d_base_vitality;
}

// Get the base health
int ActorData::getBaseHealth() const
{
  return 1;
}

// Get the max health
int ActorData::getMaxHealth() const
{
  return this->getBaseHealth();
}

// Get the health
int ActorData::getHealth() const
{
  return d_health;
}

// Get the base mana
int ActorData::getBaseMana() const
{
  return 1;
}

// Get the max mana
int ActorData::getMaxMana() const
{
  return this->getBaseMana();
}

// Get the mana
int ActorData::getMana() const
{
  return d_mana;
}

// Set the base magic resistance
void ActorData::setBaseMagicResistance( const qreal resist_fraction )
{
  if( resist_fraction >= 0.0 )
  {
    d_base_lightning_resistance_fraction =
      std::min( resist_fraction, 1.0 );
  }
  else
    d_base_lightning_resistance_fraction = 0.0;
}

// Get the base magic resistance
qreal ActorData::getBaseMagicResistance() const
{
  return d_base_lightning_resistance_fraction;
}

// Get the magic resistance
qreal ActorData::getMagicResistance() const
{
  return d_base_lightning_resistance_fraction;
}

// Set the base fire resistance
void ActorData::setBaseFireResistance( const qreal resist_fraction )
{
  if( resist_fraction >= 0.0 )
  {
    d_base_fire_resistance_fraction =
      std::min( resist_fraction, 1.0 );
  }
  else
    d_base_fire_resistance_fraction = 0.0;
}

// Get the base fire resistance
qreal ActorData::getBaseFireResistance() const
{
  return d_base_fire_resistance_fraction;
}

// Get the fire resistance
qreal ActorData::getFireResistance() const
{
  return d_base_fire_resistance_fraction;
}

// Set the base lightning resistance
void ActorData::setBaseLightningResistance( const qreal resist_fraction )
{
  if( resist_fraction >= 0.0 )
  {
    d_base_lightning_resistance_fraction =
      std::min( resist_fraction, 1.0 );
  }
  else
    d_base_lightning_resistance_fraction = 0.0;
}

// Get the base lightning resistance
qreal ActorData::getBaseLightningResistance() const
{
  return d_base_lightning_resistance_fraction;
}

// Get the lightning resistance
qreal ActorData::getLightningResistance() const
{
  return d_base_lightning_resistance_fraction;
}

// Get the base armor class
int ActorData::getBaseArmorClass() const
{
  return 0;
}

// Get the armor class
int ActorData::getArmorClass() const
{
  return 0;
}

// Get the base damage
int ActorData::getBaseDamage() const
{
  return 0;
}

// Get the base damage
int ActorData::getMinimumDamage() const
{
  return 0;
}

// Get the maximum damage
int ActorData::getMaximumDamage() const
{
  return 0;
}

// Get the base percent chance to hit with melee weapon
qreal ActorData::getBaseChanceToHitWithMeleeWeapon() const
{
  return 0.0;
}

// Get the percent chance to hit with melee weapon
qreal ActorData::getChanceToHitWithMeleeWeapon() const
{
  return 0.0;
}

// Get the base percent chance to hit with ranged weapon
qreal ActorData::getBaseChanceToHitWithRangedWeapon() const
{
  return 0.0;
}

// Get the percent chance to hit with ranged weapon
qreal ActorData::getChanceToHitWithRangedWeapon() const
{
  return 0.0;
}

// Get the base percent chance to hit with a spell
qreal ActorData::getBaseChanceToHitWithSpell() const
{
  return 0.0;
}

// Get the percent chance to hit with a spell
qreal ActorData::getChanceToHitWithSpell() const
{
  return 0.0;
}

// Get the actor x velocity
qreal ActorData::getXVelocity() const
{
  return d_x_velocity;
}

// Set the actor x velocity
void ActorData::setXVelocity( const qreal x_velocity )
{
  d_x_velocity = x_velocity;
}

// Get the actor y velocity
qreal ActorData::getYVelocity() const
{
  return d_y_velocity;
}

// Set the actor y velocity
void ActorData::setYVelocity( const qreal y_velocity )
{
  d_y_velocity = y_velocity;
}

// Set the actor velocity
void ActorData::setVelocity( const qreal x_velocity, const qreal y_velocity )
{
  d_x_velocity = x_velocity;
  d_y_velocity = y_velocity;
}

// Get the state direction game sprite map
auto ActorData::getSprites() -> std::shared_ptr<StateDirectionGameSpriteMap>&
{
  return d_sprites;
}

// Get the state direction game sprite map
auto ActorData::getSprites() const -> const std::shared_ptr<StateDirectionGameSpriteMap>&
{
  return d_sprites;
}

// Get the active sprite
GameSprite* ActorData::getActiveSprite()
{
  return std::get<2>( d_active_sprite );
}

// Get the active sprite
const GameSprite* ActorData::getActiveSprite() const
{
  return std::get<2>( d_active_sprite );
}

// Get the active state
Actor::State ActorData::getActiveState() const
{
  return std::get<0>( d_active_sprite );
}

// Set the active state
void ActorData::setActiveState( const Actor::State state )
{
  std::get<0>( d_active_sprite ) = state;

  this->updateActiveSprite();
}

// Get the active direction
Direction ActorData::getActiveDirection() const
{
  return std::get<1>( d_active_sprite );
}

// Set the active direction
void ActorData::setActiveDirection( const Direction direction )
{
  std::get<1>( d_active_sprite ) = direction;

  this->updateActiveSprite();
}

// Set the active state and direction
void ActorData::setActiveStateAndDirection( const Actor::State state,
                                            const Direction direction )
{
  std::get<0>( d_active_sprite ) = state;
  std::get<1>( d_active_sprite ) = direction;

  this->updateActiveSprite();
}

// Increment the base strength
void ActorData::incrementBaseStrength()
{
  ++d_base_strength;

  emit coreStatIncremented();
}

// Increment the base magic
void ActorData::incrementBaseMagic()
{
  ++d_base_magic;

  emit coreStatIncremented();
}

// Increment the base dexterity
void ActorData::incrementBaseDexterity()
{
  ++d_base_dexterity;

  emit coreStatIncremented();
}

// Increment the base vitality
void ActorData::incrementBaseVitality()
{
  ++d_base_vitality;

  emit coreStatIncremented();
}

// Set the health (will emit healthChanged signal)
void ActorData::setHealth( const int new_health )
{
  if( d_health != new_health )
  {
    if( new_health <= 0 )
      d_health = 0;
    else
      d_health = std::min( new_health, this->getMaxHealth() );

    emit healthChanged( d_health );

    if( d_health == 0 )
      emit healthDepleted();
  }
}

// Set the mana (will emit manaChanged signal)
void ActorData::setMana( const int new_mana )
{
  if( d_mana != new_mana )
  {
    if( new_mana <= 0 )
      d_mana = 0;
    else
      d_mana = std::min( new_mana, this->getMaxMana() );

    emit manaChanged( d_mana );
  }
}

// Update the active sprite
void ActorData::updateActiveSprite()
{
  Actor::State current_state = std::get<0>( d_active_sprite );
  Direction current_direction = std::get<1>( d_active_sprite );

  if( d_sprites )
  {
    std::get<2>( d_active_sprite ) =
      &(*(*d_sprites)[current_state])[current_direction];
  }
  else
    std::get<2>( d_active_sprite ) = NULL;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end ActorData.cpp
//---------------------------------------------------------------------------//
