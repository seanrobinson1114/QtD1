//---------------------------------------------------------------------------//
//!
//! \file   BasicActorStandingByTargetTransition.h
//! \author Alex Robinson
//! \brief  The actor standing by target transition class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ACTOR_STANDING_BY_TARGET_TRANSITION_H
#define ACTOR_STANDING_BY_TARGET_TRANSITION_H

// Qt Includes
#include <QSignalTransition>

namespace QtD1{

class BasicActor;

//! The actor standing by target transition class
class BasicActorStandingByTargetTransition : public QSignalTransition
{
  
public:

  //! Constructor
  BasicActorStandingByTargetTransition( BasicActor* actor );

  //! Destructor
  ~BasicActorStandingByTargetTransition()
  { /* ... */ }

private:

  // Custom event test
  bool eventTest( QEvent* event ) override;
};
  
} // end QtD1 namespace

#endif // end ACTOR_STANDING_BY_TARGET_TRANSITION_H

//---------------------------------------------------------------------------//
// end BasicActorStandingByTargetTransition.h
//---------------------------------------------------------------------------//
