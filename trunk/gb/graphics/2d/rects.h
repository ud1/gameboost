#pragma once

#include "ImageBlock.h"

namespace gb
{
	namespace graphics
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
			
			base::RefCntHolder<ImageBlock> image_block;
		};
		
		struct Rect9 : public Rect1
		{
			int ex, wx, ny, sy;
		};
	}
}
