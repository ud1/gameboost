#pragma once

#include "GLDevice.h"
#include "GLTexture.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			class GLUniform : public Uniform
			{
			public:
				GLUniform(const char *name, size_t size, GLint location, bool is_sampler, size_t width, size_t height);
				~GLUniform();
				
				bool setFloats(const float *values_, size_t count_, bool transpose_);
				bool setSamplerTexture(Texture *tex);
				
				bool setValues_(int &tex_bind);
				void unsetValues_(int &tex_bind);
				
			private:
				GLint location;
				base::RefCntHolder<GLTexture> texture;
				float *values;
				size_t count;
				bool transpose;
			};
			
		}
	}
}
