#include "pch.h"

#ifdef __linux

#include "base/Timer.h"
#include <assert.h>
#include <sys/time.h>

namespace
{
	uint64_t Time()
	{
		timeval t;
		gettimeofday(&t, nullptr);
		return (uint64_t) t.tv_sec*1000000 + t.tv_usec;
	}
}

namespace gb
{
	namespace base
	{
		
		//
		// Timer
		//

		Timer::Timer()
		{
			start_time = Time();
			global_start_time = start_time;
		}

		// Засекаем текущее время
		void Timer::startTiming()
		{
			start_time = Time();
		}

		// Возвращает прошедшее время
		double Timer::timeElapsed()
		{
			elapsed_time = ((double)( Time() - start_time )/1000000.0);
			return elapsed_time;
		}

		double Timer::globalTime()
		{
			uint64_t temp = global_start_time;
			global_start_time = Time();
			global_time += ((double)( global_start_time - temp )/1000000.0);
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
			elapsed_time=((double)( Time() - start_time)/1000000.0 )*time_acceleration;
			return elapsed_time;
		}

		double AdvancedTimer::globalTime()
		{
			uint64_t temp = global_start_time;
			global_start_time = Time();
			global_time += ((double)( global_start_time - temp )/1000000.0)*time_acceleration;
			return global_time;
		}

		void AdvancedTimer::setTimeAcceleration(double accel)
		{
			globalTime();
			time_acceleration = accel;
		}

	}
}

#endif // __linux
