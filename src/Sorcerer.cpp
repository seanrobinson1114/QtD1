//---------------------------------------------------------------------------//
//!
//! \file   Sorcerer.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The sorcerer class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Sorcerer.h"
#include "SorcererInventory.h"
#include "SorcererSpellBook.h"

namespace QtD1{

// Initialize static member data
Sorcerer::AssetStateMap Sorcerer::s_asset_state_map;

// Get the asset state map
const Sorcerer::AssetStateMap& Sorcerer::getAssetStateMap()
{
  // Just-in-time initialization
  if( Sorcerer::s_asset_state_map.size() == 0 )
    Sorcerer::initializeAssetStateMap();

  return Sorcerer::s_asset_state_map;
}

// Constructor
/*! \details This constructor should only be used by the qml engine.
 */
Sorcerer::Sorcerer( QGraphicsObject* parent )
  : Sorcerer( "", parent )
{
  // When created by the QML engine no sprites will be loaded
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Copy constructor
/*! \details This constructor should only be used by the QML engine.
 */
Sorcerer::Sorcerer( const Sorcerer& other_sorcerer )
  : Character( other_sorcerer ),
    d_base_health( other_sorcerer.d_base_health ),
    d_base_mana( other_sorcerer.d_base_mana ),
    d_base_damage( other_sorcerer.d_base_damage ),
    d_base_armor_class( other_sorcerer.d_base_armor_class ),
    d_base_chance_to_hit_with_melee( other_sorcerer.d_base_chance_to_hit_with_melee ),
    d_base_chance_to_hit_with_ranged( other_sorcerer.d_base_chance_to_hit_with_ranged ),
    d_base_chance_to_hit_with_spell( other_sorcerer.d_base_chance_to_hit_with_spell )
{
  // When created by the QML engine no sprites will be loaded
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Constructor
Sorcerer::Sorcerer( const QString& name, QGraphicsObject* parent )
  : Character( name, new SorcererInventory, new SorcererSpellBook, parent )
{
  this->connectStatChangeSignalToSorcererSlots();
  this->initializeStats();
}

// Get the character type
Character::Type Sorcerer::getType() const
{
  return Character::Sorcerer;
}

// Get the sorcerer description
QString Sorcerer::getDescriptionText() const
{
  return QString( "I am a sorcerer!" );
}

// Get the base health
int Sorcerer::getBaseHealth() const
{
  return d_base_health;
}

int Sorcerer::getBaseMana() const
{
  return d_base_mana;
}

int Sorcerer::getBaseDamage() const
{
  return d_base_damage;
}

int Sorcerer::getBaseArmorClass() const
{
  return d_base_armor_class;
}

// Get the base percent chance to hit with melee
qreal Sorcerer::getBaseChanceToHitWithMeleeWeapon() const
{
  return d_base_chance_to_hit_with_melee;
}

// Get the base percent chance to hit with ranged
qreal Sorcerer::getBaseChanceToHitWithRangedWeapon() const
{
  return d_base_chance_to_hit_with_ranged;
}

// Get the base percent chance to hit with spell
qreal Sorcerer::getBaseChanceToHitWithSpell() const
{
  return d_base_chance_to_hit_with_spell;
}

// Get the number of image assets used by the object
int Sorcerer::getNumberOfImageAssets() const
{
  return Sorcerer::getAssetStateMap().size();
}

// Get the image asset names used by the object
void Sorcerer::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  Sorcerer::AssetStateMap::const_iterator asset_state_it, asset_state_end;
  asset_state_it = Sorcerer::getAssetStateMap().begin();
  asset_state_end = Sorcerer::getAssetStateMap().end();

  while( asset_state_it != asset_state_end )
  {
    image_asset_names.insert( asset_state_it.key() );

    ++asset_state_it;
  }
}

// Check if an image asset is used
bool Sorcerer::isImageAssetUsed( const QString& image_asset_name ) const
{
  return Sorcerer::getAssetStateMap().find( image_asset_name ) !=
    Sorcerer::getAssetStateMap().end();
}

// Get the states associated with the image asset
const Character::States& Sorcerer::getImageAssetStates(
                                        const QString& image_asset_name ) const
{
  AssetStateMap::const_iterator asset_state_it =
    Sorcerer::getAssetStateMap().find( image_asset_name );

  if( asset_state_it == Sorcerer::getAssetStateMap().end() )
  {
    qFatal( "Sorcerer Error: Cannot get image asset states because image asset "
            "%s is not used by the Sorcerer!",
            image_asset_name.toStdString().c_str() );
  }

  return asset_state_it.value();
}

// Initialize sorcerer stats
void Sorcerer::initializeStats()
{
  this->setBaseStrength( 15 );
  this->setBaseMagic( 35 );
  this->setBaseDexterity( 15 );
  this->setBaseVitality( 15 );

  this->handleLevelUp( 1 );

  this->restoreHealth();
  this->restoreMana();
}

// Get the number of sprite sheet frames per direction
int Sorcerer::getSpriteSheetFramesPerDirection( const States& states ) const
{
  if( states.in_town )
  {
    if( states.actor_state == Actor::Standing )
      return 20;
    else if( states.actor_state == Actor::Walking )
      return 8;
    else
    {
      qFatal( "Sorcerer Error: actor state %i is not valid in town!",
              states.actor_state );
      return 0;
    }
  }
  else
  {
    switch( states.actor_state )
    {
      case Actor::Standing:
        return 8;
      case Actor::Walking:
        return 8;
      case Actor::Attacking:
      {
        if( states.weapon_state == Inventory::AxeEquiped )
          return 24;
        else if( states.weapon_state == Inventory::BowEquiped ||
                 states.weapon_state == Inventory::NothingEquiped )
          return 20;
        else
          return 16;
      }
      case Actor::RecoilingFromHit:
        return 8;
      case Actor::CastingSpell:
        return 12;
      case Actor::Dying:
        return 20;
      default:
      {
        qFatal( "Sorcerer Error: actor state %i does not have frames per "
                "direction info!", states.actor_state );
        return 0;
      }
    }
  }
}

// Get the duration of a sprite sheet frame (in game tics)
int Sorcerer::getSpriteSheetFrameDuration( const States& ) const
{
  return 50;
}

void Sorcerer::handleStrengthChange( int )
{
  this->calculateBaseDamage();
}

void Sorcerer::handleDexterityChange( int total_dexterity )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  d_base_armor_class = total_dexterity / 5;
}

void Sorcerer::handleVitalityChange( int, int )
{
  this->calculateBaseHealth();
}

void Sorcerer::handleMagicChange( int, int )
{
  this->calculateBaseMana();
  this->calculateBaseChanceToHitWithSpell();
}

void Sorcerer::handleLevelUp( const int )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  this->calculateBaseChanceToHitWithSpell();
  this->calculateBaseDamage();
  this->calculateBaseHealth();
  this->calculateBaseMana();

