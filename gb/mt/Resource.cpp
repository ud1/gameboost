#include "Resource.h"

namespace gb
{
	namespace mt
	{
		//----------------------- Resource --------------------------------

		Resource::ResourceStatus Resource::wait(int millisecs)
		{
			if (millisecs == -1)
			{
				ResourceStatus res;
				while (res = getStatus(), res == RESOURCE_PREPARING)
				{
					wait_(millisecs);
				}
				return res;
			}
			return wait_(millisecs);
		}

		Job *Resource::addOnFinishCallback(const JobTask &task)
		{
			if (task.policy && !sched)
				return nullptr; // Не можем выполнять задачи с политикой без шедулера
			
			Callback *callback = new Callback(this);
			callback->task_to_do = task;
			callback->addRef();

			callbacks_guard.lock();
			ResourceStatus s = getStatus();
			callbacks.push_back(*callback);
			callbacks_guard.unlock();

			if (s != RESOURCE_PREPARING)
			{
				doCallback(JobTask::DO_JOB);
			}
			return callback;
		}

		void Resource::addPreparationJob0(Job *op)
		{
			{
				boost::lock_guard<boost::mutex> guard(preparation_jobs_guard);
				preparation_jobs.insert(op);
			}
			partitialyLoaded();
		}

		void Resource::preparationFinished(ResourceStatus s)
		{
			preparation_time = timer.getTime();
			status = s;
			// отменяем задачи, если такие еще остались
			cancelPreparationJobs();
			wait_sem.post();
			doCallback(JobTask::DO_JOB);
		}

		bool Resource::eraseCallback(Callback &callback)
		{
			boost::lock_guard<boost::mutex> guard(callbacks_guard);
			if (callback.is_linked())
			{
				callbacks.erase(Callbacks::s_iterator_to(callback));
				callback.release();
				return true;
			}
			else
			{
				return false;
			}
		}

		void Resource::onWait(int millisecs)
		{
			if (millisecs == -1)
				millisecs = 10;
			double t, millisecs_remains = millisecs;
			size_t N;
			std::vector<Job *> unfinished_ops;
			
			while (millisecs_remains > 0)
			{
				std::set<Job *>::iterator it;
				Job *op;
				preparation_jobs_guard.lock();
				N = preparation_jobs.size();
				it = preparation_jobs.begin();
				if (it != preparation_jobs.end())
				{
					op = *it;
					preparation_jobs.erase(it);
				}
				else
				{
					op = nullptr;
				}
				preparation_jobs_guard.unlock();

				if (!op)
					break;
				
				t = timer.getTime();
				Job::JobStatus st = op->wait(millisecs_remains / N);
				millisecs_remains -= (timer.getTime() - t)*1000.0;
				
				if (st == Job::JOB_FINISHED || st == Job::JOB_CANCELED)
				{
					op->release();
				}
				else
				{
					unfinished_ops.push_back(op);
				}

				if (getStatus() == RESOURCE_OK)
					break;
			}

			for (size_t i = 0; i < unfinished_ops.size(); ++i)
			{
				addPreparationJob(unfinished_ops[i]);
			}
		}

		void Resource::cancelPreparationJobs()
		{
			boost::lock_guard<boost::mutex> guard(preparation_jobs_guard);
			for (PreparationJobs::iterator it = preparation_jobs.begin(); it != preparation_jobs.end(); ++it)
			{
				(*it)->tryCancel();
				(*it)->release();
			}
			preparation_jobs.clear();
		}

		Resource::ResourceStatus Resource::wait_(int millisecs)
		{
			double t, millisecs_remains = millisecs;
			t = timer.getTime();
			onWait(millisecs);
			millisecs_remains -= (timer.getTime() - t)*1000.0;
			
			bool sem_counter_changed = false;
			if (millisecs == -1 || millisecs_remains)
			{
				wait_sem.wait();
				sem_counter_changed = true;
			}
			else
			{
				if (wait_sem.timed_wait(boost::date_time::microsec_clock<boost::posix_time::ptime>::universal_time()+
					boost::posix_time::milliseconds(millisecs)))
				{
					sem_counter_changed = true;
				}
			}
			
			if (getStatus() != RESOURCE_PREPARING && sem_counter_changed)
				wait_sem.post();
			
			return getStatus();
		}

		void Resource::doCallback(JobTask::Action s)
		{
			while (1)
			{
				Callback *callback;
				callbacks_guard.lock();
				if (!callbacks.empty())
				{
					Callbacks::iterator it = callbacks.begin();
					callback = &*it;
					callbacks.erase(it);
				}
				else
				{
					callback = nullptr;
				}
				callbacks_guard.unlock();

				if (callback)
				{
					if (s == JobTask::DO_JOB)
						callback->setup(sched, callback->task_to_do);
					else callback->task_to_do.run(s);
					
					callback->release();
				} else return;
			}
		}
		
	}
}
