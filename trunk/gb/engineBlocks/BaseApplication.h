#pragma once

#include <gb/window_subsystem/WindowManager.h>
#include <gb/window_subsystem/Input.h>
#include <gb/graphics/Device.h>
#include <gb/fs/FileSystem.h>
#include <gb/base/Camera.h>

namespace gb
{
	namespace engine_blocks
	{
		
		class BaseApplication
		{
		public:
			BaseApplication();
			~BaseApplication();
			
			bool init(const char *config_file_name);
			void run();
			void stop() {is_running = false;}
			
		protected:
			window_subsystem::Input *input;
		
			window_subsystem::PWindowManager window_manager;
			window_subsystem::PWindow main_window;
			graphics::PDevice device;
			graphics::PRenderTarget main_window_rt;
			fs::PFileSystem file_system;
			base::Camera camera;
			
			bool is_running;
			
			friend class BaseApplicationInputHandler;
			class BaseApplicationInputHandler : public window_subsystem::Input
			{
			public:
				BaseApplicationInputHandler(BaseApplication *app_)
				{
					app = app_;
				}
				
				bool close()
				{
					return app->onClose();
				}
				
			private:
				BaseApplication *app;
			}; 
			
			/** Должна проинициализировать input, который после этого автоматически установится к окну */
			virtual void setupInputHandler();
			
			virtual bool onClose();
		};
		
	}
}