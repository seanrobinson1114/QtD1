//---------------------------------------------------------------------------//
//!
//! \file   CharacterFrontendProxy.h
//! \author Alex Robinson
//! \brief  The character frontend proxy class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CHARACTER_FRONTEND_PROXY_H
#define CHARACTER_FRONTEND_PROXY_H

// Qt Includes
#include <QObject>

// QtD1 Includes
#include "QMLRegistrationHelper.h"
#include "Character.h"

namespace QtD1{

//! The character frontend proxy
class CharacterFrontendProxy : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ getName)
  Q_PROPERTY(int type READ getType)
  Q_PROPERTY(int level READ getLevel)
  Q_PROPERTY(int experience READ getExperience)
  Q_PROPERTY(int nextLevelExperience READ getNextLevelExperienceThreshold)
  Q_PROPERTY(int gold READ getGold)
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
  Q_PROPERTY(qreal chanceToHit READ getChanceToHitWithMeleeWeapon)
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "CharacterBackend" )

public:
  
  //! Constructor
  CharacterFrontendProxy( QObject* parent = 0 );

  //! Destructor
  ~CharacterFrontendProxy()
  { /* ... */ }

  //! Connect to the backend
  static void connectToBackend( QDeclarativeView* frontend_widget,
                                Character* character_backend );
    
  //! Get the character name
  QString getName() const;

  //! Get the character type
  int getType() const;

  //! Get the character level
  int getLevel() const;

  //! Get the character experience
  int getExperience() const;

  //! Get the next level character experience
  int getNextLevelExperienceThreshold() const;

  //! Get the amount of gold the character is holding
  int getGold() const;

  //! Get the base strength
  int getBaseStrength() const;

  //! Get the strength
  int getStrength() const;

  //! Get the base magic
  int getBaseMagic() const;

  //! Get the magic
  int getMagic() const;

  //! Get the base dexterity
  int getBaseDexterity() const;

  //! Get the dexterity
  int getDexterity() const;

  //! Get the base vitality
  int getBaseVitality() const;

  //! Get the vitality
  int getVitality() const;

  //! Get the base health
  int getBaseHealth() const;

  //! Get the max health
  int getMaxHealth() const;

  //! Get the health
  int getHealth() const;

  //! Get the base mana
  int getBaseMana() const;

  //! Get the max mana
  int getMaxMana() const;

  //! Get the mana
  int getMana() const;

  //! Get the magic resistance
  qreal getMagicResistance() const;

  //! Get the fire resistance
  qreal getFireResistance() const;

  //! Get the lightning resistance
  qreal getLightningResistance() const;

  //! Get the armor class
  int getArmorClass() const;

  //! Get the minimum damage
  int getMinimumDamage() const;

  //! Get the maximum damage
  int getMaximumDamage() const;

  //! Get the chance to hit with melee weapon
  qreal getChanceToHitWithMeleeWeapon() const;

signals:

  void healthChanged( const int current_health );
  void manaChanged( const int current_mana );
  void baseStatsChanged();
  void statsChanged();
  void levelUp( const int new_level );
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

  // Forward health changed in character backend to frontend
  void forwardHealthChangedToFrontend( const int current_health );

  // Forward mana changed in character backend to frontend
  void forwardManaChangedToFrontend( const int current_mana );

  // Forward base stats changed in character backend to frontend
  void forwardBaseStatsChangedToFrontend();

  // Forward stats changed in character backend to frontend
  void forwardStatsChangedToFrontend();

  // Forward level up to frontend
  void forwardLevelUpToFrontend( const int new_level );

  // Forward death to frontend
  void forwardDeathToFrontend();

private:

  // Get the object name
  static QString objectName();

  // The character backend
  Character* d_character_backend;
};
  
} // end QtD1 namespace

#endif // end CHARACTER_FRONTEND_PROXY_H

//---------------------------------------------------------------------------//
// end CharacterFrontendProxy.h
//---------------------------------------------------------------------------//
