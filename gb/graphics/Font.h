#pragma once

#include <gb/containers/Image.h>
#include <gb/base/IRefCountable.h>
#include <gb/math/math.h>
#include <string>


namespace gb
{
	namespace graphics2d
	{
		
		class Font : public base::IRefCountable
		{
		public:
			
			struct GlyphInfo
			{
				/** Размер Bounding Box'а глифа в пикселях */
				int width, height;
				
				/** Координаты левого верхнего угла глифа в единицах 1/64 пикселя */
				math::ivec2 origin;
				
				/** Величина в единицах 1/64 пикселя, на которое надо сместить перо после рендеринга глифа */
				int advance;
			};
			
			struct FontInfo
			{
				std::string font_name;
				int height;
			};
			
			virtual bool getGlyphInfo(wchar_t ch, GlyphInfo &out) = 0;
			virtual bool render(wchar_t ch, containers::Image &image, int subpixel_offset = 0) = 0;
			virtual int kerning(wchar_t left, wchar_t right) = 0;
			virtual const FontInfo *getFontInfo() const = 0;
		};
		
		typedef base::RefCntHolder<Font> PFont;
	}
}