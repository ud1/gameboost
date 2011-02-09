#include "base/Timer.h"

namespace
{

#ifdef _WIN32
	#include <Windows.h>
	
	// Частота
	uint64_t freq;
	
	inline uint64_t Time()
	{
		LARGE_INTEGER s;
		QueryPerformanceCounter(&s);
		return s.QuadPart;
	}
	
	void setupFreq()
	{
		LARGE_INTEGER s;
		QueryPerformanceFrequency(&s);
		freq = s.QuadPart;
	}

#else
	#include <sys/time.h>
	#include <unistd.h>
	
	inline uint64_t Time()
	{
		timeval t;
		gettimeofday(&t, 0);
		return (uint64_t) t.tv_sec*1000000 + t.tv_usec;
	}
	
#define setupFreq() 0
#define freq 1000000

#endif

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
			setupFreq();
			start_time = getTickCount();
		}
		
		void Timer::sleep(unsigned millisecs)
		{
#ifdef _WIN32
			Sleep(millisecs);
#else
			usleep(millisecs*1000);
#endif
		}
		
		Timer::Ticks Timer::getTickCount() const
		{
			return (Ticks) Time();
		}
		
		Timer::TicksFreq Timer::getTimeFreq() const
		{
			return freq;
		}

		// Засекаем текущее время
		void Timer::startTiming()
		{
			start_time = getTickCount();
		}

		// Возвращает прошедшее время
		double Timer::timeElapsed()
		{
			elapsed_time = ((double)( getTickCount() - start_time )/getTimeFreq());
			return elapsed_time;
		}

		//
		// AdvancedTimer
		//

		AdvancedTimer::AdvancedTimer()
		{
			time_acceleration = 1.0;
			the_time = 0.0;
		}

		void AdvancedTimer::resetTime(double t_)
		{
			the_time = t;
			timer.startTiming();
		}
		
		double AdvancedTimer::getTime()
		{
			t = the_time + timer.timeElapsed()*time_acceleration;
			return t;
		}

		void AdvancedTimer::setTimeAccel(double accel)
		{
			the_time = getTime();
			timer.startTiming();
			time_acceleration = accel;
		}

	}
}

