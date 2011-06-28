#pragma once
#include <gb/base/IRefCountable.h>

#include "Texture.h"

namespace gb
{
	namespace graphics
	{
		
		/**
		 * \brief Класс для работы с юниформ-переменными шейдера
		 * 
		 * Uniform может представлять либо массив из size матриц размером width*height каждая,
		 * либо семплер. Если uniform переменная не является массивом, то size = 1.
		 * В случае если Uniform представляет только одно число, то
		 * width = height = 1.
		 */
		class Uniform
		{
		public:
			/**
			 * Функции setFloat/setFloats устанавливают внутрение переменные и
			 * не вызывают напрямую никаких функций графической библиотеки, тем
			 * самым могут вызываться из любого, не обязательно Render потока.
			 * Непостредственная установка юниформов происходит при вызове 
			 * Device::draw().
			 */
			bool setFloat(float v) {return setFloats(&v, 1, false);}
			virtual bool setFloats(const float *values, size_t count, bool transpose) = 0;
			
			virtual bool setSamplerTexture(Texture *tex) = 0;
			
			size_t getWidth() {return width;}
			size_t getHeight() {return height;}
			size_t getSize() {return size;}
			bool isSampler() {return is_sampler;}
			const char *getName() {return name.c_str();}
		
		protected:
			size_t width, height, size;
			bool is_sampler;
			std::string name;
		};
		
	}
}
