#include "GLAttribute.h"

#include <gb/base/t/debug_cast.h>

namespace
{
	GLenum AttrTypes[] =
	{
		GL_FLOAT,
		GL_DOUBLE,
	};
}

namespace gb
{
	namespace graphics
	{
		namespace gl
		{

			GLAttribute::GLAttribute(const char *name, GLint location)
			{
				this->name = name;
				this->location = location;
			}
			
			bool GLAttribute::setVertexBuffer(Buffer *buf, const Layout &l)
			{
				layout = l;
				buffer = t::debug_cast<GLBuffer *> (buf);
				return true;
			}

			void GLAttribute::bindBuffer()
			{
				buffer->bind();
				glEnableVertexAttribArray(location);
				GL_ERROR_CHECK("glEnableVertexAttribArray");
				
				glVertexAttribPointer(location, layout.ncomponents, AttrTypes[layout.type], 
					GL_FALSE, layout.stride, (char *)NULL + layout.offset);
				GL_ERROR_CHECK("glVertexAttribPointer");
			}

			void GLAttribute::unbindBuffer()
			{
				glDisableVertexAttribArray(location);
				GL_ERROR_CHECK("glDisableVertexAttribArray");
			}

		}
	}
}
