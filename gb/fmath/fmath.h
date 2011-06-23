/** \file fmath.h
 \brief Для включения всех fmath-либ.
*
*
*

\todo  Поменять ассерты на исключения  
\todo  Поправить операторы для сравнения по эпсилону.
\todo  Перенести в cpp методы матрицы 4x4 .
\todo  Тяжелые методы матриц перенести в cpp
\todo  удалить собственные #ifdef XXXXXX
\todo  Поправить макрозащиту на типы RECT и POINT
\todo Добавить каст к типам OpenGL
\todo print() поменять на << 

*
*
*/

  #pragma once
#define __GB_FMATH_H__
 
#include <math.h>
#include <limits>
#include <float.h>
#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <string>
#include <stdexcept>

#include <assert.h>
 
#ifdef _WIN32
	#if _MSC_VER<1600
		 #include <xmath.h>
	#endif
#endif
 

#pragma  warning(push)
#pragma  warning(disable : 4995)
#pragma  warning(disable : 4996)
#pragma  warning(disable : 4290)

#include <gb/base/Types.h>
#include <gb/base/Point.h>
#include <gb/base/Rectangle.h>

 
#include <gb/fmath/fmath_forward_decl.h>
#include <gb/fmath/scalar.h>
#include <gb/fmath/vectors.h>
#include <gb/fmath/matrices.h>
#include <gb/fmath/matrix_stack.h>
#include <gb/fmath/quaternion.h>
#include <gb/fmath/geom2d.h>
#include <gb/fmath/geom3d.h>
#include <gb/fmath/proj.h>
#include <gb/fmath/context.h>


 
#pragma  warning(pop)
// end file