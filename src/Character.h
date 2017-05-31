//---------------------------------------------------------------------------//
//!
//! \file   Character.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The character base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CHARACTER_H
#define CHARACTER_H

// QtD1 Includes
#include "QMLRegistrationHelper.h"
#include "Actor.h"
#include "Inventory.h"
#include "SpellBook.h"
#include "QuestLog.h"

namespace QtD1{

/*! The character base class
 *
 * Objects of this class can be passed by value without copy overhead because
 * this class uses implicit data sharing.
 */
class Character : public Actor
{
  Q_OBJECT
  Q_PROPERTY(QString name READ getName)
  Q_PROPERTY(int type READ getType)
  Q_PROPERTY(int level READ getLevel)
  Q_PROPERTY(int strength READ getStrength)
  Q_PROPERTY(int magic READ getMagic)
  Q_PROPERTY(int dexterity READ getDexterity)
  Q_PROPERTY(int vitality READ getVitality)
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Character" )

public:

  //! Character type enum
  enum Type{
    Rogue = 0,
    Sorcerer,
    Warrior
  };
  Q_ENUMS(Type)

  //! Restore the character from a save state
  static Character* restore( const QString& name );

  //! Destructor
  virtual ~Character();

  //! Get the name
  QString getName() const;

  //! Get the character type
  virtual Type getType() const = 0;

  //! Get the experience
  int getExperience() const;

  //! Get the next level experience threshold
  int getNextLevelExperienceThreshold();

  //! Get experience to next level threshold
  int getExperienceToNextLevelThreshold();

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

  //! Get the gold amount
  int getGold();

  //! Get the inventory
  const Inventory& getInventory() const;

  //! Get the inventory
  Inventory& getInventory();

  //! Get the spell book
  const SpellBook& getSpellBook() const;

  //! Get the spell book
  SpellBook& getSpellBook();

  //! Get the quest log
  const QuestLog& getQuestLog() const;

  //! Get the quest log
  QuestLog& getQuestLog();

  //! Check if the image assets have been loaded
  bool imageAssetsLoaded() const override;

  //! Load the image asset
  void loadImageAsset( const QString& image_asset_name,
                       const QVector<QPixmap>& image_asset_frames ) override;

  //! Finalize image asset loading
  void finalizeImageAssetLoading() override;

  //! Dump the image assets
  void dumpImageAssets() override;

signals:

  //! Character leveled up
  void levelUp( const int new_level );

  //! Character strength changed
  void strengthChanged( int total_strength );

  //! Character dexterity changed
  void dexterityChanged( int total_dexterity );

  //! Character vitality changed
  void vitalityChanged( int character_vitality, int inventory_vitality );

  //! Character magic changed
  void magicChanged( int character_magic, int inventory_magic );

  //! Character max health changed
  void maxHealthChanged( int base_health, int inventory_health );

  //! Character max mana changed
  void maxManaChanged( int base_mana, int inventory_mana );

  //! Character stats changed
  void statsChanged();

  //! Town entered
  void townEntered();

  //! Town exited
  void townExited();

public slots:

  //! Add to experience
  void addExperience( const int experience );

  //! Update the character stats
  void updateStats();

  //! Enter the town
  void enterTown();

  //! Exit the town
  void exitTown();

private slots:

  void incrementLevel();
  void handleWeaponChanged( const Inventory::WeaponState state );
  void handleShieldChanged( const Inventory::WeaponState state );
  void handleRingChanged();
  void handleAmuletChanged();
  void handleArmorChanged( const Inventory::ChestArmorState state );
  void handleHelmetChanged();
  void handleSpellChanged( const SpellBook::SpellState state );
  void updateActorSprites();

protected:

  // The states type associated with an asset (bool = true for in town)
  struct States{
    Actor::State actor_state;
    bool in_town;
    Inventory::ChestArmorState armor_state;
    Inventory::WeaponState weapon_state;
    SpellBook::SpellState spell_state;
  };

