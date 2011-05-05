/** \file
 \brief Прямоугольник


*/

#pragma once
#define __GB__BASE__RECTANGLE_H__ 

#include <gb/Config.h>
#include <gb/base/Types.h>
#include <gb/base/Point.h>

namespace gb
{
	namespace base
	{
		
		//! \brief Прямоугольник
		struct Rectangle
		{
			int left; //< позиция по X.
			int top;  //< позиция по Y.
			int width;  //< ширина.
			int height; //< высота.

			Rectangle(){}
			
			Rectangle(int w, int h)
			{
				width = w;
				height = h;

				top = left = 0;
			}

			Rectangle(const Rectangle &other)
			{
				init(other);
			}

			Rectangle(const RECT& r)
			{
				*this = r;
			}

			Rectangle &operator = (const Rectangle &other)
			{
				init(other);
				return *this;
			}

			void init(int x, int y, int w, int h)
			{
				left = x; 
				top  = y;
				width  = w;
				height = h;
			}

			void init(const Rectangle &rc)
			{
				*this = rc;
			}

			bool operator < (const Rectangle &other) const
			{
				if (width < other.width)
					return true;
				if (width > other.width)
					return false;
				return height < other.height;
			}

			inline void operator = (const RECT& r)
			{
				left = r.left;
				top  = r.top;
				width  = r.right - r.left;
				height = r.bottom - r.top;
			}

			inline operator RECT() const 
			{
				RECT r;
				r.top = top;
				r.left = left;
				r.bottom = top + height;
				r.right  = left + width;
				return r;
			}

			// \brief Проверка нахождения точки в прямоугольнике. 
			inline bool checkPoint(int x, int y) const 
			{
			  if( (x>left) && (x<left+width) && (y>top) && (y<top+height) ) return true;
			  return false;			
			}

			inline bool checkPoint(const Point& p) 
			{
				return checkPoint( p.x , p.y );
			}

			inline bool checkPoint(const POINT& p) 
			{
				return checkPoint( p.x , p.y );
			}

			inline void offset(int x, int y)
			{
				left += x;
				top  += y;
			}

			inline void offset(const POINT& p)
			{
				left  += p.x;
				top   += p.y;
			}

			//! \brief offset coord.
			inline void operator += (const POINT& p)
			{
				offset (p);
			}

			//! \brief offset coord.
			inline void operator += (const Point& p)
			{
				offset (p);
			}

			//! \brief  Получить центральную координату.
			inline POINT center() const 
			{
				POINT res = { (left+width)/2 , (top+height)/2 };
				return res;
			}



		};
		
	}
}
