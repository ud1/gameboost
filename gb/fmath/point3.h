﻿/**  \file
 \brief ??????


*/

#pragma once

#ifndef __GB_FMATH_H__
    #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif


namespace gb 
{

	namespace fmath
	{
	
	


		/** \brief Сущность описывает точку/координату/позицию в 3х-мерном пространстве.
		   Уровень выше, чем вектор */
		class Point3 {
		public:
			float _x;
			float _y;
			float _z;

			//! \brief  По дефолту координата нулевая .
			inline Point3() { _x=0.0f; _y=0.0f; _z=0.0f;  }
			inline Point3(const Point3& p) { _x=p._x; _y=p._y; _z=p._z; }
			inline Point3(float x, float y, float z) {_x=x; _y=y; _z=z; }

			inline operator  const float*() const  { return &_x; };
			inline operator        float*()        { return &_x; };

			inline void operator = (const  vec3& v) { _x=v.x; _y=v.y; _z=v.z; }

			inline operator       vec3 () const { return  vec3 (_x,_y,_z);  }
			inline operator const vec3*() const { return (vec3*)&_x; }
	
#ifdef _D3D9_H_
			inline operator D3DVECTOR*() { return (D3DVECTOR*)&_x; }
			inline operator const D3DVECTOR*() const { return (D3DVECTOR*)&_x; }
			inline operator D3DVECTOR() const  { D3DVECTOR r; r.x=_x; r.y=_y; r.z=_z; return r;  }
			inline void operator = (const D3DVECTOR& v) {	_x=v.x; _y=v.y; _z=v.z; }
#endif


			//! \brief установка  средней точки  
			inline Point3& setMiddle(const  vec3& p1, const  vec3& p2)
			{
				_x = (p1.x + p2.x) / 2.0f;
				_y = (p1.y + p2.y) / 2.0f;
				_z = (p1.z + p2.z) / 2.0f;
				return *this;
			}


			//! \brief установка  средней точки  
			inline Point3& setMiddle(const Point3& p)
			{
				_x = (_x + p._x) / 2.0f;
				_y = (_y + p._y) / 2.0f;
				_z = (_z + p._z) / 2.0f;
				return *this;
			}

			//! \brief  Движение к точке posTo на расстояние distance
			Point3& moveTo(const Point3& posTo, float distance)
			{
				 vec3 vn = ( vec3)posTo - ( vec3)*this;
				vn.normalize();
				vn *= distance;
				 _x += vn.x; _y=vn.y; _z=vn.z;
				return *this;
			}

			//! \brief  Перемещение точки по направлению normal на расстояние distance
			Point3& moveAlongNormal(const Normal3& normal, float distance) 
			{
				 vec3 vn = normal; 
				vn *= distance;
				_x += vn.x; _y=vn.y; _z=vn.z;
				return *this;
			}
			
			//! \brief Вернуть расстояние между точками.
			inline float distanceBetween(const Point3& p) const    
			{
		       vec3 sub = ( vec3)*this - ( vec3)p;
			  return sub.length();
		    }
			
			
			/**  \brief  Изменить расстояние между this и точкой pnt по коэф. k.
			 Если k меньше 1 то производится сближение, если больше , то удаление   */ 
			Point3& adjustDistancePoint(const Point3& pnt, const float k) 
			{
				 vec3 dv  = ( vec3)pnt - ( vec3)*this; 
			  float dist = dv.length();
			   Normal3 n  =  dv ;
			  moveAlongNormal( n,  dist - (dist * k) );
			  return *this;
			}

 
			//! \brief Трансформировать точку по матрице m
			Point3& transform(const  mat44& m) 
			{ 
			    vec3 v = *this;
			   v.transformCoord(m);
			   *this = v;
				return *this;
			}

			// void fromScreenSpace(const Point2& p, const VP& vp, const M& m) {....}
		
		};
		// end class
	
	
	
	
	
	
	
	
	
	}
}