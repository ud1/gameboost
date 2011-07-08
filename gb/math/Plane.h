#pragma once

#include "math.h"
#include "IntersectionType.h"
#include "BBox.h"

namespace gb
{
	namespace math
	{
		struct Plane
		{
			vec3 normal; 
			vec_t dist;
			
			bool isPointInside(const vec3 &p) const
			{
				vec_t r = dot(normal, p) + dist;
				if (r <= 0.0f)
					return false;
				
				return true;
			}

			eIntersectionType::IntersectionType checkBBox(const BBox &box) const
			{
				bool is_inside = false;
				bool is_outside = false;
				
				for (int i = 0; i < 8; ++i)
				{
					if (isPointInside(box.getVertex(i)))
					{
						is_inside = true;
						if (is_inside)
							return eIntersectionType::INTERSECTING;
					}
					else
					{
						is_outside = true;
						if (is_outside)
							return eIntersectionType::INTERSECTING;
					}
				}
				
				if (is_inside)
					return eIntersectionType::INSIDE;
				
				return eIntersectionType::OUTSIDE;
			}
		};
		
	}
}
