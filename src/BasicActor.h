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
#include <utility>

// Qt Includes
#include <QStateMachine>
#include <QState>

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

  //! The directional sprites type
  typedef QMap<Direction,GameSprite> DirectionGameSpriteMap;

  //! Constructor
  BasicActor( QGraphicsObject* parent = 0 );

  //! Destructor
  virtual ~BasicActor()
  { /* ... */ }

  //! Get the direction of the basic actor
  Direction getDirection() const;

  //! Get the bounding rect of the basic actor
  QRectF boundingRect() const override;

  //! Get the shape of the basic actor
  QPainterPath shape() const override;

  //! Advance the basic actor state (if time dependent)
  void advance( int phase ) override;

  //! Start the actor state machine
  void startStateMachine();

signals:

  //! The direction has changed
  void directionChanged( const Direction new_direction );

  //! The time state has been advanced
  void timeStateAdvanced();

public slots:

  //! Set the direction of the basic actor
  void setDirection( const Direction direction );

protected:

  //! Initialize the state machine
  virtual void initializeStateMachine( QStateMachine& state_machine ) = 0;

  //! Paint the actor
  void paintImpl( QPainter* painter,
                  const QStyleOptionGraphicsItem* option,
                  QWidget* widget ) override;

  //! Set the active sprites
  void setActiveSprites( DirectionGameSpriteMap* active_sprites );

private:

  // The active sprites
  DirectionGameSpriteMap* d_active_sprites;

  // The active direction sprite
  std::pair<Direction,GameSprite*> d_active_direction_sprite;

  // The basic actor state machine
  std::unique_ptr<QStateMachine> d_state_machine;
};

} // end QtD1 namespace

#endif // end BASIC_ACTOR_H

//---------------------------------------------------------------------------//
// end BasicActor.h
//---------------------------------------------------------------------------//
