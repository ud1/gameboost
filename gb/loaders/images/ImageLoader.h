/**	\file  ImageLoader.h
 *	\author ud1 (ud1@mail.ru)
*/

#pragma once

namespace gb
{
	namespace containers
	{
		struct ImageHeader;
		struct Image;
	}
	
	namespace fs
	{
		class InputStream;
		class OutputStream;
	}
	
	namespace loaders
	{
		class ImageLoader
		{
		public:
			virtual bool loadImageHeader(fs::InputStream &input, containers::ImageHeader &header_out) = 0;
			
			/**
			 * Память для данных должна быть выделена заранее,
			 * сам загрузчик никаких выделений не производит
			 */
			virtual bool loadImage(fs::InputStream &input, containers::Image &image_out) = 0;
			virtual bool saveImage(fs::OutputStream &output, const containers::Image &image) = 0;
		};
	}
}
