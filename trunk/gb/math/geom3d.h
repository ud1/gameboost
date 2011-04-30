/** \file geom3d.h
 \brief геометрия в 3d.
*
*  Наполнение на основе выложеного ребятами в папку бранч,   опенсурсных движков,   выуженого из гугла , своих наработок.
*
*
 \todo Сделать перечечения: луч, сфера, бокс, плоскость,
*/

/* *************************************

bool checkIntersectRay(const Ray& ray) {....}
bool checkIntersecеSphere(const Sphere& sph) {....}
bool checkIntersectAABB(const AABB& aabb) {....}
bool checkIntersectPlane(const Plane& aabb) {....}






*****************************************/ 

#pragma once
#include <gb/math/forw_decl.h>
#include <xmath.h>
#include <gb/math/scalar.h>
#include <gb/math/base.h>

#include <assert.h>



namespace gb 
{

  namespace math
  {
  
    /** \brief  геометрия в 3d  */
    namespace geom3d
	{


		/** \brief 3-х мерный размер */
		struct Size3d {

			union {
				float x;
				float width;
			};

			union {
				float y;
				float height;
			};

			union {
				float z;
				float depth;
			};

			inline operator base::vec3_s() const { return base::vec3_s(x,y,z); }


		};


		/** \brief Сущность описывает направление/нормаль в 3х-мерном пространстве. 
		   Уровень выше, чем вектор.  Всегда нормализован.  */
		class Normal3 {
		private:
			float _x;
			float _y;
			float _z;

			inline void __normalize() 
			{
				register float len = sqrt ( _x*_x + _y*_y + _z*_z );
				_x/=len; _y/=len; _z/=len;
			}

		public:


			//! \brief  По дефолту нормаль смотрит в Z .
			inline Normal3() { _x=0.0f; _y=0.0f; _z=1.0f;  }
			inline Normal3(const Normal3& n) { _x=n._x; _y=n._y; _z=n._z; }
			inline Normal3(float x, float y, float z) { _x=x; _y=y; _z=z; __normalize(); }
			inline Normal3(const base::vec3_s& v) { *this = v;  }

		
			inline operator  const float*() const  { return &_x; };
			inline operator        float*()        { return &_x; };

			inline float x() const { return _x; }
			inline float y() const { return _y; }
			inline float z() const { return _z; }

			inline void operator = (const base::vec3_s& vn)	{ _x = vn.x; _y = vn.y; _z = vn.z; __normalize(); }
			inline operator base::vec3_s() const { return base::vec3_s (_x,_y,_z);  }

			//! \brief  Вычислить угол между нормалями
			inline float angle (const Normal3& n) 
			{
				const float fdot = _x*n._x + _y*n._y + _z*n._z;
                return acos(  fdot );
			}

			 //! \brief Установить как направление между точками pntDest и pntSrc .  
			Normal3& setDirectionBetweenPoints(const Point3& pntSrc, const Point3& pntDest);
 
			//! \brief Изменить направление на противоположное
			inline void negate() {_x=-_x; _y=-_y; _z=-_z; }
			
			//! \brief  Трансформировать нормаль по матрице m
			Normal3& transform(const base::mat44_s& m) 
			{ 
			   base::vec3_s v = *this;
			   v.transformNormal(m);
			   //*this = v;
			   _x = v.x;
			   _y = v.y;
			   _z = v.z;
				return *this;
			}


#ifdef GB_D3D9
			inline operator D3DVECTOR*() { return (D3DVECTOR*)&_x; }
			inline operator const D3DVECTOR*() const { return (D3DVECTOR*)&_x; }
			inline operator D3DVECTOR() const  { D3DVECTOR r; r.x=_x; r.y=_y; r.z=_z; return r;  }
			inline void operator = (const D3DXVECTOR3& v) {	_x=v.x; _y=v.y; _z=v.z; __normalize(); }
#endif	


#ifdef GB_D3DX9
			inline operator const D3DXVECTOR3*() const { return (D3DXVECTOR3*)&_x; }

#endif


		};
		// end class


		/** \brief Сущность описывает точку/координату/позицию в 3х-мерном пространстве.
		   Уровень выше, чем вектор */
		class Point3 {
		public:
			float _x;
			float _y;
			float _z;

			//! \brief  По дефолту координата нулевая .
			inline Point3() { _x=0.0f; _y=0.0f; _z=0.0f;  }
			inline Point3(float x, float y, float z) {_x=x; _y=y; _z=z; }

			inline operator  const float*() const  { return &_x; };
			inline operator        float*()        { return &_x; };

			inline void operator = (const base::vec3_s& v) { _x=v.x; _y=v.y; _z=v.z; }
			inline operator base::vec3_s() const { return base::vec3_s (_x,_y,_z);  }
	
#ifdef GB_D3D9
			inline operator D3DVECTOR*() { return (D3DVECTOR*)&_x; }
			inline operator const D3DVECTOR*() const { return (D3DVECTOR*)&_x; }
			inline operator D3DVECTOR() const  { D3DVECTOR r; r.x=_x; r.y=_y; r.z=_z; return r;  }
			inline void operator = (const D3DXVECTOR3& v) {	_x=v.x; _y=v.y; _z=v.z; }
#endif


			//! \brief установка  средней точки  
			inline Point3& setMiddle(const base::vec3_s& p1, const base::vec3_s& p2)
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
				base::vec3_s vn = (base::vec3_s)posTo - (base::vec3_s)*this;
				vn.normalize();
				vn *= distance;
				 _x += vn.x; _y=vn.y; _z=vn.z;
				return *this;
			}

			//! \brief  Перемещение точки по направлению normal на расстояние distance
			Point3& moveAlongNormal(const Normal3& normal, float distance) 
			{
				base::vec3_s vn = normal; 
				vn *= distance;
				_x += vn.x; _y=vn.y; _z=vn.z;
				return *this;
			}
			
			//! \brief Вернуть расстояние между точками.
			inline float distanceBetween(const Point3& p) const    
			{
		      base::vec3_s sub = (base::vec3_s)*this - (base::vec3_s)p;
			  return sub.length();
		    }
			
			
			/**  \brief  Изменить расстояние между this и точкой pnt по коэф. k.
			 Если k меньше 1 то производится сближение, если больше , то удаление   */ 
			Point3& adjustDistancePoint(const Point3& pnt, const float k) 
			{
				base::vec3_s dv  = (base::vec3_s)pnt - (base::vec3_s)*this; 
			  float dist = dv.length();
			   Normal3 n  =  dv ;
			  moveAlongNormal( n,  dist - (dist * k) );
			  return *this;
			}

 
			//! \brief Трансформировать точку по матрице m
			Point3& transform(const base::mat44_s& m) 
			{ 
			   base::vec3_s v = *this;
			   v.transformCoord(m);
			   *this = v;
				return *this;
			}

