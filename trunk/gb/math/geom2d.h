/** \file geom2d.h
 \brief геометрия в 2d.
*
*
* 
*  Наполнение на основе выложеного ребятами в папку бранч,  
*		опенсурсных движков,   выуженого из гугла , своих наработок.


 \todo Написать для circle построение внутреннего и внешнего прямоуголника.
*
*/

#pragma once


#include <gb/math/scalar.h>
#include <gb/math/base.h>

#include <gb/base/Types.h>



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
			float x1; ///< кооордината x  верхнего левого угла . 
			float y1; ///< координата  y  верхнего левого угла .

			float x2; ///< кооордината x  нижнего правого  угла . 
			float y2; ///< координата  y  нижнего правого  угла .
 

			inline Rect() {}
			inline Rect(const Rect& r) {x1=r.x1; y1=r.y1;  x2=r.x2; y2=r.y2; }
			inline Rect(float _x1, float _y1, float _x2, float _y2) { x1=_x1; y1=_y1; x2=_x2; y2=_y2; }

#ifdef WIN32	
			Rect(const POINT p1, const POINT p2)  
			{ 
				x1=(float)p1.x;  
				y1=(float)p1.y;  
				x2=(float)p2.x;  
				y2=(float)p2.y;  
			}
			Rect(const RECT& rec) {  *this = rec; }
#endif 


			inline void set(int nx1, int ny1, int nx2, int ny2)         { x1=(float)nx1;   y1=(float)ny1;   x2=(float)nx2;   y2=(float)ny2; }
			inline void set(float _x1, float _y1, float _x2, float _y2) { x1=_x1; y1=_y1; x2=_x2; y2=_y2; }




//#ifdef WIN32	  
			inline void set(POINT np1, POINT np2) { x1=(float)np1.x; y1=(float)np1.y; x2=(float)np2.x; y2=(float)np2.y; };
			inline void operator = (const RECT& rec) 
			{
				x1 = (float)rec.left;
				y1 = (float)rec.top;
				x2 = (float)rec.right;
				y2 = (float)rec.bottom;    
			};

			inline operator RECT () const {
				RECT res;
				res.left   = (long)x1;
				res.top    = (long)y1;
				res.right  = (long)x2;
				res.bottom = (long)y2;
				return res; 
			};  

//#endif 

			//! \brief Занулить 
			inline void setzero() { x1=y1=x2=y2=0.0; }
			//! \brief  проверка всех компонентов на ноль
			inline bool empty() const { return ( (x1==0.0f) && (y1==0.0f) && (x2==0.0f) && (y2==0.0f) ); }

			//! \brief Сдвиг координат. Движение прямоугольника
			inline void translate(float x, float y)	{ x1+=x; y1+=y;	x2+=x;	y2+=y; }

			//! \brief Сдвиг координат. Движение прямоугольника на значение val
			inline void translate(const base::vec2_s& val) { x1+=val.x; y1+=val.y;	x2+=val.x; y2+=val.y; }

//#ifdef WIN32  
			/** \brief Движение координат на указаное значение */
			inline void translate(const POINT& p) {  translate((float)p.x, (float)p.y);   };
//#endif


			//! \brief Получение ширины прямоугольника  
			inline float getWidth()  const { return (x2-x1); };

			//! \brief Получение высоты прямоуголника   
			inline float getHeight() const { return (y2-y1); }; 
		
		
			/** \brief Установить новую позицию по верхнему левому краю прямоугольника. 
			      Размеры сохраняются. */
			inline void setPositionTopLeft(float x, float y) 
			{   
				float w=getWidth();  
				float h=getHeight();  
				x1=x; y1=y; 
				x2=x1+w; y2=y+h;  
			}

			inline void setPositionTopLeft(const base::vec2_s& v) { setPositionTopLeft(v.x,v.y); }  

//#ifdef WIN32
			/** \brief Установить новую позицию по верхнему левому краю прямоугольника. 
			        Размеры сохраняются. */
			inline void setPositionTopLeft(const POINT& pnt) {  setPositionTopLeft((float)pnt.x, (float)pnt.y);   };

			/** \brief Получить точку координату верхнего левого угла прямоугольника. */
			inline POINT getPositionTopLeft() const { POINT res; res.x=(long)x1; res.y=(long)y1; return res; };
