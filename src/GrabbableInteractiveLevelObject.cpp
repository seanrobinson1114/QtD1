//---------------------------------------------------------------------------//
//!
//! \file   GrabbableInteractiveLevelObject.cpp
//! \author Alex Robinson
//! \brief  The grabbable interactive level object class declaration
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "GrabbableInteractiveLevelObject.h"

namespace QtD1{

// Constructor
GrabbableInteractiveLevelObject::GrabbableInteractiveLevelObject( QGraphicsObject* parent )
  : InteractiveLevelObject( parent ),
    d_owner( NULL )
{ /* ... */ }

// Check if the object is owned
bool GrabbableInteractiveLevelObject::isOwned() const
{
  return d_owner != NULL;
}

// Get a processed description of the object when it is not owned
QPixmap GrabbableInteractiveLevelObject::getUnownedDescription() const
{
  return this->processDescriptionText( this->getUnownedDescriptionText(),
                                       "QtD1White11",
                                       true,
                                       false );
}

// Get a processed description of the object when it is not owned
QPixmap GrabbableInteractiveLevelObject::getOwnedDescription() const
{
  return this->processDescriptionText( this->getOwnedDescriptionText(),
                                       "QtD1White11",
                                       true,
                                       false );
}

// Get a processed description of the object when shown in a trade menu
QPixmap GrabbableInteractiveLevelObject::getTradeMenuDescription() const
{
  return this->processDescriptionText( this->getTradeMenuDescriptionText(),
                                       "QtD1White11",
                                       false,
                                       true );
}

// Get a description of the object
QString GrabbableInteractiveLevelObject::getDescriptionText() const
{
  if( this->isOwned() )
    return this->getOwnedDescriptionText();
  else
    return this->getUnownedDescriptionText();
}

// Get a processed description of the object
QPixmap GrabbableInteractiveLevelObject::getDescription() const
{
  if( this->isOwned() )
    return this->getOwnedDescription();
  else
    return this->getUnownedDescription();
}

// Set the owner
void GrabbableInteractiveLevelObject::setOwner( Character* character )
{
  d_owner = character;
}

// Set as unowned
void GrabbableInteractiveLevelObject::setAsUnowned()
{
  d_owner = NULL;
}

// Identify the object
void GrabbableInteractiveLevelObject::identify()
{ /* ... */ }

// Handler being targeted by another object
void GrabbableInteractiveLevelObject::handlerBeingTargeted( LevelObject* targeter )
{

}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end GrabbableInteractiveLevelObject.cpp
//---------------------------------------------------------------------------//
