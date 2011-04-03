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


#include <gb/math/scalar.h>
#include <gb/math/base.h>
#include <gb/math/geom3d.h>
#include <gb/math/geom2d.h>

#include <d3d9.h>


//* пока это пустышка.  Спецификация экспорта функций. 
#define GB_D3D9_API


namespace gb 
{
 namespace graphics 
 {
 
  //! \brief Рендеринг через d3d9. Сопутствующие типы, классы, функции и т.д.
  namespace d3d9 
  {

//--------------------------------------------------------------------------------------



  
  
  
//--------------------------------------------------------------------------------------  

  } // end ns d3d9
 } // end ns graphics
} // end ns gb

#endif // #if
// end file