


#pragma once

#include "../Texture.h"

namespace gb
{

 namespace graphics
 {

  namespace d3d9
  {
  
  
	class d3d9_texture : Texture {
	public:
	
		virtual ~d3d9_texture() {}
	
	
			virtual void setMaxLod(float lod) 
			{
				assert(false);
			}
			
			/** Загрузка изображений на определённый мип */
			virtual bool setImage(const containers::Image *im, size_t mipLevel)
			{
				assert(false);
			}
			
			/** Загрузка изображения на определённый мип стороны кубмапы */
			virtual bool setImageOnCubeFace(const containers::Image *im, CubeFace face, size_t mipLevel)
			{
				assert(false);
			}
			
			/** Обновление подизображения */
			virtual bool setSubImage(const containers::Image *im, int xoff, int yoff, int zoff, size_t mipLevel)
			{
				assert(false);
			}
			
			/** Тип текстуры */
			virtual bool setSubImageOnCubeFace(const containers::Image *im, int xoff, int yoff, int zoff, CubeFace face, size_t mipLevel)
			{
				assert(false);
			}

			/** Установка фильтрации */
			virtual void setMinFilter(TextureFilter filter = TF_LINEAR_MIPMAP_LINEAR)
			{
				assert(false);
			}
			
			/** Установка фильтрации */
			virtual void setMagFilter(TextureFilter filter = TF_LINEAR)
			{
				assert(false);
			
			}
			
			/** Установка типа границ */
			virtual void setBorderType(TextureBorder borderType = TB_REPEAT)
			{
				assert(false);
			}
			
	
	
	
	};
  
  
  
  
  
  
  
  
  
  
  }
 }
}
