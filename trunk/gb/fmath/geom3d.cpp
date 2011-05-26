
//#include "pch.h"


//#include "stdafx.h"


#include <gb/fmath/fmath.h>
#include <assert.h>

namespace gb
{

namespace fmath
{

namespace geom3d
{


//=========================================================================
//                          Normal3
//=========================================================================

//=========================================================================
	Normal3& Normal3::setDirectionBetweenPoints(const Point3& pntSrc, const Point3& pntDest) 
	{
		 vec3 v;
		v.x=  pntDest._x - pntSrc._x; // пусть пока так будет
		v.y=  pntDest._y - pntSrc._y;
		v.z=  pntDest._z - pntSrc._z;
		*this = v;
		return *this;
	}







//=========================================================================
//  Sphere
//=========================================================================


//=========================================================================
AABB Sphere::toAabbInside() const
{
  AABB res;
 
   static const float k =  1.0f / sqrt(1.0f+1.0f+1.0f);

  res.min.x = center.x - radius * k;
  res.min.y = center.y - radius * k;
  res.min.z = center.z - radius * k;

  res.max.x = center.x + radius * k;
  res.max.y = center.y + radius * k;
  res.max.z = center.z + radius * k;

   return res;


}

//=========================================================================
AABB Sphere::toAabbOutside() const
{
    AABB res;
 
  res.min.x = center.x - radius;
  res.min.y = center.y - radius;  
  res.min.z = center.z - radius;  
  
  res.max.x = center.x + radius;
  res.max.y = center.y + radius;  
  res.max.z = center.z + radius;   
  
  return res;




}


//=========================================================================
//  AABB
//=========================================================================

bool AABB::checkIntersectPlane(const plane_s& pl) const
{


   vec3 normal = pl.normal();
  float d = pl.d;

   vec3 vmax, vmin;
 
     bool result= false;

     for (unsigned int i= 0; i<3; i++)
	 {
          if (normal[i] > 0.0f) 
		  {
               vmin[i] =  min[i];
               vmax[i] =  max[i];
          } 
		  else 
		  {
               vmin[i] =  max[i];
               vmax[i] =  min[i];
		  };
     }

     if ( normal.dot(vmin) + d >  0.0f)   return result;
     if ( normal.dot(vmax) + d >= 0.0f)   result = true;
	 
	 return result;
};



//=========================================================================



//=========================================================================
//  Frustum
//=========================================================================

//=========================================================================
void Frustum::make(const  mat44& mViewProj) 
{
 
	// left plane 
	planes[0].a = mViewProj._14 + mViewProj._13;
	planes[0].b = mViewProj._24 + mViewProj._23;
	planes[0].c = mViewProj._34 + mViewProj._33;
	planes[0].d = mViewProj._44 + mViewProj._43;
	//D3DXPlaneNormalize((D3DXPLANE*)&planes[0], (D3DXPLANE*)&planes[0]);
	planes[0].normalize();


	// right plane
	planes[1].a = mViewProj._14 - mViewProj._13;
	planes[1].b = mViewProj._24 - mViewProj._23;
	planes[1].c = mViewProj._34 - mViewProj._33;
	planes[1].d = mViewProj._44 - mViewProj._43;
	//D3DXPlaneNormalize((D3DXPLANE*)&planes[1], (D3DXPLANE*)&planes[1]);
	planes[1].normalize();


	// top plane
	planes[2].a = mViewProj._14 + mViewProj._11;
	planes[2].b = mViewProj._24 + mViewProj._21;
	planes[2].c = mViewProj._34 + mViewProj._31;
	planes[2].d = mViewProj._44 + mViewProj._41;
	//D3DXPlaneNormalize((D3DXPLANE*)&planes[2], (D3DXPLANE*)&planes[2]);
	planes[2].normalize();


	//Bottom  plane
	planes[3].a = mViewProj._14 - mViewProj._11;
	planes[3].b = mViewProj._24 - mViewProj._21;
	planes[3].c = mViewProj._34 - mViewProj._31;
	planes[3].d = mViewProj._44 - mViewProj._41;
	//D3DXPlaneNormalize((D3DXPLANE*)&planes[3], (D3DXPLANE*)&planes[3]);
    planes[3].normalize();


	// near  plane
	planes[4].a = mViewProj._14 - mViewProj._12;
	planes[4].b = mViewProj._24 - mViewProj._22;
	planes[4].c = mViewProj._34 - mViewProj._32;
	planes[4].d = mViewProj._44 - mViewProj._42;
//	D3DXPlaneNormalize((D3DXPLANE*)&planes[4], (D3DXPLANE*)&planes[4]);
    planes[4].normalize();


	// far  plane
	planes[5].a = mViewProj._14 + mViewProj._12;
	planes[5].b = mViewProj._24 + mViewProj._22;
	planes[5].c = mViewProj._34 + mViewProj._32;
	planes[5].d = mViewProj._44 + mViewProj._42;
	//D3DXPlaneNormalize((D3DXPLANE*)&planes[5], (D3DXPLANE*)&planes[5]);
	planes[5].normalize();

 
};


//=========================================================================
bool Frustum::checkPoint(const  vec3& point) const  
{
	for(int c=0; c<6; c++) 
	{
		if( planes[c].dotCoord(point) < 0.0f )
		//if(D3DXPlaneDotCoord( (D3DXPLANE*)&planes[c], &D3DXVECTOR3(pos->x, pos->y, pos->z)) < 0.0f)
		{
			return true;		
		}

	}
	return false;
};


//=========================================================================
bool Frustum::checkSphere(const Sphere& sphere)  const 
{
	for(int c=0; c<6; c++) 
	{  
		if( planes[c].dotCoord(sphere.center) < -sphere.radius  )
		//if(  D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(sphere->center.x, sphere->center.y, sphere->center.z))  <  -sphere->radius  )
		{
          return true;
		}
 
	}

	return false;
};

//=========================================================================
bool Frustum::checkAABB(const AABB& aabb) const  
{

	for(int c=0; c<6; c++) 
	{
	    if( planes[c].dotCoord(  vec3(aabb.min.x, aabb.min.y, aabb.min.z) ) >= 0.0f )
        //if(D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(aabb.min.x, aabb.min.y, aabb.min.z)) >= 0.0f)
			continue;
					
	      if( planes[c].dotCoord(  vec3(aabb.max.x, aabb.min.y, aabb.min.z) ) >= 0.0f ) 	
		//if(D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(aabb.max.x, aabb.min.y, aabb.min.z)) >= 0.0f)
			continue;
			
	      if( planes[c].dotCoord(  vec3(aabb.min.x, aabb.max.x, aabb.min.z) ) >= 0.0f ) 			
		//if(D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(aabb.min.x, aabb.max.x, aabb.min.z)) >= 0.0f)
			continue;
			
	      if( planes[c].dotCoord(  vec3(aabb.max.x, aabb.max.x, aabb.min.z) ) >= 0.0f ) 			
		//if(D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(aabb.max.x, aabb.max.x, aabb.min.z)) >= 0.0f)
			continue;
			
	      if( planes[c].dotCoord(  vec3(aabb.min.x, aabb.min.y, aabb.max.z) ) >= 0.0f )			
		//if(D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(aabb.min.x, aabb.min.y, aabb.max.z)) >= 0.0f)
			continue;
			
	      if( planes[c].dotCoord(  vec3(aabb.max.x, aabb.min.y, aabb.max.z) ) >= 0.0f )			
		//if(D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(aabb.max.x, aabb.min.y, aabb.max.z)) >= 0.0f)
			continue;
			
	      if( planes[c].dotCoord(  vec3(aabb.min.x, aabb.max.x, aabb.max.z) ) >= 0.0f )			
		//if(D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(aabb.min.x, aabb.max.x, aabb.max.z)) >= 0.0f)
			continue;
			
	      if( planes[c].dotCoord(  vec3(aabb.max.x, aabb.max.x, aabb.max.z) ) >= 0.0f )			
		//if(D3DXPlaneDotCoord((D3DXPLANE*)&planes[c], &D3DXVECTOR3(aabb.max.x, aabb.max.x, aabb.max.z)) >= 0.0f)
			continue;

			
		return true;
		
	} // for

	return false;
};





} // end ns

} // end ns

} // end ns