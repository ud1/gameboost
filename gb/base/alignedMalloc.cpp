#include "alignedMalloc.h"

#ifdef _WIN32
#include <malloc.h>
#else
#include <stdlib.h>
#endif

namespace gb
{
	namespace base
	{

#ifdef _WIN32

		void *alignedMalloc(size_t size, size_t alignment)
		{
			return _aligned_malloc(size, alignment);
		}
		
		void alignedFree(void *ptr)
		{
			_aligned_free(ptr);
		}
		
#else
		
		void *alignedMalloc(size_t size, size_t alignment)
		{
			void *ptr = NULL;
			posix_memalign(&ptr, alignment, size);
			return ptr;
		}
		
		void alignedFree(void *ptr)
		{
			free(ptr);
		}
		
#endif

	}
}