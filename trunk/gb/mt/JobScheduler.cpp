#include "pch.h"

#if GB_ALLOW_BOOST_LIBRARY

#include <gb/mt/JobScheduler.h>
#include <gb/base/Debug.h>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/intrusive/set.hpp>

#include <set>
#include <map>

namespace
{
	using namespace gb::mt;
	using namespace boost::posix_time;
	typedef boost::date_time::microsec_clock<boost::posix_time::ptime> clock;

	class JobSchedulerQueue
	{
	public:
		
		JobSchedulerQueue();
		~JobSchedulerQueue();

		void setThreadGroup(ThreadGroup group)
		{
			this->group = group;
		}
		
		// thread safe
		Job *scheduleJob(int millisecs, const JobTask &f);

		bool isRunning() const
		{
			return is_running;
		}

		void startThreads(size_t threads_number);
	
		void stop()
		{
			is_running = false;
		}

		void runOnce();
		void run();

		IJobScheduler *parent;
	private:
		boost::thread **threads;
		boost::interprocess::interprocess_semaphore semaphore;
		boost::mutex mutex;
		volatile bool is_running;
		ThreadGroup group;

		typedef boost::intrusive::set_base_hook<> BaseSetHook;
		friend struct JobEntry;
		struct JobEntry : public Job, public BaseSetHook
		{
			JobEntry(JobSchedulerQueue *shd_)
			{
				shd = shd_;
				shd->parent->addRef();
			}

			~JobEntry()
			{
				shd->parent->release();
			}

			bool operator < (const JobEntry &o) const
			{
				return t < o.t;
			}

			using Job::doJob;
			using Job::setJobTask;

			boost::posix_time::ptime t;
			JobSchedulerQueue *shd;

		protected:
			bool getJobOwnership(JobTask::Action a)
			{
				return getThreadPolicy()->checkThreadGroup(ThreadMapping::getCurrentThreadGroup()) && shd->eraseJob(*this);
			}
		};

		typedef boost::intrusive::multiset<JobEntry> Jobs;
		Jobs jobs; // guarded by mutex
		size_t threadsN;
		boost::posix_time::ptime creationTime;

		JobEntry *getJob_(bool &is_empty_out, ptime &time_to_wait_out)
		{
			JobEntry *res = NULL;
			mutex.lock();
			if (!(is_empty_out = jobs.empty()))
			{
				Jobs::iterator it = jobs.begin();
				time_to_wait_out = it->t;
				if (time_to_wait_out <= clock::universal_time())
				{
					res = &*it;
					jobs.erase(it);
				}
			}
		
			mutex.unlock();
			return res;
		}

		bool eraseJob(JobEntry &job)
		{
			boost::lock_guard<boost::mutex> guard(mutex);
			if (job.is_linked())
			{
				jobs.erase(Jobs::s_iterator_to(job));
				job.release();
				return true;
			}
			else
			{
				return false;
			}
		}

		void cancelAllJobs()
		{
			while(1)
			{
				JobEntry *entry;
				mutex.lock();
				if (!jobs.empty())
				{
					Jobs::iterator it = jobs.begin();
					entry = &*it;
					jobs.erase(it);
				}
				else
				{
					entry = NULL;
				}
				mutex.unlock();

				if (entry)
				{
					entry->doJob(JobTask::CANCEL_JOB);
					entry->release();
				} else return;
			}
		}
		
		void threadFunc()
		{
			ThreadMapping::registerCurrentThread(group);
			run();
			ThreadMapping::unregisterCurrentThread();
		}
	};

	JobSchedulerQueue::JobSchedulerQueue() : semaphore(0 /* initial count */)
	{
		is_running = true;
		creationTime = clock::universal_time();
		threadsN = 0;
	}

	JobSchedulerQueue::~JobSchedulerQueue()
	{
		stop();
		for (int i = 0; i < threadsN; ++i)
		{
			semaphore.post();
		}
		
		for (int i = 0; i < threadsN; ++i)
		{
			threads[i]->join();
			delete threads[i];
		}
		
		delete []threads;
		cancelAllJobs();
	}

