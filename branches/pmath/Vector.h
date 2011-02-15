#pragma once

namespace pmath
{

template<typename T, const unsigned int N>
class Vector
{
public:
	enum
	{
		iX,
		iY,
		iZ,
		iW
	};

	typedef T type;

	enum 
	{
		Size = N
	};

	inline Vector() throw();
	inline Vector( const Vector& arr ) throw();
	inline Vector( Vector&& arr ) throw();
	inline Vector( const Vector<T, N-1>& arr, T val ) throw();
	inline Vector( const T* const arr ) throw();

	inline T X() const throw() { PMATH_STATIC_ASSERT(iX < Size, "Error. X not exists in vector of this type"); return (*this)[iX]; }
	inline T& X() throw() { PMATH_STATIC_ASSERT(iX < Size, "Error. X not exists in vector of this type"); return (*this)[iX]; }

	inline T Y() const throw() { PMATH_STATIC_ASSERT(iX < Size, "Error. Y not exists in vector of this type"); return (*this)[iY]; }
	inline T& Y() throw() { PMATH_STATIC_ASSERT(iX < Size, "Error. Y not exists in vector of this type"); return (*this)[iY]; }

	inline T Z() const throw() { PMATH_STATIC_ASSERT(iX < Size, "Error. Z not exists in vector of this type"); return (*this)[iZ]; }
	inline T& Z() throw() { PMATH_STATIC_ASSERT(iX < Size, "Error. Z not exists in vector of this type"); return (*this)[iZ]; }

	inline T W() const throw() { PMATH_STATIC_ASSERT(iX < Size, "Error. W not exists in vector of this type"); return (*this)[iW]; }
	inline T& W() throw() { PMATH_STATIC_ASSERT(iX < Size, "Error. W not exists in vector of this type"); return (*this)[iW]; }

	inline Vector& operator = ( const T* const arr ) throw();
	inline Vector& operator = ( const Vector<T,N>& other ) throw();
	inline Vector& operator = ( Vector<T,N>&& other ) throw();

	inline bool operator == ( const Vector<T,N>& arr ) throw();

	inline T& operator []( unsigned int i ) throw();
	inline T operator []( unsigned int i ) const throw();
	
	inline Vector<T,N>& operator += ( const Vector<T,N>& v2 ) throw();
	inline Vector<T,N>& operator -= ( const Vector<T,N>& v2 ) throw();
	inline Vector<T,N>& operator *= ( const Vector<T,N>& v2 ) throw();
	inline Vector<T,N>& operator /= ( const Vector<T,N>& v2 ) throw();

	inline Vector<T,N>& operator *= ( const T s) throw();
	inline Vector<T,N>& operator /= ( const T s) throw();
	inline const Vector<T,N>& operator - () throw();

private:
	T	mValue[Size];
};

///////////////////// Globals //////////////////////////////

#define DEFINE_VEC_BINARY_OPERATOR(op) \
template<typename T, const unsigned int N> \
inline Vector<T,N> operator op ( Vector<T,N> v1, const Vector<T,N>& v2 ) throw();


DEFINE_VEC_BINARY_OPERATOR( + )
DEFINE_VEC_BINARY_OPERATOR( - )
DEFINE_VEC_BINARY_OPERATOR( * )
DEFINE_VEC_BINARY_OPERATOR( / )

#undef DEFINE_VEC_BINARY_OPERATOR

#define DEFINE_VEC_BINARY_OPERATOR(op) \
template<typename T, const unsigned int N> \
inline Vector<T,N> operator op ( Vector<T,N> v, const T s ) throw();

DEFINE_VEC_BINARY_OPERATOR( * )
DEFINE_VEC_BINARY_OPERATOR( / )

#undef DEFINE_VEC_BINARY_OPERATOR

template<typename T, const unsigned int N>
inline Vector<T,N> operator - (const Vector<T,N>& v) throw();

// operations

template<typename T, const unsigned int N>
inline T dot( const Vector<T,N>& v1, const Vector<T,N>& v2 ) throw();

template<typename T, const unsigned int N>
inline T length( const Vector<T,N>& vec ) throw();

template<typename T, const unsigned int N>
inline T distance( const Vector<T,N>& vecFrom, const Vector<T,N>& vecTo ) throw();

template<typename T>
inline Vector<T,3> cross( const Vector<T,3>& v1, const Vector<T,3>& v2 ) throw();

// constructors

template<typename T>
inline Vector<T,2> vector( const T& x, const T& y ) throw();

template<typename T>
inline Vector<T,3> vector( const T& x, const T& y, const T& z ) throw();

template<typename T>
inline Vector<T,4> vector( const T& x, const T& y, const T& z, const T& w ) throw();

} // namespace math

#include "Vector.inl"