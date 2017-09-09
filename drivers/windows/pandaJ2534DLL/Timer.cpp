#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
	start = std::chrono::time_point_cast<std::chrono::milliseconds>(clock::now());
}

// gets the time elapsed from construction.
long /*milliseconds*/ Timer::getTimePassed(){
	// get the new time
	auto end = clock::now();

	// return the difference of the times
	return (end - start).count();
}