			// void fromScreenSpace(const Point2& p, const VP& vp, const M& m) {....}
		
		};
		// end class



		//! \brief  Сборка  ось повотора и угол
		struct AxiesAngle {

			base::vec3_s   axies; ///< ось повотора (должен быть нормализован)
			float   angle; ///< угол поворота

		};
		
	//! \brief Сфера по центральной точке и радиусу. Она же Bounding sphere.
	class Sphere {
	public:
	  base::vec3_s  center;  ///<  центральная координата сферы.
	  float   radius;  ///<  радиус сферы.
	  
	  inline Sphere() {}
	  inline Sphere(const Sphere& s) {center=s.center; radius=s.radius; }
	  inline Sphere(const base::vec3_s& _center, const float _radius) {center=_center; radius=_radius; }	  
	  
	
	  inline void set(const base::vec3_s& vCenter, float fRadius) {center=vCenter; radius=fRadius; }
	  inline void set( float centerX, float centerY, float centerZ, float fRadius) { center.x=centerX;  center.y=centerY;  center.z=centerZ;  radius=fRadius; 	}
	  inline void set(int ix, int iy, int iz, int r) { center.x=(float)ix;  center.y=(float)iy;  center.z=(float)iz;	radius = (float)r; }

	  //! \brief Получить расстояние между краями сфер. Вернёт отрицательное значение если сферы пересекаются.
      inline float distanceBetweenSpheres(const Sphere& s) const 
	  {
		  const float dist = center.distance(s.center);
		   float res = dist - ( radius + s.radius );
		  return res;
	  }

	  //! \brief Проверка пересечения сфер  . ПРОВЕРЕНО
	  inline bool checkIntersectSphere(const Sphere& s) const 
	  {
		  const float dist = center.distance(s.center);
		  const float rsum = radius + s.radius;

		  if (dist > (rsum) ) 
			     return false;

		  return true;
	  }
	  
	  
//bool checkIntersectRay(const Ray& ray) {....}	<- ненадо. Есть у луча
//bool checkIntersecеSphere(const Sphere& sph) {....}   есть
//bool checkIntersectAABB(const AABB& aabb) {....}
//bool checkIntersectPlane(const Plane& aabb) {....}


//! \brief  Получить бокс построеный  внутри сферы.	ПРОВЕРЕНО
AABB toAabbInside() const;

//! \brief  Получить бокс построеный по краю сферы. ПРОВЕРЕНО
AABB toAabbOutside() const;		  
	 

	
	};
	// end class
	
	
	
	// много инфы по боксу   http://www.devmaster.net/forums/showthread.php?t=10324
		
	//! \brief Бокс по мин. и макс. координатам. Axis Aligned Bounding Box.
	class AABB {
	public:
	  base::vec3_s   min; ///< минимальная точка бокса
	  base::vec3_s   max; ///< максимальная точка бокса
	  
	  inline AABB() {}
	  inline AABB(const AABB& aabb) {min=aabb.min; max=aabb.max;}	  
	  inline AABB(const base::vec3_s& _min, const base::vec3_s& _max) { min=_min; max=_max;  }
	

	  inline bool operator == (const AABB& aabb) { return (min == aabb.min) && (max == aabb.max); }
	  
 
 	  //! \brief Вернуть объединённый с боксом	
	  inline AABB operator + (const AABB& aabb) const
	  {
	    AABB res = *this;
	    if (aabb.min.x < res.min.x)   res.min.x = aabb.min.x;
	    if (aabb.min.y < res.min.y)   res.min.y = aabb.min.y;
	    if (aabb.min.z < res.min.z)   res.min.z = aabb.min.z;
	   
	    if (aabb.max.x > res.max.x)   res.max.x = aabb.max.x;
	    if (aabb.max.y > res.max.y)   res.max.y = aabb.max.y;
	    if (aabb.max.z > res.max.z)   res.max.z = aabb.max.z;  
		 return res; 
	  }
	  
	  //! \brief Вернуть объединённый с точкой	 
	  inline AABB operator + (const base::vec3_s& pnt) const	  
	  {
	     AABB res = *this;
	  	if(pnt.x < res.min.x) res.min.x = pnt.x;
		if(pnt.y < res.min.y) res.min.y = pnt.y;
		if(pnt.z < res.min.z) res.min.z = pnt.z;

		if(pnt.x > res.max.x) res.max.x = pnt.x;
		if(pnt.y > res.max.y) res.max.y = pnt.y;
		if(pnt.z > res.max.z) res.max.z = pnt.z;
		  return res;	  
	  }
	  
	  //! \brief Объединить с боксом  
	  inline AABB& operator += (const AABB& aabb)
	  {
	    if (aabb.min.x < min.x)  min.x=aabb.min.x;
	    if (aabb.min.y < min.y)  min.y=aabb.min.y;
	    if (aabb.min.z < min.z)  min.z=aabb.min.z;
	   
	    if (aabb.max.x > max.x)  max.x=aabb.max.x;
	    if (aabb.max.y > max.y)  max.y=aabb.max.y;
	    if (aabb.max.z > max.z)  max.z=aabb.max.z; 
		 return *this;	  
	  }
	  
	  //! \brief Объединить с точкой pnt	 
	  inline AABB& operator += (const base::vec3_s& pnt)
	  {
		 includePoint(pnt);
		 return *this;	  
	  }
 
	  
	  inline void set(float min_x, float min_y, float min_z,
					  float max_x, float max_y, float max_z)
	  {
		 min.x=min_x; min.y=min_y; min.z=min_z;
		 max.x=max_x; max.y=max_y; max.z=max_z;					  
	  }
	  
	  //! \brief Получить центр бокса
	  base::vec3_s center() const 
	  { 
	    base::vec3_s res;
		  res.x = (max.x + min.x)/2.0f;
		  res.y = (max.y + min.y)/2.0f;		
		  res.z = (max.z + min.z)/2.0f;		
	    return res; 
	  }
	  
	  //! \brief  Включить координату pnt в бокс
	  AABB& includePoint(const base::vec3_s& pnt) 
	  {
	    if (pnt.x < min.x) min.x = pnt.x;
		if (pnt.y < min.y) min.y = pnt.y;
		if (pnt.z < min.z) min.z = pnt.z;

		if (pnt.x > max.x) max.x = pnt.x;
		if (pnt.y > max.y) max.y = pnt.y;
		if (pnt.z > max.z) max.z = pnt.z;
	       return *this;
	  }
	  
