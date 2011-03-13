#pragma once

#include <gb/window_subsystem/WindowManager.h>
#include <gb/window_subsystem/Input.h>
#include <gb/graphics/Device.h>

namespace gb
{
	namespace engine_blocks
	{
		
		class BaseApplication
		{
		public:
			BaseApplication();
			~BaseApplication();
			
			bool init();
			void run();
			void stop() {is_running = false;}
			
		protected:
			class BaseInputHandler;
			BaseInputHandler *input;
		
			window_subsystem::PWindowManager window_manager;
			window_subsystem::PWindow main_window;
			graphics::PDevice device;
			graphics::PRenderTarget main_window_rt;
			
			bool is_running;
		};
		
	}
}