#pragma once

#include "../Device.h"
#include <boost/thread/mutex.hpp>

namespace gb
{
	namespace graphics
	{
		class GLDevice : public Device
		{
		public:
			GLDevice();
			RenderTarget *createWindowRenderTarget(window_subsystem::Window *wnd);
			bool getSize(int &width, int &height);
			void setScissorRect(const base::Rectangle &rc);

			Texture *createTexture(Texture::Type type);
			Buffer *createIndexBuffer();
			Buffer *createVertexBuffer();
			RenderState *createRenderState();
			void draw(ShaderProgram *prg, size_t count, size_t first, PrimitiveType type, Buffer *indexBuffer, int base = 0);

			ShaderServer *createShaderServer();

			void deleteUnusedObjects();
			void forDeletion_(IRefCountable *res);

		protected:
			base::RefCntHolder<ShaderProgram> activated_program;
			std::vector<IRefCountable *> for_deletion;
			boost::mutex for_deletion_guard;
		};
	}
}
