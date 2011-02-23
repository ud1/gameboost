#pragma once

#include "PixelFormat.h"
#include <cassert>
#include <boost/concept_check.hpp>

namespace gb
{
	namespace containers
	{
		struct Image2dHeader
		{
			int width, height;
			ePixelFormat::PixelFormat pixel_format;
			int row_size_in_bytes;
			int data_size;
			
			void calculateDataSize()
			{
				row_size_in_bytes = (width*getPFDescription(pixel_format)->bits/8 + 3) & ~3;
				data_size = height * row_size_in_bytes;
			}
		};
		
		struct Image2d : public Image2dHeader
		{
			Image2d()
			{
				data = 0;
			}
			
			char *data;
		};
		
		/**
		 * Копирование данных изображения с учетом pixel_format
		 */
		void convert(const Image2d &from, Image2d &to);
		
		/**
		 * Конвертирование данных изображения из одного формата пикселя в другой
		 * используется функцией convert()
		 * Для каждого формата пикселя pf необходимо специализировать
		 * эту функцию для преобразований pf-->RGBA_8888 pf-->FRGBA RGBA_8888-->pf и FRGBA-->pf
		 */
		template <int from_pf, int to_pf>
		void convert(const Image2d &from, Image2d &to)
		{
			// Применяем двойную конвертацию через промежуточный
			// формат пикселя RGBA_8888 или FRGBA, чтобы избежать написания COUNT^2 функций
			// достаточно всего 4*COUNT функций
			Image2d temp;
			temp.width = from.width;
			temp.height = from.height;
			bool floating_point = getPFDescription(to.pixel_format)->floationg_point;
			if (floating_point)
				temp.pixel_format = ePixelFormat::FRGBA;
			else temp.pixel_format = ePixelFormat::RGBA_8888;

			temp.calculateDataSize();
			temp.data = new char[temp.data_size];
			
			convert(from, temp);
			convert(temp, to);
			delete []temp.data;
		}
	}
}
