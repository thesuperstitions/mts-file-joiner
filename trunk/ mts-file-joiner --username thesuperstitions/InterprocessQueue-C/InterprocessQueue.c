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

#include "framework/cutils/interprocess_mutex.h"
#include "framework/cutils/interprocess_semaphore.h"
#include "framework/cutils/interprocess_condition.h"
#include "framework/cutils/shared_memory_object.h"
#include "framework/cutils/mapped_region.h"

#include <sys/timeb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <time.h>

/*---------------------------------------------------------------------------

//Macros

//---------------------------------------------------------------------------*/

#define RETURN_ERROR 	\
{ 										\
	free(context);			\
	*result = -1;				\
	printf("\nTest");		\
	return(0);					\
}

#define ONE_BILLION 1000000000

//---------------------------------------------------------------------------*/

/*	This structure is built within Shared Memory and holds control data for the operation of the Queue.  */

typedef struct framework_utils_SharedMemoryQueueControlData_private
{
	framework_utils_interprocess_semaphore getMsgSemaphore;      /*## Controls access to "Get" a message.*/
	framework_utils_interprocess_semaphore addMessageSemaphore;   /*## Controls access to "Add" a message.*/
	framework_utils_interprocess_mutex     myDataAccessMutex;     /*## Controls access to the Control Data.*/
	framework_utils_interprocess_condition syncrhonizeCondition; /*## Condition to wait until the queue is synchronized*/

	unsigned int                              NumberMessagesInQueue; /*## Current count of messages in Queue*/
	unsigned int                              CurrentReadSlot;       /*## Slot in Queue from which to read next message.*/
	unsigned int                              CurrentWriteSlot;      /*## Slot in Queue to write next message.*/
	int                                       InterfaceStatus;       /*## Status of the queue (both clients established)*/
} framework_utils_SharedMemoryQueueControlData_private;

enum framework_utils_InterprocessQueue_QueueState
{
	QueueSynchronizing = 0,  /*## Only one queue client established.*/
	QueueSynchronized  = 1   /*## Both queue clients established.*/
};

			/*## class InterprocessQueue*/
typedef struct framework_utils_InterprocessQueue_private
{
	char          QueueName[100];         /*## Shared memory name for the Queue.*/
	char          ControlDataName[150];   /*## Shared memory name for the Queue Control data.*/
	unsigned long maxMsgSize;             /*## Messages cannot exceed this size.*/
	unsigned long maxMsgs;	              /*## Maximum number of message that the queue can hold.*/
	unsigned long totalQueueSize;         /*## Size of queue in bytes.*/

	/*    Attributes    /*/
	int      exitFlag;
	int  createdSharedMemoryFlag;

	/*    Shared Memory Attributes    */
	unsigned char*                                myQueue;
	framework_utils_shared_memory_object          shm1;
	framework_utils_mapped_region                 region1;
	void*                                         addr1;

	framework_utils_SharedMemoryQueueControlData_private* myControlData;
	framework_utils_shared_memory_object          shm2;
	framework_utils_mapped_region                 region2;
	void*                                         addr2;
} framework_utils_InterprocessQueue_private;

struct InterprocessQueueSyncMessage
{
	unsigned int syncWord;
};

//---------------------------------------------------------------------------

int framework_utils_InterprocessQueue_destroyInterprocessQueue(const char* queueName)
{
	int result;
	char controlDataName[100];
	char s[200];

	sprintf(controlDataName, "%sControlData", queueName);

	result = framework_utils_shared_memory_object_remove(queueName);
	if (result != -1)
	{
		result = framework_utils_shared_memory_object_remove(controlDataName);
		printf("InterprocessQueue_destroyInterprocessQueue : InterprocessQueue with name \"%s\" does not exist.  No Delete Necessary.", queueName);
	}
	else
		printf("InterprocessQueue_destroyInterprocessQueue : InterprocessQueue with name \"%s\" does not exist.  No Delete Necessary.", queueName);

	return(result);
}

/*---------------------------------------------------------------------------

//Constructors

//---------------------------------------------------------------------------*/

