#pragma once

/*! \file Constants.h
 *	Фундаментальные и вспомогательные константы
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */

namespace gb
{

	double getNaN() {
		unsigned long nan_ulong[2] = {0xffffffff, 0x7fffffff};
		return *( double* )nan_ulong;
	}

#define GB_DECLARE_FLOAT_DOUBLE_CONST( NAME, VALUE ) \
	namespace detail { \
		static const double d_const##NAME = VALUE; \
		static const float f_const##NAME = (float)VALUE; \
	} \
	template <typename value_type> value_type const##NAME(); \
	template<> float const##NAME() { return gb::detail::f_const##NAME; } \
	template<> double const##NAME() { return gb::detail::d_const##NAME; }

	GB_DECLARE_FLOAT_DOUBLE_CONST( E, 2.71828182845904523536 );
	GB_DECLARE_FLOAT_DOUBLE_CONST( Pi, 3.14159265358979323846 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 2_Pi, 6.28318530717958647692 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( Pi_Div_2, 1.57079632679489661923 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( Pi_Div_4, 0.785398163397448309616 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 1_Div_Pi, 0.318309886183790671538 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 2_Div_Pi, 0.636619772367581343076 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( Sqrt_2, 1.41421356237309504880 );

 	GB_DECLARE_FLOAT_DOUBLE_CONST( Uint32Max, 4294967295.0 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 1_Div_Uint32Max, (1.0 / 4294967295.0) );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( Uint64Max, 18446744073709551615.0 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 1_Div_Uint64Max, (1.0 / 18446744073709551615.0) );

#undef GB_DECLARE_FLOAT_DOUBLE_CONST

} // namespace gb
