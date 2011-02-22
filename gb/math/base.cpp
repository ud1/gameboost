/**  \file
 \brief Реализация для gb/math/base


 \TODO  Вынести все функции специфик  max2x2 



*/

//#pragma message("KS777: NEED COMMENTED"  __FILE__ )
//#include "stdafx.h"
//#include "pch.h"


#include <gb/math/base.h>



namespace gb 
{

namespace math 
{

namespace base
{

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


}
// end ns

}
// end ns

}
// end ns


// end file