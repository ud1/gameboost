#pragma once

#include <gb/window_subsystem/WindowManager.h>
#include <gb/window_subsystem/Input.h>
#include <gb/graphics/Device.h>
#include <gb/graphics/RenderTarget.h>
#include <gb/fs/FileSystem.h>
#include <gb/engineBlocks/CameraInput.h>
#include <gb/graphics/UniformServer.h>
#include <boost/shared_ptr.hpp>

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
			graphics::UniformServer uniform_server;
			boost::shared_ptr<base::variable::Variable<math::vec2> > window_size;
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
			
			class WindowSizeVariableUpdater : public base::variable::VariableUpdater<math::vec2>
			{
			public:
				WindowSizeVariableUpdater(const graphics::PDevice &device) : device(device) {}
				
				virtual void setInitialValue(math::vec2 &value)
				{
					value = getSize();
				}
				
				virtual bool update(math::vec2 &value)
				{
					math::vec2 size = getSize();
					if (value == size)
						return false;
					
					value = size;
					return true;
				}
			private:
				graphics::PDevice device;
				
				math::vec2 getSize()
				{
					int width = 0, height = 0;
					device->getSize(width, height);
					return math::vec2((float) width, (float) height);
				}
			};
			
			boost::shared_ptr<WindowSizeVariableUpdater> window_size_updater;
			
			/** Должна проинициализировать input, который после этого автоматически установится к окну */
			virtual void setupInputHandler();
			
			virtual bool onClose();
			
			virtual void renderFrame(float dt){}
		};
		
	}
}