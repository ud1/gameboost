#pragma once
#include <gb/base/IRefCountable.h>
#include <gb/base/OnDeleteSignalingObject.h>
#include "Texture.h"

namespace gb
{
	namespace graphics
	{
		
		/**
		 * @ingroup graphics_group
		 * \brief Интерфейс для работы с юниформ-переменными шейдера
		 * 
		 * Uniform может представлять либо массив из size матриц размером width*height каждая,
		 * либо семплер. Если uniform переменная не является массивом, то size = 1.
		 * В случае если Uniform представляет только одно число, то
		 * width = height = 1.
		 */
		class Uniform : public base::OnDeleteSignalingObject
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
			
			/** @copydoc setFloat(float) */
			virtual bool setFloats(const float *values, size_t count, bool transpose) = 0;
			
			/** Биндинг текстуры к юниформу */
			virtual bool setSamplerTexture(Texture *tex) = 0;
			
			/** \return Длина строк для представления матрицы, например 3 если юниформ это одна матрица mat3, или массив таких матриц */
			size_t getWidth() {return width;}
			
			/** \return Число строк для представления матрицы, например 1, если юниформ является вовсе не матрицей а вектором (vec2, vec3 ...) или даже просто числом */
			size_t getHeight() {return height;}
			
			/** \return Число элементов массива или 1, если юниформ не представляет собой массив */
			size_t getSize() {return size;}
			
			/** \return Является или юниформ семплером */
			bool isSampler() {return is_sampler;}
			
			/** \return Имя */
			const char *getName() {return name.c_str();}
		
		protected:
			size_t width, height, size;
			bool is_sampler;
			std::string name;
		};
		
	}
}
