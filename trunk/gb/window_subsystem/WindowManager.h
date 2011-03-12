#pragma once

#include "Window.h"
#include <string>

namespace gb
{
	namespace window_subsystem
	{
		class WindowManager : public base::IRefCountable
		{
		public:
			virtual bool init(const std::vector<std::string> &options) = 0;
			virtual Window *createWindow(const std::vector<std::string> &params, WindowInfo *info) = 0;
			virtual void processMessages() = 0;
			virtual void quit() = 0;
		};
		
		typedef base::RefCntHolder<WindowManager> PWindowManager;
		
		/**
		 * @param graphics_library может принимать значения например "OpenGL" или "DirectX"
		 */
		WindowManager *createWindowManager(const char *graphics_library);
	}
}