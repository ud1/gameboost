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
#include "Algorytm.h"
#include "Vector.h"
#include "Quaternion.h"
#include "Matrix.h"
#include "Rect.h"
#include "AABBox.h"
#include "Ray.h"

}

namespace gb
{
	namespace pmath
	{

typedef Matrix<float,4> mat4;
typedef Vector<float,4> vec4;
typedef Vector<float,3> vec3;
typedef Vector<float,2> vec2;
	}
}

#endif // PMATH_HEADER