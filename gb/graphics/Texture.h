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
		
		/**
		* @ingroup graphics_group
		* \brief Интерфейс для текстур.
		*/
		class Texture : public base::IRefCountable
		{
		public:
			/** Тип текстуры */
			enum Type
			{
				Texture2D,
				Texture3D,
				TextureCube
			};

			/** Тип грани кубмапы */
			enum CubeFace
			{
				PosX = 0,
				NegX,
				PosY,
				NegY,
				PosZ,
				NegZ
			};

			/** Тип фильтрации */
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

			/** Тип границ */
			enum TextureBorder
			{
				TB_REPEAT,
				TB_CLAMP
			};

			/** \return тип текстуры */
			Type getType() const {return type;}
			
			/** \return Ширина */
			size_t getWidth() const {return width;}
			
			/** \return Высота */
			size_t getHeight() const {return height;}
			
			/** \return Глубина для трёхмерных текстур */
			size_t getDepth() const {return depth;}
			
			/** \return Количество мип-уровней */
			size_t getMipLevelsNumber() const {return mip_levels;}

			/**
			 * Устанавливает максимальный мип используемый при фильтрации. Полезен например, когда текстура используется в качестве атласа, но при этом 
			 * используюется мипмапинг. При этом между эелементами атласа должна быть дополнительная обводка, чтобы в
			 * мипах не было смешивания изображений, и размеется число мип уровней будет определяться шириной этой обводке (log2(border_width))/
			 */
			virtual void setMaxLod(float lod) = 0;
			
			/** Загрузка изображений на определённый мип */
			virtual bool setImage(const containers::Image *im, size_t mipLevel) = 0;
			
			/** Загрузка изображения на определённый мип стороны кубмапы */
			virtual bool setImageOnCubeFace(const containers::Image *im, CubeFace face, size_t mipLevel) = 0;
			
			/** Обновление подизображения */
			virtual bool setSubImage(const containers::Image *im, int xoff, int yoff, int zoff, size_t mipLevel) = 0;
			
			/** Тип текстуры */
			virtual bool setSubImageOnCubeFace(const containers::Image *im, int xoff, int yoff, int zoff, CubeFace face, size_t mipLevel) = 0;

			/** Установка фильтрации */
			virtual void setMinFilter(TextureFilter filter = TF_LINEAR_MIPMAP_LINEAR) = 0;
			
			/** Установка фильтрации */
			virtual void setMagFilter(TextureFilter filter = TF_LINEAR) = 0;
			
			/** Установка типа границ */
			virtual void setBorderType(TextureBorder borderType = TB_REPEAT) = 0;
			
		protected:
			Type type;
			size_t width, height, depth, mip_levels;
		};
		
		typedef base::RefCntHolder<Texture> PTexture;
	}
}