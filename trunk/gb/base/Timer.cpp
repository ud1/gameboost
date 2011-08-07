

#include <gb/base/Timer.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

namespace
{

#ifdef _WIN32
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
		void Timer::reset()
		{
			start_time = getTickCount();
		}

		// Возвращает прошедшее время
		double Timer::getTime()
		{
			t = ((double)( getTickCount() - start_time )/getTimeFreq());
			return t;
		}

		//
		// AcceleratedTimer
		//

		AcceleratedTimer::AcceleratedTimer()
		{
			time_acceleration = 1.0;
			the_time = 0.0;
		}

		void AcceleratedTimer::reset(double t_)
		{
			the_time = t;
			timer.reset();
		}
		
		double AcceleratedTimer::getTime()
		{
			t = the_time + timer.getTime()*time_acceleration;
			return t;
		}

		void AcceleratedTimer::setTimeAccel(double accel)
		{
			the_time = getTime();
			timer.reset();
			time_acceleration = accel;
		}

	}
}

