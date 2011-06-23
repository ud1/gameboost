#include "d3d9pch.h"

 
#pragma warning (disable : 4996)
 
#include "fxview.h"
 

 
 

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
HRESULT  CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	HRESULT  hr = 0;
	  Appl* pappl = (Appl*)pUserContext;
	 hr |= pappl->OnCreateDevice(pd3dDevice, pBackBufferSurfaceDesc);



  pappl->m_camera.setViewParams( vec3(5, 0 , 0 ) , vec3(0,0,0) );

	return  hr;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_DEFAULT resources here 
//--------------------------------------------------------------------------------------
HRESULT  CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
							   const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	HRESULT  hr = 0;
	  Appl* pappl = (Appl*)pUserContext;
	 hr |= pappl->OnResetDevice(pd3dDevice, pBackBufferSurfaceDesc);


   float asp = (float)pBackBufferSurfaceDesc->Width/(float)pBackBufferSurfaceDesc->Height;

   pappl->m_camera.setProjParams( gb::fmath::constan::CPI/3.0f,  asp , 0.1f , 1000.0f  );
   pappl->m_camera.setWindow( pBackBufferSurfaceDesc->Width , pBackBufferSurfaceDesc->Height );





	return  hr;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	  Appl* pappl = (Appl*)pUserContext;

	pappl->m_camera.frameMove(fElapsedTime);
 
}


//--------------------------------------------------------------------------------------
// Render the scene 
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	  Appl* pappl = (Appl*)pUserContext;
	HRESULT  hr;
 
	V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_ARGB(0, 45, 50, 170),
		1.0f, 0) );

 
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{
	



	 hr |=	pappl->OnFrameRender(pd3dDevice, (float)fTime,  fElapsedTime);


	
	
		V( pd3dDevice->EndScene() );
	}
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, 
						 bool* pbNoFurtherProcessing, void* pUserContext )
{
	  Appl* pappl = (Appl*)pUserContext;
   pappl->m_camera.handleMessages(hWnd , uMsg, wParam, lParam);

	return 0;
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnResetDevice callback here 
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{
  Appl* pappl = (Appl*)pUserContext;
  if(pappl)
  {
	  pappl->OnLostDevice();
  }

}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
 
  Appl* pappl = (Appl*)pUserContext;
  if(pappl->m_peff != NULL)
  {
	  pappl->OnDestroyDevice();
  }
 


}

void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
  Appl* appl = (Appl*)pUserContext;

  appl->OnKeyboard(nChar);
  // 

}

void   CALLBACK OnMouse( bool bLeftButtonDown, 
						bool bRightButtonDown, 
						bool bMiddleButtonDown, 
						bool bSideButton1Down, 
						bool bSideButton2Down, 
						int nMouseWheelDelta, 
						int xPos, int yPos, 
						void* pUserContext )
{
   Appl* pappl = (Appl*)pUserContext;


	 
}
 
 
int main(int argc,  char* argv[])
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

   Appl* appl =  new   Appl( argc, argv );
 

  // temp code !!!
   memcpy(appl->m_strFxFilePath,
	   "j:\\!!MYCODE\\ce\\exp\\test_effect.fx", 
	   MAX_PATH );



	// Set the callback functions
	DXUTSetCallbackDeviceCreated( OnCreateDevice, (void*)appl );
	DXUTSetCallbackDeviceReset( OnResetDevice,(void*)appl );
	DXUTSetCallbackDeviceLost( OnLostDevice, (void*)appl );
	DXUTSetCallbackDeviceDestroyed( OnDestroyDevice, (void*)appl );
	DXUTSetCallbackMsgProc( MsgProc, (void*)appl );
	DXUTSetCallbackFrameRender( OnFrameRender, (void*)appl );
	DXUTSetCallbackFrameMove( OnFrameMove,(void*)appl );
	DXUTSetCallbackKeyboard( OnKeyboard, (void*)appl );
	DXUTSetCallbackMouse( OnMouse , true, (void*)appl  );
 
	DXUTInit( true, true, true );  
	DXUTSetCursorSettings( true, true );  
	DXUTCreateWindow( L"fx view" );
	DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 800, 600, IsDeviceAcceptable, ModifyDeviceSettings ); 
	DXUTMainLoop();
	DXUTShutdown(0); 
	 int nexcode =  DXUTGetExitCode();
	  delete appl;
	 return nexcode;
}
 