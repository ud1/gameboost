/** 
* \file vector4simd_impl.h
* \brief Математическая библиотека с поддержкой SIMD инструкций
* \author Vincent Barabus
*/
#pragma once

inline bool Vector4f::operator== (const Vector4f &V) const
{
	return _mm_movemask_ps( _mm_cmpeq_ps(vec,V.vec) ) == 0xf;
}

inline bool Vector4f::operator!= (const Vector4f &V) const
{
	return _mm_movemask_ps( _mm_cmpneq_ps(vec,V.vec) ) != 0x0;
}

inline bool Vector4f::operator< (const Vector4f &V) const
{
	return _mm_movemask_ps( _mm_cmplt_ps(vec,V.vec) ) == 0xf;
}

inline bool Vector4f::operator<= (const Vector4f &V) const
{
	return _mm_movemask_ps(  _mm_cmple_ps(vec,V.vec) ) == 0xf;
}

inline bool Vector4f::operator> (const Vector4f &V) const
{
	return _mm_movemask_ps( _mm_cmpgt_ps(vec ,V.vec) ) == 0xf;
}

inline bool Vector4f::operator>= (const Vector4f &V) const
{
	return _mm_movemask_ps( _mm_cmpge_ps(vec ,V.vec) ) == 0x0f;
}

inline Vector4f Vector4f::operator- () const
{
	Vector4f result;

	__m128 VT = _mm_setzero_ps();
	VT = _mm_sub_ps(VT,vec);
	result.vec = VT;

	return result;
}

inline Vector4f Vector4f::operator+ (const Vector4f &V) const
{
	Vector4f result;

	result.vec = _mm_add_ps(vec,V.vec);

	return result;
}

inline Vector4f Vector4f::operator- (const Vector4f &V) const
{
	Vector4f result;

	result.vec = _mm_sub_ps(vec ,V.vec);

	return result;
}

inline Vector4f Vector4f::operator* (float F) const
{
	Vector4f result;

	result.vec = _mm_mul_ps( vec, _mm_set_ps1(F) );

	return result;
}

inline Vector4f Vector4f::operator/ (float F) const
{
	Vector4f result;

	result.vec = _mm_div_ps( vec, _mm_set_ps1(F) );

	return result;
}

inline Vector4f & Vector4f::operator+= (const Vector4f &V)
{
	vec = _mm_mul_ps( vec, V.vec );

	return *this;
}

inline Vector4f & Vector4f::operator-= (const Vector4f &V)
{
	vec = _mm_sub_ps( vec, V.vec );

	return *this;
}

inline Vector4f & Vector4f::operator*= (float F)
{
	vec = _mm_mul_ps( vec, _mm_set_ps1(F) );

	return *this;
}

inline Vector4f & Vector4f::operator/= (float F)
{
	vec = _mm_div_ps( vec, _mm_set_ps1(F) );

	return *this;
}

inline Vector4f Vector4f::cross (const Vector4f &V2, const Vector4f &V3) const
{
	Vector4f result;

	__m128 VT1 = vec;
	__m128 VT2 = V2.vec;
	__m128 VT3 = V3.vec;
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
	result.vec = VT4;

	return result;
}

inline float Vector4f::dot (const Vector4f &V) const
{
	float result;

	__m128 VT1 = vec;
	VT1 = _mm_mul_ps(VT1,V.vec);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline bool Vector4f::isZero(float epsilon)
{

	__m128 VT1 = vec;
	__m128 VT2 = _mm_set_ps1(epsilon);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	VT1 = _mm_cmple_ps(VT1,VT2);

	return _mm_movemask_ps(VT1) == 0xf;
}

inline float Vector4f::lengthSquared()
{
	float result;

	__m128 VT = vec;
	VT = _mm_mul_ps(VT,VT);
	VT = _mm_hadd_ps(VT,VT);
	VT = _mm_hadd_ps(VT,VT);
	_mm_store_ss(&result,VT);

	return result;

}
inline float Vector4f::length()
{
	float result;

	__m128 VT = vec;
	VT = _mm_mul_ps(VT,VT);
	VT = _mm_hadd_ps(VT,VT);
	VT = _mm_hadd_ps(VT,VT);
	VT = _mm_sqrt_ss(VT);
	_mm_store_ss(&result,VT);

	return result;
}

inline float Vector4f::distanceSquared(const Vector4f &V) const
{
	float result;

	__m128 VT1 = vec;
	VT1 = _mm_sub_ps(VT1,V.vec);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline float Vector4f::distance(const Vector4f &V) const
{
	float result;

	__m128 VT = vec;
	VT = _mm_sub_ps(VT,V.vec);
	VT = _mm_mul_ps(VT,VT);
	VT = _mm_hadd_ps(VT,VT);
	VT = _mm_hadd_ps(VT,VT);
	VT = _mm_sqrt_ss(VT);
	_mm_store_ss(&result,VT);

	return result;
}

inline bool Vector4f::equals (const Vector4f &V, float epsilon) const
{
	__m128 VT1 = vec;
	__m128 VT2 = _mm_set_ps1(epsilon);
	VT1 = _mm_sub_ps(VT1,V.vec);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	VT1 = _mm_cmple_ps(VT1,VT2);

	return _mm_movemask_ps(VT1) != 0x0;
}

inline float Vector4f::normalize ()
{
	float l;

	__m128 VT1 = vec;
	__m128 VT2 = VT1;
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	_mm_store_ss(&l,VT1);

	if(l)
	{
		VT2 = _mm_div_ps(VT2,VT1);
	}
	_mm_store_ps(get(),VT2);

	return l;
}

inline void Vector4f::setLength(float Length)
{
	float l;

	__m128 VT1 = vec;
	__m128 VT2 = VT1;
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	_mm_store_ss(&l,VT1);

	if(l)
	{
		VT2 = _mm_div_ps(VT2,VT1);
		VT1 = _mm_set_ps1(Length);
		VT2 = _mm_mul_ps(VT2,VT1);
		vec = VT2;
	}
}
