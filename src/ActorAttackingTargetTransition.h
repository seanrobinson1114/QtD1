//---------------------------------------------------------------------------//
//!
//! \file   ActorAttackingTargetTransition.h
//! \author Alex Robinson, Sean Robinson
//! \brief  The actor attacking target transition class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ACTOR_ATTACKING_TARGET_TRANSITION_H
#define ACTOR_ATTACKING_TARGET_TRANSITION_H

// Qt Includes
#include <QSignalTransition>

namespace QtD1{

class Actor;

//! The actor attacking target transition class
class ActorAttackingTargetTransition : public QSignalTransition
{
  
public:

  //! Constructor
  ActorAttackingTargetTransition( Actor* actor );

  //! Destructor
  ~ActorAttackingTargetTransition()
  { /* ... */ }

private:

  // Custom event test
  bool eventTest( QEvent* event ) override;
};
  
} // end QtD1 namespace

#endif // end ACTOR_ATTACKING_TARGET_TRANSITION_H

//---------------------------------------------------------------------------//
// end ActorAttackingTargetTransition.h
//---------------------------------------------------------------------------//

