/********************************************************************
	Login		: rosskw1
	Model Element	: ProducerThread
	Generated Date	: Mon, 21, Apr 2008  
	File Path	: ProducerThread.cpp

  Description: This class is based upon the "Thread" class.  It
  generates messages that get queued for consumption by the 
  "consumerThread".

*********************************************************************/

#include "ProducerThread.h"
//#include "Sleep.h"

#include "Sleep.h"

static long msgCount = 0;

#define MAX_MSG_COUNT 1048576

//----------------------------------------------------------------------------
// ProducerThread.cpp                                                                  
//----------------------------------------------------------------------------

//## class ProducerThread 

struct MessageStruct
{
  long          MsgNumber;
  unsigned char MsgBody[96];
};

MessageStruct msg[MAX_MSG_COUNT];

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
  MessageStruct* msgPtr;

  //framework::utils::Sleep::sleep(10, 0);

  while(exitFlag == false)
  {
    msgPtr = &(msg[msgCount % MAX_MSG_COUNT]);
    msgPtr->MsgNumber = msgCount++;

    while (myQueue->addMessage((void*)msgPtr) == false)
    {
      yield();
    };
  };
}

/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\ProducerThread.cpp
*********************************************************************/

