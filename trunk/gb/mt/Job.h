#pragma once

#include "gb/Config.h"

#if GB_ALLOW_BOOST_LIBRARY

#include <gb/base/IRefCountable.h>
#include <gb/base/Atomic.h>
#include <gb/base/Types.h>
#include <gb/mt/ThreadPolicy.h>

#include <vector>

#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

namespace gb
{
	namespace mt
	{
		
		/** \brief Задача
		 *
		 * Представляет собой ссылку на функцию, которую нужно выполнить,
		 * а так же стратегию выбора групп потоков (актуально только для DO_JOB).
		 * Задача для выполнения принимает один агрумент типа Action.
		 * Если аргумент принимает значение CANCEL_JOB, то поток может быть любым.
		 */
		struct JobTask
		{
			/**
			 * Используется для указания типа выполнения
			 */
			enum Action
			{
				DO_JOB, /// Обычное выполнение задачи
				CANCEL_JOB /// Задача была отменена
			};
			
			typedef boost::function<void (Action)> RunFunc;
			RunFunc run; /// Функция для выполнения
			const ThreadPolicy *policy; /// Стратегия выбора потоков, которые могут выполнять данную задачу
			
			JobTask()
			{
				policy = NULL;
			}
			
			JobTask(const JobTask &o)
			{
				run = o.run;
				policy = o.policy;
			}
			
			JobTask &operator = (const JobTask &o)
			{
				run = o.run;
				policy = o.policy;
				return *this;
			}
		};


		/**
		 * \brief Описатель задачи, используется для отслеживания и контроля выполнения задачи.
		 */
		class Job : public base::IRefCountable
		{
		public:
			/**
			 * \brief Статус задачи
			 * 
			 * При создании статус устанавливается в JOB_WAITING.
			 * 
			 * Когда задача начинает выполняться, статус меняется на JOB_RUNNING,
			 * при этом вызывается функция задачи с параметром DO_JOB.
			 * Задача может начать выполнение только, если статус был JOB_WAITING.
			 * 
			 * При отмене задачи, статус меняется на JOB_CANCELING, при этом
			 * вызывается функция задачи с параметром CANCEL_JOB.
			 * Задача может быть отменена только, если статус был JOB_WAITING.
			 * 
			 * После завершения выполнения задачи (когда завершается вызов
			 * функции задачи с параметром DO_JOB), статус переходит в JOB_FINISHED.
			 * 
			 * После отмены задачи (когда завершается вызов
			 * функции задачи с параметром CANCEL_JOB), статус переходит в JOB_CANCELED.
			 */
			enum JobStatus : base::atomic_int_t
			{
				JOB_WAITING,
				JOB_RUNNING,
				JOB_FINISHED,
				JOB_CANCELING,
				JOB_CANCELED
			};

			/** Возвращает текущий статус */
			JobStatus getStatus() const
			{
				return status;
			}

			/** Пытается отменить задачу */
			JobStatus tryCancel();

			/**
			 * Ожидание до тех пор пока задача не перейдет в состояние JOB_FINISHED
			 * или JOB_CANCELED, или не закончится интервал времени millisecs (не гарантируется).
			 * Если задача еще не начала выполнение (т.е. имеет статус JOB_WAITING), и если текущему
			 * потоку стратегией разрешенно выполнять эту задачу, то вместо усыпления текущего потока,
			 * он может попытаться выполнить задачу самостоятельно.
			 */
			JobStatus wait(int millisecs = -1);

			/**
			 * Отмена и ожидание.
			 */
			JobStatus tryCancelAndWait()
			{
				tryCancel();
				return wait();
			}
			
			/**
			 * Возвращает используемую стратегию выбора групп потоков.
			 */
			const ThreadPolicy *getThreadPolicy() const
			{
				return job_task.policy;
			}

		protected:
			Job();
			~Job();
			
			JobStatus doJob(JobTask::Action a);
			void setJobTask(const JobTask &task)
			{
				job_task = task;
			}

			/**
			 * Эта функция может быть переопределена в дочерних классах,
			 * предназначение - перехватить задачу на себя для выполнения
			 * при вызове функции wait()
			 */
			virtual bool getJobOwnership(JobTask::Action)
			{
				return false;
			}

		private:
			JobStatus status;
			JobTask job_task;
			boost::interprocess::interprocess_semaphore wait_sem;

			void doJobImpl(JobTask::Action s);
			
			friend class JobProxy;
		};
		
		class IJobScheduler;
		
		/**
		 * \brief Описатель псевдозадачи.
		 * 
		 * Иногда нужно вернуть описатель типа Job, но мы при этом не хотим или
		 * не можем установить задачу. Для этой цели и существует JobProxy, задачу
		 * можно установить в более позднее время.
		 */
		class JobProxy : public Job
		{
		protected:
			
			JobProxy()
			{
				real_job = NULL;
			}
			
			void setup(IJobScheduler *sch, const JobTask &task);
			bool getJobOwnership(JobTask::Action);
			
		private:
			Job *real_job;
		};

	} // namespace mt
} // namespace gb

#endif // GB_ALLOW_BOOST_LIBRARY
