#pragma once
#include <gb/base/Types.h>

namespace gb
{
	namespace base
	{
		
		// Класс таймера
		class Timer
		{
		public:
			typedef uint64_t Ticks, TicksFreq;
			
			Timer();
			Ticks getTickCount() const;
			TicksFreq getTimeFreq() const;
			static void sleep(unsigned millisecs);

			// сброс времени в 0
			void startTiming();
			
			// сколько секунд прошло с последнего вызова startTiming()
			double timeElapsed();

			// хранит время возвращенное последним вызовом timeElapsed()
			double elapsed_time;
			
		protected:
			Ticks start_time;
		};

		// Позволяет задавать ускорение/замедление времени
		class AdvancedTimer
		{
		public:
			AdvancedTimer();
			
			void resetTime(double t = 0.0);
			double getTime();
			
			// Если accel = 1.0, то время идет в нормальном темпе
			void setTimeAccel(double accel);
			double getTimeAccel() const {return time_acceleration;}

			// хранит время возвращенное последним вызовом getTime()
			double t;
			
		private:
			double the_time, time_acceleration;
			Timer timer;
		};
	} // namespace
	
} // namespace

