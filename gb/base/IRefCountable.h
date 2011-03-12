#pragma once

#include <gb/base/Atomic.h>
#include <cstdlib>

namespace gb
{
	namespace base
	{

		class IRefCountable
		{
		public:

			typedef base::atomic_int_t RefCount_t;

			IRefCountable()
			{
				refCount = 1;
			}

			virtual ~IRefCountable() {}

			RefCount_t addRef()
			{
				return atomicIncrAndFetchInt(&refCount);
			}

			RefCount_t release()
			{
				RefCount_t count = atomicDecrAndFetchInt(&refCount);
				if (count <= 0)
				{
					destroyThis();
					return 0;
				}
				return refCount;
			}

			RefCount_t getCounter() const
			{
				return refCount;
			}

		private:
			RefCount_t refCount;

		protected:
			// override this if you do not want to destroy object
			virtual void destroyThis()
			{
				delete this;
			}
		};
		
		template <typename T>
		struct RefCntHolder
		{
			RefCntHolder()
			{
				ptr = NULL;
			}
			
			RefCntHolder(T *t)
			{
				ptr = t;
				if (ptr)
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

	} // namespace
} // namespace
