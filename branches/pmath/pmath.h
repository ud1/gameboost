#ifndef PMATH_HEADER
#define PMATH_HEADER

#include <assert.h>
#include <math.h>
#include <algorithm>
#include <float.h>
#include <limits>

#include <cmath>
#include <utility>

namespace gb
{

#include "defines.h"
#include "Algorithm.h"
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Rect.h"
#include "Box.h"
#include "Line.h"
#include "Ray.h"

}

namespace gb
{
	namespace pmath
	{

typedef Matrix<float,4> mat4;
typedef Matrix<float,3> mat3;
typedef Matrix<float,2> mat2;
typedef Vector<float,4> vec4;
typedef Vector<float,3> vec3;
typedef Vector<float,2> vec2;
typedef Box<vec2>		box2;
typedef Box<vec3>		box3;
typedef Line<vec2>		line2;
typedef Line<vec3>		line3;
typedef Ray<vec2>		ray2;
typedef Ray<vec3>		ray3;
	}
}

#endif // PMATH_HEADER