#pragma once

#include <gb/base/Atomic.h>
#include <cstdlib>

namespace gb
{
	namespace base
	{

		/**
		 * Базовый класс для объектов, время жизни которых определяется
		 * счетчиком ссылок на них. При достижении счетчиком нуля вызывается
		 * функция destroyThis(), которую можно при необходимости переопределить
		 * в наследуемых классах.
		 */
		class IRefCountable
		{
		public:

			typedef base::atomic_int_t RefCount_t;

			IRefCountable()
			{
				refCount = 1;
			}

			virtual ~IRefCountable() {}

			RefCount_t addRef() const
			{
				return atomicIncrAndFetchInt(&refCount);
			}

			RefCount_t release() const
			{
				RefCount_t count = atomicDecrAndFetchInt(&refCount);
				if (count <= 0)
				{
					const_cast<IRefCountable *>(this)->destroyThis();
					return 0;
				}
				return refCount;
			}

			RefCount_t getCounter() const
			{
				return refCount;
			}

		private:
			mutable RefCount_t refCount;

		protected:
			virtual void destroyThis()
			{
				delete this;
			}
		};
		
		/**
		 * RefCntHolder используется для хранения IRefCountable объектов.
		 */
		template <typename T>
		struct RefCntHolder
		{
			RefCntHolder()
			{
				ptr = NULL;
			}
			
			RefCntHolder(T *t, bool inc_counter = true)
			{
				ptr = t;
				if (ptr && inc_counter)
					ptr->addRef();
			}
			
			RefCntHolder(const RefCntHolder<T> *o)
			{
				ptr = o->ptr;
				if (ptr)
					ptr->addRef();
			}
			
			~RefCntHolder()
			{
				if (ptr)
					ptr->release();
			}
			
			T *operator = (T *t)
			{
				if (ptr)
					ptr->release();
				
				ptr = t;
				
				if (ptr)
					ptr->addRef();
			}
			
			void set0(T *t)
			{
				if (ptr)
					ptr->release();
				
				ptr = t;
			}
			
			operator T *()
			{
				return ptr;
			}
			
			T *operator -> ()
			{
				return ptr;
			}
			
		private:
			T *ptr;
		};
		
		/**
		 * Данную функцию следует использовать для сохранения
		 * IRefCountable объекта полученного из фабрики непосредственно
		 * в RefCntHolder.
		 */
		template <typename T>
		RefCntHolder<T> CreateRFHolder(T *t)
		{
			return RefCntHolder<T>(t, false);
		}
	} // namespace
} // namespace
