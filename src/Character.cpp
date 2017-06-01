//---------------------------------------------------------------------------//
//!
//! \file   Character.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The character base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include "Character.h"

namespace QtD1{

// Constructor
Character::Character( const QString& name,
                      Inventory* inventory,
                      SpellBook* spell_book,
                      QGraphicsObject* parent )
  : Actor( parent ),
    d_name( name ),
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
    d_inventory( inventory ),
    d_spell_book( spell_book ),
    d_quest_log( new QuestLog ),
    d_dungeon_sprites(),
    d_town_sprites(),
    d_direction_sprites(),
    d_sprites_loaded( false ),
    d_active_armor_state( Inventory::LowClassArmorEquiped ),
    d_active_weapon_state( Inventory::NothingEquiped ),
    d_active_spell_state( SpellBook::NoSpellEquiped ),
    d_in_town( true )
{ 
  // Initialize the spell book pages
  d_spell_book->initializePages();

  // Connect to base stats changed signal
  this->connectToBaseStatsChangedSignal();

  // Connect to the inventory signals
  this->connectInventorySignalsToCharacterSlots();

  // Connect to the spell book signals
  this->connectSpellBookSignalsToCharacterSlots();
}

// Copy constructor
/*! \details The copy constructor should only be used by the QML engine
 */
Character::Character( const Character& other_character )
  : Actor( other_character.parentObject() ),
    d_name( other_character.d_name ),
    d_experience( other_character.d_experience ),
    d_next_level_experience_threshold( other_character.d_next_level_experience_threshold ),
    d_gold( other_character.d_gold ),
    d_strength( other_character.d_strength ),
    d_magic( other_character.d_magic ),
    d_dexterity( other_character.d_dexterity ),
    d_vitality( other_character.d_vitality ),
    d_max_health( other_character.d_max_health ),
    d_max_mana( other_character.d_max_mana ),
    d_magic_resistance_fraction( other_character.d_magic_resistance_fraction ),
    d_fire_resistance_fraction( other_character.d_fire_resistance_fraction ),
    d_lightning_resistance_fraction( other_character.d_lightning_resistance_fraction ),
    d_armor_class( other_character.d_armor_class ),
    d_minimum_damage( other_character.d_minimum_damage ),
    d_maximum_damage( other_character.d_maximum_damage ),
    d_chance_to_hit_with_melee( other_character.d_chance_to_hit_with_melee ),
    d_chance_to_hit_with_ranged( other_character.d_chance_to_hit_with_ranged ),
    d_chance_to_hit_with_spell( other_character.d_chance_to_hit_with_spell ),
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
  // When created by the QML engine no sprites will be loaded
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Destructor
/*! \details If the inventory and/or the spell book and/or quest log have a 
 * parent widget set, that parent will take care of destroying it/them when it
 * is closed. If one or more of them haven't been destroyed by the time this
 * destructor is invoked, they will be destroyed in the destructor.
 */
Character::~Character()
{
  if( d_inventory )
      d_inventory->close();

  if( d_spell_book )
      d_spell_book->close();

  if( d_quest_log )
    d_quest_log->close();
}

// Get the name
QString Character::getName() const
{
  return d_name;
}

// Increment the level
void Character::incrementLevel()
{
  this->setLevel( this->getLevel() + 1 );

  // Update the next level experience threshold
  d_next_level_experience_threshold *= 2;

  emit levelUp( this->getLevel() );
}

// Add to experience
void Character::addExperience( const int experience )
{
  d_experience += std::max( experience, 0 );

  while( d_experience > d_next_level_experience_threshold )
  {
    this->incrementLevel();
  }
}

// Get the experience
int Character::getExperience() const
{
  return d_experience;
}

// Get the next level experience threshold
int Character::getNextLevelExperienceThreshold()
{
  return d_next_level_experience_threshold;
}

// Get experience to next level threshold
int Character::getExperienceToNextLevelThreshold()
{
  return std::max( this->getNextLevelExperienceThreshold() - this->getExperience(), 0 );
}

// Get the strength
int Character::getStrength() const
{
  return d_strength;
}

// Get the magic
int Character::getMagic() const
{
  return d_magic;
}

// Get the dexterity
int Character::getDexterity() const
{
  return d_dexterity;
}

// Get the vitality
int Character::getVitality() const
{
  return d_vitality;
}

// Get the max health
int Character::getMaxHealth() const
{
  return d_max_health;
}

// Get the max mana
int Character::getMaxMana() const
{
  return d_max_mana;
}

// Get the magic resistance
qreal Character::getMagicResistance() const
{
  return d_magic_resistance_fraction;
}

// Get the fire resistance
qreal Character::getFireResistance() const
{
  return d_fire_resistance_fraction;
}

// Get the lightning resistance
qreal Character::getLightningResistance() const
{
  return d_lightning_resistance_fraction;
}

// Get the armor class
int Character::getArmorClass() const
{
  return d_armor_class;
}

// Get the minimum damage
int Character::getMinimumDamage() const
{
  return d_minimum_damage;
}

// Get the maximum damage
int Character::getMaximumDamage() const
{
  return d_maximum_damage;
}

// Get the percent chance to hit with melee weapon
qreal Character::getChanceToHitWithMeleeWeapon() const
{
  return d_chance_to_hit_with_melee;
}

// Get the percent chance to hit with ranged weapon
qreal Character::getChanceToHitWithRangedWeapon() const
{
  return d_chance_to_hit_with_ranged;
}

// Get the chance to hit with a spell_state
qreal Character::getChanceToHitWithSpell() const
{
  return d_chance_to_hit_with_spell;
}

// Get the movement speed (pixels per game tic)
qreal Character::getMovementSpeed() const
{
  return 0.1;
}
  
// Get the gold amount
int Character::getGold()
{
  return d_gold;
}

// Check if the character is in town
bool Character::inTown() const
{
  return d_in_town;
}

// Get the inventory
const Inventory& Character::getInventory() const
{
  return *d_inventory;
}

// Get the inventory
Inventory& Character::getInventory()
{
  return *d_inventory;
}

// Get the spell book
const SpellBook& Character::getSpellBook() const
{
  return *d_spell_book;
}

// Get the spell book
SpellBook& Character::getSpellBook()
{
  return *d_spell_book;
}

// Get the quest log
const QuestLog& Character::getQuestLog() const
{
  return *d_quest_log;
}

// Get the quest log
QuestLog& Character::getQuestLog()
{
  return *d_quest_log;
}

// Check if the image assets have been loaded
bool Character::imageAssetsLoaded() const
{
  return d_sprites_loaded;
}

// Load the image asset
void Character::loadImageAsset( const QString& image_asset_name,
                                const QVector<QPixmap>& image_asset_frames )
{
  const States& image_asset_states =
    this->getImageAssetStates( image_asset_name );

  // Check if this is a town state
  if( image_asset_states.in_town )
  {
    this->loadTownStateGameSprites(
                  image_asset_name,
                  image_asset_frames,
                  this->getSpriteSheetFramesPerDirection( image_asset_states ),
                  image_asset_states.weapon_state,
                  image_asset_states.armor_state,
                  image_asset_states.actor_state );
  }
  // Dungeon state
  else
  {
    // This is not a spell cast state
    if( image_asset_states.actor_state != Actor::CastingSpell )
    {
      this->loadNonSpellCastDungeonStateGameSprites(
                  image_asset_name,
                  image_asset_frames,
                  this->getSpriteSheetFramesPerDirection( image_asset_states ),
                  image_asset_states.weapon_state,
                  image_asset_states.armor_state,
                  image_asset_states.actor_state );
    }
    // This is a spell cast state
    else
    {
      this->loadSpellCastDungeonStateGameSprites(
                  image_asset_name,
                  image_asset_frames,
                  this->getSpriteSheetFramesPerDirection( image_asset_states ),
                  image_asset_states.spell_state,
                  image_asset_states.weapon_state,
                  image_asset_states.armor_state );
    }
  }
}

// Load the town state game sprites
void Character::loadTownStateGameSprites(
                                  const QString& image_asset_name,
                                  const QVector<QPixmap>& image_asset_frames,
                                  const int frames_per_direction,
                                  const Inventory::WeaponState weapon_state,
                                  const Inventory::ChestArmorState armor_state,
                                  const Actor::State actor_state )
{
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>&
    actor_state_direction_sprite_map = d_town_sprites[weapon_state][armor_state];

  if( !actor_state_direction_sprite_map )
  {
    actor_state_direction_sprite_map.reset(
                                      new Actor::StateDirectionGameSpriteMap );
  }

  std::shared_ptr<BasicActor::DirectionGameSpriteMap>&
    direction_game_sprites = (*actor_state_direction_sprite_map)[actor_state];

  this->loadDirectionGameSprites( image_asset_name,
                                  image_asset_frames,
                                  frames_per_direction,
                                  direction_game_sprites );
}

// Load the non-spell cast dungeon state game sprites
void Character::loadNonSpellCastDungeonStateGameSprites(
                                  const QString& image_asset_name,
                                  const QVector<QPixmap>& image_asset_frames,
                                  const int frames_per_direction,
                                  const Inventory::WeaponState weapon_state,
                                  const Inventory::ChestArmorState armor_state,
                                  const Actor::State actor_state )
{
  // Set the no spell equiped state
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>& no_spell_state_direction_sprite_map =
    d_dungeon_sprites[SpellBook::NoSpellEquiped][weapon_state][armor_state];

  if( !no_spell_state_direction_sprite_map )
  {
    no_spell_state_direction_sprite_map.reset(
                                      new Actor::StateDirectionGameSpriteMap );
  }

  std::shared_ptr<Actor::DirectionGameSpriteMap>& direction_game_sprites =
    (*no_spell_state_direction_sprite_map)[actor_state];

  this->loadDirectionGameSprites( image_asset_name,
                                  image_asset_frames,
                                  frames_per_direction,
                                  direction_game_sprites );

  // Set the non-elemental spell equiped state
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>& non_elemental_spell_state_direction_game_sprite_map =
    d_dungeon_sprites[SpellBook::NonElementalSpellEquiped][weapon_state][armor_state];

  if( !non_elemental_spell_state_direction_game_sprite_map )
  {
    non_elemental_spell_state_direction_game_sprite_map.reset(
                                      new Actor::StateDirectionGameSpriteMap );
  }

  (*non_elemental_spell_state_direction_game_sprite_map)[actor_state] =
    direction_game_sprites;

  // Set the fire spell equiped state
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>& fire_spell_state_direction_game_sprite_map =
    d_dungeon_sprites[SpellBook::NonElementalSpellEquiped][weapon_state][armor_state];

  if( !fire_spell_state_direction_game_sprite_map )
  {
    fire_spell_state_direction_game_sprite_map.reset(
                                  new Actor::StateDirectionGameSpriteMap );
  }

  (*fire_spell_state_direction_game_sprite_map)[actor_state] =
    direction_game_sprites;

  // Set the lightning spell equiped state
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>& lightning_spell_state_direction_game_sprite_map =
    d_dungeon_sprites[SpellBook::NonElementalSpellEquiped][weapon_state][armor_state];

  if( !lightning_spell_state_direction_game_sprite_map )
  {
    lightning_spell_state_direction_game_sprite_map.reset(
                                      new Actor::StateDirectionGameSpriteMap );
  }

  (*lightning_spell_state_direction_game_sprite_map)[actor_state] =
    direction_game_sprites;
}

// Load the spell cast dungeon state game sprites
void Character::loadSpellCastDungeonStateGameSprites(
                                 const QString& image_asset_name,
                                 const QVector<QPixmap>& image_asset_frames,
                                 const int frames_per_direction,
                                 const SpellBook::SpellState spell_state,
                                 const Inventory::WeaponState weapon_state,
                                 const Inventory::ChestArmorState armor_state )
{
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>& spell_cast_state_direction_game_sprite_map =
    d_dungeon_sprites[spell_state][weapon_state][armor_state];

  if( !spell_cast_state_direction_game_sprite_map )
  {
    spell_cast_state_direction_game_sprite_map.reset(
                                  new Actor::StateDirectionGameSpriteMap );
  }

  std::shared_ptr<Actor::DirectionGameSpriteMap>& direction_game_sprites =
    (*spell_cast_state_direction_game_sprite_map)[Actor::CastingSpell];

  this->loadDirectionGameSprites( image_asset_name,
                                  image_asset_frames,
                                  frames_per_direction,
                                  direction_game_sprites );
}

// Create the direction game sprites
void Character::loadDirectionGameSprites(
                            const QString& source,
                            const QVector<QPixmap>& image_asset_frames,
                            const int frames_per_direction,
                            std::shared_ptr<Actor::DirectionGameSpriteMap>&
                            direction_game_sprites )
{
  if( !direction_game_sprites )
    direction_game_sprites.reset( new Actor::DirectionGameSpriteMap );

  int offset = 0;

  this->loadGameSprites( source,
                         image_asset_frames,
                         frames_per_direction,
                         offset,
                         (*direction_game_sprites)[South] );

  offset += frames_per_direction;

  this->loadGameSprites( source,
                         image_asset_frames,
                         frames_per_direction,
                         offset,
                         (*direction_game_sprites)[Southwest] );

  offset += frames_per_direction;

  this->loadGameSprites( source,
                         image_asset_frames,
                         frames_per_direction,
                         offset,
                         (*direction_game_sprites)[West] );
  
  offset += frames_per_direction;

  this->loadGameSprites( source,
                         image_asset_frames,
                         frames_per_direction,
                         offset,
                         (*direction_game_sprites)[Northwest] );

  offset += frames_per_direction;
  
  this->loadGameSprites( source,
                         image_asset_frames,
                         frames_per_direction,
                         offset,
                         (*direction_game_sprites)[North] );

  offset += frames_per_direction;

  this->loadGameSprites( source,
                         image_asset_frames,
                         frames_per_direction,
                         offset,
                         (*direction_game_sprites)[Northeast] );

  offset += frames_per_direction;

  this->loadGameSprites( source,
                         image_asset_frames,
                         frames_per_direction,
                         offset,
                         (*direction_game_sprites)[East] );

  offset += frames_per_direction;

  this->loadGameSprites( source,
                         image_asset_frames,
                         frames_per_direction,
                         offset,
                         (*direction_game_sprites)[Southeast] );

  // Cache these sprites for quick lookup later
  d_direction_sprites[source] = direction_game_sprites;
}

// Load the game sprites 
void Character::loadGameSprites( const QString& source,
                                 const QVector<QPixmap>& image_asset_frames,
                                 const int frames_per_direction,
                                 const int offset,
                                 GameSprite& game_sprite )
{
  // This is a new game sprite - initialize it
  if( game_sprite.getNumberOfFrames() == 0 )
  {
    QVector<int> source_frame_indices( frames_per_direction );
    
    for( int i = 0; i < frames_per_direction; ++i )
      source_frame_indices[i] = i + offset;
      
    game_sprite = GameSprite( source, source_frame_indices );
  }

  game_sprite.setAsset( source, image_asset_frames );
}

// Finalize image asset loading
void Character::finalizeImageAssetLoading()
{
  d_sprites_loaded = true;

  this->setActorSprites( d_town_sprites[Inventory::NothingEquiped][Inventory::LowClassArmorEquiped] );
}

// Dump the image assets
void Character::dumpImageAssets()
{
  QMap<QString,std::shared_ptr<Actor::DirectionGameSpriteMap> >::iterator
    asset_sprite_it, asset_sprite_end;
  asset_sprite_it = d_direction_sprites.begin();
  asset_sprite_end = d_direction_sprites.end();

  while( asset_sprite_it != asset_sprite_end )
  {
    if( asset_sprite_it.value() )
    {
      Actor::DirectionGameSpriteMap::iterator direction_sprite_it,
        direction_sprite_end;
      direction_sprite_it = asset_sprite_it.value()->begin();
      direction_sprite_end = asset_sprite_it.value()->end();

      while( direction_sprite_it != direction_sprite_end )
      {
        direction_sprite_it.value().dumpAsset();
        
        ++direction_sprite_it;
      }
    }
    
    ++asset_sprite_it;
  }

  d_sprites_loaded = false;
}

// Enter the town
void Character::enterTown()
{
  d_in_town = true;

  this->updateActorSprites();
  this->setDirection( Direction::South );
}

// Exit the town
void Character::exitTown()
{
  d_in_town = false;

  this->updateActorSprites();
  this->setDirection( Direction::South );
}

// Update the active actor sprites
void Character::updateActorSprites()
{
  if( d_in_town )
  {
    this->setActorSprites(
                 d_town_sprites[d_active_weapon_state][d_active_armor_state] );
  }
  else
  {
    this->setActorSprites( d_dungeon_sprites[d_active_spell_state][d_active_weapon_state][d_active_armor_state] );
  }
}

// Update character stats
void Character::updateStats()
{
  // Update strength
  d_strength = this->getBaseStrength() +
    d_inventory->calculateStrengthModifier();
  emit strengthChanged( d_strength );

  // Update magic
  int magic_modifier = d_inventory->calculateMagicModifier();
  d_magic = this->getBaseMagic() + magic_modifier;
  
  emit magicChanged( this->getBaseMagic(), magic_modifier );

  // Update dexterity
  d_dexterity = this->getBaseDexterity() +
    d_inventory->calculateDexterityModifier();
  emit dexterityChanged( d_dexterity );

  // Update vitality
  int vitality_modifier = d_inventory->calculateVitalityModifier();
  d_vitality = this->getBaseVitality() + vitality_modifier;
    
  emit vitalityChanged( this->getBaseVitality(), vitality_modifier );

  // Update max health
  int health_modifier = d_inventory->calculateHealthModifier();
  d_max_health = this->getBaseHealth() + health_modifier;    
  
  if( d_max_health < this->getHealth() )
    this->setHealth( d_max_health );
  
  emit maxHealthChanged( this->getBaseHealth(), health_modifier );

  // Update max mana
  int mana_modifier = d_inventory->calculateManaModifier();
  d_max_mana = this->getBaseMana() + mana_modifier;
      
  if( d_max_mana < this->getMana() )
    this->setMana( d_max_mana );

  emit maxManaChanged( this->getBaseMana(), mana_modifier );

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
  d_minimum_damage = this->getBaseDamage();
  //   + d_inventory->calculateMinimumDamage();
  //
  d_maximum_damage = this->getBaseDamage();
  //   + d_inventory->calculateMaximumDamage();

  emit statsChanged();
}

// Handle character weapon changed
void Character::handleWeaponChanged( const Inventory::WeaponState state )
{
  if( d_active_weapon_state != state )
  {
    d_active_weapon_state = state;

    this->updateActorSprites();
  }

  this->updateStats();
}

// Handle character shield changed
void Character::handleShieldChanged( const Inventory::WeaponState state )
{
  if( d_active_weapon_state != state )
  {
    d_active_weapon_state = state;

    this->updateActorSprites();
  }

  this->updateStats();
}
// Handle character ring changed
void Character::handleRingChanged()
{
  this->updateStats();
}

// Handle character amulet changed
void Character::handleAmuletChanged()
{
  this->updateStats();
}

// Handle character armor changed
void Character::handleArmorChanged( const Inventory::ChestArmorState state )
{
  if( d_active_armor_state != state )
  {
    d_active_armor_state = state;

    this->updateActorSprites();
  }

  this->updateStats();
}

// Handle character helmet changed
void Character::handleHelmetChanged()
{
  this->updateStats();
}

// Handle character spell changed
void Character::handleSpellChanged( const SpellBook::SpellState state )
{
  if( d_active_spell_state != state )
  {
    d_active_spell_state = state;

    this->updateActorSprites();
  }
}

// Connect to base stats changed signal
void Character::connectToBaseStatsChangedSignal()
{
  QObject::connect( this, SIGNAL(baseStatsChanged()),
                    this, SLOT(updateStats()) );
}

// Connect to inventory signals
void Character::connectInventorySignalsToCharacterSlots()
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

// Connect to spell book signals
void Character::connectSpellBookSignalsToCharacterSlots()
{
  QObject::connect( d_spell_book, SIGNAL(spellChanged(const SpellBook::SpellState)),
                    this, SLOT(handleSpellChanged(const SpellBook::SpellState)) );
}

QML_REGISTER_BASE_TYPE( Character );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Character.cpp
//---------------------------------------------------------------------------//
