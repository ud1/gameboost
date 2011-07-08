#include <gb/engineBlocks/GameApplication.h>
#include <gb/fs/Helpers.h>
#include <gb/math/math.h>


#include <gb/containers/Image.h>
#include <gb/engineBlocks/SkyBox.h>
#include <gb/base/AutoInjection.h>

#include <vector>

#define _USE_MATH_DEFINES 
#include <cmath>

using namespace gb::base;
using namespace gb::fs;
using namespace gb::math;
using namespace gb::engine_blocks;
using namespace gb::graphics;
using namespace gb::window_subsystem;
using namespace gb::window_subsystem::eKeyCodes;
using namespace gb::loaders;
using namespace gb::containers;

class App : public GameApplication
{
public:
	App(bool console) : GameApplication(console)
	{
		camera.addKeyBinding(KEY_KEY_W, CameraInput::FORWARD);
		camera.addKeyBinding(KEY_KEY_S, CameraInput::BACKWARD);
		camera.addKeyBinding(KEY_KEY_A, CameraInput::LEFT);
		camera.addKeyBinding(KEY_KEY_D, CameraInput::RIGHT);
		camera.addKeyBinding(KEY_SPACE, CameraInput::UPWARD);
		camera.addKeyBinding(KEY_KEY_C, CameraInput::DOWNWARD);
	}
	
	void setup()
	{
		shader_program_2d = CreateRFHolder(device->createShaderProgram());
		std::string frag_source, vert_source;
		readEntireFile(*file_system, "../data/shaders/simple.frag", frag_source);
		readEntireFile(*file_system, "../data/shaders/simple.vert", vert_source);
		PShader frag_shd = CreateRFHolder(device->createFragmentShader());
		frag_shd->setSource(frag_source.c_str());
		frag_shd->compile();
		PShader vert_shd = CreateRFHolder(device->createVertexShader());
		vert_shd->setSource(vert_source.c_str());
		vert_shd->compile();
		shader_program_2d->attachShader(frag_shd);
		shader_program_2d->attachShader(vert_shd);
		shader_program_2d->link();
		
		SkyBoxConfig sky_box_config;
		sky_box_config.filenames[0] = "../data/sky/sky_ep01_02lf.bmp";
		sky_box_config.filenames[1] = "../data/sky/sky_ep01_02ft.bmp";
		sky_box_config.filenames[2] = "../data/sky/sky_ep01_02rt.bmp";
		sky_box_config.filenames[3] = "../data/sky/sky_ep01_02bk.bmp";
		sky_box_config.filenames[4] = "../data/sky/sky_ep01_02up.bmp";
		sky_box_config.filenames[5] = "../data/sky/sky_ep01_02dn.bmp";
		sky_box_config.orientation[0] = ivec2(-1, 0);
		sky_box_config.orientation[1] = ivec2(0, 0);
		sky_box_config.orientation[2] = ivec2(1, 0);
		sky_box_config.orientation[3] = ivec2(2, 0);
		sky_box_config.orientation[4] = ivec2(1, 1);
		sky_box_config.orientation[5] = ivec2(1, -1);
		
		sky_box.create(sky_box_config, camera.coord_system, 100.0f, *shader_program_2d);
	}
	
	PDevice &getDevice()
	{
		return device;
	}
	
	PFileSystem &getFileSystem()
	{
		return file_system;
	}
	
protected:
	void render(GameApplication::ApplicationState, float dt)
	{
		camera.updatePosition(dt);
		const WindowInfo *info = main_window->getWindowInfo();
		camera.aspect_ratio = (float)info->width / (float)info->height;
		
		mat4 projection = camera.getViewProjectionMatrix();
		sky_box.render(projection);
	}
	
	PShaderProgram shader_program_2d;
	
	SkyBox sky_box;
} *application;

namespace gb
{
	namespace base
	{
		template<>
		PDevice inject<Device>()
		{
			return application->getDevice();
		}
		
		template<>
		PFileSystem inject<FileSystem>()
		{
			return application->getFileSystem();
		}
	}
}

int main()
{
	application = new App(true);
	
	if (!application->init("arn/config.txt"))
		return 0;
	
	application->setup();
	
	application->run();
	
	delete application;
}
