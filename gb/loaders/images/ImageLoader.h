#pragma once

#include <gb/containers/Image2d.h>
#include <gb/fs/Stream.h>

namespace gb
{
	namespace loaders
	{
		class ImageLoader
		{
		public:
			virtual bool loadImage2dHeader(fs::InputStream &input, containers::Image2dHeader &header_out) = 0;
			
			/**
			 * Память для данных должна быть выделена заранее,
			 * сам загрузчик никаких выделений не производит
			 */
			virtual bool loadImage2d(fs::InputStream &input, containers::Image2d &image_out) = 0;
			virtual bool saveImage2d(fs::OutputStream &output, const containers::Image2d &image) = 0;
		};
	}
}
