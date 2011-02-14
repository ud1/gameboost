#pragma once

namespace pmath
{

template< typename T, const unsigned int N> 
inline Matrix<T,N>::Matrix() throw()
{
	fill<T, Cells>( mValue, T(0) );
	for ( unsigned int i = 0; i < N; ++i )
	{
		(*this)(i,i) = T(1);
	}
}

template< typename T, const unsigned int N> 
inline Matrix<T,N>::Matrix( const T* arr ) throw()
{
	copy<T, Cells>( mValue, arr );
}

template< typename T, const unsigned int N> 
inline Matrix<T,N>::Matrix( const Matrix<T,N>& matrix ) throw()
{
	copy<T, Cells>( mValue, matrix.mValue );
}

template< typename T, const unsigned int N> 
inline Matrix<T,N>::Matrix( Matrix&& matrix ) throw()
{
	copy<T, Cells>( mValue, matrix.mValue );
}

template< typename T, const unsigned int N> 
inline Matrix<T,N>& Matrix<T,N>::operator = ( const Matrix<T,N>& matrix ) throw()
{
	if (this != &matrix)
	{
		copy<T, Cells>( mValue, matrix.mValue );
	}
	return *this;
}

template< typename T, const unsigned int N>
inline Matrix<T,N>& Matrix<T,N>::operator = ( Matrix<T,N>&& matrix ) throw()
{
	if (this != &matrix) 
	{
		copy<T, Cells>( mValue, matrix.mValue );
	}
	return *this;
}

template< typename T, const unsigned int N> 
inline T& Matrix<T,N>::operator() ( unsigned int cell ) throw()
{
	PMATH_ASSERT( cell < Cells );
	return mValue[cell];
}

template< typename T, const unsigned int N> 
inline T Matrix<T,N>::operator() ( unsigned int cell ) const throw()
{
	PMATH_ASSERT( cell < Cells );
	return mValue[cell];
}

template< typename T, const unsigned int N> 
inline T& Matrix<T,N>::operator() ( unsigned int row, unsigned int col ) throw()
{
	return (*this)( row * Cols + col );
}

template< typename T, const unsigned int N> 
inline T Matrix<T,N>::operator() ( unsigned int row, unsigned int col ) const throw()
{
	return (*this)( row * Cols + col );
}

template< typename T, const unsigned int N> 
inline T* Matrix<T,N>::operator[] (unsigned int row) throw()
{
	PMATH_ASSERT( Cols*row < Cells );
	return &mValue[Cols*row];
}

template< typename T, const unsigned int N> 
inline const T* Matrix<T,N>::operator[] (unsigned int row) const throw()
{
	PMATH_ASSERT( Cols*row < Cells );
	return &mValue[Cols*row];
}

template< typename T, const unsigned int N>
template< typename S >
inline Matrix<T,N>& Matrix<T,N>::operator += ( const Matrix<S,N>& other ) throw()
{																			
	for( unsigned int row = 0; row < Rows; ++row )							
	{																		
		for ( unsigned int col = 0; col < Cols; ++col )						
		{																	
			(*this)(row, col) += other(row, col);							
		}																	
	}																		
}

template< typename T, const unsigned int N>
inline Matrix<T,N>& Matrix<T,N>::operator *= ( const Matrix<T,N>& other ) throw()
{																			
	*this = *this * other;
	return *this;
}


template< typename T, const unsigned int N>
template<typename S>
inline Matrix<T,N>& Matrix<T,N>::operator *= ( S s ) throw()
{
	for( unsigned int row = 0; row < Rows; ++row )							
	{																		
		for ( unsigned int col = 0; col < Cols; ++col )						
		{																	
			(*this)(row, col) *= s;							
		}																	
	}
}


template< typename T, const unsigned int N>
bool Matrix<T,N>::invert()
{
	unsigned int p[n];

	bool ok = true;
	for ( unsigned int k=0 ; ok && k<N ; ++k )
	{
		T max(0);
		p[k] = 0;
		for ( unsigned int i=k ; ok && i<N ; ++i )
		{
			T s(0);
			for ( unsigned int j=k ; j<N ; ++j )
			{
				s += abs( (*this)(i,j) );
			}
			ok = ( std::numeric_limits<T>::epsilon() < abs(s) );
			if ( ok )
			{
				T q = abs( (*this)(i,k) ) / s;
				if ( q > max )
				{
					max = q;
					p[k] = i;
				}
			}
		}

		ok = ( std::numeric_limits<T>::epsilon() < max );
		if ( ok )
		{
			if ( p[k] != k )
			{
				for ( unsigned int j=0 ; j<n ; ++j )
				{
					std::swap( (*this)(k,j), (*this)(p[k],j) );
				}
			}

			T pivot = (*this)(k,k);
			ok = ( std::numeric_limits<T>::epsilon() < abs( pivot ) );
			if ( ok )
			{
				for ( unsigned int j=0 ; j<n ; ++j )
				{
					if ( j != k )
					{
						(*this)(k,j) /= - pivot;
						for ( unsigned int i=0 ; i<n ; ++i )
						{
							if ( i != k )
							{
								(*this)(i,j) += (*this)(i,k) * (*this)(k,j);
							}
						}
					}
				}

				for ( unsigned int i=0 ; i<n ; ++i )
				{
					(*this)(i,k) /= pivot;
				}
				(*this)(k,k) = 1.0f / pivot;
			}
		}
	}

	if ( ok )
	{
		for ( unsigned int k=n-2 ; k<n ; --k )  //  NOTE: ( unsigned int k < n ) <=> ( int k >= 0 )
		{
			if ( p[k] != k )
			{
				for ( unsigned int i=0 ; i<n ; ++i )
				{
					std::swap( (*this)(i,k), (*this)(i,p[k]) );
				}
			}
		}
	}

	return( ok );
}

template< typename T, const unsigned int N>
inline Matrix<T,N> Matrix<T,N>::invert() const
{
	Matrix<T,N> matrix = (*this);
	if ( matrix.invert() == false )
	{
		matrix *= 0;
	}
	return matrix;
}

template< typename T, const unsigned int N>
inline Matrix<T,N> invert( Matrix<T,N> matrix )
{
	matrix.invert();
	return matrix;
}

//////// operators

template< typename T, const unsigned int N>
inline Matrix<T,N> operator * ( const Matrix<T,N>& m1, const Matrix<T,N>& m2 ) throw()
{
	Matrix<T,N> ret;																		
	for( unsigned int row = 0; row < N; ++row )							
	{																		
		for ( unsigned int col = 0; col < N; ++col )						
		{
			ret(row,col) = T(0);
			for ( unsigned int i = 0; i < N; i++ )
			{
				ret(row,col) += m1(row,i) * m2(i,col);
			}
		}																	
	}
	return ret;
}

template< typename T, const unsigned int N>
inline Vector<T,N> operator * ( const Matrix<T,N>& mat, const Vector<T,N>& vec ) throw()
{
	Vector<T,N> ret;																		
	for( unsigned int row = 0; row < N; ++row )							
	{	
		ret(row) = T(0);																	
		for ( unsigned int col = 0; col < N; ++col )						
		{
			ret(row) += mat(row,col) * vec(i);
		}																	
	}
	return ret;
}

template< typename T, const unsigned int N>
inline Vector<T,N> operator * ( const Vector<T,N>& vec, const Matrix<T,N>& mat ) throw()
{
	Vector<T,N> ret;																		
	for( unsigned int row = 0; row < N; ++row )							
	{
		ret(row) = T(0);																		
		for ( unsigned int col = 0; col < N; ++col )						
		{
			ret(row) += vec(col) * mat(col, row);
		}																	
	}
	return ret;
}

template< typename T, const unsigned int N>
inline Matrix<T,N> operator + ( Matrix<T,N> m1, const Matrix<T,N>& m2 ) throw()
{
	m1 += m2;
	return m1;
}

template< typename T, const unsigned int N>
inline Matrix<T,N> operator - ( Matrix<T,N> m1, const Matrix<T,N>& m2 ) throw()
{
	m1 -= m2;
	return m1;
}

// constructors
template<typename T>
inline Matrix<T,4> matrix( const T data[16] )
{
	return Matrix<T,4>( data );
}

template<typename T>
inline Matrix<T,4> matrix( const T& d0, const T& d1, const T& d2, const T& d3,
						const T& d4, const T& d5, const T& d6, const T& d7,
						const T& d8, const T& d9, const T& d10, const T& d11,
						const T& d12, const T& d13, const T& d14, const T& d15 )
{
	const T data[16] = { d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15 };
	return Matrix<T,4>( data );
}

}