framework_utils_InterprocessQueue* framework_utils_InterprocessQueue_create2
(
	int* result,
	const char* queueName,
	unsigned int maxMessageSizeInBytes,
	unsigned long int maxNumberOfMessages
)
{
	framework_utils_InterprocessQueue_private* context;

	if ( (context = malloc(sizeof(framework_utils_InterprocessQueue_private)) ) == 0)
	{
		*result = -1;
		return(0);
	}

	context->maxMsgSize = maxMessageSizeInBytes + sizeof(unsigned int);
	context->maxMsgs = maxNumberOfMessages;
	context->totalQueueSize = (context->maxMsgSize * context->maxMsgs);

  strcpy(context->QueueName, queueName);
	int createdFlag1, createdFlag2;
	char s[200];

	context->exitFlag = 1; /* 0=true, 1=false */

	/* Create a shared memory object. */
	*result = framework_utils_shared_memory_object_create(&(context->shm1), create_only_t, queueName, read_write);

		/*Set size */
	if (*result == EEXIST)
	{
		createdFlag1 = 1;

		//Create a shared memory object.
		*result = framework_utils_shared_memory_object_create(&(context->shm1), open_only_t, queueName, read_write);
		if (*result != 0)
			RETURN_ERROR
	}
	else
	{
		if (*result != 0)
			RETURN_ERROR

		createdFlag1 = 0;
  	if ((*result = framework_utils_shared_memory_object_truncate(&(context->shm1), context->totalQueueSize)) != 0)
			RETURN_ERROR
	}

	if ((*result = framework_utils_mapped_region_create(&(context->region1), &(context->shm1), mapped_region_read_write)) != 0)
		RETURN_ERROR

	//Get the address of the mapped region
	context->addr1 = framework_utils_mapped_region_get_address(&(context->region1));

	//Construct the shared structure in memory
	if ((context->myQueue = (unsigned char*)context->addr1) == 0)
		RETURN_ERROR


	sprintf(context->ControlDataName, "%sControlData", queueName);

	/* Create a shared memory object. */
	*result = framework_utils_shared_memory_object_create(&(context->shm2), create_only_t, context->ControlDataName, read_write);

	/*Set size */
	if (*result == EEXIST)
  {
		createdFlag2 = 1;

		//Create a shared memory object.
		*result = framework_utils_shared_memory_object_create(&(context->shm2), open_only_t, context->ControlDataName, read_write);
		if (*result != 0)
			RETURN_ERROR
	}
	else
	{
		if (*result != 0)
			RETURN_ERROR
 		createdFlag2 = 0;
  	if ((*result = framework_utils_shared_memory_object_truncate(&(context->shm2), sizeof(framework_utils_SharedMemoryQueueControlData_private))) != 0)
			RETURN_ERROR
	}

	if ((*result = framework_utils_mapped_region_create(&(context->region2), &(context->shm2), mapped_region_read_write)) != 0)
		RETURN_ERROR

	//Get the address of the mapped region
	context->addr2 = framework_utils_mapped_region_get_address(&(context->region2));

	//Construct the shared structure in memory
	if ((context->myControlData = (framework_utils_SharedMemoryQueueControlData_private*)context->addr2) == 0)
		RETURN_ERROR

		if (createdFlag2 == 0)
		{
			// The Shared Memory Block was "created".  Lock it so no other process can modify it.
			if ((*result = framework_utils_interprocess_mutex_create(&(context->myControlData->myDataAccessMutex))) != 0)
				RETURN_ERROR

			// Lock access to the shared memory
			if ((*result = framework_utils_interprocess_mutex_lock(&(context->myControlData->myDataAccessMutex))) != 0)
				RETURN_ERROR

			// Create the rest of the interprocess control data.
			if ((*result = framework_utils_interprocess_semaphore_create(&(context->myControlData->getMsgSemaphore), 0)) != 0)
				RETURN_ERROR

			if ((*result = framework_utils_interprocess_semaphore_create(&(context->myControlData->addMessageSemaphore),
					context->maxMsgs)) != 0)
				RETURN_ERROR

			if ((*result = framework_utils_interprocess_condition_create(&(context->myControlData->syncrhonizeCondition))) != 0)
				RETURN_ERROR

			context->myControlData->CurrentReadSlot = 0;
			context->myControlData->CurrentWriteSlot = 0;
			context->myControlData->NumberMessagesInQueue = 0;
			context->myControlData->InterfaceStatus = 1;

			// Unlock access to the shared memory
			if ((*result = framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex))) != 0)
				RETURN_ERROR
		}
		else
		{
			// Lock access to the shared memory
			if ((*result = framework_utils_interprocess_mutex_lock(&(context->myControlData->myDataAccessMutex))) != 0)
				RETURN_ERROR

			context->myControlData->InterfaceStatus = 0;

			if ((*result = framework_utils_interprocess_condition_notify_all(&(context->myControlData->syncrhonizeCondition))) != 0)
				RETURN_ERROR

			// Unlock access to the shared memory
			if ((*result = framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex))) != 0)
				RETURN_ERROR
    }

	return((framework_utils_InterprocessQueue_private*)context);
}

