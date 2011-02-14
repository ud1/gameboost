/** 
* \file vector.h
* \brief Математическая библиотека с поддержкой SIMD инструкций
* \author Vincent Barabus
*/
#pragma once

#include <xmmintrin.h>
#include <cfloat>
#include <cmath>
#include <cassert>
#include <intrin.h>

// #define _GB_NO_SIMD_
// #define _GB_VEC_UNALIGNED_

#ifdef _GB_NO_SIMD_
#define _GB_VEC_UNALIGNED_
#endif

namespace gb
{

namespace math
{

class Vector2f
{
public:
// конструкторы
	Vector2f() {}

	Vector2f(float F) : x(F), y(F) {}

	Vector2f(float X, float Y) : x(X), y(Y) {}

	Vector2f(const Vector2f &V)  : x(V.x), y(V.y) {}

public:
// Операторы
	inline bool operator== (const Vector2f &V) const;
	
	inline bool operator!= (const Vector2f &V) const;
	
	inline bool operator< (const Vector2f &V) const;
	
	inline bool operator<= (const Vector2f &V) const;
	
	inline bool operator> (const Vector2f &V) const;
	
	inline bool operator>= (const Vector2f &V) const;
	
	inline Vector2f operator- () const;
	
	inline Vector2f operator+ (const Vector2f &V) const;
	
	inline Vector2f operator- (const Vector2f &V) const;
	
	inline Vector2f operator* (float F) const;
	
	inline Vector2f operator/ (float F) const;
	
	inline Vector2f & operator+= (const Vector2f &V);
	
	inline Vector2f & operator-= (const Vector2f &V);
	
	inline Vector2f & operator*= (float F);
	
	inline Vector2f & operator/= (float F);
	
	inline float &  operator[] (unsigned int index)
	{
		assert( index <= 1 );
		return reinterpret_cast<float*>(this)[index];
	}

	inline float operator[] (unsigned int index) const
	{
		assert( index <= 1 );
		return reinterpret_cast<const float*>(this)[index];
	}


// Методы

	inline const float* get () const
	{
		return reinterpret_cast<const float*>(this);
	}

	inline float* get ()
	{
		return reinterpret_cast<float*>(this);
	}

	inline void  get (float *dest) const
	{
		assert( dest );
		dest[0] = x;
		dest[1] = y;
	}

	inline void  get (double *dest) const
	{
		assert( dest );
		dest[0] = x;
		dest[1] = y;
	}

	inline void set(const Vector2f &V)
	{
		*this = V;
	}

	inline void set(const float *pF)
	{
		assert( pF );
		x = pF[0];
		y = pF[1];
	}

	inline void set(const double *pD)
	{
		assert( pD );
		x = static_cast<float>(pD[0]);
		y = static_cast<float>(pD[1]);
	}

	inline void set(float X, float Y, float Z, float W)
	{
		x = X;
		y = Y;
	}

	inline void zero()
	{
		x = 0.0f;
		y = 0.0f;
	}

	inline Vector2f cross (const Vector2f &V2) const;
	
	inline float dot (const Vector2f &V) const;
	
	inline bool isZero(float epsilon = 0.0);
	
	inline float lengthSquared();
	
	inline float length();
	
	inline float distanceSquared(const Vector2f &V) const;
	
	inline float distance(const Vector2f &V) const;
	
	inline bool equals (const Vector2f &V, float epsilon) const;
	
	inline float normalize ();
	
	inline void setLength(float Length);
	
public:
// Члены
  float x, y;
};

class Vector3f
{
public:
// конструкторы
	Vector3f() {}

	Vector3f(float F) : x(F), y(F), z(F) {}

