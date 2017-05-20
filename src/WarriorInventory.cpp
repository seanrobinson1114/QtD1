//---------------------------------------------------------------------------//
//!
//! \file   WarriorInventory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The Warrior inventory class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// QtD1 Includes
#include "WarriorInventory.h"

namespace QtD1{

// Constructor
WarriorInventory::WarriorInventory( QWidget* parent )
  : Inventory( parent )
{
  // Load the background image
  QImage background_image( "/data/inv/inv.cel+levels/towndata/town.pal" );

  QLabel* background = new QLabel( this );
  background->setPixmap( QPixmap::fromImage( background_image ) );

  this->setFixedSize( background_image.size() );
  this->setInventoryImage( background );
}

// Clone the inventory
/*! \details The returned pointer is heap allocated.
 */
WarriorInventory* WarriorInventory::clone( QWidget* parent ) const
{
  return new WarriorInventory( parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end WarriorInventory.h
//---------------------------------------------------------------------------//
