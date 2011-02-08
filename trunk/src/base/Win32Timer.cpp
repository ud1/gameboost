#ifdef _WIN32

#include <windows.h>
#include "Timer.h"
#include <assert.h>

// Частота
uint64_t freq;

inline uint64_t Time()
{
	LARGE_INTEGER s;
	QueryPerformanceCounter(&s);
	return s.QuadPart;
}

//
// Timer
//

Timer::Timer()
{
	LARGE_INTEGER s;
	QueryPerformanceFrequency(&s);
	freq = s.QuadPart;
	start_time = Time();
	global_start_time = start_time;
}

Timer::~Timer() {}

void Timer::startTiming()
{
	start_time = Time();
}

double Timer::timeElapsed()
{
	elapsed_time = ((double)( Time() - start_time )/freq);
	return elapsed_time;
}

double Timer::globalTime()
{
	uint64_t temp = global_start_time;
	global_start_time = Time();
	globalTime += ((double)( global_start_time - temp )/freq);
	return global_time;
}

void Timer::resetGlobalTime(double time)
{
	global_start_time = Time();
	global_time = time;
}

//
// AdvancedTimer
//

AdvancedTimer::AdvancedTimer()
{
	time_acceleration = 1.0;
}

double AdvancedTimer::timeElapsed()
{
	elapsed_time=((double)( Time() - start_time)/freq )*time_acceleration;
	return elapsed_time;
}

double AdvancedTimer::globalTime()
{
	uint64_t temp = global_start_time;
	global_start_time = Time();
	global_time += ((double)( global_start_time - temp )/freq)*time_acceleration;
	return global_time;
}

void AdvancedTimer::setTimeAcceleration(double accel)
{
	globalTime();
	time_acceleration = accel;
}

#endif
