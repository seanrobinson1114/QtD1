//---------------------------------------------------------------------------//
//!
//! \file   Rogue.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The rogue class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Rogue.h"
#include "RogueInventory.h"
#include "RogueSpellBook.h"

namespace QtD1{

// Initialize static member data
Rogue::AssetStateMap Rogue::s_asset_state_map;

// Get the asset state map
const Rogue::AssetStateMap& Rogue::getAssetStateMap()
{
  // Just-in-time initialization
  if( Rogue::s_asset_state_map.size() == 0 )
    Rogue::initializeAssetStateMap();

  return Rogue::s_asset_state_map;
}

// Constructor
/*! \details This constructor should only be used by the QML engine.
 */
Rogue::Rogue( QGraphicsObject* parent )
  : Rogue( "", parent )
{
  // When created by the QML engine no sprites will be loaded
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Copy constructor
/*! \details This constructor should only be used by the QML engine.
 */
Rogue::Rogue( const Rogue& other_rogue )
  : Character( other_rogue ),
    d_base_health( other_rogue.d_base_health ),
    d_base_mana( other_rogue.d_base_mana ),
    d_base_damage( other_rogue.d_base_damage ),
    d_base_armor_class( other_rogue.d_base_armor_class ),
    d_base_chance_to_hit_with_melee( other_rogue.d_base_chance_to_hit_with_melee ),
    d_base_chance_to_hit_with_ranged( other_rogue.d_base_chance_to_hit_with_ranged ),
    d_base_chance_to_hit_with_spell( other_rogue.d_base_chance_to_hit_with_spell )
{
  // When created by the QML engine no sprites will be loaded
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Constructor
Rogue::Rogue( const QString& name, QGraphicsObject* parent )
  : Character( name, new RogueInventory, new RogueSpellBook, parent ),
    d_base_health( 1 ),
    d_base_mana( 1 ),
    d_base_damage( 0 ),
    d_base_armor_class( 0 ),
    d_base_chance_to_hit_with_melee( 0.0 ),
    d_base_chance_to_hit_with_ranged( 0.0 ),
    d_base_chance_to_hit_with_spell( 0.0 )
{
  this->connectStatChangeSignalToRogueSlots();
  this->initializeStats();
}

// Get the character type
Character::Type Rogue::getType() const
{
  return Character::Rogue;
}

// Get the rogue description
QString Rogue::getDescription() const
{
  return QString( "I am a rogue" );
}

// Get the base health
int Rogue::getBaseHealth() const
{
  return d_base_health;
}

int Rogue::getBaseMana() const
{
  return d_base_mana;
}

int Rogue::getBaseDamage() const
{
  return d_base_damage;
}

int Rogue::getBaseArmorClass() const
{
  return d_base_armor_class;
}

// Get the base percent chance to hit with melee
qreal Rogue::getBaseChanceToHitWithMeleeWeapon() const
{
  return d_base_chance_to_hit_with_melee;
}

// Get the base percent chance to hit with ranged
qreal Rogue::getBaseChanceToHitWithRangedWeapon() const
{
  return d_base_chance_to_hit_with_ranged;
}

// Get the base percent chance to hit with spell
qreal Rogue::getBaseChanceToHitWithSpell() const
{
  return d_base_chance_to_hit_with_spell;
}

// Get the number of image assets used by the object
int Rogue::getNumberOfImageAssets() const
{
  return Rogue::getAssetStateMap().size();
}

// Get the image asset names used by the object
void Rogue::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  AssetStateMap::const_iterator asset_state_it, asset_state_end;
  asset_state_it = Rogue::getAssetStateMap().begin();
  asset_state_end = Rogue::getAssetStateMap().end();

  while( asset_state_it != asset_state_end )
  {
    image_asset_names.insert( asset_state_it.key() );

    ++asset_state_it;
  }
}

// Check if an image asset is used
bool Rogue::isImageAssetUsed( const QString& image_asset_name ) const
{
  return Rogue::getAssetStateMap().find( image_asset_name ) !=
    Rogue::getAssetStateMap().end();
}

// Get the states associated with the image asset
const Character::States& Rogue::getImageAssetStates(
                                        const QString& image_asset_name ) const
{
  AssetStateMap::const_iterator asset_state_it =
    Rogue::getAssetStateMap().find( image_asset_name );

  if( asset_state_it == Rogue::getAssetStateMap().end() )
  {
    qFatal( "Rogue Error: Cannot get image asset states because image asset "
            "%s is not used by the Rogue!",
            image_asset_name.toStdString().c_str() );
  }

  return asset_state_it.value();
}

// Initialize rogue stats
void Rogue::initializeStats()
{
  this->setBaseStrength( 25 );
  this->setBaseMagic( 15 );
  this->setBaseDexterity( 30 );
  this->setBaseVitality( 20 );

  this->handleLevelUp( 1 );

  this->restoreHealth();
  this->restoreMana();
}

// Get the number of sprite sheet frames per direction
int Rogue::getSpriteSheetFramesPerDirection( const States& states ) const
{
  if( states.in_town )
  {
    if( states.actor_state == Actor::Standing )
      return 20;
    else if( states.actor_state == Actor::Walking )
      return 8;
    else
    {
      qFatal( "Rogue Error: actor state %i is not valid in town!",
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
          return 22;
        else if( states.weapon_state == Inventory::BowEquiped )
          return 12;
        else
          return 18;
      }
      case Actor::RecoilingFromHit:
        return 7;
      case Actor::CastingSpell:
        return 16;
      case Actor::Dying:
        return 20;
      default:
      {
        qFatal( "Rogue Error: actor state %i does not have frames per "
                "direction info!", states.actor_state );
        return 0;
      }
    }
  }
}

// Get the duration of a sprite sheet frame (in game tics)
int Rogue::getSpriteSheetFrameDuration( const States& ) const
{
  return 50;
}

void Rogue::handleStrengthChange( int )
{
  this->calculateBaseDamage();
}

void Rogue::handleDexterityChange( int total_dexterity )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  d_base_armor_class = total_dexterity / 5;
}

void Rogue::handleVitalityChange( int, int )
{
  this->calculateBaseHealth();
}

void Rogue::handleMagicChange( int, int )
{
  this->calculateBaseMana();
  this->calculateBaseChanceToHitWithSpell();
}

void Rogue::handleLevelUp( const int )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  this->calculateBaseChanceToHitWithSpell();
  this->calculateBaseDamage();
  this->calculateBaseHealth();
  this->calculateBaseMana();

