//---------------------------------------------------------------------------//
//!
//! \file   Spell.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The spell base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SPELL_H
#define SPELL_H

// Qt Includes
#include <QImage>

// QtD1 Includes
#include "LevelObject.h"

namespace QtD1 {

//! The spell base class
class Spell
{

public:

  // The spell types
  enum Type{
    // Inherited Skill
    FireBolt = 0,
    ChargedBolt = 38,
    HolyBolt = 41,
    Heal = 1,
    HealOther = 9,
    Inferno = 14,
    Resurrect = 40,
    FireWall = 5,
    Telekinesis = 39,
    Lightning = 2,
    TownPortal = 6,
    Flash = 3,
    StoneCurse = 7,
    Phasing = 27,
    ManaShield = 12,
    Elemental = 37,
    FireBall = 11,
    FlameWave = 13,
    ChainLightning = 15,
    Guardian = 17,
    Nova = 10,
    Golem = 20,
    Teleport = 23,
    Apocalypse = 24,
    BoneSpirit = 29,
    BloodStar = 35,
    Etherealize = 21,
    RepairItem = 25, // Warrior skill
    DisarmTrap = 36, // Rogue skill
    RechargeStaff = 28 // Sorcerer skill
  };

  //! Constructor
  Spell( const LevelObject* caster, const int level = 1 );

  //! Destructor
  virtual ~Spell()
  { /* ... */ }

  //! Get the spell level
  int getLevel() const;

  //! Get the spell type
  virtual Type getType() const = 0;

  //! Get the icon image
  virtual QImage getIconImage() const = 0;

  //! Get the small icon image
  virtual QImage getSmallIconImage() const = 0;

  //! Check if this is a projectile spell
  virtual bool isProjectileSpell() const = 0;

  //! Cast at a location
  virtual void cast( const QPoint& cast_target ) = 0;

  //! Present the spell
  virtual void present( QPainter* painter ) = 0;

public slots:

  void handleCast( const QPoint& cast_target );

protected:

  //! Get the caster
  const LevelObject* getCaster() const;

private:

  // The caster
  const LevelObject* d_caster;

  // The spell level
  int d_level;
};

} // end QtD1 namespace

#endif // end SPELL_H

//---------------------------------------------------------------------------//
// end Spell.h
//---------------------------------------------------------------------------//
