#include "GLTexture.h"
#include <gb/containers/Image.h>
#include <gb/containers/PixelFormat.h>

#include <GL/glew.h>

#ifdef WIN32
#include <GL/wglew.h>
#endif

#include <GL3/gl3.h>

namespace
{
	using namespace gb::containers;
	
	const GLenum MagMinFilter[] =
	{
		GL_NEAREST,
		GL_LINEAR,
		GL_NEAREST_MIPMAP_NEAREST,
		GL_LINEAR_MIPMAP_NEAREST,
		GL_NEAREST_MIPMAP_LINEAR,
		GL_LINEAR_MIPMAP_LINEAR,
	};

	const GLenum CubeMapFace[] =
	{
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
	};

	const GLenum Target[] =
	{
		GL_TEXTURE_2D, 
		GL_TEXTURE_3D,
		GL_TEXTURE_CUBE_MAP,
	};
	
	bool getGLPixelFormat(ePixelFormat::PixelFormat pf, GLenum &data_format, GLenum &data_type, GLuint &internal_format)
	{
		switch (pf)
		{
			case ePixelFormat::R_8:
				data_format = GL_RED;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = 1;
				return true;
			case ePixelFormat::RGB_888:
				data_format = GL_RGB;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_RGB;
				return true;
			case ePixelFormat::RGBA_8888:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_RGBA;
			case ePixelFormat::RGBA_16_16_16_16:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_SHORT;
				internal_format = GL_RGBA16;
				return true;
			case ePixelFormat::BGR_888:
				data_format = GL_BGR;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_RGB;
				return true;
			case ePixelFormat::BGRA_8888:
				data_format = GL_BGRA;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_RGBA;
				return true;
			case ePixelFormat::RGB_332:
				data_format = GL_RGB;
				data_type = GL_UNSIGNED_BYTE_3_3_2;
				internal_format = GL_R3_G3_B2;
				return true;
			case ePixelFormat::RGB_565:
				data_format = GL_RGB;
				data_type = GL_UNSIGNED_SHORT_5_6_5;
				internal_format = GL_RGB5;
				return true;
			case ePixelFormat::RGBA_4444:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_SHORT_4_4_4_4;
				internal_format = GL_RGBA4;
				return true;
			case ePixelFormat::RGBA_5551:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_SHORT_5_5_5_1;
				internal_format = GL_RGB5_A1;
				return true;
			case ePixelFormat::RGBA_10_10_10_2:
				data_format = GL_RGBA;
				data_type = GL_UNSIGNED_INT_10_10_10_2;
				internal_format = GL_RGB10_A2;
				return true;
			case ePixelFormat::GRAYSCALE8:
				data_format = GL_LUMINANCE;
				data_type = GL_UNSIGNED_BYTE;
				internal_format = GL_LUMINANCE;
				return true;
			case ePixelFormat::GRAYSCALE16:
				data_format = GL_LUMINANCE;
				data_type = GL_UNSIGNED_SHORT;
				internal_format = GL_LUMINANCE16;
				return true;
			case ePixelFormat::FGRAYSCALE:
				data_format = GL_LUMINANCE;
				data_type = GL_FLOAT;
				internal_format = GL_LUMINANCE16;
				return true;
			case ePixelFormat::FR:
				data_format = GL_RED;
				data_type = GL_FLOAT;
				internal_format = 1;
				return true;
			case ePixelFormat::FRGB:
				data_format = GL_RGB;
				data_type = GL_FLOAT;
				internal_format = GL_RGB;
				return true;
			case ePixelFormat::FRGBA:
				data_format = GL_RGBA;
				data_type = GL_FLOAT;
				internal_format = GL_RGBA;
				return true;
		};
		
		return false;
	}
}

namespace gb
{
	namespace graphics
	{
		namespace gl
		{

			GLTexture::GLTexture(Type _type, GLDevice *device_)
			{
				device = device_;
				type = _type;
				glGenTextures(1, &textureID);
				setBorderType(TB_REPEAT);
				setMinFilter(TF_LINEAR_MIPMAP_LINEAR);
				setMagFilter(TF_LINEAR);
				mip_levels = 1;
			}
			
			GLTexture::~GLTexture()
			{
				glDeleteTextures(1, &textureID);
			}
			
