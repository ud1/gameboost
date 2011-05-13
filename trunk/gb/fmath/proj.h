/** \file
 \brief  Перевод 2d->3d и обратно. Сопутствующие типы , фукции и т.д.
*

* \todo Перевод координат прожект /анпрожект. ...... 
 \todo Относительные координаты и перевод.

*/

#pragma once

#ifndef __GB_FMATH_H__
  #error НЕ ВКЛЮЧАЙТЕ ЭТОТ ФАЙЛ. ВКЛЮЧАЙТЕ:   #include <gb/fmath/math.h>  
#endif

/*
#ifdef _D3D9_H_
   #include <d3d9.h>
#endif
*/

namespace gb 
{

 namespace fmath
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
					            const  vec2_s& vScrCoord, 
					            const int vpWidth, const int vpHeight ) 
{
  x = - ( ((float)vpWidth /2.0f) - vScrCoord.x ) / ((float)vpWidth /2.0f);
  y = - ( ((float)vpHeight/2.0f) - vScrCoord.y ) / ((float)vpHeight/2.0f);
}


/** \brief Конвертация относительных  экранных координат в  абсолютные
  экранные координаты, 
  по размеру экрана (vpWidth и vpHeight) ПРОВЕРЕНО !    */
inline  vec2_s  toScreenCoord(const int vpWidth, const int vpHeight ) const
{
    vec2_s res;
   res.x =  ((float)vpWidth /2.0f) +   x * ((float)vpWidth /2.0f);
   res.y =  ((float)vpHeight/2.0f) +   y * ((float)vpHeight/2.0f);
   return res; 
}


};

 //! \brief Вьюпорт  Область вывода  по координате и размерам. 
 struct vieport_s  {

   unsigned int  x; ///< координата по X (по гризонтали)
   unsigned int  y; ///< координата по Y (по вертикали)
   
   unsigned int  width;  ///< ширина
   unsigned int  height; ///< высота
 
 };
  
  
  //! \brief  Расширеная область вывода с добавлением min и max для Z .
 class ViewportZ : public vieport_s  {
  public:

      float minZ;
      float maxZ;
      
#ifdef _D3D9_H_
   inline ViewportZ (const D3DVIEWPORT9& vp) { *this = vp; }
#endif

  
  #ifdef _D3D9_H_
   inline void operator = (const D3DVIEWPORT9& vp)
   {
    x = (unsigned int)vp.X;
    y = (unsigned int)vp.Y;   
	
	width  = (unsigned int)vp.Width;
    height = (unsigned int)vp.Height;

	minZ = vp.MinZ;
	maxZ = vp.MaxZ;
   }

   inline operator const D3DVIEWPORT9& () const 
   {
     return (D3DVIEWPORT9&)*this;
   }
   
   //! \brief ПРисвоить координаты, ширину и высоту в  D3DVIEWPORT9    УБРАТЬ !!!!!
   inline void to_d3d9Viewport(D3DVIEWPORT9& vpInOut) const
   {
    vpInOut.X = (DWORD)x;
	vpInOut.Y = (DWORD)y;
	
	vpInOut.Width  = (DWORD)width;
	vpInOut.Height = (DWORD)height;

	vpInOut.MinZ = minZ;
	vpInOut.MaxZ = maxZ;
	}
  #endif  // #ifdef _D3D9_H_
  
  
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