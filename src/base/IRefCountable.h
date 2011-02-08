#pragma once

#include "base/Atomic.h"

namespace gb
{
	namespace Base
	{

		class IRefCountable
		{
		public:

			typedef Base::atomic_int_t RefCount_t;

			IRefCountable()
			{
				refCount = 1;
			}

			virtual ~IRefCountable() {}

			RefCount_t addRef()
			{
				return Base::atomicIncrAndFetchInt(&refCount);
			}

			RefCount_t release()
			{
				RefCount_t count = Base::atomicDecrAndFetchInt(&refCount);
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

	} // namespace
} // namespace
