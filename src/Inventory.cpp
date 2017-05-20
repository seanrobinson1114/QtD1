//---------------------------------------------------------------------------//
//!
//! \file   Inventory.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The inventory base class definition
//!
//---------------------------------------------------------------------------//

// QtD1 includes
#include "Inventory.h"

namespace QtD1{

// Constructor
Inventory::Inventory( QWidget* parent )
  : QWidget( parent ),
    d_inventory_image( NULL )
{ /* ... */ }

// Set the inventory image
void Inventory::setInventoryImage( QLabel* inventory_image )
{
  d_inventory_image = inventory_image;
}

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

// Calculate strength modifier
int Inventory::calculateStrengthModifier() const
{
  return 0;
}

// Calculate magic modifier
int Inventory::calculateMagicModifier() const
{
  return 0;
}

// Calculate dexterity modifier
int Inventory::calculateDexterityModifier() const
{
  return 0;
}

//! Calculate vitality modifier
int Inventory::calculateVitalityModifier() const
{
  return 0;
}

// Calculate health modifier
int Inventory::calculateHealthModifier() const
{
  return 0;
}

// Calculate mana modifier
int Inventory::calculateManaModifier() const
{
  return 0;
}

// Calculate damage
int Inventory::calculateDamage() const
{
  return 0;
}
// Calculate armor class
int Inventory::calculateArmorClass() const
{
  return 0;
}

// Calculate magic resistance
qreal Inventory::calculateMagicResistance() const
{
  return 0;
}

// Calculate fire resistance
qreal Inventory::calculateFireResistance() const
{
  return 0;
}

// Calculate lightning resistance
qreal Inventory::calculateLightningResistance() const
{
  return 0;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end Inventory.cpp
//---------------------------------------------------------------------------//
