// утилита для просмотра файлов fx
//
 

#include <ce/dxut_wonly/dxut_wonly.h>
#include <d3dx9.h>
#include <gb/macro.h>

#include <assert.h>


class Appl {
public:
   ID3DXEffect* m_peff ;

	Appl(int argc,  char* argv[] )
	{
		m_peff = NULL;
	   if(argc > 1)
	   {
		   assert(false);
	   }

	}

	virtual ~Appl()
	{
		if(m_peff)
		{
			GB_SAFE_REL(m_peff)
		}

	}


};

 


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
	  Appl* pappl = (Appl*)pUserContext;



	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_DEFAULT resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
							   const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	 Appl* pappl = (Appl*)pUserContext;
   if(pappl->m_peff != NULL)
   {
	   pappl->m_peff->OnResetDevice();
   }

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	  Appl* pappl = (Appl*)pUserContext;

}


//--------------------------------------------------------------------------------------
// Render the scene 
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	  Appl* pappl = (Appl*)pUserContext;
	HRESULT hr;
 
	V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 45, 50, 170), 1.0f, 0) );

 
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{
	
	
	
	
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
		  if(pappl->m_peff != NULL)
		  {
			  pappl->m_peff->OnLostDevice();
		  }
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
	  GB_SAFE_REL(pappl->m_peff) 
  }
 


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

   Appl appl ( argc, argv );
  // pappl = new Appl(argc, argv);



	// Set the callback functions
	DXUTSetCallbackDeviceCreated( OnCreateDevice, (void*)&appl );
	DXUTSetCallbackDeviceReset( OnResetDevice,(void*)&appl );
	DXUTSetCallbackDeviceLost( OnLostDevice, (void*)&appl );
	DXUTSetCallbackDeviceDestroyed( OnDestroyDevice, (void*)&appl );
	DXUTSetCallbackMsgProc( MsgProc, (void*)&appl );
	DXUTSetCallbackFrameRender( OnFrameRender, (void*)&appl );
	DXUTSetCallbackFrameMove( OnFrameMove,(void*)&appl );
 
	DXUTInit( true, true, true );  
	DXUTSetCursorSettings( true, true );  
	DXUTCreateWindow( L"EmptyProject" );
	DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 640, 480, IsDeviceAcceptable, ModifyDeviceSettings );

 
	DXUTMainLoop();

	DXUTShutdown(0);

 
	 int nexcode =  DXUTGetExitCode();

	//GB_SAFE_DEL_OBJ(pappl)
 

	 return nexcode;
}
 