  this->updateStats();
}

void Rogue::calculateBaseChanceToHitWithMelee()
{
  d_base_chance_to_hit_with_melee = std::min( 50.0 + this->getDexterity() / 2.0 + this->getLevel(), 100.0 );
}

void Rogue::calculateBaseChanceToHitWithRanged()
{
  d_base_chance_to_hit_with_ranged = std::min( 50.0 + this->getDexterity() + this->getLevel(), 100.0 );
}

void Rogue::calculateBaseChanceToHitWithSpell()
{
  d_base_chance_to_hit_with_spell = std::min( 50.0 + this->getMagic(), 100.0 );
}

void Rogue::calculateBaseDamage()
{
  d_base_damage = (this->getStrength() + this->getDexterity()) * this->getLevel() / 200;
}

void Rogue::calculateBaseHealth()
{
  d_base_health = 1 * this->getBaseVitality() + 1.5 * this->getInventory().calculateVitalityModifier() + 2 * this->getLevel() + 23;
}

void Rogue::calculateBaseMana()
{
  d_base_mana = this->getBaseMagic() + 1.5 * this->getInventory().calculateMagicModifier() + 2 * this->getLevel() + 5;
}

void Rogue::connectStatChangeSignalToRogueSlots()
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

// Initialize asset state map
void Rogue::initializeAssetStateMap()
{
  // // High class armor: Axe Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rha/rhaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Bow Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhb/rhbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Staff Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rht/rhtqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Sword and Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhd/rhdqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Mace and Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhh/rhhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Sword Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhs/rhsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Mace Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhm/rhmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhuwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhuas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhuaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhuat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhuht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhu/rhuqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Nothing Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rhn/rhndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };

  // // Medium class armor: Axe Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rma/rmaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Bow Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmb/rmbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Staff Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmt/rmtqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Sword and Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmd/rmdqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Mace and Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmh/rmhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Sword Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rms/rmsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Mace Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmm/rmmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmuwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmuas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmuaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmuat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmuht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmu/rmuqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Nothing Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rmn/rmndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };

  // // Low class armor: Axe Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rla/rlaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Bow Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlb/rlbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Staff Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlt/rltqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Sword and Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rld/rldqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Mace and Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlh/rlhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Sword Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rls/rlsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Mace Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlm/rlmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Shield Equiped
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rlust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rluwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rluas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rluaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rluat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rluht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rlufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rlulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Rogue::s_asset_state_map["/plrgfx/rogue/rlu/rluqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // Low class armor: Nothing Equiped
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  Rogue::s_asset_state_map["/plrgfx/rogue/rln/rlndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
}

QML_REGISTER_META_TYPE( Rogue );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Rogue.cpp
//---------------------------------------------------------------------------//
