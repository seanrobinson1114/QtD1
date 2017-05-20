//---------------------------------------------------------------------------//
//!
//! \file   WarriorInventory.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Warrior inventory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef WARRIOR_INVENTORY_H
#define WARRIOR_INVENTORY_H

// QtD1 Includes
#include "Inventory.h"

namespace QtD1{

//! The warrior inventory
class WarriorInventory : public Inventory
{

public:

  //! Constructor
  WarriorInventory( QWidget* parent = 0 );

  //! Destructor
  ~WarriorInventory()
  { /* ... */ }

  //! Clone the inventory
  WarriorInventory* clone( QWidget* parent = 0 ) const override;
};
  
} // end QtD1 namespace

#endif // end WARRIOR_INVENTORY_H

//---------------------------------------------------------------------------//
// end WarriorInventory.h
//---------------------------------------------------------------------------//
