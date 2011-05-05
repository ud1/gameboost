// Пример использования dxut_wonly
//
#include "stdafx.h"

#include <ce/dxut_wonly/dxut_wonly.h>
#include <gb/graphics/d3d9/d3d9.h>
using namespace gb::graphics::d3d9;


#include <gb/macro.h> 

#ifndef GB_MATH
#define GB_MATH
#endif

#include <gb/math/math.h>
using namespace gb::math::base;



D3dFont* g_pfont = NULL;

D3dFont* g_pFontSmall = NULL;



//--------------------------------------------------------------------------------------
// Rejects any devices that aren't acceptable by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, 
								 D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
	// Typically want to skip backbuffer formats that don't support alpha blending
	IDirect3D9* pD3D = DXUTGetD3DObject(); 
	if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
		AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
		D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
		return false;

	return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )
{
	return true;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_MANAGED resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_DEFAULT resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
							   const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{

	if(g_pfont)
	{
		//g_pfont->InvalidateDeviceObjects();
	}




	return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
}

HRESULT test_drawText(IDirect3DDevice9* pd3dDevice)
{
	HRESULT hr =0;

	hr |=  g_pfont->DrawTextW(100, 100, 0xFFFFFFFF, L"sample string bla font ohoho",  0   );
 	hr |=  g_pfont->DrawTextW(100, 120, 0xFFFFFFFF, L"Русский текст WCHAR ",  0   );

 	hr |=  g_pfont->DrawTextA(100, 140, 0xFFFFFFFF,  "Ansi string text 0134568+-/*",  0   );
 	hr |=  g_pfont->DrawTextA(100, 160, 0xFFFFFFFF,  "Русский текст",  0   );


	hr |= g_pFontSmall->DrawTextW(100, 200.0f, 0-1, L"fdsf 0123456789/*-+*)(*&^ d1548$*&$^&^",  0);


	return hr;
}





inline bool IsVirtualKeyDown(int nVirtKey) {
	return (bool)(GetKeyState( nVirtKey )>>8); 
}


HRESULT test_drawText_dowble(IDirect3DDevice9* pd3dDevice)
{
	HRESULT hr =0;
   	hr |=  g_pfont->DrawTextBackgrA(345, 456, 3, 0-1, 0xff555555, "string string");
	return hr;
}



HRESULT test_DrawTextScaled(IDirect3DDevice9* pd3dDevice, double fTime )
{
	HRESULT hr =0;

	mat44_s m;
	m.reset();
	m.setViewLookAtLH( vec3_s(8.0f, 0.0f,0.0f  ) , vec3_s(-0.0f, -0.0f,0.0f ), vec3_s(0.0f, 1.0f, 0.0f  ) );
	hr |= m.makeDevice9TransfView(pd3dDevice) ;

	m.setPerspectiveFovLH(1.5f, 1.0f, 0.1f, 1000.0f);
	hr |= m.makeDevice9TransfProj(pd3dDevice);

	m.setTranslation(0.0f, 0.0f, 0.0f);
  	hr |= m.makeDevice9TransfWorld(pd3dDevice);



//  hr |=  g_pFontSmall->DrawTextScaled(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0-1, L"simplesacledtext", 0 )	;


	return hr;
}

HRESULT test_render3dText(IDirect3DDevice9* pd3dDevice) 
{ 
	HRESULT hr =0;

	Device dvc(pd3dDevice);
	dvc.setFillMode_WIREFRAME();
	gb::graphics::d3d9::draw::drawMeshPrimitiveCube1x1Mem(pd3dDevice);



	mat44_s m;
	m.reset();
	m.setViewLookAtLH( vec3_s(8.0f, 0.0f,0.0f  ) , vec3_s(-0.0f, -0.0f,0.0f ), vec3_s(0.0f, 1.0f, 0.0f  ) );
	hr |= m.makeDevice9TransfView(pd3dDevice) ;

	m.setPerspectiveFovLH(1.5f, 1.0f, 0.1f, 1000.0f);
	hr |= m.makeDevice9TransfProj(pd3dDevice);

	m.setTranslation(0.0f, 0.0f, 0.0f);
	hr |= m.makeDevice9TransfWorld(pd3dDevice);



//	hr |=  g_pFontSmall->Render3DText(L"simple3dtext", 0 );
	
	return hr; 
};




//--------------------------------------------------------------------------------------
// Render the scene 
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	HRESULT hr;

	// Clear the render target and the zbuffer 
	V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB(0, 80,80, 250), 1.0f, 0) );

	// Render the scene
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{

		mat44_s m ;
		m.reset();
	   m.makeDevice9TransfWorld (pd3dDevice);
 

	    if(NULL == g_pfont)
		{
			g_pfont = new D3dFont(  pd3dDevice, L"Arial", 13, GB_D3D9_FONT_D3DFONT_BOLD );
			//g_pfont->InitDeviceObjects(pd3dDevice);
			//g_pfont->RestoreDeviceObjects();

		}

		if(!g_pFontSmall)
		{
			g_pFontSmall = new   D3dFont(  pd3dDevice, L"Courier New", 8, 0 ); 
		}



		hr |= test_DrawTextScaled(pd3dDevice, fTime);

		hr |= test_render3dText(pd3dDevice);


  
  
 	   m.makeDevice9TransfWorld (pd3dDevice);

   		hr |= test_drawText(pd3dDevice);
		hr |= test_drawText_dowble(pd3dDevice);

		V( pd3dDevice->EndScene() );
	}
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, 
						 bool* pbNoFurtherProcessing, void* pUserContext )
{
	return 0;
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnResetDevice callback here 
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{

	GB_SAFE_DEL_OBJ(g_pfont);
	GB_SAFE_DEL_OBJ(g_pFontSmall);


	/*
   if(g_pfont)
   {
	   g_pfont->DeleteDeviceObjects();
   }

	*/

}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
  GB_SAFE_DEL_OBJ(g_pfont);



}



//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
//INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
int main(int argc,  char* argv[])
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// Set the callback functions
	DXUTSetCallbackDeviceCreated( OnCreateDevice );
	DXUTSetCallbackDeviceReset( OnResetDevice );
	DXUTSetCallbackDeviceLost( OnLostDevice );
	DXUTSetCallbackDeviceDestroyed( OnDestroyDevice );
	DXUTSetCallbackMsgProc( MsgProc );
	DXUTSetCallbackFrameRender( OnFrameRender );
	DXUTSetCallbackFrameMove( OnFrameMove );

	// TODO: Perform any application-level initialization here

	// Initialize DXUT and create the desired Win32 window and Direct3D device for the application
	DXUTInit( true, true, true ); // Parse the command line, handle the default hotkeys, and show msgboxes
	DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
	DXUTCreateWindow( L"EmptyProject" );
	DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 640, 480, IsDeviceAcceptable, ModifyDeviceSettings );

	// Start the render loop
	DXUTMainLoop();

	// TODO: Perform any application-level cleanup here

	return DXUTGetExitCode();
}


