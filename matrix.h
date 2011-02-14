/** 
* \file matrix.h
* \brief Математическая библиотека с поддержкой SIMD инструкций
* \author Vincent Barabus
*/
#pragma once

#include "vector.h"

namespace gb
{

namespace math
{

/*!
 \class Matrix2x2f
*/
class Matrix2x2f
{
public:
	/*!
	 \brief Конструктор по умолчанию
	*/
	Matrix2x2f() {}
	/*!
	 \brief Конструктор копирования
	*/
	Matrix2x2f( const Matrix2x2f& M );
	/*!
	 \brief Конструктор
	*/
	Matrix2x2f( float _11_, float _12_,
	            float _21_, float _22_ ) : 
	_11( _11_ ), _12( _12_ ),
	_21( _21_ ), _22( _22_ ) {}
	/*!
	 \brief Доступ к элементам матрицы по индексу строки и столбца
	*/
	inline float& operator () ( unsigned int Row, unsigned int Col )
	{
		assert( Col <= 1 );
		return reinterpret_cast<Vector2f*>(this)[Row][Col];
	}
	/*!
	 \brief Доступ к элементам матрицы по индексу строки и столбца
	*/
	inline float  operator () ( unsigned int Row, unsigned int Col ) const
	{
		assert( Col <= 1 );
		return reinterpret_cast<const Vector2f*>(this)[Row][Col];
	}
	/*!
	 \brief Доступ к строкам матрицы по индексу
	*/
	inline Vector2f& operator [] ( unsigned int index )
	{
		assert( index <= 1 );
		return reinterpret_cast<Vector2f*>(this)[index];
	}
	/*!
	 \brief Доступ к строкам матрицы по индексу
	*/
	inline const Vector2f operator [] ( unsigned int index ) const
	{
		assert( index <= 1 );
		return reinterpret_cast<const Vector2f*>(this)[index];
	}
	/*!
	 \brief Обращение знака всех элементов матрицы
	*/
	inline Matrix2x2f operator - () const;

