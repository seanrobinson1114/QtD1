//---------------------------------------------------------------------------//
//!
//! \file   Warrior.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The warrior class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "Warrior.h"
#include "WarriorInventory.h"
#include "WarriorSpellBook.h"

namespace QtD1{

// Initialize static member data
Warrior::AssetStateMap Warrior::s_asset_state_map;

// Get the asset state map
const Warrior::AssetStateMap& Warrior::getAssetStateMap()
{
  // Just-in-time initialization
  if( Warrior::s_asset_state_map.size() == 0 )
    Warrior::initializeAssetStateMap();

  return Warrior::s_asset_state_map;
}

// Default Constructor
/*! \details This constructor should only be used by the qml engine.
 */
Warrior::Warrior( QGraphicsObject* parent )
  : Warrior( "", parent )
{
  // When created by the QML engine no sprites will be loaded
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Copy constructor
/*! \details This constructor should only be used by the qml engine.
 */
Warrior::Warrior( const Warrior& other_warrior )
  : Character( other_warrior ),
    d_base_health( other_warrior.d_base_health ),
    d_base_mana( other_warrior.d_base_mana ),
    d_base_damage( other_warrior.d_base_damage ),
    d_base_armor_class( other_warrior.d_base_armor_class ),
    d_base_chance_to_hit_with_melee( other_warrior.d_base_chance_to_hit_with_melee ),
    d_base_chance_to_hit_with_ranged( other_warrior.d_base_chance_to_hit_with_ranged ),
    d_base_chance_to_hit_with_spell( other_warrior.d_base_chance_to_hit_with_spell )
{
  // When created by the QML engine no sprites will be loaded
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Constructor
Warrior::Warrior( const QString& name, QGraphicsObject* parent )
  : Character( name, new WarriorInventory, new WarriorSpellBook, parent ),
    d_base_health( 1 ),
    d_base_mana( 1 ),
    d_base_damage( 0 ),
    d_base_armor_class( 0 ),
    d_base_chance_to_hit_with_melee( 0.0 ),
    d_base_chance_to_hit_with_ranged( 0.0 ),
    d_base_chance_to_hit_with_spell( 0.0 )
{
  this->connectStatChangeSignalToWarriorSlots();
  this->initializeStats();
}

// Get the character type
Character::Type Warrior::getType() const
{
  return Character::Warrior;
}

// Get the warrior description
QString Warrior::getDescription() const
{
  return QString( "I am a Warrior!" );
}

// Get the base health
int Warrior::getBaseHealth() const
{
  return d_base_health;
}

int Warrior::getBaseMana() const
{
  return d_base_mana;
}

int Warrior::getBaseDamage() const
{
  return d_base_damage;
}

int Warrior::getBaseArmorClass() const
{
  return d_base_armor_class;
}

// Get the base percent chance to hit with melee
qreal Warrior::getBaseChanceToHitWithMeleeWeapon() const
{
  return d_base_chance_to_hit_with_melee;
}

// Get the base percent chance to hit with ranged
qreal Warrior::getBaseChanceToHitWithRangedWeapon() const
{
  return d_base_chance_to_hit_with_ranged;
}

// Get the base percent chance to hit with spell
qreal Warrior::getBaseChanceToHitWithSpell() const
{
  return d_base_chance_to_hit_with_spell;
}

// Get the number of image assets used by the object
int Warrior::getNumberOfImageAssets() const
{
  return Warrior::getAssetStateMap().size();
}

// Get the image asset names used by the object
void Warrior::getImageAssetNames( QSet<QString>& image_asset_names ) const
{
  Warrior::AssetStateMap::const_iterator asset_state_it, asset_state_end;
  asset_state_it = Warrior::getAssetStateMap().begin();
  asset_state_end = Warrior::getAssetStateMap().end();

  while( asset_state_it != asset_state_end )
  {
    image_asset_names.insert( asset_state_it.key() );

    ++asset_state_it;
  }
}

// Check if an image asset is used
bool Warrior::isImageAssetUsed( const QString& image_asset_name ) const
{
  return Warrior::getAssetStateMap().find( image_asset_name ) !=
    Warrior::getAssetStateMap().end();
}

// Get the states associated with the image asset
const Character::States& Warrior::getImageAssetStates(
                                        const QString& image_asset_name ) const
{
  Warrior::AssetStateMap::const_iterator asset_state_it =
    Warrior::getAssetStateMap().find( image_asset_name );

  if( asset_state_it == Warrior::getAssetStateMap().end() )
  {
    qFatal( "Warrior Error: Cannot get image asset states because image asset "
            "%s is not used by the Warrior!",
            image_asset_name.toStdString().c_str() );
  }

  return asset_state_it.value();
}

void Warrior::handleStrengthChange( int )
{
  this->calculateBaseDamage();
}

void Warrior::handleDexterityChange( int total_dexterity )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  d_base_armor_class = total_dexterity / 5;
}

void Warrior::handleVitalityChange( int, int )
{
  this->calculateBaseHealth();
}

void Warrior::handleMagicChange( int, int )
{
  this->calculateBaseMana();
  this->calculateBaseChanceToHitWithSpell();
}

void Warrior::handleLevelUp( const int )
{
  this->calculateBaseChanceToHitWithMelee();
  this->calculateBaseChanceToHitWithRanged();
  this->calculateBaseChanceToHitWithSpell();
  this->calculateBaseDamage();
  this->calculateBaseHealth();
  this->calculateBaseMana();

  this->updateStats();
}

// Initialize warrior stats
void Warrior::initializeStats()
{
  // Set the character's stats
  this->setBaseStrength( 30 );
  this->setBaseMagic( 10 );
  this->setBaseDexterity( 20 );
  this->setBaseVitality( 25 );

  this->handleLevelUp( 1 );

  this->restoreHealth();
  this->restoreMana();
}

void Warrior::calculateBaseChanceToHitWithMelee()
{
  d_base_chance_to_hit_with_melee = std::min( 50.0 + this->getDexterity() / 2.0 + this->getLevel(), 100.0 );
}

void Warrior::calculateBaseChanceToHitWithRanged()
{
  d_base_chance_to_hit_with_ranged = std::min( 50.0 + this->getDexterity() + this->getLevel(), 100.0 );
}

void Warrior::calculateBaseChanceToHitWithSpell()
{
  d_base_chance_to_hit_with_spell = std::min( 50.0 + this->getMagic(), 100.0 );
}

void Warrior::calculateBaseDamage()
{
  d_base_damage = this->getStrength() * this->getLevel() / 100;
}

void Warrior::calculateBaseHealth()
{
  d_base_health = 2 * this->getVitality() + 2 * this->getLevel() + 18;
}

void Warrior::calculateBaseMana()
{
  d_base_mana = this->getMagic() + this->getLevel() - 1;
}

// Get the number of sprite sheet frames per direction
int Warrior::getSpriteSheetFramesPerDirection( const States& states ) const
{
  if( states.in_town )
  {
    if( states.actor_state == Actor::Standing )
      return 20;
    else if( states.actor_state == Actor::Walking )
      return 8;
    else
    {
      qFatal( "Warrior Error: actor state %i is not valid in town!",
              states.actor_state );
      return 0;
    }
  }
  else
  {
    switch( states.actor_state )
    {
      case Actor::Standing:
      {
        if( states.weapon_state == Inventory::BowEquiped )
          return 8;
        else
          return 10;
      }
      case Actor::Walking:
        return 8;
      case Actor::Attacking:
      {
        if( states.weapon_state == Inventory::AxeEquiped )
          return 20;
        else
          return 16;
      }
      case Actor::RecoilingFromHit:
        return 6;
      case Actor::CastingSpell:
      {
        if( states.spell_state == SpellBook::LightningSpellEquiped &&
            states.weapon_state == Inventory::NothingEquiped &&
            states.armor_state == Inventory::LowClassArmorEquiped )
          return 21;
        else
          return 20;
      }
      case Actor::Dying:
      {
        if( states.armor_state == Inventory::LowClassArmorEquiped )
          return 20;
        else
          return 15;
      }
      default:
      {
        qFatal( "Warrior Error: actor state %i does not have frames per "
                "direction info!", states.actor_state );
        return 0;
      }
    }
  }
}

// Get the duration of a sprite sheet frame (in game tics)
int Warrior::getSpriteSheetFrameDuration( const States& states ) const
{
  switch( states.actor_state )
  {
    case Actor::Standing:
      return 10;
    case Actor::Walking:
      return 5;
    default:
      return 1;
  }
}

// Connect the stats changed signal to warrior slots
void Warrior::connectStatChangeSignalToWarriorSlots()
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
void Warrior::initializeAssetStateMap()
{
  // // High class armor: Axe Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wha/whaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Bow Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whb/whbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Staff Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wht/whtqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Sword and Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whd/whdqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Mace and Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whh/whhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Sword Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whs/whsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Mace Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whm/whmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whuwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whuas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whuaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whuat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whuht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whu/whuqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // High class armor: Nothing Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/whn/whndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::HighClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };

  // // Medium class armor: Axe Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wma/wmaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Bow Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmb/wmbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Staff Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmt/wmtqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Sword and Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmd/wmdqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Mace and Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmh/wmhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Sword Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wms/wmsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Mace Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmm/wmmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmuwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmuas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmuaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmuat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmuht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmu/wmuqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Medium class armor: Nothing Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wmn/wmndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::MediumClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };

  // // Low class armor: Axe Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlast.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlawl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlaas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlaaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlaat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlaht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlafm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlalm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wla/wlaqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::AxeEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Bow Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlbst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlbwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlbas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlbaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlbat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlbht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlbfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlblm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlb/wlbqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::BowEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Staff Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlt/wltqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::StaffEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Sword and Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wld/wldqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Mace and Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlh/wlhqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceAndShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Sword Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlsst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlswl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlsas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlsaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlsat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlsht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlsfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlslm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wls/wlsqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::SwordEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Mace Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlm/wlmqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::MaceEquiped, SpellBook::NonElementalSpellEquiped };

  // // Low class armor: Shield Equiped
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wlust.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wluwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wluas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wluaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wluat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wluht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NoSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wlufm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::FireSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wlulm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::LightningSpellEquiped };
  // Warrior::s_asset_state_map["/plrgfx/warrior/wlu/wluqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::ShieldEquiped, SpellBook::NonElementalSpellEquiped };

  // Low class armor: Nothing Equiped
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnst.cl2+levels/towndata/town.pal"] = { Actor::Standing, true, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnwl.cl2+levels/towndata/town.pal"] = { Actor::Walking, true, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnas.cl2+levels/towndata/town.pal"] = { Actor::Standing, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnaw.cl2+levels/towndata/town.pal"] = { Actor::Walking, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnat.cl2+levels/towndata/town.pal"] = { Actor::Attacking, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnht.cl2+levels/towndata/town.pal"] = { Actor::RecoilingFromHit, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnfm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::FireSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnlm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::LightningSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlnqm.cl2+levels/towndata/town.pal"] = { Actor::CastingSpell, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NonElementalSpellEquiped };
  Warrior::s_asset_state_map["/plrgfx/warrior/wln/wlndt.cl2+levels/towndata/town.pal"] = { Actor::Dying, false, Inventory::LowClassArmorEquiped, Inventory::NothingEquiped, SpellBook::NoSpellEquiped };
}

QML_REGISTER_META_TYPE( Warrior );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Warrior.cpp
//---------------------------------------------------------------------------//
