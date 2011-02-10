#include "pch.h"

#if GB_ALLOW_BOOST_LIBRARY

#include "mt/ThreadPolicy.h"

#include <map>
#include <boost/thread.hpp>

namespace
{
	using namespace gb::mt;
	
	class RenderOnlyThreadPolicy : public ThreadPolicy
	{
	public:
		RenderOnlyThreadPolicy()
		{
			desirableThreadGroup = RENDER_THREAD_GROUP;
			acceptableThreadGroups.push_back(RENDER_THREAD_GROUP);
		}
	};
	
	class IOThreadPolicy : public ThreadPolicy
	{
	public:
		IOThreadPolicy()
		{
			desirableThreadGroup = IO_THREAD_GROUP;
			acceptableThreadGroups.push_back(RENDER_THREAD_GROUP);
			acceptableThreadGroups.push_back(IO_THREAD_GROUP);
		}
	};
	
	class CPUIntensiveThreadPolicy : public ThreadPolicy
	{
	public:
		CPUIntensiveThreadPolicy()
		{
			desirableThreadGroup = CPU_INTENSIVE_THREAD_GROUP;
			acceptableThreadGroups.push_back(RENDER_THREAD_GROUP);
			acceptableThreadGroups.push_back(IO_THREAD_GROUP);
			acceptableThreadGroups.push_back(CPU_INTENSIVE_THREAD_GROUP);
		}
	};
	
	std::map<boost::thread::id, ThreadGroup> thread_groups;
}

namespace gb {
	namespace mt {
		
		const ThreadPolicy *getRenderOnlyThreadPolicy()
		{
			static RenderOnlyThreadPolicy policy;
			return &policy;
		}
		
		const ThreadPolicy *getIOThreadPolicy()
		{
			static IOThreadPolicy policy;
			return &policy;
		}
		
		const ThreadPolicy *getCPUIntensiveThreadPolicy()
		{
			static CPUIntensiveThreadPolicy policy;
			return &policy;
		}
		
		void ThreadMapping::registerCurrentThread(ThreadGroup g)
		{
			thread_groups[boost::this_thread::get_id()] = g;
		}
		
		void ThreadMapping::unregisterCurrentThread()
		{
			thread_groups.erase(boost::this_thread::get_id());
		}
		
		ThreadGroup ThreadMapping::getCurrentThreadGroup()
		{
			assert(thread_groups.count(boost::this_thread::get_id()));
			return thread_groups.find(boost::this_thread::get_id())->second;
		}
	}
}

#endif // GB_ALLOW_BOOST_LIBRARY