	/*!
	 \brief Умножение на матрицу с присваиванием
	*/
	inline Matrix2x2f& operator *= ( const Matrix2x2f& );
	/*!
	 \brief Поэлементное сложение с присваиванием
	*/
	inline Matrix2x2f& operator += ( const Matrix2x2f& );
	/*!
	 \brief Поэлементное вычитание с присваиванием
	*/
	inline Matrix2x2f& operator -= ( const Matrix2x2f& );
	/*!
	 \brief Умножение всех элементов матрицы на скаляр с присваиванием
	*/
	inline Matrix2x2f& operator *= ( float );
	/*!
	 \brief Деление всех элементов матрицы на скаляр с присваиванием
	*/
	inline Matrix2x2f& operator /= ( float );
public:
	float _11, _12,
	      _21, _22;
};


/*!
 \class Matrix3x3f
*/
class Matrix3x3f
{
public:
	/*!
	 \brief Конструктор по умолчанию
	*/
	Matrix3x3f() {}
	/*!
	 \brief Конструктор копирования
	*/
	Matrix3x3f( const Matrix3x3f& M );
	/*!
	 \brief Конструктор
	*/
	Matrix3x3f( float _11_, float _12_, float _13_,
	            float _21_, float _22_, float _23_,
	            float _31_, float _32_, float _33_ ) : 
	_11( _11_ ), _12( _12_ ), _13( _13_ ),
	_21( _21_ ), _22( _22_ ), _23( _23_ ),
	_31( _31_ ), _32( _32_ ), _33( _33_ ) {}
	/*!
	 \brief Доступ к элементам матрицы по индексу строки и столбца
	*/
	inline float& operator () ( unsigned int Row, unsigned int Col )
	{
		assert( Col <= 2 );
		return reinterpret_cast<Vector3f*>(this)[Row][Col];
	}
	/*!
	 \brief Доступ к элементам матрицы по индексу строки и столбца
	*/
	inline float  operator () ( unsigned int Row, unsigned int Col ) const
	{
		assert( Col <= 2 );
		return reinterpret_cast<const Vector3f*>(this)[Row][Col];
	}
	/*!
	 \brief Доступ к строкам матрицы по индексу
	*/
	inline Vector3f& operator [] ( unsigned int index )
	{
		assert( index <= 2 );
		return reinterpret_cast<Vector3f*>(this)[index];
	}
	/*!
	 \brief Доступ к строкам матрицы по индексу
	*/
	inline const Vector3f operator [] ( unsigned int index ) const
	{
		assert( index <= 2 );
		return reinterpret_cast<const Vector3f*>(this)[index];
	}
	/*!
	 \brief Обращение знака всех элементов матрицы
	*/
	inline Matrix3x3f operator - () const;
	/*!
	 \brief Умножение на матрицу с присваиванием
	*/
	inline Matrix3x3f& operator *= ( const Matrix3x3f& );
	/*!
	 \brief Поэлементное сложение с присваиванием
	*/
	inline Matrix3x3f& operator += ( const Matrix3x3f& );
	/*!
	 \brief Поэлементное вычитание с присваиванием
	*/
	inline Matrix3x3f& operator -= ( const Matrix3x3f& );
	/*!
	 \brief Умножение всех элементов матрицы на скаляр с присваиванием
	*/
	inline Matrix3x3f& operator *= ( float );
	/*!
	 \brief Деление всех элементов матрицы на скаляр с присваиванием
	*/
	inline Matrix3x3f& operator /= ( float );
	/*!
	 \brief Преобразование в матрицу 2x2
	*/
	inline operator Matrix2x2f()
	{
		return Matrix2x2f(_11, _12,
			              _21, _22 );
	}
public:
	float _11, _12, _13,
	      _21, _22, _23,
	      _31, _32, _33;
};

/*!
 \class Matrix4x4f
*/
class
#ifndef _GB_NO_SIMD_
__declspec(align(16))
#endif
Matrix4x4f
{
public:
	/*!
	 \brief Конструктор по умолчанию
	*/
	Matrix4x4f() {}
	/*!
	 \brief Конструктор копирования
	*/
	Matrix4x4f( const Matrix4x4f& M ) :
	_11( M._11 ), _12( M._12 ), _13( M._13 ), _14( M._14 ),
	_21( M._21 ), _22( M._22 ), _23( M._23 ), _24( M._24 ),
	_31( M._31 ), _32( M._32 ), _33( M._33 ), _34( M._34 ),
	_41( M._41 ), _42( M._42 ), _43( M._43 ), _44( M._44 ) {}
	/*!
	 \brief Конструктор
	*/
	Matrix4x4f( float _11_, float _12_, float _13_, float _14_,
	            float _21_, float _22_, float _23_, float _24_,
	            float _31_, float _32_, float _33_, float _34_,
	            float _41_, float _42_, float _43_, float _44_ ) : 
	_11( _11_ ), _12( _12_ ), _13( _13_ ), _14( _14_ ),
	_21( _21_ ), _22( _22_ ), _23( _23_ ), _24( _24_ ),
	_31( _31_ ), _32( _32_ ), _33( _33_ ), _34( _34_ ),
	_41( _41_ ), _42( _42_ ), _43( _43_ ), _44( _44_ ) {}
	/*!
	 \brief Доступ к элементам матрицы по индексу строки и столбца
	*/
	inline float& operator () ( unsigned int Row, unsigned int Col )
	{
		assert( (Row <= 3) && (Col <= 3) );
		return reinterpret_cast<Vector4f*>(this)[Row][Col];
	}
	/*!
	 \brief Доступ к элементам матрицы по индексу строки и столбца
	*/
	inline float operator () ( unsigned int Row, unsigned int Col ) const
	{
		assert( (Row <= 3) && (Col <= 3) );
		return reinterpret_cast<const Vector4f*>(this)[Row][Col];
	}
	/*!
	 \brief Доступ к строкам матрицы по индексу
	*/
	inline Vector4f& operator [] ( unsigned int index )
	{
		assert( index <= 3 );
		return reinterpret_cast<Vector4f*>(this)[index];
	}
	/*!
	 \brief Доступ к строкам матрицы по индексу
	*/
	inline const Vector4f operator [] ( unsigned int index ) const
	{
		assert( index <= 3 );
		return reinterpret_cast<const Vector4f*>(this)[index];
	}
	/*!
	 \brief Оператор присваивания
	*/
	inline Matrix4x4f& operator = ( const Matrix4x4f& M )
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = M._14;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = M._24;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = M._34;
		_41 = M._41; _42 = M._42; _43 = M._43; _44 = M._44;

		return *this;
	}
	/*!
	 \brief Обращение знака всех элементов матрицы
	*/
	inline Matrix4x4f operator - () const;
	/*!
	 \brief Умножение на матрицу с присваиванием
	*/
	inline Matrix4x4f& operator *= ( const Matrix4x4f& M);
	/*!
	 \brief Поэлементное сложение с присваиванием
	*/
	inline Matrix4x4f& operator += ( const Matrix4x4f& M);
	/*!
	 \brief Поэлементное вычитание с присваиванием
	*/
	inline Matrix4x4f& operator -= ( const Matrix4x4f& M);
	/*!
	 \brief Умножение всех элементов матрицы на скаляр с присваиванием
	*/
	inline Matrix4x4f& operator *= ( float F);
	/*!
	 \brief Деление всех элементов матрицы на скаляр с присваиванием
	*/
	inline Matrix4x4f& operator /= ( float F);

#ifndef _GB_NO_SIMD_
	// операторы выделения и освобождения памяти с выравниванием
	inline void* operator new(unsigned int size)
	{
		return _aligned_malloc(size, 16); 
	}

	inline void* operator new[](unsigned int size)
	{
		return _aligned_malloc(size, 16); 
	}

	inline void operator delete(void * _ptr)
	{
		_aligned_free(_ptr);
	}

	inline void operator delete[](void * _ptr)
	{
		_aligned_free(_ptr);
	}
#endif
	/*!
	 \brief Преобразование в матрицу 3x3
	*/
	inline operator Matrix3x3f()
	{
		return Matrix3x3f(_11, _12, _13,
			              _21, _22, _23,
			              _31, _32, _33 );
	}
	/*!
	 \brief Преобразование в матрицу 2x2
	*/
	inline operator Matrix2x2f()
	{
		return Matrix2x2f(_11, _12,
			              _21, _22 );
	}
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
// члены для прямого тоступа к 128-битным полям матрицы
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

#include "matrix2x2fpu_impl.h"
#include "matrix3x3fpu_impl.h"
#ifndef _GB_NO_SIMD_
#include "matrix4x4simd_impl.h"
#else
#include "matrix4x4fpu_impl.h"
#endif

}

}

