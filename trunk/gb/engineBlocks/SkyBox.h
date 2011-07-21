#pragma once

#include <gb/graphics/Device.h>
#include <gb/graphics/Buffer.h>
#include <gb/graphics/ShaderProgram.h>
#include <gb/containers/Image.h>
#include <gb/base/AutoInjection.h>
#include <gb/math/math.h>
#include <gb/math/CoordSystem.h>
#include <gb/fs/FileSystem.h>
#include <gb/loaders/images/BmpLoader.h>

#include <vector>
#include <string>


namespace gb
{
	namespace engine_blocks
	{
		struct SkyBoxConfig
		{
			std::string filenames[6];
			math::ivec2 orientation[6];
		};
		
		class SkyBox
		{
		public:
			base::AutoInjection<graphics::Device> device;
			base::AutoInjection<fs::FileSystem> fs;
			
			void create(const SkyBoxConfig &config, const math::CoordSystem &coord_system, float size, graphics::ShaderProgram &prg);
			void render(const math::mat4 &view_projection_matrix);
			
		private:
			void loadSkyTexture(int i, const std::string &filename);
			
			loaders::BmpLoader image_loader;
			graphics::PTexture textures[6];
			graphics::PBuffer vertex_buffer;
			graphics::PShaderProgram prg;
			graphics::Uniform *mvp_uniform, *tex_uniform;
			math::mat4 model_matrix[6];
		};
		
	}
}