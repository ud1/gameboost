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
};