#include "GLShaderProgram.h"

#include <gb/base/Logger.h>
#include <gb/t/debug_cast.h>
#include "GLShader.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			GLShaderProgram::GLShaderProgram(GLDevice *device_)
			{
				device = device_;
				is_linked = false;
				gl_program = glCreateProgram();
			}

			GLShaderProgram::~GLShaderProgram()
			{
				clear();
				glDeleteProgram(gl_program);
			}

			void GLShaderProgram::attachShader(Shader *shd)
			{
				is_linked = false;
				GLShader *shader = t::debug_cast<GLShader *> (shd);
				glAttachShader(gl_program, shader->getGLShader_());
			}

			void GLShaderProgram::detachShader(Shader *shd)
			{
				is_linked = false;
				GLShader *shader = t::debug_cast<GLShader *> (shd);
				glDetachShader(gl_program, shader->getGLShader_());
			}

			bool GLShaderProgram::link()
			{
				if (is_linked)
					return true;
				GLint status;
				glLinkProgram(gl_program);
				glGetProgramiv(gl_program, GL_LINK_STATUS, &status);

				if (status == GL_TRUE)
					clear();

				GLint len;
				glGetProgramiv(gl_program, GL_INFO_LOG_LENGTH, &len);
				if (len && status == GL_FALSE)
				{
					char *buf = new char[len+1];
					glGetProgramInfoLog(gl_program, len+1, NULL, buf);
					ERROR_LOG(buf);
				}

				is_linked = status == GL_TRUE;
				if (!is_linked)
					return false;
				
				GLint nattr;
				glGetProgramiv(gl_program, GL_ACTIVE_ATTRIBUTES, &nattr);
				glGetProgramiv(gl_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &len);
				char *buf = new char[len + 1];
				for (GLint i = 0; i < nattr; ++i)
				{
					GLint size;
					GLenum type;
					glGetActiveAttrib(gl_program, i, len+1, NULL, &size, &type, buf);
					GLAttribute *attribute = new GLAttribute(buf, glGetAttribLocation(gl_program, buf));
					attributes.push_back(attribute);
				}
				delete []buf;

				GLint nuni;
				glGetProgramiv(gl_program, GL_ACTIVE_UNIFORMS, &nuni);
				//GLint len;
				glGetProgramiv(gl_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &len);
				buf = new char[len + 1];
				for (GLint i = 0; i < nuni; ++i)
				{
					GLint size;
					GLenum type;
					glGetActiveUniform(gl_program, i, len+1, NULL, &size, &type, buf);
					
					bool uniform_is_sampler;
					size_t uniform_width = 0;
					size_t uniform_height = 0;
					switch (type) {
						case GL_FLOAT:
							uniform_width = 1;
							uniform_height = 1;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_VEC2:
							uniform_width = 1;
							uniform_height = 2;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_VEC3:
							uniform_width = 1;
							uniform_height = 3;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_VEC4:
							uniform_width = 1;
							uniform_height = 4;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT2:
							uniform_width = 2;
							uniform_height = 2;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT3:
							uniform_width = 3;
							uniform_height = 3;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT4:
							uniform_width = 4;
							uniform_height = 4;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT2x3:
							uniform_width = 2;
							uniform_height = 3;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT2x4:
							uniform_width = 2;
							uniform_height = 4;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT3x2:
							uniform_width = 3;
							uniform_height = 2;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT3x4:
							uniform_width = 3;
							uniform_height = 4;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT4x2:
							uniform_width = 4;
							uniform_height = 2;
							uniform_is_sampler = false;
							break;
						case GL_FLOAT_MAT4x3:
							uniform_width = 4;
							uniform_height = 3;
							uniform_is_sampler = false;
							break;
						case GL_SAMPLER_1D:
							uniform_is_sampler = true;
							break;
						case GL_SAMPLER_2D:
							uniform_is_sampler = true;
							break;
						case GL_SAMPLER_3D:
							uniform_is_sampler = true;
							break;
						case GL_SAMPLER_CUBE:
							uniform_is_sampler = true;
							break;
					}
					
					GLUniform *uniform = new GLUniform(buf, size, glGetUniformLocation(gl_program, buf), uniform_is_sampler, uniform_width, uniform_height);
					uniforms.push_back(uniform);
				}
				delete []buf;
				
				return status;
			}

			bool GLShaderProgram::activate_()
			{
				for (std::vector<GLAttribute *>::iterator it = attributes.begin(); it != attributes.end(); ++it)
				{
					(*it)->bindBuffer();
				}
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glUseProgram(gl_program);
				int tex_bind = 0;
				for (std::vector<GLUniform *>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
				{
					(*it)->setValues_(tex_bind);
				}
				return true;
			}

			void GLShaderProgram::deactivate_()
			{
				for (std::vector<GLAttribute *>::iterator it = attributes.begin(); it != attributes.end(); ++it)
				{
					(*it)->unbindBuffer();
				}
				
				int tex_bind = 0;
				for (std::vector<GLUniform *>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
				{
					(*it)->unsetValues_(tex_bind);
				}
				glUseProgram(0);
			}

			size_t GLShaderProgram::getUniformsNumber()
			{
				return uniforms.size();
			}

			Uniform *GLShaderProgram::getUniform(size_t i)
			{
				return uniforms[i];
			}

			size_t GLShaderProgram::getAttributesNumber()
			{
				return attributes.size();
			}

			Attribute *GLShaderProgram::getAttribute(size_t i)
			{
				return attributes[i];
			}

			void GLShaderProgram::clear()
			{
				for (std::vector<GLUniform *>::iterator it = uniforms.begin(); it != uniforms.end(); ++it)
				{
					delete *it;
				}
				uniforms.clear();

				for (std::vector<GLAttribute *>::iterator it = attributes.begin(); it != attributes.end(); ++it)
				{
					delete *it;
				}
				attributes.clear();
			}

		}
	}
}