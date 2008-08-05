/*********************************************************************
	Login		: rosskw1
	Model Element	: ConsumerThread
  Generated Date	: Mon, 21, Apr 2008  
	File Path	: ConsumerThread.h
*********************************************************************/


#ifndef ConsumerThread_H 

#define ConsumerThread_H 

#include "Thread.h"
#include "Queue.h"

//----------------------------------------------------------------------------
// ConsumerThread.h                                                                  
//----------------------------------------------------------------------------


#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif

//## class ConsumerThread 
class ConsumerThread  : public Thread
{
  ////    Constructors and destructors    ////
  public :       
    Queue* myQueue;

    //## auto_generated 
    ConsumerThread(Queue* queue);
            
    //## auto_generated 
    ~ConsumerThread();

    virtual void start();
  	virtual void stop();

	  virtual void threadOperation();

    void LogMessage(char* Msg, double count);

  protected:
    bool exitFlag;
};


#endif  
/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\ConsumerThread.h
*********************************************************************/

