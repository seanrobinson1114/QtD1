//---------------------------------------------------------------------------//
//!
//! \file   SorcererInventory.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Sorcerer inventory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SORCERER_INVENTORY_H
#define SORCERER_INVENTORY_H

// QtD1 Includes
#include "Inventory.h"

namespace QtD1{

//! The sorcerer inventory
class SorcererInventory : public Inventory
{

public:

  //! Constructor
  SorcererInventory( QWidget* parent = 0 );

  //! Destructor
  ~SorcererInventory()
  { /* ... */ }

  //! Clone the inventory
  SorcererInventory* clone( QWidget* parent = 0 ) const override;
};
  
} // end QtD1 namespace

#endif // end SORCERER_INVENTORY_H

//---------------------------------------------------------------------------//
// end SorcererInventory.h
//---------------------------------------------------------------------------//
