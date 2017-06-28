//---------------------------------------------------------------------------//
//!
//! \file   Warrior.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The warrior class declaration
//!
//---------------------------------------------------------------------------//

#ifndef WARRIOR_H
#define WARRIOR_H

// Std Lib Includes
#include <utility>
#include <tuple>

// QtD1 Includes
#include "Character.h"

namespace QtD1{

//! The warrior class
class Warrior : public Character
{
  Q_OBJECT
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Warrior" )

public:

  //! Default constructor
  Warrior( QGraphicsObject* parent = 0 );

  //! Copy constructor
  Warrior( const Warrior& other_warrior );

  //! Constructor
  Warrior( const QString& name, QGraphicsObject* parent = 0 );

  //! Destructor
  ~Warrior()
  { /* ... */ }

  //! Get the character type
  Character::Type getType() const override;

  //! Get the warrior description
  QString getDescription() const override;

  //! Get the max health
  int getBaseHealth() const override;

  //! Get the max mana
  int getBaseMana() const override;

  //! Get base the damage
  int getBaseDamage() const override;

  //! Get the base armor class
  int getBaseArmorClass() const override;

  //! Get the base percent chance to hit with melee
  qreal getBaseChanceToHitWithMeleeWeapon() const override;

  //! Get the base percent chance to hit with ranged
  qreal getBaseChanceToHitWithRangedWeapon() const override;

  //! Get the base percent chance to hit with spell
  qreal getBaseChanceToHitWithSpell() const override;

  //! Get the number of image assets used by the object
  int getNumberOfImageAssets() const override;

  //! Get the image asset names used by the object
  void getImageAssetNames( QSet<QString>& image_asset_names ) const override;

  //! Check if an image asset is used
  bool isImageAssetUsed( const QString& image_asset_name ) const override;

private slots:

  void handleStrengthChange( int total_strength );
  void handleDexterityChange( int total_dexterity );
  void handleVitalityChange( int character_vitality, int inventory_vitality );
  void handleMagicChange( int character_magic, int inventory_magic );
  void handleLevelUp( const int level );

private:

  // The map type of assets and the corresponding character states
  typedef QMap<QString,Character::States> AssetStateMap;

  // Initialize asset state map
  static void initializeAssetStateMap();

  // Get the asset state map
  static const AssetStateMap& getAssetStateMap();

  // Initialize warrior stats
  void initializeStats();

  // Get the states associated with the image asset
  const Character::States& getImageAssetStates(
                              const QString& image_asset_name ) const override;

  // Get the number of sprite sheet frames per direction
  int getSpriteSheetFramesPerDirection( const States& states ) const override;

  // Get the duration of a sprite sheet frame (in game tics)
  int getSpriteSheetFrameDuration( const States& states ) const override;

  // Connect the stats changed signal to warrior slots
  void connectStatChangeSignalToWarriorSlots();

  // Calculate the base chance to hit with a melee weapon
  void calculateBaseChanceToHitWithMelee();

  // Calculate the base chance to hit with a ranged weapon
  void calculateBaseChanceToHitWithRanged();

  // Calculate the base chance to hit with a spell
  void calculateBaseChanceToHitWithSpell();

  // Calculate the base damage
  void calculateBaseDamage();

  // Calculate the base health
  void calculateBaseHealth();

  // Calculate the base mana
  void calculateBaseMana();

  // The warrior image asset names
  static AssetStateMap s_asset_state_map;

  // The warrior base health
  int d_base_health;

  // The warrior base mana
  int d_base_mana;

  // The warrior damage
  int d_base_damage;

  // The warrior armor class
  int d_base_armor_class;

  // The chance to hit with melee weapon
  qreal d_base_chance_to_hit_with_melee;

  // The chance to hit with ranged weapon
  qreal d_base_chance_to_hit_with_ranged;

  // The chance to hit with spell
  qreal d_base_chance_to_hit_with_spell;
};

} // end QtD1 namespace

Q_DECLARE_METATYPE( QtD1::Warrior )
Q_DECLARE_METATYPE( QtD1::Warrior* )

#endif // end WARRIOR_H

//---------------------------------------------------------------------------//
// end Warrior.h
//---------------------------------------------------------------------------//
