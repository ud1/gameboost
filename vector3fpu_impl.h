/** 
* \file vector3fpu_impl.h
* \brief Математическая библиотека с поддержкой SIMD инструкций
* \author Vincent Barabus
*/
#pragma once

inline bool Vector3f::operator== (const Vector3f &V) const
{
	return (x == V.x && y == V.y && z == V.z);
}

inline bool Vector3f::operator!= (const Vector3f &V) const
{
	return (x != V.x || y != V.y || z != V.z);
}

inline bool Vector3f::operator< (const Vector3f &V) const
{
	return (x < V.x && y < V.y && z < V.z);
}

inline bool Vector3f::operator<= (const Vector3f &V) const
{
	return (x <= V.x && y <= V.y && z <= V.z);
}

inline bool Vector3f::operator> (const Vector3f &V) const
{
	return (x > V.x && y > V.y && z > V.z);
}

inline bool Vector3f::operator>= (const Vector3f &V) const
{
	return (x >= V.x && y >= V.y && z >= V.z);
}

inline Vector3f Vector3f::operator- () const
{
	return Vector3f(-x, -y, -z);
}

inline Vector3f Vector3f::operator+ (const Vector3f &V) const
{
	return Vector3f(*this) += V;
}
inline Vector3f Vector3f::operator- (const Vector3f &V) const
{
	return Vector3f(*this) -= V;
}

inline Vector3f Vector3f::operator* (float F) const
{
	return Vector3f(*this) *= F;
}

inline Vector3f Vector3f::operator/ (float F) const
{
	return Vector3f(*this) /= F;
}

inline Vector3f & Vector3f::operator+= (const Vector3f &V)
{
	x += V.x;
	y += V.y;
	z += V.z;

	return *this;
}

inline Vector3f & Vector3f::operator-= (const Vector3f &V)
{
	x -= V.x;
	y -= V.y;
	z -= V.z;

	return *this;
}

inline Vector3f & Vector3f::operator*= (float F)
{
	x *= F;
	y *= F;
	z *= F;

	return *this;
}

inline Vector3f & Vector3f::operator/= (float F)
{
	x /= F;
	y /= F;
	z /= F;

	return *this;
}

// Методы
inline Vector3f Vector3f::cross (const Vector3f &V) const
{
	Vector3f result;

	result.x = (y * V.z) - (z * V.y);
	result.y = (z * V.x) - (x * V.z);
	result.z = (x * V.y) - (y * V.x);

	return result;
}

inline float Vector3f::dot (const Vector3f &V) const
{
	float result;

	result = x * V.x + y * V.y + z * V.z;

	return result;
}


inline bool Vector3f::isZero(float epsilon)
{
	return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon ) && ( abs( z ) <= epsilon );
}

inline float Vector3f::lengthSquared()
{
	float result;

	result = x * x + y * y + z * z;

	return result;

}
inline float Vector3f::length()
{
	return sqrt( lengthSquared() );
}

inline float Vector3f::distanceSquared(const Vector3f &V) const
{
	float dx = x - V.x;
	float dy = y - V.y;
	float dz = z - V.z;
	float result = dx * dx + dy * dy + dz * dz;

	return result;
}

inline float Vector3f::distance(const Vector3f &V) const
{
	return sqrt( distanceSquared(V) );
}

inline bool Vector3f::equals (const Vector3f &V, float epsilon) const
{
	Vector3f diff(*this);
	diff -= V;
	return diff.isZero(epsilon);
}

inline float Vector3f::normalize ()
{
	float l = length();

	if(l)
	{
		const float il =  1.0f / l;
		x *= il;
		y *= il;
		z *= il;
	}

	return l;
}

inline void Vector3f::setLength(float Length)
{
	float l = length();

	if(l)
	{
		float newLength = Length / l;
		x *= newLength;
		y *= newLength;
		z *= newLength;
	}
}