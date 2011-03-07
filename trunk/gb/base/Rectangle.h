#pragma once
#include <boost/concept_check.hpp>

namespace gb
{
	namespace base
	{
		
		struct Rectangle
		{
			int left, top;
			int width, height;

			Rectangle(){}
			
			Rectangle(int w, int h)
			{
				width = w;
				height = h;
			}

			Rectangle(const Rectangle &other)
			{
				init(other);
			}

			Rectangle &operator = (const Rectangle &other)
			{
				init(other);
				return *this;
			}

			void init(int x, int y, int w, int h)
			{
				left = x; 
				top = y;
				width = w;
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
		};
		
	}
}
