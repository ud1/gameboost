/**
 * Простенький класс для управления камерой и видом.
 * При поворотах с помощью turn вид из камеры сохраняет вертикально положение,
 * если x = 0.
 */


#pragma once
#include "math.h"
#include "CoordSystem.h"
#include <cmath>

namespace gb
{
	namespace math
	{
		
		struct Camera
		{
			Camera()
			{
				position = vec3(0, 0, 0);
				orientation = angleAxis(0.0f, coord_system.getUpVector());
				fov			= 54.0f * M_PI;
				znear		= 0.1f;
				zfar		= 10000.0f;
				speed = 10.0f;
				aspect_ratio = 1.0f;
			}
			
			void turn(vec_t x, vec_t y, vec_t z)
			{
				quat turn;
				turn = angleAxis(z, coord_system.getUpVector());
				orientation = turn * orientation;
				turn = angleAxis(y, coord_system.getRightVector());
				orientation = orientation * turn;
				turn = angleAxis(-x, coord_system.getForwardVector());
				orientation = orientation * turn;
			}

			void move(vec3 delta)
			{
				vec3 VF, VU, VR;
				VF = orientation * coord_system.getForwardVector();
				VU = orientation * coord_system.getUpVector();

				VR = cross(VF, VU);
				delta *= speed;
				
				position -= VF*delta.x;
				position += VU*delta.z;
				position += VR*delta.y;
			}
			
			mat4 getViewMatrix() const
			{
				normalize(orientation);
				vec3 up = orientation * coord_system.getUpVector();
				vec3 center = orientation * coord_system.getForwardVector() + position;
				return lookAt(position, center, up);
			}

			mat4 getViewProjectionMatrix() const
			{
				mat4 proj = perspective(fov, aspect_ratio, znear, zfar);
				return proj * getViewMatrix();
			}
			
			CoordSystem coord_system;
			vec3 position;
			quat orientation;
			float fov;
			float aspect_ratio;
			float znear, zfar;
			float speed;
		};
	}
}