/********************************************************************
	Login		: rosskw1
	Model Element	: ConsumerThread
  Generated Date	: Mon, 21, Apr 2008  

  Description: This class is based upon the "Thread" class.  It reads
  messages from a Queue, one at a time, and checks to make sure that
  the messages are received in sequence.
*********************************************************************/

#include "ConsumerThread.h"
#include <stdio.h>
#include <time.h>
#include <sys\timeb.h>

#include "Sleep.h"

//----------------------------------------------------------------------------
// ConsumerThread.cpp                                                                  
//----------------------------------------------------------------------------

struct MessageStruct
{
  long MsgNumber;
  unsigned char MsgBody[96];
};


static struct timeb previousTime;

        
ConsumerThread::ConsumerThread(Queue* queue)
{
  myQueue = queue;
  exitFlag = false;
  previousTime.time = 0;
  previousTime.millitm = 0;
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
  char           s[500];
  MessageStruct* msg;
  long  msgCount = 0;
  long  prevMsgCount = -1;

  //framework::utils::Sleep::sleep(0, 100);

  while(exitFlag == false)
  {
    msg = (MessageStruct*)myQueue->getMessage(1, 0);
    if (msg != NULL)
    {
      msgCount = msg->MsgNumber;
      if (msgCount != (prevMsgCount+1))
      {
        sprintf(s, "PROBLEM!!! - MsgNumber=%u, PreviousMsgNumber=%u\n", msgCount, prevMsgCount);
        this->LogMessage(s, msgCount);
        return;
      }

      if ((msgCount % 1000000) == 0)
      {
        sprintf(s, "Msg#=%u\n", msgCount);
        LogMessage(s, msgCount);
      }

      prevMsgCount++;

      //delete msg;
    }
  };
}



        void ConsumerThread::LogMessage(char* Msg, double count)
        {
          struct timeb  t;
          int           Hours, Mins, Secs;
          double        deltaTime, iterationsPerSecond, secs, milliSecs;

          ftime(&t);
          Secs = t.time % 86400; // 86400 = Seconds/24 hours
          Hours = Secs / 3600;
          Secs -= Hours * 3600;
          Mins = Secs / 60;
          Secs -= Mins * 60;

          if (previousTime.time == 0)
          {
            previousTime = t;
            deltaTime = 0.0;
            iterationsPerSecond = 0.0;
          }
          else
          {
            secs = (t.time - previousTime.time);
            secs *= 1000.0;
            milliSecs = (t.millitm - previousTime.millitm);
            secs += milliSecs;
            deltaTime = secs / 1000.0;
            iterationsPerSecond = count / deltaTime;
          }
  
          //TS = gmtime( &tt );
          printf("%02u:%02u:%02u.%03u-DT=%7.3f S, Iter/Sec=%10.3f, QSize=%u--%s", Hours, Mins, Secs, t.millitm, deltaTime, iterationsPerSecond, this->myQueue->myQueue->size(), Msg);
        }
/*********************************************************************
	ConsumerThread.cpp
*********************************************************************/

