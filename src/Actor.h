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

// QtD1 Includes
#include "QMLRegistrationHelper.h"
#include "InteractiveLevelObject.h"
#include "Direction.h"
#include "GameSprite.h"

namespace QtD1{

class ActorData;

/*! The actor base class
 *
 * Objects of this class can be passed by value without copy overhead because
 * this class uses implicit data sharing.
 */
class Actor : public InteractiveLevelObject
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

  //! The directional sprites type
  typedef QMap<Direction,GameSprite> DirectionGameSpriteMap;

  //! The state sprites type
  typedef QMap<Actor::State,std::shared_ptr<DirectionGameSpriteMap> >
  StateDirectionGameSpriteMap;

  //! Constructor
  Actor( QGraphicsObject* parent = 0 );

  //! Copy constructor
  Actor( const Actor& other_actor );

  //! Assignment operator
  Actor& operator=( const Actor& other_actor );

  //! Destructor
  virtual ~Actor()
  { /* ... */ }

  //! Set the state of the actor
  void setState( const State state );

  //! Get the state of the actor
  State getState() const;

  //! Set the direction of the actor
  void setDirection( const Direction direction );

  //! Get the direction of the actor
  Direction getDirection() const;

  //! Set the state and direction of the actor
  void setStateAndDirection( const State state, const Direction direction );

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
  int getStrength() const;

  //! Set the base magic
  void setBaseMagic( const int magic );

  //! Get the base magic
  int getBaseMagic() const;

  //! Get the magic
  int getMagic() const;

  //! Set the base dexterity
  void setBaseDexterity( const int dexterity );

  //! Get the base dexterity
  int getBaseDexterity() const;

  //! Get the dexterity
  int getDexterity() const;

  //! Set the base vitality
  void setBaseVitality( const int vitality );

  //! Get the base vitality
  int getBaseVitality() const;

  //! Get the vitality
  int getVitality() const;

  //! Get the base health
  int getBaseHealth() const;

  //! Get the max health
  int getMaxHealth() const;

  //! Set the health
  void setHealth( const int health );

  //! Add health
  void addHealth( const int health );

  //! Remove health
  void removeHealth( const int health );

  //! Restore health
  void restoreHealth();

  //! Get the health
  int getHealth() const;

  //! Get the base mana
  int getBaseMana() const;

  //! Get the max mana
  int getMaxMana() const;

  //! Set the mana
  void setMana( const int mana );

  //! Add mana
  void addMana( const int mana );

  //! Remove mana
  void removeMana( const int mana );

  //! Restore mana
  void restoreMana();

  //! Get the mana
  int getMana() const;

  //! Set the base magic resistance
  void setBaseMagicResistance( const qreal resist_fraction );

  //! Get the base magic resistance
  qreal getBaseMagicResistance() const;

  //! Get the magic resistance
  qreal getMagicResistance() const;

  //! Set the base fire resistance
  void setBaseFireResistance( const qreal resist_fraction );

  //! Get the base fire resistance
  qreal getBaseFireResistance() const;

  //! Get the fire resistance
  qreal getFireResistance() const;

  //! Set the base lightning resistance
  void setBaseLightningResistance( const qreal resist_fraction );

  //! Get the base lightning resistance
  qreal getBaseLightningResistance() const;

  //! Get the lightning resistance
  qreal getLightningResistance() const;

  //! Get the base armor class
  int getBaseArmorClass() const;

  //! Get the armor class
  int getArmorClass() const;

  //! Get the base damage
  int getBaseDamage() const;

  //! Get the minimum damage
  int getMinimumDamage() const;

  //! Get the maximum damage
  int getMaximumDamage() const;

  //! Get the percent chance to hit with melee
  qreal getChanceToHitWithMeleeWeapon() const;

  //! Get the percent chance to hit with ranged
  qreal getChanceToHitWithRangedWeapon() const;

  //! Get the percent chance to hit with spell
  qreal getChanceToHitWithSpell() const;

  //! Get the bounding rect of the actor
  QRectF boundingRect() const override;

  //! Get the shape of the actor
  QPainterPath shape() const override;

  //! Advance the actor state
  void advance( int phase ) override;

  //! Clone the actor
  virtual Actor* clone( QGraphicsObject* parent = 0 ) const = 0;

signals:

  // Backend and frontend
  void healthChanged( const int current_health );
  void manaChanged( const int current_mana );
  void baseStatsChanged();
  void death();

public slots:

  //! Increment the base strength
  void incrementBaseStrength();

  //! Increment the base magic
  void incrementBaseMagic();

  //! Increment the base dexterity
  void incrementBaseDexterity();

  //! Increment the base vitality
  void incrementBaseVitality();

private slots:

  // Forward health changed signal in actor data to health changed signal
  void handleHealthChangedInActorData( const int current_health );

  // Forward mana changed signal in actor data to mana changed signal
  void handleManaChangedInActorData( const int current_mana );

  // Forward core stat incremented signal in actor data to base stats changed
  // signal
  void handleCoreStatIncrementedInActorData();

  // Forward health depeleted signal in actor data to death signal
  void handleHealthDepletedInActorData();

protected:

  //! Constructor
  Actor( ActorData* data, QGraphicsObject* parent = 0 );

  //! Get the actor data
  ActorData* getActorData();

  //! Get the actor data
  const ActorData* getActorData() const;

  //! Set the actor sprites
  void setActorSprites(
                 const std::shared_ptr<StateDirectionGameSpriteMap>& sprites );

  //! Paint the actor
  void paintImpl( QPainter* painter,
                  const QStyleOptionGraphicsItem* option,
                  QWidget* widget ) override;

private:

  // Connect actor data signals to actor slots
  void connectActorDataSignalsToActorSlots();

  // Disconnect actor slots from actor data signals
  void disconnectActorSlotsFromActorDataSignals();

  // The actor data
  std::shared_ptr<ActorData> d_data;
};

} // end QtD1 namespace

Q_DECLARE_METATYPE( QtD1::Actor::State )

#endif // end ACTOR_H

//---------------------------------------------------------------------------//
// end Actor.h
//---------------------------------------------------------------------------//
