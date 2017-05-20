//---------------------------------------------------------------------------//
//!
//! \file   ThreadSafeQueue.h
//! \author Alex Robinson
//! \brief  The thread-safe queue class declaration
//!
//---------------------------------------------------------------------------//

#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

// Std Lib Includes
#include <deque>

// Qt Includes
#include <QMutex>
#include <QWaitCondition>

namespace QtD1{

template<typename T>
class ThreadSafeQueue
{

public:

  //! Stop waiting conditions
  static void stopWaits();

  //! Constructor
  ThreadSafeQueue();

  //! Destructor
  ~ThreadSafeQueue();

  //! Add an item to the queue
  void pushBack( const T& item );

  //! Get the top item of the queue
  T getTop( const bool wait = true );

  //! Pop the top item from the queue
  void popTop();

  //! Get the size of the queue
  size_t size() const;

  //! Check if the queue is empty
  bool empty() const;

  //! Purge threads from this queue
  void purge();

private:

  // Copy Constructor
  ThreadSafeQueue( const ThreadSafeQueue& );

  // Assignment operator
  ThreadSafeQueue& operator=( const ThreadSafeQueue& );

  // Kills any waiting conditions
  static bool s_stop_waits;

  // Stop waits on this queue
  bool d_stop_waits;

  // The raw queue
  std::deque<T> d_data;

  // The mutex used for thread safety
  QMutex d_mutex;

  // The condition used for thread safety
  QWaitCondition d_cond;
};

} // end QtD1 namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "ThreadSafeQueue_def.h"

//---------------------------------------------------------------------------//

#endif // end THREAD_SAFE_QUEUE_H

//---------------------------------------------------------------------------//
// end ThreadSafeQueue.h
//---------------------------------------------------------------------------//
