// Пример использования dxut_wonly
//
#include "stdafx.h"

#include <ce/dxut_wonly/dxut_wonly.h>
//#include <ce/LDrw/CubeMapEnvirRender.h>

#include <gb/graphics/d3d9/d3d9.h>
#include <gb/math/math.h>

#include <gb/devhelp/devcamera.h>
#include <gb/base/Constants.h>
#include <gb/macro.h>

#include <gb/graphics/d3d9/render/render.h>
using namespace gb::graphics::d3d9::render;


 IRenderCubemapEnvironment* g_re = NULL; // test

 IDirect3DCubeTexture9* g_ptxtr = NULL;

 gb::devhelp::ModelViewerCamera g_ModelViewerCamera;


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
  HRESULT hr = 0;

 hr |= D3DXCreateCubeTextureFromFileA(pd3dDevice, "z:\\!TEXTURES\\!DVD\\!CUBEMAP\\BlueSky512.dds", &g_ptxtr);





	return  hr;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_DEFAULT resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
							   const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{

	g_ModelViewerCamera.setProjParams( GBC_PI/4.0f , 
		pBackBufferSurfaceDesc->Width/pBackBufferSurfaceDesc->Height  ,   0.1f,  1000.0f    );

	g_ModelViewerCamera.setWindow( pBackBufferSurfaceDesc->Width , pBackBufferSurfaceDesc->Height  );
	 
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	g_ModelViewerCamera.frameMove(fElapsedTime);

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

	 // set filter
	hr |= pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	hr |= pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	hr |= pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );


	  // make camera
		hr |= g_ModelViewerCamera.makeCurrent(pd3dDevice, false);



	 if(!g_re)
	 {
 
		 hr |= CreateInterfaceCubemapRender(&g_re, pd3dDevice);
		 if FAILED(hr  )
		 {
			 throw ( std::runtime_error("fail") );
		 }
	 }


	 mat44_s mView = g_ModelViewerCamera.getViewMatrix() ;
	 mat44_s mProj = g_ModelViewerCamera.getProjMatrix() ;

	 mat44_s mViewproj = mView * mProj;
	 const mat44_s viewInv = mView.inverted();

	 IRenderCubemapEnvironment::RenderEnvirOptions ro;
	 ro.roll = (float)GBC_PI/2.0f;

	hr |= g_re->RenderEnvironment(pd3dDevice, mViewproj, viewInv, g_ptxtr, ro);




   



		V( pd3dDevice->EndScene() );
	}
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, 
						 bool* pbNoFurtherProcessing, void* pUserContext )
{
	g_ModelViewerCamera.handleMessages(hWnd,  uMsg,  wParam,  lParam);
	return 0;
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnResetDevice callback here 
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
 
	GB_SAFE_DEL_OBJ(g_re)

	GB_SAFE_REL(g_ptxtr)

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


