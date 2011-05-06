/** \file d3d9.h
* \brief Вывод графики через D3D9
*
*
*
  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/


#if ( defined(GB_D3D9) && defined(WIN32) )
 

#pragma once
#define __GB_D3D9_H__

#include <gb/config.h>
#include <gb/base/Types.h>

#include <d3d9.h>
	  

#ifdef GB_COLOR
   #include <gb/color/color.h>
#endif

#ifdef GB_MATH
  #include <gb/math/math.h>
#endif



//! \brief  пока это пустышка.  Спецификация экспорта функций. 
#define GB_D3D9_API

#pragma warning (disable:4995)

#include <gb/graphics/d3d9/auto_include_libr.h>

#include <gb/graphics/d3d9/dataconv.h>
#include <gb/graphics/d3d9/Device.h>
#include <gb/graphics/d3d9/draw.h>
#include <gb/graphics/d3d9/fvf.h>
#include <gb/graphics/d3d9/hlsl/hlsl.h>
#include <gb/graphics/d3d9/d3dFont.h>

#include <gb/graphics/d3d9/render/render.h>


namespace gb 
{
 namespace graphics 
 {
 
  //! \brief Рендеринг через d3d9. Сопутствующие типы, классы, функции и т.д.
  namespace d3d9 
  {

//-------------------------------------------------------------------------



  
  
  
//-------------------------------------------------------------------------  

  } // end ns d3d9
 } // end ns graphics
} // end ns gb

 
#endif // #if ( defined(GB_D3D9) && defined(WIN32) )

// end file