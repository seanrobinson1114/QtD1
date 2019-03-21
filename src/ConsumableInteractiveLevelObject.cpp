//---------------------------------------------------------------------------//
//!
//! \file   ConsumableInteractiveLevelObject.cpp
//! \author Alex Robinson
//! \brief  The consumable interactive level object class definition
//!
//---------------------------------------------------------------------------//

//! QtD1 Includes
#include "ConsumableInteractiveLevelObject.h"

namespace QtD1{

// Constructor
ConsumableInteractiveLevelObject::ConsumableInteractiveLevelObject( QGraphicsObject* parent )
  : GrabbableInteractiveLevelObject( parent )
{ /* ... */ }

// Copy constructor
ConsumableInteractiveLevelObject::ConsumableInteractiveLevelObject( const ConsumableInteractiveLevelObject& other )
  : GrabbableInteractiveLevelObject( other )
{ /* ... */ }

// Check if the object is identified
bool ConsumableInteractiveLevelObject::isIdentified() const
{
  return true;
}

// Check if the object is consumable
bool ConsumableInteractiveLevelObject::isConsumable() const
{
  return true;
}

// Consume the object
void ConsumableInteractiveLevelObject::consume()
{
  this->consumeImpl();

  emit consumed();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end ConsumableInteractiveLevelObject.cpp
//---------------------------------------------------------------------------//