	  //! \brief Привести координаты coord в пределах бокса и вернуть результат 
	  base::vec3_s clumpCoord(const base::vec3_s& coord) const
	  {
	     base::vec3_s r = coord;
		 
		   if(coord.x > max.x) r.x = max.x;
		   if(coord.x < min.x) r.x = min.x;		   
		 
		   if(coord.y > max.y) r.y = max.y;
		   if(coord.y < min.y) r.y = min.y;		 
		 
		   if(coord.z > max.z) r.z = max.z;
		   if(coord.z < min.z) r.z = min.z;		 
	   
	          return r;
	  }
	  
	  //! \brief  Размер по X
	  inline float size_x() const { return max.x - min.x; }
	  //! \brief  Размер по Y	  
	  inline float size_y() const { return max.y - min.y; }	
	  //! \brief  Размер по Z	  
	  inline float size_z() const { return max.z - min.z; }	

	  //! \brief Получить 3d-размер бокса
	  inline Size3d size3d() const 
	  {
	   Size3d res;
	   res.x = size_x();
	   res.y = size_y();	   
	   res.z = size_z();	   
	   return res;
	  }
	  
	  //! \brief Получить объём 
	  inline float volume() const { return size_x() * size_y() * size_z(); }
	  
	  
	  /* **********************************
      plane_s  plane_positive_x() const 
	  {
	   plane_s res;
	   res.makeFromPoints( vec3_s(xxx , xxx, xxx) , vec3_s(xxx , xxx, xxx) , vec3_s(xxx , xxx, xxx) );
	   return res;
	  }
 
      plane_s  plane_negative_x() const 
	  {
	   plane_s res;
	   res.makeFromPoints( vec3_s(xxx , xxx, xxx) , vec3_s(xxx , xxx, xxx) , vec3_s(xxx , xxx, xxx) );
	   return res;
	  } 
  
	  
	  
	  *************************************/
	  
	  /*     AABB& union(const AABB& b) 
	  {
	      if(b.min.x  min.x)
	  
	  }   
	  */
	
/*  *********************	
// void transform(const mat44_s& m) {...}
************************ */ 
	

//! \brief Объединить с боксом	  
inline AABB& unionWith( const AABB& aabb)
{
   if (aabb.min.x <   min.x)     min.x=aabb.min.x;
   if (aabb.min.y <   min.y)     min.y=aabb.min.y;
   if (aabb.min.z <   min.z)     min.z=aabb.min.z;
   
   if (aabb.max.x >   max.x)     max.x=aabb.max.x;
   if (aabb.max.y >   max.y)     max.y=aabb.max.y;
   if (aabb.max.z >   max.z)     max.z=aabb.max.z; 

  return *this;   
}

	  
	 // Sphere toSphere() const
	 // {
	 //   Sphere res;
		
	//	cccc
	 //   return res;
	 // }
	  

//! \brief Проверка точки на нахождение в боксе.   ПРОВЕРЕНО!
inline bool checkContainPoint(const base::vec3_s& p )
{
  return      (p.x <= this->max.x) && (p.x >= this->min.x)
           && (p.y <= this->max.y) && (p.y >= this->min.y)
           && (p.z <= this->max.z) && (p.z >= this->min.z);
}	  
	

bool checkIntersectPlane(const plane_s& pl) const;

//bool checkIntersectRay(const Ray& ray) {....}
//bool checkIntersecеSphere(const Sphere& sph) {....}
//bool checkIntersectAABB_ex(Plane& outContactPlane, const AABB& aabb) {....}
	
	
//* времянка. Проверка пересечения боксов.
bool checkIntersectAABB(const AABB& b) const
{
    if( (max.x < b.min.x) || (min.x > b.max.x) ) return false;
    if( (max.y < b.min.y) || (min.y > b.max.y) ) return false;
    if( (max.z < b.min.z) || (min.z > b.max.z) ) return false;
    return true;
}	
	
	
// http://www.devmaster.net/forums/showthread.php?t=10324   #5	
bool checkIntersect(AABB& aabb) const
{
    return
        min.x > aabb.max.x || max.x < aabb.min.x ||
        min.y > aabb.max.y || max.y < aabb.min.y ||
        min.z > aabb.max.z || max.z < aabb.min.z;
}	
	
	


	};
		



	//! \brief   Линия в трёхмерном пространстве по двум точкам  
	class Line {
	public:
		base::vec3_s   src; 
		base::vec3_s   dest;

		inline Line() {};
		inline Line(const Line& l) {src=l.src; dest=l.dest; };	
		inline Line(const base::vec3_s& _src, const base::vec3_s& _dest) {src=_src; dest=_dest; };

		//! \brief Получить направление от src к dest
		inline base::vec3_s direction() const { base::vec3_s r (dest - src); r.normalize(); return r; }



      #if ( defined(GB_OPENGL) &&  defined(__GL_H__) )
		//! \brief Вывод вершин для OpenGl по старинке.
		inline void glVertex() { glVertex3f(src.x, src.y, src.z); glVertex3f(dest.x, dest.y, dest.z);   };
      #endif


		//! вывод на консоль.
		inline void print() const { src.print(); printf("  "); dest.print(); printf("  \n"); };

	}; // Line






	/** \brief  Углы Элера. Сборка углов поворота по всем трём осям. */
	class EulerAngles {
	public:
		float yaw;    ///<   Yaw around the y-axis, in radians. 
		float pitch;  ///<   Pitch around the x-axis, in radians.
		float roll;   ///<   Roll around the z-axis, in radians.
 
		inline EulerAngles() {};
		inline EulerAngles(const EulerAngles& ea  ) {yaw=ea.yaw; pitch=ea.pitch; roll=ea.roll; };
		inline EulerAngles(float fYaw, float fPitch, float fRoll) { yaw=fYaw;  pitch=fPitch;  roll=fRoll; };
 


	};





	//! \brief   Проскость 
	struct plane_s {
		  union {

		   struct { float x , y , z , w ;   };
		   struct { float a , b , c , d ;   };

	       float floats [4];

		  };

	   //! \brief  Присваивание из float-массива
	   inline void operator = (const float* pfArray)
	   {
		   a = pfArray[0]; 
		   b = pfArray[1];
		   c = pfArray[2];
		   d = pfArray[3];	   
	   }

