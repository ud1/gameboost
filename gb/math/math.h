/** \file math.h
 \brief Для включения всех math-либ.
*
*
*
*/



#include <gb/math/scalar.h>
#include <gb/math/base.h>
#include <gb/math/geom2d.h>
#include <gb/math/geom3d.h>


// Временно подключаем glm, так как не вся математика реализованна
#include <glm/glm.hpp>

namespace gb
{
	namespace math
	{
		
		using glm::ivec2;
		
	}
}


// end file