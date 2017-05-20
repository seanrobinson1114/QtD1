//---------------------------------------------------------------------------//
//!
//! \file   WarriorData.h
//! \author Alex, Sean Robinson
//! \brief  Warrior data class declaration
//!
//---------------------------------------------------------------------------//

#ifndef WARRIOR_DATA_H
#define WARRIOR_DATA_H

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QObject>
#include <QString>

// QtD1 Includes
#include "CharacterData.h"

namespace QtD1{

//! The character data
class WarriorData : public CharacterData
{
  Q_OBJECT

public:

  //! Constructor
  WarriorData( QObject* parent = 0 );

  //! Constructor
  WarriorData( const QString& name, QObject* parent = 0 );

  // Assignment operator
  WarriorData& operator=( const WarriorData& other_data );

  //! Destructor
  ~WarriorData()
  { /* ... */ }

  //! Get the max health
  int getBaseHealth() const override;

  //! Get the max mana
  int getBaseMana() const override;

  //! Get base the damage
  int getBaseDamage() const override;

  //! Get the base armor class
  int getBaseArmorClass() const override;

  //! Get the base percent chance to hit with melee
  qreal getBaseChanceToHitWithMeleeWeapon() const override;

  //! Get the base percent chance to hit with ranged
  qreal getBaseChanceToHitWithRangedWeapon() const override;

  //! Get the base percent chance to hit with spell
  qreal getBaseChanceToHitWithSpell() const override;

private slots:

  void handleStrengthChange( int total_strength );
  void handleDexterityChange( int total_dexterity );
  void handleVitalityChange( int character_vitality, int inventory_vitality );
  void handleMagicChange( int character_magic, int inventory_magic );
  void handleLevelUp( const int level );

private:

  void connectStatChangeSignalToWarriorDataSlots();

  void calculateBaseChanceToHitWithMelee();

  void calculateBaseChanceToHitWithRanged();

  void calculateBaseChanceToHitWithSpell();

  void calculateBaseDamage();

  void calculateBaseHealth();

  void calculateBaseMana();

  // The warrior max health
  int d_base_health;

  // The warrior max mana
  int d_base_mana;

  // The warrior damage
  int d_base_damage;

  // The warrior armor class
  int d_base_armor_class;

  // The chance to hit with melee weapon
  qreal d_base_chance_to_hit_with_melee;

  // The chance to hit with ranged weapon
  qreal d_base_chance_to_hit_with_ranged;

  // The chance to hit with spell
  qreal d_base_chance_to_hit_with_spell;
};

} // end QtD1 namespace

#endif // end WARRIOR_DATA_H

//---------------------------------------------------------------------------//
// end WarriorData.h
//---------------------------------------------------------------------------//