	   inline operator        float*()       { return &a; };
	   inline operator const  float*() const { return &a; };

#ifdef GB_D3DX9
    inline operator       D3DXPLANE*()       { return (D3DXPLANE*)&a; }
    inline operator const D3DXPLANE*() const { return (D3DXPLANE*)&a; }	
    inline operator D3DXPLANE () { return D3DXPLANE(a,b,c,d); }
	inline 	void operator = (const D3DXPLANE& p) {a=p.a; b=p.b; c=p.c; d=p.d; }
	
#endif	   

	   inline void make(float _a, float _b, float _c, float _d)  
	   { 
	       a=_a; 
		   b=_b; 
		   c=_c; 
		   d=_d; 
		   normalize(); 
	   }


	    //! \brief Построение плоскости по координате point и нормали normal.
		inline plane_s& makeFromPointNormal(const base::vec3_s& point, const base::vec3_s& normal) 
		{
			base::vec3_s nn(normal);  //< возможно принудительную нормализацию надо убрать .
			nn.normalize();
			a=nn.x;  
			b=nn.y;  
			c=nn.z;  
			d= -( nn.dot(point) );    // -( normal.dot(point) ); 
			return *this;
		};

        //! \brief Построение плоскости по точкам.
		inline plane_s& makeFromPoints(const base::vec3_s& p1, const base::vec3_s& p2, const base::vec3_s& p3 ) 
		{
			base::vec3_s vsub1 = p1 - p2;    	 
			vsub1.normalize();

			base::vec3_s vsub2 = p1 - p3;	 
			vsub2.normalize();

			base::vec3_s nrml = vsub1.cross(vsub2);   
			nrml.normalize();

			makeFromPointNormal(p1, &nrml);
			return *this;
		}

		//! \brief   Нормализовать плоскость.  ПРОВЕРЕНО!
		inline void normalize() 
		{
			register const float fm = sqrt(a*a + b*b + c*c); 
			a/= fm;	
			b/= fm; 
			c/= fm; 
			d/= fm; 
		}

		// ПРОВЕРЕНО!
		inline float dot(const base::vec4_s& v) const        { return a*v.x + b*v.y + c*v.z + d*v.w ; }
		inline float dotCoord  (const base::vec3_s& vCoord) const { return a*vCoord.x + b*vCoord.y + c*vCoord.z + d*1.0f; }
		inline float dotNormal (const base::vec3_s& vNormal) const { return a*vNormal.x + b*vNormal.y + c*vNormal.z + d*0.0f; }

		//! \brief   Масштабировать плоскость. ПРОВЕРЕНО!
		inline void scale(float s) {a*=s; b*=s; c*=s; d*=s; }


		//! \brief  Вернуть нормаль плоскости.  
		inline base::vec3_s  normal() const  
		{ 
			base::vec3_s res; 
			res.x=a; 
			res.y=b; 
			res.z=c; 
			return res; 
		}

		//! \brief  Инвертировать плоскость  
		inline void inverse() { a*=-a; b*=-b; c*=-c;  }

		//! \brief  Получить инвертированую плоскость
		inline plane_s inverted() const { plane_s res = *this; res.inverse(); return res; }
 
		//! \brief Проверка точки содержится ли она внутри плоскости.
		inline bool checkPointInside(const base::vec3_s& point)
		{
		  if( dotCoord(point) < 0.0f ) return true;
		  return false;
		}
		
		//! \brief Получить минимальное расстояние от точки pnt до плоскости .
		inline float distance(const base::vec3_s& point)
		{
		   return abs( dotCoord(point) ); 
		}
 
 
 
 
 
		//! \brief  Вывод на консоль.
		void print() const 	{ printf( "%f  %f  %f  %f", a, b, c, d); 	}


	};


	

	//! \brief Луч в 3-D по позиции и направлению   
	class Ray {
	public:
	   base::vec3_s   orig; ///< точка центр луча (позиция)
	   base::vec3_s   dir;  ///< направление луча. Должен быть нормализован.
	   
	   inline Ray() {}
	   inline Ray(const Ray& r) {orig=r.orig; dir=r.dir; }
	   
	   // возможно нужно убрать параметр bNeedNormalizeDir
	   inline Ray(const base::vec3_s& _orig, const base::vec3_s& _dir, bool bNeedNormalizeDir=true)
       {
	      orig=_orig;
	      dir=_dir;
	      if(bNeedNormalizeDir) 
			  dir.normalize();	   
	   }

