#pragma once

#include <gb/base/nullptr.h>
#include <gb/graphics/Font.h>
#include <gb/graphics/2d/ImageBlock.h>
#include <boost/unordered_map.hpp>

namespace gb
{
	namespace graphics2d
	{
		
		struct GlyphData
		{
			Font::GlyphInfo info;
			PImageBlock image_block;
			
			GlyphData() {}
			GlyphData(const GlyphData &o)
			{
				*this = o;
			}
			
			GlyphData &operator = (const GlyphData &o)
			{
				info = o.info;
				image_block = o.image_block;
				return *this;
			}
		};
		
		class GlyphCache
		{
		public:
			
			const GlyphData *get(wchar_t ch) const
			{
				Map::const_iterator it = glyph_map.find(ch);
				if (it == glyph_map.end())
					return nullptr;
				
				return &it->second;
			}
			
			void add(wchar_t ch, const GlyphData &data)
			{
				glyph_map[ch] = data;
			}
			
			void clear()
			{
				glyph_map.clear();
			}
			
		private:
			typedef boost::unordered_map<wchar_t, GlyphData> Map;
			Map glyph_map;
		};
		
	}
}
