/**  \file
 \brief Реализация  gb::fmath  для векторов.


 \TODO  Вынести все функции специфик  max2x2 

*/


#include "stdafx.h"

#include <gb/fmath/fmath.h>

namespace gb 
{
namespace fmath 
{
 

//===============================================================





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

	//=====================================================================
	vec3_s  vec3_s::project ( 
				const proj::ViewportZ& vp,
				const  mat44_s& Proj, 
				const  mat44_s& View, 
				const  mat44_s& World ) const
{	
				 vec4_s a= vec4_s( x, y, z, 1.0f );
				 mat44_s wvp = World * View * Proj ;

				 vec4_s b  = wvp * a ; 

				 vec3_s  c;
				c.x = b.x / b.w;
				c.y = b.y / b.w;
				c.z = b.z / b.w;

				 vec3_s  res;
				res.x = vp.x + vp.width  * (1.0f + c.x)  /  2.0f;
				res.y = vp.y + vp.height * (1.0f - c.y)  /  2.0f;
				res.z = vp.minZ + c.z * (vp.maxZ-vp.minZ);
				return res;
} 

//=======================================================
vec3_s  vec3_s::unproject( const proj::ViewportZ& vp,
						   const  mat44_s& Proj, 
				 		   const  mat44_s& View, 
						   const  mat44_s& World) const


{
	 mat44_s MAT = World * View *  Proj;
	 MAT.invert();

	vec4_s a;
	a.x =        (x-vp.x) * 2.0f   /  ( vp.width-1.0f );
	a.y = 1.0f - (y-vp.y) * 2.0f   /    vp.height;
	a.z = (z-vp.minZ)  /  (vp.maxZ - vp.minZ);
	a.w = 1.0f;

	vec4_s b  =  MAT * a ;  

	 const float k = 1.0f/b.w;
	vec3_s  res = vec3_s(  b.x*k  , b.y*k , b.z*k  );
	return  res ;
};


//=============================================================
float vec2_s::ccw(const vec2_s& v) const 
{
   vec3_s vv1;
   vv1.x =  x;
   vv1.y =  y;
   vv1.z = 0.0f;

   vec3_s vv2;
   vv2.x = v.x;
   vv2.y = v.y;
   vv2.z = 0.0f;

  vec3_s vres = vv1.cross(vv2);
   return vres.z;
};


//=============================================================
vec3_s&  vec3_s::transformCoord(const mat44_s& m)
{
	vec4_s v;
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 1.0f;

	v = m * v;

	x = v.x;
	y = v.y;
	z = v.z;
 
    return *this;
};

//=============================================================
vec3_s&  vec3_s::transformNormal(const mat44_s& m) 
{
	vec4_s v;
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0.0f;

	v = m * v;

	x = v.x;
	y = v.y;
	z = v.z;
 
    return *this;
};

//=========================================================================










//===============================================================

 
}
// end namespace
}
// end namespace

// end file