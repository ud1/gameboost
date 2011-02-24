/** \file geom2d.h
 \brief ��������� � 2d.
*
*
* *  ���������� �� ������ ���������� �������� � ����� �����,   ����������� �������,   ��������� �� ����� , ����� ���������.
*
*/

#pragma once
#include <gb/math/scalar.h>
#include <gb/math/base.h>


namespace gb 
{

  namespace math
  {
  
    /** \brief  ��������� � 2d  */
    namespace geom2d
	{

        /** \brief 2-� ������ ������. */
		struct Size2d {

			union {
				float x;
				float width;	
			};

			union {
				float y;
				float height;
			};


		};

	


		/** \brief ����� ���������� � 2-� ������ ������������   */
		class Circle {
		public:
			base::vec2_s  center;
			float         radius;


			inline Circle() {}
			inline Circle(const Circle& c) {center=c.center; radius=c.radius; };
			inline Circle(const base::vec2_s & _center, const float _radius) { center=_center; radius=_radius; }





		};


	


		/** \brief ��� � 2d  �� �������  (�������� �����)  �  �����������  */
		class Ray {
		public:
			base::vec2_s   orig; ///< ����� ����� ����
			base::vec2_s   dir;  ///< ����������� ���� ( ������ ���� ������������)

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