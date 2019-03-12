//---------------------------------------------------------------------------//
//!
//! \file   CharacterStats.h
//! \author Sean Robinson, Alex Robinson
//! \brief  The character stats menu class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CHARACTER_STATS_H
#define CHARACTER_STATS_H

// Std Lib Includes
#include <memory>
#include <tuple>

// Qt Includes
#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QPushButton>

namespace QtD1{

class Character;

//! The spell book class
class CharacterStats : public QWidget
{
  Q_OBJECT

public:

  //! Constructor
  CharacterStats( Character* character, QWidget* parent = 0 );

  //! Destructor
  ~CharacterStats()
  { /* ... */ }

  //! Get the character name
  QString getName() const;

  //! Get the character type
  int getType() const;

  //! Get the character level
  int getLevel() const;

  //! Get the character experience
  int getExperience() const;

  //! Get the next level character experience
  int getNextLevelExperienceThreshold() const;

  //! Get the amount of gold the character is holding
  int getGold() const;

  //! Get the base strength
  int getBaseStrength() const;

  //! Get the strength
  int getStrength() const;

  //! Get the base magic
  int getBaseMagic() const;

  //! Get the magic
  int getMagic() const;

  //! Get the base dexterity
  int getBaseDexterity() const;

  //! Get the dexterity
  int getDexterity() const;

  //! Get the base vitality
  int getBaseVitality() const;

  //! Get the vitality
  int getVitality() const;

  //! Get the base health
  int getBaseHealth() const;

  //! Get the max health
  int getMaxHealth() const;

  //! Get the health
  int getHealth() const;

  //! Get the base mana
  int getBaseMana() const;

  //! Get the max mana
  int getMaxMana() const;

  //! Get the mana
  int getMana() const;

  //! Get the magic resistance
  qreal getMagicResistance() const;

  //! Get the fire resistance
  qreal getFireResistance() const;

  //! Get the lightning resistance
  qreal getLightningResistance() const;

  //! Get the armor class
  int getArmorClass() const;

  //! Get the minimum damage
  int getMinimumDamage() const;

  //! Get the maximum damage
  int getMaximumDamage() const;

  //! Get the chance to hit with melee weapon
  qreal getChanceToHitWithMeleeWeapon() const;

signals:

  void healthChanged( const int current_health, const int max_health );
  void manaChanged( const int current_mana, const int max_mana );
  void baseStatsChanged();
  void statsChanged();
  void levelUp( const int new_level );
  void death();

public slots:

  //! Update the labels
  void updateLabels();

  //! Increment the base strength
  void incrementBaseStrength();

  //! Increment the base magic
  void incrementBaseMagic();

  //! Increment the base dexterity
  void incrementBaseDexterity();

  //! Increment the base vitality
  void incrementBaseVitality();

//private slots:
//
//   // Forward mana changed in character backend to frontend
//   void forwardManaChangedToFrontend( const int current_mana );
//
//   // Forward base stats changed in character backend to frontend
//   void forwardBaseStatsChangedToFrontend();
//
//   // Forward stats changed in character backend to frontend
//   void forwardStatsChangedToFrontend();
//
//   // Forward level up to frontend
//   void forwardLevelUpToFrontend( const int new_level );
//
//   // Forward death to frontend
//   void forwardDeathToFrontend();

private:

  // Create and place dynamic labels
  void createLabels();

  static const QString s_style_sheet;

  // Size of name and type labels
  static const QSize s_name_type_size;

  // Size of core character stats labels
  static const QSize s_core_stats_size;

  // Size of the expericence and gold labels
  static const QSize s_exp_gold_size;

  // Size of the advanced character stats labels
  static const QSize s_advanced_stats_size;

  // The Character
  Character* d_character;

  // The character name
  QLabel* d_character_name;

  // The character type
  QLabel* d_character_type;

  // The character level
  QLabel* d_character_level;

  // The character experience
  QLabel* d_character_experience;

  // The character next level experience threshold
  QLabel* d_character_next_level_experience_threshold;

  // The character gold amount
  QLabel* d_character_gold;

  // The character base strength
  QLabel* d_character_base_strength;

  // The character current strength
  QLabel* d_character_current_strength;

  // The character magic
  QLabel* d_character_base_magic;

  // The character current magic
  QLabel* d_character_current_magic;

  // The character base dexterity
  QLabel* d_character_base_dexterity;

  // The character current dexterity
  QLabel* d_character_current_dexterity;

  // The character base vitality
  QLabel* d_character_base_vitality;

  // The character current vitality
  QLabel* d_character_current_vitality;

  // The character base health
  QLabel* d_character_base_health;

  // The character current health
  QLabel* d_character_current_health;

  // The character base mana
  QLabel* d_character_base_mana;

  // The character current mana
  QLabel* d_character_current_mana;

  // The character magic resistance
  QLabel* d_character_magic_resistance;

  // The character fire resistance
  QLabel* d_character_fire_resistance;

  // The character lightning resistance
  QLabel* d_character_lightning_resistance;

  // The character armor class
  QLabel* d_character_armor_class;

  // The character damage
  QLabel* d_character_damage;

  // The character chance to hit
  QLabel* d_character_chance_to_hit;
};

} // end QtD1 namespace

#endif // end CHARACTER_STATS_H

//---------------------------------------------------------------------------//
// end CharacterStats.h
//---------------------------------------------------------------------------//
