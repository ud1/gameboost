#pragma once

#include "CacheBase.h"

#include <cassert>

#include <boost/intrusive/list.hpp>

namespace gb
{
	namespace engine_blocks
	{
		
		/**
		 * \brief Кэш объектов, объекты при обнулении счетчика ссылок на них не будут уничтожены незамедлительно,
		 * а сохрянятся во внутреней очереди на случай, если они еще могут понадобиться.
		 * 
		 * Каждый ресурс обладает дополнительным параметром - временной точкой time_point, 
		 * с помощью которого можно управлять уничтожением ресурсов.
		 */
		template <typename Resource, typename Mutex, typename Loader>
		class LRUCache : public CacheBase<Resource, Mutex, Loader, LRUCache<Resource, Mutex, Loader> >
		{
		public:
			typedef CacheBase<Resource, Mutex, Loader, LRUCache<Resource, Mutex, Loader> > Base;
			
			LRUCache()
			{
				Base::setLoader(loader);
				time_point = 0;
			}
			
			~LRUCache()
			{
				deleteGarbage(time_point);
				assert(garbageList.empty());
			}
			
			/** Увеличивает значение временной точки на 1 */
			size_t incTimePoint()
			{
				return ++time_point;
			}
			
			/** Возвращает текущее для кэша значение временной точки */
			size_t getTimePoint() const {return time_point;}
			
			/** Удаляет все объекты, которых значение временной точки меньше или равно указанной */
			void deleteGarbage(size_t time_point)
			{
				typename GarbageList::iterator it = garbageList.begin();
				while (it != garbageList.end() && (*it).time_point <= time_point)
				{
					ResourceImpl &res = *it;
					it = garbageList.erase(it);
					Base::eraseResource(res);
					delete &res;
				}
			}
			
		private:
			friend class CacheBase<Resource, Mutex, Loader, LRUCache<Resource, Mutex, Loader> >;
			typedef typename Base::ResourceImplBase ResourceImplBase;
			struct list_ {};
			typedef boost::intrusive::list_base_hook< boost::intrusive::tag<list_> > ListHook;
			
			struct ResourceImpl : public ResourceImplBase, public ListHook
			{
				size_t time_point;
			};
			
			typedef boost::intrusive::list<ResourceImpl, typename boost::intrusive::base_hook<ListHook> > GarbageList;
			GarbageList garbageList;
			
			size_t time_point;
			
			void addToGarbageList(Resource &r)
			{
				ResourceImpl &res = static_cast<ResourceImpl &>(r);
				res.time_point = time_point;
				garbageList.push_back(res);
			}
			
			bool onResourceDestruction(Resource &) {return false;}
			
			void onGetResource(Resource &r)
			{
				ResourceImpl &res = static_cast<ResourceImpl &>(r);
				if (((ListHook &)res).is_linked())
				{
					garbageList.erase(GarbageList::s_iterator_to(res));
				}
			}
			
			ResourceImplBase *createResource(){return new ResourceImpl;}
			Loader loader;
		};
		
	}
}
