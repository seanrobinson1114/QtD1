//---------------------------------------------------------------------------//
//!
//! \file   ActorStandingByTargetTransition.h
//! \author Alex Robinson
//! \brief  The actor standing by target transition class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ACTOR_STANDING_BY_TARGET_TRANSITION_H
#define ACTOR_STANDING_BY_TARGET_TRANSITION_H

// Qt Includes
#include <QSignalTransition>

namespace QtD1{

class Actor;

//! The actor standing by target transition class
class ActorStandingByTargetTransition : public QSignalTransition
{
  
public:

  //! Constructor
  ActorStandingByTargetTransition( Actor* actor );

  //! Destructor
  ~ActorStandingByTargetTransition()
  { /* ... */ }

private:

  // Custom event test
  bool eventTest( QEvent* event ) override;
};
  
} // end QtD1 namespace

#endif // end ACTOR_STANDING_BY_TARGET_TRANSITION_H

//---------------------------------------------------------------------------//
// end ActorStandingByTargetTransition.h
//---------------------------------------------------------------------------//
