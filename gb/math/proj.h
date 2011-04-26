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
  
  
	  struct ProjectionData
	  {
		float fovy;
		float aspect;
		float zn;
		float zf;
	  };

  
  
  //! \brief Вьюпорт  Область вывода .
  struct Viewport {
  public:
  
   unsigned int  x; ///< координата по X (по гризонтали)
   unsigned int  y; ///< координата по Y (по вертикали)
   
   unsigned int  width;  ///< ширина
   unsigned int  height; ///< высота
    
  
  
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