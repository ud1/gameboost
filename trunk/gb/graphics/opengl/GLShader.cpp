#include "GLShader.h"

#include <gb/base/Logger.h>

namespace gb
{
	namespace graphics
	{
		namespace gl
		{

			GLShader::GLShader(GLenum type, GLDevice *device_)
			{
				device = device_;
				gl_shader = glCreateShader(type);
			}
			
			GLShader::~GLShader()
			{
				glDeleteShader(gl_shader);
			}
			
			void GLShader::setSource(const char *str)
			{
				glShaderSource(gl_shader, 1, &str, NULL);
			}
			
			bool GLShader::compile()
			{
				GLint status;
				glCompileShader(gl_shader);
				glGetShaderiv(gl_shader, GL_COMPILE_STATUS, &status);

				GLint len;
				glGetShaderiv(gl_shader, GL_INFO_LOG_LENGTH, &len);
				if (len > 1)
				{
					char *buf = new char[len+1];
					glGetShaderInfoLog(gl_shader, len+1, NULL, buf);
					if (status = GL_TRUE)
						MESSAGE_LOG(buf);
					else
						ERROR_LOG(buf);
					
					delete []buf;
				}
				return status == GL_TRUE;
			}

		}
	}
}
