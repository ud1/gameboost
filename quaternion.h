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
#include "Matrix.h"

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
		// class Quaternion
		//
		//----------------------------------------------------------------------
		
		class Quaternion 
		{

		public:

			union 
			{
				struct { float x, y, z, w; };
				struct { float v[4]; };
			};

			Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
			Quaternion(const Vector3f &dir, float angle) { set(dir,angle); }
			Quaternion(const Vector3f &ang) { set(ang); }
			Quaternion(const Quaternion &q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
			Quaternion(float nx, float ny, float nz, float nw) : x(nx), y(ny), z(nz), w(nw) { }

			inline bool operator == (const Quaternion &v) const
			{ 
				return	x == v.x && y == v.y && z == v.z && w == v.w ||
						x == -v.x && y == -v.y && z == -v.z && w == -v.w;
			}
			
			inline bool operator != (const Quaternion &v) const
			{
				return	!(x == v.x && y == v.y && z == v.z && w == v.w ||
						x == -v.x && y == -v.y && z == -v.z && w == -v.w);
			}

			inline bool isIdentity(float epsilon = 0.0f) const
			{ 
				return 
					abs(x) <= epsilon && 
					abs(y) <= epsilon && 
					abs(z) <= epsilon && 
					abs(w) - 1.0f <= epsilon;
			}

			inline float &operator [] (int i) { return v[i]; }
			inline float operator [] (int i) const { return v[i]; }

			inline Quaternion operator - () const { return Quaternion(x, y, z, -w); }
			inline Quaternion operator * (const Quaternion &q) const;
			inline Quaternion &operator *= (const Quaternion &q);
			
			inline void normalize();
			inline float length() const;

			inline void setAxisAngle(const Vector3f &axis, float angle);

			inline void setAngles(const Vector3f &angles);
			inline Vector3f getAngles() const;

			inline void setMatrix(const Matrix4x4f &m);
			
			inline Matrix4x4f getMatrix() const;
			inline void getMatrix(Matrix4x4f &) const;
			
			inline void setTransformToPlane(const Vector3f &normal, int plane_axis = 2);

			friend inline Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t);
			friend inline Quaternion normalize(const Quaternion &);
			
		};
		
		//----------------------------------------------------------------------
		
	}

	//--------------------------------------------------------------------------

}
