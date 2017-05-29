//---------------------------------------------------------------------------//
//!
//! \file   BasicActor.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The basic actor base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef BASIC_ACTOR_H
#define BASIC_ACTOR_H

// Std Lib Includes
#include <memory>

// QtD1 Includes
#include "QMLRegistrationHelper.h"
#include "InteractiveLevelObject.h"
#include "Direction.h"
#include "GameSprite.h"

namespace QtD1{

class BasicActor : public InteractiveLevelObject
{
  Q_OBJECT

public:

  //! The basic actor state enum
  enum State{
    Standing = 0,
    Walking
  };

  //! The directional sprites type
  typedef QMap<Direction,GameSprite> DirectionGameSpriteMap;

  //! The state sprites type
  typedef QMap<Actor::State,std::shared_ptr<DirectionGameSpriteMap> >
  StateDirectionGameSpriteMap;

  //! Constructor
  BasicActor( QGraphicsObject* parent = 0 );

  //! Destructor
  virtual ~BasicActor()
  { /* ... */ }

  //! Set the state of the actor
  void setState( const State state );

  //! Get the state of the actor
  State getState() const;

  //! Set the direction of the actor
  void setDirection( const Direction direction );

  //! Get the direction of the actor
  Direction getDirection() const;

  //! Set the state and direction of the actor
  void setStateAndDirection( const State state, const Direction direction );

  //! Get the bounding rect of the actor
  QRectF boundingRect() const override;

  //! Get the shape of the actor
  QPainterPath shape() const override;

  //! Advance the actor state
  void advance( int phase ) override;

protected:

  //! Set the actor sprites
  void setActorSprites(
                 const std::shared_ptr<StateDirectionGameSpriteMap>& sprites );

  //! Paint the actor
  void paintImpl( QPainter* painter,
                  const QStyleOptionGraphicsItem* option,
                  QWidget* widget ) override;

private:

  // Connect actor data signals to actor slots
  void connectActorDataSignalsToActorSlots();

  // Disconnect actor slots from actor data signals
  void disconnectActorSlotsFromActorDataSignals();
};

} // end QtD1 namespace

#endif // end BASIC_ACTOR_H

//---------------------------------------------------------------------------//
// end BasicActor.h
//---------------------------------------------------------------------------//
