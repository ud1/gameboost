#pragma once

#include <cstdlib>

namespace gb
{
	namespace base
	{
		void *alignedMalloc(size_t size, size_t alignment);
		void alignedFree(void *ptr);
	}
}