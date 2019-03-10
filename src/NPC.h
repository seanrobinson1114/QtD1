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
#include "Sound.h"

namespace QtD1{

class NPCInteractionMenu;
class NPCDialogueBox;

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

  //! The reserved mixer channel (for playing dialogue audio)
  static int getReservedMixerChannel();

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

protected:

  //! The NPC state enum
  enum State{
    Standing = 0,
    Walking
  };

  //! The dialogue data
  struct DialogueData
  {
    //! Constructor
    DialogueData()
      : dialogue_file_name(),
        raw_dialogue_text(),
        loaded( false ),
        dialogue(),
        dialogue_text()
    { /* ... */ }

    //! Destructor
    ~DialogueData()
    { /* ... */ }
    
    QString dialogue_file_name;
    QString raw_dialogue_text;

    bool loaded;
    std::unique_ptr<Sound> dialogue;
    QPixmap dialogue_text;
  };

  //! The NPC state map
  typedef QMap<NPC::State,std::shared_ptr<BasicActor::DirectionGameSpriteMap> >
  StateDirectionGameSpriteMap;

  //! Set the NPC sprites
  void setNPCSprites(
                 const std::shared_ptr<StateDirectionGameSpriteMap>& sprites );

  //! Initialize the state machine
  virtual void initializeStateMachine( QStateMachine& state_machine );

  //! Load the interaction menu
  virtual NPCInteractionMenu* createInteractionMenu( QWidget* parent ) = 0;

  //! Greet the character
  virtual void greet() = 0;

  //! Check if the NPC has dialogue for the requested quest
  virtual bool hasDialogue( const Quest::Type quest ) const = 0;

  //! Get the dialogue font
  QString getDialogueFont() const;

  //! Get the dialogue box width
  int getDialogueBoxWidth() const;

  //! Play and display dialogue
  void playAndDisplayDialogue( DialogueData& data );

private slots:

  // Show interaction menu (signals will be emitted)
  void showInteractionMenu();

  // Hide the interaction menu (signals will be emitted)
  void hideInteractionMenu();

  // Handle dialogue finished
  void handleDialogueFinished();

  // Handle standing state entered
  void handleStandingStateEntered();

  // Handle walking state entered
  void handleWalkingStateEntered();

  // Handle walking state exited
  void handleWalkingStateExited();

private:

  // Load the interaction menu
  void loadInteractionMenu();

  // Load the dialogue data (just-in-time)
  void loadDialogueData( DialogueData& data ) const;

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

  // The dialogue font
  QString d_dialogue_font;

  // The dialogue font size
  int d_dialogue_font_size;

  // The NPC dialogue box
  NPCDialogueBox* d_dialogue_box;
};
  
} // end QtD1 namespace

#endif // end NPC_H

//---------------------------------------------------------------------------//
// end NPC.h
//---------------------------------------------------------------------------//
