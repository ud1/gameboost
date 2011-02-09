#include "base/Atomic.h"

#ifndef _WIN32

namespace gb
{
	namespace base
	{

	inline void atomicIncrInt(atomic_int_t *ptr)
	{
		__sync_add_and_fetch(ptr, 1);
	}

	inline void atomicDecrInt(atomic_int_t *ptr)
	{
		__sync_sub_and_fetch(ptr, 1);
	}

	inline atomic_int_t atomicAddAndFetchInt(atomic_int_t *ptr, atomic_int_t val)
	{
		if (val > 0)
			return __sync_add_and_fetch(ptr, val);
		else return __sync_sub_and_fetch(ptr, -val);
	}

	inline atomic_int_t atomicIncrAndFetchInt(atomic_int_t *ptr)
	{
		return __sync_add_and_fetch(ptr, 1);
	}

	inline atomic_int_t atomicDecrAndFetchInt(atomic_int_t *ptr)
	{
		return __sync_sub_and_fetch(ptr, 1);
	}

	inline atomic_int_t atomicCASInt(atomic_int_t *ptr, atomic_int_t old_val, atomic_int_t new_val)
	{
		return __sync_val_compare_and_swap(ptr, old_val, new_val);
	}

	inline atomic_int_t atomicCAS2Int(atomic_int_t *ptr, atomic_int_t old_val, atomic_int_t new_val)
	{
		atomic_int_t original, result;
		do {
			original = *ptr;
			result = (original != old_val ? new_val : original);
		} while(__sync_val_compare_and_swap(ptr, original, result) != original);

		return original;
	}

	} // namespace base
} // namespace gb

#endif
