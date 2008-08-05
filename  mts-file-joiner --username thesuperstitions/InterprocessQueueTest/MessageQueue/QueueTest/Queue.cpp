//---------------------------------------------------------------------------

#include "Queue.h"
#include "boost/thread.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/thread/xtime.hpp>
#include <stdio.h>
#include <time.h>
#include <sys\timeb.h>
#include "Sleep.h"

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

static struct timeb previousTime;
unsigned long int   previousCount = 0;

struct MessageStruct
{
  unsigned long MsgNumber;
  unsigned char MsgBody[30];
};

        Queue::Queue(unsigned long int numberOfItems) 
        {
          exitFlag = false;
          myMutex.unlock();
          myQueue = new boost::circular_buffer<void*>(numberOfItems);
previousTime.time = 0;
previousTime.millitm = 0;
        }

        
        Queue::~Queue() 
        {
            exitFlag = true;
            myMutex.unlock();  // Wake "getMessage".
            delete myQueue;
        }
        
        bool Queue::addMessage(void* message)
        {
          QString s;
            
          if (exitFlag == true)
            return(false);
  
          try
          {
            { // Start of Scope.
              // Get the mutex just long enough to add the message to the queue.
              boost::mutex::scoped_lock myDataAccessLock(myDataAccessMutex); //This lock protects the queue itself.
     
              if (myQueue->full() != true)
              {
                //myQueue.push_back(message);
                myQueue->push_back(message);

                myMutex.unlock();  // Wake "getMessage".

                return(true); // Message was queued
              }  // if (myQueue->full() != true)
              else
                return (false); // Message was NOT queued.
            } // End of Scope.
          }
          catch (...)
          {
            LogMessage(s.sprintf("Queue::addMessage -EXCEPTION"), 0);
          };
          return(false);
        }

        void* Queue::CheckForItemsInQueue(void)
        { // Start of scope for the "scoped_lock" mutex.
          void* m_Ptr = NULL;

          boost::mutex::scoped_lock myDataAccessLock(myDataAccessMutex); //This lock protects the queue itself.

          // Check to see if there's a Message in the list   
          if (myQueue->empty() != true)
          {      
            // Get the first message in the list.                                  
            m_Ptr = myQueue->front();  

            // Remove the message from the list now so that the mutex can be unlocked prior to sending.  
            myQueue->pop_front();   // Remove the just-sent Message from the list.
          }

          return(m_Ptr);
        } // End of Scope for the "scoped_lock" mutex.  This unlocks the timed mutex.
        

        void* Queue::getMessage(unsigned int timeoutSecs, unsigned long int timeoutMicroSecs)
        {
          QString s;

          void* m_Ptr = NULL;

          // Just in case this function gets invoked during shutdown.
          if (exitFlag == true)
            return(NULL);

          try
          {
            // Check to see if there's a message already waiting on the Queue.  If so, we just return it.
            if ( (m_Ptr = CheckForItemsInQueue()) != NULL)
              return(m_Ptr);

            // There were no items in the Queue, so now we have to wait for either the queue to be unlocked or the timeout occurs.

            // Calculate the duration of the timeout.
            boost::posix_time::time_duration td = boost::posix_time::seconds(timeoutSecs) + boost::posix_time::microseconds(timeoutMicroSecs); //

            // Block on the mutex until either a message is received in the queue (addMessage function unlocks the mutex after dropping a message
            // in the queue), or the timer expires.
            if (myMutex.timed_lock(boost::get_system_time() + td) == true)
            {
              return( CheckForItemsInQueue() );
            }
            else
            {
              // mutex timed out
              return(m_Ptr);
            }
          }
          catch(...)
          {
            //LogMessage(s.sprintf("Queue::getMessage - EXCEPTION"));
          };

          return(m_Ptr);
        }


        void Queue::LogMessage(QString Msg, double count)
        {
          QString       s;
          struct timeb  t;
          int           Hours, Mins, Secs;
          unsigned long milliSecs, previousMilliSecs;
          double        deltaTime, deltaSecs, iterationsPerSecond;

          ftime(&t);
          milliSecs = (t.time * 1000) + t.millitm;
          Secs = t.time % 86400; // 86400000 = Milli-Seconds/24 hours
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
            previousMilliSecs = (previousTime.time * 1000) + previousTime.millitm;
            deltaTime = (milliSecs - previousMilliSecs) / 1000.0;
  
            iterationsPerSecond = (count-previousCount) / deltaTime;
          }          

          previousTime = t;
          previousCount = count;

          //TS = gmtime( &tt );
          s.sprintf("%02u:%02u:%02u.%03u - Delta Time = %12.3f Secs, Iterations/Sec = %12.3f, , Current # Items In Queue = %u - ", 
            Hours, Mins, Secs, t.millitm, deltaTime, iterationsPerSecond, this->myQueue->size());
          s += Msg + " : ";
          this->OnLogText(s);
        }

