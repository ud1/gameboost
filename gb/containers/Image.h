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
		/**
		 * \brief Заголовок изображения.
		 * 
		 * Хранит основные параметры изображения: размеры, формат пиксела и т.д.
		 */
		struct ImageHeader
		{
			ImageHeader()
			{
				depth = 1;
			}
			/** Размеры */
			int width, height, depth;
			/** Формат пикселя */
			ePixelFormat::PixelFormat pixel_format;
			/**
			 * Размер строки изображения в пикселях а также выравнивание 
			 * Практически используется лишь для вспомогательных целей,
			 * для получения расстояния между строками следует использовать
			 * pitch класса изображения.
			 */
			int row_size, padding_bytes;
			/** Размер данных изображения */
			size_t data_size;
			
			/** Вычисляет размер данных изображения по его линейным размерам и формату пикселя */
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
		
		/**
		 * \brief Класс изображения
		 * 
		 * Хранит указатель на данные изображения. Следует заметить, что логически
		 * эти данные не принадлежат объектам этого класса, а принадлежат тому, кто создал их.
		 * В частности объекты типа Image могут ссылаться на область внутри более большого
		 * изображения.
		 */
		struct Image : public ImageHeader
		{
			Image()
			{
				data = 0;
			}
			
			int pitch; /// Расстояние между строками в байтах
			char *data; /// Размер data должен быть не меньше data_size байтов
			
			/**
			 * Инициализирует объект out так, чтобы он ссылался на подобласть изображения,
			 * на которое ссылаемся мы.
			 */
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
		
		/**
		 * \brief Класс изображения с автоматическим управлением памятью.
		 * 
		 * AutoImage в отличие от Image владеет данными изображения,
		 * он сам их создает и уничтожает при необходимости.
		 */
		class AutoImage
		{
		public:
			~AutoImage();
			/**
			 * Копирует в себя данные изображения применяя конвертацию данных
			 * с учетом формата пикселя.
			 */
			void copyFrom(const Image &o, ePixelFormat::PixelFormat pf);
			/**
			 * Загружает данные изображения используя загрузчик
			 */
			bool load(loaders::ImageLoader &loader, fs::InputStream &input);
			/**
			 * Сохраняет данные изображения используя загрузчик
			 */
			bool save(loaders::ImageLoader &loader, fs::OutputStream &output);
			operator const Image & () const
			{
				return image;
			}
			
		private:
			Image image;
		};
		
		/**
		 * \brief Конвертирование данных изображения из одного формата пикселя в другой
		 * используется функцией convert()
		 * 
		 * Для каждого формата пикселя pf необходимо специализировать
		 * эту функцию как минимум для преобразований pf-->RGBA_8888 pf-->FRGBA RGBA_8888-->pf и FRGBA-->pf
		 * чтобы иметь возможность производить любые конвертации.
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
