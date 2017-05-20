//---------------------------------------------------------------------------//
//!
//! \file   CharacterData.h
//! \author Alex Robinson
//! \brief  Character data class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QObject>
#include <QString>

// QtD1 Includes
#include "Character.h"
#include "ActorData.h"
#include "Inventory.h"
#include "SpellBook.h"
#include "QuestLog.h"

namespace QtD1{

//! The character data
class CharacterData : public ActorData
{
  Q_OBJECT

public:

  // The armor class state sprites type
  typedef QMap<Inventory::ChestArmorState,std::shared_ptr<ActorData::StateDirectionGameSpriteMap> > ArmorClassStateGameSpriteMap;

  // The weapon state sprites type
  typedef QMap<Inventory::WeaponState,ArmorClassStateGameSpriteMap> WeaponAndArmorClassStateGameSpriteMap;

  // The spell state sprites type
  typedef QMap<SpellBook::SpellState,WeaponAndArmorClassStateGameSpriteMap> SpellWeaponAndArmorClassStateGameSpriteMap;

  //! Constructor
  CharacterData( QObject* parent = 0 );

  //! Constructor
  CharacterData( const QString& character_name,
                 const Character::Type character_type,
                 QObject* parent = 0 );

  // Assignment operator
  CharacterData& operator=( const CharacterData& other_data );

  //! Destructor
  ~CharacterData();

  //! Get the name
  QString getName() const;

  //! Get the character type
  Character::Type getType() const;

  //! Set the experience
  void setExperience( const int experience );

  //! Get the experience
  int getExperience() const;

  //! Get the next level experience threshold
  int getNextLevelExperienceThreshold();

  //! Get the gold amount
  int getGold();

  //! Get the strength
  int getStrength() const override;

  //! Get the magic
  int getMagic() const override;

  //! Get the dexterity
  int getDexterity() const override;

  //! Get the vitality
  int getVitality() const override;

  //! Get the max health
  int getMaxHealth() const override;

  //! Get the max mana
  int getMaxMana() const override;

  //! Get the magic resistance
  qreal getMagicResistance() const override;

  //! Get the fire resistance
  qreal getFireResistance() const override;

  //! Get the lightning resistance
  qreal getLightningResistance() const override;

  //! Get the armor class
  int getArmorClass() const override;

  //! Get the minimum damage
  int getMinimumDamage() const override;

  //! Get the maximum damage
  int getMaximumDamage() const override;

  //! Get the percent chance to hit with melee weapon
  qreal getChanceToHitWithMeleeWeapon() const override;

  //! Get the percent chance to hit with ranged weapon
  qreal getChanceToHitWithRangedWeapon() const override;

  //! Get the chance to hit with a spell
  qreal getChanceToHitWithSpell() const override;

  //! Get the inventory
  Inventory& getInventory();

  //! Get the inventory
  const Inventory& getInventory() const;

  //! Get the spell book
  SpellBook& getSpellBook();

  //! Get the spell book
  const SpellBook& getSpellBook() const;

  //! Get the quest log
  QuestLog& getQuestLog();

  //! Get the quest log
  const QuestLog& getQuestLog() const;

  //! Get the character dungeon sprites
  SpellWeaponAndArmorClassStateGameSpriteMap& getCharacterDungeonSprites();

  //! Get the character dungeon sprites
  const SpellWeaponAndArmorClassStateGameSpriteMap&
  getCharacterDungeonSprites() const;

  //! Get the character town sprites
  WeaponAndArmorClassStateGameSpriteMap& getCharacterTownSprites();

  //! Get the character town sprites
  const WeaponAndArmorClassStateGameSpriteMap& getCharacterTownSprites() const;

  //! Get the state direction sprites
  QMap<QString,std::shared_ptr<ActorData::DirectionGameSpriteMap> >&
  getDirectionSprites();

  //! Get the state direction sprites
  const QMap<QString,std::shared_ptr<ActorData::DirectionGameSpriteMap> >&
  getDirectionSprites() const;

