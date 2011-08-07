#pragma once

#include "GLDevice.h"
#include <gb/graphics/RenderTarget.h>

#include <gb/windowSubsystem/Window.h>

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			class GLWindowRenderTarget : public RenderTarget
			{
			public:
				GL_SAFE_OBJECT_DELETION

				GLWindowRenderTarget(GLDevice *device_);
				bool initialize(window_subsystem::Window *wnd_);
				void reshape();
				void beginFrame();
				void endFrame();
				bool getSize(int &width, int &height);
				
			private:
				GLDevice *device;
				window_subsystem::PWindow wnd;
				bool viewport_changed;
			};
			
		}
	}
}