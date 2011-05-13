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

 
 //  __GB_TYPES_H__
//#include <gb/base/Types.h>

#ifndef __GB_FMATH_H__
    #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif





namespace gb 
{

  namespace fmath
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

			inline operator  vec2_s () const {  vec2_s r(x,y); return r;  };


		};


  

//! \brief  Нормаль, направление в двухмерном измерении /xx
class Normal2 {
private:
   float _x;
   float _y;
   
  inline void __normalize() 
  { 
	  float fm = sqrt(_x*_x+_y*_y); 
	  _x/=fm; 
	  _y/=fm;  
  }

public:
	// по дефолту нормаль смотрит по Y 
	Normal2() { _x=0.0f; _y=1.0f;  }
	Normal2(const Normal2& n) {  _x=n._x;   _y=n._y; }
	
	//! \brief Передавать правильные значения для нормали. Нельзя оба в ноль и т.д.
	Normal2(float x, float y)  
	{ 
		if( (0.0f==_x) && (0.0f==_y) )  throw std::runtime_error("invalid arg");
		_x=x; _y=y; __normalize(); 
	}

	Normal2(const  vec2_s& vn) { *this = vn; }
 

	inline float x() const { return _x; }
	inline float y() const { return _y; }


	inline void operator = ( vec2_s& v) {_x=v.x; _y=v.y; __normalize(); }
	inline void inverse() {_x=-_x; _y=-_y; }
	
	// setDirBetweenPoints(const Point2& src, const Point2& dest)
    // void transform(const  mat44_s& m) {....}
	// Normal2 cross(){...}
	// inline float angle(const Normal& n) const {...}
	
	// rotate (const mat22_s& m) {...}
	
	
	
	
}; 





//! \brief   Позиция, точка в двухмерном измерении  ВОЗМОЖНО УДАЛИТЬ
class Point2 {
public:
   float _x;
   float _y;
   
   Point2() { _x=0.0f; _y=0.0f; }
   Point2(const Point2& p) {_x=p._x ; _y=p._y ; }
   Point2(const float x, const float y) { _x=x;  _y=y; }
   
   inline operator const float* () const { return &_x; }

   inline void operator = (const  vec2_s& v) { _x=v.x; _y=v.y; }

#ifdef __GB_TYPES_H__
   inline void operator = (const POINT& p) { _x=(float)p.x; _y=(float)p.y; }
#endif 
 
   // void moveAlongNormal(const Normal2& normal, float distance) {....}
   // void transform(const  mat22_s& m) {....}


