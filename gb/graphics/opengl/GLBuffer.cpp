#include "GLBuffer.h"

namespace
{
	using namespace gb::base;
	using namespace gb::graphics::gl;
	
	typedef std::vector<RefCntHolder<GLBuffer> > BindedBuffers;
	BindedBuffers binded_buffers;
}

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			GLBuffer::GLBuffer(GLenum _target, GLDevice *device_)
			{
				device = device_;
				glGenBuffers(1, &bufId);
				GL_ERROR_CHECK("glGenBuffers");
				is_created = false;
				target = _target;
				is_binded = false;
			}

			GLBuffer::~GLBuffer()
			{
				glDeleteBuffers(1, &bufId);
				GL_ERROR_CHECK("glDeleteBuffers");
			}

			void* GLBuffer::map(size_t offset_bytes, size_t size)
			{
				assert(offset_bytes + size <= nelements * element_size);
				bind();
				if (!is_created)
				{
					glBufferData(target, nelements * element_size, 0, GL_STATIC_DRAW);
					GL_ERROR_CHECK("glBufferData");
					is_created = true;
				}
				
				void *res;
				if (size == 0)
				{
					res = glMapBuffer(target, GL_WRITE_ONLY);
					GL_ERROR_CHECK("glMapBuffer");
				}
				else
				{
					res = glMapBufferRange(target, offset_bytes, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
					GL_ERROR_CHECK("glMapBufferRange");
				}
				unbind();
				return res;
			}

			void GLBuffer::unmap()
			{
				bind();
				glUnmapBuffer(target);
				GL_ERROR_CHECK("glUnmapBuffer");
				unbind();
			}
			
			void GLBuffer::subData(size_t offset_bytes, size_t size, const void *data)
			{
				if (!size)
					size = nelements * element_size - offset_bytes;
				assert(offset_bytes + size <= nelements * element_size);
				
				bind();
				if (!is_created)
				{
					glBufferData(target, nelements * element_size, 0, GL_STATIC_DRAW);
					GL_ERROR_CHECK("glBufferData");
					is_created = true;
				}
				
				glBufferSubData(target, offset_bytes, size, data);
				GL_ERROR_CHECK("glBufferSubData");
				unbind();
			}

			void GLBuffer::bind()
			{
				if (!is_binded)
				{
					glBindBuffer(target, bufId);
					GL_ERROR_CHECK("glBindBuffer");
					is_binded = true;
					binded_buffers.push_back(this);
				}
			}

			void GLBuffer::unbind()
			{
				BindedBuffers::iterator it, it_end;
				it = binded_buffers.begin();
				it_end = binded_buffers.end();
				for (;it != it_end; ++it)
				{
					(*it)->is_binded = false;
				}
				binded_buffers.clear();
				glBindBuffer(target, 0);
			}

		}
	}
}