  //! Check if the sprites have been loaded
  bool spritesLoaded() const;

  //! The sprites have been loaded
  void setSpritesLoaded();

  //! The sprites have not been loaded
  void setSpritesNotLoaded();

  //! Get the active armor state
  Inventory::ChestArmorState getActiveArmorState() const;

  //! Get the active weapon state
  Inventory::WeaponState getActiveWeaponState() const;

  //! Get the active spell state
  SpellBook::SpellState getActiveSpellState() const;

  //! Check if the character is in town
  bool isInTown() const;


signals:

  void levelUp( const int new_level );
  void strengthChanged( int total_strength );
  void dexterityChanged( int total_dexterity );
  void vitalityChanged( int character_vitality, int inventory_vitality );
  void magicChanged( int character_magic, int inventory_magic );
  void statsChanged();
  void characterStateChanged();

public slots:

  void incrementLevel();
  void addExperience( const int experience );
  void updateStats();
  void enterTown();
  void exitTown();

private slots:

  void handleWeaponChanged( const Inventory::WeaponState state );
  void handleShieldChanged( const Inventory::WeaponState state );
  void handleRingChanged();
  void handleAmuletChanged();
  void handleArmorChanged( const Inventory::ChestArmorState state );
  void handleHelmetChanged();
  void handleSpellChanged( const SpellBook::SpellState state );
  void updateActorSprites();

private:

  // Connect to base stats changed signal
  void connectToBaseStatsChangedSignal();

  // Connect to inventory signals
  void connectInventorySignalsToCharacterDataSlots();

  // Disconnect from inventory signals
  void disconnectCharacterDataSlotsFromInventorySignals();

  // Connect to spell book signals
  void connectSpellBookSignalsToCharacterDataSlots();

  // Disconnect from spell book signals
  void disconnectCharacterDataSlotsFromSpellBookSignals();

  // The character name
  QString d_name;

  // The character type
  Character::Type d_type;

  // The character experience
  int d_experience;

  // The next level experience threshold
  int d_next_level_experience_threshold;

  // The gold amount
  int d_gold;

  // The character strength
  int d_strength;

  // The character magic
  int d_magic;

  // The character dexterity
  int d_dexterity;

  // The character vitality
  int d_vitality;

  // The character max health
  int d_max_health;

  // The character max mana
  int d_max_mana;

  // The character magic resistance
  int d_magic_resistance_fraction;

  // The character fire resistance
  int d_fire_resistance_fraction;

  // The character lightning resistance
  int d_lightning_resistance_fraction;

  // The character armor class
  int d_armor_class;

  // The character minimum damage
  int d_minimum_damage;

  // The character maximum damage
  int d_maximum_damage;

  // The chance to hit with melee weapon
  qreal d_chance_to_hit_with_melee;

  // The chance to hit with ranged weapon
  qreal d_chance_to_hit_with_ranged;

  // The chance to hit with spell
  qreal d_chance_to_hit_with_spell;

  // The inventory
  Inventory* d_inventory;

  // The spell book
  SpellBook* d_spell_book;

  // The quest log
  QuestLog* d_quest_log;

  // The character dungeon sprites
  SpellWeaponAndArmorClassStateGameSpriteMap d_dungeon_sprites;

  // The character town sprites
  WeaponAndArmorClassStateGameSpriteMap d_town_sprites;

  // The direction sprites
  QMap<QString,std::shared_ptr<ActorData::DirectionGameSpriteMap> >
  d_direction_sprites;

  // Records if the sprites have been loaded
  bool d_sprites_loaded;

  // The active character states
  Inventory::ChestArmorState d_active_armor_state;
  Inventory::WeaponState d_active_weapon_state;
  SpellBook::SpellState d_active_spell_state;
  bool d_in_town;
};

} // end QtD1 namespace

#endif // end CHARACTER_DATA_H

//---------------------------------------------------------------------------//
// end CharacterData.h
//---------------------------------------------------------------------------//
