#pragma once

#include "gb/Config.h"

#if GB_ALLOW_BOOST_LIBRARY

#include <gb/mt/ThreadPolicy.h>
#include <gb/mt/Job.h>

namespace gb
{
	namespace mt
	{

		/**
		 * \brief Шедулер
		 * 
		 * Предназначен для выполнения задач в определенный момент времени.
		 * Для выполнения задач используется пулы потоков, по одному на каждую
		 * группу потоков.
		 */
		class IJobScheduler : public base::IRefCountable
		{
		public:
			/**
			 * Добавляет задачу в очередь в пул потоков соответсвующий
			 * предпочтительной для данной задаче группы (определяется стратегией выбора
			 * группы потоков задачи). Задача должна начать выполнения через millisecs
			 * миллисекунд после добавления.
			 * @return Описатель задачи
			 */
			virtual Job *scheduleJob(int millisecs, const JobTask &f) = 0;

			/**
			 * Добавляет задачу в очередь, при этом описатель задачи не возвращается.
			 */
			void scheduleJob0(int millisecs, const JobTask &f)
			{
				scheduleJob(millisecs, f)->release();
			}

			/**
			 * Возвращает true до тех пор, пока не вызовется stop
			 */
			virtual bool isRunning() const = 0;

			/**
			 * Стартует указанное число потоков для указанной группы.
			 * Все потоки автоматически регистрируются в ThreadMapping
			 * Может вызываться только один раз для каждой группы.
			 */
			virtual void startThreads(size_t threads_number, ThreadGroup group) = 0;
			
			/**
			 * Отмена всех задач, остановка потоков.
			 */
			virtual void stop() = 0;

			/**
			 * Обрабатывает одну задачу из указанной группы, если такая существует.
			 * Обычно Render-поток не управляется шедулером, и данная функция используется
			 * им для выполнения своих задач.
			 * @return true если была задача для выполнения.
			 */
			virtual bool runOnce(ThreadGroup group) = 0;
		};

		IJobScheduler *createJobScheduler();

		/**
		 * \brief Вспомогательный клас для выполнения задач через равные промежутки времени
		 * 
		 * Отмена выполнения задачи происходит при уничтожении объекта данного класса
		 */
		class Loop
		{
		public:
			Loop(IJobScheduler *sched, int period_millisecs, const JobTask &f);
			~Loop();
			
			void changePeriod(int millisecs)
			{
				period = millisecs;
			}
		
		private:
			IJobScheduler *sched;
			Job *job;
			JobTask task;
			JobTask::RunFunc func;
			boost::mutex job_mutex;
			int period;
			void doJob(JobTask::Action a);
		};

	} // namespace mt
} // namespace gb

#endif // GB_ALLOW_BOOST_LIBRARY
