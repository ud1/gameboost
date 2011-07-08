#pragma once
#include <gb/base/nullptr.h>
#include <gb/base/IRefCountable.h>

namespace gb
{
	namespace base
	{
		template<typename T>
		RefCntHolder<T> inject();
		
		
		template<typename T>
		struct AutoInjection
		{
			RefCntHolder<T> operator = (RefCntHolder<T> v)
			{
				ptr = v;
				return ptr;
			}
			
			RefCntHolder<T> &get()
			{
				if (!ptr)
					ptr = inject<T>();
				
				return ptr;
			}
			
			RefCntHolder<T> &operator -> ()
			{
				return get();
			}
		
		private:
			RefCntHolder<T> ptr;
		};
		
	}
}
