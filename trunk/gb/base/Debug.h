/*! \file Debug.h
 *	Отладочные функции и макросы
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */
#pragma once

#include <gb/Config.h>
#include <gb/base/Logger.h>
#include <iostream>

#define GB_ASSERT_3_EXCEPTION_CLASS std::exception

#if GB_ASSERT_TYPE == 0
#define GBASSERT(COND) (void)0
#endif


#if GB_ASSERT_TYPE == 1
	#ifdef _WIN32
		#define GBASSERT(COND) if (!(COND)) { \
			ERROR_LOG(__FILE__ << ":" << __LINE__ << " ASSERTION FAILED: " #COND); \
			__debugbreak(); }
	#else
		#include <assert.h>
		#define GBASSERT(COND) if (!(COND)) { \
			ERROR_LOG(__FILE__ << ":" << __LINE__ << " ASSERTION FAILED: " #COND); \
			assert( COND ); }
	#endif
#endif


#if GB_ASSERT_TYPE == 2
extern void gameboostAssertionFailed( const char * reason, const char * file, int line )
#define GBASSERT(COND) if (!(COND)) { \
	ERROR_LOG(__FILE__ << ":" << __LINE__ << " ASSERTION FAILED: " #COND); \
	::gameboostAssertionFailed( #COND, __FILE__, __LINE__ ); \
	}
#endif


#if GB_ASSERT_TYPE == 3
#define GBASSERT(COND) if (!(COND)) { \
	ERROR_LOG(__FILE__ << ":" << __LINE__ << " ASSERTION FAILED: " #COND); \
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
