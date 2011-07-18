// matrix4x4.hpp

#ifndef __MATRIX_4X4_HPP__
#define __MATRIX_4X4_HPP__


#pragma once

#ifndef __GB_FMATH_H__
    #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif

#include "matrix_quad.hpp"


#include <boost/array.hpp>

namespace gb
{

	namespace fmath
	{
	
 

	template <typename T>
	struct matrix4x4 : public matrix_quad<T,4> {
	 /// ....
	 
	};

 


	
	
	}
}

#endif // __MATRIX_4X4_HPP__