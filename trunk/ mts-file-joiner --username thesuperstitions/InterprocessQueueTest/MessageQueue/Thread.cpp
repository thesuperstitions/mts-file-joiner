// File:  Thread.cpp
// 
// Componentized Combat System Testbed Framework IR&D
// Copyright 2008, Johns Hopkins University / Applied Physics Laboratory (JHU/APL)
// 
// Date of creation: 19 March 2008
//
// Implementation for class Thread
// 
//


#include "framework/utils/Thread.h"

#include "boost/bind.hpp"
#include "boost/function.hpp"
//#include "boost/thread.hpp"

#include "framework/utils/Exception.h"


#include <iostream>

namespace framework {
	namespace utils {

Thread::Thread() 
	: theThread(0) {}
	
	
Thread::~Thread() 
{

	stop();

}

void Thread::start() 
{

	if (this->theThread) {
	
		std::cout<<"Tried to start a new thread when one is already running"
		<<std::endl;
		
		throw Exception(
		"framework::utils::Thread: Tried to start a new thread when one is already running",
		__FILE__,__LINE__);

	
	}

   //boost::function0<void> fun(boost::bind(&(TestThread::memberThread),*this));
   boost::function0<void> fun( boost::bind( &(Thread::threadOper), this )  );
   this->theThread = new boost::thread(fun);

}

void Thread::stop() 
{

	delete theThread;
	theThread=0;
	
}

void Thread::join()
{
	if (theThread)
	{
		theThread->join();
	}
}



void Thread::threadOper(Thread* thisObject) 
{

	thisObject->threadOperation();
}



void Thread::yield() 
{

	theThread->yield();
	
}

} // end of namespace framework
} // end of namespace utils
