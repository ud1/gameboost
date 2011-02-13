//------------------------------------------------------------------------------
//
// GameBoost
//
// copyright:	(c) 2011 GameDev.ru
// authors:		Alexey Egorov (FadeToBlack aka EvilSpirit) anandamide@mail.ru
//
// url:			http://gameboost.googlecode.com/
//				http://www.gamedev.ru/community/gameboost
//
//------------------------------------------------------------------------------

#include "Overlaps.h"

//------------------------------------------------------------------------------

#include "Distances.h"

//------------------------------------------------------------------------------
//
// namespace gb
//
//------------------------------------------------------------------------------

namespace gb
{

	//--------------------------------------------------------------------------
	//
	// namespace base
	//
	//--------------------------------------------------------------------------
	
	namespace base
	{
		
		//----------------------------------------------------------------------
		
		bool overlaps(const BSphere &s0, const BSphere &s1) {
			return distance(s0.center, s1.center) < s0.radius + s1.radius;
		}

		//----------------------------------------------------------------------

		bool overlaps(const BBox &b0, const BBox &b1) {

			vec3 t = b1.getOrigin() - b0.getOrigin();
			vec3 e = b1.getExtents() + b0.getExtents();

			return math::abs(t.x) < e.x && math::abs(t.y) < e.y && math::abs(t.z) < e.z;
		}

		//----------------------------------------------------------------------

		bool overlaps(const BSphere &s, const BBox &b) {

			float d = 0;
			float a;

			for (int i=0; i<3; i++) {

				if (s.center[i] < b.min[i]) {
					a = s.center[i] - b.min[i];
					d += a * a;
				}

				if (s.center[i] > b.max[i]) {
					a = s.center[i] - b.max[i];
					d += a * a;
				}
			}

			return d <= (s.radius * s.radius);
		}

		//----------------------------------------------------------------------

		bool overlapsExact(const BSphere &s, const BBox &b, const mat4 &transform) {

			vec3 tmin = transform * b.min;
			vec3 tmax = transform * b.max;
			vec3 pos = transform * vec3(0.0f, 0.0f, 0.0f);
			vec3 normal[3];
			normal[0] = normalize(transform * vec3(1, 0, 0) - pos);
			normal[1] = normalize(transform * vec3(0, 1, 0) - pos);
			normal[2] = normalize(transform * vec3(0, 0, 1) - pos);

			float d = 0;
			float a;

			for (int i=0; i<3; i++) {

				a = distance(Plane(normal[i], tmax), s.center);
				if (a > 0) d += a * a;

				a = distance(Plane(-normal[i], tmin), s.center);
				if (a > 0) d += a * a;
			}

			return d <= (s.radius * s.radius);

		}
		
		//----------------------------------------------------------------------

		bool overlaps(const BSphere &s, const BBox &b, const mat4 &transform) {

			vec3 tmin = transform * b.min;
			vec3 tmax = transform * b.max;
			vec3 pos = transform * vec3(0.0f, 0.0f, 0.0f);
			vec3 normal[3];
			normal[0] = normalize(transform * vec3(1, 0, 0) - pos);
			normal[1] = normalize(transform * vec3(0, 1, 0) - pos);
			normal[2] = normalize(transform * vec3(0, 0, 1) - pos);

			float a;

			for (int i=0; i<3; i++) {

				a = distance(Plane(normal[i], tmax), s.center);
				if (a > s.radius) return false;

				a = distance(Plane(-normal[i], tmin), s.center);
				if (a > s.radius) return false;
			}

			return true;

		}

		//----------------------------------------------------------------------

