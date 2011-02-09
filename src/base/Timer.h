#pragma once
#include "Types.h"

namespace gb
{
	namespace base
	{
		
		// Класс таймера
		class Timer
		{
		public:
			
			Timer();
			virtual ~Timer();
			
			// сброс времени в 0
			void startTiming();
			
			// сколько секунд прошло с последнего вызова startTiming()
			virtual double timeElapsed();
			
			// сколько секунд прошло с момента создания таймера,
			// может быть переустановлено функцией resetGlobalTime()
			virtual double globalTime();
			
			// переустановка глобального времени
			virtual void resetGlobalTime(double time = 0.0);

			// хранит время возвращенное последним вызовом timeElapsed()
			double elapsed_time;
			
		protected:
			// Для хранения времени
			uint64_t start_time;
			uint64_t global_start_time;
			double global_time;
		};

		// Позволяет задавать ускорение/замедление времени
		class AdvancedTimer: public Timer
		{
		public:
			AdvancedTimer();
			virtual ~AdvancedTimer() {}

			double timeElapsed();
			double globalTime();
			
			// Если accel = 1.0, то время идет в нормальном темпе
			void setTimeAcceleration(double accel);
			double getTimeAcceleration() {return time_acceleration;}

		private:
			double time_acceleration;
		};
		
		// Таймер используется для расчета количества кадров в секунду
		class FPSTimer: public AdvancedTimer 
		{
			FPSTimer();

			// завершение цикла измерения времени кадра
			float finishTiming();
			
			// получить время кадра в секундах
			float getDt() const;
			
			// получить сглаженное время кадра в секундах
			float getAverageDt() const;
			
			// получить количество кадров в секунду, расчитаное исходя из 
			// длительности одного кадра
			float getFPS() const;
			
			// получить реальное количество кадров в секунду
			float getAverageFPS() const;
			
		private:
			int frames;
			double time;
			float dt;
			float adt;
			float fps;
			float afps;
		};
		
	} // namespace
	
} // namespace

