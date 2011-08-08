#include "SkyBox.h"

#include <gb/math/math.h>

namespace gb
{
	namespace engine_blocks
	{
		using namespace gb::math;
		using namespace gb::graphics;
		using namespace gb::fs;
		using namespace gb::containers;
		
		void SkyBox::create(const SkyBoxConfig &config, const math::CoordSystem &coord_system, float size, ShaderProgram &prg)
		{
			struct Vert
			{
				vec3 pos;
				vec2 tex_coord;
			};
			
			Vert verts[6];
			verts[0].pos = (coord_system.getForwardVector() - coord_system.getRightVector() + coord_system.getUpVector())*size;
			verts[1].pos = (coord_system.getForwardVector() + coord_system.getRightVector() + coord_system.getUpVector())*size;
			verts[2].pos = (coord_system.getForwardVector() - coord_system.getRightVector() - coord_system.getUpVector())*size;
			verts[3].pos = (coord_system.getForwardVector() - coord_system.getRightVector() - coord_system.getUpVector())*size;
			verts[4].pos = (coord_system.getForwardVector() + coord_system.getRightVector() + coord_system.getUpVector())*size;
			verts[5].pos = (coord_system.getForwardVector() + coord_system.getRightVector() - coord_system.getUpVector())*size;
			
			verts[0].tex_coord = vec2(1, 0);
			verts[1].tex_coord = vec2(0, 0);
			verts[2].tex_coord = vec2(1, 1);
			verts[3].tex_coord = vec2(1, 1);
			verts[4].tex_coord = vec2(0, 0);
			verts[5].tex_coord = vec2(0, 1);
			
			vertex_buffer = base::CreateRFHolder(device->createVertexBuffer());
			vertex_buffer->setElementSize(sizeof(Vert));
			vertex_buffer->setElementsNumber(6);
			vertex_buffer->subData(0, 0, (void *) verts);
			
			this->prg = &prg;
			size_t n = prg.getAttributesNumber();
			for (size_t i = 0; i < n; ++i)
			{
				Attribute *attr = prg.getAttribute(i);
				if (std::string("position") == attr->getName())
				{
					attr->setVertexBuffer(vertex_buffer, getLayoutOf(&Vert::pos));
				}
				else if (std::string("tex_coord") == attr->getName())
				{
					attr->setVertexBuffer(vertex_buffer, getLayoutOf(&Vert::tex_coord));
				}
			}
			
			n = prg.getUniformsNumber();
			for (size_t i = 0; i < n; ++i)
			{
				Uniform *uniform = prg.getUniform(i);
				if (std::string("mvp") == uniform->getName())
				{
					mvp_uniform = uniform;
				}
				else if (std::string("tex") == uniform->getName())
				{
					tex_uniform = uniform;
				}
			}
			
			for (int i = 0; i < 6; ++i)
				loadSkyTexture(i, config.filenames[i]);
			
			for (int i = 0; i < 6; ++i)
				model_matrix[i] = rotate(rotate(mat4(1.0f), -90.0f*config.orientation[i].x, coord_system.getUpVector()), 90.0f*config.orientation[i].y, coord_system.getRightVector());
		}
		
		void SkyBox::loadSkyTexture(int i, const std::string &filename)
		{
			InputStream *file = fs->getInputStream(filename);
			AutoImage im;
			im.load(image_loader, *file);
			file->release();
			PTexture image = base::CreateRFHolder<Texture>(device->createTexture(Texture::Texture2D));
			image->setMinFilter(Texture::TF_LINEAR);
			image->setMagFilter(Texture::TF_LINEAR);
			image->setBorderType(Texture::TB_CLAMP);
			image->setImage(&(const Image &)im, 0);
			textures[i] = image;
		}
		
		void SkyBox::render(const math::mat4 &view_projection_matrix)
		{
			for (int i = 0; i < 6; ++i)
			{
				tex_uniform->setSamplerTexture(textures[i]);
				mat4 mvp = view_projection_matrix * model_matrix[i];
				mvp_uniform->setFloats((const float *) &mvp, 1, false);
				
				device->draw((ShaderProgram *) prg, 6, 0, Device::TRIANGLES, nullptr);
			}
		}
	}
}
