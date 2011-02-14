/** 
* \file vector2fpu_impl.h
* \brief Математическая библиотека с поддержкой SIMD инструкций
* \author Vincent Barabus
*/
#pragma once

inline bool Vector2f::operator== (const Vector2f &V) const
{
	return (x == V.x && y == V.y);
}

inline bool Vector2f::operator!= (const Vector2f &V) const
{
	return (x != V.x || y != V.y);
}

inline bool Vector2f::operator< (const Vector2f &V) const
{
	return (x < V.x && y < V.y);
}

inline bool Vector2f::operator<= (const Vector2f &V) const
{
	return (x <= V.x && y <= V.y);
}

inline bool Vector2f::operator> (const Vector2f &V) const
{
	return (x > V.x && y > V.y);
}

inline bool Vector2f::operator>= (const Vector2f &V) const
{
	return (x >= V.x && y >= V.y);
}

inline Vector2f Vector2f::operator- () const
{
	return Vector2f(-x, -y);
}

inline Vector2f Vector2f::operator+ (const Vector2f &V) const
{
	return Vector2f(*this) += V;
}
inline Vector2f Vector2f::operator- (const Vector2f &V) const
{
	return Vector2f(*this) -= V;
}

inline Vector2f Vector2f::operator* (float F) const
{
	return Vector2f(*this) *= F;
}

inline Vector2f Vector2f::operator/ (float F) const
{
	return Vector2f(*this) /= F;
}

inline Vector2f & Vector2f::operator+= (const Vector2f &V)
{
	x += V.x;
	y += V.y;

	return *this;
}

inline Vector2f & Vector2f::operator-= (const Vector2f &V)
{
	x -= V.x;
	y -= V.y;

	return *this;
}

inline Vector2f & Vector2f::operator*= (float F)
{
	x *= F;
	y *= F;

	return *this;
}

inline Vector2f & Vector2f::operator/= (float F)
{
	x /= F;
	y /= F;

	return *this;
}

// Методы
inline Vector2f Vector2f::cross (const Vector2f &V) const
{
	Vector2f result;

	result.x = 
	result.y = x * V.y - y * V.x;


	return result;
}

inline float Vector2f::dot (const Vector2f &V) const
{
	return x * V.x + y * V.y;
}


inline bool Vector2f::isZero(float epsilon)
{
	return( abs( x ) <= epsilon ) && ( abs( y ) <= epsilon );
}

inline float Vector2f::lengthSquared()
{
	return x * x + y * y;

}
inline float Vector2f::length()
{
	return sqrt( lengthSquared() );
}

inline float Vector2f::distanceSquared(const Vector2f &V) const
{
	float dx = x - V.x;
	float dy = y - V.y;
	float result = dx * dx + dy * dy;

	return result;
}

inline float Vector2f::distance(const Vector2f &V) const
{
	return sqrt( distanceSquared(V) );
}

inline bool Vector2f::equals (const Vector2f &V, float epsilon) const
{
	Vector2f diff(*this);
	diff -= V;
	return diff.isZero(epsilon);
}

inline float Vector2f::normalize ()
{
	float l = length();

	if(l)
	{
		const float il =  1.0f / l;
		x *= il;
		y *= il;
	}

	return l;
}

inline void Vector2f::setLength(float Length)
{
	float l = length();

	if(l)
	{
		float newLength = Length / l;
		x *= newLength;
		y *= newLength;
	}
}