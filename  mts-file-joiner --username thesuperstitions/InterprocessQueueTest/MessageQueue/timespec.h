//---------------------------------------------------------------------------
#ifndef timespecH
#define timespecH

#include <sys/types.h>
#include <time.h>
//---------------------------------------------------------------------------

    
#ifdef WIN32
	#include <Windows.h>
	struct timespec
	{
		time_t tv_sec; //< seconds
		long   tv_nsec; //< nanoseconds
	};
#endif




#endif
 