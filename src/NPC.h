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
#include "Quest.h"

namespace QtD1{

class NPCInteractionMenu;

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

  //! Load the interaction menu
  void loadInteractionMenu( QWidget* parent );

signals:

  //! The interaction menu has been activated
  void interactionMenuActivated();

  //! The interaction menu has been deactivated
  void interactionMenuDeactivated();

public slots:

  //! Activate a quest
  void activateQuest( const Quest::Type quest );

  //! Deactivate a quest
  void deactivateQuest( const Quest::Type quest );

  //! Play quest dialogue
  virtual void discussQuest( const Quest::Type quest ) = 0;

  //! Play gossip dialogue
  virtual void gossip() = 0;

  //! Stop playing dialogue
  void stopTalking();

protected slots:

  //! Handle being targeted by another object
  void handleBeingTargeted( LevelObject* object ) override;

  //! Show interaction menu
  void showInteractionMenu();

  //! Hide the interaction menu
  void hideInteractionMenu();

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

  //! Check if the NPC has dialogue for the requested quest
  virtual bool hasDialogue( const Quest::Type quest ) const = 0;
                                                                  
private slots:

  // Handle standing state entered
  void handleStandingStateEntered();

  // Handle walking state entered
  void handleWalkingStateEntered();

  // Handle walking state exited
  void handleWalkingStateExited();

private:

  // Load the interaction menu
  void loadInteractionMenu();

  // Update the time dependent states
  bool updateTimeDependentStates() override;

  // Record if the NPC has a walking state
  bool d_has_walking_state;

  // The NPC sprites
  std::shared_ptr<StateDirectionGameSpriteMap> d_sprites;

  // The active state
  State d_active_state;

  // The interaction menu
  NPCInteractionMenu* d_interaction_menu;
};
  
} // end QtD1 namespace

#endif // end NPC_H

//---------------------------------------------------------------------------//
// end NPC.h
//---------------------------------------------------------------------------//
