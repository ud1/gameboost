#include "GLDevice.h"
#include "GLAttribute.h"
#include "GLTexture.h"
#include "GLBuffer.h"
#include "GLRenderState.h"
#include "GLShader.h"
#include "GLShaderProgram.h"
#include "GLUniform.h"
#include "GLWindowRenderTarget.h"

#include <gb/containers/Image.h>
#include <gb/t/debug_cast.h>
#include <gb/window_subsystem/Window.h>
#include <gb/base/nullptr.h>

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			RenderTarget *GLDevice::current_render_target = nullptr;
			
			RenderTarget *GLDevice::createWindowRenderTarget(window_subsystem::Window *wnd)
			{
				GLWindowRenderTarget *rt = new GLWindowRenderTarget(this);
				if (rt->initialize(wnd))
					return rt;
				
				delete rt;
				return nullptr;
			}

			bool GLDevice::getSize(int &width, int &height)
			{
				if (current_render_target)
					return current_render_target->getSize(width, height);
				
				return false;
			}

			void GLDevice::setScissorRect(const base::Rectangle &rc)
			{
				int w, h;
				getSize(w, h);
				glScissor(rc.left, h - rc.top - rc.height, rc.width, rc.height);
			}

			Texture *GLDevice::createTexture(Texture::Type type)
			{
				return new GLTexture(type, this);
			}

			Buffer *GLDevice::createIndexBuffer()
			{
				return new GLBuffer(GL_ELEMENT_ARRAY_BUFFER, this);
			}

			Buffer *GLDevice::createVertexBuffer()
			{
				return new GLBuffer(GL_ARRAY_BUFFER, this);
			}

			RenderState *GLDevice::createRenderState()
			{
				return new GLRenderState;
			}

			static GLenum PrimitiveTypes[] =
			{
				GL_POINTS,
				GL_LINE_STRIP,
				GL_LINE_LOOP,
				GL_LINES,
				GL_TRIANGLE_STRIP,
				GL_TRIANGLE_FAN,
				GL_TRIANGLES
			};

			void GLDevice::draw(ShaderProgram *prg, size_t count, size_t first, PrimitiveType ptype, Buffer *indexBuffer, int base)
			{
				GLShaderProgram *program = t::debug_cast<GLShaderProgram *>(prg);
				if (activated_program && activated_program != prg)
				{
					t::debug_cast<GLShaderProgram *>((ShaderProgram *&) activated_program)->deactivate_();
				}
				program->activate_();
				activated_program = program;

				if (indexBuffer)
				{
					GLBuffer *ind_buf = t::debug_cast<GLBuffer *> (indexBuffer);
					ind_buf->bind();
					GLenum type;
					switch (ind_buf->getElementSize())
					{
						case 1:
							type = GL_UNSIGNED_BYTE;
							break;
						case 2:
							type = GL_UNSIGNED_SHORT;
							break;
						case 4:
							type = GL_UNSIGNED_INT;
							break;
					}
					char *ptr = NULL;
					ptr += ind_buf->getElementSize() * first;
					if (!count)
						count = indexBuffer->getElementsNumber();
					if (!base)
						glDrawElements(PrimitiveTypes[ptype], count, type, ptr);
					else glDrawElementsBaseVertex(PrimitiveTypes[ptype], count, type, ptr, base);
					ind_buf->unbind();
				}
				else
				{
					glDrawArrays(PrimitiveTypes[ptype], first, count);
				}
			}

			void GLDevice::deleteUnusedObjects()
			{
				boost::lock_guard<boost::mutex> guard(for_deletion_guard);
				for (size_t i = 0; i < for_deletion.size(); ++i)
				{
					delete for_deletion[i];
				}
				for_deletion.clear();
			}

			void GLDevice::forDeletion_(IRefCountable *res)
			{
				boost::lock_guard<boost::mutex> guard(for_deletion_guard);
				for_deletion.push_back(res);
			}
		
		
			Shader *GLDevice::createVertexShader()
			{
				return new GLShader(GL_VERTEX_SHADER, this);
			}

			Shader *GLDevice::createGeometryShader()
			{
				return new GLShader(GL_GEOMETRY_SHADER, this);
			}

			Shader *GLDevice::createFragmentShader()
			{
				return new GLShader(GL_FRAGMENT_SHADER, this);
			}

			ShaderProgram *GLDevice::createShaderProgram()
			{
				return new GLShaderProgram(this);
			}
			
			void GLDevice::clean()
			{
				activated_program = NULL;
			}
		}
	}
}