	//! \brief  Трансформировать луч по матрице m
	inline void transform(const base::mat44_s& m)
	{
	     orig.transformCoord(m);
	     dir.transformNormal(m);
	}
	
 

//>>>>>>>>>>>>>>>       checkIntersectSphere  >>>>>>>>>>>>>>>>>>>>>>>>>>>

//  http://netlib.narod.ru/library/book0032/ch15_04.htm
bool  checkIntersectSphere(const Sphere& sphere) const
{
	base::vec3_s v =  this->orig - sphere.center;

     float b = 2.0f * this->dir.dot(v);
     float c =    v.dot(v) - (sphere.radius * sphere.radius);

     // Находим дискриминант
     float discriminant = (b * b) - (4.0f * c);

     // Проверяем на мнимые числа
     if(discriminant < 0.0f)
	 {
          return false;
	 }

     discriminant = sqrtf(discriminant);

     float s0 = (-b + discriminant) / 2.0f;
     float s1 = (-b - discriminant) / 2.0f;

     // Если есть решение >= 0, луч пересекает сферу
     if(s0 >= 0.0f || s1 >= 0.0f)
	 {
          return true;
	 }

     return false;
}

	 
 /**   \brief 
 http://www.gamecoder.ru/2011/04/3d-3d.html    */
bool checkIntersectSphere_2 (const Sphere& sphere, float* result)
{
	base::vec3_s vect = orig - sphere.center ;

   const float c = vect.lengthSq() -  sphere.radius * sphere.radius;
   float res = 0.0f;

   if(c < 0.0f)
   {
	   res = 0.0f;
     if(result) *result = 0.0f;
      return true;
   }


  const  float b = vect.dot(dir);//    dotProduct(vect, ray.direction);


   const float d = b*b - c;


   if (d < 0.0f)
   {
      return (false);
   }


   float root1 = -b - sqrt(c);
   float root2 = -b + sqrt(c);


   if(root1 >= root2)
	   res = root1;
      if(result) *result = root1;
   else
	   res =  root2;
      if(result) *result = root2;
  
   return ( res >= 0.0f );
}


// Aslan.   Проверка пересечения со сферой.  ПРОВЕРЕНО
bool checkIntersectSphere_3( const Sphere& sph )   
{
  float res = 0.0f;

 // квадрат радиуса
  const float r =  (sph.radius * sph.radius);
  
  // квадрат расстояния от точки до центра сферы
   float d;
  {
	 //  assert(false);
	  // inline float distanceSq(const vec3_s& point) const { return vec3_s(*this-point).lenghtSq ;  }
	//  vec3_s vs = sph.center-orig;
    // d =  vs.lengthSq(); //  sph.center.lengthSq();//  lenghtSq(p); // norm2(c-p);
	   d = sph.center.distanceSq(orig);
  }
  
  // проекция центра сферы на луч
  float s =   (sph.center-orig).dot(dir) / dir.length(); //         sprod(c-p,l)/norm(l);
  
  if( (d>r) && (s<0) ) // точка снаружи сферы и луч направлен от сферы
  {
  
    res = INF; // return INF; // нет пересечения
	 return false;
  }
	
  // квадрат расстояния от прямой до центра сферы по теореме Пифагора
  float h = d - s*s;
  
  if(h>r) // луч не пересекает сферу
  {
      res = INF;
	return false;
  }
 
  res = s+sqrt(r-h)*math::scalar::sign(r-d); // расстояние до пересечения

  // inline int Sign(float x) {  return (x>0)-(x<0);  }
  
  return  true;
}



//
//>>>>>>>>>>>>>>      checkIntersectAABB        >>>>>>>>>>>>>>>>>>>>>>>>>>>
//

//bool checkIntersectAABB( const AABB& aabb) {....}


// http://www.gamecoder.ru/2011/04/3d-3d.html
bool checkIntersectAABB(const AABB& aabb,  float* result)
{
   //Проверим если луч находится внутри параллелепипеда.
   if (   orig.x >= aabb.min.x
       && orig.x <= aabb.max.x
       && orig.y >= aabb.min.y
       && orig.y <= aabb.max.y
       && orig.z >= aabb.min.z
       && orig.z <= aabb.max.z)
   {
      *result = 0.0f;
      return true;
   }


   float t_near = FLT_MIN;
   float t_far = FLT_MAX;
   float t1;
   float t2;
   float tmp;



   if(dir.x != 0.0f)
   {
      t1 = (aabb.min.x - orig.x) / dir.x;
      t2 = (aabb.max.x - orig.x) / dir.x;

      if(t1 > t2)
      {
         tmp = t1;
         t2 = t1;
         t2 = tmp;         
      }
      
      if(t1 > t_near)
      {
         t_near = t1;
      }

      if(t2 < t_far)
      {
         t_far = t2;
      }

      if(t_near > t_far) return false;
      if(t_far < 0) return false;

   }




   if(dir.y != 0.0f)
   {
      t1 = (aabb.min.y - orig.y) / dir.y;
      t2 = (aabb.max.y - orig.y) / dir.y;

      if(t1 > t2)
      {
         tmp = t1;
         t2 = t1;
         t2 = tmp;         
      }
      
      if(t1 > t_near)
      {
         t_near = t1;
      }

      if(t2 < t_far)
      {
         t_far = t2;
      }

      if(t_near > t_far) return false;
      if(t_far < 0) return false;

   }

   if(dir.z != 0.0f)
   {
      t1 = (aabb.min.y - orig.y) / dir.y;
      t2 = (aabb.max.y - orig.y) / dir.y;

      if(t1 > t2)
      {
         tmp = t1;
         t2 = t1;
         t2 = tmp;         
      }
      
      if(t1 > t_near)
      {
         t_near = t1;
      }

      if(t2 < t_far)
      {
         t_far = t2;
      }

      if(t_near >= t_far) return false;
      if(t_far < 0) return false;
   }

   *result = t_near;

   return (*result < t_far && *result >= 0);
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

 
//
//>>>>>>>>>>>>>>>>>  checkIntersectPlane  >>>>>>>>>>>>>>>>>>>>>>>>>
//

//bool checkIntersectPlane(vec3& outContactCoord, const Plane& aabb) {....} 

// http://www.gamecoder.ru/2011/04/3d-3d.html

bool checkIntersectPlane( const plane_s& plane , float* pfOutResult=NULL) const
{
	const base::vec3_s plNrml = plane.normal();
   const float alpha = plNrml.dot(dir); //    dotProduct(plane.normal, dir);

   float fres = 0.0f;

   if(alpha != 0.0f)
   {
	    fres  = //   ( - dotProduct(plane.normal(), orig ) + plane.d )/alpha;
		 ( -  plNrml.dot(orig)  + plane.d ) / alpha;

	   if(pfOutResult)
	   {
         *pfOutResult = fres ;
	   }

      return ( fres >= 0.0f );
   }


   return false;
}

 //--------------------------------------------------------

// http://www.gamespp.com/algorithms/collisionDetectionTutorial02.html
// find the distance between a ray and a plane.
inline float distanceToPlane( plane_s& plane )   const
{

	const base::vec3_s vRayOrigin = orig;
	const base::vec3_s vnRayVector = dir;

	const  base::vec3_s& vnPlaneNormal = plane.normal();
	const float planeD = plane.d;



	float cosAlpha = vnRayVector.dot(vnPlaneNormal);

	// parallel to the plane (alpha=90)
	if (cosAlpha==0)
	{
		return -1.0f;
	}


	float  deltaD = planeD -  vRayOrigin.dot(vnPlaneNormal); //  DotProduct(vRayOrigin,vnPlaneNormal);

	return (deltaD/cosAlpha);
}
 
	
	   //! \brief  вывод на консоль.
       inline void print() const { orig.print(); printf("  "); dir.print(); printf("  "); };
	
	};
 
   //----------------------------------------------------------------------



	// ! УБРАТЬ !!!
	class Plane : public plane_s {
	public:
		inline Plane() {};
		inline Plane(const Plane& p) {a=p.a; b=p.b; c=p.c; d=p.d; }

		inline Plane(float _a, float _b, float _c, float _d) { a=_a; b=_b; c=_c; d=_d; }


		//---------------------------------------------------------------------
		//                        ОПЕРАТОРЫ
		//---------------------------------------------------------------------




		inline bool operator == ( const Plane& p ) const
		{
			return a == p.a && b == p.b && c == p.c && d == p.d;
		}

		inline bool operator != ( const Plane& p ) const
		{
			return a != p.a || b != p.b || c != p.c || d != p.d;
		}