	Vector3f(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

	Vector3f(const Vector3f &V)  : x(V.x), y(V.y), z(V.z) {}

public:
// Операторы
	inline bool operator== (const Vector3f &V) const;
	
	inline bool operator!= (const Vector3f &V) const;
	
	inline bool operator< (const Vector3f &V) const;
	
	inline bool operator<= (const Vector3f &V) const;
	
	inline bool operator> (const Vector3f &V) const;
	
	inline bool operator>= (const Vector3f &V) const;
	
	inline Vector3f operator- () const;
	
	inline Vector3f operator+ (const Vector3f &V) const;
	
	inline Vector3f operator- (const Vector3f &V) const;
	
	inline Vector3f operator* (float F) const;
	
	inline Vector3f operator/ (float F) const;
	
	inline Vector3f & operator+= (const Vector3f &V);
	
	inline Vector3f & operator-= (const Vector3f &V);
	
	inline Vector3f & operator*= (float F);
	
	inline Vector3f & operator/= (float F);
	
	inline float &  operator[] (unsigned int index)
	{
		assert( index <= 2 );
		return reinterpret_cast<float*>(this)[index];
	}

	inline float operator[] (unsigned int index) const
	{
		assert( index <= 2 );
		return reinterpret_cast<const float*>(this)[index];
	}

	inline operator Vector2f()
	{
		return *reinterpret_cast<Vector2f*>(this);
	}

// Методы

	inline const float* get () const
	{
		return reinterpret_cast<const float*>(this);
	}

	inline float* get ()
	{
		return reinterpret_cast<float*>(this);
	}

	inline void  get (float *dest) const
	{
		assert( dest );
		dest[0] = x;
		dest[1] = y;
		dest[2] = z;
	}

	inline void  get (double *dest) const
	{
		assert( dest );
		dest[0] = x;
		dest[1] = y;
		dest[2] = z;
	}

	inline void set(const Vector3f &V)
	{
		*this = V;
	}

	inline void set(const float *pF)
	{
		assert( pF );
		x = pF[0];
		y = pF[1];
		z = pF[2];
	}

	inline void set(const double *pD)
	{
		assert( pD );
		x = static_cast<float>(pD[0]);
		y = static_cast<float>(pD[1]);
		z = static_cast<float>(pD[2]);
	}

	inline void set(float X, float Y, float Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	inline void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	inline Vector3f cross (const Vector3f &V2) const;
	
	inline float dot (const Vector3f &V) const;
	
	inline bool isZero(float epsilon = 0.0);
	
	inline float lengthSquared();
	
	inline float length();
	
	inline float distanceSquared(const Vector3f &V) const;
	
	inline float distance(const Vector3f &V) const;
	
	inline bool equals (const Vector3f &V, float epsilon) const;
	
	inline float normalize ();
	
	inline void setLength(float Length);
	
public:
// Члены
  float x, y, z;
};


class
#ifndef _GB_NO_SIMD_
__declspec(align(16))
#endif
Vector4f
{
public:
// конструкторы
	Vector4f() {}

	Vector4f(float F) : x(F), y(F), z(F), w(F) {}

	Vector4f(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

	Vector4f(const Vector4f &V)  : x(V.x), y(V.y), z(V.z), w(V.w) {}

public:
// Операторы
	inline bool operator== (const Vector4f &V) const;
	
	inline bool operator!= (const Vector4f &V) const;
	
	inline bool operator< (const Vector4f &V) const;
	
	inline bool operator<= (const Vector4f &V) const;
	
	inline bool operator> (const Vector4f &V) const;
	
	inline bool operator>= (const Vector4f &V) const;
	
	inline Vector4f operator- () const;
	
	inline Vector4f operator+ (const Vector4f &V) const;
	
	inline Vector4f operator- (const Vector4f &V) const;
	
	inline Vector4f operator* (float F) const;
	
	inline Vector4f operator/ (float F) const;
	
	inline Vector4f & operator+= (const Vector4f &V);
	
	inline Vector4f & operator-= (const Vector4f &V);
	
	inline Vector4f & operator*= (float F);
	
	inline Vector4f & operator/= (float F);
	
	inline float &  operator[] (int index)
	{
		assert( index >=0 && index <= 3 );
		return reinterpret_cast<float*>(this)[index];
	}

	inline float operator[] (int index) const
	{
		assert( index >=0 && index <= 3 );
		return reinterpret_cast<const float*>(this)[index];
	}

	inline operator Vector3f()
	{
		return *reinterpret_cast<Vector3f*>(this);
	}

	inline operator Vector2f()
	{
		return *reinterpret_cast<Vector2f*>(this);
	}

// Методы
	inline const float* get () const
	{
		return reinterpret_cast<const float*>(this);
	}

	inline float* get ()
	{
		return reinterpret_cast<float*>(this);
	}

	inline void get (float *dest) const
	{
		assert( dest );
		dest[0] = x;
		dest[1] = y;
		dest[2] = z;
		dest[3] = w;
	}

	inline void get (double *dest) const
	{
		assert( dest );
		dest[0] = x;
		dest[1] = y;
		dest[2] = z;
		dest[3] = w;
	}

	inline void set(const Vector4f &V)
	{
		*this = V;
	}

	inline void set(const float *pF)
	{
		assert( pF );
		x = pF[0];
		y = pF[1];
		z = pF[2];
		w = pF[3];
	}

	inline void set(const double *pD)
	{
		assert( pD );
		x = static_cast<float>(pD[0]);
		y = static_cast<float>(pD[1]);
		z = static_cast<float>(pD[2]);
		w = static_cast<float>(pD[3]);
	}

	inline void set(float X, float Y, float Z, float W)
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	inline void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	inline Vector4f cross (const Vector4f &V2, const Vector4f &V3) const;
	
	inline float dot (const Vector4f &V) const;
	
	inline bool isZero(float epsilon = 0.0);
	
	inline float lengthSquared();
	
	inline float length();
	
	inline float distanceSquared(const Vector4f &V) const;
	
	inline float distance(const Vector4f &V) const;
	
	inline bool equals (const Vector4f &V, float epsilon) const;
	
	inline float normalize ();
	
	inline void setLength(float Length);

#ifndef _GB_NO_SIMD_
	inline void* operator new(unsigned int size)
	{
		return _aligned_malloc(size*sizeof(Vector4f), 16); 
	}

	inline void* operator new[](unsigned int size)
	{
		return _aligned_malloc(size*sizeof(Vector4f), 16); 
	}

	inline void operator delete(void * _ptr)
	{
		if(_ptr)
		_aligned_free(_ptr);
	}

	inline void operator delete[](void * _ptr)
	{
		if(_ptr)
		_aligned_free(_ptr);
	}
#endif

public:
// Члены
#ifndef _GB_NO_SIMD_
	union
	{
		struct
		{
#endif
  float x, y, z, w;
#ifndef _GB_NO_SIMD_
		};
		struct
		{
			__m128 vec;
		};
	};
#endif
};

#include "vector2fpu_impl.h"
#include "vector3fpu_impl.h"

#ifdef _GB_NO_SIMD_
#include "vector4fpu_impl.h"
#else
#include "vector4simd_impl.h"
#endif


}

}