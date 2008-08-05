#ifndef __framework_utils_Mutex_H
#define __framework_utils_Mutex_H
// File:  Mutex.h
// 
// Componentized Combat System Testbed Framework IR&D
// Copyright 2008, Johns Hopkins University / Applied Physics Laboratory (JHU/APL)
// 
// Date of creation: 19 March 2008
//
// Specification for class Mutex
// 
//

#include "boost/thread/mutex.hpp"


namespace framework {
	namespace utils {


/**
 * This class represents a generic Mutex object.
 * Currently it is implemented using boost::mutex.
 * See the class MutexLock to see how to lock the mutex.
 * 
 */
class Mutex {

	public:
	
		/**
		 * Default constructor.  Creates the mutex.
		 */
		Mutex() {}
		
		/**
		 * Default destructor.
		 */
		~Mutex() {}
		
	protected:
	
		/**
		 * Unimplemented copy constructor to prevent object from being copied.
		 */
		Mutex(const Mutex& );
		
		/**
		 * Unimplemented operator= to prevent object from being copied.
		 */
		Mutex& operator=(const Mutex& );
	
	private:
		
		
		boost::mutex mutex;        //< The actual boost mutex.

		/*
		 * make MutexLock a friend of this class so that it (but no one else)
		 * can access the mutex member.
		 */
		friend class MutexLock;
};

} // end of namespace utils
} // end of namespace framework

#endif
