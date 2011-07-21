/** \file math.h
 \brief Для включения всех math-либ.
*
*
     вся fixed-математика перенесена в пространство gb::fmath
  чтобы никому не мазолила глаза

*
*/

#pragma once
#define __GB_MATH_H__

#include "../Config.h"

#include <math.h>
#include <limits>

#ifdef _WIN32
#if _MSC_VER<1600
    #include <xmath.h>
#endif
#endif
 
#pragma  warning(push)
#pragma  warning(disable : 4995)

#include <gb/base/nullptr.h>
 
// Временно подключаем glm, так как не вся математика реализованна
// http://glm.g-truc.net/
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gb
{
	namespace math
	{
		using namespace glm;
		
		typedef vec3::value_type vec_t;
		
		inline int ilog2(int v)
		{
			int lev = sizeof(int)*8 - 1;
			for (; lev; --lev)
			{
				int val = 1 << lev;
				if (v & val)
					return lev;
			}
			return 0;
		}
		
		// FIXME Надо сделать все по нормальному
		inline float const * value_ptr(const int &vec)
		{
			return nullptr;
		}
		
		inline float const * value_ptr(const vec2 &v)
		{
			return &v.x;
		}
		
		inline float const * value_ptr(const vec3 v)
		{
			return &v.x;
		}
	}
}

#pragma  warning(pop)
// end file