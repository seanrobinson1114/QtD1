//---------------------------------------------------------------------------//
//!
//! \file   BasicActor.cpp
//! \author Alex Robinson
//! \brief  The basic actor base class definition
//!
//---------------------------------------------------------------------------//

// QtD1 Includes
#include "BasicActor.h"

namespace QtD1{

// Constructor
BasicActor::BasicActor( QGraphicsObject* parent )
  : InteractiveLevelObject( parent ),
    d_active_sprites(),
    d_active_direction_sprite( std::make_pair( South, (GameSprite*)0 ) ),
    d_state_machine(),
    d_grid(),
    d_path(),
    d_x_velocity( 0.0 ),
    d_y_velocity( 0.0 ),
    d_target( NULL )
{ /* ... */ }

// Copy Constructor
BasicActor::BasicActor( const BasicActor& other_actor )
  : InteractiveLevelObject( other_actor.parentObject() ),
    d_active_sprites(),
    d_active_direction_sprite( std::make_pair( South, (GameSprite*)0 ) ),
    d_state_machine(),
    d_grid( other_actor.d_grid ),
    d_path( other_actor.d_path ),
    d_x_velocity( other_actor.d_x_velocity ),
    d_y_velocity( other_actor.d_y_velocity ),
    d_target( other_actor.d_target )
{ /* ... */ }

// Assignment Operator
BasicActor& BasicActor::operator=( const BasicActor& other_actor )
{
  if( this != &other_actor )
  {
    this->setParentItem( other_actor.parentObject() );
    
    d_grid = other_actor.d_grid;
    d_path = other_actor.d_path;
    d_x_velocity = other_actor.d_x_velocity;
    d_y_velocity = other_actor.d_y_velocity;
    d_target = other_actor.d_target;    
  }
  
  return *this;
}

// Get the description of the basic actor
QString BasicActor::getDescription() const
{
  return QString( "No Description Beyond BasicActor Found!" );
}

// Set the direction of the basic actor
void BasicActor::setDirection( const Direction direction )
{
  if( direction != d_active_direction_sprite.first )
  {
    d_active_direction_sprite.first = direction;
    d_active_direction_sprite.second = &(*d_active_sprites)[direction];
  }
}

// Set the target
void BasicActor::setTarget( LevelObject* target, QPointF target_coord )
{
  if( target )
  {
    d_target = target;

    // Get approximate position of Actors feet
    QPointF lower_center_point( this->boundingRect().left() + this->boundingRect().width()/2, this->boundingRect().height() - 20 );

    this->setPath( this->getGrid().constructPath( this, target, target_coord, this->mapToScene( lower_center_point ) ) );
    
    emit targetSet( this, target );
  }
}

// Get the direction of the basic actor
Direction BasicActor::getDirection() const
{
  return d_active_direction_sprite.first;
}

// Get the actor x velocity (pixels per game tic)
qreal BasicActor::getXVelocity() const
{
  return d_x_velocity;
}

// Set the actor x velocity
void BasicActor::setXVelocity( const qreal x_velocity )
{
  d_x_velocity = x_velocity;
}

// Get the actor y velocity (pixels per game tic)
qreal BasicActor::getYVelocity() const
{
  return d_y_velocity;
}

// Set the actor y velocity
void BasicActor::setYVelocity( const qreal y_velocity )
{
  d_y_velocity = y_velocity;
}

// Set the actor velocity
void BasicActor::setVelocity( const qreal x_velocity, const qreal y_velocity )
{
  d_x_velocity = x_velocity;
  d_y_velocity = y_velocity;
}

// Get the bounding rect of the basic actor
QRectF BasicActor::boundingRect() const
{
  if( d_active_direction_sprite.second )
    return d_active_direction_sprite.second->boundingRect();
  else
    return QRectF();
}

// Get the shape of the basic actor
QPainterPath BasicActor::shape() const
{
  if( d_active_direction_sprite.second )
    return d_active_direction_sprite.second->shape();
  else
    return QPainterPath();
}

// Advance the basic actor state (if time dependent)
void BasicActor::advance( int phase )
{
  // Phase 0: about to advance
  // Phase 1: advancing
  if( phase == 1 )
  {
    if( d_active_direction_sprite.second )
    {
      bool screen_update_required =
        d_active_direction_sprite.second->incrementElapsedGameTics();

      if( screen_update_required )
      {
        if( d_active_direction_sprite.second->getFrame() == 0 )
          emit allActiveFramesShown();

        // Only update time dependent states when the sprite frame changes
        this->updateTimeDependentStates();

        // Only request a screen update if it is necessary
        this->update( d_active_direction_sprite.second->boundingRect() );
      }
    }
    else
      std::cout << "An empty sprite sheet was found!" << std::endl;
  }
}

// Paint the actor
void BasicActor::paintImpl( QPainter* painter,
                            const QStyleOptionGraphicsItem* option,
                            QWidget* widget )
{
  if( d_active_direction_sprite.second )
    d_active_direction_sprite.second->paint( painter, option, widget );
  else
    std::cout << "empty sprite sheet detected!" << std::endl;
}

// Start the actor state machine
void BasicActor::startStateMachine()
{
  bool needs_start = false;

  if( !d_state_machine )
  {
    d_state_machine.reset( new QStateMachine( this ) );

    needs_start = true;
  }
  else if( !d_state_machine->isRunning() )
  {
    d_state_machine.reset( new QStateMachine( this ) );

    needs_start = true;
  }

  if( needs_start )
  {
    this->initializeStateMachine( *d_state_machine );
    d_state_machine->start();
  }
}

// Set the grid
void BasicActor::setGrid( const std::shared_ptr<Grid>& grid )
{
  d_grid = grid;
}

// Check if is a pillar
bool BasicActor::isPillar() const
{
  return false;
}

// Set the active spritess
void BasicActor::setActiveSprites(
                const std::shared_ptr<DirectionGameSpriteMap>& active_sprites )
{
  if( active_sprites )
  {
    d_active_sprites = active_sprites;

    d_active_direction_sprite.second =
      &(*d_active_sprites)[d_active_direction_sprite.first];
  }
}

// Restart active sprite
void BasicActor::restartActiveSprite()
{
  if( d_active_direction_sprite.second )
    d_active_direction_sprite.second->setFrame( 0 );
}

// Update time dependent states implementation (return if a screen update)
/*! \details If the actor direction or position changes this method will
 * return true indicating that the screen update is required.
 */
bool BasicActor::updateTimeDependentStatesImpl( const bool in_walking_state )
{
  bool update_required = false;
  
  if( d_target )
  {
    if( in_walking_state )
    {
      bool destination_reached = this->getPath().empty();

      if( destination_reached )
      {
        emit targetReached( this, d_target );

        this->notifyTarget( d_target );
      }
      else
      {
        Direction direction = this->getPath().front().first;
        std::cout << "DIRECTION: " << direction << std::endl;

        double& distance = this->getPath().front().second;
        std::cout << "DISTANCE: " << distance << std::endl;
      
        update_required = true;
        
        // Calculate the velocity of the actor
        if( direction != this->getDirection() )
        {
          // Get the movement direction enum
          this->setDirection( direction );

          // Calculate the velocity
          double speed = this->getMovementSpeed();

          if( distance < speed )
            speed = distance;

          QPointF direction_vector = QtD1::getDirectionVector( direction );
          
          d_x_velocity = direction_vector.x()*speed;
          d_y_velocity = direction_vector.y()*speed;
        }

        this->moveBy( d_x_velocity, d_y_velocity );

        // Update the path
        distance -= std::sqrt( d_x_velocity*d_x_velocity +
                               d_y_velocity*d_y_velocity );

        if( distance <= 0.0 )
          this->getPath().pop_front();
      }
    }
  }
  
  return update_required;
}

// Get the grid
const Grid& BasicActor::getGrid() const
{
  return *d_grid;
}

// Get the grid
Grid& BasicActor::getGrid()
{
  return *d_grid;
}

// Set the path
void BasicActor::setPath( const Grid::Path& path )
{
  d_path = path;
}

// Get the path
const Grid::Path& BasicActor::getPath() const
{
  return d_path;
}

// Get the path
Grid::Path& BasicActor::getPath()
{
  return d_path;
}

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end BasicActor.cpp
//---------------------------------------------------------------------------//
