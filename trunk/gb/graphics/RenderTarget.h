#pragma once
#include <gb/base/IRefCountable.h>

namespace gb
{
	namespace graphics
	{
		
		/**
		 * @ingroup graphics_group
		 * 
		 * \brief Интерфейс к поверхности, в которую происходить рендеринг,
		 * пока таком качестве может использоваться только окно.
		 */
		class RenderTarget : public base::IRefCountable
		{
		public:
			/** Задаёт цвет, к который будет чиститься поверхность перед началом рендеринга */
			void setClearColor(float r, float g, float b, float a)
			{
				cl_r = r;
				cl_g = g;
				cl_b = b;
				cl_a = a;
			}

			/** Нужно ли очищать цветовой буфер */
			void clearColor(bool b) {isClearColor = b;}
			
			/** Нужно ли очищать буфер глубины */
			void clearDepth(bool b) {isClearDepth = b;}
		
			/** Должен вызываться при изменении размера */
			virtual void reshape() = 0;
			
			/** Начало рендеринта */
			virtual void beginFrame() = 0;
			
			/** Окончание рендеринга */
			virtual void endFrame() = 0;

			/** Возвращает размер */
			virtual bool getSize(int &width, int &height) = 0;
			
		protected:
			float cl_r, cl_g, cl_b, cl_a;
			bool isClearColor, isClearDepth;
		};
		
		typedef base::RefCntHolder<RenderTarget> PRenderTarget;
		
	}
}
