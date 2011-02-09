#ifndef MATH_ALGORYTM_H
#define MATH_ALGORYTM_H

namespace pmath
{

using ::std::min;
using ::std::max;

template<typename T>
inline T sqr( const T val ) throw()
{
	return val * val;
}

template<typename T>
inline T sqrt( const T val) throw()
{
	return T(::sqrt(double(val)));
}

template<typename T> 
inline T lerp( float alpha, const T &v0, const T &v1 ) throw()
{
	return( (T)(v0 + alpha * ( v1 - v0 )) );
}

template<class T> 
inline T clamp( const T& v, const T& l, const T& u ) throw()
{
	return min(u, max(l,v));
}

template<typename T, const unsigned int Count>
inline void fill( T * dest, const T val ) throw()
{
	for (unsigned int i = 0; i < Count; i++)
	{
		dest[i] = val;
	}
}

template<typename T, const unsigned int Count>
inline void copy( T * dest, const T * val ) throw()
{
	for (unsigned int i = 0; i < Count; i++)
	{
		dest[i] = val[i];
	}
}

}

#endif // MATH_ALGORYTM_H