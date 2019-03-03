//---------------------------------------------------------------------------//
//!
//! \file   BasicActorStandingByTargetTransition.cpp
//! \author Alex Robinson
//! \brief  The actor standing by target transition class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QStateMachine>

// QtD1 Includes
#include "BasicActorStandingByTargetTransition.h"
#include "Actor.h"

namespace QtD1{

// Constructor
BasicActorStandingByTargetTransition::BasicActorStandingByTargetTransition( BasicActor* actor )
  : QSignalTransition( actor, SIGNAL(targetReached(LevelObject*,LevelObject*)) )
{ /* ... */ }

// Custom event test
bool BasicActorStandingByTargetTransition::eventTest( QEvent* event )
{
  // Let the QSignalTransition test if the event type is correct
  if( !QSignalTransition::eventTest( event ) )
    return false;

  QStateMachine::SignalEvent* signal_event =
    dynamic_cast<QStateMachine::SignalEvent*>( event );

  LevelObject* target = signal_event->arguments().at(1).value<LevelObject*>();

  return !target->canBeAttacked();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end BasicActorStandingByTargetTransition.cpp
//---------------------------------------------------------------------------//
