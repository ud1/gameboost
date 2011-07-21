#pragma once

#include "ImageBlock.h"

#include <gb/graphics/Device.h>
#include <boost/shared_ptr.hpp>

namespace gb
{
	namespace graphics2d
	{
		class TextureAtlas
		{
		public:
			TextureAtlas(graphics::Device &device);
			bool initialize(int tex_width = 512, int tex_height = 512);
			const ImageBlock *createImageBlock(const containers::Image &image);
			base::RefCntHolder<graphics::Texture> getTexture();
			
		private:
			class TextureAtlasImpl;
			boost::shared_ptr<TextureAtlasImpl> pimpl;
		};
	}
}
