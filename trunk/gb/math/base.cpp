/**  \file
 \brief Реализация для gb/math/base


 \TODO  Вынести все функции специфик  max2x2 


*/

//#pragma message("KS777: NEED COMMENTED"  __FILE__ )
//#include "stdafx.h"
//#include "pch.h"


#include <gb/math/base.h>

#include <gb/math/geom2d.h>
#include <gb/math/geom3d.h>

namespace gb 
{

namespace math 
{

namespace base
{


//=========================================================================
//  vec3_s
//=========================================================================

	//=====================================================================
	void  vec3_s::operator = (const geom3d::Point3& pnt)
	{
     x=pnt._x;
	 y=pnt._y;
	 z=pnt._z;
	};


//=========================================================================
//    mat22_s
//=========================================================================
//
////=========================================================================
//mat22_s& mat22_s::operator = ( const mat22_s& m )
//{
//fggfgdfg
//
//	return *this;
//}
//
////=========================================================================
//mat22_s& mat22_s::operator = ( float f )
//{
//gfgdfdfgfdg
//
//	return *this;
//}
//
////=========================================================================
//mat22_s& mat22_s::operator += ( const mat22_s& m )
//{
//dfdsfsdfdsf
//}
//
////=========================================================================
//mat22_s& mat22_s::operator -= ( const mat22_s& m )
//gffgdfg
//
////=========================================================================
//mat22_s& mat22_s::operator *= ( const mat22_s& m )
//
//
////=========================================================================
//mat22_s& mat22_s::operator *= ( float f )
//gfdfgfgfd
//
////=========================================================================
//mat22_s& mat22_s::operator /= ( float f )
//{
//fddfs
//};
//
//
////=========================================================================
//mat22_s  mat22_s::operator + ( const mat22_s& m ) const 
//gfggfggfgfggdgf fgfggf
//
////=========================================================================
//mat22_s  mat22_s::operator - ( const mat22_s& m) const 
//dffdfdsf
//
////=========================================================================
//mat22_s  mat22_s::operator * ( const mat22_s& m) const 
//fgdfgfdgfd
//
////=========================================================================
//mat22_s  mat22_s::operator * (  float f ) const
//fdfddf
//
////=========================================================================
//vec2_s   mat22_s::operator * ( const vec2_s& v ) const

/************************
//=========================================================================
mat22_s operator * ( float b, const mat22_s& a )
{
	mat22_s c;

	c.x[0][0]=a.x[0][0]*b;
	c.x[0][1]=a.x[0][1]*b;
	c.x[1][0]=a.x[1][0]*b;
	c.x[1][1]=a.x[1][1]*b;

	return c;
}
**************************************/

//=========================================================================

//
//
////=========================================================================
//mat22_s& mat22_s::invert ()
//fgfddgdfg
// 
////=========================================================================
//mat22_s& mat22_s::setScaling ( const vec2_s& v )
//ggffdf
//
////=========================================================================
//mat22_s&   mat22_s::setScaling (float x, float y)
//dfdsdfsdfds
//
////=========================================================================
//mat22_s& mat22_s::setRotation ( float angle )
//dfdsfdsdf
// 
 


//=========================================================================
//
//    mat33_s
//
//=========================================================================
 
//=========================================================================
mat33_s& mat33_s::operator *= ( float f )
{
	floats[0][0] *= f;
	floats[0][1] *= f;
	floats[0][2] *= f;
	floats[1][0] *= f;
	floats[1][1] *= f;
	floats[1][2] *= f;
	floats[2][0] *= f;
	floats[2][1] *= f;
	floats[2][2] *= f;

	return *this;
}

//=========================================================================
mat33_s& mat33_s::operator /= ( float f )
{
	floats[0][0] /= f;
	floats[0][1] /= f;
	floats[0][2] /= f;
	floats[1][0] /= f;
	floats[1][1] /= f;
	floats[1][2] /= f;
	floats[2][0] /= f;
	floats[2][1] /= f;
	floats[2][2] /= f;

	return *this;
};

//=========================================================================
float mat33_s::determinant () const
{
	return floats [0][0]*(floats [1][1]* floats [2][2]-floats [1][2]* floats [2][1]) -
	       floats [0][1]*(floats [1][0]* floats [2][2]-floats [1][2]* floats [2][0]) +
	       floats [0][2]*(floats [1][0]* floats [2][1]-floats [1][1]* floats [2][0]);
}

//=========================================================================
mat33_s&  mat33_s::invert ()
{
	mat33_s a;

 
	float det = 
		floats [0][0]*(floats [1][1]* floats [2][2]-floats [1][2]* floats [2][1]) -
	    floats [0][1]*(floats [1][0]* floats [2][2]-floats [1][2]* floats [2][0]) +
	    floats [0][2]*(floats [1][0]* floats [2][1]-floats [1][1]* floats [2][0]);

	a.floats  [0][0] = (floats [1][1]* floats [2][2]-floats [1][2]* floats [2][1]) / det;
	a.floats  [0][1] = (floats [0][2]* floats [2][1]-floats [0][1]* floats [2][2]) / det;
	a.floats  [0][2] = (floats [0][1]* floats [1][2]-floats [0][2]* floats [1][1]) / det;
	a.floats  [1][0] = (floats [1][2]* floats [2][0]-floats [1][0]* floats [2][2]) / det;
	a.floats  [1][1] = (floats [0][0]* floats [2][2]-floats [0][2]* floats [2][0]) / det;
	a.floats  [1][2] = (floats [0][2]* floats [1][0]-floats [0][0]* floats [1][2]) / det;
	a.floats  [2][0] = (floats [1][0]* floats [2][1]-floats [1][1]* floats [2][0]) / det;
	a.floats  [2][1] = (floats [0][1]* floats [2][0]-floats [0][0]* floats [2][1]) / det;
	a.floats  [2][2] = (floats [0][0]* floats [1][1]-floats [0][1]* floats [1][0]) / det;

	*this = a;

	return *this;
}

//=========================================================================

mat33_s mat33_s::operator + ( const mat33_s& m ) const  
{
	mat33_s res;

	res.floats [0][0] = floats [0][0] + m.floats [0][0];
	res.floats [0][1] = floats [0][1] + m.floats [0][1];
	res.floats [0][2] = floats [0][2] + m.floats [0][2];
	res.floats [1][0] = floats [1][0] + m.floats [1][0];
	res.floats [1][1] = floats [1][1] + m.floats [1][1];
	res.floats [1][2] = floats [1][2] + m.floats [1][2];
	res.floats [2][0] = floats [2][0] + m.floats [2][0];
	res.floats [2][1] = floats [2][1] + m.floats [2][1];
	res.floats [2][2] = floats [2][2] + m.floats [2][2];

	return res;
}

//=========================================================================
mat33_s mat33_s::operator - ( const mat33_s& m ) const  
{
	mat33_s r;

	r.floats [0][0] = floats [0][0] - m.floats [0][0];
	r.floats [0][1] = floats [0][1] - m.floats [0][1];
	r.floats [0][2] = floats [0][2] - m.floats [0][2];
	r.floats [1][0] = floats [1][0] - m.floats [1][0];
	r.floats [1][1] = floats [1][1] - m.floats [1][1];
	r.floats [1][2] = floats [1][2] - m.floats [1][2];
	r.floats [2][0] = floats [2][0] - m.floats [2][0];
	r.floats [2][1] = floats [2][1] - m.floats [2][1];
	r.floats [2][2] = floats [2][2] - m.floats [2][2];

	return r;
}

//==========================================================================
mat33_s& mat33_s::operator = ( float a )
{
  floats [0][1] = floats [0][2] = floats [1][0] =
  floats [1][2] = floats [2][0] = floats [2][1] = 0.0;
  
  floats [0][0] = floats [1][1] = floats [2][2] = a;

	return *this;
}

//=========================================================================
mat33_s& mat33_s::operator += ( const mat33_s& a )
{
  floats [0][0] += a.floats  [0][0];
  floats [0][1] += a.floats  [0][1];
  floats [0][2] += a.floats  [0][2];
  floats [1][0] += a.floats  [1][0];
  floats [1][1] += a.floats  [1][1];
  floats [1][2] += a.floats  [1][2];
  floats [2][0] += a.floats  [2][0];
  floats [2][1] += a.floats  [2][1];
  floats [2][2] += a.floats  [2][2];

	return *this;
}

//=========================================================================
mat33_s& mat33_s::operator -= ( const mat33_s& a )
{
  floats [0][0] -=a.floats  [0][0];
  floats [0][1] -=a.floats  [0][1];
  floats [0][2] -=a.floats  [0][2];
  floats [1][0] -=a.floats  [1][0];
  floats [1][1] -=a.floats  [1][1];
  floats [1][2] -=a.floats  [1][2];
  floats [2][0] -=a.floats  [2][0];
  floats [2][1] -=a.floats  [2][1];
  floats [2][2] -=a.floats  [2][2];

	return *this;
}


//=========================================================================
mat33_s mat33_s::operator * ( const mat33_s& m) const 
{
	mat33_s res;
    res = *this;

	res.floats[0][0]= floats [0][0]*m.floats[0][0]+ floats [0][1]*m.floats[1][0]+ floats [0][2]*m.floats[2][0];
	res.floats[0][1]= floats [0][0]*m.floats[0][1]+ floats [0][1]*m.floats[1][1]+ floats [0][2]*m.floats[2][1];
	res.floats[0][2]= floats [0][0]*m.floats[0][2]+ floats [0][1]*m.floats[1][2]+ floats [0][2]*m.floats[2][2];
	res.floats[1][0]= floats [1][0]*m.floats[0][0]+ floats [1][1]*m.floats[1][0]+ floats [1][2]*m.floats[2][0];
	res.floats[1][1]= floats [1][0]*m.floats[0][1]+ floats [1][1]*m.floats[1][1]+ floats [1][2]*m.floats[2][1];
	res.floats[1][2]= floats [1][0]*m.floats[0][2]+ floats [1][1]*m.floats[1][2]+ floats [1][2]*m.floats[2][2];
	res.floats[2][0]= floats [2][0]*m.floats[0][0]+ floats [2][1]*m.floats[1][0]+ floats [2][2]*m.floats[2][0];
	res.floats[2][1]= floats [2][0]*m.floats[0][1]+ floats [2][1]*m.floats[1][1]+ floats [2][2]*m.floats[2][1];
	res.floats[2][2]= floats [2][0]*m.floats[0][2]+ floats [2][1]*m.floats[1][2]+ floats [2][2]*m.floats[2][2];

	return res;
}

//=========================================================================
mat33_s mat33_s::operator * (  float f ) const 
{
	mat33_s  res;

	res.floats [0][0] =  floats  [0][0] * f;
	res.floats [0][1] =  floats  [0][1] * f;
	res.floats [0][2] =  floats  [0][2] * f;
	res.floats [1][0] =  floats  [1][0] * f;
	res.floats [1][1] =  floats  [1][1] * f;
	res.floats [1][2] =  floats  [1][2] * f;
	res.floats [2][0] =  floats  [2][0] * f;
	res.floats [2][1] =  floats  [2][1] * f;
	res.floats [2][0] =  floats  [0][0] * f;

	return res;
}

//=========================================================================
mat33_s&   mat33_s::operator *= ( const mat33_s& m )
{
	mat33_s t  = *this;

	floats[0][0]=t.floats[0][0]*m.floats[0][0]+t.floats[0][1]*m.floats[1][0]+t.floats[0][2]*m.floats[2][0];
	floats[0][1]=t.floats[0][0]*m.floats[0][1]+t.floats[0][1]*m.floats[1][1]+t.floats[0][2]*m.floats[2][1];
	floats[0][2]=t.floats[0][0]*m.floats[0][2]+t.floats[0][1]*m.floats[1][2]+t.floats[0][2]*m.floats[2][2];
	floats[1][0]=t.floats[1][0]*m.floats[0][0]+t.floats[1][1]*m.floats[1][0]+t.floats[1][2]*m.floats[2][0];
	floats[1][1]=t.floats[1][0]*m.floats[0][1]+t.floats[1][1]*m.floats[1][1]+t.floats[1][2]*m.floats[2][1];
	floats[1][2]=t.floats[1][0]*m.floats[0][2]+t.floats[1][1]*m.floats[1][2]+t.floats[1][2]*m.floats[2][2];
	floats[2][0]=t.floats[2][0]*m.floats[0][0]+t.floats[2][1]*m.floats[1][0]+t.floats[2][2]*m.floats[2][0];
	floats[2][1]=t.floats[2][0]*m.floats[0][1]+t.floats[2][1]*m.floats[1][1]+t.floats[2][2]*m.floats[2][1];
	floats[2][2]=t.floats[2][0]*m.floats[0][2]+t.floats[2][1]*m.floats[1][2]+t.floats[2][2]*m.floats[2][2];
 
	return *this;
}

//=========================================================================
vec3_s mat33_s::operator * ( const vec3_s& v ) const
{
	vec3_s res;

	res.x = floats [0][0]*v.x + floats [0][1]*v.y + floats [0][2]*v.z;
	res.y = floats [1][0]*v.x + floats [1][1]*v.y + floats [1][2]*v.z;
	res.z = floats [2][0]*v.x + floats [2][1]*v.y + floats [2][2]*v.z;

	return res;
}

//=========================================================================
mat33_s& mat33_s::setScaling ( float x, float y, float z )
{
	 setIdentity();

  floats  [0][0] = x;
  floats  [1][1] = y;
  floats  [2][2] = z;

	return *this;
}

//=========================================================================
mat33_s& mat33_s::setScaling ( const vec3_s& v )
{
    setIdentity();

  floats  [0][0] = v.x;
  floats  [1][1] = v.y;
  floats  [2][2] = v.z;

	return *this;
}

//=========================================================================
mat33_s& mat33_s::setRotationX ( float angle )
{
	float sine ,  cosine;
	scalar::sincos(angle , sine, cosine);
 
	setIdentity();
	floats  [1][1] = cosine;
	floats  [1][2] = sine;
	floats  [2][1] = -sine;
	floats  [2][2] = cosine;

	return *this;
}

//=========================================================================
mat33_s& mat33_s::setRotationY ( float angle )
{
	float sine ,  cosine;
	scalar::sincos(angle , sine, cosine);
 
	setIdentity();
	floats  [0][0] = cosine;
	floats  [0][2] = -sine;
	floats  [2][0] = sine;
	floats  [2][2] = cosine;

	return *this;
}

//=========================================================================
mat33_s& mat33_s::setRotationZ ( float angle )
{
 
	float sine ,  cosine;
	scalar::sincos(angle , sine, cosine);
 
	setIdentity();
	floats  [0][0] = cosine;
	floats  [0][1] = sine;
	floats  [1][0] = -sine;
	floats  [1][1] = cosine;

	return *this;
}

//=========================================================================
mat33_s& mat33_s::setRotation ( const vec3_s& v, float angle )
{

 	float sine ,  cosine;
 	scalar::sincos(angle , sine, cosine);

	 floats [0][0] = v.x *v.x + (1-v.x*v.x) * cosine;
	 floats [0][1] = v.x *v.y * (1-cosine) + v.z * sine;
	 floats [0][2] = v.x *v.z * (1-cosine) - v.y * sine;
	 floats [1][0] = v.x *v.y * (1-cosine) - v.z * sine;
	 floats [1][1] = v.y *v.y + (1-v.y*v.y) * cosine;
	 floats [1][2] = v.y *v.z * (1-cosine) + v.x * sine;
	 floats [2][0] = v.x *v.z * (1-cosine) + v.y * sine;
	 floats [2][1] = v.y *v.z * (1-cosine) - v.x * sine;
	 floats [2][2] = v.z *v.z + (1-v.z*v.z) * cosine;

	
	return *this; 
}

//=========================================================================
mat33_s&  mat33_s::setMirrorX()
{
 setIdentity();
 floats  [0][0] = -1.0;
 return *this;
}

//=========================================================================
mat33_s&  mat33_s::setMirrorY()
{
 setIdentity();
  floats  [1][1] = -1.0;
 return *this;
}

//=========================================================================
mat33_s&  mat33_s::setMirrorZ()
{
 setIdentity();
 floats  [2][2] = -1.0;
 return  *this;
}

//=========================================================================
//    mat44_s
//=========================================================================


//=========================================================================
mat44_s& mat44_s::setTransformation(const vec3_s& vScale, 
								const geom3d::Quaternion& qRotation,
								const vec3_s& vTranslation)
{
   mat44_s ms; 
   ms.setScaling( vScale );

   mat44_s mr; 
   mr.setRotationQuaternion(  qRotation );

   mat44_s mt; 
   mt.setTranslation(  vTranslation );

   *this = mt * mr * ms;

   return *this;
};

//=========================================================================
mat44_s& mat44_s::setWorldTransform(const geom3d::TransformData& t)
{
	return setTransformation(t.vScaling, t.qRotation, t.vTranslation );
}


// bool invert ()
//=========================================================================
mat44_s& mat44_s::invert () throw()
{
#define SWAP_ROWS(a, b) {  float * _tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(fl,r,c)     fl [r][c]
#define INV_ERR   std::runtime_error("invert failed");

	float	wtmp [4][8];
	float	m0, m1, m2, m3, s;
	float	* r0, * r1, * r2, * r3;

	r0 = wtmp [0];
	r1 = wtmp [1];
	r2 = wtmp [2];
	r3 = wtmp [3];

	r0 [0] = MAT(floats,0,0);
	r0 [1] = MAT(floats,0,1);
	r0 [2] = MAT(floats,0,2);
	r0 [3] = MAT(floats,0,3);
	r0 [4] = 1;
	r0 [5] =
	r0 [6] =
	r0 [7] = 0;

	r1 [0] = MAT(floats,1,0);
	r1 [1] = MAT(floats,1,1);
	r1 [2] = MAT(floats,1,2);
	r1 [3] = MAT(floats,1,3);
	r1 [5] = 1;
	r1 [4] =
	r1 [6] =
	r1 [7] = 0,

	r2 [0] = MAT(floats,2,0);
	r2 [1] = MAT(floats,2,1);
	r2 [2] = MAT(floats,2,2);
	r2 [3] = MAT(floats,2,3);
	r2 [6] = 1;
	r2 [4] =
	r2 [5] =
	r2 [7] = 0;

	r3 [0] = MAT(floats,3,0);
	r3 [1] = MAT(floats,3,1);
	r3 [2] = MAT(floats,3,2);
	r3 [3] = MAT(floats,3,3);
	r3 [7] = 1;
	r3 [4] =
	r3 [5] =
	r3 [6] = 0;

											// choose pivot - or die
	if ( fabs (r3 [0] )> fabs ( r2 [0] ) )
		SWAP_ROWS ( r3, r2 );

	if ( fabs ( r2 [0] ) > fabs ( r1 [0] ) )
		SWAP_ROWS ( r2, r1 );

	if ( fabs ( r1 [0] ) > fabs ( r0 [0 ] ) )
		SWAP_ROWS ( r1, r0 );

	if ( r0 [0] == 0 )
	{
		  INV_ERR
		//return false;
	}

											// eliminate first variable
	m1 = r1[0]/r0[0];
	m2 = r2[0]/r0[0];
	m3 = r3[0]/r0[0];

	s = r0[1];
	r1[1] -= m1 * s;
	r2[1] -= m2 * s;
	r3[1] -= m3 * s;

	s = r0[2];
	r1[2] -= m1 * s;
	r2[2] -= m2 * s;
	r3[2] -= m3 * s;

	s = r0[3];
	r1[3] -= m1 * s;
	r2[3] -= m2 * s;
	r3[3] -= m3 * s;

	s = r0[4];

	if ( s != 0 )
	{
		r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s;
	}

	s = r0[5];

	if ( s != 0.0 )
	{
		r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s;
	}

	s = r0[6];

	if ( s != 0 )
	{
		r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s;
	}

	s = r0[7];

	if ( s != 0 )
	{
		r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s;
	}

											// choose pivot - or die
	if ( fabs (r3 [1] ) > fabs ( r2 [1] ) )
		SWAP_ROWS ( r3, r2 );

	if ( fabs ( r2 [1] ) > fabs ( r1 [1] ) )
		SWAP_ROWS ( r2, r1 );

	if ( r1 [1] == 0 )
	{
       INV_ERR
		//return false;
	}


											// eliminate second variable
	m2     = r2[1]/r1[1]; m3     = r3[1]/r1[1];
	r2[2] -= m2 * r1[2];  r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3];  r3[3] -= m3 * r1[3];

