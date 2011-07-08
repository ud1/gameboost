#pragma once

#include "GLDevice.h"

namespace gb
{
	namespace graphics
	{
		namespace gl
		{
			class GLTexture : public Texture
			{
			public:
				GL_SAFE_OBJECT_DELETION

				GLTexture(Type _type, GLDevice *device_);
				~GLTexture();
				
				bool setImage(const containers::Image *im, size_t mipLevel);
				bool setImageOnCubeFace(const containers::Image *im, CubeFace face, size_t mipLevel);
				bool setSubImage(const containers::Image *im, int xoff, int yoff, int zoff, size_t mipLevel);
				bool setSubImageOnCubeFace(const containers::Image *im, int xoff, int yoff, int zoff, CubeFace face, size_t mipLevel);
				void setMinFilter(TextureFilter filter);
				void setMagFilter(TextureFilter filter);
				void setMaxLod(float lod);
				void setBorderType(TextureBorder border_type_);
				void bind();
				void unbind();
				
			private:
				base::RefCntHolder<GLDevice> device;
				GLuint textureID;
				TextureFilter min_filter, mag_filter;
				TextureBorder border_type;
				GLenum target;
			};
			
		}
	}
}