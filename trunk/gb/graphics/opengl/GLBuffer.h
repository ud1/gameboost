#pragma once

#include "GLDevice.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			class GLBuffer : public Buffer
			{
			public:
				GL_SAFE_OBJECT_DELETION

				GLBuffer(GLenum _target, GLDevice *device_);
				~GLBuffer();
				
				void* map(size_t offset_bytes, size_t size);
				void unmap();
				void subData(size_t offset_bytes, size_t size, const void *data);
				void bind();
				void unbind();
				
			private:
				GLDevice *device;
				GLuint bufId;
				GLenum target;
				bool is_binded;
			};
		
		}
	}
}
