/** 
* \file vector4fpu_impl.h
* \brief Математическая библиотека с поддержкой SIMD инструкций
* \author Vincent Barabus
*/
#pragma once

inline bool Vector4f::operator== (const Vector4f &V) const
{
	return (x == V.x && y == V.y && z == V.z && w == V.w);
}

inline bool Vector4f::operator!= (const Vector4f &V) const
{
	return (x != V.x || y != V.y || z != V.z || w != V.w);
}

inline bool Vector4f::operator< (const Vector4f &V) const
{
	return (x < V.x && y < V.y && z < V.z && w < V.w);
}

inline bool Vector4f::operator<= (const Vector4f &V) const
{
	return (x <= V.x && y <= V.y && z <= V.z && w <= V.w);
}

inline bool Vector4f::operator> (const Vector4f &V) const
{
	return (x > V.x && y > V.y && z > V.z && w > V.w);
}

inline bool Vector4f::operator>= (const Vector4f &V) const
{
	return (x >= V.x && y >= V.y && z >= V.z && w >= V.w);
}

inline Vector4f Vector4f::operator- () const
{
	return Vector4f(-x,-y,-z,-w);
}

inline Vector4f Vector4f::operator+ (const Vector4f &V) const
{
	return Vector4f(*this) += V;
}
inline Vector4f Vector4f::operator- (const Vector4f &V) const
{
	return Vector4f(*this) -= V;
}

inline Vector4f Vector4f::operator* (float F) const
{
	return Vector4f(*this) *= F;
}

inline Vector4f Vector4f::operator/ (float F) const
{
	return Vector4f(*this) /= F;
}

inline Vector4f & Vector4f::operator+= (const Vector4f &V)
{
	x += V.x;
	y += V.y;
	z += V.z;
	w += V.w;

	return *this;
}

inline Vector4f & Vector4f::operator-= (const Vector4f &V)
{
	x -= V.x;
	y -= V.y;
	z -= V.z;
	w -= V.w;

	return *this;
}

inline Vector4f & Vector4f::operator*= (float F)
{
	x *= F;
	y *= F;
	z *= F;
	w *= F;

	return *this;
}

inline Vector4f & Vector4f::operator/= (float F)
{
	x /= F;
	y /= F;
	z /= F;
	w /= F;

	return *this;
}

// Методы
inline Vector4f Vector4f::cross (const Vector4f &V2, const Vector4f &V3) const
{
	Vector4f result;

	result.x = (V2.z * V3.w - V2.w * V3.z) * y + (V2.w * V3.y - V2.y * V3.w) * z + (V2.y * V3.z - V2.z * V3.y) * w;
	result.y = (V2.w * V3.z - V2.z * V3.w) * x + (V2.x * V3.w - V2.w * V3.x) * z + (V2.z * V3.x - V2.x * V3.z) * w;
	result.z = (V2.y * V3.w - V2.w * V3.y) * x + (V2.w * V3.x - V2.x * V3.w) * y + (V2.x * V3.y - V2.y * V3.x) * w;
	result.w = (V2.z * V3.y - V2.y * V3.z) * x + (V2.x * V3.z - V2.z * V3.x) * y + (V2.y * V3.x - V2.x * V3.y) * z;

	return result;
}

inline float Vector4f::dot (const Vector4f &V) const
{
	return x * V.x + y * V.y + z * V.z + w * V.w;
}


inline bool Vector4f::isZero(float epsilon)
{
	return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon ) && ( abs( y ) <= epsilon );
}

inline float Vector4f::lengthSquared()
{
	return x * x + y * y + z * z + w * w;

}
inline float Vector4f::length()
{
	return sqrt( lengthSquared() );
}

inline float Vector4f::distanceSquared(const Vector4f &V) const
{
	float result;

	float dx = x - V.x;
	float dy = y - V.y;
	float dz = z - V.z;
	float dw = w - V.w;
	result = dx * dx + dy * dy + dz * dz + dw * dw;

	return result;
}

inline float Vector4f::distance(const Vector4f &V) const
{
	return sqrt( distanceSquared(V) );
}

inline bool Vector4f::equals (const Vector4f &V, float epsilon) const
{
	Vector4f diff(*this);
	diff -= V;
	return diff.isZero(epsilon);
}

inline float Vector4f::normalize ()
{
	float l = length();

	if(l)
	{
		const float il =  1.0f / l;
		x *= il;
		y *= il;
		z *= il;
		w *= il;
	}

	return l;
}

inline void Vector4f::setLength(float Length)
{
	float l = length();

	if(l)
	{
		float newLength = Length / l;
		x *= newLength;
		y *= newLength;
		z *= newLength;
		w *= newLength;
	}
}
