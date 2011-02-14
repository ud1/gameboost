#pragma once

namespace pmath
{

// row major matrix

template< typename T, const unsigned int N> 
class Matrix
{
public:
	typedef T type;

	enum
	{
		Rows = N,
		Cols = N,
		Cells = Rows*Cols,
	};

	inline Matrix() throw();
	inline Matrix( const T* arr ) throw();
	inline Matrix( const Matrix& matrix ) throw();
	inline Matrix( Matrix&& matrix ) throw();
	inline Matrix& operator = ( const Matrix& matrix ) throw();
	inline Matrix& operator = ( Matrix&& matrix ) throw();

	inline T& operator() ( unsigned int cell ) throw();
	inline T operator() ( unsigned int cell ) const throw();
	inline T& operator() ( unsigned int row, unsigned int col ) throw();
	inline T operator() ( unsigned int row, unsigned int col ) const throw();
	inline T* operator[] (unsigned int row) throw();
	inline const T* operator[] (unsigned int row) const throw();

	template<typename S>
	inline Matrix<T,N>& operator += ( const Matrix<S,N>& other ) throw();

	inline Matrix<T,N>& operator *= ( const Matrix<T,N>& other ) throw();

	template<typename S>
	inline Matrix<T,N>& operator *= ( S s ) throw();

	bool invert();
	Matrix<T,N> invert() const;

	const T* get() const throw() { return &mValue[0]; }
private:
	T mValue[Cells];
};

template< typename T, const unsigned int N>
inline Matrix<T,N> operator * ( const Matrix<T,N>& m1, const Matrix<T,N>& m2 ) throw();

template< typename T, const unsigned int N>
inline Vector<T,N> operator * ( const Matrix<T,N>& mat, const Vector<T,N>& vec ) throw();

template< typename T, const unsigned int N>
inline Vector<T,N> operator * ( const Vector<T,N>& vec, const Matrix<T,N>& mat ) throw();

template< typename T, const unsigned int N>
inline Matrix<T,N> operator + ( Matrix<T,N> m1, const Matrix<T,N>& m2 ) throw();

template< typename T, const unsigned int N>
inline Matrix<T,N> operator - ( Matrix<T,N> m1, const Matrix<T,N>& m2 ) throw();

template<typename T>
inline Matrix<T,4> matrix( const T data[16] );

template<typename T>
inline Matrix<T,4> matrix( const T& d0, const T& d1, const T& d2, const T& d3,
						const T& d4, const T& d5, const T& d6, const T& d7,
						const T& d8, const T& d9, const T& d10, const T& d11,
						const T& d12, const T& d13, const T& d14, const T& d15 );

}

#include "Matrix.inl"