framework_utils_InterprocessQueue* framework_utils_InterprocessQueue_create(int* result, const char* queueName)
{
	return( framework_utils_InterprocessQueue_create2(result, queueName, INTERPROCESS_QUEUE_MAX_MESSAGE_SIZE_IN_BYTES,
					INTERPROCESS_QUEUE_MAX_MESSAGES_IN_QUEUE) );
}

framework_utils_InterprocessQueue* framework_utils_InterprocessQueue_create1(int* result, const char* queueName,
							   unsigned int maxMessageSizeInBytes)
{
	return( framework_utils_InterprocessQueue_create2(result, queueName, maxMessageSizeInBytes,
																										INTERPROCESS_QUEUE_MAX_MESSAGES_IN_QUEUE) );
}

//---------------------------------------------------------------------------

// Destructor

//---------------------------------------------------------------------------

int framework_utils_InterprocessQueue_delete(framework_utils_InterprocessQueue* contxt)
{
	char s[200];
	int result;
	framework_utils_InterprocessQueue_private* context = (framework_utils_InterprocessQueue_private*) contxt;

	context->exitFlag = 0;

	result = framework_utils_interprocess_mutex_lock(&(context->myControlData->myDataAccessMutex)); //This lock protects the queue itself.

	if (context->myControlData->InterfaceStatus == 1)  // Status of 0 == 2 clients, 1 == 1 client.  If 1, we must delete shared memory.
	{
		result = framework_utils_interprocess_semaphore_post(&(context->myControlData->getMsgSemaphore));  // Wake "timedGetMessage".
		result = framework_utils_interprocess_semaphore_post(&(context->myControlData->addMessageSemaphore));

		// Delete all of the Interprocess resources.
		result = framework_utils_interprocess_semaphore_delete(&(context->myControlData->getMsgSemaphore));
		result = framework_utils_interprocess_semaphore_delete(&(context->myControlData->addMessageSemaphore));

		result = framework_utils_interprocess_condition_notify_all(&(context->myControlData->syncrhonizeCondition));
		result = framework_utils_interprocess_condition_delete(&(context->myControlData->syncrhonizeCondition));

		result = framework_utils_mapped_region_delete(&(context->region1));
		result = framework_utils_shared_memory_object_delete(&(context->shm1));
		result = framework_utils_shared_memory_object_remove(context->QueueName);

		result = framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex)); // Unlock access
		result = framework_utils_interprocess_mutex_delete(&(context->myControlData->myDataAccessMutex)); // Delete the mutex

		result = framework_utils_mapped_region_delete(&(context->region2));
		result = framework_utils_shared_memory_object_delete(&(context->shm2));
		result = framework_utils_shared_memory_object_remove(context->ControlDataName);
	}
	else
	{
		context->myControlData->InterfaceStatus = 1;
		result = framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex)); // Unlock access
	}

	free(context);

	context = 0;

	return(0);
}

//*********************************************************************************************************************
//
//  Name: framework_utils_getExpirationTime
//
//  Purpose: Get the current time.  Add in the seconds and usecs from the input params.  Return the "timespec"
//           structure.
//
//*********************************************************************************************************************

void framework_utils_getExpirationTime(struct timespec* ts, unsigned int timeoutSecs,
unsigned long int timeoutMicroSecs)
{
	int i;

	/* Calculate the absolute time for timer expiration. */
	clock_gettime(CLOCK_REALTIME, ts);        // Get the current time.
	ts->tv_nsec += (timeoutMicroSecs * 1000); // Convert input usecs to nsecs
	i  = ts->tv_nsec / ONE_BILLION;           // Do we now have enough nsecs to == 1 sec?
	ts->tv_nsec -= (i * ONE_BILLION);         // Subtract off the seconds portion.
	ts->tv_sec  += timeoutSecs + i;           // Add in the possible 1-second carryover from nsecs.
}


