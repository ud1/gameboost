#pragma once

#include <gb/graphics/Device.h>
#include "TextRenderer.h"

namespace gb
{
	namespace graphics2d
	{
		
		class Render2d
		{
		public:
			Render2d(graphics::Device &device, graphics::ShaderProgram &prg);
			
			void startRendering();
			void finishRendering();
			
		private:
			TextRenderer *text_renderer;
			TextureAtlas *atlas;
			graphics::Device &device;
			graphics::ShaderProgram &program;
		};
		
	}
}