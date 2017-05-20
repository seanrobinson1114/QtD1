//---------------------------------------------------------------------------//
//!
//! \file   SorcererData.h
//! \author Alex, Sean Robinson
//! \brief  Sorcerer data class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SORCERER_DATA_H
#define SORCERER_DATA_H

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
class SorcererData : public CharacterData
{
  Q_OBJECT

public:

  //! Constructor
  SorcererData( QObject* parent = 0 );

  //! Constructor
  SorcererData( const QString& name, QObject* parent = 0 );

  // Assignment operator
  SorcererData& operator=( const SorcererData& other_data );

  //! Destructor
  ~SorcererData()
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

  void connectStatChangeSignalToSorcererDataSlots();

  void calculateBaseChanceToHitWithMelee();

  void calculateBaseChanceToHitWithRanged();

  void calculateBaseChanceToHitWithSpell();

  void calculateBaseDamage();

  void calculateBaseHealth();

  void calculateBaseMana();

  // The sorcerer max health
  int d_base_health;

  // The sorcerer max mana
  int d_base_mana;

  // The sorcerer damage
  int d_base_damage;

  // The sorcerer armor class
  int d_base_armor_class;

  // The chance to hit with melee weapon
  qreal d_base_chance_to_hit_with_melee;

  // The chance to hit with ranged weapon
  qreal d_base_chance_to_hit_with_ranged;

  // The chance to hit with spell
  qreal d_base_chance_to_hit_with_spell;
};

} // end QtD1 namespace

#endif // end SORCERER_DATA_H

//---------------------------------------------------------------------------//
// end SorcererData.h
//---------------------------------------------------------------------------//
