/**
 * Простенький класс для управления камерой и видом.
 * При поворотах с помощью turn вид из камеры сохраняет вертикально положение,
 * если x = 0.
 */


#pragma once
#include <gb/math/math.h>
#include <cmath>

namespace gb
{
	namespace base
	{
		
		struct Camera
		{
			
			// направление векторов в локальной системе координат
			//
			//          | z, Up'
			//          |
			//          |
			//          |
			//          |
			//          |
			//          |______________ y, Right'
			//         /
			//        /
			//       /
			//      /
			//     / x, -Forward'
			//
			// Up = orientation * Up'
			// Right = orientation * Right'
			// Forward = orientation * Forward'
			
			Camera()
			{
				position = math::vec3(0, 0, 0);
				up = math::vec3(0,0,1);
				forward = math::vec3(-1,0,0);
				right = math::cross(forward, up);
				orientation = math::angleAxis(0.0f, up);
				fov			= 54.0f * M_PI;
				znear		= 0.1f;
				zfar		= 10000.0f;
				speed = 10.0f;
				aspect_ratio = 1.0f;
			}
			
			const math::vec3& getUpVector() {return up;}
			const math::vec3& getForwardVector() {return forward;}
			const math::vec3& getRightVector() {return right;}
			
			void setUpVector(math::vec3 &v)
			{
				up = v;
				forward = math::cross(up, right);
			}
			
			void setForwardVector(math::vec3 &v)
			{
				forward = v;
				right = math::cross(forward, up);
			}
			
			void turn(math::vec_t x, math::vec_t y, math::vec_t z)
			{
				math::quat turn;
				turn = math::angleAxis(z, up);
				orientation = turn * orientation;
				turn = math::angleAxis(y, right);
				orientation = orientation * turn;
				turn = math::angleAxis(-x, forward);
				orientation = orientation * turn;
			}

			void move(math::vec3 delta)
			{
				math::vec3 VF, VU, VR;
				VF = orientation * forward;
				VU = orientation * up;

				VR = math::cross(VF, VU);
				delta *= speed;
				
				position -= VF*delta.x;
				position += VU*delta.z;
				position += VR*delta.y;
			}
			
			math::mat4 getViewMatrix() const
			{
				math::normalize(orientation);
				math::vec3 up = orientation * up;
				math::vec3 center = orientation * forward + position;
				return math::lookAt(position, center, up);
			}

			math::mat4 getViewProjectionMatrix() const
			{
				math::mat4 proj = math::perspective(fov, aspect_ratio, znear, zfar);
				return proj * getViewMatrix();
			}
			
			math::vec3 position;
			math::quat orientation;
			float fov;
			float aspect_ratio;
			float znear, zfar;
			float speed;
			
		private:
			math::vec3 up, forward, right;
		};
		
	}
}