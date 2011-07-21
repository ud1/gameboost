#pragma once

#include "ImageBlock.h"

namespace gb
{
	namespace graphics2d
	{
		struct Rect1 : public base::Rectangle
		{
			Rect1() {}
			Rect1(const Rect1 &o)
			{
				*this = o;
			}
			
			Rect1 &operator = (const Rect1 &o)
			{
				(base::Rectangle &) *this = (const base::Rectangle &) o;
				image_block = o.image_block;
				return *this;
			}
			
			PImageBlock image_block;
		};
		
		struct Rect9 : public Rect1
		{
			int ex, wx, ny, sy;
			
			Rect9() {}
			Rect9(const Rect9 &o)
			{
				*this = o;
			}
			
			Rect9 &operator = (const Rect9 &o)
			{
				*(Rect1 *) this = (const Rect1 &) o;
				ex = o.ex;
				wx = o.wx;
				ny = o.ny;
				sy = o.sy;
				return *this;
			}
		};
	}
}
