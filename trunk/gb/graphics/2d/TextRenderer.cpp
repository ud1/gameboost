#include "TextRenderer.h"
#include "rects.h"

namespace gb
{
	namespace graphics2d
	{
		
		bool TextRenderer::renderToBuffer(const std::wstring &text, math::vec3 color)
		{
			std::vector<const GlyphData *> glyphs;
			glyphs.reserve(text.size());
			
			for (size_t i = 0; i < text.size(); ++i)
			{
				wchar_t ch = text[i];
				const GlyphData *glyph_data = getGlyphData(ch);
				if (!glyph_data)
					return false;
				
				glyphs.push_back(glyph_data);
			}
			
			for (size_t i = 0; i < text.size(); ++i)
			{
				if (i > 0)
				{
					int advance = glyphs[i - 1]->info.advance + font.kerning(text[i - 1], text[i]);
					current_position.x += (advance >> 6);
				}
				
				const GlyphData *glyph_data = glyphs[i];
				Rect1 rect;
				rect.image_block = glyph_data->image_block;
				rect.left = current_position.x + (glyph_data->info.origin.x >> 6);
				rect.top = current_position.y - (glyph_data->info.origin.y >> 6);
				rect.width = rect.image_block->width;
				rect.height = rect.image_block->height;
				
				buffer->addRects(&rect, 1, color);
			}
			
			current_position.x += glyphs.back()->info.advance;
			
			return true;
		}
		
		const GlyphData *TextRenderer::getGlyphData(wchar_t ch)
		{
			const GlyphData *result = glyph_cache.get(ch);
			
			if (result)
				return result;
			
			GlyphData data;
			if (!font.getGlyphInfo(ch, data.info))
				return nullptr;
			
			containers::AutoImage im(data.info.width, data.info.height, containers::ePixelFormat::ALPHA8);
			if (!font.render(ch, im.getImage()))
				return nullptr;
			
			data.image_block = atlas.createImageBlock(im);
			
			if (!data.image_block)
				return nullptr;
			
			glyph_cache.add(ch, data);
			return glyph_cache.get(ch);
		}
	}
}
