//---------------------------------------------------------------------------//
//!
//! \file   RogueInventory.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The Rogue inventory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ROGUE_INVENTORY_H
#define ROGUE_INVENTORY_H

// QtD1 Includes
#include "Inventory.h"

namespace QtD1{

//! The rogue inventory
class RogueInventory : public Inventory
{

public:

  //! Constructor
  RogueInventory( QWidget* parent = 0 );

  //! Destructor
  ~RogueInventory()
  { /* ... */ }

  //! Clone the inventory
  RogueInventory* clone( QWidget* parent = 0 ) const override;
};
  
} // end QtD1 namespace

#endif // end ROGUE_INVENTORY_H

//---------------------------------------------------------------------------//
// end RogueInventory.h
//---------------------------------------------------------------------------//
