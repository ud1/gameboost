#pragma once
#define __GB_TYPES_H__

#if defined(_MSC_VER) // MS Visual Studio dosen't have stdint.h
	typedef __int8 int8_t;
	typedef unsigned __int8 uint8_t;
	typedef __int16 int16_t;
	typedef unsigned __int16 uint16_t;
	typedef __int32 int32_t;
	typedef unsigned __int32 uint32_t;
	typedef __int64 int64_t;
	typedef unsigned __int64 uint64_t;
#else // maybe elif defined(__GNUC__) || defined(__INTEL_COMPILER)
	#include <stdint.h>
#endif

#ifndef WIN32

typedef struct tagPOINT
{
	long  x;
	long  y;
} POINT, *PPOINT;

typedef struct tagRECT
{
	long    left;
	long    top;
	long    right;
	long    bottom;
} RECT, *PRECT;


typedef uint32_t   BOOL;
#define FALSE  0
#define TRUE   1



#endif // #ifndef WIN32
