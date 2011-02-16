#pragma once

/*! \file Constants.h
 *	Фундаментальные и вспомогательные константы
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */

#define GB_CONST_E				2.71828182845904523536
#define GB_CONST_PI				3.14159265358979323846
#define GB_CONST_DOUBLE_PI		6.28318530717958647692
#define GB_CONST_HALF_PI		1.57079632679489661923
#define GB_CONST_QUARTER_PI		0.785398163397448309616
#define GB_CONST_INV_PI			0.318309886183790671538
#define GB_CONST_DOUBLE_INV_PI	0.636619772367581343076
#define GB_CONST_SQRT_2			1.41421356237309504880

#define GB_CONST_UINT32MAX		4294967295.0
#define GB_CONST_UINT32MAX_INV	(1.0 / 4294967295.0)
#define GB_CONST_UINT64MAX		18446744073709551615.0
#define GB_CONST_UINT64MAX_INV	(1.0 / 18446744073709551615.0)

namespace gb
{

	double getNaN() {
		unsigned long nan_ulong[2] = {0xffffffff, 0x7fffffff};
		return *( double* )nan_ulong;
	}

} // namespace gb
