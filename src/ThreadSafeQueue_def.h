//---------------------------------------------------------------------------//
//!
//! \file   ThreadSafeQueue_def.h
//! \author Alex Robinson
//! \brief  The thread-safe queue class definition
//!
//---------------------------------------------------------------------------//

#ifndef THREAD_SAFE_QUEUE_DEF_H
#define THREAD_SAFE_QUEUE_DEF_H

// Qt Includes
#include <QMutexLocker>

namespace QtD1{

// Initialize the static member data
template<typename T>
bool ThreadSafeQueue<T>::s_stop_waits = false;

// Stop waiting conditions
template<typename T>
void ThreadSafeQueue<T>::stopWaits()
{
  s_stop_waits = true;
}

// Constructor
template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue()
  : d_stop_waits( false ), d_data(), d_mutex(), d_cond()
{ /* ... */ }

// Destructor
template<typename T>
ThreadSafeQueue<T>::~ThreadSafeQueue()
{
  this->purge();
}

// Add an item to the queue
template<typename T>
void ThreadSafeQueue<T>::pushBack( const T& item )
{
  QMutexLocker locker(&d_mutex);
  
  d_data.push_back( item );
  
  d_cond.wakeOne();
}

// Get the top item of the queue
template<typename T>
T ThreadSafeQueue<T>::getTop( const bool wait )
{
  QMutexLocker lock( &d_mutex );
  
  T top_element;
  
  while( true )
  {
    if( s_stop_waits || d_stop_waits )
      break;
    
    if( !this->empty() )
    {
      top_element = d_data.front();
      
      break;
    }
    else if( !wait )
      break;
    else
    {
      d_cond.wait( &d_mutex );
    }
  }
  
  return top_element;
}

// Pop the top item from the queue
template<typename T>
void ThreadSafeQueue<T>::popTop()
{
  if( !this->empty() )
  {
    QMutexLocker lock( &d_mutex );
    
    d_data.pop_front();
  }
}

// Get the size of the queue
template<typename T>
size_t ThreadSafeQueue<T>::size() const
{
  return d_data.size();
}

// Check if the queue is empty
template<typename T>
bool ThreadSafeQueue<T>::empty() const
{
  return d_data.empty();
}

// Purge threads from this queue
template<typename T>
void ThreadSafeQueue<T>::purge()
{
  d_stop_waits = true;
  
  d_cond.wakeAll();
}
  
} // end QtD1 namespace

#endif // end THREAD_SAFE_QUEUE_DEF_H

//---------------------------------------------------------------------------//
// end ThreadSafeQueue.h
//---------------------------------------------------------------------------//
