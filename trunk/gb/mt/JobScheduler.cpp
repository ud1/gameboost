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
	using namespace boost::interprocess;
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

		bool runOnce();
		void run(size_t n);

		IJobScheduler *parent;
	private:
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
				assigned_thread = -1;
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

			ptime t;
			JobSchedulerQueue *shd;
			long assigned_thread;

		protected:
			bool getJobOwnership(JobTask::Action a)
			{
				if (a == JobTask::DO_JOB && !getThreadPolicy()->checkThreadGroup(ThreadMapping::getCurrentThreadGroup()))
					return false;
				return shd->eraseJob(*this);
			}
		};

		typedef boost::intrusive::multiset<JobEntry> Jobs;
		Jobs jobs; // guarded by mutex
		Jobs::iterator frontier_job, last_zero_delay_job;
		size_t frontier_job_pos; // number of entries before frontier_job plus 1, frontier_job_pos <= free_workers.size()
		size_t last_zero_delay_job_pos; // number of entries before last_zero_delay_job plus 1
		size_t threadsN;
		ptime creationTime;
		
		//                            |----frontier_job
		//                            |
		//                            *
		// | Job | Job | Job | ... | Job | Job | Job | Job | Job | ... |
		// | t=0 | t=0 | t=0 | ... | t=0 | t=0 | t=0 | t>0 | t>0 | ... |
		// |                             |        ^
		// |       waiting_workers       |        |
		// <---------------------------->         |
		//                                        |---last_zero_delay_job
		//
		// frontier_job_pos/last_zero_delay_job_pos:
		// |  1  |  2  |  3  | ... |
		
		friend struct Worker;
		struct Worker
		{
			Worker()
			{
				semaphore = NULL;
				job = NULL;
			}
			
			void init(JobSchedulerQueue *holder, size_t n)
			{
				semaphore = new interprocess_semaphore(0);
				thread = new boost::thread(boost::bind(&JobSchedulerQueue::threadFunc, holder, n));
			}
			
			~Worker()
			{
				semaphore->post();
				thread->join();
				delete semaphore;
				delete thread;
			}
			
			boost::thread *thread;
			interprocess_semaphore *semaphore;
			JobSchedulerQueue::JobEntry *job;
		};
		Worker *workers;
		std::vector<size_t> free_workers; // values = [0..threadsN-1]
		size_t waiting_workers;

		JobEntry *getFirstJob(ptime time_before)
		{
			JobEntry *res = NULL;
			mutex.lock();
			if (!jobs.empty())
			{
				Jobs::iterator it = jobs.begin();
				if (it->t <= time_before)
				{
					res = &*it;
					--waiting_workers;

					frontier_job_pos--;
					if (res->t == creationTime)
						last_zero_delay_job_pos--;

					workers[res->assigned_thread].job = NULL;
					jobs.erase(it);
				}
			}
		
			mutex.unlock();
			return res;
		}
		
		void threadReleased(size_t n)
		{ // mutex locked
			if (frontier_job_pos)
			{
				Jobs::iterator it = frontier_job;
				if (++it != jobs.end())
				{
					++frontier_job;
					++frontier_job_pos;
					workers[n].job = &*frontier_job;
					frontier_job->assigned_thread = n;
				}
				else
				{
					free_workers.push_back(n);
					workers[n].job = NULL;
				}
			}
			else
			{
				frontier_job = jobs.begin();
				frontier_job_pos = 0;
				if (frontier_job != jobs.end())
				{
					frontier_job_pos = 1;
					workers[n].job = &*frontier_job;
					frontier_job->assigned_thread = n;
				}
			}
		}

		bool eraseJob(JobEntry &job)
		{
			boost::lock_guard<boost::mutex> guard(mutex);
			if (job.is_linked())
			{
				Jobs::iterator it = Jobs::s_iterator_to(job);
				
				if (job.t == creationTime)
				{
					if (last_zero_delay_job_pos > 1 && it == last_zero_delay_job)
						--last_zero_delay_job;
					--last_zero_delay_job_pos;
				}
				
				if (job.assigned_thread >= 0)
				{
					if (frontier_job_pos > 1 && it == frontier_job)
						--frontier_job;
					--frontier_job_pos;
				}
				
				jobs.erase(it);
				
				if (job.assigned_thread >= 0)
				{
					threadReleased(job.assigned_thread);
					workers[job.assigned_thread].semaphore->post();
				}
				
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
		
		void threadFunc(size_t n)
		{
			ThreadMapping::registerCurrentThread(group);
			run(n);
			ThreadMapping::unregisterCurrentThread();
		}
		
		Jobs::iterator insertJob(JobEntry *entry, int millisecs, bool &fire_semaphore_out)
		{ // mutex is locked
			Jobs::iterator result;
			bool inserted_before_frontier_job = false;
			bool update_frontier_job_pos = false;
			fire_semaphore_out = false;
			if (!millisecs)
			{
				if (!last_zero_delay_job_pos)
					result = last_zero_delay_job = jobs.insert(*entry);
				else result = last_zero_delay_job = jobs.insert_before(++last_zero_delay_job, *entry);

				++last_zero_delay_job_pos;
				
				if (last_zero_delay_job_pos <= waiting_workers)
					inserted_before_frontier_job = true;
			}
			else
			{
				if (!frontier_job_pos)
				{
					result = frontier_job = jobs.insert(*entry);
					frontier_job_pos = 1;
					fire_semaphore_out = true;
				}
				else if (entry->t < frontier_job->t)
				{
					result = jobs.insert(*entry);
					inserted_before_frontier_job = true;
				}
				else if (entry->t == frontier_job->t)
				{
					Jobs::iterator it = frontier_job;
					result = jobs.insert_before(++it, *entry);
					update_frontier_job_pos = true;
				}
				else
				{
					result = jobs.insert(*entry);
					update_frontier_job_pos = true;
				}
			}
			
			if (update_frontier_job_pos && frontier_job_pos < waiting_workers)
			{
				frontier_job = result;
				++frontier_job_pos;
				fire_semaphore_out = true;
			}
			
			if (inserted_before_frontier_job)
			{
				fire_semaphore_out = true;
				if (waiting_workers && frontier_job_pos == waiting_workers)
				{
					frontier_job->assigned_thread = -1;
					--frontier_job;
				}
				else
				{
					++frontier_job_pos;
					assert(frontier_job_pos <= waiting_workers);
				}
			}
			return result;
		}
	};

	JobSchedulerQueue::JobSchedulerQueue()
	{
		is_running = true;
		creationTime = clock::universal_time();
		threadsN = 0;
		frontier_job = last_zero_delay_job = jobs.end();
		frontier_job_pos = last_zero_delay_job_pos = 0;
	}

	JobSchedulerQueue::~JobSchedulerQueue()
	{
		stop();
		delete []workers;
		cancelAllJobs();
	}

	Job *JobSchedulerQueue::scheduleJob(int millisecs, const JobTask &f)
	{
		JobEntry *entry = new JobEntry(this);
		entry->setJobTask(f);
		entry->addRef();

		if (millisecs > 0)
			entry->t = clock::universal_time() + milliseconds(millisecs);
		else entry->t = creationTime;
		
		mutex.lock();
		size_t old_frontier_job_pos = frontier_job_pos;
		size_t old_frontier_job_thread = (old_frontier_job_pos == 0 ? 0 : frontier_job->assigned_thread);
		bool fire_semaphore;
		insertJob(entry, millisecs, fire_semaphore);
		if (fire_semaphore)
		{
			if (!free_workers.empty())
			{
				entry->assigned_thread = *free_workers.rbegin();
				free_workers.pop_back();
				workers[entry->assigned_thread].job = entry;
			}
			else
			{
				entry->assigned_thread = old_frontier_job_thread;
				workers[entry->assigned_thread].job = entry;
			}
			
			workers[entry->assigned_thread].semaphore->post();
		}
		mutex.unlock();

		return entry;
	}

	void JobSchedulerQueue::run(size_t n)
	{
		while (is_running)
		{
			mutex.lock();
			bool has_job = workers[n].job != NULL;
			ptime time_to_wait;
			if (has_job)
				time_to_wait = workers[n].job->t;
			mutex.unlock();
			
			JobEntry *job;
			if (has_job && !workers[n].semaphore->timed_wait(time_to_wait))
			{
				if (job = getFirstJob(time_to_wait))
				{
					job->doJob(JobTask::DO_JOB);
					job->release();
					mutex.lock();
					++waiting_workers;
					threadReleased(n);
					mutex.unlock();
				}
			}
			
			if (!has_job)
			{
				workers[n].semaphore->wait();
			}
		}
	}

	bool JobSchedulerQueue::runOnce()
	{
		while (is_running)
		{
			JobEntry *job;
			if (job = getFirstJob(clock::universal_time()))
			{
				job->doJob(JobTask::DO_JOB);
				job->release();
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	void JobSchedulerQueue::startThreads(size_t threads_number)
	{
		if (threadsN)
			return;

		threadsN = threads_number;
		workers = new Worker[threadsN];
		free_workers.reserve(threadsN);
		waiting_workers = threadsN;
		for (size_t i = 0; i < threadsN; ++i)
		{
			workers[i].init(this, i);
			free_workers.push_back(i);
		}
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

		bool runOnce(ThreadGroup group)
		{
			return queues[group].runOnce();
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