		inline Plane& operator *= ( const float f )
		{
			a *= f;  b *= f;  c *= f;  d *= f;   return *this;
		}

		inline Plane& operator /= ( const float f )
		{
			const float fi = 1.0f/f;    a*=fi;  b*=fi;  c*=fi;  d*=fi;   return *this;
		}



		inline Plane operator + () const {    return *this; }
		inline Plane operator - () const {   return Plane(-a, -b, -c, -d);}

		inline Plane operator * ( const float f ) const
		{
			return Plane(a * f, b * f, c * f, d * f);
		}

		inline Plane operator / ( const float f ) const
		{
			const float fi = 1.0f / f;  return Plane(a*fi, b*fi, c*fi, d*fi);
		}

		inline friend Plane operator * (float f, const Plane& p )
		{
			return Plane(f*p.a, f*p.b, f*p.c, f*p.d);
		}
 
		//---------------------------------------------------------------------
		//                         МЕТОДЫ
		//---------------------------------------------------------------------
 
	};



	struct quat_s {

		union {
			struct { float x, y, z, w;  };
			float floats [4];
		};


	};





	//! \brief Стандартный  кватернион.
	class Quaternion : public quat_s {
	public:

		inline Quaternion() { x=y=z=0.0f; w=1.0f; };
		inline Quaternion(const Quaternion& q) { x=q.x; y=q.y; z=q.z; w=q.w; };
		inline Quaternion(float _x, float _y, float _z, float _w) { x=_x; y=_y; z=_z; w=_w; };
		inline Quaternion(const float* pfArray)
		{
			 x = pfArray[0];
			 y = pfArray[1];
			 z = pfArray[2];
			 w = pfArray[3];
		}

		//-----------------------------------------------------------------
		//                     ОПЕРАТОРЫ
		//-----------------------------------------------------------------

		inline operator         float*()         { return &x; };
		inline operator const   float*() const   { return &x; };


		inline bool operator == (const Quaternion &q) const
		{ 
			return	x == q.x && y == q.y && z == q.z && w == q.w ||
				x == -q.x && y == -q.y && z == -q.z && w == -q.w;
		}

		inline bool operator != (const Quaternion &q) const
		{
			return	!(x == q.x && y == q.y && z == q.z && w == q.w ||
				x == -q.x && y == -q.y && z == -q.z && w == -q.w);
		}

		inline Quaternion&  operator += ( const Quaternion& q )
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			return *this;
		}

		inline Quaternion& operator -= ( const Quaternion& q )
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			return *this;
		}
 
		inline Quaternion& operator *= ( const float f )
		{
			x *= f;
			y *= f;
			z *= f;
			w *= f;
			return *this;
		}

		inline Quaternion& operator /= ( const float f )
		{
			const float  fInverse = 1.0f/f;
			x *= fInverse;
			y *= fInverse;
			z *= fInverse;
			w *= fInverse;
			return *this;
		}
 
		inline Quaternion operator + () const
		{
			return *this;
		}

		inline Quaternion operator - () const
		{
			return Quaternion(-x, -y, -z, -w);
		}

		inline Quaternion operator + ( const Quaternion& q ) const
		{
			return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
		}

		inline Quaternion operator - ( const Quaternion& q ) const
		{
			return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
		}
 

		//!   ПРОВЕРЕНО
		inline Quaternion operator * ( const Quaternion &q ) const 
		{
			Quaternion res;
			res.x = w*q.x + x*q.w + z*q.y - y*q.z;
			res.y = w*q.y + y*q.w + x*q.z - z*q.x;
			res.z = w*q.z + z*q.w + y*q.x - x*q.y;

			res.w = w*q.w - x*q.x - y*q.y - z*q.z;
			return res;
		}
 
		inline Quaternion operator * ( const float f ) const
		{
			return Quaternion( x*f, y*f, z*f, w*f );
		}


		inline Quaternion operator / ( const float f ) const
		{
			const float fInverse = 1.0f / f;
			return Quaternion(x * fInverse, y * fInverse, z * fInverse, w * fInverse);
		}
 
		inline Quaternion&   operator *= (const Quaternion &q) { Quaternion r(*this); *this=r*q; return *this;   } 
 

#ifdef GB_D3DX9
		inline operator D3DXQUATERNION*()             { return (D3DXQUATERNION*)&x; }
		inline operator const D3DXQUATERNION*() const { return (D3DXQUATERNION*)&x; }
		inline operator D3DXQUATERNION() { return D3DXQUATERNION( x , y , z , w ); }
		inline void operator = (const D3DXQUATERNION& q) { x=q.x; y=q.y; z=q.z; w=q.w; }
#endif //#ifdef GB_D3DX9



		//----------------------------------------------------------------//
		//                           МЕТОДЫ		        	              //
		//----------------------------------------------------------------//
 
		// \brief  Присвоить значения  затем нормализовать
		inline void set(float _x, float _y, float _z, float _w)
		{
			x=_x; y=_y; z=_z; w=_w;
			normalize();
		}

		// \brief Сбросить в идентичный
		inline void setIdentity() { x=y=z=0.0f; w=1.0f; }
		// \brief Сбросить в идентичный
		inline void reset() { setIdentity(); }

		// \brief Проверка на идентичное значение
		inline bool isIdentity(float eps = 0.0f) const
		{ 
			return abs(x) <= eps && abs(y) <= eps && abs(z) <= eps && abs(w) - 1.0f <= eps;
		}

		//! \brief  Получить длинну
		inline float length() const	{ return sqrt(x*x + y*y + z*z + w*w); }
		//! \brief  Получить квадрат длинны
		inline float lengthSq() const {	return   (x*x + y*y + z*z + w*w); }

		// \brief   Нормализовать   ПРОВЕРЕНО!
		inline Quaternion&  normalize()
		{
			const float len = length();
			if (len > 1e-6) 
			{
				x /= len;
				y /= len;
				z /= len;
				w /= len;
			}
			return *this;
		}

		// //! \brief Получить нормализованый кватернион
		// inline Quaternion getNormalized() const { Quaternion r = *this; r.normalize(); return r;  }

		//! \brief  вернуть сопряженный кватернион   ПРОВЕРЕНО
		inline Quaternion conjugate(const Quaternion &q) const
		{
			  Quaternion res;
			    res.w =  q.w;
			    res.x = -q.x;
			    res.y = -q.y;
			    res.z = -q.z;
			  return  res;
		}

		//! \brief Вернуть скалярное произведение 
		inline float dot(const Quaternion &g) const 
		{
			return w*g.w + x*g.x + y*g.y + z*g.z;
		}

