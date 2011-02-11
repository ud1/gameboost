/*! \file Debug.h
 *	Отладочные функции и макросы
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */
#pragma once

#include <gb/Config.h>

#include <iostream>


// GB_ASSERT_TYPE=0 - ничего
// GB_ASSERT_TYPE=1 - Вывод ошибки в лог и __debugbreak() (MSVC only) или стандартный assert
// GB_ASSERT_TYPE=2 - Вывод ошибки в лог и вызов gameboostAssertionFailed() определённой пользователем
// GB_ASSERT_TYPE=3 - Вывод ошибки в лог и бросок исключения GB_ASSERT_3_EXCEPTION_CLASS
// GB_ASSERT_TYPE=4 - Стандартный виндовый _ASSERTE (Win32 only)
#define GB_ASSERT_TYPE 4

#define GB_ASSERT_3_EXCEPTION_CLASS std::exception

//! Переопределить эту функцию, чтобы ASSERT-ам было куда писать логи. Можно просто возвращать std::cerr
extern std::ostream & gameboostGetLogStream();


#if GB_ASSERT_TYPE == 0
#define GBASSERT(COND) (void)0
#endif


#if GB_ASSERT_TYPE == 1
	#ifdef _WIN32
		#define GBASSERT(COND) if (!(COND)) { \
			gameboostGetLogStream() << __FILE__ << ":" << __LINE__ << " ASSERTION FAILED: " #COND; \
			__debugbreak(); }
	#else
		#include <assert.h>
		#define GBASSERT(COND) if (!(COND)) { \
			gameboostGetLogStream() << __FILE__ << ":" << __LINE__ << " ASSERTION FAILED: " #COND; \
			assert( COND ); }
	#endif
#endif


#if GB_ASSERT_TYPE == 2
extern void gameboostAssertionFailed( const char * reason, const char * file, int line )
#define GBASSERT(COND) if (!(COND)) { \
	gameboostGetLogStream() << __FILE__ << ":" << __LINE__ << " ASSERTION FAILED: " #COND; \
	::gameboostAssertionFailed( #COND, __FILE__, __LINE__ ); \
	}
#endif


#if GB_ASSERT_TYPE == 3
#define GBASSERT(COND) if (!(COND)) { \
	gameboostGetLogStream() << __FILE__ << ":" << __LINE__ << " ASSERTION FAILED: " #COND; \
	throw GB_ASSERT_3_EXCEPTION_CLASS(); \
	}
#endif


#if GB_ASSERT_TYPE == 4
	#ifdef _WIN32
		#include <crtdbg.h>
		#define GBASSERT _ASSERTE
	#else
		#error Win32 Only GB_ASSERT_TYPE = 4 (ASSERTE macro)
	#endif
#endif

namespace gb
{
	namespace base
	{


	} // namespace base
} // namespace gb
