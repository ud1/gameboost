#include <gb/engineBlocks/GameApplication.h>
#include <gb/fs/Helpers.h>
#include <gb/math/math.h>

#include <gb/graphics/2d/TextureAtlas.h>
#include <gb/graphics/2d/TextRenderer.h>
#include <gb/graphics/2d/RectsBuffer.h>
#include <gb/graphics/FontFreeType.h>
#include <gb/containers/Image.h>
#include <gb/engineBlocks/SkyBox.h>
#include <gb/base/AutoInjection.h>
#include <gb/base/Logger.h>

#include <vector>

#define _USE_MATH_DEFINES 
#include <cmath>
#include <gb/graphics/RenderState.h>

using namespace gb::base;
using namespace gb::fs;
using namespace gb::math;
using namespace gb::engine_blocks;
using namespace gb::graphics;
using namespace gb::graphics2d;
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
		setupSkyBox();
		setup2d();
	}
	
	void setup2d()
	{
		if (!free_type.init())
			return;
		
		shader_program_2d = createShaderProgram("../data/shaders/simple2d.vert", "../data/shaders/simple2d.frag");
		InputStream *input = file_system->getInputStream("../data/BaroqueScript.ttf");
		if (!input)
			return;
		font = CreateRFHolder(free_type.create(*input, 16*64));
		
		input->release();
		atlas = boost::shared_ptr<TextureAtlas>(new TextureAtlas(*device));
		atlas->initialize();
		text_renderer = boost::shared_ptr<TextRenderer>(new TextRenderer(*font, *atlas.get()));
		
		vertex_buffer = CreateRFHolder(device->createVertexBuffer());
		vertex_buffer->setElementSize(sizeof(Vertex2d));
		index_buffer = CreateRFHolder(device->createIndexBuffer());
		index_buffer->setElementSize(sizeof(short));
		
		size_t n = shader_program_2d->getAttributesNumber();
		for (size_t i = 0; i < n; ++i)
		{
			Attribute *attr = shader_program_2d->getAttribute(i);
			if (std::string("position") == attr->getName())
			{
				attr->setVertexBuffer(vertex_buffer, getLayoutOf(&Vertex2d::coord));
			}
			else if (std::string("tex_coord") == attr->getName())
			{
				attr->setVertexBuffer(vertex_buffer, getLayoutOf(&Vertex2d::tex_coord));
			}
			else if (std::string("color") == attr->getName())
			{
				attr->setVertexBuffer(vertex_buffer, getLayoutOf(&Vertex2d::color));
			}
		}
		
		n = shader_program_2d->getUniformsNumber();
		for (size_t i = 0; i < n; ++i)
		{
			Uniform *uniform = shader_program_2d->getUniform(i);
			if (std::string("mvp") == uniform->getName())
			{
				mvp_uniform = uniform;
			}
			else if (std::string("tex") == uniform->getName())
			{
				tex_uniform = uniform;
			}
			else if (std::string("window_size") == uniform->getName())
			{
				uniform_server.bindUniform(uniform_group, *uniform);
			}
		}
		
		render_state_2d = device->createRenderState();
		render_state_2d->setSource("DepthTest disable\n");
	}
	
	void setupSkyBox()
	{
		shader_program = createShaderProgram("../data/shaders/simple.vert", "../data/shaders/simple.frag");

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
		
		sky_box.create(sky_box_config, camera.coord_system, 100.0f, *shader_program);
	}
	
	PShaderProgram createShaderProgram(const std::string &vert_shd_filename,const std::string &frag_shd_filename)
	{
		PShaderProgram result = CreateRFHolder(device->createShaderProgram());
		std::string frag_source, vert_source;
		readEntireFile(*file_system, frag_shd_filename, frag_source);
		readEntireFile(*file_system, vert_shd_filename, vert_source);
		PShader frag_shd = CreateRFHolder(device->createFragmentShader());
		frag_shd->setSource(frag_source.c_str());
		frag_shd->compile();
		PShader vert_shd = CreateRFHolder(device->createVertexShader());
		vert_shd->setSource(vert_source.c_str());
		vert_shd->compile();
		result->attachShader(frag_shd);
		result->attachShader(vert_shd);
		result->link();
		return result;
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
		
		render2d();
	}
	
	void render2d()
	{
		RectsBuffer buffer;
		text_renderer->reset(ivec2(100, 100), buffer);
		text_renderer->renderToBuffer(L"Hello_World little_brown_cat++--++", vec3(0.0f, 0.0f, 0.0f));
		
		uniform_group.updateUniforms();
		if (tex_uniform)
			tex_uniform->setSamplerTexture(atlas->getTexture());
		
		int w, h;
		device->getSize(w, h);
		mat4 mvp = ortho(0.0f, (float) w, (float) h, 0.0f);
		if (mvp_uniform)
			mvp_uniform->setFloats((const float *)&mvp, 1, false);
		
		const RectsBuffer::VertexBuffer &vb = buffer.getVertexBuffer();
		vertex_buffer->setElementsNumber(vb.size());
		vertex_buffer->subData(0, 0, &vb[0]);
		
		const RectsBuffer::IndexBuffer &ib = buffer.getIndexBuffer();
		index_buffer->setElementsNumber(ib.size());
		index_buffer->subData(0, 0, &ib[0]);
		
		render_state_2d->apply();
		device->draw(shader_program_2d, 0, 0, Device::TRIANGLES, index_buffer);
	}
	
	PShaderProgram shader_program, shader_program_2d;
	
	SkyBox sky_box;
	FontFreeType free_type;
	PFont font;
	boost::shared_ptr<TextureAtlas> atlas;
	boost::shared_ptr<TextRenderer> text_renderer;
	PBuffer vertex_buffer, index_buffer;
	Uniform *mvp_uniform, *tex_uniform;
	PRenderState render_state_2d;
	UniformGroup uniform_group;
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
