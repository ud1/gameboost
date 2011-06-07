/** \file
*   \brief функции, типы D3D9 связаные с выводом вершин  
*      и прочих вспомогательных объектов.
*


  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586

  \todo   Добавлять отрисовку сетей.

*/



//#if ( defined(GB_D3D9) && defined(WIN32) )
#if ( defined(WIN32) && defined(_D3D9_H_) )
						  
#pragma once
#define __GB_D3D9_DRAW_H__
 
//#include <d3d9.h>

#include <gb/graphics/d3d9/api_decl.h>
#include <gb/graphics/d3d9/auto_include_libr.h> 

//#include <gb/graphics/d3d9/common.h>


 

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


namespace gb 
{
 namespace graphics 
 {
  namespace d3d9 
  {

   //! \brief функции, типы D3D9 связаные с выводом вершин, визуальных примитивов и прочего
   namespace draw
   {
	
//-------------------------------------------------------------------------

/** \brief Удалить все ресурсы , которые создаёт эта часть библиотеки изнутри.
 
  ОБЯЗАТЕЛЬНО ВЫЗВАТЬ ПРИ :  потере, сбросе или удалении девайса  */
GB_D3D9_API HRESULT ReleaseAllInternalData();
 

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




 //! \brief   Нарисовать наклонный маркер экранной точки.
GB_D3D9_API  HRESULT DrawScreenMarkerObl(IDirect3DDevice9* pdevice, 
										float x, float y, 
										float size,
										D3DCOLOR color);
 

//! \brief  Нарисовать вертикальный маркер экранной точки. 
GB_D3D9_API  HRESULT DrawScreenMarker(IDirect3DDevice9* pdevice,  
									 float x, float y,  
									 float size, 
									 D3DCOLOR color);



//------------------------------------

//! \brief  Нарисовать точки в 3d
GB_D3D9_API HRESULT Draw3dPoints(
					 IDirect3DDevice9* pdevice, 
					 const float* vec3Array_coord,
					 int num, 
					 float pointSize, 
					 D3DCOLOR color );



//! \brief  Нарисовать линии в 3d
GB_D3D9_API HRESULT Draw3dLines( IDirect3DDevice9* pdevice, 
								const float* vec3_coord, 
								int num,  D3DCOLOR color );


//! \brief  Нарисовать луч в 3d
GB_D3D9_API HRESULT Draw3dRay(IDirect3DDevice9* pdevice,
							  const float* vec3_orig, 
							  const float* vec3_normal, 
							  D3DCOLOR color);



//! \brief  Нарисовать треугольник в 3d
GB_D3D9_API HRESULT  Draw3dTraingle(
					IDirect3DDevice9* pdevice,
					const float* vec3_v1, 
					const float* vec3_v2, 
					const float* vec3_v3,
					D3DCOLOR color ); 


//! \brief  Нарисовать в 3d  бокс по мин и макс точкам  .
GB_D3D9_API HRESULT Draw3dAxiesAlignBoundBox(IDirect3DDevice9* pdevice,
								 const float* vec3_min, 
								 const float* vec3_max,
								 D3DCOLOR color ); 
 

//! \brief Нарисовать коррдинатные оси в 3d	 .
GB_D3D9_API HRESULT Draw3dAxies(IDirect3DDevice9* pdevice, 
								const float* vec3_coord, float  axiesLen);


//-------------------------------------------------------------------------

GB_D3D9_API HRESULT DrawStr(
				IDirect3DDevice9* pdevice,
				int x, 
				int y, 
				const char* str, 
				D3DCOLOR color
							);



GB_D3D9_API HRESULT DrawStrFormat(
			  IDirect3DDevice9* pdevice, 
			  int x, int y, 
			  D3DCOLOR color, 
			  const char *_Format, ...
								  );
//! \brief  Размер шрифта для DrawStrEx
struct FontSize_e 
{
	  enum e
	  {
		 NORMAL = 0,
		 BIG    = 1,
		 SMALL  = 2
	  };
};

GB_D3D9_API HRESULT DrawStrEx(
							IDirect3DDevice9* pdevice,
							int x, 
							int y,
							FontSize_e::e fontSize,
							const char* str, 
							D3DCOLOR color
							);



//-----------------------------------------------------------------


GB_D3D9_API  IDirect3DTexture9* getSampleDebugTexture(IDirect3DDevice9* pdevice)  throw();



/**************************************************************
	// тестирочовный код для draw3d пока здесь.. 


	mat44 mview;
	mview.setViewLookAtLH( 
	vec3( sin(fTime)*10.0f , 10.0f , cos(fTime)*10.0f ),
	vec3(0.0f, 0.0f, -0.0f), 
	vec3(0.0f,1.0f,0.0f)   
	) ;
	hr |= mview.makeDevice9TransfView( pd3dDevice );

	mat44 mproj;
	mproj.setPerspectiveFovLH( gb::fmath::constan::CPI/4.0f, 1.0f, 0.1f, 1000.0f );
	hr |= mproj.makeDevice9TransfProj(pd3dDevice);

	mat44 mworld(1.0f);
	hr |= mworld.makeDevice9TransfWorld(pd3dDevice);




	gb::fmath::vec3 varr[4];

	//Draw3dPoints

	varr[0] = vec3( 5.04f , 1.25f , 3.45f   );
	varr[1] = vec3( 1.04f , 3.25f , -1.45f   );
	varr[2] = vec3( 0.04f , 0.25f , 4.45f   );
	varr[3] = vec3( -2.04f , -2.25f , 2.45f   );

	hr |= Draw3dPoints(pd3dDevice, varr[0], 4, 4,  0-1 );

	// Draw3dPoints
	hr |= Draw3dLines(pd3dDevice, varr[0], 4, 0xffff0000 );

	// Draw3dRay
	varr[0] = vec3(0.0f, 0.0f, 0.0f  );
	varr[1] = vec3( 0.15f, 0.8f , -0.2f  );

	hr |= Draw3dRay(pd3dDevice, varr[0], varr[1], 0xff00ff00 );


	// Draw3dTraingle

	varr[0] = vec3( 1.0f , 1.5f , 2.45f  );
	varr[1] = vec3( 2.0f , 1.8f , 3.45f  );
	varr[2] = vec3( 1.56f , -1.45f , 5.43f  );

	hr |= Draw3dTraingle(pd3dDevice, varr[0], varr[1], varr[2], 0xffffff00 );


	// Draw aabb

	varr[0] = vec3( -1.45f , -2.48f, 0.36f  );
	varr[1] = vec3(  2.45f ,  1.65f, 3.26f  );
	hr |= Draw3dAxiesAlignBoundBox(pd3dDevice, varr[0] , varr[1],  0xff00ff00 );


	// draw axies
	varr[0] = vec3( 0.2f , 0.2f , 0.2f );
	hr |= Draw3dAxies( pd3dDevice,  varr[0], 5.0f );



**************************************************************/




//-------------------------------------------------------------------------

   } // end namespace draw
  } // end namespace d3d9
 } // end namespace graphics
} // end namespace gb

#endif
// end file