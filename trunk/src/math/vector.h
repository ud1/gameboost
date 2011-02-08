#pragma once

#include <xmmintrin.h>
#include <cfloat>
#include <cmath>
#include <cassert>

// #define _GDB_NO_SIMD_



namespace gb
{

namespace math
{

class __declspec(align(16)) Vector4f
{
public:
// конструкторы
	Vector4f() {}

	Vector4f(float F) : x(F), y(F), z(F), w(F) {}

	Vector4f(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) {}

	Vector4f(const Vector4f &V)  : x(V.x), y(V.y), z(V.z), w(V.w) {}
public:
// Операторы
	inline bool operator== (const Vector4f &V) const
	{
#ifdef _GDB_NO_SIMD_
		return (x == V.x && y == V.y && z == V.z && w == V.w);
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_cmpeq_ps(VT1,VT2);
		return _mm_movemask_ps(VT1) == 0xf;
#endif
	}

	inline bool operator!= (const Vector4f &V) const
	{
#ifdef _GDB_NO_SIMD_
		return (x != V.x || y != V.y || z != V.z || w != V.w);
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_cmpneq_ps(VT1,VT2);
		return _mm_movemask_ps(VT1) != 0x0;
#endif
	}

	inline bool operator< (const Vector4f &V) const
	{
#ifdef _GDB_NO_SIMD_
		return (x < V.x && y < V.y && z < V.z && w < V.w);
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_cmplt_ps(VT1,VT2);
		return _mm_movemask_ps(VT1)==0x0f;
#endif
	}

	inline bool operator<= (const Vector4f &V) const
	{
#ifdef _GDB_NO_SIMD_
		return (x <= V.x && y <= V.y && z <= V.z && w <= V.w);
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_cmple_ps(VT1,VT2);
		return _mm_movemask_ps(VT1)==0x0f;
#endif
	}

	inline bool operator> (const Vector4f &V) const
	{
#ifdef _GDB_NO_SIMD_
		return (x > V.x && y > V.y && z > V.z && w > V.w);
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_cmpgt_ps(VT1,VT2);
		return _mm_movemask_ps(VT1)==0x0f;

#endif
	}

	inline bool operator>= (const Vector4f &V) const
	{
#ifdef _GDB_NO_SIMD_
		return (x >= V.x && y >= V.y && z >= V.z && w >= V.w);
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_cmpge_ps(VT1,VT2);
		return _mm_movemask_ps(VT1)==0x0f;

#endif
	}

	inline Vector4f operator- () const
	{
		Vector4f result;
#ifdef _GDB_NO_SIMD_
		result.x = -x;
		result.y = -y;
		result.z = -z;
		result.w = -w;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_set_ps(0.0f, 0.0f, 0.0f, 0.0f);
		VT1 = _mm_sub_ps(VT2,VT1);
		_mm_store_ps(result.get(), VT1 );
#endif
		return result;
	}

	inline Vector4f operator+ (const Vector4f &V) const
	{
		Vector4f result;
#ifdef _GDB_NO_SIMD_
		result = *this;
		result += V;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_add_ps(VT1,VT2);
		_mm_store_ps(result.get(), VT1 );
#endif
		return result;
	}
	inline Vector4f operator- (const Vector4f &V) const
	{
		Vector4f result;
#ifdef _GDB_NO_SIMD_
		result = *this;
		result -= V;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_sub_ps(VT1,VT2);
		_mm_store_ps(result.get(), VT1 );
#endif
		return result;
	}

	inline Vector4f operator* (float F) const
	{
		Vector4f result;
#ifdef _GDB_NO_SIMD_
		result = *this;
		result.x *= F;
		result.y *= F;
		result.z *= F;
		result.w *= F;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_set_ps(F, F, F, F);
		VT1 = _mm_mul_ps(VT1,VT2);
		_mm_store_ps(result.get(), VT1 );
#endif
		return result;
	}

	inline Vector4f operator/ (float F) const
	{
		Vector4f result;
#ifdef _GDB_NO_SIMD_
		result = *this;
		result.x /= F;
		result.y /= F;
		result.z /= F;
		result.w /= F;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_set_ps(F, F, F, F);
		VT1 = _mm_div_ps(VT1,VT2);
		_mm_store_ps(result.get(), VT1 );
#endif
		return result;
	}

