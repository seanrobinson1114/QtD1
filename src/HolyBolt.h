//---------------------------------------------------------------------------//
//!
//! \file   HolyBolt.h
//! \author Alex Robinson, Sean Robinson
//! \brief  Holy bolt spell class declaration
//!
//---------------------------------------------------------------------------//

#ifndef HOLY_BOLT_H
#define HOLY_BOLT_H

// Qt Includes
#include <QImage>
#include <QVector>

// QtD1 Includes
#include "ProjectileSpell.h"
#include "Sound.h"

namespace QtD1{

//! The holy bolt spell class
class HolyBolt : public ProjectileSpell
{
  Q_OBJECT

public:

  //! Constructor
  HolyBolt( const Object* caster, const int level = 1 );

  //! Destructor
  ~HolyBolt()
  { /* ... */ }

  //! Get the spell type
  Type getType() const override;

  //! Get the magic damage
  int getMagicDamage() const override;
  
  //! Get the fire damage
  int getFireDamage() const override;

  //! Get the lightning damage
  int getLightningDamage() const override;

  //! Get the base damage
  int getBaseDamage() const override;

  //! Cast at a location
  void cast( const QPoint& cast_target ) override;
  
  //! Cast at an actor
  void castAt( const QPoint& origin, Actor& cast_target ) override;

  //! Cast at an object
  void castAt( const QPoint& origin, Object& cast_target ) override;
                                                    
  //! Present the spell
  void present( QPainter* painter ) override;

private:

  struct Data
  {
    static Data* getInstance();

    // The icon image
    QImage icon_image;

    // The small icon image
    QImage small_icon_image;
    
    // The south directed holy bolt sprite
    QVector<QImage> south_directed_holy_bolt_sprite;

    // The south-southwest directed holy bolt sprite
    QVector<QImage> south_southwest_directed_holy_bolt_sprite;
    
    // The southwest directed holy bolt sprite
    QVector<QImage> southwest_directed_holy_bolt_sprite;

    // The west-southwest directed holy bolt sprite
    QVector<QImage> west_southwest_directed_holy_bolt_sprite;

    // The west directed holy bolt sprite
    QVector<QImage> west_directed_holy_bolt_sprite;

    // The west-northwest directed holy bolt sprite
    QVector<QImage> west_northwest_directed_holy_bolt_sprite;
    
    // The northwest directed holy bolt sprite
    QVector<QImage> northwest_directed_holy_bolt_sprite;

    // The north-northwest directed holy bolt sprite
    QVector<QImage> north_northwest_directed_holy_bolt_sprite;
    
    // The north directed holy bolt sprite
    QVector<QImage> north_directed_holy_bolt_sprite;

    // The north-northeast directed holy bolt sprite
    QVector<QImage> north_northwest_directed_holy_bolt_sprite;
    
    // The northeast directed holy bolt sprite
    QVector<QImage> northeast_directed_holy_bolt_sprite;

    // The east-northeast directed holy bolt sprite
    QVector<QImage> east_northeast_directed_holy_bolt_sprite;
    
    // The east directed holy bolt sprite
    QVector<QImage> east_directed_holy_bolt_sprite;

    // The east-southeast directed holy bolt sprite
    QVector<QImage> east_southeast_directed_holy_bolt_sprite;
    
    // The southeast directed holy bolt sprite
    QVector<QImage> southeast_directed_holy_bolt_sprite;

    // The south-southeast directed holy bolt sprite
    QVector<QImage> south_southeast_directed_holy_bolt_sprite;
    
    // The explosion holy bolt sprite
    QVector<QImage> explosion_holy_bolt_sprite;
    
    // The holy bolt sound
    Sound sound;

  private:

    // Constructor
    Data();

    // The singleton instance
    std::unique_ptr<Data> s_instance;
  };

  // The spell data
  const Data* d_data;
};
  
} // end QtD1 namespace

#endif // end HOLY_BOLT_H

//---------------------------------------------------------------------------//
// end HolyBolt.h
//---------------------------------------------------------------------------//
