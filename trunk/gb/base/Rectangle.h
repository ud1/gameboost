/** \file
 \brief Прямоугольник


*/

#pragma once
#define __GB__BASE__RECTANGLE_H__ 

#include "../Config.h"
#include "Types.h"

#include <ostream>
#include <sstream>
#include <string>

namespace gb
{
	namespace base
	{
		
		//! \brief Прямоугольник
		// Эта структура превратилась в кучу дерьма
		struct Rectangle
		{
			int left; //< позиция по X.
			int top;  //< позиция по Y.
			int width;  //< ширина.
			int height; //< высота.

			Rectangle() 
			{
				left = top = width = height = 0;
			}
			
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

			Rectangle(int x, int y, int w, int h)
			{
				void init(int x, int y, int w, int h);
			}

#ifdef _WINDOWS_
			Rectangle(const RECT& r)
			{
				*this = r;
			}
#endif

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
				init(rc.left, rc.top, rc.width, rc.height);
			}

			void set_zero()
			{
				left = top = width = height = 0;
			}

			bool operator < (const Rectangle &other) const
			{
				if (width < other.width)
					return true;
				if (width > other.width)
					return false;
				return height < other.height;
			}

#ifdef _WINDOWS_
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
#endif

			// \brief Проверка нахождения точки в прямоугольнике.  // old name: checkPoint
			inline bool check_point(int x, int y) const 
			{
			  if( (x>left) && (x<left+width) && (y>top) && (y<top+height) ) return true;
			  return false;			
			}

			inline void offset(int x, int y)
			{
				left += x;
				top  += y;
			}

#ifdef _WINDOWS_
			inline void offset(const POINT& p)
			{
				left  += p.x;
				top   += p.y;
			}
#endif

#ifdef _WINDOWS_
			//! \brief offset coord.
			inline void operator += (const POINT& p)
			{
				offset (p);
			}

 #endif

			friend std::ostream& operator << (std::ostream& os, const Rectangle& r)
			{
				os << r.left << " " << r.top << " " << r.width << " " << r.height; 
				return os;
			}


			operator std::string() const 
			{
				std::ostringstream ss;
				ss << left << " " << top << " " << width << " " << height; 
				return ss.str();
			}

		};
		
	}
}
