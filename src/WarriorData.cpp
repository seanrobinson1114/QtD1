//---------------------------------------------------------------------------//
//!
//! \file   WarriorData.cpp
//! \author Alex, Sean Robinson
//! \brief  The warrior data class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "WarriorData.h"
#include "Character.h"

namespace QtD1{

// Constructor
WarriorData::WarriorData( QObject* parent )
  : WarriorData( "", parent )
{ /* ... */ }

WarriorData::WarriorData( const QString& name, QObject* parent )
  : CharacterData( name, Character::Warrior, parent ),
    d_base_health( 1 ),
    d_base_mana( 1 ),
    d_base_damage( 0 ),
    d_base_armor_class( 0 ),
    d_base_chance_to_hit_with_melee( 0.0 ),
    d_base_chance_to_hit_with_ranged( 0.0 ),
    d_base_chance_to_hit_with_spell( 0.0 )
{
  this->connectStatChangeSignalToWarriorDataSlots();
  this->handleLevelUp( 1 );
}

// Assignment operator
WarriorData& WarriorData::operator=( const WarriorData& other_data )
{
  if( this != &other_data )
  {
    // Copy the actor data
    CharacterData::operator=( other_data );

    // Copy the warrior data
    d_base_health = other_data.d_base_health;
    d_base_mana = other_data.d_base_mana;
    d_base_damage = other_data.d_base_damage;
    d_base_armor_class = other_data.d_base_armor_class;
    d_base_chance_to_hit_with_melee = other_data.d_base_chance_to_hit_with_melee;
    d_base_chance_to_hit_with_ranged = other_data.d_base_chance_to_hit_with_ranged;
    d_base_chance_to_hit_with_spell = other_data.d_base_chance_to_hit_with_spell;
  }

  return *this;
}

// Get the base health
int WarriorData::getBaseHealth() const
{
  return d_base_health;
}

int WarriorData::getBaseMana() const
{
  return d_base_mana;
}

int WarriorData::getBaseDamage() const
{
  return d_base_damage;
}

int WarriorData::getBaseArmorClass() const
{
  return d_base_armor_class;
}

// Get the base percent chance to hit with melee
qreal WarriorData::getBaseChanceToHitWithMeleeWeapon() const
{
  return d_base_chance_to_hit_with_melee;
}

// Get the base percent chance to hit with ranged
qreal WarriorData::getBaseChanceToHitWithRangedWeapon() const
{
  return d_base_chance_to_hit_with_ranged;
}

// Get the base percent chance to hit with spell
qreal WarriorData::getBaseChanceToHitWithSpell() const
{
  return d_base_chance_to_hit_with_spell;
}

void WarriorData::handleStrengthChange( int )
{
  this->calculateBaseDamage();
}

void WarriorData::handleDexterityChange( int total_dexterity )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  d_base_armor_class = total_dexterity / 5;
}

void WarriorData::handleVitalityChange( int, int )
{
  this->calculateBaseHealth();
}

void WarriorData::handleMagicChange( int, int )
{
  this->calculateBaseMana();
  this->calculateBaseChanceToHitWithSpell();
}

void WarriorData::handleLevelUp( const int )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  this->calculateBaseChanceToHitWithSpell();
  this->calculateBaseDamage();
  this->calculateBaseHealth();
  this->calculateBaseMana();

  this->updateStats();
}

void WarriorData::connectStatChangeSignalToWarriorDataSlots()
{
  QObject::connect( this, SIGNAL( strengthChanged( int ) ),
                    this, SLOT( handleStrengthChange( int ) ) );
  QObject::connect( this, SIGNAL( dexterityChanged( int ) ),
                    this, SLOT( handleDexterityChange( int ) ) );
  QObject::connect( this, SIGNAL( vitalityChanged( int, int ) ),
                    this, SLOT( handleVitalityChange( int, int ) ) );
  QObject::connect( this, SIGNAL( magicChanged( int, int ) ),
                    this, SLOT( handleMagicChange( int, int ) ) );
  QObject::connect( this, SIGNAL( levelUp( const int ) ),
                    this, SLOT( handleLevelUp( const int ) ) );
}

void WarriorData::calculateBaseChanceToHitWithMelee()
{
  d_base_chance_to_hit_with_melee = std::min( 50.0 + this->getDexterity() / 2.0 + this->getLevel(), 100.0 );
}

void WarriorData::calculateBaseChanceToHitWithRanged()
{
  d_base_chance_to_hit_with_ranged = std::min( 50.0 + this->getDexterity() + this->getLevel(), 100.0 );
}

void WarriorData::calculateBaseChanceToHitWithSpell()
{
  d_base_chance_to_hit_with_spell = std::min( 50.0 + this->getMagic(), 100.0 );
}

void WarriorData::calculateBaseDamage()
{
  d_base_damage = this->getStrength() * this->getLevel() / 100;
}

void WarriorData::calculateBaseHealth()
{
  d_base_health = 2 * this->getVitality() + 2 * this->getLevel() + 18;
}

void WarriorData::calculateBaseMana()
{
  d_base_mana = this->getMagic() + this->getLevel() - 1;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end WarriorData.cpp
//---------------------------------------------------------------------------//
