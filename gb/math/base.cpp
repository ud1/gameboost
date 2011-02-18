/**  \file
 \brief Реализация для gb/math/base


 \TODO  Вынести все функции специфик  max2x2 



*/

//#pragma message("WARN "  __FILE__ )
#include "pch.h"
//#include "stdafx.h"

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

//=========================================================================


//=========================================================================
mat22_s&  

mat22_s::operator = 

( const mat22_s& m )

{
	floats [0][0] = m.floats [0][0]; 
	floats [0][1] = m.floats [0][1]; 
	floats [1][0] = m.floats [1][0];
	floats [1][1] = m.floats [1][1];

	return *this;
}

//=========================================================================
mat22_s& mat22_s::operator = ( float f )
{
	floats [0][1] = floats [1][0] = 0.0;
	floats [0][0] = floats [1][1] = f;

	return *this;
}

//=========================================================================
mat22_s& mat22_s::operator += ( const mat22_s& m )
{
	floats [0][0] += m.floats [0][0];
	floats [0][1] += m.floats [0][1];
	floats [1][0] += m.floats [1][0];
	floats [1][1] += m.floats [1][1];

	return *this;
}

//=========================================================================
mat22_s& mat22_s::operator -= ( const mat22_s& m )
{
	floats [0][0] -= m.floats [0][0];
	floats [0][1] -= m.floats [0][1];
	floats [1][0] -= m.floats [1][0];
	floats [1][1] -= m.floats [1][1];

	return *this;
}

//=========================================================================
mat22_s& mat22_s::operator *= ( const mat22_s& m )
{
	mat22_s c  = *this ;

	floats [0][0] = c.floats [0][0]*m.floats [0][0] + c.floats [0][1]*m.floats [1][0];
	floats [0][1] = c.floats [0][0]*m.floats [0][1] + c.floats [0][1]*m.floats [1][1];
	floats [1][0] = c.floats [1][0]*m.floats [0][0] + c.floats [1][1]*m.floats [1][0];
	floats [1][1] = c.floats [1][0]*m.floats [0][1] + c.floats [1][1]*m.floats [1][1];

	return *this;
}

//=========================================================================
mat22_s& mat22_s::operator *= ( float f )
{
	floats [0][0] *= f;
	floats [0][1] *= f;
	floats [1][0] *= f;
	floats [1][1] *= f;
	return *this;
}

//=========================================================================
mat22_s& mat22_s::operator /= ( float f )
{
	floats [0][0] /= f;
	floats [0][1] /= f;
	floats [1][0] /= f;
	floats [1][1] /= f;

	return *this;
};


//=========================================================================
mat22_s  mat22_s::operator + ( const mat22_s& m ) //, const mat22_s& m )
{
	mat22_s res;

	res.floats[0][0] = floats [0][0] + m.floats [0][0];
	res.floats[0][1] = floats [0][1] + m.floats [0][1];
	res.floats[1][0] = floats [1][0] + m.floats [1][0];
	res.floats[1][1] = floats [1][1] + m.floats [1][1];

	return res;
}

//=========================================================================
mat22_s  mat22_s::operator - ( const mat22_s& m) //, const mat22_s& b )
{
	mat22_s res;

	res.floats [0][0] = floats [0][0] - m.floats [0][0];
	res.floats [0][1] = floats [0][1] - m.floats [0][1];
	res.floats [1][0] = floats [1][0] - m.floats [1][0];
	res.floats [1][1] = floats [1][1] - m.floats [1][1];

	return res;
}

//=========================================================================
mat22_s  mat22_s::operator * ( const mat22_s& m)// a, const mat22_s& b )
{
	mat22_s res;

	res.floats[0][0] = floats[0][0]*m.floats[0][0]+floats[0][1]*m.floats[1][0];
	res.floats[0][1] = floats[0][0]*m.floats[0][1]+floats[0][1]*m.floats[1][1];
	res.floats[1][0] = floats[1][0]*m.floats[0][0]+floats[1][1]*m.floats[1][0];
	res.floats[1][1] = floats[1][0]*m.floats[0][1]+floats[1][1]*m.floats[1][1];

	return res;
}

//=========================================================================
mat22_s  mat22_s::operator * (  float f )
{
	mat22_s res;

	res.floats[0][0] = floats[0][0] * f;
	res.floats[0][1] = floats[0][1] * f;
	res.floats[1][0] = floats[1][0] * f;
	res.floats[1][1] = floats[1][1] * f;

	return  res;
}

//=========================================================================
vec2_s   mat22_s::operator * ( const vec2_s& v )
{
	vec2_s res;// ( 

		res.x =  floats [0][0]*v.x + floats [0][1]*v.y ;
		res.y =  floats [1][0]*v.x + floats [1][1]*v.y ;
			  //);
	return res;
}
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



//=========================================================================
void mat22_s::invert ()
{
// 
	float det =  this->determinant  ();  
	
	mat22_s m;

	m.floats [0][0] =  floats [1][1] / det;
	m.floats [0][1] = -floats [0][1] / det;
	m.floats [1][0] = -floats [1][0] / det;
	m.floats [1][1] =  floats [0][0] / det;

	*this = m;
}
 
//=========================================================================
void mat22_s::setScaling ( const vec2_s& v )
{
	//mat22_s m;

	floats [0][0] = v.x;
	floats [1][1] = v.y;
	floats [0][1] =
	floats [1][0] = 0.0;

	//return m;
}

//=========================================================================
void   mat22_s::setScaling (float x, float y)
{
	floats [0][0] = x;
	floats [1][1] = y;
	floats [0][1] =
	floats [1][0] = 0.0;

};

//=========================================================================
void mat22_s::setRotation ( float angle )
{

	//mat22_s m; 
	//m.setIdentity();

	//float    cosine,sine;
	//cosine;     = cos ( angle );
	//sine;       = sin ( angle );
 //    sincos(angle , sine , cosine );

	//m.floats [0][0] = cosine;
	//m.floats [0][1] = sine;
	//m.floats [1][0] = -sine;
	//m.floats [1][1] = cosine;

	//return m;

  //setIdentity();

	float    cosine,sine;
	scalar::sincos(angle , sine , cosine );

	floats [0][0] = cosine;
	floats [0][1] = sine;
	floats [1][0] = -sine;
	floats [1][1] = cosine;

}
 

//=========================================================================

 

}
// end ns

}
// end ns

}
// end ns


// end file