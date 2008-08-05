//---------------------------------------------------------------------------
#ifndef QueueH
#define QueueH

//---------------------------------------------------------------------------


#ifdef SOLARIS
#include <sys/mman.h>
extern "C" {
extern int shm_open(const char *, int, mode_t);
extern int shm_unlink(const char *);
}
#endif

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

#define INTERPROCESS_QUEUE_MAX_MESSAGE_SIZE_IN_BYTES 100
#define INTERPROCESS_QUEUE_MAX_MESSAGES_IN_QUEUE     20


struct SharedMemoryQueueControlData
{
SharedMemoryQueueControlData(unsigned int numMsgs) : getMsgSemaphore(0), addMessageSemaphore(numMsgs) {}

  boost::interprocess::interprocess_semaphore getMsgSemaphore;		//## attribute getMsgSemaphore
  boost::interprocess::interprocess_semaphore addMessageSemaphore;
  boost::interprocess::interprocess_mutex myDataAccessMutex;

  unsigned int                            NumberMessagesInQueue;
  unsigned int                            CurrentReadSlot;
  unsigned int                            CurrentWriteSlot;
  unsigned long                           UniqueValue;
  bool                                    InterfaceStatus;
};


using namespace boost::interprocess;


        //## class Queue
class InterprocessQueue
{
  ////    Constructors and destructors    ////
  public :
    enum QueueState
    {
      QueueSynchronizing = 0,
      QueueSynchronized = 1
    };

    InterprocessQueue(char* queueName, unsigned int maxMessageSizeInBytes, unsigned long int maxNumberOfMessages);

    //## operation Queue()
    virtual ~InterprocessQueue();

  protected:
    //unsigned long CurrentMessageSlot;
    char          QueueName[100];
    char          ControlDataName[150];
    unsigned long maxMsgSize;
    unsigned long maxMsgs;
    unsigned long totalQueueSize;
    boost::interprocess::interprocess_semaphore QueueInitializationSemaphore;

    QueueState queueState;

    ////    Operations    ////
    public :
      //## operation addMessage(FederateMessage*)
      virtual bool timedAddMessage(unsigned char* message, unsigned int messageSizeInBytes, unsigned int timeoutSecs,
                                   unsigned long int timeoutMicroSecs);
			virtual bool timedGetMessage(unsigned char* msg, unsigned int* messageSizeInBytes, unsigned int timeoutSecs, unsigned long int timeoutMicroSecs);
      virtual bool SynchronizeQueueUsers(void);
      virtual InterprocessQueue::QueueState getQueueState(void);

    ////    Attributes    ////
    protected :
      bool      exitFlag;

    ////    Shared Memory Attributes    ////
    public :
      unsigned char*                myQueue;
      shared_memory_object*         shm1;
      mapped_region*                region1;
      void*                         addr1;

      SharedMemoryQueueControlData* myControlData;
      shared_memory_object*         shm2;
      mapped_region*                region2;
      void*                         addr2;
void LogMessage(char* Msg, double count);
};



//---------------------------------------------------------------------------
#endif
