#pragma once

namespace pmath
{
	template<typename T>
	class Box
	{
		T	mMin;
		T	mMax;
	public:
		Box(){}
		Box( const T& min, const T& max ) : mMin(min), mMax(max) {}
	};

	template<typename T>
	bool intersects( const Box<T>& box1, const Box<T>& box2 );

	template<typename T>
	bool contains( const Box<T>& outer, const Box<T>& inner );

	template<typename T>
	Box<T> crop( const Box<T>& outer, const Box<T>& inner );
};

#include "Box.inl"