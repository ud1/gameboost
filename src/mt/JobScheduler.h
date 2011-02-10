#pragma once

#if GB_ALLOW_BOOST_LIBRARY

#include "ThreadPolicy.h"
#include "Job.h"

namespace gb {
	namespace mt {

		class IJobScheduler : public base::IRefCountable {
		public:
			virtual Job *scheduleJob(int millisecs, const JobTask &f) = 0;

			void scheduleJob0(int millisecs, const JobTask &f)
			{
				scheduleJob(millisecs, f)->release();
			}

			virtual bool isRunning() const = 0;

			// Threads automaticly register themself in ThreadMapping
			virtual void startThreads(size_t threads_number, ThreadGroup group) = 0;
			virtual void stop() = 0;

			virtual void runOnce(ThreadGroup group) = 0;
			virtual void run(ThreadGroup group) = 0;
		};

		IJobScheduler *createJobScheduler();

		class Loop {
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
