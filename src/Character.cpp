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
#include "CharacterData.h"

namespace QtD1{

// Constructor
Character::Character( QGraphicsObject* parent )
  : Actor( parent )
{
  // Frontend proxies do not need to display anything
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );
}

// Copy constructor
/*! \details This constructor should only be called by the qml engine.
 */
Character::Character( const Character& other_character )
  : Actor( other_character )
{
  // Frontend proxies do not need to display anything
  this->setFlag( QGraphicsItem::ItemHasNoContents, true );

  // Connect to the character data signals
  this->connectCharacterDataSignalsToCharacterSlots();
}

// Constructor
Character::Character( CharacterData* data, QGraphicsObject* parent )
  : Actor( data, parent )
{
  this->connectCharacterDataSignalsToCharacterSlots();
}

// Assignment operator
/*! \details This operator should only be called by the qml engine.
 */
Character& Character::operator=( const Character& other_character )
{
  if( this != &other_character )
  {
    this->disconnectCharacterSlotsFromCharacterDataSignals();

    Actor::operator=( other_character );

    // Connect to the character data signals
    this->connectCharacterDataSignalsToCharacterSlots();

    // Frontend proxies do not need to display anything
    this->setFlag( QGraphicsItem::ItemHasNoContents, true );
  }

  return *this;
}



// Get the name
QString Character::getName() const
{
  return this->getCharacterData()->getName();
}

// Get the character type
Character::Type Character::getType() const
{
  return this->getCharacterData()->getType();
}

// Increment the level
void Character::incrementLevel()
{
  this->getCharacterData()->incrementLevel();
}

// Set the experience
void Character::setExperience( const int experience )
{
  this->getCharacterData()->setExperience( experience );
}

// Add to experience
void Character::addExperience( const int experience )
{
  this->getCharacterData()->addExperience( experience );
}

// Get the experience
int Character::getExperience() const
{
  return this->getCharacterData()->getExperience();
}

// Get the next level experience threshold
int Character::getNextLevelExperienceThreshold()
{
  return this->getCharacterData()->getNextLevelExperienceThreshold();
}

// Get experience to next level threshold
int Character::getExperienceToNextLevelThreshold()
{
  return std::max( this->getCharacterData()->getNextLevelExperienceThreshold() - this->getCharacterData()->getExperience(), 0 );
}

// Get the gold amount
int Character::getGold()
{
  return this->getCharacterData()->getGold();
}

// Get the inventory
const Inventory& Character::getInventory() const
{
  return this->getCharacterData()->getInventory();
}

// Get the inventory
Inventory& Character::getInventory()
{
  return this->getCharacterData()->getInventory();
}

// Get the spell book
const SpellBook& Character::getSpellBook() const
{
  return this->getCharacterData()->getSpellBook();
}

// Get the spell book
SpellBook& Character::getSpellBook()
{
  return this->getCharacterData()->getSpellBook();
}

// Get the quest log
const QuestLog& Character::getQuestLog() const
{
  return this->getCharacterData()->getQuestLog();
}

// Get the quest log
QuestLog& Character::getQuestLog()
{
  return this->getCharacterData()->getQuestLog();
}

