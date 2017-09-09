#pragma once
#include <chrono>

//Copied from https://stackoverflow.com/a/31488113

class Timer
{
	using clock = std::chrono::system_clock;
	using time_point_type = std::chrono::time_point < clock, std::chrono::milliseconds >;
public:
	Timer();

	// gets the time elapsed from construction.
	long /*milliseconds*/ getTimePassed();

private:
	time_point_type start;
};