	s = r1[4];

	if ( 0 != s )
	{
		r2[4] -= m2 * s; r3[4] -= m3 * s;
	}

	s = r1[5];

	if ( 0 != s )
	{
		r2[5] -= m2 * s; r3[5] -= m3 * s;
	}

	s = r1[6];

	if ( 0 != s )
	{
		r2[6] -= m2 * s; r3[6] -= m3 * s;
	}

	s = r1[7];

	if ( 0 != s )
	{
		r2[7] -= m2 * s; r3[7] -= m3 * s;
	}

											// choose pivot - or die
	if ( fabs ( r3 [2] ) > fabs ( r2 [2] ) )
		SWAP_ROWS ( r3, r2 );

	if ( r2 [2] == 0)
	{
		INV_ERR
	    //return false;
	}

											// eliminate third variable
	m3     = r3[2]/r2[2];
	r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
	r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
	r3[7] -= m3 * r2[7];

											// last check
	if ( r3 [3] == 0 )
	{
		INV_ERR
		//return false;
	}


											// now back substitute row 3
	s      = 1/r3[3];
	r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

											// now back substitute row 2
	m2    = r2[3];
	s     = 1/r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
	r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);

	m1     = r1[3];
	r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
	r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;

	m0     = r0[3];
	r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
	r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

