/**   \file Device.h
 \brief Класс на основе интерфейса устройства d3d9. Для облегчения написания  кода.



  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#if ( defined(WIN32) && defined(GB_D3D9)  )
 
 

#pragma once
#define __GB_D3D9_DEVICE_H__


#include <gb/config.h>
#include <gb/base/Types.h>

#include <d3d9.h>

#include <stdexcept>

#ifdef GB_MATH
  #include <gb/math/math.h>
  using namespace gb::math::base;
  using namespace gb::math::geom3d;
#endif

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
inline HRESULT clearFull(D3DCOLOR color=0) { return dvc->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0); }
//! \brief Очистка только Z-буфера .
inline HRESULT clearZBuffer() {  return dvc->Clear(0, NULL,  D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);  }
//! \brief Очистка только  поверхности устройства.
inline HRESULT clearTarget(D3DCOLOR color) { return dvc->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0); }
 

//! \brief Заполнить прямоугольник цветом методом очистки.  
inline HRESULT clearRect(const D3DRECT& rec, const D3DCOLORVALUE& col) { return dvc->Clear(1 ,  &rec , D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(col.r, col.g, col.b, col.a), 1.0f, 0); }

 

//! \brief включить/отключить Z-буфер
inline HRESULT set_Zenable      (bool val) { if(val) return dvc->SetRenderState(D3DRS_ZENABLE,1); return dvc->SetRenderState(D3DRS_ZENABLE,0); };
//! \brief включить/отключить запись в Z-буфер
inline HRESULT set_ZWriteEnable (bool val) { if(val) return dvc->SetRenderState(D3DRS_ZWRITEENABLE,1); return dvc->SetRenderState(D3DRS_ZWRITEENABLE,0); };

//! \brief   включить/выключить альфа-смешивание.
inline HRESULT set_AlphaBlendeble(bool val) {if(val) return dvc->SetRenderState(D3DRS_ALPHABLENDENABLE,1); return dvc->SetRenderState(D3DRS_ALPHABLENDENABLE,0); };

inline bool get_Zenable() const  {
	DWORD val;
	HRESULT hr = dvc->GetRenderState(D3DRS_ZENABLE, &val);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	if(val) return true;   return false;
}

inline bool get_ZWriteEnable() const  {
	DWORD val;
	HRESULT hr = dvc->GetRenderState(D3DRS_ZWRITEENABLE, &val);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	if(val) return true;   return false;
}

inline bool get_AlphaBlendeble() const  {
	DWORD val;
	HRESULT hr = dvc->GetRenderState(D3DRS_ALPHABLENDENABLE, &val);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	if(val) return true;   return false;
}

HRESULT setFillMode_POINT()      { return dvc->SetRenderState(D3DRS_FILLMODE,  D3DFILL_POINT); }
HRESULT setFillMode_WIREFRAME()  { return dvc->SetRenderState(D3DRS_FILLMODE,  D3DFILL_WIREFRAME); }
HRESULT setFillMode_SOLID()      { return dvc->SetRenderState(D3DRS_FILLMODE,  D3DFILL_SOLID); }


 


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

inline HRESULT get_CullMode() const {
	D3DCULL val;
	HRESULT hr=dvc->GetRenderState( D3DRS_CULLMODE , (DWORD*)&val );
	return val;
}


#ifdef GB_MATH

inline mat44_s getTransformWorld() const {
	mat44_s res;
	HRESULT hr=dvc->GetTransform( D3DTS_WORLD , res );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
}

inline mat44_s getTransformView() const {
	mat44_s res;
	HRESULT hr=dvc->GetTransform( D3DTS_VIEW , res );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
}

inline mat44_s getTransformProj() const {
	mat44_s res;
	HRESULT hr=dvc->GetTransform( D3DTS_PROJECTION , res );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
}

#endif // GB_MATH

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


inline D3DMATERIAL9 getMaterial() const {
    D3DMATERIAL9 res;
	HRESULT hr = dvc->GetMaterial(&res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
}

HRESULT setMaterial(const D3DMATERIAL9& mat) const {
	HRESULT hr = dvc->SetMaterial( (D3DMATERIAL9*)&mat.Diffuse.r );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return  hr;
}

RECT getScissorRect() const  {
	RECT res;
	HRESULT hr = dvc->GetScissorRect(&res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
    return res;
}

HRESULT setScissorRect(const RECT& r) {
	 RECT rect = r;
	 HRESULT hr = dvc->SetScissorRect(&rect);
};

UINT getStreamSourceFreq(UINT StreamNumber) {
    UINT res = 0;
	HRESULT hr = dvc->GetStreamSourceFreq(StreamNumber, &res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};


IDirect3DSurface9* getBackBuffer() {
   IDirect3DSurface9* res = NULL;
   HRESULT hr = dvc->GetBackBuffer( 0 , 0, D3DBACKBUFFER_TYPE_MONO, &res  );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};

D3DSURFACE_DESC getBackBufferDescr() {
  D3DSURFACE_DESC res;
    IDirect3DSurface9* pbbuf = getBackBuffer();
	HRESULT hr = pbbuf->GetDesc(&res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};


 
/*************************
#ifdef GB_MATH

plane_s getClipPlane(DWORD index) {
	plane_s res;
	HRESULT hr = dvc->GetClipPlane( index , res );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};

HRESULT  setClipPlane(DWORD index, const plane_s& pln) {
	HRESULT hr = dvc->SetClipPlane( index, &pln.a );
	return hr;
};

#endif   // #ifdef GB_MATH
*******************************/ 
 

