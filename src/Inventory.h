//---------------------------------------------------------------------------//
//!
//! \file   Inventory.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The inventory base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef INVENTORY_H
#define INVENTORY_H

// Std Lib Includes
#include <memory>

// Qt Includes
#include <QWidget>
#include <QLabel>

namespace QtD1{

//! The inventory base class
class Inventory : public QWidget
{
  Q_OBJECT

public:

  //! The inventory weapon state enum
  enum WeaponState{
    AxeEquiped,
    BowEquiped,
    StaffEquiped,
    SwordEquiped,
    SwordAndShieldEquiped,
    MaceEquiped,
    MaceAndShieldEquiped,
    ShieldEquiped,
    NothingEquiped
  };

  //! The inventory chest armor state enum
  enum ChestArmorState{
    LowClassArmorEquiped,
    MediumClassArmorEquiped,
    HighClassArmorEquiped
  };

  //! Destructor
  virtual ~Inventory()
  { /* ... */ }

  //! Set the right hand item
  //void setRightHandItem( const std::shared_ptr<Weapon>& weapon );

  //! Get right hand item
  //const std::shared_ptr<Weapon>& getRightHandItem() const;

  //! Set the left hand item
  //void setLeftHandItem( const std::shared_ptr<Shield>& shield );

  //! Get the left hand item
  //const std::shared_ptr<Shield>& getLeftHandItem() const;

  //! Set the right hand ring
  //void setRightHandRing( const std::shared_ptr<Ring>& ring );

  //! Get the right hand ring
  //const std::shared_ptr<Ring>& getRightHandRing() const;

  //! Set the left hand ring
  //void setLeftHandRing( const std::shared_ptr<Ring>& ring );

  //! Get the left hand ring
  //const std::shared_ptr<Ring>& getLeftHandRing() const;

  //! Set the amulet
  //void setAmulet( const std::shared_ptr<Amulet>& amulet );

  //! Get the amulet
  //const std::shared_ptr<Amulet>& getAmulet() const;

  //! Set the chest armor
  //void setChestArmor( const std::shared_ptr<ChestArmor>& armor );

  //! Get the chest armor
  //const std::shared_ptr<ChestArmor>& getChestArmor() const;

  //! Set the helmet
  //void setHelmet( const std::shared_ptr<Helmet>& helmet );

  //! Get the helmet
  //const std::shared_ptr<Helmet>& getHelmet() const;

  //! Calculate strength modifier
  int calculateStrengthModifier() const;

  //! Calculate magic modifier
  int calculateMagicModifier() const;

  //! Calculate dexterity modifier
  int calculateDexterityModifier() const;

  //! Calculate vitality modifier
  int calculateVitalityModifier() const;

  //! Calculate health modifier
  int calculateHealthModifier() const;

  //! Calculate mana modifier
  int calculateManaModifier() const;

  //! Calculate damage
  int calculateDamage() const;

  //! Calculate armor class
  int calculateArmorClass() const;

  //! Calculate magic resistance
  qreal calculateMagicResistance() const;

  //! Calculate fire resistance
  qreal calculateFireResistance() const;

  //! Calculate lightning resistance
  qreal calculateLightningResistance() const;

  //! Clone the inventory
  virtual Inventory* clone( QWidget* parent = 0 ) const = 0;

signals:

  void weaponChanged( const Inventory::WeaponState state );
  void shieldChanged( const Inventory::WeaponState state );
  void ringChanged();
  void amuletChanged();
  void armorChanged( const Inventory::ChestArmorState state );
  void helmetChanged();

protected:

  //! Constructor
  Inventory( QWidget* parent = 0 );

  //! Set the inventory image
  void setInventoryImage( QLabel* inventory_image );

private:

  // The inventory image
  QLabel* d_inventory_image;

  // // The right hand item
  // std::shared_ptr<Weapon> d_weapon;

  // // The left hand item
  // std::shared_ptr<Shield> d_shield;

  // // The right hand ring
  // std::shared_ptr<Ring> d_right_hand_ring;

  // // The left hand ring
  // std::shared_ptr<Ring> d_left_hand_ring;

  // // The amulet
  // std::shared_ptr<Amulet> d_amulet;

  // // The chest armor
  // std::shared_ptr<ChestArmor> d_armor;

  // // The helmet
  // std::shared_ptr<Helmet> d_helmet;
};

} // end QtD1 namespace

#endif // end INVENTORY_H

//---------------------------------------------------------------------------//
// end Inventory.h
//---------------------------------------------------------------------------//