  this->updateStats();
}

void Sorcerer::connectStatChangeSignalToSorcererSlots()
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

void Sorcerer::calculateBaseChanceToHitWithMelee()
{
  d_base_chance_to_hit_with_melee = std::min( 50.0 + this->getDexterity() / 2.0 + this->getLevel(), 100.0 );
}

void Sorcerer::calculateBaseChanceToHitWithRanged()
{
  d_base_chance_to_hit_with_ranged = std::min( 50.0 + this->getDexterity() + this->getLevel(), 100.0 );
}

void Sorcerer::calculateBaseChanceToHitWithSpell()
{
  d_base_chance_to_hit_with_spell = std::min( 50.0 + this->getMagic(), 100.0 );
}

void Sorcerer::calculateBaseDamage()
{
  d_base_damage = this->getStrength() * this->getLevel() / 200;
}

void Sorcerer::calculateBaseHealth()
{
  d_base_health = this->getVitality() + this->getLevel() + 9;
}

void Sorcerer::calculateBaseMana()
{
  d_base_mana = 2 * this->getMagic() + 2 * this->getLevel() - 2;
}

// Initialize asset state map
void Sorcerer::initializeAssetStateMap()
{
  // // High class armor: Axe Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sha/shaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Bow Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shb/shbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Staff Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sht/shtqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Sword and Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shd/shdqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Mace and Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shh/shhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Sword Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shs/shsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Mace Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shm/shmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shuwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shuas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shuaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shuat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shuht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shu/shuqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Nothing Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/shn/shndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };

  // // Medium class armor: Axe Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sma/smaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Bow Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smb/smbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Staff Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smt/smtqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Sword and Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smd/smdqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Mace and Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smh/smhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Sword Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sms/smsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Mace Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smm/smmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smuwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smuas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smuaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smuat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smuht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smu/smuqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Nothing Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/smn/smndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };

  // // Low class armor: Axe Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sla/slaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Bow Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slb/slbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Staff Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slt/sltqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Sword and Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sld/sldqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Mace and Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slh/slhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Sword Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/sls/slsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Mace Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slm/slmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Shield Equiped
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/slust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/sluwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/sluas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/sluaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/sluat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/sluht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/slufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/slulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Sorcerer::s_asset_state_map["/plrgfx/sorceror/slu/sluqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // Low class armor: Nothing Equiped
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  Sorcerer::s_asset_state_map["/plrgfx/sorceror/sln/slndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
}

QML_REGISTER_META_TYPE( Sorcerer );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Sorcerer.cpp
//---------------------------------------------------------------------------//
