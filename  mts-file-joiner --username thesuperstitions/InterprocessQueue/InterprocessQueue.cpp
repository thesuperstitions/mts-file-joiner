//---------------------------------------------------------------------------
/*********************************************************************
	Login		: rosskw1
	Model Element	: Queue
  Generated Date	: Mon, 21, Apr 2008
	File Path	: Queue.cppmy

  Description: This class uses a boost timed-mutex to provide a means
  by which a user can de-queue messages and have an automatic timeout
  so that if a message isn't de-queued within a user-specified timout,
  control is returned to the user with a NULL pointer.

  For the producer, messages are dropped in the queue and control is
  returned, with a status of "true". If the queue is full, a return
  value of "false" is returned.  The user could then try to queue the
  message again.
*********************************************************************/


#include "InterprocessQueue.h"
#include <boost/interprocess/mapped_region.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/interprocess/sync/scoped_lock.hpp>
#include "boost/thread.hpp"
#include <sys/timeb.h>


using namespace boost::interprocess;

namespace framework {
	namespace utils {

struct InterprocessQueueSyncMessage
{
  unsigned int syncWord;
};

//---------------------------------------------------------------------------


//Constructor

//---------------------------------------------------------------------------
InterprocessQueue::InterprocessQueue(const char* queueName, unsigned int maxMessageSizeInBytes,
                                     unsigned long int maxNumberOfMessages) :
exitFlag(false), QueueInitializationSemaphore(0), 
maxMsgSize(maxMessageSizeInBytes + sizeof(unsigned int)),
maxMsgs(maxNumberOfMessages), totalQueueSize(maxMsgSize * maxMsgs)
{
  bool alreadyCreatedFlag = false;

  strcpy(QueueName, queueName);

  try
  {
    try
    {
      //Create a shared memory object.
      shm1 = new shared_memory_object(create_only, queueName, read_write);

      //Set size
      shm1->truncate(totalQueueSize);
		}
    catch (...)
    {
      //Create a shared memory object.
      shm1 = new shared_memory_object(open_only, queueName, read_write);
    };

    region1 = new mapped_region
      (*shm1                       //What to map
      ,read_write   //Map it as read-write
      );

    //Get the address of the mapped region
    addr1 = region1->get_address();

    //Construct the shared structure in memory
    myQueue = new (addr1) unsigned char[totalQueueSize];
    //printf("\nInterprocessQueue-QName=%s, Qadd=0x%x, Qsize=%u\n", queueName, myQueue, totalQueueSize);


    sprintf(ControlDataName, "%sControlData", queueName);

    try
    {
      //Create a shared memory object.
      shm2 = new shared_memory_object(create_only, ControlDataName, read_write);

      //Set size
      shm2->truncate(sizeof(SharedMemoryQueueControlData));
    }
    catch (...)
    {
      //Create a shared memory object.
      shm2 = new shared_memory_object(open_only, ControlDataName, read_write);
      alreadyCreatedFlag = true;
		}

    //Map the whole shared memory in this process
    region2 = new mapped_region
      (*shm2                       //What to map
      ,read_write   //Map it as read-write
      );

    //Get the address of the mapped region
    addr2       = region2->get_address();

    //Construct the shared structure in memory
    myControlData = new (addr2) SharedMemoryQueueControlData(maxMsgs);

    if (alreadyCreatedFlag != true)
    {
      //myControlData->getMsgSemaphore = 0;
      //myControlData->addMessageSemaphore = maxMsgs;
      myControlData->CurrentReadSlot = 0;
      myControlData->CurrentWriteSlot = 0;
      myControlData->NumberMessagesInQueue = 0;
      myControlData->InterfaceStatus = false;
    }
    else
    {
      myControlData->InterfaceStatus = true;
      //queueState = QueueSynchronized;
      //printf("\nInterprocessQueue::InterprocessQueue-Queue Synching Complete");
    }

  }
  catch (...)
  {
  };
}

//---------------------------------------------------------------------------

// Destructor

//---------------------------------------------------------------------------

InterprocessQueue::~InterprocessQueue()
{
  bool result1, result2;
  try
  {
    exitFlag = true;

  { // Start of scope.
    scoped_lock<interprocess_mutex> lock(myControlData->myDataAccessMutex); //This lock protects the queue itself.
    myControlData->getMsgSemaphore.post();  // Wake "timedGetMessage".
    myControlData->myDataAccessMutex.unlock();
    myControlData->addMessageSemaphore.post();
    myControlData->InterfaceStatus = false;
  } // End of scope.

    delete region1;
    delete shm1;
    result1 = shared_memory_object::remove(QueueName);

    delete region2;
    delete shm2;
    result2 = shared_memory_object::remove(ControlDataName);
  }
  catch (...)
  {
  };
}

//**********************************************************************************************************************
//
//  Name: getQueueState
//
//  Purpose: Determines if either itself or the "Queue Partner" has taken the interface down.
//           Returns "QueueState".
//
//           QueueSynchronizing = Queue interface is down.
//
//           QueueSynchronized = Queue interface is operational.
//
//**********************************************************************************************************************

InterprocessQueue::QueueState InterprocessQueue::getQueueState(void)
{
	bool sharedMemoryQueueState;

  { // Start of scope.
    scoped_lock<interprocess_mutex> lock(myControlData->myDataAccessMutex); //This lock protects the queue itself.
		sharedMemoryQueueState = myControlData->InterfaceStatus;
  } // End of scope.

  if (sharedMemoryQueueState == true)
  {
    return(QueueSynchronized);
  }
  else
    return(QueueSynchronizing);
}

//---------------------------------------------------------------------------
//
// timedAddMessage
//
// User adds messages by calling "addMessage".  Returns "true" if
// successful (queue not full) or "false" if unsuccessful (queue full).
//
// This is a "Timed Add" which means that this function will try to queue the
// message for the user-specified period of time.  The user gets an indication
// of whether the message was queued within that time period.
//
// "true"  = successfully queued message within the time period.
// "false" = message could not be queued within the time period.
//
//---------------------------------------------------------------------------

bool InterprocessQueue::timedAddMessage(const unsigned char* message, unsigned int messageSizeInBytes,
                                        unsigned int timeoutSecs, unsigned long int timeoutMicroSecs)
{
  try
  {
    // Just in case this function gets invoked during shutdown.
    if (exitFlag == true)
      return(false);

    if (getQueueState() == QueueSynchronizing)
        return(false);

	  { // Start of Scope.
      // Get the mutex just long enough to add the message to the queue.
		  scoped_lock<interprocess_mutex> lock(myControlData->myDataAccessMutex); //This lock protects the queue itself.

      // If the queue is full, pull the 1st message out to make room for the new message.  Keep only the freshest data.  
      if (myControlData->NumberMessagesInQueue >= maxMsgs)
      {
        unsigned char msg[INTERPROCESS_QUEUE_MAX_MESSAGE_SIZE_IN_BYTES];
        unsigned int messageSizeInBytes;

	      // Copy the message into the from the queue into the user's buffer.
		    messageSizeInBytes = *((unsigned int*)&(myQueue[myControlData->CurrentReadSlot*maxMsgSize]));
        memcpy(&msg, &(myQueue[(myControlData->CurrentReadSlot*maxMsgSize)+sizeof(unsigned int)]), messageSizeInBytes);
 
        myControlData->NumberMessagesInQueue--; // Decrement # messages in the queue.
  
        ++myControlData->CurrentReadSlot %= maxMsgs; // Move pointer to next message in the queue.
        myControlData->addMessageSemaphore.post();   // Indicate that there's now room in the queue for another message.
      }
	  } // End of Scope.

    // Wait for the specified amount of time for a message to come into the queue.
    if(myControlData->addMessageSemaphore.timed_wait(boost::get_system_time() + boost::posix_time::seconds(timeoutSecs) +
    boost::posix_time::microseconds(timeoutMicroSecs)) == false)
      return(false);

    { // Start of Scope.
      // Get the mutex just long enough to add the message to the queue.
      scoped_lock<interprocess_mutex> lock(myControlData->myDataAccessMutex); //This lock protects the queue itself.

      unsigned char* ptr = &(myQueue[myControlData->CurrentWriteSlot*maxMsgSize]);
      ((unsigned int*)ptr)[0] = messageSizeInBytes; // Put the # of Message-bytes at front of message.

      ptr += sizeof(unsigned int);  // Set the pointer past the byte-count, to the message portion of the buffer.
      memcpy(ptr, message, messageSizeInBytes);

      myControlData->NumberMessagesInQueue++;

      ++myControlData->CurrentWriteSlot %= maxMsgs;

      myControlData->getMsgSemaphore.post();  // Wake "timedGetMessage".

      return(true); // Message was queued
    } // End of Scope.
  }
  catch (...)
  {
		return(false);
	};
  return(false);
}

//---------------------------------------------------------------------------

// timedGetMessage

// Immediately check to see if the thread should exit.  Check to see if there
// is a message in the queue and, if so, return it to the user.  If not, wait
// up to the user-defined timeout.  If a message becomes available in the
// queue within the timeout period, return value = "true".  If not, return
// value = "false".
//---------------------------------------------------------------------------

bool InterprocessQueue::timedGetMessage(unsigned char* msg, unsigned int* messageSizeInBytes, unsigned int timeoutSecs, unsigned long int timeoutMicroSecs)
{
  try
  {
    // Just in case this function gets invoked during shutdown.
    if (exitFlag == true)
      return(false);

    if (getQueueState() == QueueSynchronizing)
        return (false);

		// Wait on a semaphore that indicates that there is room in the queue for another message.
    if (myControlData->getMsgSemaphore.timed_wait(boost::get_system_time() + boost::posix_time::seconds(timeoutSecs) +
        boost::posix_time::microseconds(timeoutMicroSecs)) == true)
    {
			//This lock protects the queue itself.
      scoped_lock<interprocess_mutex> myDataAccessLock(myControlData->myDataAccessMutex);

	    // Copy the message into the from the queue into the user's buffer.
			*messageSizeInBytes = *((unsigned int*)&(myQueue[myControlData->CurrentReadSlot*maxMsgSize]));
      memcpy(msg, &(myQueue[(myControlData->CurrentReadSlot*maxMsgSize)+sizeof(unsigned int)]), *messageSizeInBytes);

      myControlData->NumberMessagesInQueue--; // Decrement # messages in the queue.

      ++myControlData->CurrentReadSlot %= maxMsgs; // Move pointer to next message in the queue.
      myControlData->addMessageSemaphore.post();   // Indicate that there's now room in the queue for another message.

      return(true);
    }
    else
      return(false);
  }
  catch(...)
  {
    return(false);
  };

  return(false);
}


} // end of namespace framework
} // end of namespace utils


