#pragma once

namespace pmath
{
	template<typename T>
	class Rect
	{
		Vector<T,2>	mPos;
		Vector<T,2> mDim;
	public:
		Rect(){}
		Rect( const Vector<T,2>& pos, const Vector<T,2>& dim ) : mPos(pos), mDim(dim) {}
		Rect( T x, T y, T width, T height ) : mPos( vec(x,y) ), mDim( vec(width, height) ) {}

		const Vector<T,2>& GetPosition() const throw() { return mPos; }
		const Vector<T,2>& GetDimension() const throw() { return mDim; }

		const T X() const throw() { return mPos.X(); }
		const T Y() const throw() { return mPos.Y(); } 

		const T Width() const throw() { return mDim.X(); }
		const T Height() const throw() { return mDim.Y(); } 
	};
};