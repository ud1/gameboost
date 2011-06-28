#pragma once

#include <gb/math/math.h>
#include <cassert>

namespace gb
{
	namespace math
	{
		
		struct BBox
		{
			vec3 corner, size;
			
			BBox(const vec3 &corner, const vec3 &size)
			{
				this->corner = corner;
				this->size = size;
			}

			vec3 getVertex(int n) const
			{
				assert(n >= 0 && n < 8);
				
				switch (n)
				{
					case 0:
						return corner;
					case 1:
						return corner + vec3(size.x, 0.0f, 0.0f);
					case 2:
						return corner + vec3(0.0f, size.y, 0.0f);
					case 3:
						return corner + vec3(size.x, size.y, 0.0f);
					case 4:
						return corner + vec3(0.0f, 0.0f, size.z);
					case 5:
						return corner + vec3(size.x, 0.0f, size.z);
					case 6:
						return corner + vec3(0.0f, size.y, size.z);
					case 7:
						return corner + vec3(size.x, size.y, size.z);
				}
			}
		};
		
	}
}
