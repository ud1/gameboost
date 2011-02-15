#pragma once

namespace pmath
{

template<typename T>
class Quaternion
{
	Vector< T, 4 > mVal;
public:
};

template<typename T>
Quaternion<T> quaternion( const Vector<T,3>& axis, const T& angle );

};

#include "Quaternion.inl"