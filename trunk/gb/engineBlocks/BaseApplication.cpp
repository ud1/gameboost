#include "BaseApplication.h"

namespace gb
{
	namespace engine_blocks
	{

		class BaseApplication::BaseInputHandler : public window_subsystem::Input
		{
		public:
			BaseInputHandler(BaseApplication *app_)
			{
				app = app_;
			}
			
			bool close()
			{
				app->stop();
			}
			
		private:
			BaseApplication *app;
		};
			
		BaseApplication::BaseApplication()
		{
			is_running = true;
			input = new BaseInputHandler(this);
		}
		
		BaseApplication::~BaseApplication()
		{
			delete input;
		}
		
		bool BaseApplication::init()
		{
			window_manager = window_subsystem::createWindowManager("OpenGL");
			if (!window_manager)
				return false;
			
			if (!window_manager->init(std::vector<std::string>()))
				return false;
			
			std::vector<std::string> wnd_opts;
			wnd_opts.push_back("--rel_width=0.5");
			wnd_opts.push_back("--rel_height=0.5");
			wnd_opts.push_back("--rel_x=0.25");
			wnd_opts.push_back("--rel_y=0.25");
			
			main_window = window_manager->createWindow(wnd_opts, NULL);
			if (!main_window)
				return false;
			
			main_window->attachInputHandler(input);
			
			device = graphics::createDevice("OpenGL");
			if (!device)
				return false;
			
			main_window_rt = device->createWindowRenderTarget(main_window);
			if (!main_window_rt)
				return false;
			
			main_window_rt->clearColor(true);
			main_window_rt->setClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			main_window_rt->clearDepth(true);
			
			return true;
		}
		
		void BaseApplication::run()
		{
			main_window->show(true);
			
			while (is_running)
			{
				window_manager->processMessages();
				main_window_rt->beginFrame();
				main_window_rt->endFrame();
			}
		}
		
	}
}