#pragma once

inline bool Vector2f::operator== (const Vector2f &V) const
{
	__m128 VT1 = _mm_set_ps(y,x,V.y,V.x);
	__m128 VT2 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(1,0,3,2));
	VT1 = _mm_cmpeq_ps(VT1,VT2);
	return _mm_movemask_ps(VT1) == 0xf;
}

inline bool Vector2f::operator!= (const Vector2f &V) const
{
	__m128 VT1 = _mm_set_ps(y,x,V.y,V.x);
	__m128 VT2 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(1,0,3,2));
	VT1 = _mm_cmpneq_ps(VT1,VT2);
	return _mm_movemask_ps(VT1) != 0x0;
}

inline bool Vector2f::operator< (const Vector2f &V) const
{
	__m128 VT1 = _mm_set_ps(y,x,V.y,V.x);
	__m128 VT2 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(1,0,3,2));
	VT1 = _mm_cmplt_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector2f::operator<= (const Vector2f &V) const
{
	__m128 VT1 = _mm_set_ps(y,x,V.y,V.x);
	__m128 VT2 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(1,0,3,2));
	VT1 = _mm_cmple_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector2f::operator> (const Vector2f &V) const
{
	__m128 VT1 = _mm_set_ps(y,x,V.y,V.x);
	__m128 VT2 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(1,0,3,2));
	VT1 = _mm_cmpgt_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline bool Vector2f::operator>= (const Vector2f &V) const
{
	__m128 VT1 = _mm_set_ps(y,x,V.y,V.x);
	__m128 VT2 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(1,0,3,2));
	VT1 = _mm_cmpge_ps(VT1,VT2);
	return _mm_movemask_ps(VT1)==0x0f;
}

inline Vector2f Vector2f::operator+ (const Vector2f &V) const
{
	Vector4f result;

	__m128 VT1 = _mm_set_ps(y,V.y,x,V.x);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector2f Vector2f::operator- (const Vector2f &V) const
{
	Vector4f result;

	__m128 VT1 = _mm_set_ps(y,V.y,x,V.x);
	VT1 = _mm_hsub_ps(VT1,VT1);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector2f Vector2f::operator* (float F) const
{
	Vector4f result;

	__m128 VT1 = _mm_set_ps1(F);
	__m128 VT2 = _mm_set_ps(0.0f,0.0f,y,x);
	VT1 = _mm_mul_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector2f Vector2f::operator/ (float F) const
{
	Vector4f result;

	__m128 VT1 = _mm_set_ps1(F);
	__m128 VT2 = _mm_set_ps(0.0f,0.0f,y,x);
	VT1 = _mm_div_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );

	return result;
}

inline Vector2f & Vector2f::operator+= (const Vector2f &V)
{
	Vector4f result;

	__m128 VT1 = _mm_set_ps(y,V.y,x,V.x);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ps(result.get(), VT1 );

	*this = result;
	return *this;
}

inline Vector2f & Vector2f::operator-= (const Vector2f &V)
{
	Vector4f result;

	__m128 VT1 = _mm_set_ps(y,V.y,x,V.x);
	VT1 = _mm_hsub_ps(VT1,VT1);
	_mm_store_ps(result.get(), VT1 );

	*this = result;
	return *this;
}

inline Vector2f & Vector2f::operator*= (float F)
{
	Vector4f result;

	__m128 VT1 = _mm_set_ps1(F);
	__m128 VT2 = _mm_set_ps(0.0f,0.0f,y,x);
	VT1 = _mm_mul_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );


	*this = result;
	return *this;
}

inline Vector2f & Vector2f::operator/= (float F)
{
	Vector4f result;

	__m128 VT1 = _mm_set_ps1(F);
	__m128 VT2 = _mm_set_ps(0.0f,0.0f,y,x);
	VT1 = _mm_div_ps(VT1,VT2);
	_mm_store_ps(result.get(), VT1 );


	*this = result;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline Vector2f Vector2f::cross (const Vector2f &V) const
{
	float result;

	__m128 VT1 = _mm_set_ps(V.y,V.x,y,x);
	__m128 VT2 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(0,1,2,3));
    VT1 = _mm_mul_ps(VT1,VT2);
	VT1 = _mm_hsub_ps(VT1,VT2);
	_mm_store_ss(&result, VT1 );

	return Vector2f(result,result);
}

inline float Vector2f::dot (const Vector2f &V) const
{
	float result;
	__m128 VT1 = _mm_set_ps(V.y,V.x,y,x);
	__m128 VT2 = _mm_shuffle_ps(VT1,VT1,_MM_SHUFFLE(1,0,3,2));
	VT1 = _mm_mul_ps(VT1,VT2);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline bool Vector2f::isZero(float epsilon)
{

	__m128 VT1 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 VT2 = _mm_set_ps(0.0f,0.0f,epsilon,epsilon);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	VT1 = _mm_cmple_ps(VT1,VT2);

	return _mm_movemask_ps(VT1)==0x0f;
}

inline float Vector2f::lengthSquared()
{
	float result;
	__m128 VT1 = _mm_set_ps(0.0f,0.0f,y,x);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;
}
inline float Vector2f::length()
{
	float result;
	__m128 VT1 = _mm_set_ps(0.0f,0.0f,y,x);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_sqrt_ss(VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline float Vector2f::distanceSquared(const Vector2f &V) const
{
	float result;

	__m128 VT1 = _mm_set_ps(y,V.y,x,V.x);
	VT1 = _mm_hsub_ps(VT1,VT1);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline float Vector2f::distance(const Vector2f &V) const
{
	float result;

	__m128 VT1 = _mm_set_ps(y,V.y,x,V.x);
	VT1 = _mm_hsub_ps(VT1,VT1);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_sqrt_ss(VT1);
	_mm_store_ss(&result,VT1);

	return result;
}

inline bool Vector2f::equals (const Vector2f &V, float epsilon) const
{
	__m128 VT1 = _mm_set_ps(y,V.y,x,V.x);
	VT1 = _mm_hsub_ps(VT1,VT1);
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	__m128 VT2 = _mm_set_ps1(epsilon);
	VT1 = _mm_cmple_ps(VT1,VT2);

	return _mm_movemask_ps(VT1) != 0;
}

inline float Vector2f::normalize ()
{
	float l;
	Vector4f result;

	__m128 VT1 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 VT2 =  VT1;
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	_mm_store_ss(&l,VT1);

	if(l)
	{
		VT2 = _mm_div_ps(VT2,VT1);
	}
	_mm_store_ps(result.get(),VT2);

	*this = result;
	return l;
}

inline void Vector2f::setLength(float Length)
{
	float l;
	Vector4f result;

	__m128 VT1 = _mm_set_ps(0.0f,0.0f,y,x);
	__m128 VT2 =  VT1;
	VT1 = _mm_mul_ps(VT1,VT1);
	VT1 = _mm_hadd_ps(VT1,VT1);
	VT1 = _mm_sqrt_ps(VT1);
	_mm_store_ss(&l,VT1);

	if(l)
	{
		VT2 = _mm_div_ps(VT2,VT1);
		VT1 = _mm_set_ps1(Length);
		VT2 = _mm_mul_ps(VT2,VT1);
		_mm_store_ps(result.get(),VT2);

		*this = result;
	}
}
