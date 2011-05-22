#pragma once

#include <gb/mt/JobScheduler.h>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

namespace gb
{
	namespace resource
	{
		
		/**
		 * \brief Ассинхронный загрузчик ресурсов, для выполнения своих задач использует IJobScheduler.
		 * 
		 * SyncLoader помимо требований указаных в CacheBase должен иметь функцию
		 * @code
		 * void cancel(const Resource::Request &req, Resouce &res);
		 * @endcode
		 */
		template <typename SyncLoader, typename Resource>
		class AsyncLoader
		{
		public:
			AsyncLoader(SyncLoader &loader, mt::IJobScheduler *scheduler) : loader(loader), scheduler(scheduler)
			{
				scheduler->addRef();
			}
			
			~AsyncLoader()
			{
				scheduler->release();
			}
			
			bool checkRequest(const Resource::Request &req)
			{
				return loader.checkRequest(req);
			}
			
			void load(const Resource::Request &req, Resouce &res)
			{
				res.addRef();
				mt::JobTask task;
				task.policy = mt::getIOThreadPolicy();
				task.run = boost::bind(&AsyncLoader<SyncLoader, Resource>::loan_func, req, &res, boost::lambda::_1);
				scheduler->scheduleJob0(0, task);
			}
			
			void update(const Resource::Request &req, Resouce &res)
			{
				loader.update(req, res);
			}
			
		private:
			SyncLoader &loader;
			mt::IJobScheduler *scheduler;
			
			void loan_func(Resource::Request req, Resouce *res, mt::JobTask::Action a)
			{
				if (a == mt::JobTask::DO_JOB)
				{
					loader.load(req, res);
				}
				else
				{
					loader.cancel(req, res);
				}
				res->release();
			}
		};
		
	}
}
