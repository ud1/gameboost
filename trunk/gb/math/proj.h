/** \file
 \brief  Перевод 2d->3d и обратно. Сопутствующие типы , фукции и т.д.
*

* \todo Перевод координат прожект /анпрожект. ...... 
 \todo Относительные координаты и перевод.

*/

#pragma once

//#include <gb/math/math.h>
#include <math.h>
#include <gb/math/scalar.h>
#include <gb/math/base.h>
#include <gb/math/forw_decl.h>

#ifdef GB_D3D9
   #include <d3d9.h>
#endif


namespace gb 
{

 namespace math
 {
 
 /** \brief  операции перевода 2d->3d и обратно. Сопутствующие типы , фукции и т.д.
	  Сделал так, чтобы не перегружать базовые пространства имён,  если это по вашему
	   "коряво" ,  то пишите на форуме.   */
  namespace proj
  {
//--------------------------------------------------------------------------------------
  
  
	  //! \brief  Сборка из данных проекции.
	  struct ProjectionData
	  {
		float fovy;
		float aspect;
		float zn;
		float zf;
	  };


//! \brief Относительные экранные координаты.
struct RelatCoord 
{

  float x;
  float y; 

/** \brief Конвертация абсолютных экранных координат в 
   относительные экранные координаты, 
    по размеру экрана (vpWidth и vpHeight)  ПРОВЕРЕНО !  */
inline void   fromScreenCoord( // ScreenCoord_To_RelatCoord(
					            const base::vec2_s& vScrCoord, 
					            const int vpWidth, const int vpHeight ) 
{
  x = - ( ((float)vpWidth /2.0f) - vScrCoord.x ) / ((float)vpWidth /2.0f);
  y = - ( ((float)vpHeight/2.0f) - vScrCoord.y ) / ((float)vpHeight/2.0f);
}


/** \brief Конвертация относительных  экранных координат в  абсолютные
  экранные координаты, 
  по размеру экрана (vpWidth и vpHeight) ПРОВЕРЕНО !    */
inline base::vec2_s  toScreenCoord(const int vpWidth, const int vpHeight ) const
{
   base::vec2_s res;
   res.x =  ((float)vpWidth /2.0f) +   x * ((float)vpWidth /2.0f);
   res.y =  ((float)vpHeight/2.0f) +   y * ((float)vpHeight/2.0f);
   return res; 
}


};

  
  
  //! \brief Вьюпорт  Область вывода .
  class Viewport {
  public:
  
   unsigned int  x; ///< координата по X (по гризонтали)
   unsigned int  y; ///< координата по Y (по вертикали)
   
   unsigned int  width;  ///< ширина
   unsigned int  height; ///< высота
      
#ifdef GB_D3D9
   inline Viewport (const D3DVIEWPORT9& vp) { *this = vp; }
#endif

  
  #ifdef GB_D3D9
   inline void operator = (const D3DVIEWPORT9& vp)
   {
    x = (unsigned int)vp.X;
    y = (unsigned int)vp.Y;   
	
	width  = (unsigned int)vp.Width;
    height = (unsigned int)vp.Height;
   }
   
   //! \brief ПРисвоить координаты, ширину и высоту в  D3DVIEWPORT9  
   inline void to_d3d9Viewport(D3DVIEWPORT9& vpInOut) const
   {
    vpInOut.X = (DWORD)x;
	vpInOut.Y = (DWORD)y;
	
	vpInOut.Width  = (DWORD)width;
	vpInOut.Height = (DWORD)height;
	}
  #endif
  
  
  };
  
  

 //----------------------------------------------------------------------  
 
 
 
   //struct ScreenRelatCoord { float x;  float y; };
  
  
  
  // void vec3_project();
  
  // void vec3_unproject();
  
  
  
  
  
  
//--------------------------------------------------------------------------------------  
  } // end ns
 } // end ns
} // end ns
  
// end file