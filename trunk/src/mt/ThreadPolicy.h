#pragma once

#if GB_ALLOW_BOOST_LIBRARY

#include <vector>
#include <algorithm>

namespace gb {
	namespace mt {
		
		enum ThreadGroup
		{
			RENDER_THREAD_GROUP,
			IO_THREAD_GROUP,
			CPU_INTENSIVE_THREAD_GROUP,
			
			THREAD_GROUP_NUMBER,
		};
		
		class ThreadPolicy
		{
		public:
			ThreadGroup getDesirableThreadGroup() const
			{
				return desirableThreadGroup;
			}
			
			bool checkThreadGroup(ThreadGroup group) const
			{
				return
					std::find(acceptableThreadGroups.begin(), acceptableThreadGroups.end(), group)
						!= acceptableThreadGroups.end();
			}
			
		protected:
			ThreadGroup desirableThreadGroup;
			std::vector<ThreadGroup> acceptableThreadGroups;
		};
		
		const ThreadPolicy *getRenderOnlyThreadPolicy(); // jobs could be executed by render thread only
		const ThreadPolicy *getIOThreadPolicy(); // jobs could be executed by render thread and IO threads
		const ThreadPolicy *getCPUIntensiveThreadPolicy(); // jobs could be executed by render, IO and CPU intensive threads
		
		class ThreadMapping
		{
		public:
			static void registerCurrentThread(ThreadGroup g);
			static void unregisterCurrentThread();
			static ThreadGroup getCurrentThreadGroup();
			
		private:
			ThreadMapping(){}
		};

	} // namespace mt
} // namespace gb

#endif // GB_ALLOW_BOOST_LIBRARY
