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
		
		struct JobTask
		{
			enum Action
			{
				DO_JOB,
				CANCEL_JOB
			};
			
			typedef boost::function<void (Action)> RunFunc;
			RunFunc run;
			const ThreadPolicy *policy;
			
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


		class Job : public base::IRefCountable
		{
		public:
			// status = JOB_WAITING at start
			// JOB_WAITING -> JOB_RUNNING when job starts to be carried out
			// JOB_WAITING -> JOB_CANCELING at Cancel()
			// JOB_RUNNING -> JOB_FINISHED then job(DO_JOB) ends
			// JOB_CANCELING -> JOB_CANCELED then job(CANCEL_JOB) ends
			// running job cannot be canceled
			enum JobStatus : base::atomic_int_t
			{
				JOB_WAITING,
				JOB_RUNNING,
				JOB_FINISHED,
				JOB_CANCELING,
				JOB_CANCELED
			};

			JobStatus getStatus() const
			{
				return status;
			}

			// try to cancel job
			JobStatus cancel();

			// wait until status won't become JOB_FINISHED or JOB_CANCELED
			// may do the job by self
			JobStatus wait(int millisecs = -1);

			JobStatus cancelAndWait()
			{
				cancel();
				return wait();
			}
			
			const ThreadPolicy *getThreadPolicy() const
			{
				return job_task.policy;
			}

		protected:
			Job();
			~Job();
			
			JobStatus doJob(JobTask::Action s);
			void setJobTask(const JobTask &task)
			{
				job_task = task;
			}

			// Overrided by scheduler
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

		class JobContainer
		{
		public:
			~JobContainer()
			{
				for (size_t i = 0; i < jobs.size(); ++i)
				{
					jobs[i]->release();
				}
			}

			void add0(Job *job)
			{
				jobs.push_back(job);
			}

			void add(Job *job)
			{
				job->addRef();
				add0(job);
			}

		private:
			typedef std::vector<Job *> Jobs;
			Jobs jobs;
		};

	} // namespace mt
} // namespace gb

#endif // GB_ALLOW_BOOST_LIBRARY
