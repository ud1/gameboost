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
			int row_size, padding_bytes;
			size_t data_size;
			
			void calculateDataSize()
			{
				row_size = width*getPFDescription(pixel_format)->bits/8;
				padding_bytes = ((row_size + 3) & ~3) - row_size;
				// Добавляем хвостик в 4 байта, чтобы можно было
				// создавать подизображения использующие туже пямять,
				// и не беспокоится о паддинге
				data_size = depth * height * (row_size + padding_bytes) + 4;
			}
		};
		
		struct Image : public ImageHeader
		{
			Image()
			{
				data = 0;
			}
			
			int pitch; // Расстояние между строками в байтах
			char *data; // Размер data должен быть не меньше data_size байтов
			
			bool subImage(Image &out, int offset_x, int offset_y)
			{
				if (offset_x + out.width > width)
					return false;
				
				if (offset_y + out.height > height)
					return false;
				
				out.pixel_format = pixel_format;
				out.calculateDataSize();
				out.pitch = pitch;
				out.data = data + offset_y * pitch + offset_x * getPFDescription(pixel_format)->bits/8;
				return true;
			}
		};
		
		/**
		 * Копирование данных изображения с учетом pixel_format
		 */
		void convert(const Image &from, Image &to);
		
		class AutoImage
		{
		public:
			~AutoImage();
			void copyFrom(const Image &o, ePixelFormat::PixelFormat pf);
			bool load(loaders::ImageLoader &loader, fs::InputStream &input);
			bool save(loaders::ImageLoader &loader, fs::OutputStream &output);
			operator const Image & () const
			{
				return image;
			}
			
		private:
			Image image;
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
			ePixelFormat::PixelFormat pixel_format;
			if (floating_point)
				pixel_format = ePixelFormat::FRGBA;
			else pixel_format = ePixelFormat::RGBA_8888;

			temp.copyFrom(from, pixel_format);
			
			convert(temp, to);
		}
	}
}
