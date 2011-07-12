#pragma once

#include <gb/math/math.h>

#include <boost/mpl/int.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace gb
{
	namespace math
	{
		
		template<typename T>
		struct rows_number : public boost::mpl::int_<1> {};
		
		template <>
		struct rows_number<mat3> : public boost::mpl::int_<3> {};
		
		template <>
		struct rows_number<mat4> : public boost::mpl::int_<4> {};
		
		
		template<typename T>
		struct columns_number : public boost::mpl::int_<1> {};
		
		template <>
		struct columns_number<mat3> : public boost::mpl::int_<3> {};
		
		template <>
		struct columns_number<mat4> : public boost::mpl::int_<4> {};
		
		
		template <typename T>
		struct is_floating_point_type : public boost::mpl::bool_<false> {};
		
		template <>
		struct is_floating_point_type<mat3> : public boost::false_type {};
		
		template <>
		struct is_floating_point_type<mat4> : public boost::true_type {};
	}
}