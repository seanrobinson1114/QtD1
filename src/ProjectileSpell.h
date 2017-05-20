//---------------------------------------------------------------------------//
//!
//! \file   ProjectileSpell.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The projectile spell base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PROJECTILE_SPELL_H
#define PROJECTILE_SPELL_H

// QtD1 Includes
#include "Spell.h"

namespace QtD1 {

//! The projectile spell base class
class ProjectileSpell : public Spell, public Projectile
{

public:

  //! Constructor
  ProjectileSpell( const Object* caster, const int level = 1 );

  //! Destructor
  virtual ~ProjectileSpell()
  { /* ... */ }

  //! Check if this is a projectile spell
  bool isProjectileSpell() const override;

  //! Treat this spell as a projectile
  Projectile* toProjectile() override;

  //! Treat this spell as a projectile
  const Projectile* toProjectile() const override;
};
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end ProjectileSpell.h
//---------------------------------------------------------------------------//
