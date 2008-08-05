//---------------------------------------------------------------------------
/*********************************************************************
	Login		: rosskw1
	Model Element	: Queue
  Generated Date	: Mon, 21, Apr 2008  
	File Path	: Queue.cpp

  Description: This class uses a boost timed-mutex to provide a means
  by which a user can de-queue messages and have an automatic timeout
  so that if a message isn't de-queued within a user-specified timout,
  control is returned to the user with a NULL pointer.

  For the producer, messages are dropped in the queue and control is
  returned, with a status of "true". If the queue is full, a return
  value of "false" is returned.  The user could then try to queue the
  message again.
*********************************************************************/


#include "Queue.h"
#include "boost/thread.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

//---------------------------------------------------------------------------

//Constructor

//---------------------------------------------------------------------------
Queue::Queue(unsigned long int numberOfItems) 
{
  exitFlag = false;
  myMutex.unlock();
  myQueue = new boost::circular_buffer<void*>(numberOfItems);
}

//---------------------------------------------------------------------------

// Destructor

//---------------------------------------------------------------------------

Queue::~Queue() 
{
  exitFlag = true;
  myMutex.unlock();  // Wake "getMessage".
  delete myQueue;
}

//---------------------------------------------------------------------------

// addMessage

// User adds messages by calling "addMessage".  Returns "true" if
// successful (queue not full) or "false" if unsuccessful (queue full).

//---------------------------------------------------------------------------
        
bool Queue::addMessage(void* message)
{
  if (exitFlag == true)
    return(false);
  
  try
  {
    { // Start of Scope.
      // Get the mutex just long enough to add the message to the queue.
      boost::mutex::scoped_lock myDataAccessLock(myDataAccessMutex); //This lock protects the queue itself.
    
      if (myQueue->full() != true)
      {
        //myQueue.push_back(message);
        myQueue->push_back(message);

        myMutex.unlock();  // Wake "getMessage".

        return(true); // Message was queued
      }  // if (myQueue->full() != true)
      else
        return (false); // Message was NOT queued.
    } // End of Scope.
  }
  catch (...)
  {
  };
  return(false);
}

//---------------------------------------------------------------------------

// CheckForItemsInQueue

// Waits on a mutex that protects access to the queue.  When mutex is received,
// a check is made to see if there's at least one message in the queue.  If
// not, a NULL pointer is returned.  If not empty, the first message (the 
// oldest one) is taken off the queue and passed back to the caller.
//---------------------------------------------------------------------------

void* Queue::CheckForItemsInQueue(void)
{ // Start of scope for the "scoped_lock" mutex.
  void* m_Ptr = NULL;

  boost::mutex::scoped_lock myDataAccessLock(myDataAccessMutex); //This lock protects the queue itself.

  // Check to see if there's a Message in the list   
  if (myQueue->empty() != true)
  {      
    // Get the first message in the list.                                  
    m_Ptr = myQueue->front();  

    // Remove the message from the list now so that the mutex can be unlocked prior to sending.  
    myQueue->pop_front();   // Remove the just-sent Message from the list.
  }

  return(m_Ptr);
} // End of Scope for the "scoped_lock" mutex.  This unlocks the timed mutex.

//---------------------------------------------------------------------------
        
// getMessage

// Immediately check to see if the thread should exit.  Check to see if there
// is a message in the queue and, if so, return it to the user.  If not, wait
// up to the user-defined timeout.  If a message becomes available in the
// queue within the timeout period, return the message.  If not, return a 
// NULL pointer.
//---------------------------------------------------------------------------

void* Queue::getMessage(unsigned int timeoutSecs, unsigned long int timeoutMicroSecs)
{
  void* m_Ptr = NULL;

  // Just in case this function gets invoked during shutdown.
  if (exitFlag == true)
    return(NULL);

  try
  {
    // Check to see if there's a message already waiting on the Queue.  If so, we just return it.
    if ( (m_Ptr = CheckForItemsInQueue()) != NULL)
      return(m_Ptr);

    // There were no items in the Queue, so now we have to wait for either the queue to be unlocked or the timeout occurs.

    // Calculate the duration of the timeout.
    boost::posix_time::time_duration td = boost::posix_time::seconds(timeoutSecs) + boost::posix_time::microseconds(timeoutMicroSecs); //

    // Block on the mutex until either a message is received in the queue (addMessage function unlocks the mutex after dropping a message
    // in the queue), or the timer expires.
    if (myMutex.timed_lock(boost::get_system_time() + td) == true)
    {
      return( CheckForItemsInQueue() );
    }
    else
    {
      // mutex timed out
      return(m_Ptr);
    }
  }
  catch(...)
  {
  };

  return(m_Ptr);
}