		//! \brief return  exponentiation
		Quaternion  pow(const Quaternion &q, float exponent) const;

		//! \brief  Инвертировать.  ПРОВЕРЕНО !
		void inverse () 
		{
			const float fNorm = x*x + y*y + z*z + w*w;
			if ( fNorm > 0.0 )
			{
				const float fin = 1.0f/fNorm;
				w =   w * fin;
				x = - x * fin;
				y = - y * fin;
				z = - z * fin;
			}
			else
			{

			}
		}

		//! \brief  Вернуть инвертированый .
		inline Quaternion inversed() const 
		{
		  Quaternion res(*this);
		  res.inverse(); 
		  return res;
		}


 

		////*  natural log
		//Quaternion  logn () const
		//{
		//	Quaternion res;

		//	//		A unit quaternion, is defined by:
		//	//Q == (cos(theta), sin(theta) * v) where |v| = 1
		//	//The natural logarithm of Q is, ln(Q) = (0, theta * v)


		//	//????
		//		return res;

		//}



		// todo !!!!!!!!!!!!!!!!!!!
	//	Quaternion& setFromRotationMatrix(const base::mat44_s& m);





#ifdef GB_D3DX9


		//! \brief Сделать без d3dx  return calculates the natural logarithm.
		Quaternion ln(const Quaternion& q)
		{
		//A unit quaternion, is defined by:
		//Q == (cos(theta), sin(theta) * v) where |v| = 1
		//The natural logarithm of Q is, ln(Q) = (0, theta * v)
             Quaternion res;
			D3DXQuaternionLn(res , *this );
			return res;
		}



		// todo Сделать без d3dx
		Quaternion  exp(const Quaternion& qu) const 
		{
			//Given a pure quaternion defined by:
			// q = (0, theta * v); 
			//This method calculates the exponential result.
			//exp(Q) = (cos(theta), sin(theta) * v)
			Quaternion res;
			D3DXQuaternionExp(  res , qu  );
			return res;
		};


		// todo Сделать без d3dx
	   Quaternion& setBaryCentric(const Quaternion& q1,	const Quaternion& q2,const Quaternion& q3, float f,	float g	)
	   {
		   D3DXQuaternionBaryCentric( *this, q1, q2, q3, f,	g);
           return *this;
	   };


      // todo Сделать без d3dx
      Quaternion& setSquad(const Quaternion& q1, const Quaternion& a,  const Quaternion& b,  const Quaternion& c, float t )
	  {
		  D3DXQuaternionSquad( *this, q1, a, b, c, t);
		  return *this;
	  };


      static void  squadSetup( Quaternion& AOut, Quaternion& BOut, Quaternion& COut,
	             const Quaternion& Q0, const Quaternion& Q1, const Quaternion& Q2, const Quaternion& Q3 )
	   {
		     D3DXQuaternionSquadSetup( AOut,  BOut, COut, Q0,  Q1, Q2 , Q3  );
	   };



#endif GB_D3DX9



		/**  имеются небольшие несоответствия с d3dx  
		-------------------------------------
		0.606882  0.275320  0.666870  0.333432
		-------------------------------------
		0.610759  0.206986  0.689953  0.328778
		*/
	    Quaternion slerp(const Quaternion&q, float t);

		//inline Quaternion slerp(const Quaternion &q, float t) const { Quaternion r = slerp(*this, q, t); return r;  };


		inline float getRotationAngle() const 
		{
			// Compute the half angle.  Remember that w = cos(theta / 2)
			float thetaOver2 = scalar::safeAcos(w);
			// Return the rotation angle
			return thetaOver2 * 2.0f;
		}

		base::vec3_s  getRotationAxis() const;

		inline AxiesAngle getRotationAxiesAngle() const 
		{
			AxiesAngle res;
			res.angle = getRotationAngle();
			res.axies = getRotationAxis();
			return res;
		}

		inline AxiesAngle toAxiesAngle() const { return getRotationAxiesAngle(); }


		inline Quaternion& setRotationX(float theta) {

			// Compute the half angle
			const float k = theta*0.5f;

			// Set the values
			w = cos(k);
			x = sin(k);
			y = 0.0f;
			z = 0.0f;
			return *this;
		}

		inline Quaternion&	setRotationY(float theta) 
		{
			const float	k =   theta*0.5f;
			w = cos(k);
			x = 0.0f;
			y = sin(k);
			z = 0.0f;
			return *this;
		}

		inline Quaternion&  setRotationZ(float theta) 
		{
			float	k = theta*0.5f;
			w = cos(k);
			x = 0.0f;
			y = 0.0f;
			z = sin(k);
			return *this;
		}

		Quaternion&         setRotationAxis(const base::vec3_s &axis, float theta) ;

		inline Quaternion&  setRotationAxis(const AxiesAngle& aa)
		{
		  return setRotationAxis( aa.axies , aa.angle );
		}



		//// ПРОВЕРИТЬ !!!!
		//void  setFromMatrix(const base::mat44_s& m) 
		//{

		//	float fTrace = m.floats[0][0] + m.floats[1][1] + m.floats [2][2];
		//	float fRoot;

		//	if (fTrace > 0.0) 
		//	{

		//		fRoot =   sqrt(fTrace + 1.0f);//  math::sqrt(fTrace + 1.0f);
		//		w = 0.5f * fRoot;

		//		fRoot = 0.5f / fRoot;

		//		x = ( m.floats[1][2] - m.floats[2][1]) * fRoot;
		//		y = ( m.floats[2][0] - m.floats[0][2]) * fRoot;
		//		z = ( m.floats[0][1] - m.floats[1][0]) * fRoot;
		//	}
		//	else
		//	{
		//		static size_t s_iNext[3] = { 1, 2, 0 };
		//		size_t i = 0;

		//		if (m.floats[1][1] > m.floats[0][0]) i = 1;
		//		if (m.floats[2][2] > m.floats[i][i]) i = 2;

		//		size_t j = s_iNext[i];
		//		size_t k = s_iNext[j];

		//		fRoot = sqrt(m.floats[i][i] - m.floats[j][j] - m.floats[k][k] + 1.0f);//math::sqrt(m.data[i][i] - m.data[j][j] - m.data[k][k] + 1.0f);

		//		v[i] = 0.5f * fRoot;
		//		fRoot = 0.5f / fRoot;
		//		w    = (m.floats[j][k] - m.floats[k][j]) * fRoot;
		//		v[j] = (m.floats[i][j] + m.floats[j][i]) * fRoot;
		//		v[k] = (m.floats[i][k] + m.floats[k][i]) * fRoot;
		//	}


