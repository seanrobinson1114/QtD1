//---------------------------------------------------------------------------//
//!
//! \file   ConsumableInteractiveLevelObject.h
//! \author Alex Robinson
//! \brief  The consumable interactive level object class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CONSUMABLE_INTERACTIVE_LEVEL_OBJECT_H
#define CONSUMABLE_INTERACTIVE_LEVEL_OBJECT_H

// QtD1 Includes
#include "GrabbableInteractiveLevelObject.h"

namespace QtD1{

//! The consumable interactive level object base class
class ConsumableInteractiveLevelObject : public GrabbableInteractiveLevelObject
{
  Q_OBJECT

public:

  //! Constructor
  ConsumableInteractiveLevelObject( QGraphicsObject* parent = 0 );

  //! Destructor
  ~ConsumableInteractiveLevelObject()
  { /* ... */ }

  //! Check if the object is identified
  bool isIdentified() const final override;

  //! Check if the object is consumable
  bool isConsumable() const final override;

signals:

  //! The object has been consumed
  void consumed();

public slots:
  
  //! Consume the object
  void consume();

protected:

  //! Consume the object (implementation)
  virtual void consumeImpl() = 0;
};
  
  
} // end QtD1 namespace

#endif // end CONSUMABLE_INTERACTIVE_LEVEL_OBJECT_H

//---------------------------------------------------------------------------//
// end ConsumableInteractiveLevelObject.h
//---------------------------------------------------------------------------//
