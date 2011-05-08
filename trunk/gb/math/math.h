/** \file math.h
 \brief Для включения всех math-либ.
*
*
*
*/

#pragma once
#define __GB_MATH_H__

#include <gb/Config.h>

#include <math.h>

#ifdef _WIN32
#include <xmath.h>
#endif

#ifdef GB_D3D9
    #include <d3d9.h>
#endif 

#ifdef GB_D3DX9
    #include <d3dx9math.h>
#endif 

#pragma  warning(push)
#pragma  warning(disable : 4995)
 

#include <gb/math/forw_decl.h>
#include <gb/math/scalar.h>
#include <gb/math/base.h>
#include <gb/math/geom2d.h>
// #include <gb/math/geom3d.h>
#include <gb/math/proj.h>




// Временно подключаем glm, так как не вся математика реализованна
// http://glm.g-truc.net/
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform2.hpp>

namespace gb
{
	namespace math
	{
		using namespace glm;
		
		typedef vec3::value_type vec_t;
	}
}

#pragma  warning(pop)
// end file