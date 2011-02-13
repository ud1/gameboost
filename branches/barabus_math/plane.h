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
		// class Plane
		//
		//----------------------------------------------------------------------

		class Plane {

		public:
			
			Vector3f normal;
			float dist;

			Plane() : normal(0.0f, 0.0f, 1.0f), dist(0.0f) { }
			Plane(const Vector3f &n, float d) : normal(n), dist(d) { }
			
			Plane(const Vector3f &, const Vector3f &)
			{
				normal = n;
				setOrigin(o);
			}

			inline Vector3f getOrigin()
			{
			
			}
			
			inline void setOrigin(const Vector3f &o)
			{
				dist = -dot(normal, o);
			}

			inline void normalize()
			{
				float len = normal.length();

				if (len > 1e-6) {
					normal /= len;
					dist /= len;
				}
			}
			
			inline friend Plane normalize(const Plane &)
			{
				float len = p.normal.length();

				if (len > 1e-6) {
					float ilen = 1.0 / len;
					return Plane(p.normal * ilen, p.dist * ilen);
				}
				return p;
			}
			
			inline bool trace(const Line &l, TracePoint &i, bool fix_src = true, bool fix_dst = false) const
			{
				float cosang = 0;
				float d = 0;
				float lamda = 0;

				vec3 dir = l.getDirection();
				cosang = dot(dir, normal);

				if (cosang > -EPSILON && cosang < EPSILON) return false;

				d = dot(l.src, normal);

				lamda = (-dist - d) / cosang;

				if ((fix_src && lamda < 0) || (fix_dst && lamda > 1)) return false;

				i.point = l.src + dir * lamda;
				i.normal = normal;

				return true;
			
			}
			
		};
		
		//----------------------------------------------------------------------
		
	}
	
	//--------------------------------------------------------------------------
	
}