		//}



		//! \brief  Построить поворотный по углам эллера
		void setRotationYawPitchRoll( float yaw, float pitch, float roll)
		{
			float	sp, sb, sh;
			float	cp, cb, ch;
			gb::math::scalar::sincos(pitch * 0.5f , sp , cp  ); 
			gb::math::scalar::sincos(roll * 0.5f  , sb , cb  );
			gb::math::scalar::sincos(yaw * 0.5f   , sh , ch  );
			  x =  -(-ch*sp*cb - sh*cp*sb);
			  y =  -(ch*sp*sb  - sh*cb*cp);
			  z =  -(sh*sp*cb  - ch*cp*sb);
			  w =  ch*cp*cb + sh*sp*sb;
		}
		//! \brief  Построить поворотный по углам эллера  
		inline void setRotationEulersAngles(const EulerAngles& ea)
		{
		     setRotationYawPitchRoll(ea.yaw, ea.pitch, ea.roll);
		}
 
 /*
		inline void  invert() 
		{
			*this = conjugate(*this);
			*this /= lengthSq();
		}

		inline Quaternion inverse() const 
		{
			return conjugate(*this) / lengthSq();
		}
*/


		//! \brief  Вывод на консоль
		void print() const { printf("%f  %f  %f  %f" , x , y, z, w ); }

	};




	//! \brief Треугольник по трём точкам . 
	class Triangle {
	public:
		base::vec3_s   p1; ///< первая точка(вершина) треугольника 
		base::vec3_s   p2; ///< вторая точка(вершина) треугольника   
		base::vec3_s   p3; ///< третья точка(вершина) треугольника 


		inline Triangle() {}
		inline Triangle(const Triangle& t) { *this = t; }
		inline Triangle(const base::vec3_s _p1, const base::vec3_s _p2, const base::vec3_s _p3) 
		{
			p1=_p1;	p2=_p2;	p3=_p3;	
		}

		inline void set(const base::vec3_s _p1, const base::vec3_s _p2, const base::vec3_s _p3) 
		{
			p1=_p1;	p2=_p2;	p3=_p3;	
		}

		/** \brief Вычислить и вернуть среднюю точку треугольника */
		inline base::vec3_s middlePoint() const 
		{ 
			base::vec3_s res;
			res.x= (p1.x + p2.x + p3.x) / 3.0f;
			res.y= (p1.y + p2.y + p3.y) / 3.0f;
			res.z= (p1.z + p2.z + p3.z) / 3.0f;
			return res;
		}

		//! \brief Вычислить и вернуть плоскость по точкам треугольника 
		plane_s getPlane() const
		{
			plane_s plane; 
			plane.makeFromPoints(p1,p2,p3); 	
			return plane;
		}


#if ( defined(GB_OPENGL) && defined(__GL_H__)   )
		//! \brief Вывод вершин по OpenGL  по старинке.
		inline void glVertex()   
		{
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
			glVertex3f(p3.x, p3.y, p3.z); 
		}
#endif





	};



	//!  \brief Клас бесконечный прожектор по лучу (точка основания) и углу прожектора 
	class  Projector {
	public:
		Ray ray;   ///< луч (центр и направление прожектора)
		float phi; ///< угол конуса

		Projector() {};
		Projector(const Projector& pr) {ray=pr.ray; phi=pr.phi;  };


	}; // Projector



   //! \brief Стандартная пирамида видимости
   class Frustum  {
   public:

	   union {
		   struct {
			   Plane  front;
			   Plane  back;  
			   Plane  left;   
			   Plane  right;   
			   Plane  top;
			   Plane  bottom;  
		   };

		   plane_s  planes[6] ;
	   };

	   inline Frustum() {}
	   inline Frustum(const Frustum& f) { *this=f; }


	   /** \brief Выполнить построение из матричного произведения view * proj */
	   void make(const base::mat44_s& mViewProj);	

	   /** \brief Выполнить построение из матриц   view и proj */
	   void make(const base::mat44_s& mView, const base::mat44_s& mProj) 
	   {
		   base::mat44_s mViewProj = mView * mProj;
		   make(mViewProj);
	   }

       //! \brief Проверка попадания точки в пирамиду 
	   bool checkPoint(const base::vec3_s& point) const; 

       //! \brief Проверка попадания сферы в пирамиду
	   bool checkSphere(const Sphere& sphere)  const; 

	   //! \brief Проверка попадания бокса в пирамиду
       bool checkAABB(const AABB& aabb) const;




     //! \brief Отладочный вывод на консоль
     inline void print() const 
	 {
		 printf("\n");
		 printf("front=");  front.print();  printf("\n");
		 printf("back=");   back.print();   printf("\n");
		 printf("left= ");  left.print();   printf("\n");
		 printf("right=");  right.print();  printf("\n");
		 printf("top=");    top.print();    printf("\n");
		 printf("bottom="); bottom.print(); printf("\n");
 	 }


   };


   //! \brief Класс цилиндр по точкам координатам центров основания и радиусу  
   class Cilinder {
   public:
	   base::vec3_s  p1;  ///< Первая центральная координата в основании цилиндра.
	   base::vec3_s  p2;  ///< Вторая центральная координата в основании цилиндра.

	   float      radius; ///< Радиус цилиндра

	   Cilinder() {}
	   Cilinder(const Cilinder& c) { p1=c.p1; p2=c.p2; radius=c.radius;  }
	   Cilinder(const base::vec3_s& _p1, const base::vec3_s& _p2, float _radius) 
	   {
		   p1=_p1; 
		   p2=_p2; 
		   radius = _radius;   
	   }


	   //! \brief Вывод значений на консоль. 
	   void print() const 
	   {
	     printf("\n");
		 printf("p1= "); p1.print(); printf("\n");
		 printf("p2= "); p2.print(); printf("\n");
		 printf("r= %f", radius);    printf("\n");
	   }




   };
   //  end class Cilinder


   //! \brief Сборка из данных трансформации: скалирование(вектор) + поворот(кват.) + позиция(вектор).
   struct TransformData
   {
	   base::vec3_s     vScaling;     ///< масштабирование
	   Quaternion       qRotation;    ///< вращение
	   base::vec3_s     vTranslation; ///<  позиция



   };



    //---------------------------------------------------------------------
	//                    КОНСТАНТЫ
	//---------------------------------------------------------------------


// static const Quaternion QUATERNION_IDENTITY = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );





    } // end ns
  } // end ns math
} // end ns gb

// end file