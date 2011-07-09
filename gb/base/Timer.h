#pragma once
#include <gb/base/Types.h>

namespace gb
{
	namespace base
	{
		
		/**
		 * @ingroup base_group
		 * \brief Класс таймера
		 */
		class Timer
		{
		public:
			typedef uint64_t Ticks, TicksFreq;
			
			Timer();
			/** Возвращает текущее число тиков, реализация зависит от операционной системы */
			Ticks getTickCount() const;
			
			/** Количество тиков в секунду */
			TicksFreq getTimeFreq() const;
			
			/** Функция операционной системы усыпляющая поток на указанное число миллисекунд */
			static void sleep(unsigned millisecs);

			/** сброс времени в 0 */
			void reset();
			
			/** сколько секунд прошло с последнего вызова resetTime() */
			double getTime();

			/**
			 * хранит время возвращенное последним вызовом getTime(). Исключительно для удобства, так как в большинстве случаев
			 * требуется только одна переменная для хранения времени.
			 */
			double t;
			
		protected:
			Ticks start_time;
		};

		/**
		 * @ingroup base_group
		 * \brief Класс таймера с возсожностью ускорения/замедления времени
		 */
		class AcceleratedTimer
		{
		public:
			AcceleratedTimer();
			
			/** сброс времени в 0 */
			void reset(double t = 0.0);
			
			/** сколько секунд с учётом ускорения/замедления прошло с последнего вызова resetTime() */
			double getTime();
			
			/**
			 * Если accel = 1.0, то время идет в нормальном темпе
			 * Чтобы остановить таймер достаточно задать здесь 0.0
			 */
			void setTimeAccel(double accel);
			
			/** Текущее ускорение времени */
			double getTimeAccel() const {return time_acceleration;}

			/**
			 * хранит время возвращенное последним вызовом getTime(). Исключительно для удобства, так как в большинстве случаев
			 * требуется только одна переменная для хранения времени.
			 */
			double t;
			
		private:
			double the_time, time_acceleration;
			Timer timer;
		};
	} // namespace
	
} // namespace

