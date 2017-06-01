//---------------------------------------------------------------------------//
//!
//! \file   ActorStandingByTargetTransition.cpp
//! \author Alex Robinson
//! \brief  The actor standing by target transition class definition
//!
//---------------------------------------------------------------------------//

// Qt Includes
#include <QStateMachine>

// QtD1 Includes
#include "ActorStandingByTargetTransition.h"
#include "Actor.h"

namespace QtD1{

// Constructor
ActorStandingByTargetTransition::ActorStandingByTargetTransition( Actor* actor )
  : QSignalTransition( actor, SIGNAL(targetReached(LevelObject*)) )
{ /* ... */ }

// Custom event test
bool ActorStandingByTargetTransition::eventTest( QEvent* event )
{
  // Let the QSignalTransition test if the event type is correct
  if( !QSignalTransition::eventTest( event ) )
    return false;

  QStateMachine::SignalEvent* signal_event =
    dynamic_cast<QStateMachine::SignalEvent*>( event );

  LevelObject* target = signal_event->arguments().at(0).value<LevelObject*>();

  return !target->canBeAttacked();
}
  
} // end QtD1 namespace

//---------------------------------------------------------------------------//
// end ActorStandingByTargetTransition.cpp
//---------------------------------------------------------------------------//
