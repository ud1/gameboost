/** 
* \file matrix4x4fpu_impl.h
* \brief Математическая библиотека с поддержкой SIMD инструкций
* \author Vincent Barabus
*/
#pragma once

inline Matrix4x4f& Matrix4x4f::operator *= ( const Matrix4x4f& M)
{
	Matrix4x4f result;

	result._11 = _11 * M._11 + _12 * M._21 + _13 * M._31 + _14 * M._41;
	result._12 = _11 * M._12 + _12 * M._22 + _13 * M._32 + _14 * M._42;
	result._13 = _11 * M._13 + _12 * M._23 + _13 * M._33 + _14 * M._43;
	result._14 = _11 * M._14 + _12 * M._24 + _13 * M._34 + _14 * M._44;
	result._21 = _21 * M._11 + _22 * M._21 + _23 * M._31 + _24 * M._41;
	result._22 = _22 * M._22 + _21 * M._12 + _23 * M._32 + _24 * M._42;
	result._23 = _22 * M._23 + _21 * M._13 + _23 * M._33 + _24 * M._43;
	result._24 = _22 * M._24 + _21 * M._14 + _23 * M._34 + _24 * M._44;
	result._31 = _31 * M._11 + _32 * M._21 + _33 * M._31 + _34 * M._41;
	result._32 = _32 * M._22 + _31 * M._12 + _33 * M._32 + _34 * M._42;
	result._33 = _32 * M._23 + _31 * M._13 + _33 * M._43 + _34 * M._33;
	result._34 = _32 * M._24 + _31 * M._14 + _33 * M._34 + _34 * M._44;
	result._41 = _42 * M._21 + _41 * M._11 + _43 * M._31 + _44 * M._41;
	result._42 = _41 * M._12 + _42 * M._22 + _43 * M._32 + _44 * M._42;
	result._43 = _41 * M._13 + _42 * M._23 + _43 * M._33 + _44 * M._43;
	result._44 = _41 * M._14 + _42 * M._24 + _43 * M._34 + _44 * M._44;

	*this = result;
	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator += ( const Matrix4x4f& M)
{
	_11 += M._11;
	_12 += M._12;
	_13 += M._13;
	_14 += M._14;
	_21 += M._21;
	_22 += M._22;
	_23 += M._23;
	_24 += M._24;
	_31 += M._31;
	_32 += M._32;
	_33 += M._33;
	_34 += M._34;
	_41 += M._41;
	_42 += M._42;
	_43 += M._43;
	_44 += M._44;

	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator -= ( const Matrix4x4f& M)
{
	_11 -= M._11;
	_12 -= M._12;
	_13 -= M._13;
	_14 -= M._14;
	_21 -= M._21;
	_22 -= M._22;
	_23 -= M._23;
	_24 -= M._24;
	_31 -= M._31;
	_32 -= M._32;
	_33 -= M._33;
	_34 -= M._34;
	_41 -= M._41;
	_42 -= M._42;
	_43 -= M._43;
	_44 -= M._44;

	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator *= ( float F)
{
	_11 *= F;
	_12 *= F;
	_13 *= F;
	_14 *= F;
	_21 *= F;
	_22 *= F;
	_23 *= F;
	_24 *= F;
	_31 *= F;
	_32 *= F;
	_33 *= F;
	_34 *= F;
	_41 *= F;
	_42 *= F;
	_43 *= F;
	_44 *= F;

	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator /= ( float F)
{
	_11 /= F;
	_12 /= F;
	_13 /= F;
	_14 /= F;
	_21 /= F;
	_22 /= F;
	_23 /= F;
	_24 /= F;
	_31 /= F;
	_32 /= F;
	_33 /= F;
	_34 /= F;
	_41 /= F;
	_42 /= F;
	_43 /= F;
	_44 /= F;

	return *this;
}

inline Matrix4x4f Matrix4x4f::operator - () const
{
	return Matrix4x4f(	-_11, -_12, -_13, -_14,
	                    -_21, -_22, -_23, -_24,
	                    -_31, -_32, -_33, -_34,
	                    -_41, -_42, -_43, -_44 );
}

/*!
 \brief перемножение матриц
*/
inline Matrix4x4f operator * ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	Matrix4x4f result;

	result._11 = M1._11 * M2._11 + M1._12 * M2._21 + M1._13 * M2._31 + M1._14 * M2._41;
	result._12 = M1._11 * M2._12 + M1._12 * M2._22 + M1._13 * M2._32 + M1._14 * M2._42;
	result._13 = M1._11 * M2._13 + M1._12 * M2._23 + M1._13 * M2._33 + M1._14 * M2._43;
	result._14 = M1._11 * M2._14 + M1._12 * M2._24 + M1._13 * M2._34 + M1._14 * M2._44;
	result._21 = M1._21 * M2._11 + M1._22 * M2._21 + M1._23 * M2._31 + M1._24 * M2._41;
	result._22 = M1._22 * M2._22 + M1._21 * M2._12 + M1._23 * M2._32 + M1._24 * M2._42;
	result._23 = M1._22 * M2._23 + M1._21 * M2._13 + M1._23 * M2._33 + M1._24 * M2._43;
	result._24 = M1._22 * M2._24 + M1._21 * M2._14 + M1._23 * M2._34 + M1._24 * M2._44;
	result._31 = M1._31 * M2._11 + M1._32 * M2._21 + M1._33 * M2._31 + M1._34 * M2._41;
	result._32 = M1._32 * M2._22 + M1._31 * M2._12 + M1._33 * M2._32 + M1._34 * M2._42;
	result._33 = M1._32 * M2._23 + M1._31 * M2._13 + M1._33 * M2._43 + M1._34 * M2._33;
	result._34 = M1._32 * M2._24 + M1._31 * M2._14 + M1._33 * M2._34 + M1._34 * M2._44;
	result._41 = M1._42 * M2._21 + M1._41 * M2._11 + M1._43 * M2._31 + M1._44 * M2._41;
	result._42 = M1._41 * M2._12 + M1._42 * M2._22 + M1._43 * M2._32 + M1._44 * M2._42;
	result._43 = M1._41 * M2._13 + M1._42 * M2._23 + M1._43 * M2._33 + M1._44 * M2._43;
	result._44 = M1._41 * M2._14 + M1._42 * M2._24 + M1._43 * M2._34 + M1._44 * M2._44;

	return result;
}

/*!
 \brief Поэлементное сложение матриц
*/
inline Matrix4x4f operator + ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	Matrix4x4f result;

	result._11 = M1._11 + M2._11;
	result._12 = M1._12 + M2._12;
	result._13 = M1._13 + M2._13;
	result._14 = M1._14 + M2._14;
	result._21 = M1._21 + M2._21;
	result._22 = M1._22 + M2._22;
	result._23 = M1._23 + M2._23;
	result._24 = M1._24 + M2._24;
	result._31 = M1._31 + M2._31;
	result._32 = M1._32 + M2._32;
	result._33 = M1._33 + M2._33;
	result._34 = M1._34 + M2._34;
	result._41 = M1._41 + M2._41;
	result._42 = M1._42 + M2._42;
	result._43 = M1._43 + M2._43;
	result._44 = M1._44 + M2._44;

	return result;
}

/*!
 \brief Поэлементное вычитание матриц
*/
inline Matrix4x4f operator - ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	Matrix4x4f result;

	result._11 = M1._11 - M2._11;
	result._12 = M1._12 - M2._12;
	result._13 = M1._13 - M2._13;
	result._14 = M1._14 - M2._14;
	result._21 = M1._21 - M2._21;
	result._22 = M1._22 - M2._22;
	result._23 = M1._23 - M2._23;
	result._24 = M1._24 - M2._24;
	result._31 = M1._31 - M2._31;
	result._32 = M1._32 - M2._32;
	result._33 = M1._33 - M2._33;
	result._34 = M1._34 - M2._34;
	result._41 = M1._41 - M2._41;
	result._42 = M1._42 - M2._42;
	result._43 = M1._43 - M2._43;
	result._44 = M1._44 - M2._44;

	return result;
}

/*!
 \brief Умножение всех элементов матрицы на скаляр
*/
inline Matrix4x4f operator * ( const Matrix4x4f& M, float F )
{
	Matrix4x4f result;

	result._11 = M._11 * F;
	result._12 = M._12 * F;
	result._13 = M._13 * F;
	result._14 = M._14 * F;
	result._21 = M._21 * F;
	result._22 = M._22 * F;
	result._23 = M._23 * F;
	result._24 = M._24 * F;
	result._31 = M._31 * F;
	result._32 = M._32 * F;
	result._33 = M._33 * F;
	result._34 = M._34 * F;
	result._41 = M._41 * F;
	result._42 = M._42 * F;
	result._43 = M._43 * F;
	result._44 = M._44 * F;

	return result;
}

/*!
 \brief Деление всех элементов матрицы на скаляр
*/
inline Matrix4x4f operator / ( const Matrix4x4f& M, float F )
{
	Matrix4x4f result;

	result._11 = M._11 / F;
	result._12 = M._12 / F;
	result._13 = M._13 / F;
	result._14 = M._14 / F;
	result._21 = M._21 / F;
	result._22 = M._22 / F;
	result._23 = M._23 / F;
	result._24 = M._24 / F;
	result._31 = M._31 / F;
	result._32 = M._32 / F;
	result._33 = M._33 / F;
	result._34 = M._34 / F;
	result._41 = M._41 / F;
	result._42 = M._42 / F;
	result._43 = M._43 / F;
	result._44 = M._44 / F;

	return result;
}

/*!
 \brief Строгое сравнение
*/
inline bool operator == ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	return ( (M1._11 == M2._11) &&
	         (M1._12 == M2._12) &&
	         (M1._13 == M2._13) &&
	         (M1._14 == M2._14) &&
	         (M1._21 == M2._21) &&
	         (M1._22 == M2._22) &&
	         (M1._23 == M2._23) &&
	         (M1._24 == M2._24) &&
	         (M1._31 == M2._31) &&
	         (M1._32 == M2._32) &&
	         (M1._33 == M2._33) &&
	         (M1._34 == M2._34) &&
	         (M1._41 == M2._41) &&
	         (M1._42 == M2._42) &&
	         (M1._43 == M2._43) &&
	         (M1._44 == M2._44) );
}

