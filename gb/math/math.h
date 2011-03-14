/** \file math.h
 \brief ��� ��������� ���� math-���.
*
*
*
*/



#include <gb/math/scalar.h>
#include <gb/math/base.h>
#include <gb/math/geom2d.h>
#include <gb/math/geom3d.h>


// �������� ���������� glm, ��� ��� �� ��� ���������� ������������
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/matrix_projection.hpp>

namespace gb
{
	namespace math
	{
		using namespace glm;
		
		typedef vec3::value_type vec_t;
	}
}


// end file