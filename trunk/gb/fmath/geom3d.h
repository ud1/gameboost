/** \file geom3d.h
 \brief геометрия в 3d.
*
*  Наполнение на основе выложеного ребятами в папку бранч,   опенсурсных движков,   выуженого из гугла , своих наработок.
*
*
 \todo Сделать перечечения: луч, сфера, бокс, плоскость,
  \todo   bool checkIntersectRay(const Ray& ray) {....} 
  \todo   bool checkIntersecеSphere(const Sphere& sph) {....}
  \todo  bool checkIntersectAABB(const AABB& aabb) {....} 
  \todo  bool checkIntersectPlane(const Plane& aabb) {....} 


*/
 
#pragma once

#ifndef __GB_FMATH_H__
   #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif

namespace gb 
{

  namespace fmath
  {
  
    /** \brief  геометрия в 3d  */
    namespace geom3d
	{


 
		//! \brief описание состояния пространственого  пересачения объектов
		enum  ObjContainsE   
		{ 
			SC_NOOVERLAP, ///<   объект не касается другого объекта
			SC_CONTAINSFULLY, ///<   объект  полностью расположен  в другом
			SC_CONTAINSPARTIALLY  ///< объект частично содержится в другом
		};




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

			inline operator  vec3() const { return  vec3(x,y,z); }


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
			inline Normal3(const  vec3& v) { *this = v;  }

		
			inline operator  const float*() const  { return &_x; };
			inline operator        float*()        { return &_x; };

			inline float x() const { return _x; }
			inline float y() const { return _y; }
			inline float z() const { return _z; }

			inline void operator = (const  vec3& vn)	{ _x = vn.x; _y = vn.y; _z = vn.z; __normalize(); }
			inline operator  vec3() const { return  vec3 (_x,_y,_z);  }

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
			Normal3& transform(const  mat44& m) 
			{ 
			    vec3 v = *this;
			   v.transformNormal(m);
			   //*this = v;
			   _x = v.x;
			   _y = v.y;
			   _z = v.z;
				return *this;
			}


#ifdef _D3D9_H_
			inline operator D3DVECTOR*() { return (D3DVECTOR*)&_x; }
			inline operator const D3DVECTOR*() const { return (D3DVECTOR*)&_x; }
			inline operator D3DVECTOR() const  { D3DVECTOR r; r.x=_x; r.y=_y; r.z=_z; return r;  }
			inline void operator = (const D3DVECTOR& v) {	_x=v.x; _y=v.y; _z=v.z; __normalize(); }
#endif	


#ifdef __D3DX9MATH_H__
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

			inline void operator = (const  vec3& v) { _x=v.x; _y=v.y; _z=v.z; }
			inline operator  vec3() const { return  vec3 (_x,_y,_z);  }
	
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




	//! \brief   Проскость 
	struct plane_s {

		  union {

		   struct { float x , y , z , w ;   };
		   struct { float a , b , c , d ;   };

	       float floats [4];

		  };



		  //---------------------------------------------------------------------
		  //                        ОПЕРАТОРЫ
		  //---------------------------------------------------------------------




		  inline bool operator == ( const plane_s& p ) const
		  {
			  return a == p.a && b == p.b && c == p.c && d == p.d;
		  }

		  inline bool operator != ( const plane_s& p ) const
		  {
			  return a != p.a || b != p.b || c != p.c || d != p.d;
		  }

		  inline plane_s& operator *= ( const float f )
		  {
			  a *= f;  b *= f;  c *= f;  d *= f;   return *this;
		  }

		  inline plane_s& operator /= ( const float f )
		  {
			  const float fi = 1.0f/f;    a*=fi;  b*=fi;  c*=fi;  d*=fi;   return *this;
		  }



		  inline plane_s operator + () const
		  {    
			  return *this; 
		  }

		  inline plane_s operator - () const 
		  {  
			  plane_s res;
			  res.a = -a;
			  res.b = -b;
			  res.c = -c;
			  res.d = -d;
			  return res;
		  }

		  inline plane_s operator * ( const float f ) const
		  {
			  plane_s res;
			  res.a = a * f;
			  res.b = b * f;
			  res.c = c * f;
			  res.d = d * f;
			  return  res;
		  }

