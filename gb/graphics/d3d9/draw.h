/** \file
 \brief функции, типы D3D9 связаные с выводом вершин
*
*
*
*
  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#if ( defined(GB_D3D9) && defined(WIN32) )


#pragma once
#define __GB_D3D9_DRAW_H__

#include <gb/graphics/d3d9/common.h>



namespace gb 
{
   namespace graphics 
   {
      namespace d3d9 
	  {
	     //! \brief функции, типы D3D9 связаные с выводом вершин
	     namespace draw
		 {
		 
		 
/** \brief   Отрисовка сети куба  с координатами вершин от (-1,-1,-1)  до (1,1,1)  имеющем текстурные координаты, 
из вершинного буфера расположеного в памяти CPU методом DrawIndexedPrimitiveUP .  
  Можно использовать для отладочного вывода кубика или отрисовки окружения.  */		 
GB_D3D9_API HRESULT drawMeshPrimitiveCube1x1Mem(IDirect3DDevice9* pdevice);

		 
/** \brief   Отрисовка сети  квадрата  координатами вершин от (-1,-1,-1)  до (1,1,1) 
   выровненого по оси Z   имеющем текстурные координаты, из вершинного буфера 
    расположеного в памяти CPU методом DrawIndexedPrimitiveUP .   
	Можно использовать для выполнения постпроцессов, билбоардов и др.  */			 
GB_D3D9_API HRESULT drawMeshPrimitiveQuadXyMem(IDirect3DDevice9* pdevice);		 
		 
		 
		 } // end ns draw
      } // end ns d3d9
   } // end ns graphics
} // end ns gb

#endif
// end file