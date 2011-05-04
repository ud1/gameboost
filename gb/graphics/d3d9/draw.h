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
		 
//-------------------------------------------------------------------------


/** \brief   Отрисовка сети куба  с координатами вершин от (-1,-1,-1)  до (1,1,1)
 имеющем текстурные координаты, 
из вершинного буфера расположеного в памяти CPU методом DrawIndexedPrimitiveUP .  
  Можно использовать для отладочного вывода кубика или отрисовки окружения.  */		 
GB_D3D9_API HRESULT drawMeshPrimitiveCube1x1Mem(IDirect3DDevice9* pdevice);

		 
/** \brief   Отрисовка сети  квадрата  координатами вершин от (-1,-1,-1)  до (1,1,1) 
   выровненого по оси Z   имеющем текстурные координаты, из вершинного буфера 
    расположеного в памяти CPU методом DrawIndexedPrimitiveUP .   
	Можно использовать для выполнения постпроцессов, билбоардов и др.  */			 
GB_D3D9_API HRESULT drawMeshPrimitiveQuadXyMem(IDirect3DDevice9* pdevice);		 
		 
	
//! \brief Отрисовать  прямоугольник  
GB_D3D9_API HRESULT  DrawScreenQuad( IDirect3DDevice9* pdevice,  
									const RECT& rect, 
									const D3DCOLORVALUE& color );

//! \brief Отрисовать  прямоугольник   в полноэкранный экран на весь бэкбуфер.
GB_D3D9_API HRESULT  DrawFullScreenQuad( IDirect3DDevice9* pdevice, 
										const D3DCOLORVALUE& color);

//! \brief  полноэкранный прямоугольник
GB_D3D9_API HRESULT DrawScreenPoint(IDirect3DDevice9* pdevice, 
									const D3DCOLORVALUE& color,
									float x, float y, int pointSize); 


//! \brief Нарисовать точки
GB_D3D9_API HRESULT  DrawScreenPoints(IDirect3DDevice9* pdevice,
									  const D3DCOLORVALUE& color,
									  const float* vec2_arrayCoord, 
									  int num, 
									  int pointSize);  

//! \brief Нарисовать линии по точкам
GB_D3D9_API HRESULT  DrawScreenLines(IDirect3DDevice9* pdevice, 
									 const D3DCOLORVALUE& color, 
									 const float* vec2_arrayCoord,
									 int num);

//! \brief Нарисовать окружность
GB_D3D9_API HRESULT DrawScreenCircle(IDirect3DDevice9* pdevice, 
									 const D3DCOLORVALUE& color,
									 float x, float y, 
									 float radius);


//! \brief Нарисовать прямоугольник
GB_D3D9_API HRESULT  DrawScreenRect(IDirect3DDevice9* pdevice, 
									const D3DCOLORVALUE& color,
									float x1, float y1, 
									float x2, float y2 )  ;




















//-------------------------------------------------------------------------

   } // end namespace draw
  } // end namespace d3d9
 } // end namespace graphics
} // end ns gb

#endif
// end file