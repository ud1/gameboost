#include "pch.h"

#if GB_ALLOW_BOOST_LIBRARY

#include <gb/mt/Job.h>
#include <gb/mt/JobScheduler.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>

namespace gb {
	namespace mt {

		Job::Job() : wait_sem(0)
		{
			status = JOB_WAITING;
		}

		Job::~Job()
		{
			cancelAndWait();
		}

		Job::JobStatus Job::cancel()
		{
			if (getJobOwnership(JobTask::CANCEL_JOB) &&
				base::atomicCASInt((base::atomic_int_t *) &status, JOB_WAITING, JOB_CANCELING) == JOB_WAITING)
			{
				doJobImpl(JobTask::CANCEL_JOB);
			}
			return getStatus();
		}

		Job::JobStatus Job::wait(int millisecs)
		{
			using namespace boost::posix_time;

			// try to do job by ourself
			if (getJobOwnership(JobTask::DO_JOB) &&
				base::atomicCASInt((base::atomic_int_t *) &status, JOB_WAITING, JOB_RUNNING) == JOB_WAITING)
			{
				doJobImpl(JobTask::DO_JOB);
			}

			if (millisecs == -1)
			{
				wait_sem.wait();
				wait_sem.post();
			}
			else
			{
				if (wait_sem.timed_wait(boost::date_time::microsec_clock<ptime>::universal_time() + milliseconds(millisecs)))
				{
					wait_sem.post();
				}
			}

			return getStatus();
		}

		void Job::doJobImpl(JobTask::Action s)
		{
			if (s == JobTask::CANCEL_JOB)
			{
				assert(status == JOB_CANCELING);
				job_task.run(s);
				status = JOB_CANCELED;
			}
			else
			{
				assert(status == JOB_RUNNING);
				job_task.run(s);
				status = JOB_FINISHED;
			}
			wait_sem.post();
		}

		Job::JobStatus Job::doJob(JobTask::Action s)
		{
			if (base::atomicCASInt((base::atomic_int_t *) &status, JOB_WAITING, JOB_RUNNING) == JOB_WAITING)
			{
				doJobImpl(JobTask::DO_JOB);
			}
			return getStatus();
		}
		
		void JobProxy::setup(IJobScheduler *sch, const JobTask &task)
		{
			setJobTask(task);
			if (sch && task.policy)
			{
				JobTask new_task;
				new_task.policy = task.policy;
				new_task.run = boost::bind(&JobProxy::doJob, this, boost::lambda::_1);
				real_job = sch->scheduleJob(0, new_task);
			}
			else
			{
				doJob(JobTask::DO_JOB);
			}
		}
		
		bool JobProxy::getJobOwnership(JobTask::Action a)
		{
			if (!real_job)
				return false;
			return real_job->getJobOwnership(a);
		}

	}
}

#endif // GB_ALLOW_BOOST_LIBRARY
