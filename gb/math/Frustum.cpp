#include "Frustum.h"

namespace gb
{
	namespace math
	{
		
		void Frustum::setup(const mat4 &MVP)
		{
			const vec_t *mat = (const vec_t *) &MVP;
			float t;
			
			// Right plane
			planes[0].normal[0] = mat[ 3] - mat[ 0]; 
			planes[0].normal[1] = mat[ 7] - mat[ 4]; 
			planes[0].normal[2] = mat[11] - mat[ 8]; 
			planes[0].dist = mat[15] - mat[12]; 

			t = 1.0f / length(planes[0].normal); 
			planes[0].normal *= t;
			planes[0].dist *= t; 

			// Left plane
			planes[1].normal[0] = mat[ 3] + mat[ 0]; 
			planes[1].normal[1] = mat[ 7] + mat[ 4]; 
			planes[1].normal[2] = mat[11] + mat[ 8]; 
			planes[1].dist = mat[15] + mat[12]; 

			t = 1.0f / length(planes[1].normal); 
			planes[1].normal *= t;
			planes[1].dist *= t; 

			// Lower plane
			planes[2].normal[0] = mat[ 3] + mat[ 1]; 
			planes[2].normal[1] = mat[ 7] + mat[ 5]; 
			planes[2].normal[2] = mat[11] + mat[ 9]; 
			planes[2].dist = mat[15] + mat[13]; 

			t = 1.0f / length(planes[2].normal); 
			planes[2].normal *= t;
			planes[2].dist *= t; 

			// Upper plane
			planes[3].normal[0] = mat[ 3] - mat[ 1]; 
			planes[3].normal[1] = mat[ 7] - mat[ 5]; 
			planes[3].normal[2] = mat[11] - mat[ 9]; 
			planes[3].dist = mat[15] - mat[13]; 

			t = 1.0f / length(planes[3].normal); 
			planes[3].normal *= t;
			planes[3].dist *= t; 

			// Far plane
			planes[4].normal[0] = mat[ 3] - mat[ 2]; 
			planes[4].normal[1] = mat[ 7] - mat[ 6]; 
			planes[4].normal[2] = mat[11] - mat[10]; 
			planes[4].dist = mat[15] - mat[14]; 

			t = 1.0f / length(planes[4].normal); 
			planes[4].normal *= t;
			planes[4].dist *= t; 

			// Near  plane
			planes[5].normal[0] = mat[ 3] + mat[ 2]; 
			planes[5].normal[1] = mat[ 7] + mat[ 6]; 
			planes[5].normal[2] = mat[11] + mat[10]; 
			planes[5].dist = mat[15] + mat[14]; 

			t = 1.0f / length(planes[5].normal); 
			planes[5].normal *= t;
			planes[5].dist *= t;
		}
		
	}
}