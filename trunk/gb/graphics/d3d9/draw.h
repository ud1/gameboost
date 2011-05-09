/** \file
*   \brief функции, типы D3D9 связаные с выводом вершин  
*      и прочих вспомогательных объектов.
*
*
*
*

  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/



#if ( defined(GB_D3D9) && defined(WIN32) )

						  
#pragma once
#define __GB_D3D9_DRAW_H__

#include <windows.h>

#include <d3d9.h>

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


#define GB_D3D9_API


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

//! \brief Отрисовать  прямоугольник 
inline HRESULT DrawScreenQuad( IDirect3DDevice9* pdevice,  
							  int x1, int y1, int x2, int y2, 
							  const D3DCOLORVALUE& color )
{
	RECT rect; ::SetRect(&rect, x1, y1, x1, y2);
	return DrawScreenQuad(pdevice, rect, color);
};

//! \brief Отрисовать  прямоугольник   в полноэкранный экран на весь бэкбуфер.
GB_D3D9_API HRESULT  DrawFullScreenQuad( IDirect3DDevice9* pdevice, 
										const D3DCOLORVALUE& color);

//! \brief Нарисовать точку
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


//! \brief  Отрисовка экранного квадрата по текстуре, позиции , текстурным координатам, цветам вершин.
GB_D3D9_API  HRESULT  DrawTexturedMemQuad( IDirect3DDevice9* pdevice, 
										   IDirect3DTexture9 *pTexture ,
								     	    const RECT& recScreen,
										    const RECT& recTexture,
										      const D3DCOLOR cLeftTop,
										      const D3DCOLOR cRightTop,
										      const D3DCOLOR cLeftBottom,
										      const D3DCOLOR cRightBottom
										    );




 //! \brief   Нарисавать наклонный маркер экранной точки.
GB_D3D9_API  HRESULT DrawScreenMarkerObl(IDirect3DDevice9* pdevice, 
										float x, float y, 
										float size,
										D3DCOLOR color);
 

//! \brief  Нарисовать маркер вертикальной точки расположеный верникально. 
GB_D3D9_API  HRESULT DrawScreenMarker(IDirect3DDevice9* pdevice,  
									 float x, float y,  
									 float size, 
									 D3DCOLOR color);





//-------------------------------------------------------------------------

   } // end namespace draw
  } // end namespace d3d9
 } // end namespace graphics
} // end ns gb

#endif
// end file