class StreamSourceData {
public:
	const UINT nStreamNumber;
	IDirect3DVertexBuffer9* pStreamData;
	UINT nOffsetInBytes;
	UINT nStride;

	StreamSourceData(UINT _nStreamNumber) :nStreamNumber(_nStreamNumber)  
	{ 
		 nOffsetInBytes=nStride=0; pStreamData=NULL; 
	}

	StreamSourceData(const StreamSourceData& ssd) : nStreamNumber(ssd.nStreamNumber)
	{
		pStreamData = ssd.pStreamData;
		nOffsetInBytes = ssd.nOffsetInBytes;
		nStride = ssd.nStride;
	}


};


StreamSourceData getStreamSourceData(UINT nStreamNumber) const {
	StreamSourceData res(nStreamNumber);
	HRESULT hr = dvc->GetStreamSource(res.nStreamNumber, &res.pStreamData, &res.nOffsetInBytes, &res.nStride);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
}

HRESULT setStreamSourceData(const StreamSourceData& ssd) {
	HRESULT hr = dvc->SetStreamSource(ssd.nStreamNumber, ssd.pStreamData, ssd.nOffsetInBytes, ssd.nStride);
	return hr;
};


DWORD getFvf() const {
	DWORD res;
	HRESULT hr = dvc->GetFVF(&res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
} 

IDirect3DIndexBuffer9* getIndexBuffer() const {
	IDirect3DIndexBuffer9* res;
	HRESULT hr = dvc->GetIndices( &res );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res; 
};


HRESULT setIndexBuffer(IDirect3DIndexBuffer9 * pIndxBuffer) const {
   return dvc->SetIndices(pIndxBuffer);
}; 

D3DLIGHT9 getLight(DWORD index) const  {
    D3DLIGHT9 res;
	HRESULT hr = dvc->GetLight(index, &res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};


HRESULT setLight(DWORD indx, const D3DLIGHT9& lght) {
    HRESULT hr = setLight(indx, lght);
    return hr;
};

bool getLightEnable( DWORD index ) const {
	BOOL res = FALSE;
	HRESULT hr = dvc->GetLightEnable(index, &res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	if(res) return true; return false;
}; 

HRESULT setLightEnable( DWORD index, bool val ) const {
	BOOL res = FALSE;
	HRESULT hr = dvc->LightEnable( index, (BOOL)val );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return hr;
}; 

 
BOOL getVertexShaderConstBool(UINT nStartRegister) {
	BOOL res;
	HRESULT hr = dvc->GetVertexShaderConstantB( nStartRegister, &res, 1 );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
}

#ifdef GB_MATH

vec4_s getVertexShaderConstVec4(UINT nStartRegister) {
	vec4_s res;
	HRESULT hr = dvc->GetVertexShaderConstantF(nStartRegister , res, 1);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};

mat44_s getVertexShaderConstMatrix4x4(UINT nStartRegister) {
	mat44_s res;
	HRESULT hr = dvc->GetVertexShaderConstantF(nStartRegister , res,  4 );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};


HRESULT getVertexShaderConstMatrix4x4_arg(mat44_s* pmOut, UINT nStartRegister) {
	HRESULT hr = dvc->GetVertexShaderConstantF(nStartRegister , &pmOut->_11,  4 );
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return  hr;
};

#endif // GB_MATH



// =============== end shaders ==========================


D3DVIEWPORT9 getViewport() {
	D3DVIEWPORT9 res;
	HRESULT hr = dvc->GetViewport(&res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};

HRESULT setViewport(const D3DVIEWPORT9& vp) {
	HRESULT hr = dvc->SetViewport( (D3DVIEWPORT9*)&vp.X);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return hr;
};

IDirect3DBaseTexture9* getTexture(DWORD nStage) const {
   IDirect3DBaseTexture9* res= NULL;
	HRESULT hr = dvc->GetTexture(nStage, &res);
	if FAILED(hr) throw std::runtime_error("Failed operation");
	return res;
};

HRESULT setTexture(DWORD nStage, IDirect3DBaseTexture9* pTxtr) {
   HRESULT hr = dvc->SetTexture( nStage, pTxtr);
   if FAILED(hr) throw std::runtime_error("Failed operation");
   return  hr;
};

 


 








	  };
	  // end class





//------------------------------------------------------------------------- 

  } // end namespace d3d9
 } // end namespace graphics
} // end namespace gb


#endif  // #if ( defined(WIN32) && defined(GB_D3D9)  )
// end file