//---------------------------------------------------------------------------
#ifndef QueueH
#define QueueH

//---------------------------------------------------------------------------

//#include <QString>
//#include <QObject>
//#include "Thread.h"
#include "boost/thread/mutex.hpp"
#include <boost/circular_buffer.hpp>


#include <ctime>

#define MAX_QUEUE_SIZE 262144

        //## class Queue
class Queue
{
  ////    Constructors and destructors    ////
  public :
    Queue(unsigned long int numberOfItems = MAX_QUEUE_SIZE);

    //## operation Queue()
    virtual ~Queue();

    ////    Operations    ////
    public :
      //## operation addMessage(FederateMessage*)
      virtual bool addMessage(void* message);
      virtual void* getMessage(unsigned int timeoutSecs, unsigned long int timeoutMicroSecs);

    protected :
      void* Queue::CheckForItemsInQueue(void);

    ////    Attributes    ////
    protected :
      boost::timed_mutex        myMutex;		//## attribute myMutex
      boost::mutex              myDataAccessMutex;
      bool                      exitFlag;

    ////    Relations and components    ////
    public :
      boost::circular_buffer<void*>* myQueue;
 };








//---------------------------------------------------------------------------
#endif
