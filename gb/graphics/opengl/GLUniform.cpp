#include "GLUniform.h"

#include <gb/t/debug_cast.h>

namespace gb
{
	namespace graphics
	{
		namespace gl
		{

			GLUniform::GLUniform(const char *name, size_t size, GLint location, bool is_sampler, size_t width, size_t height)
			{
				values = NULL;
				this->name = name;
				this->size = size;
				this->location = location;
				this->is_sampler = is_sampler;
				this->width = width;
				this->height = height;
			}

			GLUniform::~GLUniform()
			{
				delete []values;
			}

			bool GLUniform::setFloats(const float *values_, size_t count_, bool transpose_)
			{
				if (!count_)
					count_ = size;
				count = count_;
				transpose = transpose_;
				if (!values)
					values = new float[width*height*size];
				memcpy(values, values_, width*height*count*sizeof(float));
				return true;
			}

			bool GLUniform::setValues_(int &tex_bind)
			{
				if (!is_sampler)
				{
					switch (width)
					{
					case 1:
						switch (height)
						{
						case 1:
							glUniform1fv(location, count, values);
							break;
						case 2:
							glUniform2fv(location, count, values);
							break;
						case 3:
							glUniform3fv(location, count, values);
							break;
						case 4:
							glUniform4fv(location, count, values);
							break;
						}
						break;
					case 2:
						switch (height)
						{
						case 2:
							glUniformMatrix2fv(location, count, transpose, values);
							break;
						case 3:
							glUniformMatrix2x3fv(location, count, transpose, values);
							break;
						case 4:
							glUniformMatrix2x4fv(location, count, transpose, values);
							break;
						}
						break;
					case 3:
						switch (height)
						{
						case 2:
							glUniformMatrix3x2fv(location, count, transpose, values);
							break;
						case 3:
							glUniformMatrix3fv(location, count, transpose, values);
							break;
						case 4:
							glUniformMatrix3x4fv(location, count, transpose, values);
							break;
						}
						break;
					case 4:
						switch (height)
						{
						case 2:
							glUniformMatrix4x2fv(location, count, transpose, values);
							break;
						case 3:
							glUniformMatrix4x3fv(location, count, transpose, values);
							break;
						case 4:
							glUniformMatrix4fv(location, count, transpose, values);
							break;
						}
						break;
					default:
						return false;
					}
				}
				else
				{
					glActiveTexture(GL_TEXTURE0 + tex_bind);
					texture->bind();
					glUniform1i(location, tex_bind++);
				}
				return true;
			}

			void GLUniform::unsetValues_(int &tex_bind)
			{
				if (is_sampler)
				{
					glActiveTexture(GL_TEXTURE0 + tex_bind++);
					texture->unbind();
				}
			}

			bool GLUniform::setSamplerTexture(Texture *tex)
			{
				if (is_sampler)
				{
					texture = t::debug_cast<GLTexture *> (tex);
					return true;
				}
				return false;
			}

		}
	}
}
	