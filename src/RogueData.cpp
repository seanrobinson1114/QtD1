//---------------------------------------------------------------------------//
//!
//! \file   RogueData.cpp
//! \author Alex, Sean Robinson
//! \brief  The rogue data class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "RogueData.h"
#include "Character.h"

namespace QtD1{

// Constructor
RogueData::RogueData( QObject* parent )
  : RogueData( "", parent )
{ /* ... */ }

RogueData::RogueData( const QString& name, QObject* parent )
  : CharacterData( name, Character::Rogue, parent ),
    d_base_health( 1 ),
    d_base_mana( 1 ),
    d_base_damage( 0 ),
    d_base_armor_class( 0 ),
    d_base_chance_to_hit_with_melee( 0.0 ),
    d_base_chance_to_hit_with_ranged( 0.0 ),
    d_base_chance_to_hit_with_spell( 0.0 )
{
  this->connectStatChangeSignalToRogueDataSlots();
  this->handleLevelUp( 1 );
}

// Assignment operator
RogueData& RogueData::operator=( const RogueData& other_data )
{
  if( this != &other_data )
  {
    // Copy the actor data
    CharacterData::operator=( other_data );

    // Copy the Rogue data
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
int RogueData::getBaseHealth() const
{
  return d_base_health;
}

int RogueData::getBaseMana() const
{
  return d_base_mana;
}

int RogueData::getBaseDamage() const
{
  return d_base_damage;
}

int RogueData::getBaseArmorClass() const
{
  return d_base_armor_class;
}

// Get the base percent chance to hit with melee
qreal RogueData::getBaseChanceToHitWithMeleeWeapon() const
{
  return d_base_chance_to_hit_with_melee;
}

// Get the base percent chance to hit with ranged
qreal RogueData::getBaseChanceToHitWithRangedWeapon() const
{
  return d_base_chance_to_hit_with_ranged;
}

// Get the base percent chance to hit with spell
qreal RogueData::getBaseChanceToHitWithSpell() const
{
  return d_base_chance_to_hit_with_spell;
}

void RogueData::handleStrengthChange( int )
{
  this->calculateBaseDamage();
}

void RogueData::handleDexterityChange( int total_dexterity )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  d_base_armor_class = total_dexterity / 5;
}

void RogueData::handleVitalityChange( int, int )
{
  this->calculateBaseHealth();
}

void RogueData::handleMagicChange( int, int )
{
  this->calculateBaseMana();
  this->calculateBaseChanceToHitWithSpell();
}

void RogueData::handleLevelUp( const int )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  this->calculateBaseChanceToHitWithSpell();
  this->calculateBaseDamage();
  this->calculateBaseHealth();
  this->calculateBaseMana();

  this->updateStats();
}

void RogueData::connectStatChangeSignalToRogueDataSlots()
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

void RogueData::calculateBaseChanceToHitWithMelee()
{
  d_base_chance_to_hit_with_melee = std::min( 50.0 + this->getDexterity() / 2.0 + this->getLevel(), 100.0 );
}

void RogueData::calculateBaseChanceToHitWithRanged()
{
  d_base_chance_to_hit_with_ranged = std::min( 50.0 + this->getDexterity() + this->getLevel(), 100.0 );
}

void RogueData::calculateBaseChanceToHitWithSpell()
{
  d_base_chance_to_hit_with_spell = std::min( 50.0 + this->getMagic(), 100.0 );
}

void RogueData::calculateBaseDamage()
{
  d_base_damage = (this->getStrength() + this->getDexterity()) * this->getLevel() / 200;
}

void RogueData::calculateBaseHealth()
{
  d_base_health = 1 * this->getBaseVitality() + 1.5 * this->getInventory().calculateVitalityModifier() + 2 * this->getLevel() + 23;
}

void RogueData::calculateBaseMana()
{
  d_base_mana = this->getBaseMagic() + 1.5 * this->getInventory().calculateMagicModifier() + 2 * this->getLevel() + 5;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end RogueData.cpp
//---------------------------------------------------------------------------//
