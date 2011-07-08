#pragma once

#include "Plane.h"
#include <gb/math/math.h>

namespace gb
{
	namespace math
	{
		struct Frustum
		{
			Plane planes[6];

			void setup(const mat4 &MVP);
			
			bool isPointInsideFrustum(const vec3 &point) const
			{
				for (int i = 0; i < 6; ++i)
				{
					if (!planes[i].isPointInside(point))
						return false;
				}
				return true;
			}

			eIntersectionType::IntersectionType CheckBBox(const BBox &box) const
			{
				bool inside = true;
			
				for (int i = 0; i < 6; ++i)
				{
					eIntersectionType::IntersectionType r = planes[i].checkBBox(box);
					if (r == eIntersectionType::OUTSIDE)
						return eIntersectionType::OUTSIDE;
					
					if (r == eIntersectionType::INTERSECTING)
						inside = false; 
				}
				
				if (inside)
					return eIntersectionType::INSIDE;
				
				return eIntersectionType::INTERSECTING;
			}
		};
	}
}