  // The armor class state sprites type
  typedef QMap<Inventory::ChestArmorState,std::shared_ptr<ActorData::StateDirectionGameSpriteMap> > ArmorClassStateGameSpriteMap;

  // The weapon state sprites type
  typedef QMap<Inventory::WeaponState,ArmorClassStateGameSpriteMap> WeaponAndArmorClassStateGameSpriteMap;

  // The spell state sprites type
  typedef QMap<SpellBook::SpellState,WeaponAndArmorClassStateGameSpriteMap> SpellWeaponAndArmorClassStateGameSpriteMap;

  //! Constructor
  Character( const QString& name,
             Inventory* inventory,
             SpellBook* spell_book,
             QGraphicsObject* parent = 0 );

  //! Update character stats
  void updateStats();

  //! Get the states associated with the image asset
  virtual const States& getImageAssetStates(
                                   const QString& image_asset_name ) const = 0;

  //! Get the number of sprite sheet frames per direction
  virtual int getSpriteSheetFramesPerDirection( const States& states ) const = 0;

private:

  //! Copy constructor
  Character( const Character& other_character );

  //! Assignment operator
  Character& operator=( const Character& other_character );

  //! Initialize the state machine
  void initializeStateMachine( QStateMachine& state_machine ) override;

  //! Create the transition to the attacking state
  QAbstractTransition* createTransitionToAttackingState() override;

  //! Create the transition to the walking state
  QAbstractTransition* createTransitionToWalkingState() override;

  //! Create the transition to the standing state
  QAbstractTransition* createTransitionToStandingState() override;

  //! Create the transition to the casting state
  QAbstractTransition* createTransitionToCastingState() override;
  
  // Connect to base stats changed signal
  void connectToBaseStatsChangedSignal();

  // Connect to inventory signals
  void connectInventorySignalsToCharacterSlots();

  // Connect to spell book signals
  void connectSpellBookSignalsToCharacterSlots();

  // Load the town state game sprites
  void loadTownStateGameSprites( const QString& image_asset_name,
                                 const QVector<QPixmap>& image_asset_frames,
                                 const int frames_per_direction,
                                 const Inventory::WeaponState weapon_state,
                                 const Inventory::ChestArmorState armor_state,
                                 const Actor::State actor_state );

  // Load the non-spell cast dungeon state game sprites
  void loadNonSpellCastDungeonStateGameSprites(
                                 const QString& image_asset_name,
                                 const QVector<QPixmap>& image_asset_frames,
                                 const int frames_per_direction,
                                 const Inventory::WeaponState weapon_state,
                                 const Inventory::ChestArmorState armor_state,
                                 const Actor::State actor_state );

  // Load the spell cast dungeon state game sprites
  void loadSpellCastDungeonStateGameSprites(
                                const QString& image_asset_name,
                                const QVector<QPixmap>& image_asset_frames,
                                const int frames_per_direction,
                                const SpellBook::SpellState spell_state,
                                const Inventory::WeaponState weapon_state,
                                const Inventory::ChestArmorState armor_state );

  // Load the direction game sprites
  void loadDirectionGameSprites(
                            const QString& source,
                            const QVector<QPixmap>& image_asset_frames,
                            const int frames_per_direction,
                            std::shared_ptr<Actor::DirectionGameSpriteMap>&
                            direction_game_sprites );

  // Load the game sprites 
  void loadGameSprites( const QString& source,
                        const QVector<QPixmap>& image_asset_frames,
                        const int frames_per_direction,
                        const int offset,
                        GameSprite& game_sprite );

  // Update the actor sprites
  void updateActorSprites();

  // The character name
  QString d_name;

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

Q_DECLARE_METATYPE( QtD1::Character::Type )

#endif // end CHARACTER_H

//---------------------------------------------------------------------------//
// end Character.h
//---------------------------------------------------------------------------//
