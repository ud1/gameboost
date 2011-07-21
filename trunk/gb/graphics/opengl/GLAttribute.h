#pragma once

#include "GLDevice.h"
#include "GLBuffer.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			class GLAttribute : public Attribute
			{
			public:
				GLAttribute(const char *name, GLint location);
				bool setVertexBuffer(Buffer *buf, const Layout &l);
				void bindBuffer();
				void unbindBuffer();
				
			private:
				GLint location;
				Layout layout;
				base::RefCntHolder<GLBuffer> buffer;
			};
		}
	}
}
