#pragma once

#include "gb/Config.h"

#if GB_ALLOW_BOOST_LIBRARY

#include <vector>
#include <algorithm>

namespace gb {
	namespace mt {
		
		/**
		 * Группы потоков
		 */
		enum ThreadGroup
		{
			RENDER_THREAD_GROUP,
			IO_THREAD_GROUP,
			CPU_INTENSIVE_THREAD_GROUP,
			
			THREAD_GROUP_NUMBER,
		};
		
		/**
		 * \brief Стратегия выбора групп потоков для выполнения задач
		 * 
		 * Определяет какая группа потоков предпочтительна для выполнения задачи,
		 * а так же список групп, которым разрешено выполнять задачу.
		 */
		class ThreadPolicy
		{
		public:
			/** Возвращает группу потоков, предпочтительной для данной задачи */
			ThreadGroup getDesirableThreadGroup() const
			{
				return desirableThreadGroup;
			}
			
			/** Проверяет входит ли данная группа в список разрешённых */
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
		
		/**
		 * Возвращает RenderOnly стратегию. Задачи для неё могут выполнять только
		 * потоками из RENDER_THREAD_GROUP (обычно существует только один такой поток).
		 */
		const ThreadPolicy *getRenderOnlyThreadPolicy();
		
		/**
		 * Возвращает IOThread стратегию. Предпочтительной группой является IO_THREAD_GROUP.
		 * Но задачи также могут выполняться потоками из RENDER_THREAD_GROUP.
		 */
		const ThreadPolicy *getIOThreadPolicy();
		
		/**
		 * Возвращает CPUIntensive стратегию. Предпочтительной группой является CPU_INTENSIVE_THREAD_GROUP.
		 * Но задачи также могут выполняться потоками из RENDER_THREAD_GROUP, IO_THREAD_GROUP.
		 */
		const ThreadPolicy *getCPUIntensiveThreadPolicy(); // jobs could be executed by render, IO and CPU intensive threads
		
		/** \brief Определяет, в какую группу входит текущий поток
		 *
		 * Каждый поток может входить только в одну группу.
		 */
		class ThreadMapping
		{
		public:
			/** Регистрирует текущий поток в данной группе */
			static void registerCurrentThread(ThreadGroup g);
			
			/** Удаляет текущий поток из списка */
			static void unregisterCurrentThread();
			
			/** Возвращает группу для текущего потока */
			static ThreadGroup getCurrentThreadGroup();
			
		private:
			ThreadMapping(){}
		};

	} // namespace mt
} // namespace gb

#endif // GB_ALLOW_BOOST_LIBRARY
