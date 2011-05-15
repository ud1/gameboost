#pragma once

#include <boost/thread/mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/intrusive/list.hpp>

#include <set>

#include <gb/base/IRefCountable.h>
#include <gb/base/Atomic.h>
#include <gb/mt/Job.h>
#include <gb/base/nullptr.h>
#include <gb/base/Timer.h>

namespace gb
{
	namespace mt
	{
	
		/**
		 * \brief Ресурс
		 * 
		 * Под ресурсом понимается любой объект, который не может быть использован сразу же
		 * после создания, а требует некоторого времени на подготовку (например на загрузку с диска).
		 * Является центральным элементом в системе асинхронной загрузки ресурсов.
		 */
		class Resource : public base::IRefCountable
		{
		public:
			/**
			 * Статус ресурса. Сразу же после создания ресурс получает статус RESOURCE_PREPARING.
			 * После успешной или неуспешной подготовки статус меняется на RESOURCE_PREPARATION_FAILED
			 * или RESOURCE_OK соответсвенно.
			 */
			enum ResourceStatus : base::atomic_int_t
			{
				RESOURCE_PREPARING,
				RESOURCE_PREPARATION_FAILED,
				RESOURCE_OK
			};

			/**
			 * Возвращает текущий статус ресурса
			 */
			ResourceStatus getStatus()
			{
				return status;
			}

			/**
			 * Ожидание, пока статус не изменится с RESOURCE_PREPARING на любой другой.
			 */
			ResourceStatus wait(int millisecs = -1);
			
			/**
			 * Колбек, который должен будет быть вызван после того, как подготовка ресурса завершится.
			 * При этом вызов функции происходит с параметром DO_JOB.
			 * Если ресурс уничтожается, так и не закончив подготовку, происходит вызов
			 * с параметром CANCEL_JOB.
			 */
			Job *addOnFinishCallback(const JobTask &task);
			
			/**
			 * Объем занимаемой памяти, наследуемые классы должны должным образом переопределять эту функцию.
			 */
			virtual size_t getMemoryUse() const
			{
				return 0;
			}
			
			/**
			 * Возвращает сколько времени ушло на подготовку.
			 */
			double getPreparationTime() const
			{
				return preparation_time;
			}

		protected:
			Resource() : wait_sem(0)
			{
				status = RESOURCE_PREPARING;
				preparation_time = 0.0;
				sched = nullptr;
				timer.reset();
			}

			~Resource()
			{
				cancelPreparationJobs();
			}
			
			void setStatus(ResourceStatus s)
			{
				status = s;
			}
			
			/**
			 * Для выполнения подготовки ресурса нужно выполнить одну или несколько задач,
			 * эти задачи должны быть зарегестрированны вызовом этой функции.
			 * Обычно этим должен заниматься загрузчик данного типа ресурсов.
			 */
			void addPreparationJob0(Job *op);
			void addPreparationJob(Job *op)
			{
				op->addRef();
				addPreparationJob0(op);
			}

			void partitialyLoaded()
			{
				wait_sem.post();
			}

			// возвращает старый статус
			ResourceStatus setStatusIf(ResourceStatus s, ResourceStatus compare)
			{
				return (ResourceStatus) base::atomicCASInt((base::atomic_int_t *) &status, compare, s);
			}

			// возвращает старый статус
			ResourceStatus setStatusIfNot(ResourceStatus s, ResourceStatus compare)
			{
				return (ResourceStatus) base::atomicCAS2Int((base::atomic_int_t *) &status, compare, s);
			}

			// Для перевода ресурса в одно из конечных состояний следует вызывать эту функцию
			void preparationFinished(ResourceStatus s);

			// Шедулер для колбеков
			void setJobScheduler(IJobScheduler *s)
			{
				sched = s;
			}
			
		private:
			ResourceStatus status;
			boost::mutex callbacks_guard, preparation_jobs_guard;
			boost::interprocess::interprocess_semaphore wait_sem;
			typedef std::set<Job *> PreparationJobs;
			PreparationJobs preparation_jobs;
			base::Timer timer;
			double preparation_time;

			typedef boost::intrusive::list_base_hook<> BaseListHook;
			friend struct Callback;
			struct Callback : public JobProxy, public BaseListHook
			{
				Callback(Resource *owner_)
				{
					owner = owner_;
					owner->addRef();
				}

				~Callback()
				{
					owner->release();
				}

				using JobProxy::setup;
				using Job::doJob;
				using Job::setJobTask;

				JobTask task_to_do;
			private:
				Resource *owner;

				bool getJobOwnership(JobTask::Action a)
				{
					if (JobProxy::getJobOwnership(a))
					{
						owner->eraseCallback(*this);
						return true;
					}
					return false;
				}
			};

			typedef boost::intrusive::list<Callback> Callbacks;
			Callbacks callbacks;
			IJobScheduler *sched;

			bool eraseCallback(Callback &callback);
			void onWait(int millisecs);
			void cancelPreparationJobs();
			ResourceStatus wait_(int millisecs);
			void doCallback(JobTask::Action s);
		};
	}
}