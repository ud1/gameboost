#pragma once

inline Matrix4x4f& Matrix4x4f::operator *= ( const Matrix4x4f& M)
{
	Matrix4x4f result;

	__m128 VT3 = row0;
	__m128 VT0 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,0,0,0));
    __m128 VT1 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,1,1,1));
    __m128 VT2 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,2,2,2));
    VT3 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(3,3,3,3));
    VT0 = _mm_mul_ps(VT0,M.row0);
    VT1 = _mm_mul_ps(VT1,M.row1);
    VT2 = _mm_mul_ps(VT2,M.row2);
    VT3 = _mm_mul_ps(VT3,M.row3);
    VT0 = _mm_add_ps(VT0,VT2);
    VT1 = _mm_add_ps(VT1,VT3);
    VT0 = _mm_add_ps(VT0,VT1);
	row0 = VT0;

	VT3 = row1;
	VT0 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,0,0,0));
    VT1 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,1,1,1));
    VT2 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,2,2,2));
    VT3 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(3,3,3,3));
    VT0 = _mm_mul_ps(VT0,M.row0);
    VT1 = _mm_mul_ps(VT1,M.row1);
    VT2 = _mm_mul_ps(VT2,M.row2);
    VT3 = _mm_mul_ps(VT3,M.row3);
    VT0 = _mm_add_ps(VT0,VT2);
    VT1 = _mm_add_ps(VT1,VT3);
    VT0 = _mm_add_ps(VT0,VT1);
	row1 = VT0;

	VT3 = row2;
	VT0 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,0,0,0));
    VT1 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,1,1,1));
    VT2 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,2,2,2));
    VT3 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(3,3,3,3));
    VT0 = _mm_mul_ps(VT0,M.row0);
    VT1 = _mm_mul_ps(VT1,M.row1);
    VT2 = _mm_mul_ps(VT2,M.row2);
    VT3 = _mm_mul_ps(VT3,M.row3);
    VT0 = _mm_add_ps(VT0,VT2);
    VT1 = _mm_add_ps(VT1,VT3);
    VT0 = _mm_add_ps(VT0,VT1);
	row2 = VT0;

	VT3 = row3;
	VT0 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,0,0,0));
    VT1 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,1,1,1));
    VT2 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,2,2,2));
    VT3 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(3,3,3,3));
    VT0 = _mm_mul_ps(VT0,M.row0);
    VT1 = _mm_mul_ps(VT1,M.row1);
    VT2 = _mm_mul_ps(VT2,M.row2);
    VT3 = _mm_mul_ps(VT3,M.row3);
    VT0 = _mm_add_ps(VT0,VT2);
    VT1 = _mm_add_ps(VT1,VT3);
    VT0 = _mm_add_ps(VT0,VT1);
	row3 = VT0;

	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator += ( const Matrix4x4f& M)
{
	row0 = _mm_add_ps(row0,M.row0);
	row1 = _mm_add_ps(row1,M.row0);
	row2 = _mm_add_ps(row2,M.row0);
	row3 = _mm_add_ps(row3,M.row0);

	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator -= ( const Matrix4x4f& M)
{
	row0 = _mm_sub_ps(row0,M.row0);
	row1 = _mm_sub_ps(row1,M.row0);
	row2 = _mm_sub_ps(row2,M.row0);
	row3 = _mm_sub_ps(row3,M.row0);

	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator *= ( float F)
{
	__m128 VT = _mm_set_ps1(F);
	row0 = _mm_mul_ps(row0,VT);
	row1 = _mm_mul_ps(row1,VT);
	row2 = _mm_mul_ps(row2,VT);
	row3 = _mm_mul_ps(row3,VT);

	return *this;
}

inline Matrix4x4f& Matrix4x4f::operator /= ( float F)
{
	__m128 VT = _mm_set_ps1(F);
	row0 = _mm_div_ps(row0,VT);
	row1 = _mm_div_ps(row1,VT);
	row2 = _mm_div_ps(row2,VT);
	row3 = _mm_div_ps(row3,VT);

	return *this;
}

inline Matrix4x4f Matrix4x4f::operator - () const
{
	Matrix4x4f result;

	__m128 VT = _mm_set_ps1(-1.0f);
	result.row0 = _mm_mul_ps(row0,VT);
	result.row1 = _mm_mul_ps(row1,VT);
	result.row2 = _mm_mul_ps(row2,VT);
	result.row3 = _mm_mul_ps(row3,VT);

	return result;
}


// common operators
inline Matrix4x4f operator * ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	Matrix4x4f result;

	__m128 VT3 = M1.row0;
	__m128 VT0 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,0,0,0));
    __m128 VT1 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,1,1,1));
    __m128 VT2 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,2,2,2));
    VT3 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(3,3,3,3));
    VT0 = _mm_mul_ps(VT0,M2.row0);
    VT1 = _mm_mul_ps(VT1,M2.row1);
    VT2 = _mm_mul_ps(VT2,M2.row2);
    VT3 = _mm_mul_ps(VT3,M2.row3);
    VT0 = _mm_add_ps(VT0,VT2);
    VT1 = _mm_add_ps(VT1,VT3);
    VT0 = _mm_add_ps(VT0,VT1);
	result.row0 = VT0;

	VT3 = M1.row1;
	VT0 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,0,0,0));
    VT1 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,1,1,1));
    VT2 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,2,2,2));
    VT3 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(3,3,3,3));
    VT0 = _mm_mul_ps(VT0,M2.row0);
    VT1 = _mm_mul_ps(VT1,M2.row1);
    VT2 = _mm_mul_ps(VT2,M2.row2);
    VT3 = _mm_mul_ps(VT3,M2.row3);
    VT0 = _mm_add_ps(VT0,VT2);
    VT1 = _mm_add_ps(VT1,VT3);
    VT0 = _mm_add_ps(VT0,VT1);
	result.row1 = VT0;

	VT3 = M1.row2;
	VT0 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,0,0,0));
    VT1 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,1,1,1));
    VT2 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,2,2,2));
    VT3 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(3,3,3,3));
    VT0 = _mm_mul_ps(VT0,M2.row0);
    VT1 = _mm_mul_ps(VT1,M2.row1);
    VT2 = _mm_mul_ps(VT2,M2.row2);
    VT3 = _mm_mul_ps(VT3,M2.row3);
    VT0 = _mm_add_ps(VT0,VT2);
    VT1 = _mm_add_ps(VT1,VT3);
    VT0 = _mm_add_ps(VT0,VT1);
	result.row2 = VT0;

	VT3 = M1.row3;
	VT0 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(0,0,0,0));
    VT1 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(1,1,1,1));
    VT2 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(2,2,2,2));
    VT3 = _mm_shuffle_ps(VT3,VT3,_MM_SHUFFLE(3,3,3,3));
    VT0 = _mm_mul_ps(VT0,M2.row0);
    VT1 = _mm_mul_ps(VT1,M2.row1);
    VT2 = _mm_mul_ps(VT2,M2.row2);
    VT3 = _mm_mul_ps(VT3,M2.row3);
    VT0 = _mm_add_ps(VT0,VT2);
    VT1 = _mm_add_ps(VT1,VT3);
    VT0 = _mm_add_ps(VT0,VT1);
	result.row3 = VT0;

	return result;
}