//#endif


  
  /** \brief Установить новую ширину. Координата левого вернего угла не меняется. */
  inline void setWidth(float fWidth)   { x2 = x1 + fWidth;  }
  /** \brief Установить новую высоту. Координата левого вернего угла не меняется. */
  inline void setHeight(float fHeight) { y2 = y1 + fHeight; }
  /** \brief Установить новую ширину и высоту. Координата левого вернего угла не меняется. */
  inline void setWidthHeight(float fWidth, float fHeight) {
   x2 = x1 + fWidth;
   y2 = y1 + fHeight;
  }


  /** \brief Получить  координату верхнего левого угла прямоугольника. */
  inline POINT getTopLeft() const {  POINT res; res.x=(long)x1; res.y=(long)y1; return res; };
  /** \brief Получить  координату нижнег оправого угла прямоугольника. */
  inline POINT getBottomRight() const {  POINT res; res.x=(long)x2; res.y=(long)y2; return res; };



  /** \brief Получить центральную среднюю точку прямоугольника */
  inline POINT getCenterPoint() const 
  {
	  POINT res;
	  POINT pTpLft = getTopLeft();
	  POINT pBtRt  = getBottomRight();

	  res.x = (pTpLft.x + pBtRt.x) / 2;
	  res.y = (pTpLft.y + pBtRt.y) / 2;

	  return res; 
  };

  /** \brief  Установить координаты прямоугольника по средней точке. Размеры не меняются.  */
  inline void  setCenterPoint(const POINT& pnt) 
  {
	  float nw = getWidth();
	  float nh = getHeight();

	  //setPositionTopLeft( pnt.x - nw/2 , pnt.y - nh/2); 
	  //float w=getWidth();  
	  //float h=getHeight();

	  x1=(float)pnt.x - nw/2.0f; 
	  y1=(float)pnt.y - nh/2.0f; 

	  x2=x1 + nw; 
	  y2=y1 + nh; 
  };


  /** \brief Отсечение координат точки p в пределах прямоугольника */
  inline void clumpCoord(   POINT& pntTobeClump ) const 
  {
	  if( (float)pntTobeClump.x < x1 ) { pntTobeClump.x = (long)x1; };
	  if( (float)pntTobeClump.x > x2 ) { pntTobeClump.x = (long)x2; };
	  if( (float)pntTobeClump.y < y1 ) { pntTobeClump.y = (long)y1; };
	  if( (float)pntTobeClump.y > y2 ) { pntTobeClump.y = (long)y2; };
  }

  /** \brief Отсечение координат точки p в пределах прямоугольника */
  inline void clumpCoord(  base::vec2_s& pntTobeClump ) const 
  {
	  if( pntTobeClump.x < x1 ) { pntTobeClump.x = x1; };
	  if( pntTobeClump.x > x2 ) { pntTobeClump.x = x2; };
	  if( pntTobeClump.y < y1 ) { pntTobeClump.y = y1; };
	  if( pntTobeClump.y > y2 ) { pntTobeClump.y = y2; };
  }



  //! \brief Проверка попадания точки в прямоугольник . 
  inline bool checkContainPoint(int x, int y) const {
	  if( (x>x1) && (y>y1) && (x<x2) && (y<y2)  ) return true;
	  return false;
  }

  //! \brief Проверка попадания точки в прямоугольник .
  inline bool checkContainPoint(const POINT& pnt) const { return checkContainPoint(pnt.x, pnt.y); }


  //!   \brief Вычислить площадь.
  inline float computeSquare() { return ( getWidth() * getHeight()  );  };

#pragma warning (push)
#pragma warning (disable : 4996)


  /** \brief  В виде в строку разделёную пробелами  */
  void  toCstr(char* buf) const 
  {
	  *buf = '\0';
	  sprintf(buf, "%i %i    %i  %i",  x1, y1, x2, y2  );   
  };

  /** \brief Прочитать значения из строки разделёной пробелами */
  bool fromCstr(const char* s) 
  {
	  const int n = sscanf(s, "%i %i %i %i",   x1, y1, x2, y2   ); 
	  if(n!=4) return false;
	  return true;
  };

#pragma warning (pop)





#ifdef GB_D3D9

  void operator = (const D3DRECT&  rc) { x1=(float)rc.x1; y1=(float)rc.y1; x2=(float)rc.x2; y2=(float)rc.y2; }

  /** \brief Получить  в виде  D3DRECT */
  inline operator D3DRECT() const { D3DRECT r; r.x1=(LONG)x1; r.y1=(LONG)y1; r.x2=(LONG)x2; r.y2=(LONG)y2;  return r; }

  /** \brief Получить  в виде указателя  D3DRECT */
  inline operator const D3DRECT* ()  const {  return (D3DRECT*)&x1;  }

  /** \brief  Установить из вьпорта d3d9 устройства */
  inline void operator =  ( const D3DVIEWPORT9& vp ) 
  {
	  x1 = (float)vp.X;
	  y1 = (float)vp.Y;
	  x2 = x1 + (float)vp.Width;
	  y2 = y1 + (float)vp.Height;
  }

  //*  \brief Присвоить вьюпорту vpInOut  размеры и позицию прямоугольника.
  void to_viewport(D3DVIEWPORT9& vpInOut) const
  {
    vpInOut.X = (DWORD)x1;
	vpInOut.Y = (DWORD)y1;
	vpInOut.Width = (DWORD)getWidth();
	vpInOut.Height = (DWORD)getHeight();
  }


#endif   // #ifdef GB_D3D9







  /** \brief печать на консоль  */
  void print() const {   printf("%f  %f     %f  %f", x1, y1,   x2, y2);    };

		};

	


		/** \brief Класс окружность в 2-х мерном пространстве   */
		class Circle {
		public:
			base::vec2_s  center;
			float         radius;


			inline Circle() {}
			inline Circle(const Circle& c) {center=c.center; radius=c.radius; };
			inline Circle(const base::vec2_s & _center, const float _radius) { center=_center; radius=_radius; }

			inline void set(int iCenterX, int iCenterY, int iRadius) { center.x=(float)iCenterY; center.y=(float)iCenterY; radius=(float)iRadius;	}
			inline void set(const base::vec2_s& vCenter, float fRadius)    { center=vCenter; radius=fRadius; }
			inline void set(float fcx, float fcy,  float fRadius)    { center.x=fcx; center.y=fcy;   radius=fRadius; }


			//! \brief Проверка пересечения окружностей
			bool checkIntersect(const Circle& c) 
			{
				float fDist;
				{ base::vec2_s t(center - c.center); fDist = t.length();  }
				if (fDist >= (radius + c.radius))	return false;
				return true;
			}

			//! \brief Проверка попадания точки   point
			inline bool checkContainPoint(const base::vec2_s point) 
			{
				float fDist;
				{ base::vec2_s t(center - point); fDist = t.length();  }
				if( fDist > radius ) 
					return false; 
				return true;
			}


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