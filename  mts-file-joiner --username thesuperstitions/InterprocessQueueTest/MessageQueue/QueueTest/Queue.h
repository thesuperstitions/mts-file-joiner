//---------------------------------------------------------------------------
#ifndef QueueH
#define QueueH

//---------------------------------------------------------------------------

#include <QString>
#include <QObject>
#include "Thread.h"
#include "boost/thread/mutex.hpp"
#include <boost/circular_buffer.hpp>


#include <ctime>

#define MAX_QUEUE_SIZE 262144

        //## class Queue
  class Queue : public QObject
        {
          Q_OBJECT
  
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

            void LogMessage(QString Msg, double count);

          protected :
            void* Queue::CheckForItemsInQueue(void);

          ////    Attributes    ////
          protected :

            boost::timed_mutex        myMutex;		//## attribute myMutex
            boost::mutex              myDataAccessMutex;
            bool                      exitFlag;

          ////    Relations and components    ////
          protected :
            boost::circular_buffer<void*>* myQueue;


          public :
            signals:
              void OnLogText(QString);
        };








//---------------------------------------------------------------------------
#endif