		  inline plane_s operator / ( const float f ) const
		  {
			  plane_s res;
			  const float fi = 1.0f / f; 
			  res.a = a * fi;
			  res.b = b * fi;
			  res.c = c * fi;
			  res.d = d * fi;	  
			  return  res;
		  }

		  inline friend plane_s operator * (float f, const plane_s& p )
		  {
			  plane_s res;
			  res.a = f * p.a;
			  res.b = f * p.b;
			  res.c = f * p.c;
			  res.d = f * p.d;
			  return res;  // plane_s(f*p.a, f*p.b, f*p.c, f*p.d);
		  }

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

#ifdef __D3DX9MATH_H__
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
		inline plane_s& makeFromPointNormal(const  vec3& point, const  vec3& normal) 
		{
			 vec3 nn(normal);  //< возможно принудительную нормализацию надо убрать .
			nn.normalize();
			a=nn.x;  
			b=nn.y;  
			c=nn.z;  
			d= -( nn.dot(point) );    // -( normal.dot(point) ); 
			return *this;
		};

        //! \brief Построение плоскости по точкам.
		inline plane_s& makeFromPoints(const  vec3& p1, const  vec3& p2, const  vec3& p3 ) 
		{
			 vec3 vsub1 = p1 - p2;    	 
			vsub1.normalize();

			 vec3 vsub2 = p1 - p3;	 
			vsub2.normalize();

			 vec3 nrml = vsub1.cross(vsub2);   
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
		inline float dot(const  vec4& v) const        { return a*v.x + b*v.y + c*v.z + d*v.w ; }
		inline float dotCoord  (const  vec3& vCoord) const { return a*vCoord.x + b*vCoord.y + c*vCoord.z + d*1.0f; }
		inline float dotNormal (const  vec3& vNormal) const { return a*vNormal.x + b*vNormal.y + c*vNormal.z + d*0.0f; }

		//! \brief   Масштабировать плоскость. ПРОВЕРЕНО!
		inline void scale(float s) {a*=s; b*=s; c*=s; d*=s; }


		//! \brief  Вернуть нормаль плоскости.  
		inline  vec3  normal() const  
		{ 
			 vec3 res; 
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
		inline bool checkPointInside(const  vec3& point)
		{
		  if( dotCoord(point) < 0.0f ) return true;
		  return false;
		}
		
		//! \brief Получить минимальное расстояние от точки pnt до плоскости .
		inline float distance(const  vec3& point)
		{
		   return abs( dotCoord(point) ); 
		}
 
 
 
 
 
		//! \brief  Вывод на консоль.
		void print() const 	{ printf( "%f  %f  %f  %f", a, b, c, d); 	}


	};





		//! \brief  Сборка  ось повотора и угол
		struct AxiesAngle {

			 vec3   axies; ///< ось повотора (должен быть нормализован)
			float   angle; ///< угол поворота

		};
		
	//! \brief Сфера по центральной точке и радиусу. Она же Bounding sphere.
	class Sphere {
	public:
	   vec3  center;  ///<  центральная координата сферы.
	  float   radius;  ///<  радиус сферы.
	  
	  inline Sphere() {}
	  inline Sphere(const Sphere& s) {center=s.center; radius=s.radius; }
	  inline Sphere(const  vec3& _center, const float _radius) {center=_center; radius=_radius; }	  
	  
	
	  inline void set(const  vec3& vCenter, float fRadius) {center=vCenter; radius=fRadius; }
	  inline void set( float centerX, float centerY, float centerZ, float fRadius) { center.x=centerX;  center.y=centerY;  center.z=centerZ;  radius=fRadius; 	}
//	  inline void set(int ix, int iy, int iz, int r) { center.x=(float)ix;  center.y=(float)iy;  center.z=(float)iz;	radius = (float)r; }

	  //! \brief Получить расстояние между краями сфер. Вернёт отрицательное значение если сферы пересекаются.
	  inline float distanceBetweenSpheres(const Sphere& s) const 
	  {
		  const float dist = center.distance(s.center);
		  float res = dist - ( radius + s.radius );
		  return res;
	  }

	  //! \brief  Получить бокс построеный  внутри сферы.	ПРОВЕРЕНО
	  AABB toAabbInside() const;

	  //! \brief  Получить бокс построеный по краю сферы. ПРОВЕРЕНО
	  AABB toAabbOutside() const;		  
	

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


	ObjContainsE BSphereContainsBSphere(const Sphere& s) const
	{
	   const float d2 = (center - s.center).lengthSq(); 
	  
	  if (d2 < scalar::sqr( radius + s.radius))	   
	  {
			if ( d2 < scalar::sqr(radius-s.radius) )
			  return SC_CONTAINSFULLY;
			else
			  return SC_CONTAINSPARTIALLY;
	  } 
	  // else
	  //  return SC_NOOVERLAP;

	  return   SC_NOOVERLAP;
	};

	


	};
	// end class
	
	
	
	// много инфы по боксу   http://www.devmaster.net/forums/showthread.php?t=10324
		
	//! \brief Бокс по мин. и макс. координатам. Axis Aligned Bounding Box.
	class AABB {
	public:
	   vec3   min; ///< минимальная точка бокса
	   vec3   max; ///< максимальная точка бокса

	  //! углы бокса
	  struct corners {
		   vec3 points [8];

		  inline  vec3& operator [] (unsigned int index)
		  {
		    assert(index<8 && "invelid index");
			return points[index];
		  }

 		  inline  vec3 operator [] (unsigned int index)   const
		  {
		    assert(index<8 && "invelid index");
			return points[index];
		  }


	  };
	  
	  inline AABB() {}
	  inline AABB(const AABB& aabb) {min=aabb.min; max=aabb.max;}	  
	  inline AABB(const  vec3& _min, const  vec3& _max) { min=_min; max=_max;  }
	

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
	  inline AABB operator + (const  vec3& pnt) const	  
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
	  inline AABB& operator += (const  vec3& pnt)
	  {
		 includePoint(pnt);
		 return *this;	  
	  }
 
	  //! \brief  Построить по точкам  ПРОВЕРИТЬ
	  inline void make(const  vec3& p1, const  vec3& p2)
	  {
	     min = p1.minimized(p2);
	     max = p1.maximized(p2);
	  }
	  
	  //! \brief  Построить по точкам 
	  inline void make(float p1_x, float p1_y, float p1_z,
					   float p2_x, float p2_y, float p2_z)
	  {
		  make(  vec3(p1_x , p1_y , p1_z) ,  vec3(p2_x , p2_y , p2_z) );
	  }
 

	  //! \brief Извлечь углы бокса в cOut
	  inline void extractCorners(corners& cOut) const
	  {
		  cOut[0] =  vec3(  min.x,  min.y,  min.z );
		  cOut[1] =  vec3(  min.x,  min.y,  max.z );
		  cOut[2] =  vec3(  min.x,  max.y,  min.z );
		  cOut[3] =  vec3(  min.x,  max.y,  max.z );
		  cOut[4] =  vec3(  max.x,  min.y,  min.z );
		  cOut[5] =  vec3(  max.x,  min.y,  max.z );
		  cOut[6] =  vec3(  max.x,  max.y,  min.z );
		  cOut[7] =  vec3(  max.x,  max.y,  max.z );   
	  }
	  

	  //! \brief Получить центр бокса
	   vec3 center() const 
	  { 
	     vec3 res;
		  res.x = (max.x + min.x)/2.0f;
		  res.y = (max.y + min.y)/2.0f;		
		  res.z = (max.z + min.z)/2.0f;		
	    return res; 
	  }
	  
	  //! \brief  Включить координату pnt в бокс
	  AABB& includePoint(const  vec3& pnt) 
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
	   vec3 clumpCoord(const  vec3& coord) const
	  {
	      vec3 r = coord;
		 
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
	  


	  inline plane_s  plane_positive_x() const 
	  {
		  plane_s res = { 1.0f , 0.0f , 0.0f , max.x };
		  return res;
	  }


	  inline plane_s  plane_negative_x() const 
	  {
  		  plane_s res = { -1.0f , 0.0f , 0.0f ,  min.x };
		  return res;
	  } 


	  inline plane_s  plane_positive_y() const 
	  {
		  plane_s res = { 0.0f , 1.0f , 0.0f ,  max.y};
		  return res;
	  }


	  inline plane_s  plane_negative_y() const 
	  {
 		  plane_s res = { 0.0f , -1.0f , 0.0f ,  min.y};
		  return res;
	  } 


	  inline plane_s  plane_positive_z() const 
	  {
		  plane_s res = { 0.0f , 0.0f , 1.0f , max.z };
		  return res;
	  }


	  inline plane_s  plane_negative_z() const 
	  {
		  plane_s res = { 0.0f , 0.0f , -1.0f , min.z };
		  return res;
	  } 

 

//! \brief  Трансформировать по матрице m . Получить выровненые вершины.
AABB& transform(const  mat44& m)
{
   corners cr;
   extractCorners(cr);

   min.setzero();
   max.setzero();

   for(int c=0; c<8; c++)
   {
     cr[c].transformCoord(m);
	 *this += cr[c];
   }
 
  return *this;
}

 

	  //! \brief  Сдвинуть.
	  inline void offset(const  vec3& v)
	  {
		  min += v;
		  max += v;
	  }

	  //! \brief Объединить с боксом	  
	  inline AABB& includeAabb( const AABB& aabb)
	  {
		  if (aabb.min.x <   min.x)     min.x=aabb.min.x;
		  if (aabb.min.y <   min.y)     min.y=aabb.min.y;
		  if (aabb.min.z <   min.z)     min.z=aabb.min.z;

		  if (aabb.max.x >   max.x)     max.x=aabb.max.x;
		  if (aabb.max.y >   max.y)     max.y=aabb.max.y;
		  if (aabb.max.z >   max.z)     max.z=aabb.max.z; 

		  return *this;   
	  }

	  //! \brief  Преобразование в сферу. Край сферы по углам бокса.
	  Sphere toSphere() const
	  {
		  Sphere res;
		  res.center =  min.middle(max); 
		  res.radius =  min.distance(max) * 0.5f; 
		  return res;
	  }

	  //! \brief Проверка точки на нахождение в боксе.   ПРОВЕРЕНО!
	  inline bool checkContainPoint(const  vec3& p )
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
bool checkIntersectAABB_2(AABB& aabb) const
{
    return
        min.x > aabb.max.x || max.x < aabb.min.x ||
        min.y > aabb.max.y || max.y < aabb.min.y ||
        min.z > aabb.max.z || max.z < aabb.min.z;
}


 
 
//function AABBContainsAABB(const mainAABB, testAABB : TAABB) : TSpaceContains;

ObjContainsE checkContainsAabb( const AABB& box ) const
{
  if
   (( min.x<box.max.x) &&
    ( min.y<box.max.y) &&
    ( min.z<box.max.z) &&

    (box.min.x< max.x) &&
    (box.min.y< max.y) &&
    (box.min.z< max.z))  
  {
    if((box.min.x>= min.x) &&
      (box.min.y>= min.y) &&
      (box.min.z>= min.z) &&

      (box.max.x<= max.x) &&
      (box.max.y<= max.y) &&
      (box.max.z<= max.z) ) 
       return SC_CONTAINSFULLY;
    else
	{
      return SC_CONTAINSPARTIALLY;
	}; 
  }
  else
     return  SC_NOOVERLAP;


   return SC_NOOVERLAP;
};

 
ObjContainsE checkContainsSphere( const Sphere& s)  const 
{
    AABB b = s.toAabbOutside();
     return checkContainsAabb(b);
};
	 
	






	};
	// end class
		



	class OOBB  {
	public:

		OOBB(){}	
	
	
	};


	//! \brief   Линия в трёхмерном пространстве по двум точкам  
	class Line {
	public:
		 vec3   src; 
		 vec3   dest;

		inline Line() {};
		inline Line(const Line& l) {src=l.src; dest=l.dest; };	
		inline Line(const  vec3& _src, const  vec3& _dest) {src=_src; dest=_dest; };

		//! \brief Получить направление от src к dest
		inline  vec3 direction() const {  vec3 r (dest - src); r.normalize(); return r; }



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





	

	//! \brief Луч в 3-D по позиции и направлению   
	class Ray {
	public:
	    vec3   orig; ///< точка центр луча (позиция)
	    vec3   dir;  ///< направление луча. Должен быть нормализован.
	   
	   inline Ray() {}
	   inline Ray(const Ray& r) {orig=r.orig; dir=r.dir; }
	   
	   // возможно нужно убрать параметр bNeedNormalizeDir
	   inline Ray(const  vec3& _orig, const  vec3& _dir, bool bNeedNormalizeDir=true)
       {
	      orig=_orig;
	      dir=_dir;
	      if(bNeedNormalizeDir) 
			  dir.normalize();	   
	   }

	//! \brief  Трансформировать луч по матрице m
	inline void transform(const  mat44& m)
	{
	     orig.transformCoord(m);
	     dir.transformNormal(m);
	}
	
 

//>>>>>>>>>>>>>>>       checkIntersectSphere  >>>>>>>>>>>>>>>>>>>>>>>>>>>

//  http://netlib.narod.ru/library/book0032/ch15_04.htm
bool  checkIntersectSphere(const Sphere& sphere) const
{
	 vec3 v =  this->orig - sphere.center;

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
	 vec3 vect = orig - sphere.center ;

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

 // // в 10й студии нет xmath.h  Временное определение.
 // static const float INF = 1.0f/0.0f;

 // квадрат радиуса
  const float r =  (sph.radius * sph.radius);
  
  // квадрат расстояния от точки до центра сферы
   float d;
  {
	 //  assert(false);
	  // inline float distanceSq(const vec3& point) const { return vec3(*this-point).lenghtSq ;  }
	//  vec3 vs = sph.center-orig;
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
 
  res = s+sqrt(r-h)*fmath::scalar::sign(r-d); // расстояние до пересечения

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
	const  vec3 plNrml = plane.normal();
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

	const  vec3 vRayOrigin = orig;
	const  vec3 vnRayVector = dir;

	const   vec3& vnPlaneNormal = plane.normal();
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


   /*****************************
	// ! УБРАТЬ !!!
	class Plane : public plane_s {
	public:
		inline Plane() {};
		inline Plane(const Plane& p) {a=p.a; b=p.b; c=p.c; d=p.d; }

		inline Plane(float _a, float _b, float _c, float _d) { a=_a; b=_b; c=_c; d=_d; }

 
	};
	****************************/



	/**********************
	struct quat_s {


	};
	**************************/






	//! \brief Треугольник по трём точкам . 
	class Triangle {
	public:
		 vec3   p1; ///< первая точка(вершина) треугольника 
		 vec3   p2; ///< вторая точка(вершина) треугольника   
		 vec3   p3; ///< третья точка(вершина) треугольника 


		inline Triangle() {}
		inline Triangle(const Triangle& t) { *this = t; }
		inline Triangle(const  vec3 _p1, const  vec3 _p2, const  vec3 _p3) 
		{
			p1=_p1;	p2=_p2;	p3=_p3;	
		}

		inline void set(const  vec3 _p1, const  vec3 _p2, const  vec3 _p3) 
		{
			p1=_p1;	p2=_p2;	p3=_p3;	
		}

		/** \brief Вычислить и вернуть среднюю точку треугольника */
		inline  vec3 middlePoint() const 
		{ 
			 vec3 res;
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
			   plane_s  front;
			   plane_s  back;  
			   plane_s  left;   
			   plane_s  right;   
			   plane_s  top;
			   plane_s  bottom;  
		   };

		   plane_s  planes[6] ;
	   };

	   inline Frustum() {}
	   inline Frustum(const Frustum& f) { *this=f; }


	   /** \brief Выполнить построение из матричного произведения view * proj */
	   void make(const  mat44& mViewProj);	

	   /** \brief Выполнить построение из матриц   view и proj */
	   void make(const  mat44& mView, const  mat44& mProj) 
	   {
		    mat44 mViewProj = mView * mProj;
		   make(mViewProj);
	   }

       //! \brief Проверка попадания точки в пирамиду 
	   bool checkPoint(const  vec3& point) const; 

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
	    vec3  p1;  ///< Первая центральная координата в основании цилиндра.
	    vec3  p2;  ///< Вторая центральная координата в основании цилиндра.

	   float      radius; ///< Радиус цилиндра

	   Cilinder() {}
	   Cilinder(const Cilinder& c) { p1=c.p1; p2=c.p2; radius=c.radius;  }
	   Cilinder(const  vec3& _p1, const  vec3& _p2, float _radius) 
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
	    vec3     vScaling;     ///< масштабирование
	   Quaternion       qRotation;    ///< вращение
	    vec3     vTranslation; ///<  позиция



   };



    //---------------------------------------------------------------------
	//                    КОНСТАНТЫ
	//---------------------------------------------------------------------


// static const Quaternion QUATERNION_IDENTITY = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );





    } // end ns
  } // end ns fmath
} // end ns gb

// end file