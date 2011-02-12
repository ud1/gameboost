#pragma once

#include "vector.h"

namespace gb
{

namespace math
{

class Matrix3x3f
{
public:
	Matrix3x3f() {}
	Matrix3x3f( const Matrix3x3f& M );
	Matrix3x3f( float _11_, float _12_, float _13_,
	            float _21_, float _22_, float _23_,
	            float _31_, float _32_, float _33_ ) : 
	_11( _11_ ), _12( _12_ ), _13( _13_ ),
	_21( _21_ ), _22( _22_ ), _23( _23_ ),
	_31( _31_ ), _32( _32_ ), _33( _33_ ) {}

	// access grants
	inline float& operator () ( unsigned int Row, unsigned int Col )
	{
		assert( (Row <= 2) && (Col <= 2) );
		return reinterpret_cast<Vector3f*>(this)[Row][Col];
	}

	inline float  operator () ( unsigned int Row, unsigned int Col ) const
	{
		assert( (Row <= 2) && (Col <= 2) );
		return reinterpret_cast<const Vector3f*>(this)[Row][Col];
	}

	// row access operators
	inline Vector3f& operator [] ( unsigned int index )
	{
		assert( index <= 2 );
		return reinterpret_cast<Vector3f*>(this)[index];
	}

	inline const Vector3f operator [] ( unsigned int index ) const
	{
		assert( index <= 2 );
		return reinterpret_cast<const Vector3f*>(this)[index];
	}

	// unary operators
	inline Matrix3x3f operator - () const;

	// assignment operators
	inline Matrix3x3f& operator *= ( const Matrix3x3f& );
	inline Matrix3x3f& operator += ( const Matrix3x3f& );
	inline Matrix3x3f& operator -= ( const Matrix3x3f& );
	inline Matrix3x3f& operator *= ( float );
	inline Matrix3x3f& operator /= ( float );

	// binary operators
	inline Matrix3x3f operator * ( const Matrix3x3f& ) const;
	inline Matrix3x3f operator + ( const Matrix3x3f& ) const;
	inline Matrix3x3f operator - ( const Matrix3x3f& ) const;
	inline Matrix3x3f operator * ( float ) const;
	inline Matrix3x3f operator / ( float ) const;

	inline bool operator == ( const Matrix3x3f& ) const;
	inline bool operator != ( const Matrix3x3f& ) const;
public:
	float _11, _12, _13,
	      _21, _22, _23,
	      _31, _32, _33;
};

class
#ifndef _GB_NO_SIMD_
__declspec(align(16))
#endif
Matrix4x4f
{
public:
	Matrix4x4f() {}
	Matrix4x4f( const Matrix4x4f& M ) :
	_11( M._11 ), _12( M._12 ), _13( M._13 ), _14( M._14 ),
	_21( M._21 ), _22( M._22 ), _23( M._23 ), _24( M._24 ),
	_31( M._31 ), _32( M._32 ), _33( M._33 ), _34( M._34 ),
	_41( M._41 ), _42( M._42 ), _43( M._43 ), _44( M._44 ) {}
	Matrix4x4f( float _11_, float _12_, float _13_, float _14_,
	            float _21_, float _22_, float _23_, float _24_,
	            float _31_, float _32_, float _33_, float _34_,
	            float _41_, float _42_, float _43_, float _44_ ) : 
	_11( _11_ ), _12( _12_ ), _13( _13_ ), _14( _14_ ),
	_21( _21_ ), _22( _22_ ), _23( _23_ ), _24( _24_ ),
	_31( _31_ ), _32( _32_ ), _33( _33_ ), _34( _34_ ),
	_41( _41_ ), _42( _42_ ), _43( _43_ ), _44( _44_ ) {}
	

	// access grants
	inline float& operator () ( unsigned int Row, unsigned int Col )
	{
		assert( (Row <= 3) && (Col <= 3) );
		return reinterpret_cast<Vector4f*>(this)[Row][Col];
	}

	inline float  operator () ( unsigned int Row, unsigned int Col ) const
	{
		assert( (Row <= 3) && (Col <= 3) );
		return reinterpret_cast<const Vector4f*>(this)[Row][Col];
	}

	// row access operators
	inline Vector4f& operator [] ( unsigned int index )
	{
		assert( index <= 3 );
		return reinterpret_cast<Vector4f*>(this)[index];
	}

	inline const Vector4f operator [] ( unsigned int index ) const
	{
		assert( index <= 3 );
		return reinterpret_cast<const Vector4f*>(this)[index];
	}

	inline Matrix4x4f& operator = ( const Matrix4x4f& M )
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = M._14;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = M._24;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = M._34;
		_41 = M._41; _42 = M._42; _43 = M._43; _44 = M._44;

		return *this;
	}

	// unary operators
	inline Matrix4x4f operator - () const;

	// assignment operators
	inline Matrix4x4f& operator *= ( const Matrix4x4f& M);
	inline Matrix4x4f& operator += ( const Matrix4x4f& M);
	inline Matrix4x4f& operator -= ( const Matrix4x4f& M);
	inline Matrix4x4f& operator *= ( float F);
	inline Matrix4x4f& operator /= ( float F);

/*
	// binary operators
	inline Matrix4x4f operator * ( const Matrix4x4f& ) const;
	inline Matrix4x4f operator + ( const Matrix4x4f& ) const;
	inline Matrix4x4f operator - ( const Matrix4x4f& ) const;
	inline Matrix4x4f operator * ( float ) const;
	inline Matrix4x4f operator / ( float ) const;

	inline bool operator == ( const Matrix4x4f& ) const;
	inline bool operator != ( const Matrix4x4f& ) const;
*/
public:
#ifndef _GB_NO_SIMD_
	union
	{
		struct
		{
#endif

		float _11, _12, _13, _14,
			  _21, _22, _23, _24,
			  _31, _32, _33, _34,
			  _41, _42, _43, _44;
#ifndef _GB_NO_SIMD_
		};
		struct
		{
			__m128 row0;
			__m128 row1;
			__m128 row2;
			__m128 row3;
		};
	};
#endif
};

#ifndef _GB_NO_SIMD_
#include "matrix4x4simd_impl.h"
#else
#include "matrix4x4fpu_impl.h"
#endif

}

}

