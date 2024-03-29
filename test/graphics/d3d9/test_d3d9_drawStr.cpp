
#include "d3d9pch.h"
#include <ce/dxut_wonly/dxut_wonly.h>
 
#include <gb/graphics/d3d9/auto_include_libr.h>
#include <gb/graphics/d3d9/fx/create_effect.h>

#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
using   gb::graphics::d3d9::d3dx9_dynamic_load::CD3DX9_Dll_Loader;

CD3DX9_Dll_Loader* g_ploader = NULL;

#include <d3dx9.h> // temp
#include <string>
using namespace    gb::graphics::d3d9::fx;

#include <d3d9.h>

// new dev
#include <gb/graphics/d3d9/draw/draw.h>
namespace drw = gb::graphics::d3d9::draw;


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
     HRESULT hr =0;

	 // temp !!
	 return hr;


	 ID3DXEffect* eff = NULL;
	 std::string err;
	 CreateEffectOptions opt(NULL,NULL);
	 const char* text = " dsd da sad a ";
	 hr |= createEffectFromText(&eff, g_ploader, pd3dDevice, text, err, &opt, true);


	return   hr;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_DEFAULT resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
							   const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Render the scene 
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	HRESULT hr;

	// Clear the render target and the zbuffer 
	V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 45, 50, 170), 1.0f, 0) );

	// Render the scene
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{

	// draw cube
	hr |= pd3dDevice->SetTexture(0, drw::getSampleDebugTexture(pd3dDevice) );
	hr|= drw::drawMeshPrimitiveCube1x1Mem(pd3dDevice);


   // draw text
 hr |= drw::DrawStr(pd3dDevice, 100, 100, "zZxZzxzx", 0xffffffff);
 hr |= drw::DrawStrEx(pd3dDevice, 100, 120,  
	 drw::FontSize_e::SMALL, "this is string 12354897!@##$$%%&", 0xffffffff );

 hr |= drw::DrawStrEx(pd3dDevice, 100, 170,  
	 drw::FontSize_e::BIG, "this is string 12354897!@##$$%%&", 0xffffffff );



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
	drw::ReleaseAllInternalData();
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
	drw::ReleaseAllInternalData();
}

#include <gb/macro.h>

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

	
	try 
	{
		g_ploader = new CD3DX9_Dll_Loader();
	}
	catch(...)
	{
		GB_MBOX("failed create d3dx9 dll loader");
		return -1;
	}

	unsigned int vers = g_ploader->getLoadedD3DX9dll_version();

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

	DXUTShutdown(0);

	delete g_ploader;

	// TODO: Perform any application-level cleanup here

	return DXUTGetExitCode();
}


