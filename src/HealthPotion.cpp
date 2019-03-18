//---------------------------------------------------------------------------//
//!
//! \file   HealthPotion.cpp
//! \author Alex Robinson
//! \brief  The health potion class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "HealthPotion.h"

namespace QtD1{

// Constructor
HealthPotion::HealthPotion( QGraphicsObject* parent )
  : ConsumableInteractiveLevelObject( parent )
{ /* ... */ }

// Check if the object is tradable
bool HealthPotion::isTradable() const
{
  return true;
}

// Check if the object can be placed in the belt
bool HealthPotion::canBePlacedInBelt() const
{
  return true;
}

// Get a description of the object when it is not owned
QString HealthPotion::getUnownedDescriptionText() const
{
  return "Potion of Healing"
}

// Get a processed description of the object when it is not owned
QPixmap HealthPotion::getUnownedDescription() const
{

}

// Get a description of the object when it is owned
QString HealthPotion::getOwnedDescriptionText() const
{
  return "Potion of Healing\nRecover Health\nRight Click To Use";
}

// Get a processed description of the object when it is not owned
QPixmap HealthPotion::getOwnedDescription() const
{

}

// Get a description of the object when shown in a trade menu
QString HealthPotion::getTradeMenuDescriptionText() const
{
  return "Potion of Healing\nNo Required Attributes";
}

// Get a processed description of the object when shown in a trade menu
QPixmap HealthPotion::getTradeMenuDescription() const
{

}

// Get the game cursor that is used when the object is clicked
CursorDatabase::GameCursor HealthPotion::getClickCursor() const
{
  return CursorDatabase::GameCursor::SmallHealthPostionGameCursor;
}

// Get the gold value of the object
int HealthPotion::getGoldValue() const
{
  return 50;
}

// Clone the object
HealthPotion* HealthPotion::clone() const
{
  return new HealthPotion( this->getParent() );

  // Set the parent
}

// Consume the object (implementation)
void HealthPotion::consumeImpl()
{

}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end HealthPotion.cpp
//---------------------------------------------------------------------------//
