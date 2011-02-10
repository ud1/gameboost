#pragma once

// Отключить SSE инструкции для совместимости
#define GB_NO_SIMD 0

// Запретить использование Boost (http://boost.org)
#define GB_ALLOW_BOOST_LIBRARY 0


// microsoft specific
#ifdef _MSC_VER
	#pragma warning(disable:4996)
	#pragma warning(disable:4273)
	#pragma warning(disable:4049)
	#pragma warning(disable:4554)

	#ifdef _DEBUG
		#define _CRTDBG_MAP_ALLOC
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif
#endif
// end microsoft specific