// Check if the image assets have been loaded
bool Character::imageAssetsLoaded() const
{
  return this->getCharacterData()->spritesLoaded();
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
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>& actor_state_direction_sprite_map =
    this->getCharacterData()->getCharacterTownSprites()[weapon_state][armor_state];

  if( !actor_state_direction_sprite_map )
  {
    actor_state_direction_sprite_map.reset(
                                      new Actor::StateDirectionGameSpriteMap );
  }

  std::shared_ptr<Actor::DirectionGameSpriteMap>&
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
    this->getCharacterData()->getCharacterDungeonSprites()[SpellBook::NoSpellEquiped][weapon_state][armor_state];

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
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>&
    non_elemental_spell_state_direction_game_sprite_map = this->getCharacterData()->getCharacterDungeonSprites()[SpellBook::NonElementalSpellEquiped][weapon_state][armor_state];

  if( !non_elemental_spell_state_direction_game_sprite_map )
  {
    non_elemental_spell_state_direction_game_sprite_map.reset(
                                      new Actor::StateDirectionGameSpriteMap );
  }

  (*non_elemental_spell_state_direction_game_sprite_map)[actor_state] =
    direction_game_sprites;

  // Set the fire spell equiped state
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>&
    fire_spell_state_direction_game_sprite_map = this->getCharacterData()->getCharacterDungeonSprites()[SpellBook::NonElementalSpellEquiped][weapon_state][armor_state];

  if( !fire_spell_state_direction_game_sprite_map )
  {
    fire_spell_state_direction_game_sprite_map.reset(
                                  new Actor::StateDirectionGameSpriteMap );
  }

  (*fire_spell_state_direction_game_sprite_map)[actor_state] =
    direction_game_sprites;

  // Set the lightning spell equiped state
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>&
    lightning_spell_state_direction_game_sprite_map = this->getCharacterData()->getCharacterDungeonSprites()[SpellBook::NonElementalSpellEquiped][weapon_state][armor_state];

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
  std::shared_ptr<Actor::StateDirectionGameSpriteMap>&
    spell_cast_state_direction_game_sprite_map = this->getCharacterData()->getCharacterDungeonSprites()[spell_state][weapon_state][armor_state];

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
  this->getCharacterData()->getDirectionSprites()[source] =
    direction_game_sprites;
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
  this->getCharacterData()->setSpritesLoaded();
  this->setActorSprites( this->getCharacterData()->getCharacterTownSprites()[Inventory::NothingEquiped][Inventory::LowClassArmorEquiped] );
}

// Dump the image assets
void Character::dumpImageAssets()
{
  QMap<QString,std::shared_ptr<Actor::DirectionGameSpriteMap> >::iterator
    asset_sprite_it, asset_sprite_end;
  asset_sprite_it = this->getCharacterData()->getDirectionSprites().begin();
  asset_sprite_end = this->getCharacterData()->getDirectionSprites().end();

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

  this->getCharacterData()->setSpritesNotLoaded();
}

// Enter the town
void Character::enterTown()
{
  this->getCharacterData()->enterTown();
}

// Exit the town
void Character::exitTown()
{
  this->getCharacterData()->enterTown();
}

void Character::handleLevelUpInCharacterData( const int new_level )
{
  emit levelUp( new_level );
}

void Character::handleStatsChangedInCharacterData()
{
  emit statsChanged();
}

// Connect character data signals to character slots
void Character::connectCharacterDataSignalsToCharacterSlots()
{
  QObject::connect( this->getCharacterData(), SIGNAL(levelUp(const int)),
                    this, SLOT(handleLevelUpInCharacterData(const int)) );
  QObject::connect( this->getCharacterData(), SIGNAL(statsChanged()),
                    this, SLOT(handleStatsChangedInCharacterData()) );
}

// Disconnect character slots from character data signals
void Character::disconnectCharacterSlotsFromCharacterDataSignals()
{
  QObject::disconnect( this->getCharacterData(), SIGNAL(levelUp(const int)),
                       this, SLOT(handleLevelUpInCharacterData(const int)) );
  QObject::disconnect( this->getCharacterData(), SIGNAL(statsChanged()),
                       this, SLOT(handleStatsChangedInCharacterData()) );
}

// Update character stats
void Character::updateStats()
{
  this->getCharacterData()->updateStats();
}

// Get the character data
CharacterData* Character::getCharacterData()
{
  return dynamic_cast<CharacterData*>( this->getActorData() );
}

// Get the character data
const CharacterData* Character::getCharacterData() const
{
  return dynamic_cast<const CharacterData*>( this->getActorData() );
}

QML_REGISTER_BASE_TYPE( Character );

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Character.cpp
//---------------------------------------------------------------------------//