/*!
 \brief Строгое сравнение с отрицанием
*/
inline bool operator != ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	return ( (M1._11 != M2._11) ||
	         (M1._12 != M2._12) ||
	         (M1._13 != M2._13) ||
	         (M1._14 != M2._14) ||
	         (M1._21 != M2._21) ||
	         (M1._22 != M2._22) ||
	         (M1._23 != M2._23) ||
	         (M1._24 != M2._24) ||
	         (M1._31 != M2._31) ||
	         (M1._32 != M2._32) ||
	         (M1._33 != M2._33) ||
	         (M1._34 != M2._34) ||
	         (M1._41 != M2._41) ||
	         (M1._42 != M2._42) ||
	         (M1._43 != M2._43) ||
	         (M1._44 != M2._44) );
}

/*!
 \brief Умножение вектора на матрицу
*/
inline Vector4f operator * ( const Vector4f& V, const Matrix4x4f& M )
{
	Vector4f result;

	result.x = M._11 * V.x + M._21 * V.y + M._31 * V.z + M._41 * V.w;
	result.y = M._12 * V.x + M._22 * V.y + M._32 * V.z + M._42 * V.w;
	result.z = M._13 * V.x + M._23 * V.y + M._33 * V.z + M._43 * V.w;
	result.w = M._14 * V.x + M._24 * V.y + M._34 * V.z + M._44 * V.w;

	return result;
}