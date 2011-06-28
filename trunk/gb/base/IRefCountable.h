#pragma once

#include <gb/base/Atomic.h>
#include <cstdlib>

namespace gb
{
	namespace base
	{

		/**
		 * \brief Базовый класс для объектов, время жизни которых определяется
		 * счетчиком ссылок на них.
		 * 
		 * При достижении счетчиком нуля вызывается
		 * функция destroyThis(), которую можно при необходимости переопределить
		 * в наследуемых классах.
		 * Хотя функции увеличения и уменьшения счетчика потокобезопасны,
		 * классы наследуемые от IRefCountable быть таковыми не обязанны.
		 * 
		 * Следует придерживаться следующих правил при работе с IRefCountable объектами:
		 * <ol>
		 * 	<li> Если IRefCountable объект приходит как параметр функции никаких
		 * дополнительных действий производить не требуется:
		 * @code
		 * void someFunc(IRefCountable *obj)
		 * {
		 * 	obj->doSmth();
		 * }
		 * @endcode
		 * 		Если же при этом его нужно сохранить в какой-то локальной переменной для
		 * 		позднего использования, следует увеличить счетчик ссылок на 1. Когда объект больше не требуется
		 * 		счетчик ссылок следует уменьшить:
		 * @code
		 * struct someStruct
		 * {
		 * 	~someStruct()
		 * 	{
		 * 		local->release();
		 * 	}
		 * 
		 * 	void setObj(IRefCountable *obj)
		 * 	{
		 * 		local = obj;
		 * 		obj->addRef();
		 * 	}
		 * 	IRefCountable *local;
		 * };
		 * @endcode
		 * 		Или для этого можно использовать RefCntHolder:
		 * @code
		 * struct someStruct
		 * {
		 * 	void setObj(IRefCountableObj *obj)
		 * 	{
		 * 		local = obj;
		 * 	}
		 * 	RefCntHolder<IRefCountableObj> local;
		 * };
		 * @endcode
		 * 
		 * <li> Если мы создаем объект сами, или с помощью фабрики, или получаем из какой-то
		 * 		функции, то увеличивать счетчик ссылок не требуется. Когда объект больше не нужен
		 * 		следует вызвать release():
		 * @code
		 * void someFunc()
		 * {
		 * 	IRefCountable *obj = createSomeObject();
		 * 	...
		 * 	obj->release();
		 * }
		 * @endcode
		 * Или можно использовать RefCntHolder в паре с функцией CreateRFHolder:
		 * @code
		 * void someFunc()
		 * {
		 * 	RefCntHolder<IRefCountableObj> obj = CreateRFHolder(createSomeObject());
		 * 	...
		 *	// Объект освободится автоматически
		 * }
		 * @endcode
		 * <li> При возвращении объекта из функции следует увеличить счетчик
		 * 		(разумеется, если если у нас все еще остается ссылка на него):
		 * @code
		 * struct someStruct
		 * {
		 * 	IRefCountable *getObj()
		 * 	{
		 * 		local->addRef();
		 * 		return local;
		 * 	}
		 * 	IRefCountable *local;
		 * };
		 * @endcode
		 * <li> При передаче объекта функции ничего делать требуется:
		 * @code
		 * ...
		 * callSomeFunc(obj);
		 * ...
		 * @endcode
		 * </ol>
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

			/** Увеличивает счетчик ссылок на 1 */
			RefCount_t addRef() const
			{
				return atomicIncrAndFetchInt(&refCount);
			}

			/** Уменьшает счетчик ссылок на 1. При достижении счетчиком нуля вызывается destroyThis() */
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

			/** Возвращает текущее значение счетчика */
			RefCount_t getCounter() const
			{
				return refCount;
			}

		private:
			mutable RefCount_t refCount;

		protected:
			/**
			 * Следует переопределить эту функцию, если не следует удалять объект
			 * при обнулении счетчика.
			 */
			virtual void destroyThis()
			{
				delete this;
			}
		};
		
		/**
		 * \brief RefCntHolder используется для хранения IRefCountable объектов.
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
			
			RefCntHolder(const RefCntHolder<T> &o)
			{
				ptr = o.ptr;
				if (ptr)
					ptr->addRef();
			}
			
			~RefCntHolder()
			{
				if (ptr)
					ptr->release();
			}
			
			RefCntHolder<T> &operator = (T *t)
			{
				if (ptr)
					ptr->release();
				
				ptr = t;
				
				if (ptr)
					ptr->addRef();
				
				return *this;
			}
			
			RefCntHolder<T> &operator = (const RefCntHolder<T> &o)
			{
				if (ptr)
					ptr->release();
				
				ptr = o.ptr;
				
				if (ptr)
					ptr->addRef();
				
				return *this;
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
			
			operator const T *() const
			{
				return ptr;
			}
			
			T *operator -> ()
			{
				return ptr;
			}
			
			const T *operator -> () const
			{
				return ptr;
			}
			
		private:
			T *ptr;
		};
		
		/**
		 * \brief Данную функцию следует использовать для сохранения
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
