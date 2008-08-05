#ifndef __framework_utils__Thread__H
#define __framework_utils__Thread__H
#include "boost/thread.hpp"

// File:  Thread.h
// 
// Componentized Combat System Testbed Framework IR&D
// Copyright 2008, Johns Hopkins University / Applied Physics Laboratory (JHU/APL)
// 
// Date of creation: 19 March 2008
//
// Specification for class Thread
// 
//


/**
 * Generic wrapper for a thread class.  This is an abstract class;
 * clients should subclass and implement threadOperation, which contains
 * the code executed in the new thread.
 */
class Thread {

public:
	Thread();
	virtual ~Thread()=0;
	
	/**
	 * Starts a new thread and calls the pure virtual member function threadOperation
	 * as the thread entry point.
	 * Currently this creates a new boost::thread object.
	 */
	void start();
	
	/**
	 * Stops the thread.  Virtual so that subclasses can add behavior.
	 * Current implementation deletes the boost thread object.
	 */
	virtual void stop();
	
	/**
	 * Wait for this thread to finish running.  Note:  if thread is in infinite loop
	 * you may be waiting quite a long time.
	 */
	void join();
	
protected:

	/**
	 * Unimplemented copy constructor to prevent this object from being copied.
	 */
	Thread(const Thread& );
	
	/**
	 * Unimplemented copy constructor to prevent this object from being copied.
	 */
	Thread& operator=(const Thread&);  
	
	/**
	 * This the actual operation that is started when a thread kicks off.
	 * It is started/called as soon as "start" is called.
	 */
	virtual void threadOperation()=0;
	

	/**
	 * Yields to allow other threads to run.
	 */
	void yield();
	
	
	
private:

	/**
	 * Returns a refernce to the boost::thread object.
	 *
	 * we could move this to protected if we ever think of a need
	 * for a subclass to have direct access to the thread.
	 */
	boost::thread& getThread() {return *theThread;}

	
	boost::thread* theThread;    //< Pointer to the actual thread object.
	
	 /**
	  * The static operation used to kick off the thread.  Static function
	  * is used because of the way boost handles function pointers,
	  * but there might be way to make this a member and still work.
	  */
	static void threadOper(Thread* thisObject);

};


#endif
