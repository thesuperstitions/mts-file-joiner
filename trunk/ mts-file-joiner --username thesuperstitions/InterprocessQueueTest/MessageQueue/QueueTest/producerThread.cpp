/********************************************************************
	Rhapsody	: 7.1 
	Login		: rosskw1
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Framework::utils::ProducerThread
//!	Generated Date	: Mon, 14, Apr 2008  
	File Path	: DefaultComponent\DefaultConfig\ProducerThread.cpp
*********************************************************************/

#include "ProducerThread.h"
#include "Sleep.h"

static unsigned long msgCount = 1;

//----------------------------------------------------------------------------
// ProducerThread.cpp                                                                  
//----------------------------------------------------------------------------

//## class ProducerThread 

struct MessageStruct
{
  unsigned long MsgNumber;
  unsigned char MsgBody[30];
};

ProducerThread::ProducerThread(Queue* queue) 
{
  myQueue = queue;
  exitFlag = false;
}
        
ProducerThread::~ProducerThread() 
{
  exitFlag = true;
  stop();
}

void ProducerThread::start() 
{
  exitFlag = false;
  this->Thread::join();

  Thread::start();	
}

void ProducerThread::stop() 
{
  exitFlag = true;

  Thread::stop();	
}

        
void ProducerThread::threadOperation()
{
  MessageStruct* msg;

  while(exitFlag == false)
  {
    msg = new MessageStruct;
    msg->MsgNumber = msgCount++;

    while (myQueue->addMessage((void*)msg) == false)
    {
      yield();
    };
  };
}

/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\ProducerThread.cpp
*********************************************************************/

