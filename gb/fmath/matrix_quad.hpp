// matrix_quad.hpp


#ifndef __MATRIX_QUAD_HPP__
#define __MATRIX_QUAD_HPP__


#pragma once

#ifndef __GB_FMATH_H__
    #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif

//#include "matrix.hpp"

namespace gb
{

	namespace fmath
	{
	
 
	template <typename T, size_t N>
	struct matrix_quad : public  matrix<T, N, N> {
	   // .....
	}; 








	
	
	}
}

#endif // __MATRIX_QUAD_HPP__