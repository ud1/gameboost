﻿/** \file geom2d.h
 \brief геометрия в 2d.
*
*
* *  Наполнение на основе выложеного ребятами в папку бранч,   опенсурсных движков,   выуженого из гугла , своих наработок.
*
*/

#pragma once
#include <gb/math/scalar.h>
#include <gb/math/base.h>


namespace gb 
{

  namespace math
  {
  
    /** \brief  геометрия в 2d  */
    namespace geom2d
	{

        /** \brief 2-х мерный размер. */
		struct Size2d {

			union {
				float x;
				float width;	
			};

			union {
				float y;
				float height;
			};

			inline operator base::vec2_s () const { base::vec2_s r(x,y); return r;  };


		};

		//! Прямоугольник по мин. и макс координате
		class Rect {
		public:
			float x1, y1;
			float x2, y2;

			inline Rect() {}
			inline Rect(const Rect& r) {x1=r.x1; y1=r.y1;  x2=r.x2; y2=r.y2; }


			inline void translate(int x, int y)
			{
			x1+=x;
			y1+=y;
			x2+=x;
			y2+=y;
			}
		
		
		};

	


		/** \brief Класс окружность в 2-х мерном пространстве   */
		class Circle {
		public:
			base::vec2_s  center;
			float         radius;


			inline Circle() {}
			inline Circle(const Circle& c) {center=c.center; radius=c.radius; };
			inline Circle(const base::vec2_s & _center, const float _radius) { center=_center; radius=_radius; }





		};


		//! Линия в 2d по двум точкам
		class Line {
		public:
			base::vec2_s   src;
			base::vec2_s   dest;


			inline Line() {}
		};


	


		/** \brief Луч в 2d  по позиции  (исходной точке)  и  направлению  */
		class Ray {
		public:
			base::vec2_s   orig; ///< точка центр луча
			base::vec2_s   dir;  ///< направление луча ( должен быть нормализован)

			inline Ray() {}
			inline Ray(const Ray& r) {orig=r.orig; dir=r.dir; }
			inline Ray(const base::vec2_s& _orig, const base::vec2_s& _dir, bool bNeedNormalizeDir)
			{
				orig=_orig;
				dir=_dir;
				if(bNeedNormalizeDir) dir.normalize();	   
			}




		};

	
    } // end ns
  } // end ns
} // end ns

// end file	