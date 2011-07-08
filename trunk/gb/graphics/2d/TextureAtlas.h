#pragma once

#include "ImageBlock.h"

#include <gb/graphics/Device.h>

#include <boost/shared_ptr.hpp>

namespace gb
{
	namespace graphics
	{
		class TextureAtlas
		{
		public:
			TextureAtlas(Device &device);
			bool initialize(int tex_width = 512, int tex_height = 512);
			const ImageBlock *createImageBlock(const containers::Image &image);
			
		private:
			class TextureAtlasImpl;
			boost::shared_ptr<TextureAtlasImpl> pimpl;
		};
	}
}
