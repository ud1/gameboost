#include "BaseApplication.h"
#include "InputHandlerMap.h"
#include <gb/fs/LocalFS.h>
#include <gb/fs/Helpers.h>
#include <gb/base/Logger.h>

#include <yaml-cpp/yaml.h>
#include <sstream>

#include <cmath>

namespace
{
	void setupCamera(gb::base::Camera &camera, const YAML::Node &config)
	{
		const YAML::Node *camera_node = config.FindValue("camera");
		if (camera_node)
		{
			const YAML::Node *node;
			if (node = camera_node->FindValue("znear"))
				*node >> camera.znear;
			
			if (node = camera_node->FindValue("zfar"))
				*node >> camera.zfar;
			
			if (node = camera_node->FindValue("fov"))
			{
				*node >> camera.fov;
				camera.fov *= M_PI;
			}
			
			if (node = camera_node->FindValue("speed"))
				*node >> camera.speed;
		}
	}
}

namespace gb
{
	namespace engine_blocks
	{
		BaseApplication::BaseApplication()
		{
			is_running = true;
			file_system = new fs::LocalFS;
		}
		
		BaseApplication::~BaseApplication()
		{
			delete input;
		}
		
		bool BaseApplication::init(const char *config_file_name)
		{
			std::string config_text;
			if (!fs::readEntireFile(*file_system, config_file_name, config_text))
				return false;
			
			std::istringstream iss(config_text);
			
			std::vector<std::string> wnd_opts;
			
			try
			{
				YAML::Parser parser(iss);
				YAML::Node doc;
				parser.GetNextDocument(doc);
				
				const YAML::Node *window_node = doc.FindValue("window");
				if (window_node)
				{
					const YAML::Node *window_options_node = window_node->FindValue("options");
					if (window_options_node)
					{
						for (YAML::Iterator it = window_options_node->begin(); it != window_options_node->end(); ++it)
							wnd_opts.push_back(*it);
					}
				}
				
				setupCamera(camera, doc);
			}
			catch (YAML::ParserException& e)
			{
				ERROR_LOG(e.what());
				return false;
			}
			
			window_manager = window_subsystem::createWindowManager("OpenGL");
			if (!window_manager)
				return false;
			
			if (!window_manager->init(std::vector<std::string>()))
				return false;
			
			main_window = window_manager->createWindow(wnd_opts, NULL);
			if (!main_window)
				return false;
			
			setupInputHandler();
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
		
		void BaseApplication::setupInputHandler()
		{
			input = new BaseApplicationInputHandler(this);
		}
		
		bool BaseApplication::onClose()
		{
			stop();
			return false; // Выполнить закрытие окна
		}
		
	}
}