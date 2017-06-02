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
#include "CharacterStats.h"
#include "Inventory.h"
#include "SpellBook.h"
#include "QuestLog.h"

namespace QtD1{

class CharacterData;

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

  //! The character town state enum
  enum TownState{
    StandingInTown = -2,
    WalkingInTown = -1
  };

  //! Restore the character from a save state
  static Character* restore( const QString& name );

  //! Constructor
  Character( QGraphicsObject* parent = 0 );

  //! Copy constructor
  Character( const Character& other_character );

  //! Assignment operator
  Character& operator=( const Character& other_character );

  //! Destructor
  virtual ~Character()
  { /* ... */ }

  //! Get the name
  QString getName() const;

  //! Get the character type
  Type getType() const;

  //! Increment the level
  void incrementLevel();

  //! Set the experience
  void setExperience( const int experience );

  //! Add to experience
  void addExperience( const int experience );

  //! Get the experience
  int getExperience() const;

  //! Get the next level experience threshold
  int getNextLevelExperienceThreshold();

  //! Get experience to next level threshold
  int getExperienceToNextLevelThreshold();

  //! Get the gold amount
  int getGold();

  //! Get the character stats
  const CharacterStats& getCharacterStats() const;

  //! Get the character stats
  CharacterStats& getCharacterStats();

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

  //! Character stats changed
  void statsChanged();

public slots:

  //! Enter the town
  void enterTown();

  //! Exit the town
  void exitTown();

private slots:

  //! Forward level up signal in character data to level up signal
  void handleLevelUpInCharacterData( const int new_level );

  //! Forward stats changed signal in character data to stats changed signal
  void handleStatsChangedInCharacterData();

protected:

  // The states type associated with an asset (bool = true for in town)
  struct States{
    Actor::State actor_state;
    bool in_town;
    Inventory::ChestArmorState armor_state;
    Inventory::WeaponState weapon_state;
    SpellBook::SpellState spell_state;
  };

  //! Constructor
  Character( CharacterData* data, QGraphicsObject* parent = 0 );

  //! Update character stats
  void updateStats();

  //! Get the states associated with the image asset
  virtual const States& getImageAssetStates(
                                   const QString& image_asset_name ) const = 0;

  //! Get the number of sprite sheet frames per direction
  virtual int getSpriteSheetFramesPerDirection( const States& states ) const = 0;

  //! Get the character data
  CharacterData* getCharacterData();

  //! Get the character data
  const CharacterData* getCharacterData() const;

private:

  // Connect character data signals to character slots
  void connectCharacterDataSignalsToCharacterSlots();

  // Disconnect character slots from character data signals
  void disconnectCharacterSlotsFromCharacterDataSignals();

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

  // The character data
  std::shared_ptr<CharacterData> d_data;
};

} // end QtD1 namespace

Q_DECLARE_METATYPE( QtD1::Character::Type )

#endif // end CHARACTER_H

//---------------------------------------------------------------------------//
// end Character.h
//---------------------------------------------------------------------------//
