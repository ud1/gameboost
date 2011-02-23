#pragma once

#include "ImageLoader.h"

namespace gb
{
	namespace loaders
	{
		class BmpLoader : public ImageLoader
		{
		public:
			bool loadImage2dHeader(fs::InputStream &input, containers::Image2dHeader &header_out);
			bool loadImage2d(fs::InputStream &input, containers::Image2d &image_out);
			bool saveImage2d(fs::OutputStream &output, const containers::Image2d &image);
		};
	}
}
