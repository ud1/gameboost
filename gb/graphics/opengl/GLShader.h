#pragma once

#include "GLDevice.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			class GLShader : public Shader
			{
			public:
				GL_SAFE_OBJECT_DELETION

				GLShader(GLenum type, GLDevice *device_);
				~GLShader();
				
				void setSource(const char *str);
				bool compile();
				
				GLuint getGLShader_() const {return gl_shader;}
			private:
				GLDevice *device;
				GLuint gl_shader;
			};
		}
	}
}
