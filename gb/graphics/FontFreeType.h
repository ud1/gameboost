#pragma once

#include "Font.h"
#include <gb/fs/Stream.h>

namespace gb
{
	namespace graphics2d
	{
		
		class FontFreeType
		{
		public:
			FontFreeType();
			bool init();
			Font *create(fs::InputStream &input, int height, int width = 0);
			
		private:
			class FontFreeTypeImpl;
			FontFreeTypeImpl *pimpl;
		};
		
	}
}