#pragma once
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

#ifdef _WIN32
typedef signed		__int32 int32_t;
typedef unsigned	__int32 uint32_t;
typedef signed		__int64 int64_t;
typedef unsigned	__int64 uint64_t;
typedef signed		__int16 int16_t;
typedef unsigned	__int16 uint16_t;
typedef signed		__int8	int8_t;
typedef unsigned	__int8	uint8_t;
#endif

#ifdef MACOSX
#endif

#ifdef __linux
#include <stdint.h>
#endif

using namespace std;
