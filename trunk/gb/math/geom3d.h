/** \file geom3d.h
 \brief геометрия в 3d.
*
*  Наполнение на основе выложеного ребятами в папку бранч,   опенсурсных движков,   выуженого из гугла , своих наработок.
*
*
*/

#pragma once
#include <gb/math/scalar.h>
#include <gb/math/base.h>


namespace gb 
{

  namespace math
  {
  
    /** \brief  геометрия в 3d  */
    namespace geom3d
	{

	
	
	
	//! \brief Сфера по центральной точке и радиусу. Она же Bounding sphere.
	class Sphere {
	public:
	  base::vec3_s  center;  ///<  центральная координата сферы.
	  float   radius;  ///<  радиус сферы.
	  
	  inline Sphere() {}
	  inline Sphere(const Sphere& s) {center=s.center; radius=s.radius; }
	  inline Sphere(const base::vec3_s& _center, const float _radius) {center=_center; radius=_radius; }	  
	  
	
	
	
	};
	
	
	//! \brief Бокс по мин. и макс. координатам. Axis aligned bounding box.
	class AABB {
	public:
	  base::vec3_s   min; ///< минимальная точка бокса
	  base::vec3_s   max; ///< максимальная точка бокса
	  
	  inline AABB() {}
	  inline AABB(const AABB& aabb) {min=aabb.min; max=aabb.max;}	  
	  inline AABB(const base::vec3_s& _min, const base::vec3_s& _max) { min=_min; max=_max;  }
	
	
	
	};
	
	
	//! \brief Луч в трёхмерном пространстве по позиции и направлению   
	class Ray {
	public:
	   base::vec3_s   orig; ///< точка центр луча
	   base::vec3_s   dir;  ///< направление луча ( должен быть нормализован)
	   
	   inline Ray() {}
	   inline Ray(const Ray& r) {orig=r.orig; dir=r.dir; }
	   inline Ray(const base::vec3_s& _orig, const base::vec3_s& _dir, bool bNeedNormalizeDir)
       {
	    orig=_orig;
	    dir=_dir;
	    if(bNeedNormalizeDir) dir.normalize();	   
	   }	   
	
	
	//! вывод на консоль.
    inline void print() const { orig.print(); printf("  "); dir.print(); printf("  "); };
	
	};
 

	/** \brief   Линия в трёхмерном пространстве по двум точкам  */
	class Line {
	public:
		base::vec3_s   src; 
		base::vec3_s   dest;

		inline Line() {};
		inline Line(const Line& l) {src=l.src; dest=l.dest; };	
		inline Line(const base::vec3_s& _src, const base::vec3_s& _dest) {src=_src; dest=_dest; };



      #ifdef GB_OPENGL
		//! \brief Вывод вершин для OpenGl по старинке.
		inline void glVertex() { glVertex3f(src.x, src.y, src.z); glVertex3f(dest.x, dest.y, dest.z);   };
      #endif


		//! вывод на консоль.
		inline void print() const { src.print(); printf("  "); dest.print(); printf("  "); };

	}; // Line






    } // end ns
  } // end ns
} // end ns

// end file