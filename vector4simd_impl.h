#pragma once

inline bool Vector4f::operator== (const Vector4f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmpeq_ps(VT1,VT2);
	return _mm_movemask_ps(VT1) == 0xf;
}

inline bool Vector4f::operator!= (const Vector4f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmpneq_ps(VT1,VT2);
	return _mm_movemask_ps(VT1) != 0x0;
}

inline bool Vector4f::operator< (const Vector4f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmplt_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector4f::operator<= (const Vector4f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmple_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector4f::operator> (const Vector4f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmpgt_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector4f::operator>= (const Vector4f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmpge_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline Vector4f Vector4f::operator- () const
{
	Vector4f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_setzero_ps();
	VT1 = _mm_sub_ps(VT2,VT1);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector4f Vector4f::operator+ (const Vector4f &V) const
{
	Vector4f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_add_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector4f Vector4f::operator- (const Vector4f &V) const
{
	Vector4f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_sub_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector4f Vector4f::operator* (float F) const
{
	Vector4f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps1(&F);
	VT1 = _mm_mul_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector4f Vector4f::operator/ (float F) const
{
	Vector4f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps1(&F);
	VT1 = _mm_div_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector4f & Vector4f::operator+= (const Vector4f &V)
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_add_ps(VT1,VT2);
	_mm_store_ps(get(), VT1 );

	return *this;
}

inline Vector4f & Vector4f::operator-= (const Vector4f &V)
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_sub_ps(VT1,VT2);
	_mm_store_ps(get(), VT1 );

	return *this;
}

inline Vector4f & Vector4f::operator*= (float F)
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps1(&F);
	VT1 = _mm_mul_ps(VT1,VT2);
	_mm_store_ps(get(), VT1 );

	return *this;
}

inline Vector4f & Vector4f::operator/= (float F)
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps1(&F);
	VT1 = _mm_div_ps(VT1,VT2);
	_mm_store_ps(get(), VT1 );

	return *this;
}

// Ìועמהû
inline Vector4f Vector4f::cross (const Vector4f &V2, const Vector4f &V3) const
{
	Vector4f result;

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

	return result;
}

inline float Vector4f::dot (const Vector4f &V) const
{
	float result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_mul_ps(VT1,VT2);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline bool Vector4f::isZero(float epsilon)
{

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_set_ps(epsilon,epsilon,epsilon,epsilon);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	VT1 = _mm_cmple_ps(VT1,VT2);

	return _mm_movemask_ps(VT1)==0x0f;
}

inline float Vector4f::lengthSquared()
{
	float result;

	__m128 VT1 = _mm_load_ps( get() );
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;

}
inline float Vector4f::length()
{
	float result;

	__m128 VT1 = _mm_load_ps( get() );
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_sqrt_ss(VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline float Vector4f::distanceSquared(const Vector4f &V) const
{
	float result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_sub_ps(VT1,VT2);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline float Vector4f::distance(const Vector4f &V) const
{
	float result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_sub_ps(VT1,VT2);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_sqrt_ss(VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline bool Vector4f::equals (const Vector4f &V, float epsilon) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_sub_ps(VT1,VT2);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	VT2 = _mm_set_ps(epsilon, epsilon, epsilon, epsilon);
	VT1 = _mm_cmple_ps(VT1,VT2);

	return _mm_movemask_ps(VT1) != 0;
}

inline float Vector4f::normalize ()
{
	float l;

	__m128 VT1 = _mm_load_ps( get() );
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

	__m128 VT1 = _mm_load_ps( get() );
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
		_mm_store_ps(get(),VT2);
	}
}
