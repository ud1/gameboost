#pragma once
#include "math.h"

namespace gb
{
	namespace math
	{
		
		struct CoordSystem
		{
			CoordSystem()
			{
				setupFromFR(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
			}
			
			const vec3 &getForwardVector() const {return forward;}
			const vec3 &getRightVector() const {return right;}
			const vec3 &getUpVector() const {return up;}
			
			void setupFromFR(const vec3 &forward, const vec3 right)
			{
				this->forward = forward;
				this->right = right;
				this->up = cross(right, forward);
			}
			
			void setupFromFU(const vec3 &forward, const vec3 &up)
			{
				this->forward = forward;
				this->up = up;
				this->right = cross(forward, up);
			}
			
			void setupFromRU(const vec3 &right, const vec3 &up)
			{
				this->right = right;
				this->up = up;
				this->forward = cross(up, right);
			}
			
		private:
			vec3 forward, right, up;
		};
		
	}
}