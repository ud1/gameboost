#pragma once

#include "../Device.h"
#include <gb/graphics/ShaderProgram.h>
#include <gb/mt/ThreadPolicy.h>
#include <gb/logging/Logger.h>
#include <boost/thread/mutex.hpp>

#include <GL/glew.h>

#ifdef WIN32
#include <GL/wglew.h>
#endif

#include <GL3/gl3.h>

//------------------- Safe opengl refcountable objects deletion macros---------

#define GL_SAFE_OBJECT_DELETION														\
	void DestroyThis()																\
	{																				\
		if (mt::ThreadMapping::getCurrentThreadGroup() == mt::RENDER_THREAD_GROUP)	\
		{																			\
			delete this;															\
			return;																	\
		}																			\
		device->forDeletion_(this); /*delete later by render thread*/				\
	}

#ifndef NDEBUG
#define GL_ERROR_CHECK(function_name) 			\
{												\
	GLenum error = glGetError();				\
	if (error)									\
		ERROR_LOG("GL error " << error << "(" << function_name << ")");		\
}
#else
#define GL_ERROR_CHECK(function_name)
#endif

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			
			class GLDevice : public Device
			{
			public:
				RenderTarget *createWindowRenderTarget(window_subsystem::Window *wnd);
				bool getSize(int &width, int &height);
				void setScissorRect(const base::Rectangle &rc);

				Texture *createTexture(Texture::Type type);
				Buffer *createIndexBuffer();
				Buffer *createVertexBuffer();
				RenderState *createRenderState();
				void draw(ShaderProgram *prg, size_t count, size_t first, PrimitiveType type, Buffer *indexBuffer, int base = 0);

				Shader *createVertexShader();
				Shader *createGeometryShader();
				Shader *createFragmentShader();
				ShaderProgram *createShaderProgram();
				
				void deleteUnusedObjects();
				void clean();
				void forDeletion_(IRefCountable *res);

				void setCurrentRenderTarget_(RenderTarget *rt) {current_render_target = rt;}
				
			protected:
				PShaderProgram activated_program;
				std::vector<IRefCountable *> for_deletion;
				boost::mutex for_deletion_guard;
				
				static RenderTarget *current_render_target;
			};
		
		}
	}
}