//*********************************************************************************************************************
//
//  Name: waitOnQueueSynchronization
//
//  Purpose: Wait for the Queue Constructor to be invoked by the client on the other end of the Queue.  The other
//           client's Constructor will change the "Condition" of the queue to "Synchronized".  If the queue is already
//           synchronized, return and allow this client to use the queue.
//
//*********************************************************************************************************************

int framework_utils_InterprocessQueue_waitOnQueueSynchronization(framework_utils_InterprocessQueue* contxt,
	unsigned int timeoutSecs, unsigned long int timeoutMicroSecs)
{
	int result = 0;
	framework_utils_InterprocessQueue_private* context = (framework_utils_InterprocessQueue_private*) contxt;

	struct timespec ts;

	if (framework_utils_InterprocessQueue_getQueueState(context) == QueueSynchronizing)
	{
		//This lock protects the queue itself.
		framework_utils_interprocess_mutex_lock(&(context->myControlData->myDataAccessMutex));

		/* Calculate the absolute time for timer expiration. */
		framework_utils_getExpirationTime(&ts, timeoutSecs, timeoutMicroSecs);

		framework_utils_getExpirationTime(&ts, timeoutSecs, timeoutMicroSecs);

  	if((result = framework_utils_interprocess_condition_timed_wait(&(context->myControlData->syncrhonizeCondition),
		&(context->myControlData->myDataAccessMutex), &ts)) == ETIMEDOUT)
			result = 1;

		//This lock protects the queue itself.
		framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex));
	}

	return(result);
}

//*********************************************************************************************************************
//
//	Name:     getQueueState
//
//	Purpose:  Determines if either itself or the "Queue Partner" has taken the interface down.
//            Returns "QueueState".
//
//            QueueSynchronizing = Queue interface is down.
//
//            QueueSynchronized = Queue interface is operational.
//
//*********************************************************************************************************************

int framework_utils_InterprocessQueue_getQueueState(framework_utils_InterprocessQueue* contxt)
{
	int sharedMemoryQueueState;
	framework_utils_InterprocessQueue_private* context = (framework_utils_InterprocessQueue_private*) contxt;

	//This lock protects the queue itself.
	framework_utils_interprocess_mutex_lock(&(context->myControlData->myDataAccessMutex));

	sharedMemoryQueueState = context->myControlData->InterfaceStatus;

	framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex));

	return(sharedMemoryQueueState);
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

int framework_utils_InterprocessQueue_timedAddMessage(framework_utils_InterprocessQueue* contxt,
	const unsigned char* message, unsigned int messageSizeInBytes, unsigned int timeoutSecs,
	unsigned long int timeoutMicroSecs)
{
	struct timespec ts;
	unsigned char*  ptr;
	int             result = 0;
	framework_utils_InterprocessQueue_private* context = (framework_utils_InterprocessQueue_private*) contxt;

	// Just in case this function gets invoked during shutdown.
	if (context->exitFlag == 0)
		result = 1;
	else
	{
		// Wait for the specified amount of time for adding the message to the queue.
		framework_utils_getExpirationTime(&ts, timeoutSecs, timeoutMicroSecs);

		if((result = framework_utils_interprocess_semaphore_timed_wait(
		&(context->myControlData->addMessageSemaphore), &ts)) == ETIMEDOUT)
			result = 1;
		else
		{
			// Start of Scope.
			// Get the mutex just long enough to add the message to the queue.
			if ((result = framework_utils_interprocess_mutex_lock(
			&(context->myControlData->myDataAccessMutex))) == -1) //This lock protects the queue itself
				result = 1;
			else
			{
				result = 0;

				ptr = &(context->myQueue[context->myControlData->CurrentWriteSlot * context->maxMsgSize]);
				((unsigned int*)ptr)[0] = messageSizeInBytes; // Put the # of Message-bytes at front of message.

				ptr += sizeof(unsigned int);  // Set the pointer past the byte-count, to the message portion of the buffer.
				memcpy(ptr, message, messageSizeInBytes);

				context->myControlData->NumberMessagesInQueue++;

				context->myControlData->CurrentWriteSlot++;
				context->myControlData->CurrentWriteSlot %= context->maxMsgs;

				// Wake "timedGetMessage".
				if (framework_utils_interprocess_semaphore_post(&(context->myControlData->getMsgSemaphore)) == -1)
					result = 1;
			}
		}
	}
	framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex));

	return(result); // Message was queued.
}

