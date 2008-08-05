#ifndef __framework_utils_Sleep__H
#define __framework_utils_Sleep__H

// File:  Sleep.h
// 
// Componentized Combat System Testbed Framework IR&D
// Copyright 2008, Johns Hopkins University / Applied Physics Laboratory (JHU/APL)
// 
// Date of creation: 28 March 2008
//
// Provides platform-independent sleep function.


#include <ctime>

#ifdef WIN32
	#include <Windows.h>
	struct timespec
	{
		time_t tv_sec; //< seconds
		long   tv_nsec; //< nanoseconds
	};
#endif



#include "framework/utils/Exception.h"

namespace framework {
	namespace utils {
	
	
class Sleep {

  public:

	static inline void sleep(const struct timespec& request, const bool interposition_safe=false)
	{
		#ifdef UNIX
		
			
			
			if (!interposition_safe)
			{
				struct timespec remaining;
				if (nanosleep(&request, &remaining) == -1)
				{
					throw framework::utils::Exception("sleep failed");
				}
			}
			else
			{
			
				const static struct timespec INTERPOSITION_SAFE_SLEEP  = {-1,-1};
				if (nanosleep(&request, const_cast<struct timespec*>(&INTERPOSITION_SAFE_SLEEP))==-1)
				{
					throw framework::utils::Exception("sleep failed");
				}
			
			}
		#elif defined WIN32
		
			// TODO use a higher-res sleep at some point.
			time_t numberMilliseconds = request.tv_sec*MILLISECONDS_PER_SECOND;
			
			// in this case the truncation shouldn't matter because windows
			// timer using Sleep is not that precise.
			numberMilliseconds += (request.tv_nsec / NANOSECONDS_PER_MILLISECOND);
			
			::Sleep(static_cast<DWORD>(numberMilliseconds));
			
		
		#endif
	}
	
	static inline void sleep(const time_t seconds, const long nanoseconds, const bool interposition_safe=false)
	{
		struct timespec request = { seconds, nanoseconds };
		sleep(request, interposition_safe);
	}

	
	const static int MILLISECONDS_PER_SECOND=1000;
	const static int NANOSECONDS_PER_MILLISECOND=1000*1000;

	
	//static int 

}; // end of class Sleep	
	
} // end of namespace utils
} // end of namespace framework

#endif
