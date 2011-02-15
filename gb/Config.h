#pragma once

// GB_ASSERT_TYPE=0 - ничего
// GB_ASSERT_TYPE=1 - Вывод ошибки в лог и __debugbreak() (MSVC only) или стандартный assert
// GB_ASSERT_TYPE=2 - Вывод ошибки в лог и вызов gameboostAssertionFailed() определённой пользователем
// GB_ASSERT_TYPE=3 - Вывод ошибки в лог и бросок исключения GB_ASSERT_3_EXCEPTION_CLASS
// GB_ASSERT_TYPE=4 - Стандартный виндовый _ASSERTE (Win32 only)
#ifdef _DEBUG
#define GB_ASSERT_TYPE 1
#else
#define GB_ASSERT_TYPE 0
#endif

#define GB_LOGGER_TYPE gb::base::ConsoleLogger

// LOG_LEVEL Сооствествует gb::base::eLogType::LogType
#define GB_LOG_LEVEL 0

// Отключить SSE инструкции для совместимости
#define GB_NO_SIMD 0

// Запретить использование Boost (http://boost.org)
#define GB_ALLOW_BOOST_LIBRARY 1

// Включить поддержку классами Boost.Serialize
#define GB_ENABLE_BOOST_SERIALIZE 1

// Для того, чтоб WinDef.h не определял макросы min/max, мы используем расово верные макросы из <algorithm>
#define NOMINMAX 1

// microsoft specific
#ifdef _MSC_VER
	#pragma warning(disable:4996)
	#pragma warning(disable:4273)
	#pragma warning(disable:4049)
	#pragma warning(disable:4554)

	#ifdef _DEBUG
		// включение этого макроса вызывает проблемы в boost/pool, boost/segregated_storage
		// поскольку там создаётся функция malloc, и этот флаг её превращает в макрос
		//#define _CRTDBG_MAP_ALLOC

		#include <stdlib.h>
		#include <crtdbg.h>
	#endif
#endif
// end microsoft specific
