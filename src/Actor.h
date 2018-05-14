//---------------------------------------------------------------------------//
//!
//! \file   Actor.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The actor base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ACTOR_H
#define ACTOR_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QState>

// QtD1 Includes
#include "BasicActor.h"

namespace QtD1{

/*! The actor base class
 *
 * Objects of this class can be passed by value without copy overhead because
 * this class uses implicit data sharing.
 */
class Actor : public BasicActor
{
  Q_OBJECT
  Q_PROPERTY(int level READ getLevel)
  Q_PROPERTY(int baseStrength READ getBaseStrength)
  Q_PROPERTY(int strength READ getStrength)
  Q_PROPERTY(int baseMagic READ getBaseMagic)
  Q_PROPERTY(int magic READ getMagic)
  Q_PROPERTY(int baseDexterity READ getBaseDexterity)
  Q_PROPERTY(int dexterity READ getDexterity)
  Q_PROPERTY(int baseVitality READ getBaseVitality)
  Q_PROPERTY(int vitality READ getVitality)
  Q_PROPERTY(int baseHealth READ getBaseHealth)
  Q_PROPERTY(int maxHealth READ getMaxHealth)
  Q_PROPERTY(int health READ getHealth)
  Q_PROPERTY(int baseMana READ getBaseMana)
  Q_PROPERTY(int maxMana READ getMaxMana)
  Q_PROPERTY(int mana READ getMana)
  Q_PROPERTY(qreal magicResistance READ getMagicResistance)
  Q_PROPERTY(qreal fireResistance READ getFireResistance)
  Q_PROPERTY(qreal lightningResistance READ getLightningResistance)
  Q_PROPERTY(int armorClass READ getArmorClass)
  Q_PROPERTY(int minimumDamage READ getMinimumDamage)
  Q_PROPERTY(int maximumDamage READ getMaximumDamage)
  Q_PROPERTY(int chanceToHit READ getChanceToHitWithMeleeWeapon)
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Actor" )

public:

  //! Constructor
  Actor( QGraphicsObject* parent = 0 );

  //! Copy constructor
  Actor( const Actor& other_actor );

  //! Assignment operator
  Actor& operator=( const Actor& other_actor );

  //! Destructor
  virtual ~Actor()
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

  //! Get the maximum damage
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

  //! Get the actor x velocity (pixels per game tic)
  qreal getXVelocity() const;

  //! Get the actor y velocity (pixels per game tic)
  qreal getYVelocity() const;

  //! The actor can be attacked
  bool canBeAttacked() const override;

signals:

  //! Actor health changed
  void healthChanged( const int current_health );

  //! Actor mana changed
  void manaChanged( const int current_mana );

  //! Actor base stats changed
  void baseStatsChanged();

  //! Actor health depleted
  void healthDepleted();

  //! Actor target set
  void targetSet( LevelObject* target );

  //! Actor target reached
  void targetReached( LevelObject* target );

  //! Actor cast spell at
  void spellCastAt( LevelObject* target );

  //! Actor hit
  void hit();

  //! Actor dead
  void dead();

public slots:

  //! Increment the base strength
  void incrementBaseStrength();

  //! Increment the base magic
  void incrementBaseMagic();

  //! Increment the base dexterity
  void incrementBaseDexterity();

  //! Increment the base vitality
  void incrementBaseVitality();

  //! Add health
  void addHealth( const int health );

  //! Remove health
  void removeHealth( const int health );

  //! Restore health
  void restoreHealth();

    //! Add mana
  void addMana( const int mana );

  //! Remove mana
  void removeMana( const int mana );

  //! Restore mana
  void restoreMana();

  //! Set the target
  void setTarget( LevelObject* target, QPointF target_coord );

  //! Cast a spell at the target
  virtual void castSpellAt( LevelObject* target );

protected:

  //! The actor state enum
  enum State{
    Standing = 0,
    Walking,
    Attacking,
    RecoilingFromHit,
    CastingSpell,
    Dying,
    Dead
  };

  //! The state sprites type
  typedef QMap<Actor::State,std::shared_ptr<BasicActor::DirectionGameSpriteMap> >
  StateDirectionGameSpriteMap;

  //! Set the actor sprites
  void setActorSprites(
                 const std::shared_ptr<StateDirectionGameSpriteMap>& sprites );

  //! Initialize the state machine
  virtual void initializeStateMachine( QStateMachine& state_machine );

  //! Create the action states
  void createActionStates( QState* parent_state );

protected slots:

  //! Set the health (will emit healthChanged signal)
  void setHealth( const int new_health );

  //! Set the mana (will emit manaChanged signal)
  void setMana( const int new_mana );

  //! Set the actor x velocity
  void setXVelocity( const qreal x_velocity );

  //! Set the actor y velocity
  void setYVelocity( const qreal y_velocity );

  //! Set the actor velocity
  void setVelocity( const qreal x_velocity, const qreal y_velocity );

private slots:

  // Handle standing state entered
  void handleStandingStateEntered();

  // Handle walking state entered
  void handleWalkingStateEntered();

  // Handle walking state exited
  void handleWalkingStateExited();

  // Handle attacking state entered
  void handleAttackingStateEntered();

  // Handle attacking state exited
  void handleAttackingStateExited();

  // Handle casting state entered
  void handleCastingStateEntered();

  // Handle casting state exited
  void handleCastingStateExited();

  // Handle recoiling state entered
  void handleRecoilingStateEntered();

  // Handle dying state entered
  void handleDyingStateEntered();

  // Handle dead state entered
  void handleDeadStateEntered();

private:

  // Create the alive states
  void createAliveStates( QState* alive_parent_state );

  // Update time dependent states
  bool updateTimeDependentStates() override;

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

  // The target of the actor
  LevelObject* d_target;

  // The actor sprites
  std::shared_ptr<StateDirectionGameSpriteMap> d_sprites;

  // The active state
  State d_active_state;
};

} // end QtD1 namespace

#endif // end ACTOR_H

//---------------------------------------------------------------------------//
// end Actor.h
//---------------------------------------------------------------------------//
