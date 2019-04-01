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

// QtD1 Includes
#include "QMLRegistrationHelper.h"
#include "InteractiveLevelObject.h"
#include "Direction.h"
#include "GameSprite.h"
#include "Grid.h"

namespace QtD1{

class BasicActor : public InteractiveLevelObject
{
  Q_OBJECT

public:

  //! Constructor
  BasicActor( QGraphicsObject* parent = 0 );

  //! Copy Constructor
  BasicActor( const BasicActor& other_actor );

  //! Assignment Operator
  BasicActor& operator=( const BasicActor& other_actor );

  //! Destructor
  virtual ~BasicActor()
  { /* ... */ }

  //! Get the description of the basic actor
  virtual QString getDescriptionText() const override;

  // ! Check if basic actor is collideable
  virtual bool isCollideable() const override;

  //! Get the direction of the basic actor
  Direction getDirection() const;

  //! Get the movement speed (pixels per game tic)
  virtual qreal getMovementSpeed() const = 0;

  //! Get the actor x velocity (pixels per game tic)
  qreal getXVelocity() const;

  //! Get the actor y velocity (pixels per game tic)
  qreal getYVelocity() const;

  //! Get the bounding rect
  QRectF boundingRect() const override;

  //! Get the bounding rect of the collideable area
  QPainterPath boundingCollideablePolygon() const;

  //! Get the shape of the basic actor
  QPainterPath shape() const override;

  //! Advance the basic actor state (if time dependent)
  void advance( int phase ) override;

  //! Start the actor state machine
  void startStateMachine();

  //! Set the grid
  void setGrid( const std::shared_ptr<Grid>& );

  //! Check if is a pillar
  bool isPillar() const override;

signals:

  //! All of the active sprite frames have been shown
  void allActiveFramesShown();

  //! Actor target set
  void targetSet( LevelObject* targeter, LevelObject* target );
  
  //! Actor target reached
  void targetReached( LevelObject* targeter, LevelObject* target );

public slots:

  //! Set the direction of the basic actor
  void setDirection( const Direction direction );

  //! Set the target
  void setTarget( LevelObject* target, QPointF target_coord );

protected slots:

  //! Set the actor x velocity
  void setXVelocity( const qreal x_velocity );

  //! Set the actor y velocity
  void setYVelocity( const qreal y_velocity );

  //! Set the actor velocity
  void setVelocity( const qreal x_velocity, const qreal y_velocity );

protected:

  //! The directional sprites type
  typedef QMap<Direction,GameSprite> DirectionGameSpriteMap;

  //! Initialize the state machine
  virtual void initializeStateMachine( QStateMachine& state_machine ) = 0;

  //! Paint the actor
  void paintImpl( QPainter* painter,
                  const QStyleOptionGraphicsItem* option,
                  QWidget* widget ) override;

  //! Set the active sprites
  void setActiveSprites(
               const std::shared_ptr<DirectionGameSpriteMap>& active_sprites );

  //! Restart active sprite
  void restartActiveSprite();

  //! Update time dependent states
  virtual bool updateTimeDependentStates() = 0;

  //! Update time dependent states implementation (return if a screen update)
  bool updateTimeDependentStatesImpl( const bool in_walking_state );

  //! Get the grid
  const Grid& getGrid() const;

  //! Get the grid
  Grid& getGrid();

  //! Set the path
  void setPath( const Grid::Path& path );

  //! Get the path
  const Grid::Path& getPath() const;

  //! Get the path
  Grid::Path& getPath();

private:

  // The active sprites
  std::shared_ptr<DirectionGameSpriteMap> d_active_sprites;

  // The active direction sprite
  std::pair<Direction,GameSprite*> d_active_direction_sprite;

  // The basic actor state machine
  std::unique_ptr<QStateMachine> d_state_machine;

  // The grid
  std::shared_ptr<Grid> d_grid;

  // The path through the grid
  Grid::Path d_path;

  // The velocity of the actor
  qreal d_x_velocity;
  qreal d_y_velocity;

  // The target of the actor
  LevelObject* d_target;
};

} // end QtD1 namespace

#endif // end BASIC_ACTOR_H

//---------------------------------------------------------------------------//
// end BasicActor.h
//---------------------------------------------------------------------------//
