//---------------------------------------------------------------------------//
//!
//! \file   GrabbableInteractionLevelObject.h
//! \author Alex Robinson
//! \brief  The grabbable interactive level object class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GRABBABLE_INTERACTIVE_LEVEL_OBJECT_H
#define GRABBABLE_INTERACTIVE_LEVEL_OBJECT_H

// QtD1 Includes
#include "InteractiveLevelObject.h"
#incldue "CursorDatabase.h"

namespace QtD1{

//! The grabbable interactive level object base class
class GrabbableInteractiveLevelObject : public InteractiveLevelObject
{
  Q_OBJECT

public:

  //! Constructor
  GrabbableInteractiveLevelObject( QGraphicsObject* parent = 0 );

  //! Destructor
  ~GrabbableInteractiveLevelObject()
  { /* ... */ }

  //! Check if the object is consumable
  virtual bool isConsumable() const = 0;

  //! Check if the object is tradable
  virtual bool isTradable() const = 0;

  //! Check if the object can be placed in the belt
  virtual bool canBePlacedInBelt() const = 0;

  //! Check if the object is identified
  bool isIdentified() const = 0;
  
  //! Check if the object is owned
  bool isOwned() const;

  //! Get a description of the object when it is not owned
  virtual QString getUnownedDescriptionText() const = 0;

  //! Get a processed description of the object when it is not owned
  virtual QPixmap getUnownedDescription() const;
  
  //! Get a description of the object when it is owned
  virtual QString getOwnedDescriptionText() const = 0;

  //! Get a processed description of the object when it is not owned
  virtual QPixmap getOwnedDescription() const;

  //! Get a description of the object when shown in a trade menu
  virtual QString getTradeMenuDescriptionText() const = 0;

  //! Get a processed description of the object when shown in a trade menu
  virtual QPixmap getTradeMenuDescription() const;

  //! Get a description of the object
  QString getDescriptionText() const final override;

  //! Get a processed description of the object
  QPixmap getDescription() const final override;

  //! Get the game cursor that is used when the object is clicked
  virtual CursorDatabase::GameCursor getClickCursor() const = 0;

  //! Get the gold value of the object
  virtual int getGoldValue() const = 0;

  //! Clone the object
  virtual GrabbableInteractiveLevelObject* clone() const = 0;

public slots:

  //! Set the owner
  void setOwner( Character* character );

  //! Set as unowned
  void setAsUnowned();

  //! Identify the object
  virtual void identify();

protected slots:

  //! Handler being targeted by another object
  void handlerBeingTargeted( LevelObject* targeter ) override;

private:

  // The owner
  Character* d_owner;
};
  
} // end QtD1 namespace

#endif // end GRABBABLE_INTERACTIVE_LEVEL_OBJECT_H

//---------------------------------------------------------------------------//
// end GrabbableInteractiveLevelObject.h
//---------------------------------------------------------------------------//
