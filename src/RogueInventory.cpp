//---------------------------------------------------------------------------//
//!
//! \file   RogueInventory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The Rogue inventory class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "RogueInventory.h"

namespace QtD1{

// Constructor
RogueInventory::RogueInventory( QWidget* parent )
  : Inventory( parent )
{
  // Load the background image
  QImage background_image( "/data/inv/inv_rog.cel+levels/towndata/town.pal" );

  QLabel* background = new QLabel( this );
  background->setPixmap( QPixmap::fromImage( background_image ) );

  this->setFixedSize( background_image.size() );
  this->setInventoryImage( background );
}

// Clone the inventory
/*! \details The returned pointer is heap allocated.
 */
RogueInventory* RogueInventory::clone( QWidget* parent ) const
{
  return new RogueInventory( parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end RogueInventory.h
//---------------------------------------------------------------------------//
