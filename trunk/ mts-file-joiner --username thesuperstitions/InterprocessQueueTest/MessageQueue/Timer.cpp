/********************************************************************
	Rhapsody	: 7.1 
	Login		: rosskw1
	Component	: DefaultComponent 
	Configuration 	: DefaultConfig
	Model Element	: Framework::utils::Timer
//!	Generated Date	: Tue, 8, Apr 2008  
	File Path	: DefaultComponent\DefaultConfig\Timer.cpp
*********************************************************************/

#include "Timer.h"
// dependency Sleep 
#include "Sleep.h"

//----------------------------------------------------------------------------
// Timer.cpp                                                                  
//----------------------------------------------------------------------------

//## package Framework::utils 

//## class Timer 

namespace Framework {
    namespace utils {
        
        
        Timer::Timer(int seconds, unsigned long nanoseconds, bool startImmediately, bool periodic) : isPeriodic(periodic), timerActive(startImmediately), seconds(seconds), nanoseconds(nanoseconds) {
            //#[ operation Timer(int,unsigned long,bool,bool) 
            //#]
        }
        
        Timer::~Timer() {
        }
        
        void Timer::startOneShotTimer(int seconds, unsigned long nanoseconds) {
            //#[ operation startOneShotTimer(int,unsigned long) 
            
            setSeconds(seconds);
            setNanoseconds(nanoseconds);
            
            setIsPeriodic(false);
            setTimerActive(true);
            
            Thread::start();
            
            //#]
        }
        
        void Timer::startPeriodicTimer(int seconds, unsigned long nanoseconds) {
            //#[ operation startPeriodicTimer(int,unsigned long) 
            
            setSeconds(seconds);
            setNanoseconds(nanoseconds);
            setIsPeriodic(true);
            setTimerActive(true);  
            
            Thread::start();
            
            //#]
        }
        
        void Timer::stopPeriodicTimer() {
            //#[ operation stopPeriodicTimer() 
            
            
            //            Thread::stop();
            setTimerActive(false);  
            
            //#]
        }
        
        void Timer::threadOperation() {
            //#[ operation threadOperation() 
            if (timerActive == true)
            {
              // Sleep for the timer's interval.
              Framework::utils::Sleep::sleep(seconds, nanoseconds);
                
              // Let the user know that the timer has expired.
              if (timerActive == true) //  While sleeping, the timer could have been stopped.
                this->onTimerExpired();
            } 
            
            //#]
        }
        
        bool Timer::getIsPeriodic() const {
            return isPeriodic;
        }
        
        void Timer::setIsPeriodic(bool p_isPeriodic) {
            isPeriodic = p_isPeriodic;
        }
        
        unsigned long Timer::getNanoseconds() const {
            return nanoseconds;
        }
        
        void Timer::setNanoseconds(unsigned long p_nanoseconds) {
            nanoseconds = p_nanoseconds;
        }
        
        int Timer::getSeconds() const {
            return seconds;
        }
        
        void Timer::setSeconds(int p_seconds) {
            seconds = p_seconds;
        }
        
        bool Timer::getTimerActive() const {
            return timerActive;
        }
        
        void Timer::setTimerActive(bool p_timerActive) {
            timerActive = p_timerActive;
        }
        
    }
}


/*********************************************************************
	File Path	: DefaultComponent\DefaultConfig\Timer.cpp
*********************************************************************/

