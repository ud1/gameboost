/** \file
 \brief Для внутреннего использования.

*/

#pragma once



/*
#ifndef	 __GB_D3D9_MDXUTGUI_H__
   #error
#endif
*/

#pragma warning(disable : 4996)
#pragma warning(disable : 4995)

#include <strsafe.h>

#include <stdexcept>


inline int RectWidth( RECT &rc ) 
{
	return ( (rc).right - (rc).left ); 
}

inline int RectHeight( RECT &rc ) 
{ 
	return ( (rc).bottom - (rc).top ); 
}


double getGlobalTime();
HWND getGlobalHwnd();
void setGlobalHwnd(HWND h);
bool getGlobalAutomation();
IDirect3DDevice9* getGlobalDevice();
void setGlobalDevice(IDirect3DDevice9* pdevice);


HRESULT  CreateGUITextureFromInternalArray( IDirect3DDevice9* pdevice, 
										    IDirect3DTexture9** ppTexture,
										    const  D3DXIMAGE_INFO* info);



// temp  ВРЕМЕННО !!!
#define MYUT_ERR(m,hr)       (hr);

#ifdef _DEBUG
#define V_RETURN(hr)  if FAILED(hr) { throw std::runtime_error("pizdets prishol");  };
#else
#define V_RETURN(hr)  if FAILED(hr) { return hr; };
#endif

#define DXTRACE_ERR(msg,hres)   (hres)
#define DXTRACE_ERR_MSGBOX(wmsg,herr)    (herr)
#define MYUTTRACE(msg)





// end file