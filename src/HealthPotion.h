//---------------------------------------------------------------------------//
//!
//! \file   HealthPotion.h
//! \author Alex Robinson
//! \brief  The health potion class declaration
//!
//---------------------------------------------------------------------------//

#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

// QtD1 Includes
#include "ConsumableInteractiveLevelObject.h"

namespace QtD1{

//! The health potion
class HealthPotion : public ConsumableInteractiveLevelObject
{
  Q_OBJECT

public:

  //! Constructor
  HealthPotion( QGraphicsObject* parent = 0 );

  //! Destructor
  ~HealthPotion()
  { /* ... */ }

  //! Check if the object is tradable
  bool isTradable() const final override;

  //! Check if the object can be placed in the belt
  bool canBePlacedInBelt() const final override;

  //! Get a description of the object when it is not owned
  QString getUnownedDescriptionText() const final override;

  //! Get a processed description of the object when it is not owned
  QPixmap getUnownedDescription() const final override;

  //! Get a description of the object when it is owned
  QString getOwnedDescriptionText() const final override;

  //! Get a processed description of the object when it is not owned
  QPixmap getOwnedDescription() const final override;

  //! Get a description of the object when shown in a trade menu
  QString getTradeMenuDescriptionText() const final override;

  //! Get a processed description of the object when shown in a trade menu
  QPixmap getTradeMenuDescription() const final override;

  //! Get the game cursor that is used when the object is clicked
  CursorDatabase::GameCursor getClickCursor() const final override;

  //! Get the gold value of the object
  int getGoldValue() const final override;

  //! Clone the object
  HealthPotion* clone() const final override;

protected:

  //! Consume the object (implementation)
  void consumeImpl() final override;
};
  
} // end QtD1 namespace

#endif // end HEALTH_POTION_H

//---------------------------------------------------------------------------//
// end HealthPotion.h
//---------------------------------------------------------------------------//
