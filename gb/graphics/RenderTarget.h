#pragma once
#include <gb/base/IRefCountable.h>

namespace gb
{
	namespace graphics
	{
		
		/**
		 * Интерфейс к поверхности, в которую происходить рендеринг,
		 * пока таком качестве может спользоваться только окно.
		 */
		class RenderTarget : public base::IRefCountable
		{
		public:
			void setClearColor(float r, float g, float b, float a)
			{
				cl_r = r;
				cl_g = g;
				cl_b = b;
				cl_a = a;
			}

			void clearColor(bool b) {isClearColor = b;}
			void clearDepth(bool b) {isClearDepth = b;}
		
			virtual void reshape() = 0;
			virtual void beginFrame() = 0;
			virtual void endFrame() = 0;

			virtual bool getSize(int &width, int &height) = 0;
			
		protected:
			float cl_r, cl_g, cl_b, cl_a;
			bool isClearColor, isClearDepth;
		};
		
		typedef base::RefCntHolder<RenderTarget> PRenderTarget;
		
	}
}