	inline Vector4f & operator+= (const Vector4f &V)
	{
#ifdef _GDB_NO_SIMD_
		x += V.x;
		y += V.y;
		z += V.z;
		w += V.w;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_add_ps(VT1,VT2);
		_mm_store_ps(get(), VT1 );
#endif
		return *this;
	}

	inline Vector4f & operator-= (const Vector4f &V)
 	{
#ifdef _GDB_NO_SIMD_
		x -= V.x;
		y -= V.y;
		z -= V.z;
		w -= V.w;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_sub_ps(VT1,VT2);
		_mm_store_ps(get(), VT1 );

#endif
		return *this;
	}

	inline Vector4f & operator*= (float F)
 	{
#ifdef _GDB_NO_SIMD_
		x *= F;
		y *= F;
		z *= F;
		w *= F;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_set_ps(F, F, F, F);
		VT1 = _mm_mul_ps(VT1,VT2);
		_mm_store_ps(get(), VT1 );
#endif
		return *this;
	}

	inline Vector4f & operator/= (float F)
 	{
#ifdef _GDB_NO_SIMD_
		x /= F;
		y /= F;
		z /= F;
		w /= F;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_set_ps(F, F, F, F);
		VT1 = _mm_div_ps(VT1,VT2);
		_mm_store_ps(get(), VT1 );
#endif
		return *this;
	}

	inline float &  operator[] (int index)
	{
		assert( index >=0 && index <= 3 );
		return reinterpret_cast<float*>(this)[index];
	}

	inline float operator[] (int index) const
	{
		return reinterpret_cast<const float*>(this)[index];
	}

// методы
	inline Vector4f cross (const Vector4f &V2, const Vector4f &V3) const
	{
		Vector4f result;
#ifdef _GDB_NO_SIMD_
		result.x = (V2.z * V3.w - V2.w * V3.z) * y + (V2.w * V3.y - V2.y * V3.w) * z + (V2.y * V3.z - V2.z * V3.y) * w;
		result.y = (V2.w * V3.z - V2.z * V3.w) * x + (V2.x * V3.w - V2.w * V3.x) * z + (V2.z * V3.x - V2.x * V3.z) * w;
		result.z = (V2.y * V3.w - V2.w * V3.y) * x + (V2.w * V3.x - V2.x * V3.w) * y + (V2.x * V3.y - V2.y * V3.x) * w;
		result.w = (V2.z * V3.y - V2.y * V3.z) * x + (V2.x * V3.z - V2.z * V3.x) * y + (V2.y * V3.x - V2.x * V3.y) * z;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V2.get() );
		__m128 VT3 = _mm_load_ps( V3.get() );
		__m128 VT4 = _mm_shuffle_ps(VT2,VT2,_MM_SHUFFLE(2,1,3,2));
		__m128 VT5 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,3,2,3));
		VT4 = _mm_mul_ps(VT4,VT5);
		__m128 VT6 = _mm_shuffle_ps(VT2,VT2,_MM_SHUFFLE(1,3,2,3));
		VT5 = _mm_shuffle_ps(VT5,VT5,_MM_SHUFFLE(1,3,0,1));
		VT6 = _mm_mul_ps(VT6,VT5);
		VT4 = _mm_sub_ps(VT4,VT6);
		__m128 VT7 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(0,0,0,1));
		VT4 = _mm_mul_ps(VT4,VT7);
		VT6 = _mm_shuffle_ps(VT2,VT2,_MM_SHUFFLE(2,0,3,1));
		VT5 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,3,0,3));
		VT5 = _mm_mul_ps(VT5,VT6);
		VT6 = _mm_shuffle_ps(VT6,VT6,_MM_SHUFFLE(2,1,2,1));
		VT7 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,0,3,1));
		VT6 = _mm_mul_ps(VT6,VT7);
		VT5 = _mm_sub_ps(VT5,VT6);
		VT7 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(1,1,2,2));
		VT7 = _mm_mul_ps(VT7,VT5);
		VT4 = _mm_sub_ps(VT4,VT7);
		VT6 = _mm_shuffle_ps(VT2,VT2,_MM_SHUFFLE(1,0,2,1));
		VT5 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,1,0,2));
		VT5 = _mm_mul_ps(VT5,VT6);
		VT6 = _mm_shuffle_ps(VT6,VT6,_MM_SHUFFLE(2,0,2,1));
		VT7 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,0,2,1));
		VT7 = _mm_mul_ps(VT7,VT6);
		VT5 = _mm_sub_ps(VT5,VT7);
		VT7 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(2,3,3,3));
		VT5 = _mm_mul_ps(VT5,VT7);
		VT4 = _mm_add_ps(VT4,VT5);
		_mm_store_ps(result.get(), VT4 );
