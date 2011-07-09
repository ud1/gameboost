#pragma once

#include "CacheBase.h"

namespace gb
{
	namespace resource
	{
		
		/**
		 * @ingroup redource_group
		 * \brief Самая простая реализация кэша, объекты при обнулении счетчика ссылок на них
		 * будут уничтожены незамедлительно.
		 */
		template <typename Resource, typename Mutex, typename Loader>
		class CacheNoGarbage : public CacheBase<Resource, Mutex, Loader, CacheNoGarbage<Resource, Mutex, Loader> >
		{
		public:
			typedef CacheBase<Resource, Mutex, Loader, CacheNoGarbage<Resource, Mutex, Loader> > Base;
			
			CacheNoGarbage()
			{
				Base::setLoader(loader);
			}
			
		private:
			friend class CacheBase<Resource, Mutex, Loader, CacheNoGarbage<Resource, Mutex, Loader> >;
			typedef typename Base::ResourceImplBase ResourceImplBase;
			void addToGarbageList(Resource &) {}
			bool onResourceDestruction(Resource &) {return true;}
			void onGetResource(Resource &) {}
			ResourceImplBase *createResource(){return new ResourceImplBase;}
			Loader loader;
		};
		
	}
}
