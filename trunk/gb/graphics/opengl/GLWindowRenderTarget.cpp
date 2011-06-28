#include "GLWindowRenderTarget.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			GLWindowRenderTarget::GLWindowRenderTarget(GLDevice *device_)
			{
				device = device_;
				isClearColor = isClearDepth = true;
				viewport_changed = false;
			}
			
			bool GLWindowRenderTarget::initialize(window_subsystem::Window *wnd_)
			{
				wnd = wnd_;
				return true;
			}

			void GLWindowRenderTarget::reshape()
			{
				viewport_changed = true;
			}

			void GLWindowRenderTarget::beginFrame()
			{
				device->setCurrentRenderTarget_(this);
				wnd->startRendering();
				glDisable(GL_SCISSOR_TEST);
				
				if (viewport_changed)
				{
					viewport_changed = false;
					const window_subsystem::WindowInfo *info = wnd->getWindowInfo();
					glViewport (0, 0, (GLsizei)(info->width), (GLsizei)(info->height));
				}
				
				if (isClearColor)
				{
					glClearColor(cl_r, cl_g, cl_b, cl_a);
					if (isClearDepth)
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					else glClear(GL_COLOR_BUFFER_BIT);
					return;
				}
				
				if (isClearDepth)
				{
					glClear(GL_DEPTH_BUFFER_BIT);
				}
			}
			
			void GLWindowRenderTarget::endFrame()
			{
				wnd->finishRendering();
			}

			bool GLWindowRenderTarget::getSize(int &width, int &height)
			{
				if (wnd)
				{
					const window_subsystem::WindowInfo *info = wnd->getWindowInfo();
					width = info->width;
					height = info->height;
					return true;
				}
				return false;
			}

		}
	}
}
