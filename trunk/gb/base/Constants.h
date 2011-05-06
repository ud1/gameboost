#pragma once

/*! \file Constants.h
 *	Фундаментальные и вспомогательные константы
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 */
#include <limits>

namespace gb
{

  // старый какой-то .. запутанный .. пока пусть будут макросы 
	
#define GBC_PI   3.1415926535898





	template <typename value_type>
	inline value_type getNaN()
	{
		return std::numeric_limits <value_type>::quiet_NaN();
	}

#define GB_DECLARE_FLOAT_DOUBLE_CONST( NAME ) \
			namespace detail { \
				extern const double d_const##NAME; \
				extern const float f_const##NAME; \
			} \
			template <typename value_type> value_type const##NAME(); \
			template<> inline float const##NAME() { return gb::detail::f_const##NAME; } \
			template<> inline double const##NAME() { return gb::detail::d_const##NAME; }

	GB_DECLARE_FLOAT_DOUBLE_CONST( E );
	GB_DECLARE_FLOAT_DOUBLE_CONST( Pi );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 2_Pi );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( Pi_Div_2 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( Pi_Div_4 );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 1_Div_Pi );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 2_Div_Pi );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( Sqrt_2 );

 	GB_DECLARE_FLOAT_DOUBLE_CONST( Uint32Max );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 1_Div_Uint32Max );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( Uint64Max );
 	GB_DECLARE_FLOAT_DOUBLE_CONST( 1_Div_Uint64Max );

#undef GB_DECLARE_FLOAT_DOUBLE_CONST

} // namespace gb
