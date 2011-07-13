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
 
#define _USE_MATH_DEFINES
#include <math.h>

#include <limits>
#include <float.h>
#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <string>
#include <istream>
#include <ostream>
#include <stdexcept>

#include <assert.h>
 
#ifdef _WIN32
	#if _MSC_VER<1600
		 #include <xmath.h>
	#endif
#endif
 

#ifdef _MSC_VER
#pragma  warning(push)
#pragma  warning(disable : 4995)
#pragma  warning(disable : 4996)
#pragma  warning(disable : 4290)
#endif


#include "../base/Types.h"
#include "../base/Point.h"
#include "../base/Rectangle.h"

 
#include "fmath_forward_decl.h"
#include "scalar.h"


#include "vectors.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"


#include "matrices.h"
#include "matrix22.h"
#include "matrix33.h"
#include "matrix44.h"


#include "matrix_stack.h"
#include "quaternion.h"


//  Наполнение на основе выложеного ребятами в папку бранч,  
//	опенсурсных движков,   выуженого из гугла , своих наработок.


#include "geom2d.h"

#include "geom3d.h"


#include "proj.h"
#include "context.h"


#ifdef _MSC_VER
#pragma  warning(pop)
#endif

// do include static lib for VC
#if GB_LIB
	#ifndef _LIB_GB_FMATH
		#ifdef _DEBUG
				#pragma comment( lib , "gb_fmath_d.lib" )
		#else
				#pragma comment( lib , "gb_fmath.lib" )
		#endif
	#endif
#endif


// end file