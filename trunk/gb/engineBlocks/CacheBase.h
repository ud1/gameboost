#pragma once

#include <boost/intrusive/set.hpp>
#include <boost/thread.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace gb
{
	namespace engine_blocks
	{
		namespace detail
		{
			template <typename Request, typename Hook, bool>
			struct ResourceImplBase_;
			
			template <typename Request, typename Hook>
			struct ResourceImplBase_<Request, Hook, true> : public Hook
			{
				Request &getRequest() {return *this;}
				const Request &getRequest() const {return *this;}
			};
			
			template <typename Request, typename Hook>
			struct ResourceImplBase_<Request, Hook, false> : public Request, public Hook
			{
				Request &getRequest() {return *this;}
				const Request &getRequest() const {return *this;}
			};
		}
		
		/**
		 * CacheBase является основой для различных алгоритмов кэширования ресурсов.
		 * Управляет объектами типа Resource. Resource должен определять (typedef)
		 * у себя тип Request, являющимся уникальным идентификатором ресурса,
		 * и имеющим оператор <.
		 * Loader непосредственно выполянет загрузку ресурсов. Он должен реализовывать следующие функции:
		 * bool checkRequest(const Resource::Request &req); - проверяет валидность запроса.
		 * void load(const Resource::Request &req, Resouce &res); - непосредственная загрузка ресурса
		 * void update(const Resource::Request &req, Resouce &res); - обновление состояния ресурса.
		 */
		
		template <typename Resource, typename Mutex, typename Loader, typename Derived>
		class CacheBase
		{
		public:
			typedef typename Resource::Request Request;
			typedef CacheBase<Resource, Mutex, Loader, Derived> This;
			
			void setLoader(Loader &loader)
			{
				res_loader = &loader;
			}
			
			Resource *get(const Request &req)
			{
				ResourceImplBase *res;
				{
					boost::lock_guard<Mutex> guard(guard_mutex);
					res = getResourceCached(req);
					if (res)
						return res;
					
					if (!res_loader->checkRequest(req))
						return NULL;

					res = getDerived()->createResource();
					res->parent = this;
					
					// Добавляем только что созданный ресурс в кэш
					res->getRequest() = req;
					res_cache.insert(*res);
				}

				// Выполняем загрузку ресурса
				res_loader->load(req, *res);
				return res;
			}
			
		protected:
			struct set_ {};
			typedef boost::intrusive::set_base_hook< boost::intrusive::tag<set_> > BaseSetHook;

			friend class ResourceImplBase;
			
			class ResourceImplBase : public Resource, public detail::ResourceImplBase_<Request, BaseSetHook, boost::is_base_of<Resource, Request>::value>
			{
			public:
				bool operator < (const ResourceImplBase &o) const
				{
					return this->getRequest() < o.getRequest();
				}

				void destroyThis()
				{
					if(parent->onResourceDestruction(*this))
					{
						// Ресурс следует удалить из кеша и уничтожить
						parent->eraseResource(*this);
						delete this;
					} else {
						// Ресурс может быть еще полезен, сохраняем его во временном хранилище
						parent->registerGarbage(*this);
					}
				}
				
				This *parent;
			};

			struct ElemComp
			{
				bool operator() (const ResourceImplBase &f, const Request &s) const
				{
					return f.getRequest() < s;
				}

				bool operator() (const Request &f, const ResourceImplBase &s) const
				{
					return f < s.getRequest();
				}
			};
			
			typedef boost::intrusive::set<ResourceImplBase, typename boost::intrusive::base_hook<BaseSetHook> > ResourceCache;
			ResourceCache res_cache; // used for caching results
			Loader *res_loader;
			Mutex guard_mutex;
			
			ResourceImplBase *getResourceCached(const Request &req)
			{
				typename ResourceCache::iterator it = res_cache.find(req, ElemComp());
				if (it != res_cache.end()) {
					ResourceImplBase *elem = &*it;
					
					// Сообщаем наследуемому классу о том, что счеткик ссылок
					// ресурса будет увеличен. При этом ресурс должен быть изъят из
					// списка неиспользуемых ресурсов, если это имеет место.
					getDerived()->onGetResource(*elem);

					elem->addRef();
					res_loader->update(req, *elem);
					return elem;
				}
				return NULL;
			}
			
			/**
			 * Удаляет ресурс из кеша, может вызываться в наследуемых классах.
			 */
			void eraseResource(ResourceImplBase &res)
			{
				res_cache.erase(ResourceCache::s_iterator_to(res));
			}
			
			/**
			 * Вызывается, когда на ресурс больше никто не ссылается,
			 * но при этом мы не хотим пока его уничтожать. Ресурс продолжнает
			 * храниться в кэше, и должен добавиться в список неиспользуемых объектов
			 * у наследуемого класса.
			 */
			void registerGarbage(ResourceImplBase &res)
			{
				getDerived()->addToGarbageList(res);
			}
			
			/**
			 * Кастуем себя к типу наследуемого класса.
			 */
			Derived *getDerived()
			{
				return static_cast<Derived *>(this);
			}
			
			/**
			 * Вызывается когда счетчик ссылок на ресурс становится равным нулю,
			 * при этом наследуемый класс должен определить, нужно ли уничтожить
			 * ресурс, или есть смысл его сохранить на некоторое время в кэше.
			 * Если возвращает true, то ресурс будет уничтожен.
			 */
			bool onResourceDestruction(ResourceImplBase &res)
			{
				return getDerived()->onResourceDestruction(res);
			}
		};
		
	}
}