#pragma once

inline bool Vector3f::operator== (const Vector3f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmpeq_ps(VT1,VT2);
	return _mm_movemask_ps(VT1) == 0xf;
}

inline bool Vector3f::operator!= (const Vector3f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmpneq_ps(VT1,VT2);
	return _mm_movemask_ps(VT1) != 0x0;
}

inline bool Vector3f::operator< (const Vector3f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmplt_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector3f::operator<= (const Vector3f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmple_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector3f::operator> (const Vector3f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmpgt_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector3f::operator>= (const Vector3f &V) const
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_cmpge_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline Vector3f Vector3f::operator+ (const Vector3f &V) const
{
	Vector3f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_add_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector3f Vector3f::operator- (const Vector3f &V) const
{
	Vector3f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_sub_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector3f Vector3f::operator* (float F) const
{
	Vector3f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps1(&F);
	VT1 = _mm_mul_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector3f Vector3f::operator/ (float F) const
{
	Vector3f result;

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps1(&F);
	VT1 = _mm_div_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector3f & Vector3f::operator+= (const Vector3f &V)
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_add_ps(VT1,VT2);
	_mm_store_ps(get(), VT1 );

	return *this;
}

inline Vector3f & Vector3f::operator-= (const Vector3f &V)
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_sub_ps(VT1,VT2);
	_mm_store_ps(get(), VT1 );

	return *this;
}

inline Vector3f & Vector3f::operator*= (float F)
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps1(&F);
	VT1 = _mm_mul_ps(VT1,VT2);
	_mm_store_ps(get(), VT1 );

	return *this;
}

inline Vector3f & Vector3f::operator/= (float F)
{
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps1(&F);
	VT1 = _mm_div_ps(VT1,VT2);
	_mm_store_ps(get(), VT1 );

	return *this;
}

inline Vector3f Vector3f::cross (const Vector3f &V) const
{
	Vector3f result;
	
	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_load_ps( V.get() );
	VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(3,0,2,1));
	VT2 = _mm_shuffle_ps(VT2,VT2,_MM_SHUFFLE(3,1,0,2));
	__m128 VT3 = _mm_mul_ps(VT1,VT2);
	VT1 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(3,0,2,1));
	VT2 = _mm_shuffle_ps(VT2,VT2,_MM_SHUFFLE(3,1,0,2));
	VT1 = _mm_mul_ps(VT1,VT2);
	VT3 = _mm_sub_ps(VT3,VT1);
	_mm_store_ps(result.get(), VT1 );
	
	result.w = 0.0f;
	
	return result;
}

inline float Vector3f::dot (const Vector3f &V) const
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

inline bool Vector3f::isZero(float epsilon)
{

	__m128 VT1 = _mm_load_ps( get() );
	__m128 VT2 = _mm_set_ps(epsilon,epsilon,epsilon,epsilon);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	VT1 = _mm_cmple_ps(VT1,VT2);

	return _mm_movemask_ps(VT1)==0x0f;
}

inline float Vector3f::lengthSquared()
{
	float result;

	__m128 VT1 = _mm_load_ps( get() );
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;

}
inline float Vector3f::length()
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

inline float Vector3f::distanceSquared(const Vector3f &V) const
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

inline float Vector3f::distance(const Vector3f &V) const
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

inline bool Vector3f::equals (const Vector3f &V, float epsilon) const
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

inline float Vector3f::normalize ()
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

inline void Vector3f::setLength(float Length)
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
		VT1 = _mm_set_ps(Length, Length, Length, 0.0f);
		VT2 = _mm_mul_ps(VT2,VT1);
		_mm_store_ps(get(),VT2);
	}
}
