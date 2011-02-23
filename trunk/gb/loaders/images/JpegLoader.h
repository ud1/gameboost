#pragma once

#include "ImageLoader.h"

namespace gb
{
	namespace loaders
	{
		class JpegLoader : public ImageLoader
		{
		public:
			JpegLoader()
			{
				quality = 95;
			}
			
			bool loadImage2dHeader(fs::InputStream &input, containers::Image2dHeader &header_out);
			bool loadImage2d(fs::InputStream &input, containers::Image2d &image_out);
			bool saveImage2d(fs::OutputStream &output, const containers::Image2d &image);
			
			int quality;
		};
	}
}
