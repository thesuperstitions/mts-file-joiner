//---------------------------------------------------------------------------
#ifndef QueueH
#define QueueH

//---------------------------------------------------------------------------

#include <vector>
#include <iterator>
// link itsMessage 
//#include "FederateMessage.h"
// class FederateIO_HandlerOutputThread 
#include "Thread.h"
#include "boost/thread/mutex.hpp"

        //## class Queue
        class Queue : public Thread
        {
          ////    Constructors and destructors    ////
          public :
            //## operation Queue()
            virtual ~Queue();

          ////    Operations    ////
          public :
            //## operation addMessage(FederateMessage*)
            virtual void addMessage(void* message);

            //## operation threadOperation()
            virtual void threadOperation();


          ////    Additional operations    ////
          public :
            //## auto_generated
            std::vector<void*>::const_iterator getItsMessage() const;

            //## auto_generated
            std::vector<void*>::const_iterator getItsMessageEnd() const;

            //## auto_generated
            void addItsMessage(void* p_Message);

            //## auto_generated
            void removeItsMessage(void* p_Message);

            //## auto_generated
            void clearItsMessage();

          protected :

            //## auto_generated
            void cleanUpRelations();


          ////    Attributes    ////
          protected :
            boost::mutex myMutex;		//## attribute myMutex

          ////    Relations and components    ////
          protected :
            std::vector<void*> itsMessage;		//## link itsMessage
        };








//---------------------------------------------------------------------------
#endif
