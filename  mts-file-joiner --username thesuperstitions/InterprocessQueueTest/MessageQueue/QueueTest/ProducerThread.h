/*********************************************************************
	Rhapsody	: 7.1 
	Login		: rosskw1
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Framework::utils::ProducerThread
//!	Generated Date	: Mon, 14, Apr 2008  
	File Path	: DefaultComponent\DefaultConfig\ProducerThread.h
*********************************************************************/


#ifndef ProducerThread_H 

#define ProducerThread_H 

#include "Thread.h"
#include "Queue.h"

//----------------------------------------------------------------------------
// ProducerThread.h                                                                  
//----------------------------------------------------------------------------

//## package Framework::utils 

#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif

        //## class ProducerThread 
class ProducerThread  : public Thread
{             
  ////    Constructors and destructors    ////
  public :
    Queue* myQueue;
            
    //## auto_generated 
    ProducerThread(Queue* queue);
            
    //## auto_generated 
    ~ProducerThread();

	  virtual void threadOperation();

    virtual void start();
  	virtual void stop();

  protected:
    bool exitFlag;
};


#endif  
/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\ProducerThread.h
*********************************************************************/

