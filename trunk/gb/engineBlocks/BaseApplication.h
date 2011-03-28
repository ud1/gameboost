#pragma once

#include <gb/window_subsystem/WindowManager.h>
#include <gb/window_subsystem/Input.h>
#include <gb/graphics/Device.h>
#include <gb/fs/FileSystem.h>
#include <gb/engineBlocks/CameraInput.h>

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
			graphics::PShaderServer shader_server;
			graphics::PRenderTarget main_window_rt;
			fs::PFileSystem file_system;
			CameraInput camera;
			
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
				
				bool reshape()
				{
					app->main_window_rt->reshape();
					return true;
				}
				
			private:
				BaseApplication *app;
			};
			
			/** Должна проинициализировать input, который после этого автоматически установится к окну */
			virtual void setupInputHandler();
			
			virtual bool onClose();
			
			virtual void renderFrame(float dt){}
		};
		
	}
}