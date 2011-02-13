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

#pragma once

//------------------------------------------------------------------------------

#include "Vector.h"
#include "Line.h"
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
		//
		// class BSphere
		//
		//----------------------------------------------------------------------

		class BSphere {

		public:
			Vector3f center;
			float radius;

			BSphere() : radius(0.0f) { }
			BSphere(const Vector3f &c, float r) : center(c), radius(r) { }
			
			bool trace(const Line &l, TracePoint &r, bool fix_src = true, bool fix_dst = false) const
			{
				vec3 d = l.getDirection();
				vec3 o = l.src;
				vec3 ce = center;

				vec3 av = d * d;
				vec3 bv = d * (o - ce) * 2.0f;
				vec3 cv = o * o + ce * ce - o * ce * 2.0f;

				float a = av.x + av.y + av.z;

				if (math::abs(a) < 1e-6) return false;

				float b = bv.x + bv.y + bv.z;
				float c = cv.x + cv.y + cv.z - radius * radius;

				float disc = b * b - 4.0f * a * c;

				if (disc < 0) return false;

				float i2a = 1.0f / (2.0f * a);

				disc = math::sqrt(disc);

				float t2 = (-b - disc) * i2a;

				if ((fix_src && t2 < 0.0f) || (fix_dst && t2 > 1.0f)) return false;

				r.point = o + d * t2;
				r.normal = normalize(r.point - center);

				return true;
			}
			
			void include(const Vector3f &, float = 0.0f)
			{
				float dist = distance(v, center) + r;
				if (dist > radius) {
					radius = dist;
				}
			}

		};
		
		//----------------------------------------------------------------------
		
	}
	
	//--------------------------------------------------------------------------
	
}
