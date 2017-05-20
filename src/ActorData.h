//---------------------------------------------------------------------------//
//!
//! \file   ActorData.h
//! \author Alex Robinson
//! \brief  The actor data class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ACTOR_DATA_H
#define ACTOR_DATA_H

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QObject>

// QtD1 Includes
#include "Actor.h"
#include "Direction.h"

namespace QtD1{

//! The actor data
class ActorData : public QObject
{
  Q_OBJECT

public:

  //! The directional sprites type
  typedef Actor::DirectionGameSpriteMap DirectionGameSpriteMap;

  //! The state sprites type
  typedef Actor::StateDirectionGameSpriteMap StateDirectionGameSpriteMap;

  //! Constructor
  ActorData( QObject* parent = 0 );

  //! Assignment operator
  ActorData& operator=( const ActorData& other );

  //! Destructor
  virtual ~ActorData()
  { /* ... */ }

  //! Set the level
  void setLevel( const int level );

  //! Get the level
  int getLevel() const;

  //! Set the kill experience
  void setKillExperience( const int kill_experience );

  //! Get the kill experience
  int getKillExperience() const;

  //! Set the base strength
  void setBaseStrength( const int strength );

  //! Get the base strength
  int getBaseStrength() const;

  //! Get the strength
  virtual int getStrength() const;

  //! Set the base magic
  void setBaseMagic( const int magic );

  //! Get the base magic
  int getBaseMagic() const;

  //! Get the magic
  virtual int getMagic() const;

  //! Set the base dexterity
  void setBaseDexterity( const int dexterity );

  //! Get the base dexterity
  int getBaseDexterity() const;

  //! Get the dexterity
  virtual int getDexterity() const;

  //! Set the base vitality
  void setBaseVitality( const int vitality );

  //! Get the base vitality
  int getBaseVitality() const;

  //! Get the vitality
  virtual int getVitality() const;

  //! Get the base health
  virtual int getBaseHealth() const;

  //! Get the max health
  virtual int getMaxHealth() const;

  //! Get the health
  int getHealth() const;

  //! Get the base mana
  virtual int getBaseMana() const;

  //! Get the max mana
  virtual int getMaxMana() const;

  //! Get the mana
  int getMana() const;

  //! Set the base magic resistance
  void setBaseMagicResistance( const qreal resist_fraction );

  //! Get the base magic resistance
  qreal getBaseMagicResistance() const;

  //! Get the magic resistance
  virtual qreal getMagicResistance() const;

  //! Set the base fire resistance
  void setBaseFireResistance( const qreal resist_fraction );

  //! Get the base fire resistance
  qreal getBaseFireResistance() const;

  //! Get the fire resistance
  virtual qreal getFireResistance() const;

  //! Set the base lightning resistance
  void setBaseLightningResistance( const qreal resist_fraction );

  //! Get the base lightning resistance
  qreal getBaseLightningResistance() const;

  //! Get the lightning resistance
  virtual qreal getLightningResistance() const;

  //! Get the base armor class
  virtual int getBaseArmorClass() const;

  //! Get the armor class
  virtual int getArmorClass() const;

  //! Get the base damage
  virtual int getBaseDamage() const;

  //! Get the minimum damage
  virtual int getMinimumDamage() const;

  //! Get base the damage
  virtual int getMaximumDamage() const;

  //! Get the base percent chance to hit with melee weapon
  virtual qreal getBaseChanceToHitWithMeleeWeapon() const;

  //! Get the percent chance to hit with melee weapon
  virtual qreal getChanceToHitWithMeleeWeapon() const;

  //! Get the base percent chance to hit with ranged weapon
  virtual qreal getBaseChanceToHitWithRangedWeapon() const;

  //! Get the percent chance to hit with ranged weapon
  virtual qreal getChanceToHitWithRangedWeapon() const;

  //! Get the base percent chance to hit with a spell
  virtual qreal getBaseChanceToHitWithSpell() const;

  //! Get the chance to hit with a spell
  virtual qreal getChanceToHitWithSpell() const;

  //! Get the actor x velocity
  qreal getXVelocity() const;

  //! Set the actor x velocity
  void setXVelocity( const qreal x_velocity );

  //! Get the actor y velocity
  qreal getYVelocity() const;

  //! Set the actor y velocity
  void setYVelocity( const qreal y_velocity );

  //! Set the actor velocity
  void setVelocity( const qreal x_velocity, const qreal y_velocity );

  //! Get the state direction game sprite map
  std::shared_ptr<StateDirectionGameSpriteMap>& getSprites();

  //! Get the state direction game sprite map
  const std::shared_ptr<StateDirectionGameSpriteMap>& getSprites() const;

  // Update active sprite
  void updateActiveSprite();

  //! Get the active sprite
  GameSprite* getActiveSprite();

  //! Get the active sprite
  const GameSprite* getActiveSprite() const;

  //! Get the active state
  Actor::State getActiveState() const;

  //! Set the active state
  void setActiveState( const Actor::State state );

  //! Get the active direction
  Direction getActiveDirection() const;

  //! Set the active direction
  void setActiveDirection( const Direction direction );

  //! Set the active state and direction
  void setActiveStateAndDirection( const Actor::State state,
                                   const Direction direction );

signals:

  void healthChanged( const int current_health );
  void manaChanged( const int current_mana );
  void coreStatIncremented();
  void healthDepleted();

public slots:

  //! Increment the base strength
  void incrementBaseStrength();

  //! Increment the base magic
  void incrementBaseMagic();

  //! Increment the base dexterity
  void incrementBaseDexterity();

  //! Increment the base vitality
  void incrementBaseVitality();

  //! Set the health (will emit healthChanged signal)
  void setHealth( const int new_health );

  //! Set the mana (will emit manaChanged signal)
  void setMana( const int new_mana );

private:

  // The level
  int d_level;

  // The kill experience
  int d_kill_experience;

  // The base strength
  int d_base_strength;

  // The base magic
  int d_base_magic;

  // The base dexterity
  int d_base_dexterity;

  // The base vitality
  int d_base_vitality;

  // The current health
  int d_health;

  // The current mana
  int d_mana;

  // The base magic resistance percent
  qreal d_base_magic_resistance_fraction;

  // The base fire resistance percent
  qreal d_base_fire_resistance_fraction;

  // The base lightning resistance percent
  qreal d_base_lightning_resistance_fraction;

  // The velocity of the actor
  qreal d_x_velocity;
  qreal d_y_velocity;

  // The actor sprites
  std::shared_ptr<StateDirectionGameSpriteMap> d_sprites;

  // The active game sprite (active state, active direction, active sprite)
  std::tuple<Actor::State,Direction,GameSprite*> d_active_sprite;
};

} // end QtD1 namespace

#endif // end ACTOR_DATA_H

//---------------------------------------------------------------------------//
// end ActorData.h
//---------------------------------------------------------------------------//
