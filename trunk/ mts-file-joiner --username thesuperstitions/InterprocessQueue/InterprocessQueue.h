//---------------------------------------------------------------------------
#ifndef __framework__utils__InterprocessQueueH
#define __framework__utils__InterprocessQueueH

//---------------------------------------------------------------------------


#ifdef SOLARIS
#include <sys/mman.h>
extern "C" {
extern int shm_open(const char *, int, mode_t);
extern int shm_unlink(const char *);
}
#endif

#ifdef SOLARIS
     
	// The include <inttypes.h> below is put in to avoid the following warning, seen with Sun CC
    //     compiler on Solaris:
	//"/usr/include/sys/int_const.h", line 73: Warning (Anachronism): Attempt to redefine INT64__ C without using #undef.
	// This is deliberately put in _before_ the boost includes.
	#include <inttypes.h>
     
#endif


#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

#define INTERPROCESS_QUEUE_MAX_MESSAGE_SIZE_IN_BYTES 4096
#define INTERPROCESS_QUEUE_MAX_MESSAGES_IN_QUEUE     1000

namespace framework {
	namespace utils {

// This structure is built within Shared Memory and holds control data for the operation
// of the Queue.
struct SharedMemoryQueueControlData
{
  SharedMemoryQueueControlData(unsigned int numMsgs) : getMsgSemaphore(0), addMessageSemaphore(numMsgs) {}

  boost::interprocess::interprocess_semaphore getMsgSemaphore;		 //## Controls access to "Get" a message.
  boost::interprocess::interprocess_semaphore addMessageSemaphore; //## Controls access to "Add" a message.
  boost::interprocess::interprocess_mutex     myDataAccessMutex;   //## Controls access to the Control Data.

  unsigned int                                NumberMessagesInQueue;
  unsigned int                                CurrentReadSlot;
  unsigned int                                CurrentWriteSlot;
  bool                                        InterfaceStatus;
};


        //## class InterprocessQueue
class InterprocessQueue
{
  ////    Constructors and destructors    ////
  public :
    enum QueueState
    {
      QueueSynchronizing = 0,
      QueueSynchronized  = 1
    };

    InterprocessQueue(const char* queueName, unsigned int maxMessageSizeInBytes=INTERPROCESS_QUEUE_MAX_MESSAGE_SIZE_IN_BYTES, 
                      unsigned long int maxNumberOfMessages=INTERPROCESS_QUEUE_MAX_MESSAGES_IN_QUEUE);

    //## operation Queue()
    virtual ~InterprocessQueue();

  protected:
    char          QueueName[100];
    char          ControlDataName[150];
    unsigned long maxMsgSize;
    unsigned long maxMsgs;
    unsigned long totalQueueSize;
    boost::interprocess::interprocess_semaphore QueueInitializationSemaphore;

    ////    Operations    ////
    public :
      //## operation addMessage(FederateMessage*)
      virtual bool       timedAddMessage(const unsigned char* message, unsigned int messageSizeInBytes, 
                                         unsigned int timeoutSecs, unsigned long int timeoutMicroSecs);

			virtual bool       timedGetMessage(unsigned char* msg, unsigned int* messageSizeInBytes, 
                                         unsigned int timeoutSecs, unsigned long int timeoutMicroSecs);


      virtual QueueState getQueueState(void);

    ////    Attributes    ////
    protected :
      bool      exitFlag;

    ////    Shared Memory Attributes    ////
    public :
      unsigned char*                           myQueue;
      boost::interprocess::shared_memory_object* shm1;
      boost::interprocess::mapped_region*        region1;
      void*                                    addr1;

      SharedMemoryQueueControlData*            myControlData;
      boost::interprocess::shared_memory_object* shm2;
      boost::interprocess::mapped_region*        region2;
      void*                         addr2;
void LogMessage(char* Msg, double count);
};

} // end of namespace utils
} // end of namespace framework


//---------------------------------------------------------------------------
#endif