											// now back substitute row 1
	m1    = r1[2];
	s     = 1/r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
	r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);

	m0     = r0[2];
	r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
	r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

											// now back substitute row 0
	m0    = r0[1];
	s     = 1/r0[0];

	r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
	r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	MAT(floats,0,0) = r0[4];   MAT(floats,0,1) = r0[5],
	MAT(floats,0,2) = r0[6];   MAT(floats,0,3) = r0[7],
	MAT(floats,1,0) = r1[4];   MAT(floats,1,1) = r1[5],
	MAT(floats,1,2) = r1[6];   MAT(floats,1,3) = r1[7],
	MAT(floats,2,0) = r2[4];   MAT(floats,2,1) = r2[5],
	MAT(floats,2,2) = r2[6];   MAT(floats,2,3) = r2[7],
	MAT(floats,3,0) = r3[4];   MAT(floats,3,1) = r3[5],
	MAT(floats,3,2) = r3[6];   MAT(floats,3,3) = r3[7];

#undef MAT
#undef SWAP_ROWS
#undef INV_ERR

	//return true;
	return *this;
}


//====================================================================

/*******  Evel ***********
void mat44_s::decompose(vec3_s& pos, geom3d::Quaternion& rot, vec3_s& scale) const 
{

		mat44_s m = *this;

		pos = m.getPos();

		scale.x = math::sqrt(math::sqr(m.data[0][0]) + math::sqr(m.data[0][1]) + math::sqr(m.data[0][2]));
		scale.y = math::sqrt(math::sqr(m.data[1][0]) + math::sqr(m.data[1][1]) + math::sqr(m.data[1][2]));
		scale.z = math::sqrt(math::sqr(m.data[2][0]) + math::sqr(m.data[2][1]) + math::sqr(m.data[2][2]));

		for (int i=0; i<3; i++) {
			if (scale.v[i] > EPSILON) {
				m.data[i][0] /= scale.v[i];
				m.data[i][1] /= scale.v[i];
				m.data[i][2] /= scale.v[i];
			}
		}

		rot.fromMatrix(m);
		
}
 ******************************/

}
// end ns

}
// end ns

}
// end ns


// end file