	Job *JobSchedulerQueue::scheduleJob(int millisecs, const JobTask &f)
	{
		JobEntry *entry = new JobEntry(this);
		entry->setJobTask(f);
		entry->addRef();

		if (millisecs > 0)
		{
			entry->t = clock::universal_time() + milliseconds(millisecs);
			mutex.lock();
			if (jobs.insert(*entry) == jobs.begin())
			{
				semaphore.post();
			}
			mutex.unlock();
		}
		else
		{
			entry->t = creationTime;
			mutex.lock();
			if (jobs.insert(jobs.begin(), *entry) == jobs.begin())
			{
				semaphore.post();
			}
			mutex.unlock();
		}

		return entry;
	}

	void JobSchedulerQueue::run()
	{
		while (is_running)
		{
			JobEntry *job;
			bool is_empty;
			ptime time_to_wait;

			if (job = getJob_(is_empty, time_to_wait))
			{
				job->doJob(JobTask::DO_JOB);
				job->release();
			}
			else if (is_empty)
			{
				semaphore.wait();
			}
			else
			{
				semaphore.timed_wait(time_to_wait);
			}
		}
	}

	void JobSchedulerQueue::runOnce()
	{
		while (is_running)
		{
			JobEntry *job;
			bool is_empty;
			boost::posix_time::ptime time_to_wait;
			// unreferenced -- const void *owner;

			if (job = getJob_(is_empty, time_to_wait))
			{
				job->doJob(JobTask::DO_JOB);
				job->release();
			}
			else
			{
				return;
			}
		}
	}

	void JobSchedulerQueue::startThreads(size_t threads_number)
	{
		if (threadsN)
			return;

		threadsN = threads_number;
		threads = new boost::thread *[threadsN];
		for (int i = 0; i < threadsN; ++i)
			threads[i] = new boost::thread(boost::bind(&JobSchedulerQueue::threadFunc, this));
	}
	
	
	class JobScheduler : public IJobScheduler
	{
	public:
		JobScheduler()
		{
			is_running = true;
			for (size_t i = 0; i < (size_t) THREAD_GROUP_NUMBER; ++i)
			{
				queues[i].setThreadGroup((ThreadGroup) i);
				queues[i].parent = this;
			}
		}
		
		Job *scheduleJob(int millisecs, const JobTask &f)
		{
			return queues[f.policy->getDesirableThreadGroup()].scheduleJob(millisecs, f);
		}
		
		bool isRunning() const
		{
			return is_running;
		}

		void startThreads(size_t threads_number, ThreadGroup group)
		{
			queues[group].startThreads(threads_number);
		}
		
		void stop()
		{
			for (size_t i = 0; i < THREAD_GROUP_NUMBER; ++i)
			{
				is_running = false;
				queues[i].stop();
			}
		}

		void runOnce(ThreadGroup group)
		{
			queues[group].runOnce();
		}
		
		void run(ThreadGroup group)
		{
			queues[group].run();
		}
		
	private:
		JobSchedulerQueue queues[THREAD_GROUP_NUMBER];
		bool is_running;
	};
}

namespace gb {
	namespace mt {
		IJobScheduler *createJobScheduler()
		{
			return new JobScheduler;
		}

		Loop::Loop(IJobScheduler *sched_, int period_millisecs, const JobTask &f)
		{
			GBASSERT(sched_);
			sched = sched_;
			period = period_millisecs;
			task.policy = f.policy;
			task.run = boost::bind(&Loop::doJob, this, boost::lambda::_1);
			func = f.run;
			job = sched->scheduleJob(period, task);
		}
		
		Loop::~Loop()
		{
			job_mutex.lock();
			Job *theJob = job;
			job = NULL;
			job_mutex.unlock();
			
			theJob->cancelAndWait();
			theJob->release();
		}
		
		void Loop::doJob(JobTask::Action a)
		{
			func(a);
			
			job_mutex.lock();
			if (job)
			{
				job->release();
				job = sched->scheduleJob(period, task);
			}
			job_mutex.unlock();
		}
	}
}

#endif // GB_ALLOW_BOOST_LIBRARY
