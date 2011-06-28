#include <gb/engineBlocks/GameApplication.h>
#include <gb/fs/Helpers.h>
#include <gb/math/math.h>

#include <gb/loaders/images/BmpLoader.h>
#include <gb/containers/Image.h>

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
		
		InputStream *file = file_system->getInputStream("../data/sky/sky_ep01_02bk.bmp");
		AutoImage im;
		im.load(image_loader, *file);
		file->release();
		image = CreateRFHolder<Texture>(device->createTexture(Texture::Texture2D));
// 		image->setMinFilter(Texture::TF_LINEAR);
// 		image->setMagFilter(Texture::TF_LINEAR);
		image->setImage(&(const Image &)im, 0);
		
		struct Vert
		{
			vec3 pos;
			vec2 tex_coord;
		};
		
		float s = 100.0f;
		
		Vert verts[4];
		verts[0].pos = vec3(-1, 1, 0);
		verts[1].pos = vec3(1, 1, 0);
		verts[2].pos = vec3(1, -1, 0);
		verts[3].pos = vec3(-1, -1, 0);
		
		verts[0].tex_coord = vec2(-1, 1);
		verts[1].tex_coord = vec2(1, 1);
		verts[2].tex_coord = vec2(1, -1);
		verts[3].tex_coord = vec2(-1, -1);
		
		short inds[6] = {0, 1, 3, 3, 1, 2};
		
		vertex_buffer = CreateRFHolder(device->createVertexBuffer());
		vertex_buffer->setElementSize(sizeof(Vert));
		vertex_buffer->setElementsNumber(4);
		vertex_buffer->subData(0, 0, (void *) verts);
		
		index_buffer = CreateRFHolder(device->createIndexBuffer());
		index_buffer->setElementSize(sizeof(short));
		index_buffer->setElementsNumber(6);
		index_buffer->subData(0, 0, (void *) inds);
		
		size_t n = shader_program_2d->getAttributesNumber();
		for (size_t i = 0; i < n; ++i)
		{
			Attribute *attr = shader_program_2d->getAttribute(i);
			if (std::string("position") == attr->getName())
			{
				Layout layout;
				layout.ncomponents = 3;
				layout.offset = 0;
				layout.stride = sizeof(Vert);
				layout.type = Layout::FLOAT;
				attr->setVertexBuffer(vertex_buffer, &layout);
			}
			else if (std::string("tex_coord") == attr->getName())
			{
				Layout layout;
				layout.ncomponents = 2;
				layout.offset = reinterpret_cast<size_t>(&((Vert *) NULL)->tex_coord);
				layout.stride = sizeof(Vert);
				layout.type = Layout::FLOAT;
				attr->setVertexBuffer(vertex_buffer, &layout);
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
				uniform->setSamplerTexture(image);
			}
		}
	}
	
protected:
	void render(GameApplication::ApplicationState, float dt)
	{
		mat4 mvp = ortho(-2.0f, 2.0f, 2.0f, -2.0f);
		mvp_uniform->setFloats((float *)&mvp, 1, false);
		
		device->draw((ShaderProgram *) shader_program_2d, 0, 0, Device::TRIANGLES, index_buffer);
	}
	
	PBuffer index_buffer, vertex_buffer;
	PShaderProgram shader_program_2d;
	BmpLoader image_loader;
	//PTexture images[8];
	PTexture image;
	Uniform *mvp_uniform;
};

int main()
{
	App application(true);
	
	if (!application.init("arn/config.txt"))
		return 0;
	
	application.setup();
	
	application.run();
}