inline Matrix4x4f operator + ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	Matrix4x4f result;

	result.row0 = _mm_add_ps(M1.row0,M2.row0);
	result.row1 = _mm_add_ps(M1.row1,M2.row1);
	result.row2 = _mm_add_ps(M1.row2,M2.row2);
	result.row3 = _mm_add_ps(M1.row3,M2.row3);

	return result;
}

inline Matrix4x4f operator - ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	Matrix4x4f result;

	result.row0 = _mm_sub_ps(M1.row0,M2.row0);
	result.row1 = _mm_sub_ps(M1.row1,M2.row1);
	result.row2 = _mm_sub_ps(M1.row2,M2.row2);
	result.row3 = _mm_sub_ps(M1.row3,M2.row3);

	return result;
}

inline Matrix4x4f operator * ( const Matrix4x4f& M, float F )
{
	Matrix4x4f result;

	__m128 VT = _mm_set_ps1(F);

	result.row0 = _mm_mul_ps(M.row0,VT);
	result.row1 = _mm_mul_ps(M.row1,VT);
	result.row2 = _mm_mul_ps(M.row2,VT);
	result.row3 = _mm_mul_ps(M.row3,VT);

	return result;
}

inline Matrix4x4f operator / ( const Matrix4x4f& M, float F )
{
	Matrix4x4f result;

	__m128 VT = _mm_set_ps1(F);

	result.row0 = _mm_div_ps(M.row0,VT);
	result.row1 = _mm_div_ps(M.row1,VT);
	result.row2 = _mm_div_ps(M.row2,VT);
	result.row3 = _mm_div_ps(M.row3,VT);

	return result;
}

inline bool operator == ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	__m128 VT = _mm_cmpeq_ps(M1.row0,M2.row0);
	VT = _mm_and_ps( VT,_mm_cmpeq_ps(M1.row1,M2.row1) );
	VT = _mm_and_ps( VT,_mm_cmpeq_ps(M1.row2,M2.row2) );
	VT = _mm_and_ps( VT,_mm_cmpeq_ps(M1.row3,M2.row3) );
	return (_mm_movemask_ps(VT) == 0xF);
}

/*
inline bool operator != ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	__m128 VT = _mm_cmpneq_ps(M1.row0,M2.row0);
	VT = _mm_or_ps( VT,_mm_cmpneq_ps(M1.row1,M2.row1) );
	VT = _mm_or_ps( VT,_mm_cmpneq_ps(M1.row2,M2.row2) );
	VT = _mm_or_ps( VT,_mm_cmpneq_ps(M1.row3,M2.row3) );
	return (_mm_movemask_ps(VT) != 0x0);
}*/

inline bool operator != ( const Matrix4x4f& M1, const Matrix4x4f& M2 )
{
	if(_mm_movemask_ps( _mm_cmpneq_ps(M1.row0,M2.row0) ) != 0x0) return true;
	if(_mm_movemask_ps( _mm_cmpneq_ps(M1.row1,M2.row1) ) != 0x0) return true;
	if(_mm_movemask_ps( _mm_cmpneq_ps(M1.row2,M2.row2) ) != 0x0) return true;
	return (_mm_movemask_ps( _mm_cmpneq_ps(M1.row3,M2.row3) ) != 0x0);
}
