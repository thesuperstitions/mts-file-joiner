/********************************************************************
	Rhapsody	: 7.1 
	Login		: rosskw1
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Framework::utils::ConsumerThread
//!	Generated Date	: Mon, 14, Apr 2008  
	File Path	: DefaultComponent\DefaultConfig\ConsumerThread.cpp
*********************************************************************/

#include "ConsumerThread.h"

//----------------------------------------------------------------------------
// ConsumerThread.cpp                                                                  
//----------------------------------------------------------------------------

struct MessageStruct
{
  unsigned long MsgNumber;
  unsigned char MsgBody[30];
};


        
ConsumerThread::ConsumerThread(Queue* queue)
{
  myQueue = queue;
  exitFlag = false;
}
        
ConsumerThread::~ConsumerThread() 
{
  exitFlag = true;
  stop();
}

void ConsumerThread::start() 
{
  exitFlag = false;

  Thread::start();	
}

void ConsumerThread::stop() 
{
  exitFlag = true;
  this->Thread::join();

  Thread::stop();	
}
        
void ConsumerThread::threadOperation()
{
  QString s;
  MessageStruct* msg;
  unsigned long msgCount = 0;
  unsigned long prevMsgCount = 0;

  while(exitFlag == false)
  {
    msg = (MessageStruct*)myQueue->getMessage(1, 0);
    if (msg != NULL)
    {
      msgCount = msg->MsgNumber;
      if (msgCount != (prevMsgCount+1))
      {
        myQueue->LogMessage(s.sprintf("ConsumerThread::threadOperation - PROBLEM!!! - MsgNumber=%u, PreviousMsgNumber=%u", msgCount, prevMsgCount), msgCount);
        return;
      }

      if ((msgCount % 1000000) == 0)
        myQueue->LogMessage(s.sprintf("ConsumerThread::threadOperation - MsgNumber=%u", msgCount), msgCount);

      prevMsgCount++;

      delete msg;
    }
  };
}

/*********************************************************************
	ConsumerThread.cpp
*********************************************************************/

