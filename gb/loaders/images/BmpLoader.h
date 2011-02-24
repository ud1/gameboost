/**	\file  BmpLoader.h
 *	\author ud1 (ud1@mail.ru)
*/

#pragma once

#include "ImageLoader.h"

namespace gb
{
	namespace loaders
	{
		class BmpLoader : public ImageLoader
		{
		public:
			bool loadImageHeader(fs::InputStream &input, containers::ImageHeader &header_out);
			bool loadImage(fs::InputStream &input, containers::Image &image_out);
			bool saveImage(fs::OutputStream &output, const containers::Image &image);
		};
	}
}