   /**************

   Point3 from3dSpace(const VP& vp, const mat44_s& mwvp) {...}




   ****************/


}; 








		//! Прямоугольник по мин. и макс координате
		class Rect {
		public:
			float x1; ///< кооордината x  верхнего левого угла . 
			float y1; ///< координата  y  верхнего левого угла .

			float x2; ///< кооордината x  нижнего правого  угла . 
			float y2; ///< координата  y  нижнего правого  угла .


			//! \brief Углы прямоугольника
			struct Corners {
				 vec2_s points[4];
			};
 

			inline Rect() {}
			inline Rect(const Rect& r) {x1=r.x1; y1=r.y1;  x2=r.x2; y2=r.y2; }
			inline Rect(float _x1, float _y1, float _x2, float _y2) { x1=_x1; y1=_y1; x2=_x2; y2=_y2; }

#ifdef __GB_TYPES_H__	
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




#ifdef __GB_TYPES_H__	

			inline void set(const POINT& np1, const POINT& np2) { x1=(float)np1.x; y1=(float)np1.y; x2=(float)np2.x; y2=(float)np2.y; };
			inline void operator = (const RECT& rec) 
			{
				x1 = (float)rec.left;
				y1 = (float)rec.top;
				x2 = (float)rec.right;
				y2 = (float)rec.bottom;    
			};


			inline operator RECT () const 
			{
				RECT res;
				res.left   = (long)x1;
				res.top    = (long)y1;
				res.right  = (long)x2;
				res.bottom = (long)y2;
				return res; 
			};  

#endif // #ifdef __GB_TYPES_H__

			//! \brief Занулить 
			inline void setzero() { x1=y1=x2=y2=0.0; }
			//! \brief  проверка всех компонентов на ноль
			inline bool empty() const { return ( (x1==0.0f) && (y1==0.0f) && (x2==0.0f) && (y2==0.0f) ); }

			//! \brief Сдвиг координат. Движение прямоугольника
			inline void translate(float x, float y)	{ x1+=x; y1+=y;	x2+=x;	y2+=y; }

			//! \brief Сдвиг координат. Движение прямоугольника на значение val
			inline void translate(const  vec2_s& val) { x1+=val.x; y1+=val.y;	x2+=val.x; y2+=val.y; }

#ifdef __GB_TYPES_H__  

			/** \brief Движение координат на указаное значение */
			inline void translate(const POINT& p) {  translate( (float)p.x, (float)p.y );   }

#endif // #ifdef __GB_TYPES_H__ 


			//! \brief Получение ширины прямоугольника  
			inline float getWidth()  const { return (x2-x1); };

			//! \brief Получение высоты прямоуголника   
			inline float getHeight() const { return (y2-y1); }; 

			//! \brief Получить/установить первичную координату прямоугольника
			inline  vec2_s  minCoord() const {  vec2_s res; res.x=x1; res.y=y1; return res; }
			inline void          minCoord( vec2_s& coord)       
			{ 
				x1=coord.x;
				y1=coord.y;
			}
		
			//! \brief Получить/установить Вторичную координату прямоугольника
			inline  vec2_s maxCoord() const {  vec2_s res; res.x=x2; res.y=y2; return res; }
			inline void         maxCoord( vec2_s& coord)       
			{ 
				x2=coord.x;
				y2=coord.y;
			}

			// TODO void move(const Normal2& normal, float distance) { }

			//! \brief  Извлечь все 4 вершины прямоугольника.
			void extractCorners(Corners& _out) 
			{
				_out.points[0] =  vec2_s(x1, y1);
				_out.points[2] =  vec2_s(x2, y1);
				_out.points[3] =  vec2_s(x2, y2);
				_out.points[4] =  vec2_s(x1, y2);
			}


		
			/** \brief Установить новую позицию по верхнему левому краю прямоугольника. 
			      Размеры сохраняются. */
			inline void setPositionTopLeft(float x, float y) 
			{   
				float w=getWidth();  
				float h=getHeight();  
				x1=x; y1=y; 
				x2=x1+w; y2=y+h;  
			}

			inline void setPositionTopLeft(const  vec2_s& v) { setPositionTopLeft(v.x,v.y); }  

#ifdef __GB_TYPES_H__ 
			/** \brief Установить новую позицию по верхнему левому краю прямоугольника. 
			        Размеры сохраняются. */
			inline void setPositionTopLeft(const POINT& pnt) {  setPositionTopLeft((float)pnt.x, (float)pnt.y);   };

			/** \brief Получить точку координату верхнего левого угла прямоугольника. */
			inline POINT getPositionTopLeft() const { POINT res; res.x=(long)x1; res.y=(long)y1; return res; };

#endif 


  
  /** \brief Установить новую ширину. Координата левого вернего угла не меняется. */
  inline void setWidth(float fWidth)   { x2 = x1 + fWidth;  }
  /** \brief Установить новую высоту. Координата левого вернего угла не меняется. */
  inline void setHeight(float fHeight) { y2 = y1 + fHeight; }
  /** \brief Установить новую ширину и высоту. Координата левого вернего угла не меняется. */
  inline void setWidthHeight(float fWidth, float fHeight) 
  {
   x2 = x1 + fWidth;
   y2 = y1 + fHeight;
  }


//  /** \brief Получить  координату верхнего левого угла прямоугольника. */
//  inline POINT getTopLeft() const {  POINT res; res.x=(long)x1; res.y=(long)y1; return res; };
//  /** \brief Получить  координату нижнег оправого угла прямоугольника. */
//  inline POINT getBottomRight() const {  POINT res; res.x=(long)x2; res.y=(long)y2; return res; };


  //! \brief Получить  координату верхнего левого угла прямоугольника.
  inline  vec2_s getTopLeft() const {   vec2_s res; res.x=x1; res.y=y1; return res; }
  //! \brief Получить  координату нижнег оправого угла прямоугольника. 
  inline  vec2_s getBottomRight() const {   vec2_s res; res.x=x2; res.y=y2; return res; }



  /** \brief Получить центральную среднюю точку прямоугольника */
  inline  vec2_s getCenterPoint() const 
  {
	   vec2_s res;
	   vec2_s pTpLft = getTopLeft();
	   vec2_s pBtRt  = getBottomRight();

	  res.x = (pTpLft.x + pBtRt.x) / 2.0f;
	  res.y = (pTpLft.y + pBtRt.y) / 2.0f;

	  return res; 
  }

  /** \brief  Установить координаты прямоугольника по средней точке. Размеры не меняются.  */
  inline void  setCenterPoint(const  vec2_s& pnt) 
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

#if ( defined(_WINDEF_) || defined(__GB_TYPES_H__) )

  /** \brief Отсечение координат точки p в пределах прямоугольника */
  inline void clumpCoord(   POINT& pntTobeClump ) const 
  {
	  if( (float)pntTobeClump.x < x1 ) { pntTobeClump.x = (long)x1; };
	  if( (float)pntTobeClump.x > x2 ) { pntTobeClump.x = (long)x2; };
	  if( (float)pntTobeClump.y < y1 ) { pntTobeClump.y = (long)y1; };
	  if( (float)pntTobeClump.y > y2 ) { pntTobeClump.y = (long)y2; };
  }

#endif

  /** \brief Отсечение координат точки p в пределах прямоугольника */
  inline void clumpCoord(   vec2_s& pntTobeClump ) const 
  {
	  if( pntTobeClump.x < x1 ) { pntTobeClump.x = x1; };
	  if( pntTobeClump.x > x2 ) { pntTobeClump.x = x2; };
	  if( pntTobeClump.y < y1 ) { pntTobeClump.y = y1; };
	  if( pntTobeClump.y > y2 ) { pntTobeClump.y = y2; };
  }



  //! \brief Проверка попадания точки в прямоугольник . 
  inline bool checkContainPoint(int x, int y) const 
  {
	  if( (x>x1) && (y>y1) && (x<x2) && (y<y2)  ) return true;
	  return false;
  }

#if ( defined(_WINDEF_) || defined(__GB_TYPES_H__) )
  //! \brief Проверка попадания точки в прямоугольник .
  inline bool checkContainPoint(const POINT& pnt) const { return checkContainPoint(pnt.x, pnt.y); }
#endif

  //!   \brief Вычислить площадь.
  inline float computeSquare() { return ( getWidth() * getHeight()  );  };

 

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

 


#ifdef _D3D9_H_

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


#endif   // #ifdef _D3D9_H_







          //! \brief печать на консоль 
          void print() const {   printf("%f  %f     %f  %f", x1, y1,   x2, y2);    };

		};

	


		/** \brief Класс окружность в 2-х мерном пространстве   */
		class Circle {
		public:
			 vec2_s  center;
			float         radius;


			inline Circle() {}
			inline Circle(const Circle& c) {center=c.center; radius=c.radius; };
			inline Circle(const  vec2_s & _center, const float _radius) { center=_center; radius=_radius; }
			inline Circle(float _centerx, float _centery,  float _radius)    { center.x=_centerx; center.y=_centery;   radius=_radius; }
			
			inline void set(int iCenterX, int iCenterY, int iRadius) { center.x=(float)iCenterY; center.y=(float)iCenterY; radius=(float)iRadius;	}
			inline void set(const  vec2_s& vCenter, float fRadius)    { center=vCenter; radius=fRadius; }
			inline void set(float _centerx, float _centery,  float _radius)    { center.x=_centerx; center.y=_centery;   radius=_radius; }


			//! \brief Проверка пересечения окружностей overlap
			bool checkIntersect(const Circle& c) 
			{
				float fDist;
				{  vec2_s t(center - c.center); fDist = t.length();  }
				if (fDist >= (radius + c.radius))	return false;
				return true;
			}
			
			
			
			// bool checkIntersectContactPoints(vec2_s& outp1, vec2_s& outp2, const Circle& c) {...}
			// http://algolist.manual.ru/maths/geom/intersect/circlecircle2d.php
			
			
			/*
			bool checkIntersectCircleContactPnt(const Circle& c, vec3_s& pc1, vec3_s& pc2) const {...}
			*/

			//! \brief Проверка попадания точки   point
			inline bool checkContainPoint(const  vec2_s point) 
			{
				float fDist;
				{  vec2_s t(center - point); fDist = t.length();  }
				if( fDist > radius ) 
					return false; 
				return true;
			}

			// bool checkIntersectCircle(const Circle& c) const {...}
			// bool checkIntersectRect(const Rect& r) const {...}
			
			// 3d::Sphere toObjectSphere(VP& vp, )



			// fromCstr(const char* s) {..}
			// toCstr(char* buf) const	  {....}


		};


		//! Линия в 2d по двум точкам
		class Line2d {
		public:
			 vec2_s   src;
			 vec2_s   dest;


			inline Line2d() {}
			inline Line2d(const Line2d& l) {src=l.src;  dest=l.dest; }
			inline Line2d(const  vec2_s& _src, const  vec2_s& _dest)
			{
			   src=_src;
			   dest=_dest;
			}
			
			Normal2 direction() const 
			{
			    Normal2 res = (dest - src);
			    return res;	
			}
			

			inline void set(const  vec2_s& _src,  vec2_s& _dest)
			{
			 src  = _src;
			 dest = _dest;
			}
			
			
			// vec2_s projectPoint(const vec2_s& pnt) const 
			
			// checkIntersect......
			
			
			
			
		};


	


		/** \brief Луч в 2d  по позиции  (исходной точке)  и  направлению  */
		class Ray2d {
		public:
			 vec2_s   orig; ///< точка центр луча
			 vec2_s   dir;  ///< направление луча ( должен быть нормализован)

			inline Ray2d() {}
			inline Ray2d(const Ray2d& r) {orig=r.orig; dir=r.dir; }
			inline Ray2d(const  vec2_s& _orig, const  vec2_s& _dir, bool bNeedNormalizeDir)
			{
				orig=_orig;
				dir=_dir;
				if(bNeedNormalizeDir) dir.normalize();	   
			}


			// bool checkIntersectCircle(const CIrcle& c)
			// bool checkIntersectRect(const Rect& r)
			// bool checkIntersectRectContactPnts(const Rect& r)			
			// bool checkIntersectLine


		};

	
    } // end ns
  } // end ns
} // end ns

// end file	