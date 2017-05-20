//---------------------------------------------------------------------------//
//!
//! \file   SorcererData.cpp
//! \author Alex, Sean Robinson
//! \brief  The Sorcerer data class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "SorcererData.h"
#include "Character.h"

namespace QtD1{

// Constructor
SorcererData::SorcererData( QObject* parent )
  : SorcererData( "", parent )
{ /* ... */ }

SorcererData::SorcererData( const QString& name, QObject* parent )
  : CharacterData( name, Character::Sorcerer, parent ),
    d_base_health( 1 ),
    d_base_mana( 1 ),
    d_base_damage( 0 ),
    d_base_armor_class( 0 ),
    d_base_chance_to_hit_with_melee( 0.0 ),
    d_base_chance_to_hit_with_ranged( 0.0 ),
    d_base_chance_to_hit_with_spell( 0.0 )
{
  this->connectStatChangeSignalToSorcererDataSlots();
  this->handleLevelUp( 1 );
}

// Assignment operator
SorcererData& SorcererData::operator=( const SorcererData& other_data )
{
  if( this != &other_data )
  {
    // Copy the actor data
    CharacterData::operator=( other_data );

    // Copy the Sorcerer data
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
int SorcererData::getBaseHealth() const
{
  return d_base_health;
}

int SorcererData::getBaseMana() const
{
  return d_base_mana;
}

int SorcererData::getBaseDamage() const
{
  return d_base_damage;
}

int SorcererData::getBaseArmorClass() const
{
  return d_base_armor_class;
}

// Get the base percent chance to hit with melee
qreal SorcererData::getBaseChanceToHitWithMeleeWeapon() const
{
  return d_base_chance_to_hit_with_melee;
}

// Get the base percent chance to hit with ranged
qreal SorcererData::getBaseChanceToHitWithRangedWeapon() const
{
  return d_base_chance_to_hit_with_ranged;
}

// Get the base percent chance to hit with spell
qreal SorcererData::getBaseChanceToHitWithSpell() const
{
  return d_base_chance_to_hit_with_spell;
}

void SorcererData::handleStrengthChange( int )
{
  this->calculateBaseDamage();
}

void SorcererData::handleDexterityChange( int total_dexterity )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  d_base_armor_class = total_dexterity / 5;
}

void SorcererData::handleVitalityChange( int, int )
{
  this->calculateBaseHealth();
}

void SorcererData::handleMagicChange( int, int )
{
  this->calculateBaseMana();
  this->calculateBaseChanceToHitWithSpell();
}

void SorcererData::handleLevelUp( const int )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  this->calculateBaseChanceToHitWithSpell();
  this->calculateBaseDamage();
  this->calculateBaseHealth();
  this->calculateBaseMana();

  this->updateStats();
}

void SorcererData::connectStatChangeSignalToSorcererDataSlots()
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

void SorcererData::calculateBaseChanceToHitWithMelee()
{
  d_base_chance_to_hit_with_melee = std::min( 50.0 + this->getDexterity() / 2.0 + this->getLevel(), 100.0 );
}

void SorcererData::calculateBaseChanceToHitWithRanged()
{
  d_base_chance_to_hit_with_ranged = std::min( 50.0 + this->getDexterity() + this->getLevel(), 100.0 );
}

void SorcererData::calculateBaseChanceToHitWithSpell()
{
  d_base_chance_to_hit_with_spell = std::min( 50.0 + this->getMagic(), 100.0 );
}

void SorcererData::calculateBaseDamage()
{
  d_base_damage = this->getStrength() * this->getLevel() / 200;
}

void SorcererData::calculateBaseHealth()
{
  d_base_health = this->getVitality() + this->getLevel() + 9;
}

void SorcererData::calculateBaseMana()
{
  d_base_mana = 2 * this->getMagic() + 2 * this->getLevel() - 2;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SorcererData.cpp
//---------------------------------------------------------------------------//
