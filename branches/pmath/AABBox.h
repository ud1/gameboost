#pragma once

namespace pmath
{
	template<typename T>
	class AABBbox
	{
		Vector<T,3>	mMin;
		Vector<T,3> mMax;
	public:
		AABBbox(){}
		AABBbox( const Vector<T,3>& min, const Vector<T,3>& max ) : mMin(min), mMax(max) {}
	};
};