#pragma once

namespace gb
{
	namespace base
	{
		typedef long atomic_int_t;

		void atomicIncrInt(atomic_int_t *ptr);
		void atomicDecrInt(atomic_int_t *ptr);
		atomic_int_t atomicAddAndFetchInt(atomic_int_t *ptr, int atomic_int_t);
		atomic_int_t atomicIncrAndFetchInt(atomic_int_t *ptr);
		atomic_int_t atomicDecrAndFetchInt(atomic_int_t *ptr);

		// if *ptr == old_val then *ptr = new_val
		// returns old *ptr value
		atomic_int_t atomicCASInt(atomic_int_t *ptr, atomic_int_t old_val, atomic_int_t new_val);
	
		// if *ptr != old_val then *ptr = new_val
		// returns old *ptr value
		atomic_int_t atomicCAS2Int(atomic_int_t *ptr, atomic_int_t old_val, atomic_int_t new_val);
	}
}

#ifdef _WIN32
#include "Win32Atomic.inl"
#else
#include <gb/base/LinuxAtomic.inl>
#endif