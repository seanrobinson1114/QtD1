//---------------------------------------------------------------------------//
//!
//! \file   SorcererInventory.cpp
//! \author Alex Robinson, Sean Robinson
//! \brief  The Sorcerer inventory class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "SorcererInventory.h"

namespace QtD1{

// Constructor
SorcererInventory::SorcererInventory( QWidget* parent )
  : Inventory( parent )
{
  // Load the background image
  QImage background_image( "/data/inv/inv_sor.cel+levels/towndata/town.pal" );

  QLabel* background = new QLabel( this );
  background->setPixmap( QPixmap::fromImage( background_image ) );

  this->setFixedSize( background_image.size() );
  this->setInventoryImage( background );
}

// Clone the inventory
/*! \details The returned pointer is heap allocated.
 */
SorcererInventory* SorcererInventory::clone( QWidget* parent ) const
{
  return new SorcererInventory( parent );
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end SorcererInventory.h
//---------------------------------------------------------------------------//