#endif
		return result;
	}

	inline float dot (const Vector4f &V) const
	{
		float result;
#ifdef _GDB_NO_SIMD_
		result = x * V.x + y * V.y + z * V.z + w * V.w;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_mul_ps(VT1,VT2);
		VT2 = _mm_shuffle_ps(VT2,VT1,_MM_SHUFFLE(1,0,0,0));
		VT2 = _mm_add_ps(VT2,VT1);
		VT1 = _mm_shuffle_ps(VT1,VT2,_MM_SHUFFLE(0,3,0,0));
		VT1 = _mm_add_ps(VT1,VT2);
		VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(2,2,2,2));

		_mm_store_ss(&result,VT1);
#endif
		return result;
	}

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
		dest[0] = x;
		dest[1] = y;
		dest[2] = z;
		dest[3] = w;
	}

	inline void  get (double *dest) const
	{
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
		x = pF[0];
		y = pF[1];
		z = pF[2];
		w = pF[3];
	}

	inline void set(const double *pD)
	{
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

	inline bool isZero(float epsilon = 0.0)
	{
#ifdef _GDB_NO_SIMD_
		return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon ) && ( abs( y ) <= epsilon );
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_set_ps(epsilon,epsilon,epsilon,epsilon);
		VT1 = _mm_mul_ps(VT1,VT1);
		VT1 = _mm_sqrt_ps(VT1);
		VT1 = _mm_cmple_ps(VT1,VT2);
		return _mm_movemask_ps(VT1)==0x0f;

#endif
	}

	inline float lengthSquared()
	{
		float result;
#ifdef _GDB_NO_SIMD_
		result = x * x + y * y + z * z + w * w;
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = VT1;
		VT1 = _mm_mul_ps(VT1,VT1);
		VT2 = _mm_shuffle_ps(VT2,VT1,_MM_SHUFFLE(1,0,0,0));
		VT2 = _mm_add_ps(VT2,VT1);
		VT1 = _mm_shuffle_ps(VT1,VT2,_MM_SHUFFLE(0,3,0,0));
		VT1 = _mm_add_ps(VT1,VT2);
		VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(2,2,2,2));
		_mm_store_ss(&result,VT1);
#endif
		return result;
	
	}
	inline float length()
	{
		float result;
#ifdef _GDB_NO_SIMD_
		result = sqrt( lengthSquared() );
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = VT1;
		VT1 = _mm_mul_ps(VT1,VT1);
		VT2 = _mm_shuffle_ps(VT2,VT1,_MM_SHUFFLE(1,0,0,0));
		VT2 = _mm_add_ps(VT2,VT1);
		VT1 = _mm_shuffle_ps(VT1,VT2,_MM_SHUFFLE(0,3,0,0));
		VT1 = _mm_add_ps(VT1,VT2);
		VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(2,2,2,2));
		VT1 = _mm_sqrt_ss(VT1);
		_mm_store_ss(&result,VT1);
#endif
		return result;
	}

	inline float distanceSquared(const Vector4f &V) const
	{
		float result;
#ifdef _GDB_NO_SIMD_
	float dx = x - V.x;
	float dy = y - V.y;
	float dz = z - V.z;
	float dw = w - V.w;
	result = dx * dx + dy * dy + dz * dz + dw * dw;

#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_sub_ps(VT1,VT2);
		VT1 = _mm_mul_ps(VT1,VT1);
		VT2 = _mm_shuffle_ps(VT2,VT1,_MM_SHUFFLE(1,0,0,0));
		VT2 = _mm_add_ps(VT2,VT1);
		VT1 = _mm_shuffle_ps(VT1,VT2,_MM_SHUFFLE(0,3,0,0));
		VT1 = _mm_add_ps(VT1,VT2);
		VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(2,2,2,2));
		_mm_store_ss(&result,VT1);
