#pragma once

#include <gb/math/math.h>
#include <gb/graphics/Font.h>
#include "TextureAtlas.h"
#include "GlyphCache.h"
#include "RectsBuffer.h"

namespace gb
{
	namespace graphics2d
	{
		
		class TextRenderer
		{
		public:
			TextRenderer(Font &font, TextureAtlas &atlas) : font(font), atlas(atlas) {}
			
			void reset(math::ivec2 start_position, RectsBuffer &buffer)
			{
				current_position = start_position;
				this->buffer = &buffer;
			}
			
			bool renderToBuffer(const std::wstring &text, math::vec3 color);
			
			
		private:
			math::ivec2 current_position;
			Font &font;
			TextureAtlas &atlas;
			GlyphCache glyph_cache;
			RectsBuffer *buffer;
			
			const GlyphData *getGlyphData(wchar_t ch);
		};
		
	}
}