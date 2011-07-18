
#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__


#pragma once

#ifndef __GB_FMATH_H__
    #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif

#include <boost/array.hpp>
#include <iostream>
#include <string>

namespace gb
{

	namespace fmath
	{

	template <typename T, size_t NumColumns, size_t NumRows>
	struct matrix : public boost::array< T , NumColumns * NumRows > {
	  /// ....
 


	};






	}

}

#endif // __MATRIX_HPP__