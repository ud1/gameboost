#ifndef VECTOR_H
#define VECTOR_H

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

	inline T X() const throw() { return (*this)[iX]; }
	inline T& X() throw() { return (*this)[iX]; }

	inline T Y() const throw() { return (*this)[iY]; }
	inline T& Y() throw() { return (*this)[iY]; }

	inline T Z() const throw() { return (*this)[iZ]; }
	inline T& Z() throw() { return (*this)[iZ]; }

	inline T W() const throw() { return (*this)[iW]; }
	inline T& W() throw() { return (*this)[iW]; }

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

////////////////////////////////////////////////////////////
template<typename T, const unsigned int N>
Vector<T,N>::Vector() throw()
{
	fill<T,Size>( &((*this)[0]), T(0) );
}

template<typename T, const unsigned int N>
Vector<T,N>::Vector( const Vector& other ) throw()
{
	copy<T, N>( mValue, other.mValue);
}

template<typename T, const unsigned int N>
Vector<T,N>::Vector( Vector<T,N>&& other ) throw()
{
	copy<T, N>( mValue, other.mValue);
}

template<typename T, const unsigned int N>
Vector<T,N>::Vector( const Vector<T, N-1>& vec, T val ) throw()
{
	copy<T, N-1>( mValue, vec.mValue);
	(*this)[N-1] = val;
}

template<typename T, const unsigned int N>
Vector<T,N>::Vector( const T* const arr ) throw()
{
	*this = arr;	
}

template<typename T, const unsigned int N>
inline Vector<T,N>& Vector<T,N>::operator = ( const T* const other ) throw()
{
	copy<T, N>( mValue, other );
	return *this;
}

template<typename T, const unsigned int N>
inline Vector<T,N>& Vector<T,N>::operator = ( const Vector<T,N>& other ) throw()
{
	if (this != &other)
	{
		copy<T, N>( mValue, other.mValue );
	}
	return *this;
}

template<typename T, const unsigned int N>
inline Vector<T,N>& Vector<T,N>::operator = ( Vector<T,N>&& other ) throw()
{
	if (this != &other)
	{
		copy<T, N>( mValue, other.mValue );
	}
	return *this;
}

template<typename T, const unsigned int N>
bool Vector<T,N>::operator == ( const Vector<T,N>& arr ) throw()
{
	bool ret = true;
	for( unsigned int i = 0; i < Size && ret; i++ )
	{
		ret = ( (*this)[i] == v2[i] );
	}
	return ret;
}

template<typename T, const unsigned int N>
inline T& Vector<T,N>::operator []( unsigned int i ) throw()
{
	PMATH_ASSERT( i < Size );
	return mValue[i];
}

template<typename T, const unsigned int N>
inline T Vector<T,N>::operator []( unsigned int i ) const throw()
{
	PMATH_ASSERT( i < Size );
	return mValue[i];
}

#define DEFINE_VEC_UNARY_OPERATOR(op) \
	template<typename T, const unsigned int N> \
	inline Vector<T,N>& Vector<T,N>::operator op ( const Vector<T,N>& v2 )  throw()\
	{ \
		for( unsigned int i = 0; i < Size; i++ ) \
		{ \
			(*this)[i] op v2[i]; \
		} \
		return (*this);	\
	}

	DEFINE_VEC_UNARY_OPERATOR(+=)
	DEFINE_VEC_UNARY_OPERATOR(-=)
	DEFINE_VEC_UNARY_OPERATOR(*=)
	DEFINE_VEC_UNARY_OPERATOR(/=)

#undef DEFINE_VEC_UNARY_OPERATOR

#define DEFINE_VEC_UNARY_OPERATOR(op) \
	template<typename T, const unsigned int N> \
	inline Vector<T,N>& Vector<T,N>::operator op ( const T s)  throw()\
	{ \
		for( unsigned int i = 0; i < N; i++ ) \
		{ \
			(*this)[i] op s; \
		} \
		return (*this);	\
	}

	DEFINE_VEC_UNARY_OPERATOR(*=)
	DEFINE_VEC_UNARY_OPERATOR(/=)

#undef DEFINE_VEC_UNARY_OPERATOR

template<typename T, const unsigned int N> 
inline const Vector<T,N>& Vector<T,N>::operator - () throw()
{ 
	for( unsigned int i = 0; i < N; i++ ) 
	{ 
		(*this)[i] = -(*this)[i]; 
	} 
	return (*this);		
}

///////////////////// Globals //////////////////////////////

#define DEFINE_VEC_BINARY_OPERATOR(op) \
template<typename T, const unsigned int N> \
inline Vector<T,N> operator op ( Vector<T,N> v1, const Vector<T,N>& v2 ) throw() \
{ \
	v1 op= v2; \
	return v1; \
}

DEFINE_VEC_BINARY_OPERATOR( + )
DEFINE_VEC_BINARY_OPERATOR( - )
DEFINE_VEC_BINARY_OPERATOR( * )
DEFINE_VEC_BINARY_OPERATOR( / )

#undef DEFINE_VEC_BINARY_OPERATOR

#define DEFINE_VEC_BINARY_OPERATOR(op) \
template<typename T, const unsigned int N> \
inline Vector<T,N> operator op ( Vector<T,N> v, const T s ) throw() \
{ \
	v op= s; \
	return v; \
}

DEFINE_VEC_BINARY_OPERATOR( * )
DEFINE_VEC_BINARY_OPERATOR( / )

#undef DEFINE_VEC_BINARY_OPERATOR

template<typename T, const unsigned int N>
inline Vector<T,N> operator - (const Vector<T,N>& v) throw()
{
	Vector<T,N> ret;

	for ( unsigned int i = 0; i < N; i++ )
	{
		ret[i] = -v[i];
	}

	return ret;		
}

// operations

template<typename T, const unsigned int N>
inline T dot( const Vector<T,N>& v1, const Vector<T,N>& v2 ) throw()
{
	T dot = v1[0] * v2[0];
	for ( unsigned int i = 1; i < N; i++ )
	{
		dot += v1[i] * v2[i];
	}
	return dot;
}

template<typename T, const unsigned int N>
inline T length( const Vector<T,N>& vec ) throw()
{
	return sqrt( dot( vec, vec ) );
}

template<typename T, const unsigned int N>
inline T distance( const Vector<T,N>& vecFrom, const Vector<T,N>& vecTo ) throw()
{
	return length( vecFrom - vecTo );
}

template<typename T>
inline Vector<T,3> cross( const Vector<T,3>& v1, const Vector<T,3>& v2 ) throw()
{
    return Vector<T,3>( v0.Y()*v1.Z() - v0.Z()*v1.Y(), v0.Z()*v1.X() - v0.X()*v1.Z(), v0.X()*v1.Y() - v0.Y()*v1.X() );
}

// constructors

template<typename T>
inline Vector<T,2> vec( const T& x, const T& y ) throw()
{
	T arr[] = { x, y };
	return Vector<T,2>( arr );
}

template<typename T>
inline Vector<T,3> vec( const T& x, const T& y, const T& z ) throw()
{
	T arr[] = { x, y, z };
	return Vector<T,3>( arr );
}

template<typename T>
inline Vector<T,4> vec( const T& x, const T& y, const T& z, const T& w ) throw()
{
	T arr[] = { x, y, z, w };
	return Vector<T,4>( arr );
}

} // namespace math
#endif