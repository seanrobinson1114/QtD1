//---------------------------------------------------------------------------//
//!
//! \file   GrabbableInteractionLevelObject.h
//! \author Alex Robinson
//! \brief  The grabbable interactive level object class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GRABBABLE_INTERACTIVE_LEVEL_OBJECT_H
#define GRABBABLE_INTERACTIVE_LEVEL_OBJECT_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "InteractiveLevelObject.h"
#include "Cursor.h"
#include "Character.h"

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

  //! Check if the object is grabbable
  bool isGrabbable() const final override;

  //! Check if the object is consumable
  virtual bool isConsumable() const = 0;

  //! Check if the object is tradable
  virtual bool isTradable() const = 0;

  //! Check if the object can be attacked
  bool canBeAttacked() const final override;

  //! Check if the object can be placed in the belt
  virtual bool canBePlacedInBelt() const = 0;

  //! Check if the object is identified
  virtual bool isIdentified() const = 0;
  
  //! Check if the object is owned
  virtual bool isOwned() const;

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
  virtual Cursor::GameCursor getClickCursor() const = 0;

  //! Get the gold value of the object
  virtual int getGoldValue() const = 0;

  //! Get the inventory image
  virtual QPixmap getInventoryPixmap() const = 0;

  //! Get the owner
  Character* getOwner() const;

  //! Clone the object
  virtual GrabbableInteractiveLevelObject* clone() const = 0;

  //! Get the bounding rect of the basic actor
  QRectF boundingRect() const override;

  //! Get the shape of the basic actor
  QPainterPath shape() const override;

  //! Advance the basic actor state (if time dependent)
  void advance( int phase ) override;

  //! Start the actor state machine
  void startStateMachine();

signals:

  //! All of the active sprite frames have been shown
  void allActiveFramesShown();

  //! No current owner
  void dropped();

public slots:

  //! Set the owner
  void setOwner( Character* character );

  //! Set as unowned
  void setAsUnowned();

  //! Drop the item
  void drop();

  //! Identify the object
  virtual void identify();

protected slots:

  //! Handler being targeted by another object
  void handleBeingTargeted( LevelObject* targeter ) override;

protected:

  //! The grabbable item states
  enum State{
    Flipping,
    OnFloor
  };

  //! The state game sprite map
  typedef QMap<State,GameSprite> StateGameSpriteMap;

  //! Copy constructor
  GrabbableInteractiveLevelObject( const GrabbableInteractiveLevelObject& other );

  //! Set the sprites
  void setSprites( const std::shared_ptr<StateGameSpriteMap>& sprites );

  //! Check if the state machine is running
  bool isStateMachineRunning() const;

  //! The paint implementation
  void paintImpl( QPainter* painter,
                  const QStyleOptionGraphicsItem* option,
                  QWidget* widget ) final override;

  //! Play the flipping sound
  virtual void playFlippingSound() = 0;

private slots:

  // Handle standing state entered
  void handleOnFloorStateEntered();

  // Handle walking state entered
  void handleFlippingStateEntered();

  // Handle walking state exited
  void handleFlippingStateExited();
  
private:

  // The owner
  Character* d_owner;

  // The sprites
  std::shared_ptr<StateGameSpriteMap> d_sprites;

  // The active sprite
  GameSprite* d_active_sprite;

  // The grabbable object state machine
  std::unique_ptr<QStateMachine> d_state_machine;
};
  
} // end QtD1 namespace

#endif // end GRABBABLE_INTERACTIVE_LEVEL_OBJECT_H

//---------------------------------------------------------------------------//
// end GrabbableInteractiveLevelObject.h
//---------------------------------------------------------------------------//
