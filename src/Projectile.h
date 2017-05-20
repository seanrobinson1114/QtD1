//---------------------------------------------------------------------------//
//!
//! \file   Projectile.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The projectile base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PROJECTILE_H
#define PROJECTILE_H

// Qt Includes
#include <QPoint>

// QtD1 Includes
#include "Object.h"
#include "Actor.h"

namespace QtD1 {

//! The projectile base class
class Projectile : public Object
{
  Q_OBJECT

public:

  //! Constructor
  Projectile( const Object* caster );

  //! Destructor
  virtual ~Projectile()
  { /* ... */ }

  //! Get the magic damage
  virtual int getMagicDamage() const = 0;
  
  //! Get the fire damage
  virtual int getFireDamage() const = 0;

  //! Get the lightning damage
  virtual int getLightningDamage() const = 0;

  //! Get the base damage
  virtual int getBaseDamage() const = 0;

  //! Get the projectile location
  const QPointF& getLocation() const;

  //! Get the projectile direction
  const QPointF& getDirection() const;

  //! Cast at a location
  virtual void cast( const QPoint& cast_target ) = 0;

  //! Cast at an actor
  virtual void castAt( Actor& cast_target ) = 0;

  //! Cast at an object
  virtual void castAt( Object& cast_target ) = 0;

public slots:

  void handleCast( const QPoint& cast_target );
  void handleCastAt( const Actor& cast_target );
  void handleCastAt( const Object& cast_target );

protected:

  //! Step the projectile along its direction
  void step( const qreal step_size );

  //! Change the projectile direction
  void changeDirection( const QPointF& new_direction );

  //! Get the caster
  const Object* getCaster() const;

  // The projectile caster
  const Object* d_caster;

  // The projectile position
  QPointF d_position;

  // The projection direction
  QPointF d_direction;
};
  
} // end QtD1 namespace

#endif // end PROJECTILE_H

//---------------------------------------------------------------------------//
// end Projectile.h
//---------------------------------------------------------------------------//
