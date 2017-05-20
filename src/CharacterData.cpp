//---------------------------------------------------------------------------//
//!
//! \file   CharacterData.cpp
//! \author Alex Robinson
//! \brief  The character data class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "CharacterData.h"
#include "Character.h"
#include "RogueInventory.h"
#include "RogueSpellBook.h"
#include "SorcererInventory.h"
#include "SorcererSpellBook.h"
#include "WarriorInventory.h"
#include "WarriorSpellBook.h"

namespace QtD1{

// Constructor
CharacterData::CharacterData( QObject* parent )
  : ActorData( parent )
{ /* ... */ }

// Constructor
CharacterData::CharacterData( const QString& character_name,
                              const Character::Type character_type,
                              QObject* parent )
  : ActorData( parent ),
    d_name( character_name ),
    d_type( character_type ),
    d_experience( 0 ),
    d_next_level_experience_threshold( 2000 ),
    d_gold( 0 ),
    d_strength( 0 ),
    d_magic( 0 ),
    d_dexterity( 0 ),
    d_vitality( 0 ),
    d_max_health( 1 ),
    d_max_mana( 1 ),
    d_magic_resistance_fraction( 0.0 ),
    d_fire_resistance_fraction( 0.0 ),
    d_lightning_resistance_fraction( 0.0 ),
    d_armor_class( 0 ),
    d_minimum_damage( 0 ),
    d_maximum_damage( 0 ),
    d_chance_to_hit_with_melee( 0.0 ),
    d_chance_to_hit_with_ranged( 0.0 ),
    d_chance_to_hit_with_spell( 0.0 ),
    d_inventory( NULL ),
    d_spell_book( NULL ),
    d_quest_log( NULL ),
    d_dungeon_sprites(),
    d_town_sprites(),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_active_armor_state( Inventory::LowClassArmorEquiped ),
    d_active_weapon_state( Inventory::NothingEquiped ),
    d_active_spell_state( SpellBook::NoSpellEquiped ),
    d_in_town( true )
{
  // Create the required inventory and spell book
  switch( character_type )
  {
    case Character::Rogue:
    {
      d_inventory = new RogueInventory;
      d_spell_book = new RogueSpellBook;
      break;
    }
    case Character::Sorcerer:
    {
      d_inventory = new SorcererInventory;
      d_spell_book = new SorcererSpellBook;
      break;
    }
    case Character::Warrior:
    {
      d_inventory = new WarriorInventory;
      d_spell_book = new WarriorSpellBook;
      break;
    }
    default:
    {
      qFatal( "CharacterData Error: Unsupported character type!" );
    }
  }

  // Create the quest log
  d_quest_log = new QuestLog;

  // Initialize the spell book pages
  d_spell_book->initializePages();

  // Connect to base stats changed signal
  this->connectToBaseStatsChangedSignal();

  // Connect to the inventory signals
  this->connectInventorySignalsToCharacterDataSlots();

  // Connect to the spell book signals
  this->connectSpellBookSignalsToCharacterDataSlots();
}

// Assignment operator
CharacterData& CharacterData::operator=( const CharacterData& other_data )
{
  if( this != &other_data )
  {
    // Copy the actor data
    ActorData::operator=( other_data );

    // Copy the character data
    d_name = other_data.d_name;
    d_type = other_data.d_type;
    d_experience = other_data.d_experience;
    d_next_level_experience_threshold =
      other_data.d_next_level_experience_threshold;
    d_gold = other_data.d_gold;
    d_strength = other_data.d_strength;
    d_magic = other_data.d_magic;
    d_dexterity = other_data.d_dexterity;
    d_vitality = other_data.d_vitality;
    d_max_health = other_data.d_max_health;
    d_max_mana = other_data.d_max_mana;
    d_magic_resistance_fraction = other_data.d_magic_resistance_fraction;
    d_fire_resistance_fraction = other_data.d_fire_resistance_fraction;
    d_lightning_resistance_fraction =
      other_data.d_lightning_resistance_fraction;
    d_armor_class = other_data.d_armor_class;
    d_minimum_damage = other_data.d_minimum_damage;
    d_maximum_damage = other_data.d_maximum_damage;
    d_chance_to_hit_with_melee = other_data.d_chance_to_hit_with_melee;
    d_chance_to_hit_with_ranged = other_data.d_chance_to_hit_with_ranged;
    d_chance_to_hit_with_spell = other_data.d_chance_to_hit_with_spell;
    d_active_armor_state = other_data.d_active_armor_state;
    d_active_weapon_state = other_data.d_active_weapon_state;
    d_active_spell_state = other_data.d_active_spell_state;
    d_in_town = other_data.d_in_town;

    // Disconnect from the current inventory signals
    this->disconnectCharacterDataSlotsFromInventorySignals();

    // Disconnect from the current spell book signals
    this->disconnectCharacterDataSlotsFromSpellBookSignals();

    // Clone the inventory and the spell book
    if( d_inventory )
      d_inventory->close();

    d_inventory = other_data.d_inventory->clone();
    d_spell_book = other_data.d_spell_book->clone();

    // Connect to the inventory signals
    this->connectInventorySignalsToCharacterDataSlots();

    // Connect to the spell book signals
    this->connectSpellBookSignalsToCharacterDataSlots();

    // Do we need a deep copy of the sprites too?
    d_dungeon_sprites = other_data.d_dungeon_sprites;
    d_town_sprites = other_data.d_town_sprites;
    d_direction_sprites = other_data.d_direction_sprites;
  }

  return *this;
}

//! Destructor
CharacterData::~CharacterData()
{
  if( d_inventory )
      d_inventory->close();

  if( d_spell_book )
      d_spell_book->close();
}

// Get the name
QString CharacterData::getName() const
{
  return d_name;
}

// Get the character type
Character::Type CharacterData::getType() const
{
  return d_type;
}

// Increment the level
void CharacterData::incrementLevel()
{
  this->setLevel( this->getLevel() + 1 );

  // Update the next level experience threshold
  d_next_level_experience_threshold *= 2;

  emit levelUp( this->getLevel() );
}

// Set the experience
void CharacterData::setExperience( const int experience )
{
  d_experience = std::max( experience, 0 );
}

// Add to experience
void CharacterData::addExperience( const int experience )
{
  d_experience += std::max( experience, 0 );

  while( d_experience > d_next_level_experience_threshold )
  {
    this->incrementLevel();
  }
}

// Get the experience
int CharacterData::getExperience() const
{
  return d_experience;
}

// Get the next level experience threshold
int CharacterData::getNextLevelExperienceThreshold()
{
  return d_next_level_experience_threshold;
}

// Get the gold amount
int CharacterData::getGold()
{
  return d_gold;
}

// Get the strength
int CharacterData::getStrength() const
{
  return d_strength;
}

// Get the magic
int CharacterData::getMagic() const
{
  return d_magic;
}

// Get the dexterity
int CharacterData::getDexterity() const
{
  return d_dexterity;
}

// Get the vitality
int CharacterData::getVitality() const
{
  return d_vitality;
}

// Get the max health
int CharacterData::getMaxHealth() const
{
  return d_max_health;
}

// Get the max mana
int CharacterData::getMaxMana() const
{
  return d_max_mana;
}

// Get the magic resistance
qreal CharacterData::getMagicResistance() const
{
  return d_magic_resistance_fraction;
}

// Get the fire resistance
qreal CharacterData::getFireResistance() const
{
  return d_fire_resistance_fraction;
}

// Get the lightning resistance
qreal CharacterData::getLightningResistance() const
{
  return d_lightning_resistance_fraction;
}

// Get the armor class
int CharacterData::getArmorClass() const
{
  return d_armor_class;
}

// Get the minimum damage
int CharacterData::getMinimumDamage() const
{
  return d_minimum_damage;
}

// Get the maximum damage
int CharacterData::getMaximumDamage() const
{
  return d_maximum_damage;
}

// Get the percent chance to hit with melee weapon
qreal CharacterData::getChanceToHitWithMeleeWeapon() const
{
  return d_chance_to_hit_with_melee;
}

// Get the percent chance to hit with ranged weapon
qreal CharacterData::getChanceToHitWithRangedWeapon() const
{
  return d_chance_to_hit_with_ranged;
}

// Get the chance to hit with a spell_state
qreal CharacterData::getChanceToHitWithSpell() const
{
  return d_chance_to_hit_with_spell;
}

// Get the inventory
const Inventory& CharacterData::getInventory() const
{
  return *d_inventory;
}

// Get the inventory
Inventory& CharacterData::getInventory()
{
  return *d_inventory;
}

// Get the spell book
const SpellBook& CharacterData::getSpellBook() const
{
  return *d_spell_book;
}

// Get the spell book
SpellBook& CharacterData::getSpellBook()
{
  return *d_spell_book;
}

// Get the quest log
const QuestLog& CharacterData::getQuestLog() const
{
  return *d_quest_log;
}

// Get the quest log
QuestLog& CharacterData::getQuestLog()
{
  return *d_quest_log;
}

// Get the character dungeon sprites
auto CharacterData::getCharacterDungeonSprites() -> SpellWeaponAndArmorClassStateGameSpriteMap&
{
  return d_dungeon_sprites;
}

// Get the character dungeon sprites
auto CharacterData::getCharacterDungeonSprites() const -> const SpellWeaponAndArmorClassStateGameSpriteMap&
{
  return d_dungeon_sprites;
}

// Get the character town sprites
auto CharacterData::getCharacterTownSprites() -> WeaponAndArmorClassStateGameSpriteMap&
{
  return d_town_sprites;
}

// Get the character town sprites
auto CharacterData::getCharacterTownSprites() const -> const WeaponAndArmorClassStateGameSpriteMap&
{
  return d_town_sprites;
}

// Get the state direction sprites
auto CharacterData::getDirectionSprites() ->   QMap<QString,std::shared_ptr<ActorData::DirectionGameSpriteMap> >&
{
  return d_direction_sprites;
}

// Get the state direction sprites
auto CharacterData::getDirectionSprites() const -> const QMap<QString,std::shared_ptr<ActorData::DirectionGameSpriteMap> >&
{
  return d_direction_sprites;
}

// Check if the sprites have been loaded
bool CharacterData::spritesLoaded() const
{
  return d_sprites_loaded;
}

// The sprites have been loaded
void CharacterData::setSpritesLoaded()
{
  d_sprites_loaded = true;
}

// The sprites have not been loaded
void CharacterData::setSpritesNotLoaded()
{
  d_sprites_loaded = false;
}

// Get the active armor state
Inventory::ChestArmorState CharacterData::getActiveArmorState() const
{
  return d_active_armor_state;
}

// Get the active weapon state
Inventory::WeaponState CharacterData::getActiveWeaponState() const
{
  return d_active_weapon_state;
}

// Get the active spell state
SpellBook::SpellState CharacterData::getActiveSpellState() const
{
  return d_active_spell_state;
}

// Check if the character is in town
bool CharacterData::isInTown() const
{
  return d_in_town;
}

// The character has entered the town
void CharacterData::enterTown()
{
  d_in_town = true;

  this->updateActorSprites();
  this->setActiveStateAndDirection( Actor::Standing, Direction::South );
}

// The character has exited the town
void CharacterData::exitTown()
{
  d_in_town = false;

  this->updateActorSprites();
  this->setActiveStateAndDirection( Actor::Standing, Direction::South );
}

// Weapon has been changed
void CharacterData::handleWeaponChanged( const Inventory::WeaponState state )
{
  if( d_active_weapon_state != state )
  {
    d_active_weapon_state = state;

    this->updateActorSprites();
  }

  this->updateStats();
}

// Shield has been changed
void CharacterData::handleShieldChanged( const Inventory::WeaponState state )
{
  if( d_active_weapon_state != state )
  {
    d_active_weapon_state = state;

    this->updateActorSprites();
  }

  this->updateStats();
}

// Ring has been changed
void CharacterData::handleRingChanged()
{
  this->updateStats();
}

// Amulet has been changed
void CharacterData::handleAmuletChanged()
{
  this->updateStats();
}

// Armor has been changed
void CharacterData::handleArmorChanged( const Inventory::ChestArmorState state )
{
  if( d_active_armor_state != state )
  {
    d_active_armor_state = state;

    this->updateActorSprites();
  }

  this->updateStats();
}

// Helmet has been changed
void CharacterData::handleHelmetChanged()
{
  this->updateStats();
}

// Spell changed
void CharacterData::handleSpellChanged( const SpellBook::SpellState state )
{
  if( d_active_spell_state != state )
  {
    d_active_spell_state = state;

    this->updateActorSprites();
  }
}

// Update the active actor sprites
void CharacterData::updateActorSprites()
{
  if( d_in_town )
  {
    this->getSprites() =
      d_town_sprites[d_active_weapon_state][d_active_armor_state];
  }
  else
  {
    this->getSprites() = d_dungeon_sprites[d_active_spell_state][d_active_weapon_state][d_active_armor_state];
  }

  this->updateActiveSprite();

  emit characterStateChanged();
}

// Update the character stats after the inventory has changed
void CharacterData::updateStats()
{
  // Update strength
  d_strength = this->getBaseStrength() +
    d_inventory->calculateStrengthModifier();
  emit strengthChanged( d_strength );

  // Update magic
  d_magic = this->getBaseMagic() +
    d_inventory->calculateMagicModifier();
  emit magicChanged( this->getBaseMagic(), d_inventory->calculateMagicModifier() );

  // Update dexterity
  d_dexterity = this->getBaseDexterity() +
    d_inventory->calculateDexterityModifier();
  emit dexterityChanged( d_dexterity );

  // Update vitality
  d_vitality = this->getBaseVitality() +
    d_inventory->calculateVitalityModifier();
  emit vitalityChanged( this->getBaseVitality(), d_inventory->calculateVitalityModifier() );

  // Update max health
  d_max_health = this->getBaseHealth() +
    d_inventory->calculateHealthModifier();
  if( d_max_health < this->getHealth() )
    this->setHealth( d_max_health );

  // Update max mana
  d_max_mana = this->getBaseMana() +
    d_inventory->calculateManaModifier();
  if( d_max_mana < this->getMana() )
    this->setMana( d_max_mana );

  // Update magic resistance
  d_magic_resistance_fraction = this->getBaseMagicResistance() +
    d_inventory->calculateMagicResistance();

  // Update fire resistance
  d_fire_resistance_fraction = this->getBaseFireResistance() +
    d_inventory->calculateFireResistance();

  // Update lightning resistance
  d_lightning_resistance_fraction = this->getBaseLightningResistance() +
    d_inventory->calculateLightningResistance();

  // Update the armor class
  d_armor_class = this->getBaseArmorClass() +
    d_inventory->calculateArmorClass();

  // Update the damage
  /*d_damage = this->getBaseDamage() +
    d_inventory->calculateDamage();*/

  d_minimum_damage = this->getBaseDamage();
  //   + d_inventory->calculateMinimumDamage();
  //
  d_maximum_damage = this->getBaseDamage();
  //   + d_inventory->calculateMaximumDamage();

  emit statsChanged();
}

// Connect to base stats changed signal
void CharacterData::connectToBaseStatsChangedSignal()
{
  QObject::connect( this, SIGNAL(coreStatIncremented()),
                    this, SLOT(updateStats()) );
}

// Connect to inventory signals
void CharacterData::connectInventorySignalsToCharacterDataSlots()
{
  QObject::connect( d_inventory, SIGNAL(weaponChanged(const Inventory::WeaponState)),
                    this, SLOT(handleWeaponChanged(const Inventory::WeaponState)) );
  QObject::connect( d_inventory, SIGNAL(shieldChanged(const Inventory::WeaponState)),
                    this, SLOT(handleShieldChanged(const Inventory::WeaponState)) );
  QObject::connect( d_inventory, SIGNAL(ringChanged()),
                    this, SLOT(handleRingChanged()) );
  QObject::connect( d_inventory, SIGNAL(amuletChanged()),
                    this, SLOT(handleAmuletChanged()) );
  QObject::connect( d_inventory, SIGNAL(armorChanged(const Inventory::ChestArmorState)),
                    this, SLOT(handleArmorChanged(const Inventory::ChestArmorState)) );
  QObject::connect( d_inventory, SIGNAL(helmetChanged()),
                    this, SLOT(handleHelmetChanged()) );
}

// Disconnect from inventory signals
void CharacterData::disconnectCharacterDataSlotsFromInventorySignals()
{
  QObject::disconnect( d_inventory, SIGNAL(weaponChanged(const Inventory::WeaponState)),
                       this, SLOT(handleWeaponChanged(const Inventory::WeaponState)) );
  QObject::disconnect( d_inventory, SIGNAL(shieldChanged(const Inventory::WeaponState)),
                       this, SLOT(handleShieldChanged(const Inventory::WeaponState)) );
  QObject::disconnect( d_inventory, SIGNAL(ringChanged()),
                       this, SLOT(handleRingChanged()) );
  QObject::disconnect( d_inventory, SIGNAL(amuletChanged()),
                       this, SLOT(handleAmuletChanged()) );
  QObject::disconnect( d_inventory, SIGNAL(armorChanged(const Inventory::ChestArmorState)),
                       this, SLOT(handleArmorChanged(const Inventory::ChestArmorState)) );
  QObject::disconnect( d_inventory, SIGNAL(helmetChanged()),
                       this, SLOT(handleHelmetChanged()) );
}

// Connect to spell book signals
void CharacterData::connectSpellBookSignalsToCharacterDataSlots()
{
  QObject::connect( d_spell_book, SIGNAL(spellChanged(const SpellBook::SpellState)),
                    this, SLOT(handleSpellChanged(const SpellBook::SpellState)) );
}

// Disconnect from inventory signals
void CharacterData::disconnectCharacterDataSlotsFromSpellBookSignals()
{
  QObject::disconnect( d_spell_book, SIGNAL(spellChanged(const SpellBook::SpellState)),
                       this, SLOT(handleSpellChanged(const SpellBook::SpellState)) );
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end CharacterData.cpp
//---------------------------------------------------------------------------//
