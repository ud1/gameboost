/**   \file 
 \brief ����� �� ������ ���������� ���������� d3d9. ��� ���������� ���������  ����.


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


      /** \brief ����� �� ������ ���������� ���������� d3d9. ��� ���������� ���������  ����. */
	  class Device {
	  public:
		  IDirect3DDevice9* dvc; /// ��������� �� ����������.

		  inline Device(IDirect3DDevice9* pdevice) : dvc(pdevice)     {}
		  inline Device(const Device& device)      : dvc(device.dvc)  {}

          //! \brief "����������" ��������� ��������� �� ����������.
		  inline IDirect3DDevice9* operator -> () const { return dvc; }
 

//! \brief  ������ ������� ������� ����� ��������� ����� .
inline HRESULT �learFull(D3DCOLOR color=0) { return dvc->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0); }
//! \brief ������� ������ Z-������ .
inline HRESULT �learZBuffer() {  return dvc->Clear(0, NULL,  D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);  }
//! \brief ������� ������  ����������� ����������.
inline HRESULT �learTraget(D3DCOLOR color) { return dvc->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0); }
//! \brief ��������� ������������� ������ ������� �������.  
inline HRESULT clearRect(const D3DRECT& rec, const D3DCOLORVALUE& col) { return dvc->Clear(1 ,  &rec , D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(col.r, col.g, col.b, col.a), 1.0f, 0); }



//! \brief ��������/��������� Z-�����
inline HRESULT set_Zenable      (bool val) { if(val) return dvc->SetRenderState(D3DRS_ZENABLE,1); return dvc->SetRenderState(D3DRS_ZENABLE,0); }
//! \brief ��������/��������� ������ � Z-�����
inline HRESULT set_ZWriteEnable (bool val) { if(val) return dvc->SetRenderState(D3DRS_ZWRITEENABLE,1); return dvc->SetRenderState(D3DRS_ZWRITEENABLE,0); }

//! \brief   ��������/��������� �����-����������.
inline HRESULT set_AlphaBlendeble(bool val) {if(val) return dvc->SetRenderState(D3DRS_ALPHABLENDENABLE,1); return dvc->SetRenderState(D3DRS_ALPHABLENDENABLE,0); }


//! \brief ��������� ��������������� �� ����������� ����� 
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




/** \brief ���������� � ������ �������������. � ������ �������� ����� �������� NULL ���� �������� �� �����. */
inline HRESULT setTransform(const D3DMATRIX* mWorld, const D3DMATRIX* mView, const D3DMATRIX* mProj)
{
	HRESULT hr =0;
	if(mWorld) hr|=dvc->SetTransform(D3DTS_WORLD,  mWorld );
	if(mView)  hr|=dvc->SetTransform(D3DTS_VIEW, mView  );
	if(mProj)  hr|=dvc->SetTransform(D3DTS_PROJECTION,  mProj );
	return hr;
}

//! \brief �������� ������������� �� ����������.  � ������ �������� ����� �������� NULL ���� �������� �� �����.
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