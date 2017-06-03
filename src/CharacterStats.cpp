//---------------------------------------------------------------------------//
//!
//! \file   CharacterStats.cpp
//! \author Sean Robinson, Alex Robinson
//! \brief  The character stats menu class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <utility>

// Qt Includes
#include <QImageReader>
#include <QShowEvent>

// QtD1 Includes
#include "CharacterStats.h"
#include "Character.h"

namespace QtD1{

// Initialize static member data
const QString CharacterStats::s_style_sheet( "background-color: transparent; color: white; font-family: monospace; font-size: 14px" );
const QSize CharacterStats::s_name_type_size( 135, 15 );
const QSize CharacterStats::s_core_stats_size( 36, 18 );
const QSize CharacterStats::s_exp_gold_size( 90, 18 );
const QSize CharacterStats::s_advanced_stats_size( 48, 18 );

// Constructor
CharacterStats::CharacterStats( Character* character, QWidget* parent )
  : QWidget( parent ),
    d_character( character ),
    d_character_name( NULL ),
    d_character_type( NULL ),
    d_character_level( NULL ),
    d_character_experience( NULL ),
    d_character_next_level_experience_threshold( NULL ),
    d_character_gold( NULL ),
    d_character_base_strength( NULL ),
    d_character_current_strength( NULL ),
    d_character_base_magic( NULL ),
    d_character_current_magic( NULL ),
    d_character_base_dexterity( NULL ),
    d_character_current_dexterity( NULL ),
    d_character_base_vitality( NULL ),
    d_character_current_vitality( NULL ),
    d_character_base_health( NULL ),
    d_character_current_health( NULL ),
    d_character_base_mana( NULL ),
    d_character_current_mana( NULL ),
    d_character_magic_resistance( NULL ),
    d_character_fire_resistance( NULL ),
    d_character_lightning_resistance( NULL ),
    d_character_armor_class( NULL ),
    d_character_damage( NULL ),
    d_character_chance_to_hit( NULL )
{
  // Load the character stats menu image
  QImage background_image( "/data/char.cel+levels/towndata/town.pal" );
  QLabel* character_stats_image = new QLabel( this );
  character_stats_image->setPixmap( QPixmap::fromImage( background_image ) );
  character_stats_image->setFixedSize( background_image.size() );
  this->setFixedSize( character_stats_image->size() );

  // Connect to the character stats changed signals
  QObject::connect( d_character, SIGNAL( statsChanged() ),
                    this, SLOT( updateLabels() ) );
  QObject::connect( d_character, SIGNAL( healthChanged(const int) ),
                    this, SLOT( updateLabels() ) );
  QObject::connect( d_character, SIGNAL( manaChanged(const int) ),
                    this, SLOT( updateLabels() ) );

  // Create the labels
  this->createLabels();
}

// Get the character name
QString CharacterStats::getName() const
{
  if( d_character )
    return d_character->getName();
  else
    return QString();
}

// Get the character type
int CharacterStats::getType() const
{
  if( d_character )
    return d_character->getType();
  else
    return 0;
}

// Get the character level
int CharacterStats::getLevel() const
{
  if( d_character )
    return d_character->getLevel();
  else
    return 0;
}

// Get the character experience
int CharacterStats::getExperience() const
{
  if( d_character )
    return d_character->getExperience();
  else
    return 0;
}

// Get the next level character experience
int CharacterStats::getNextLevelExperienceThreshold() const
{
  if( d_character )
    return d_character->getNextLevelExperienceThreshold();
  else
    return 0;
}

// Get the amount of gold the character is holding
int CharacterStats::getGold() const
{
  if( d_character )
    return d_character->getGold();
  else
    return 0;
}

// Get the base strength
int CharacterStats::getBaseStrength() const
{
  if( d_character )
    return d_character->getBaseStrength();
  else
    return 0;
}

// Get the strength
int CharacterStats::getStrength() const
{
  if( d_character )
    return d_character->getStrength();
  else
    return 0;
}

// Get the base magic
int CharacterStats::getBaseMagic() const
{
  if( d_character )
    return d_character->getBaseMagic();
  else
    return 0;
}

// Get the magic
int CharacterStats::getMagic() const
{
  if( d_character )
    return d_character->getMagic();
  else
    return 0;
}

// Get the base dexterity
int CharacterStats::getBaseDexterity() const
{
  if( d_character )
    return d_character->getBaseDexterity();
  else
    return 0;
}

// Get the dexterity
int CharacterStats::getDexterity() const
{
  if( d_character )
    return d_character->getDexterity();
  else
    return 0;
}

// Get the base vitality
int CharacterStats::getBaseVitality() const
{
  if( d_character )
    return d_character->getBaseVitality();
  else
    return 0;
}

// Get the vitality
int CharacterStats::getVitality() const
{
  if( d_character )
    return d_character->getVitality();
  else
    return 0;
}

// Get the base health
int CharacterStats::getBaseHealth() const
{
  if( d_character )
    return d_character->getBaseHealth();
  else
    return 0;
}

// Get the max health
int CharacterStats::getMaxHealth() const
{
  if( d_character )
    return d_character->getMaxHealth();
  else
    return 0;
}

// Get the health
int CharacterStats::getHealth() const
{
  if( d_character )
    return d_character->getHealth();
  else
    return 0;
}

// Get the base mana
int CharacterStats::getBaseMana() const
{
  if( d_character )
    return d_character->getBaseMana();
  else
    return 0;
}

// Get the max mana
int CharacterStats::getMaxMana() const
{
  if( d_character )
    return d_character->getMaxMana();
  else
    return 0;
}

// Get the mana
int CharacterStats::getMana() const
{
  if( d_character )
    return d_character->getMana();
  else
    return 0;
}

// Get the magic resistance
qreal CharacterStats::getMagicResistance() const
{
  if( d_character )
    return d_character->getMagicResistance();
  else
    return 0.0;
}

// Get the fire resistance
qreal CharacterStats::getFireResistance() const
{
  if( d_character )
    return d_character->getFireResistance();
  else
    return 0.0;
}

// Get the lightning resistance
qreal CharacterStats::getLightningResistance() const
{
  if( d_character )
    return d_character->getLightningResistance();
  else
    return 0.0;
}

// Get the armor class
int CharacterStats::getArmorClass() const
{
  if( d_character )
    return d_character->getArmorClass();
  else
    return 0;
}

// Get the minimum damage
int CharacterStats::getMinimumDamage() const
{
  if( d_character )
    return d_character->getMinimumDamage();
  else
    return 0;
}

// Get the maximum damage
int CharacterStats::getMaximumDamage() const
{
  if( d_character )
    return d_character->getMaximumDamage();
  else
    return 0;
}

// Get the chance to hit with melee weapon
qreal CharacterStats::getChanceToHitWithMeleeWeapon() const
{
  if( d_character )
    return d_character->getChanceToHitWithMeleeWeapon();
  else
    return 0.0;
}

// Update the labels
void CharacterStats::updateLabels()
{
  d_character_name->setText( this->getName() );
  switch( this->getType() )
  {
    case Character::Warrior:
      d_character_type->setText( "Warrior" );
      break;
    case Character::Rogue:
      d_character_type->setText( "Rogue" );
      break;
    case Character::Sorcerer:
      d_character_type->setText( "Sorcerer" );
      break;
    default:
      break;
  }
  d_character_level->setText( QString::number( this->getLevel() ) );
  d_character_experience->setText( QString::number( this->getExperience() ) );
  d_character_next_level_experience_threshold->setText( QString::number( this->getNextLevelExperienceThreshold() ) );
  d_character_gold->setText( QString::number( this->getGold() ) );
  d_character_base_strength->setText( QString::number( this->getBaseStrength() ) );
  d_character_current_strength->setText( QString::number( this->getStrength() ) );
  d_character_base_magic->setText( QString::number( this->getBaseMagic() ) );
  d_character_current_magic->setText( QString::number( this->getMagic() ) );
  d_character_base_dexterity->setText( QString::number( this->getBaseDexterity() ) );
  d_character_current_dexterity->setText( QString::number( this->getDexterity() ) );
  d_character_base_vitality->setText( QString::number( this->getBaseVitality() ) );
  d_character_current_vitality->setText( QString::number( this->getVitality() ) );
  d_character_base_health->setText( QString::number( this->getBaseHealth() ) );
  d_character_current_health->setText( QString::number( this->getHealth() ) );
  d_character_base_mana->setText( QString::number( this->getBaseMana() ) );
  d_character_current_mana->setText( QString::number( this->getMana() ) );
  d_character_magic_resistance->setText( QString::number( this->getMagicResistance() ) );
  d_character_fire_resistance->setText( QString::number( this->getFireResistance() ) );
  d_character_lightning_resistance->setText( QString::number( this->getLightningResistance() ) );
  d_character_armor_class->setText( QString::number( this->getArmorClass() ) );
  d_character_damage->setText( QString::number( this->getMinimumDamage() ) + "-" + QString::number( this->getMaximumDamage() ) );
  d_character_chance_to_hit->setText( QString::number( this->getChanceToHitWithMeleeWeapon() ) + "%" );
}

// Increment the base strength
void CharacterStats::incrementBaseStrength()
{
  if( d_character )
    d_character->incrementBaseStrength();
  else
  {
    qWarning( "Cannot increment the base strength because the character "
              "backend has not been connected!" );
  }
}

// Increment the base magic
void CharacterStats::incrementBaseMagic()
{
  if( d_character )
    d_character->incrementBaseMagic();
  else
  {
    qWarning( "Cannot increment the base magic because the character "
              "backend has not been connected!" );
  }
}

// Increment the base dexterity
void CharacterStats::incrementBaseDexterity()
{
  if( d_character )
    d_character->incrementBaseDexterity();
  else
  {
    qWarning( "Cannot increment the base dexterity because the character "
              "backend has not been connected!" );
  }
}

// Increment the base vitality
void CharacterStats::incrementBaseVitality()
{
  if( d_character )
    d_character->incrementBaseVitality();
  else
  {
    qWarning( "Cannot increment the base vitality because the character "
              "backend has not been connected!" );
  }
}

// Create and place the dynamic labels
void CharacterStats::createLabels()
{
  // Character name
  d_character_name = new QLabel( this );
  d_character_name->move( 20, 18 );
  d_character_name->resize( s_name_type_size );
  d_character_name->setStyleSheet( s_style_sheet );
  d_character_name->setAlignment( Qt::AlignCenter );

  // Character type
  d_character_type = new QLabel( this );
  d_character_type->move( 168, 18 );
  d_character_type->resize( s_name_type_size );
  d_character_type->setStyleSheet( s_style_sheet );
  d_character_type->setAlignment( Qt::AlignCenter );

  // Character level
  d_character_level = new QLabel( this );
  d_character_level->move( 63, 56 );
  d_character_level->resize( 47, 18 );
  d_character_level->setStyleSheet( s_style_sheet );
  d_character_level->setAlignment( Qt::AlignCenter );

  // Character base strength
  d_character_base_strength = new QLabel( this );
  d_character_base_strength->move( 94, 141 );
  d_character_base_strength->resize( s_core_stats_size );
  d_character_base_strength->setStyleSheet( s_style_sheet );
  d_character_base_strength->setAlignment( Qt::AlignCenter );

  // Character current strength
  d_character_current_strength = new QLabel( this );
  d_character_current_strength->move( 140, 141 );
  d_character_current_strength->resize( s_core_stats_size );
  d_character_current_strength->setStyleSheet( s_style_sheet );
  d_character_current_strength->setAlignment( Qt::AlignCenter );

  // Character base magic
  d_character_base_magic = new QLabel( this );
  d_character_base_magic->move( 94, 169 );
  d_character_base_magic->resize( s_core_stats_size );
  d_character_base_magic->setStyleSheet( s_style_sheet );
  d_character_base_magic->setAlignment( Qt::AlignCenter );

  // Character current magic
  d_character_current_magic = new QLabel( this );
  d_character_current_magic->move( 140, 169 );
  d_character_current_magic->resize( s_core_stats_size );
  d_character_current_magic->setStyleSheet( s_style_sheet );
  d_character_current_magic->setAlignment( Qt::AlignCenter );

  // Character base dexterity
  d_character_base_dexterity = new QLabel( this );
  d_character_base_dexterity->move( 94, 197 );
  d_character_base_dexterity->resize( s_core_stats_size );
  d_character_base_dexterity->setStyleSheet( s_style_sheet );
  d_character_base_dexterity->setAlignment( Qt::AlignCenter );

  // Character current dexterity
  d_character_current_dexterity = new QLabel( this );
  d_character_current_dexterity->move( 140, 197 );
  d_character_current_dexterity->resize( s_core_stats_size );
  d_character_current_dexterity->setStyleSheet( s_style_sheet );
  d_character_current_dexterity->setAlignment( Qt::AlignCenter );

  // Character base vitality
  d_character_base_vitality = new QLabel( this );
  d_character_base_vitality->move( 94, 225 );
  d_character_base_vitality->resize( s_core_stats_size );
  d_character_base_vitality->setStyleSheet( s_style_sheet );
  d_character_base_vitality->setAlignment( Qt::AlignCenter );

  // Character current vitality
  d_character_current_vitality = new QLabel( this );
  d_character_current_vitality->move( 140, 225 );
  d_character_current_vitality->resize( s_core_stats_size );
  d_character_current_vitality->setStyleSheet( s_style_sheet );
  d_character_current_vitality->setAlignment( Qt::AlignCenter );

  // Character base health
  d_character_base_health = new QLabel( this );
  d_character_base_health->move( 94, 290 );
  d_character_base_health->resize( s_core_stats_size );
  d_character_base_health->setStyleSheet( s_style_sheet );
  d_character_base_health->setAlignment( Qt::AlignCenter );

  // Character current health
  d_character_current_health = new QLabel( this );
  d_character_current_health->move( 140, 290 );
  d_character_current_health->resize( s_core_stats_size );
  d_character_current_health->setStyleSheet( s_style_sheet );
  d_character_current_health->setAlignment( Qt::AlignCenter );

  // Character base mana
  d_character_base_mana = new QLabel( this );
  d_character_base_mana->move( 94, 318 );
  d_character_base_mana->resize( s_core_stats_size );
  d_character_base_mana->setStyleSheet( s_style_sheet );
  d_character_base_mana->setAlignment( Qt::AlignCenter );

  // Character base mana
  d_character_current_mana = new QLabel( this );
  d_character_current_mana->move( 140, 318 );
  d_character_current_mana->resize( s_core_stats_size );
  d_character_current_mana->setStyleSheet( s_style_sheet );
  d_character_current_mana->setAlignment( Qt::AlignCenter );

  // Character experience
  d_character_experience = new QLabel( this );
  d_character_experience->move( 213, 55 );
  d_character_experience->resize( s_exp_gold_size );
  d_character_experience->setStyleSheet( s_style_sheet );
  d_character_experience->setAlignment( Qt::AlignCenter );

  // Character next level experience threshold
  d_character_next_level_experience_threshold = new QLabel( this );
  d_character_next_level_experience_threshold->move( 213, 83 );
  d_character_next_level_experience_threshold->resize( s_exp_gold_size );
  d_character_next_level_experience_threshold->setStyleSheet( s_style_sheet );
  d_character_next_level_experience_threshold->setAlignment( Qt::AlignCenter );

  // Character gold amount
  d_character_gold = new QLabel( this );
  d_character_gold->move( 213, 132 );
  d_character_gold->resize( s_exp_gold_size );
  d_character_gold->setStyleSheet( s_style_sheet );
  d_character_gold->setAlignment( Qt::AlignCenter );

  // Character armor class
  d_character_armor_class = new QLabel( this );
  d_character_armor_class->move( 255, 168 );
  d_character_armor_class->resize( s_advanced_stats_size );
  d_character_armor_class->setStyleSheet( s_style_sheet );
  d_character_armor_class->setAlignment( Qt::AlignCenter );

  // Character melee chance to hit
  d_character_chance_to_hit = new QLabel( this );
  d_character_chance_to_hit->move( 255, 196 );
  d_character_chance_to_hit->resize( s_advanced_stats_size );
  d_character_chance_to_hit->setStyleSheet( s_style_sheet );
  d_character_chance_to_hit->setAlignment( Qt::AlignCenter );

  // Character damage range
  d_character_damage = new QLabel( this );
  d_character_damage->move( 255, 224 );
  d_character_damage->resize( s_advanced_stats_size );
  d_character_damage->setStyleSheet( s_style_sheet );
  d_character_damage->setAlignment( Qt::AlignCenter );

  // Character magic resistance
  d_character_magic_resistance = new QLabel( this );
  d_character_magic_resistance->move( 255, 262 );
  d_character_magic_resistance->resize( s_advanced_stats_size );
  d_character_magic_resistance->setStyleSheet( s_style_sheet );
  d_character_magic_resistance->setAlignment( Qt::AlignCenter );

  // Character fire resistance
  d_character_fire_resistance = new QLabel( this );
  d_character_fire_resistance->move( 255, 290 );
  d_character_fire_resistance->resize( s_advanced_stats_size );
  d_character_fire_resistance->setStyleSheet( s_style_sheet );
  d_character_fire_resistance->setAlignment( Qt::AlignCenter );

  // Character lightning resistance
  d_character_lightning_resistance = new QLabel( this );
  d_character_lightning_resistance->move( 255, 318 );
  d_character_lightning_resistance->resize( s_advanced_stats_size );
  d_character_lightning_resistance->setStyleSheet( s_style_sheet );
  d_character_lightning_resistance->setAlignment( Qt::AlignCenter );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CharacterStats.cpp
//---------------------------------------------------------------------------//