		bool overlaps(const BBox &a, const mat4 &aInvTransform, const BBox &b, const mat4 &bTransform) {

			mat4 matB = bTransform * aInvTransform;
			vec3 vPosB = matB * vec3();

			vec3 XAxis = vec3(matB.data[0][0], matB.data[1][0], matB.data[2][0]);
			vec3 YAxis = vec3(matB.data[0][1], matB.data[1][1], matB.data[2][1]);
			vec3 ZAxis = vec3(matB.data[0][2], matB.data[1][2], matB.data[2][2]);
			vec3 aBounds = a.getExtents();
			vec3 bBounds = b.getExtents();

			//15 tests
			//1 (Ra)x
			if( fabs(vPosB.x) > aBounds.x + bBounds.x * fabs(XAxis.x) + bBounds.y * fabs(XAxis.y) + bBounds.z * fabs(XAxis.z))
				return false;

			//2 (Ra)y
			if(fabs(vPosB.y) > aBounds.y + bBounds.x * fabs(YAxis.x) + bBounds.y * fabs(YAxis.y) + bBounds.z * fabs(YAxis.z))
				return false;
			//3 (Ra)z
			if(fabs(vPosB.z) > aBounds.z + bBounds.x * fabs(ZAxis.x) + bBounds.y * fabs(ZAxis.y) + bBounds.z * fabs(ZAxis.z))
				return false;

			//4 (Rb)x
			if(fabs(vPosB.x * XAxis.x + vPosB.y * YAxis.x + vPosB.z * ZAxis.x) >
				(bBounds.x + aBounds.x * fabs(XAxis.x) + aBounds.y * fabs(YAxis.x) + aBounds.z * fabs(ZAxis.x)))
				return false;
			//5 (Rb)y
			if(fabs(vPosB.x * XAxis.y + vPosB.y * YAxis.y + vPosB.z * ZAxis.y) >
				(bBounds.y + aBounds.x * fabs(XAxis.y) + aBounds.y * fabs(YAxis.y) + aBounds.z * fabs(ZAxis.y)))
				return false;
			//6 (Rb)z
			if(fabs(vPosB.x * XAxis.z + vPosB.y * YAxis.z + vPosB.z * ZAxis.z) >
				(bBounds.z + aBounds.x * fabs(XAxis.z) + aBounds.y * fabs(YAxis.z) + aBounds.z * fabs(ZAxis.z)))
				return false;

			//7 (Ra)x X (Rb)x
			if(fabs(vPosB.z * YAxis.x - vPosB.y * ZAxis.x) > aBounds.y * fabs(ZAxis.x) +
				aBounds.z * fabs(YAxis.x) + bBounds.y * fabs(XAxis.z) + bBounds.z * fabs(XAxis.y))
				return false;
			//8 (Ra)x X (Rb)y
			if(fabs(vPosB.z * YAxis.y - vPosB.y * ZAxis.y) > aBounds.y * fabs(ZAxis.y) +
				aBounds.z * fabs(YAxis.y) + bBounds.x * fabs(XAxis.z) + bBounds.z * fabs(XAxis.x))
				return false;
			//9 (Ra)x X (Rb)z
			if(fabs(vPosB.z * YAxis.z - vPosB.y * ZAxis.z) > aBounds.y * fabs(ZAxis.z) +
				aBounds.z * fabs(YAxis.z) + bBounds.x * fabs(XAxis.y) + bBounds.y * fabs(XAxis.x))
				return false;

			//10 (Ra)y X (Rb)x
			if(fabs(vPosB.x * ZAxis.x - vPosB.z * XAxis.x) > aBounds.x * fabs(ZAxis.x) +
				aBounds.z * fabs(XAxis.x) + bBounds.y * fabs(YAxis.z) + bBounds.z * fabs(YAxis.y))
				return false;
			//11 (Ra)y X (Rb)y
			if(fabs(vPosB.x * ZAxis.y - vPosB.z * XAxis.y) > aBounds.x * fabs(ZAxis.y) +
				aBounds.z * fabs(XAxis.y) + bBounds.x * fabs(YAxis.z) + bBounds.z * fabs(YAxis.x))
				return false;
			//12 (Ra)y X (Rb)z
			if(fabs(vPosB.x * ZAxis.z - vPosB.z * XAxis.z) > aBounds.x * fabs(ZAxis.z) +
				aBounds.z * fabs(XAxis.z) + bBounds.x * fabs(YAxis.y) + bBounds.y * fabs(YAxis.x))
				return false;

			//13 (Ra)z X (Rb)x
			if(fabs(vPosB.y * XAxis.x - vPosB.x * YAxis.x) > aBounds.x * fabs(YAxis.x) +
				aBounds.y * fabs(XAxis.x) + bBounds.y * fabs(ZAxis.z) + bBounds.z * fabs(ZAxis.y))
				return false;
			//14 (Ra)z X (Rb)y
			if(fabs(vPosB.y * XAxis.y - vPosB.x * YAxis.y) > aBounds.x * fabs(YAxis.y) +
				aBounds.y * fabs(XAxis.y) + bBounds.x * fabs(ZAxis.z) + bBounds.z * fabs(ZAxis.x))
				return false;
			//15 (Ra)z X (Rb)z
			if(fabs(vPosB.y * XAxis.z - vPosB.x * YAxis.z) > aBounds.x * fabs(YAxis.z) +
				aBounds.y * fabs(XAxis.z) + bBounds.x * fabs(ZAxis.y) + bBounds.y * fabs(ZAxis.x))
				return false;

			return true;
		}

		//----------------------------------------------------------------------

		bool overlaps(const BBox &box, const Frustum &frustum) {

			for (int i=0; i<6; i++) {
				int j = 0;
				for (j=0; j<8; j++) {
					float dist = distance(frustum.getPlane(i), box.getVertex(j));
					if (dist > -EPSILON) {
						break;
					}
				}
				if (j == 8) {
					return false;
				}
			}
			return true;
		}

		//----------------------------------------------------------------------

		bool overlaps(const BBox &box, const mat4 &boxTransform, const Frustum &frustum) {
			static vec3 vertex[8];

			for (int i=0; i<8; i++) {
				vertex[i] = boxTransform * box.getVertex(i);
			}

			for (int i=0; i<6; i++) {
				int j = 0;
				for (j=0; j<8; j++) {
					float dist = distance(frustum.getPlane(i), vertex[j]);
					if (dist > -EPSILON) {
						break;
					}
				}
				if (j == 8) {
					return false;
				}
			}
			return true;
		}

		//----------------------------------------------------------------------

		bool overlaps(const BSphere &sphere, const Frustum &frustum) {

			for (int i=0; i<6; i++) {
				if (distance(frustum.getPlane(i), sphere.center) < -sphere.radius) {
					return false;
				}
			}
			return true;
		}
		
	}
	
	//--------------------------------------------------------------------------
	
}
