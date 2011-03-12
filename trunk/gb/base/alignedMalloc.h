/**
 * Функции для выделения выровненной памяти.
 * На самом деле в большинстве случаев можно применять
 * обычные new или malloc, так как стандарт определяет, что
 * их возвращаемые значения должны быть достаточно
 * выровненны для всех базовых типов данных.
 * Например согласно http://msdn.microsoft.com/en-us/library/ycsb6wwf(v=vs.80).aspx
 * malloc для VC должен возвращать блок памяти
 * выровненный по границе 16 байт.
 */


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