/**   \file 
 \brief Класс на основе интерфейса устройства d3d9. Для облегчения написания  кода.


  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once
#define __GB_D3D9_DEVICE_H__

#include <gb/base/Types.h>
#include <gb/config.h>

#include <d3d9.h>

namespace gb 
{
 namespace graphics 
 {
  namespace d3d9 
  {
 
//--------------------------------------------------------------------------


      /** \brief Класс на основе интерфейса устройства d3d9. Для облегчения написания  кода. */
	  class Device {
	  public:
		  IDirect3DDevice9* dvc; /// Указатель на устройство.

		  inline Device(IDirect3DDevice9* pdevice) : dvc(pdevice)     {}
		  inline Device(const Device& device)      : dvc(device.dvc)  {}

          //! \brief "стрелочкой" получение указателя на устройство.
		  inline IDirect3DDevice9* operator -> () const { return dvc; }
 

//! \brief  ПОЛНАЯ ОЧИСТКА девайса перед отрисовка кадра .
inline HRESULT сlearFull(D3DCOLOR color=0) { return dvc->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0); }
//! \brief Очистка только Z-буфера .
inline HRESULT сlearZBuffer() {  return dvc->Clear(0, NULL,  D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);  }
//! \brief Очистка только  поверхности устройства.
inline HRESULT сlearTraget(D3DCOLOR color) { return dvc->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0); }
//! \brief Заполнить прямоугольник цветом методом очистки.  
inline HRESULT clearRect(const D3DRECT& rec, const D3DCOLORVALUE& col) { return dvc->Clear(1 ,  &rec , D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(col.r, col.g, col.b, col.a), 1.0f, 0); }



//! \brief включить/отключить Z-буфер
inline HRESULT set_Zenable      (bool val) { if(val) return dvc->SetRenderState(D3DRS_ZENABLE,1); return dvc->SetRenderState(D3DRS_ZENABLE,0); }
//! \brief включить/отключить запись в Z-буфер
inline HRESULT set_ZWriteEnable (bool val) { if(val) return dvc->SetRenderState(D3DRS_ZWRITEENABLE,1); return dvc->SetRenderState(D3DRS_ZWRITEENABLE,0); }

//! \brief   включить/выключить альфа-смешивание.
inline HRESULT set_AlphaBlendeble(bool val) {if(val) return dvc->SetRenderState(D3DRS_ALPHABLENDENABLE,1); return dvc->SetRenderState(D3DRS_ALPHABLENDENABLE,0); }


//! \brief Включение альфасмешивания по стандартной схеме 
inline HRESULT set_EnableStdAlphaBlending() 
{
	HRESULT hr =  dvc->SetRenderState(D3DRS_ALPHABLENDENABLE,1);
	hr |=         dvc->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	hr |=         dvc->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA); 
	return hr;
};

inline HRESULT set_CullModeNone() {	return dvc->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE ); }
inline HRESULT set_CullModeCW()   { return dvc->SetRenderState( D3DRS_CULLMODE , D3DCULL_CW   ); }
inline HRESULT set_CullModeCCW()  { return dvc->SetRenderState( D3DRS_CULLMODE , D3DCULL_CCW  ); }




/** \brief Установить в девайс трансформацию. В каждый параметр можно передать NULL если изменять не нужно. */
inline HRESULT setTransform(const D3DMATRIX* mWorld, const D3DMATRIX* mView, const D3DMATRIX* mProj)
{
	HRESULT hr =0;
	if(mWorld) hr|=dvc->SetTransform(D3DTS_WORLD,  mWorld );
	if(mView)  hr|=dvc->SetTransform(D3DTS_VIEW, mView  );
	if(mProj)  hr|=dvc->SetTransform(D3DTS_PROJECTION,  mProj );
	return hr;
}

//! \brief Получить трансформацию из устройства.  В каждый параметр можно передать NULL если получать не нужно.
inline HRESULT getTransform( D3DMATRIX* mOutWorld, D3DMATRIX* mOutView, D3DMATRIX* mOutProj )
{
	HRESULT hr =0;
	if(mOutWorld) hr|=dvc->GetTransform(D3DTS_WORLD,  mOutWorld );
	if(mOutView)  hr|=dvc->GetTransform(D3DTS_VIEW, mOutView  );
	if(mOutProj)  hr|=dvc->GetTransform(D3DTS_PROJECTION,  mOutProj );
    return hr;
}












	  };
	  // end class





//-------------------------------------------------------------------------- 

  } // end ns d3d9
 } // end ns graphics
} // end ns gb

#endif // #if ( defined(GB_D3D9) && defined(WIN32) )
// end file