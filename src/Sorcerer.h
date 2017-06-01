//---------------------------------------------------------------------------//
//!
//! \file   Sorcerer.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The sorcerer class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SORCERER_H
#define SORCERER_H

// QtD1 Includes
#include "Character.h"

namespace QtD1{

//! The sorcerer class
class Sorcerer : public Character
{
  Q_OBJECT
  Q_IMPORT_ALIAS( "QtD1", 1, 0, "Sorcerer" )
  
public:

  //! Default constructor
  Sorcerer( QGraphicsObject* parent = 0 );

  //! Copy constructor
  Sorcerer( const Sorcerer& other_sorcerer );

  //! Constructor
  Sorcerer( const QString& name, QGraphicsObject* parent = 0 );

  //! Destructor
  ~Sorcerer()
  { /* ... */ }

  //! Get the character type
  Character::Type getType() const override;

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

  //! Get the number of sprite sheet frames per direction
  int getSpriteSheetFramesPerDirection( const States& states ) const override;

  void connectStatChangeSignalToSorcererSlots();

  void calculateBaseChanceToHitWithMelee();

  void calculateBaseChanceToHitWithRanged();

  void calculateBaseChanceToHitWithSpell();

  void calculateBaseDamage();

  void calculateBaseHealth();

  void calculateBaseMana();

  // The sorcerer image asset names
  static AssetStateMap s_asset_state_map;

  // The sorcerer max health
  int d_base_health;

  // The sorcerer max mana
  int d_base_mana;

  // The sorcerer damage
  int d_base_damage;

  // The sorcerer armor class
  int d_base_armor_class;

  // The chance to hit with melee weapon
  qreal d_base_chance_to_hit_with_melee;

  // The chance to hit with ranged weapon
  qreal d_base_chance_to_hit_with_ranged;

  // The chance to hit with spell
  qreal d_base_chance_to_hit_with_spell;
};

} // end QtD1 namespace

Q_DECLARE_METATYPE( QtD1::Sorcerer )
Q_DECLARE_METATYPE( QtD1::Sorcerer* )

#endif // end SORCERER_H

//---------------------------------------------------------------------------//
// end Sorcerer.h
//---------------------------------------------------------------------------//
