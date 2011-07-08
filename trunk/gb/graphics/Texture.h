#pragma once

#include <gb/base/IRefCountable.h>

namespace gb
{
	namespace containers
	{
		struct Image;
	}
	
	namespace graphics
	{
		
		class Texture : public base::IRefCountable
		{
		public:
			enum Type
			{
				Texture2D,
				Texture3D,
				TextureCube
			};

			enum CubeFace
			{
				PosX = 0,
				NegX,
				PosY,
				NegY,
				PosZ,
				NegZ
			};

			enum TextureFilter
			{
				TF_NONE = -1,
				// Mag/Min filters
				TF_NEAREST,
				TF_LINEAR,

				// Min filters only
				TF_NEAREST_MIPMAP_NEAREST,
				TF_LINEAR_MIPMAP_NEAREST,
				TF_NEAREST_MIPMAP_LINEAR,
				TF_LINEAR_MIPMAP_LINEAR
			};

			enum TextureBorder
			{
				TB_REPEAT,
				TB_CLAMP
			};

			Type getType() const {return type;}
			size_t getWidth() const {return width;}
			size_t getHeight() const {return height;}
			size_t getDepth() const {return depth;}
			size_t getMipLevelsNumber() const {return mip_levels;}

			virtual void setMaxLod(float lod) = 0;
			virtual bool setImage(const containers::Image *im, size_t mipLevel) = 0;
			virtual bool setImageOnCubeFace(const containers::Image *im, CubeFace face, size_t mipLevel) = 0;
			virtual bool setSubImage(const containers::Image *im, int xoff, int yoff, int zoff, size_t mipLevel) = 0;
			virtual bool setSubImageOnCubeFace(const containers::Image *im, int xoff, int yoff, int zoff, CubeFace face, size_t mipLevel) = 0;

			virtual void setMinFilter(TextureFilter filter = TF_LINEAR_MIPMAP_LINEAR) = 0;
			virtual void setMagFilter(TextureFilter filter = TF_LINEAR) = 0;
			virtual void setBorderType(TextureBorder borderType = TB_REPEAT) = 0;
			
		protected:
			Type type;
			size_t width, height, depth, mip_levels;
		};
		
		typedef base::RefCntHolder<Texture> PTexture;
	}
}