//---------------------------------------------------------------------------

// timedGetMessage

// Immediately check to see if the thread should exit.  Check to see if there
// is a message in the queue and, if so, return it to the user.  If not, wait
// up to the user-defined timeout.  If a message becomes available in the
// queue within the timeout period, return value = "true".  If not, return
// value = "false".
//---------------------------------------------------------------------------

int framework_utils_InterprocessQueue_timedGetMessage(framework_utils_InterprocessQueue* contxt, unsigned char* msg,
	unsigned int* messageSizeInBytes, unsigned int timeoutSecs, unsigned long int timeoutMicroSecs)
{
	struct timespec ts;
	int    result = 0;
	framework_utils_InterprocessQueue_private* context = (framework_utils_InterprocessQueue_private*) contxt;

	// Just in case this function gets invoked during shutdown.
	if (context->exitFlag == 0)
		result = 1;
	else
	{
		// Wait on a semaphore that indicates that there is room in the queue for another message.
		framework_utils_getExpirationTime(&ts, timeoutSecs, timeoutMicroSecs);

		if((result = framework_utils_interprocess_semaphore_timed_wait(&(context->myControlData->getMsgSemaphore), &ts))
		== ETIMEDOUT)
			result = 1;
		else
		{
			result = 0;

			//This lock protects the queue itself.
			if (framework_utils_interprocess_mutex_lock(&(context->myControlData->myDataAccessMutex)) == -1)
				result = 1;
			else
			{
				// Copy the message from the queue into the user's buffer.
				*messageSizeInBytes = *((unsigned int*)&(context->myQueue[context->myControlData->CurrentReadSlot*
					context->maxMsgSize]));
				memcpy(msg, &(context->myQueue[(context->myControlData->CurrentReadSlot*context->maxMsgSize)+
					sizeof(unsigned int)]), *messageSizeInBytes);

				context->myControlData->NumberMessagesInQueue--; // Decrement # messages in the queue.

				context->myControlData->CurrentReadSlot++;
				context->myControlData->CurrentReadSlot %= context->maxMsgs; // Move pointer to next message in the queue.

				// Indicate that there's now room in the queue for another message.
				if(framework_utils_interprocess_semaphore_post(&(context->myControlData->addMessageSemaphore)) == -1)
					result = 1;
			}
		}
	}
	framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex));

	return(result);
}

//---------------------------------------------------------------------------

// flushQueue

// Immediately check to see if the thread should exit.  Try to get the semaphore
// that protects the queue.  Flush the queue by resetting the control structure
// to the initialized state.
//---------------------------------------------------------------------------

int framework_utils_InterprocessQueue_flushQueue(framework_utils_InterprocessQueue* contxt)
{
	unsigned int i;
	int          result = 0;
	framework_utils_InterprocessQueue_private* context = (framework_utils_InterprocessQueue_private*) contxt;

	// Just in case this function gets invoked during shutdown.
	if (context->exitFlag == 0)
		result = 1;
	else
	{
		//This lock protects the queue itself.
		if (framework_utils_interprocess_mutex_lock(&(context->myControlData->myDataAccessMutex)) == -1)
			result = 1;
		else
		{
			//Drain the remaining semaphores.
			for (i=0; i<context->myControlData->NumberMessagesInQueue; i++)
			{
  			framework_utils_interprocess_semaphore_try_wait(&(context->myControlData->getMsgSemaphore));

				// Indicate that there's now room in the queue for another message.
				framework_utils_interprocess_semaphore_post(&(context->myControlData->addMessageSemaphore));
			}

			context->myControlData->NumberMessagesInQueue = 0; // Initialize number of messages in the queue.

			context->myControlData->CurrentReadSlot = 0;       // Initialize pointer to next slot in the queue to read.

			context->myControlData->CurrentWriteSlot = 0;      // Initialize pointer to next slot in the queue to write.
			framework_utils_interprocess_mutex_unlock(&(context->myControlData->myDataAccessMutex));
		} //## End of scope
	}

	return(result);
}

