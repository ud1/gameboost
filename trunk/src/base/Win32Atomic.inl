#include "base/Atomic.h"

#if defined(_WIN32)
#include <Windows.h>
#include <intrin.h>

namespace gb
{
	namespace base
	{

	inline void atomicIncrInt(atomic_int_t *ptr)
	{
		_InterlockedIncrement(ptr);
	}

	inline void atomicDecrInt(atomic_int_t *ptr)
	{
		_InterlockedDecrement(ptr);
	}

	inline atomic_int_t atomicAddAndFetchInt(atomic_int_t *ptr, atomic_int_t val)
	{
		return _InterlockedExchangeAdd(ptr, val);
	}

	inline atomic_int_t atomicIncrAndFetchInt(atomic_int_t *ptr)
	{
		return _InterlockedIncrement(ptr);
	}

	inline atomic_int_t atomicDecrAndFetchInt(atomic_int_t *ptr)
	{
		return _InterlockedDecrement(ptr);
	}

	inline atomic_int_t atomicCASInt(atomic_int_t *ptr, atomic_int_t old_val, atomic_int_t new_val)
	{
		return _InterlockedCompareExchange(ptr, new_val, old_val);
	}

	inline atomic_int_t atomicCAS2Int(atomic_int_t *ptr, atomic_int_t old_val, atomic_int_t new_val)
	{
		atomic_int_t original, result;
		do {
			original = *ptr;
			result = (original != old_val ? new_val : original);
		} while(_InterlockedCompareExchange(ptr, result, original) != original);

		return original;
	}
	
	} // namespace base
} // namespace gb

#endif