			bool GLTexture::setImage(const Image *im, size_t mipLevel)
			{
				return setImageOnCubeFace(im, PosX, mipLevel);
			}

			bool GLTexture::setImageOnCubeFace(const Image *im, CubeFace face, size_t mipLevel)
			{
				if ((size_t) im->data & 3)
				{
					// Данные не выровнены, придется сначала скопировать
					AutoImage auto_image;
					auto_image.copyFrom(*im, im->pixel_format);
					return setImageOnCubeFace(&(const Image &)auto_image, face, mipLevel);
				}
				
				bind();

				GLuint internal_format;
				GLenum data_format;
				GLenum data_type;

				if (!getGLPixelFormat(im->pixel_format, data_format, data_type, internal_format))
					return false;

				GLint row_len = im->pitch / (getPFDescription(im->pixel_format)->bits/8);
				glPixelStorei(GL_UNPACK_ROW_LENGTH, row_len);
				
				switch (type)
				{
					case Texture2D:
						width = im->width;
						height = im->height;
						glTexImage2D(target, mipLevel, internal_format, im->width, im->height, 0, data_format, data_type, im->data);
						break;
					case Texture3D:
						width = im->width;
						height = im->height;
						depth = im->depth;
						glTexImage3D(target, mipLevel, internal_format, im->width, im->height, im->depth, 0, data_format, data_type, im->data);
						break;
					case TextureCube:
						width = im->width;
						height = im->height;
						glTexImage2D(CubeMapFace[face], mipLevel, internal_format, im->width, im->height, 0, data_format, data_type, im->data);
						break;
					default:
						unbind();
						return false;
				}

				unbind();
				return true;
			}

			bool GLTexture::setSubImage(const Image *im, int xoff, int yoff, int zoff, size_t mipLevel)
			{
				return setSubImageOnCubeFace(im, xoff, yoff, zoff, PosX, mipLevel);
			}

			bool GLTexture::setSubImageOnCubeFace(const Image *im, int xoff, int yoff, int zoff, CubeFace face, size_t mipLevel)
			{
				if ((size_t) im->data & 3)
				{
					// Данные не выровнены, придется сначала скопировать
					AutoImage auto_image;
					auto_image.copyFrom(*im, im->pixel_format);
					return setImageOnCubeFace(&(const Image &)auto_image, face, mipLevel);
				}
				
				bind();

				GLuint internal_format;
				GLenum data_format;
				GLenum data_type;

				getGLPixelFormat(im->pixel_format, data_format, data_type, internal_format);

				GLint row_len = im->pitch / (getPFDescription(im->pixel_format)->bits/8);
				glPixelStorei(GL_UNPACK_ROW_LENGTH, row_len);
				
				switch (type)
				{
					case Texture2D:
						glTexSubImage2D(target, mipLevel, xoff, yoff, im->width, im->height, data_format, data_type, im->data);
						break;
					case Texture3D:
						glTexSubImage3D(target, mipLevel, xoff, yoff, zoff, im->width, im->height, im->depth, data_format, data_type, im->data);
						break;
					case TextureCube:
						glTexSubImage2D(CubeMapFace[face], mipLevel, xoff, yoff, im->width, im->height, data_format, data_type, im->data);
						break;
					default:
						unbind();
						return false;
				}

				unbind();
				return true;
			}

			void GLTexture::setMinFilter(TextureFilter filter)
			{
				bind();
				min_filter = filter;
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MagMinFilter[min_filter]);	
				unbind();
			}

			void GLTexture::setMagFilter(TextureFilter filter)
			{
				bind();
				mag_filter = filter;
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagMinFilter[mag_filter]);	
				unbind();
			}

			void GLTexture::setMaxLod(float lod)
			{
				bind();
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, lod);
				unbind();
			}

			void GLTexture::setBorderType(TextureBorder border_type_)
			{
				bind();
				GLuint brd_type; 
				border_type = border_type_;
				switch (border_type)
				{
					case TB_CLAMP:
						brd_type = GL_CLAMP_TO_EDGE;
						break;

					case TB_REPEAT:
						brd_type = GL_REPEAT;
						break;
				}

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, brd_type);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, brd_type);
				unbind();
			}

			void GLTexture::bind()
			{
				target = Target[type];
				glBindTexture(target, textureID);
			}

			void GLTexture::unbind()
			{
				glBindTexture(target, 0);
			}
		}
	}
}
