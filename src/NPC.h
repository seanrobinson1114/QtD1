//---------------------------------------------------------------------------//
//!
//! \file   NPC.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The NPC base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NPC_H
#define NPC_H

// QtD1 Includes
#include "BasicActor.h"

namespace QtD1{

//! The NPC base class
class NPC : public BasicActor
{
  Q_OBJECT

public:

  //! Constructor
  NPC( QGraphicsObject* parent = 0,
       const bool has_walking_state = false );

  //! Destructor
  virtual ~NPC()
  { /* ... */ }

  //! Check if the object can be attacked
  bool canBeAttacked() const final override;

protected slots:

  //! Handle being targeted by another object
  void handleBeingTargeted( LevelObject* object ) override;

protected:

  //! The NPC state enum
  enum State{
    Standing = 0,
    Walking
  };

  //! The NPC state map
  typedef QMap<NPC::State,std::shared_ptr<BasicActor::DirectionGameSpriteMap> >
  StateDirectionGameSpriteMap;

  //! Set the NPC sprites
  void setNPCSprites(
                 const std::shared_ptr<StateDirectionGameSpriteMap>& sprites );

  //! Initialize the state machine
  virtual void initializeStateMachine( QStateMachine& state_machine );
                                                                     
  //! Greet the character
  virtual void greet() = 0;
                                                                  
private slots:

  // Handle standing state entered
  void handleStandingStateEntered();

  // Handle walking state entered
  void handleWalkingStateEntered();

  // Handle walking state exited
  void handleWalkingStateExited();

private:

  // Update the time dependent states
  bool updateTimeDependentStates() override;

  // Record if the NPC has a walking state
  bool d_has_walking_state;

  // The NPC sprites
  std::shared_ptr<StateDirectionGameSpriteMap> d_sprites;

  // The active state
  State d_active_state;
};
  
} // end QtD1 namespace

#endif // end NPC_H

//---------------------------------------------------------------------------//
// end NPC.h
//---------------------------------------------------------------------------//