#endif
		return result;
	}

	inline float distance(const Vector4f &V) const
	{
		float result;
#ifdef _GDB_NO_SIMD_
		result = sqrt( distanceSquared(V) );

#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_sub_ps(VT1,VT2);
		VT1 = _mm_mul_ps(VT1,VT1);
		VT2 = _mm_shuffle_ps(VT2,VT1,_MM_SHUFFLE(1,0,0,0));
		VT2 = _mm_add_ps(VT2,VT1);
		VT1 = _mm_shuffle_ps(VT1,VT2,_MM_SHUFFLE(0,3,0,0));
		VT1 = _mm_add_ps(VT1,VT2);
		VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(2,2,2,2));
		VT1 = _mm_sqrt_ss(VT1);
		_mm_store_ss(&result,VT1);
#endif
		return result;
	}

	inline bool equals (const Vector4f &V, float epsilon) const
	{
#ifdef _GDB_NO_SIMD_
		Vector4f diff(*this);
		diff -= V;
		return diff.isZero(epsilon);
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = _mm_load_ps( V.get() );
		VT1 = _mm_sub_ps(VT1,VT2);
		VT1 = _mm_mul_ps(VT1,VT1);
		VT1 = _mm_sqrt_ps(VT1);
		VT2 = _mm_set_ps(epsilon, epsilon, epsilon, epsilon);
		VT1 = _mm_cmple_ps(VT1,VT2);
		return _mm_movemask_ps(VT1) != 0;
#endif
	}

	inline float normalize ()
	{
		float l;
#ifdef _GDB_NO_SIMD_
		l = length();
		if(l)
		{
			const float il =  1.0f / l;
			x *= il;
			y *= il;
			z *= il;
			w *= il;
		}
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = VT1;
		__m128 VT3 = VT1;
		VT1 = _mm_mul_ps(VT1,VT1);
		VT2 = _mm_shuffle_ps(VT2,VT1,_MM_SHUFFLE(1,0,0,0));
		VT2 = _mm_add_ps(VT2,VT1);
		VT1 = _mm_shuffle_ps(VT1,VT2,_MM_SHUFFLE(0,3,0,0));
		VT1 = _mm_add_ps(VT1,VT2);
		VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(2,2,2,2));
		VT1 = _mm_sqrt_ps(VT1);
		_mm_store_ss(&l,VT1);

		if(l)
		{
			VT3 = _mm_div_ps(VT3,VT1);
		}
		_mm_store_ps(get(),VT3);
#endif
		return l;
	}

	inline void setLength(float Length)
	{
		float l;
#ifdef _GDB_NO_SIMD_
		l = length();
		if(l)
		{
			float newLength = Length / l;
			x *= newLength;
			y *= newLength;
			z *= newLength;
			w *= newLength;
		}
#else
		__m128 VT1 = _mm_load_ps( get() );
		__m128 VT2 = VT1;
		__m128 VT3 = VT1;
		VT1 = _mm_mul_ps(VT1,VT1);
		VT2 = _mm_shuffle_ps(VT2,VT1,_MM_SHUFFLE(1,0,0,0));
		VT2 = _mm_add_ps(VT2,VT1);
		VT1 = _mm_shuffle_ps(VT1,VT2,_MM_SHUFFLE(0,3,0,0));
		VT1 = _mm_add_ps(VT1,VT2);
		VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(2,2,2,2));
		VT1 = _mm_sqrt_ps(VT1);
		_mm_store_ss(&l,VT1);

		if(l)
		{
			VT3 = _mm_div_ps(VT3,VT1);
			VT1 = _mm_set_ps(Length, Length, Length, Length);
			VT3 = _mm_mul_ps(VT3,VT1);
			_mm_store_ps(get(),VT3);
		}
#endif

	}

public:
// Члены
	float x, y, z, w;
};


}

}