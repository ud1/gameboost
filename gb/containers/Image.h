/**	\file  Image.h
 *	\author ud1 (ud1@mail.ru)
*/

#pragma once

#include "PixelFormat.h"
#include <gb/loaders/images/ImageLoader.h>
#include <cassert>

namespace gb
{
	namespace containers
	{
		struct ImageHeader
		{
			ImageHeader()
			{
				depth = 1;
			}
			int width, height, depth;
			ePixelFormat::PixelFormat pixel_format;
			int row_size_in_bytes;
			int data_size;
			
			void calculateDataSize()
			{
				row_size_in_bytes = (width*getPFDescription(pixel_format)->bits/8 + 3) & ~3;
				data_size = depth * height * row_size_in_bytes;
			}
		};
		
		struct Image : public ImageHeader
		{
			Image()
			{
				data = 0;
			}
			
			char *data;
		};
		
		/**
		 * Копирование данных изображения с учетом pixel_format
		 */
		void convert(const Image &from, Image &to);
		
		struct AutoImage : public Image
		{
			AutoImage()
			{
				if (data)
					delete []data;
			}
			
			void copyFrom(const Image &o, ePixelFormat::PixelFormat pf);
			bool load(loaders::ImageLoader &loader, fs::InputStream &input);
			bool save(loaders::ImageLoader &loader, fs::OutputStream &output);
		};
		
		/**
		 * Конвертирование данных изображения из одного формата пикселя в другой
		 * используется функцией convert()
		 * Для каждого формата пикселя pf необходимо специализировать
		 * эту функцию для преобразований pf-->RGBA_8888 pf-->FRGBA RGBA_8888-->pf и FRGBA-->pf
		 */
		template <int from_pf, int to_pf>
		void convert(const Image &from, Image &to)
		{
			// Применяем двойную конвертацию через промежуточный
			// формат пикселя RGBA_8888 или FRGBA, чтобы избежать написания COUNT^2 функций
			// достаточно всего 4*COUNT функций
			AutoImage temp;
			bool floating_point = getPFDescription(to.pixel_format)->floationg_point;
			if (floating_point)
				temp.pixel_format = ePixelFormat::FRGBA;
			else temp.pixel_format = ePixelFormat::RGBA_8888;

			temp.copyFrom(from, temp.pixel_format);
			
			convert(temp, to);
			delete []temp.data;
		}
	}
}
