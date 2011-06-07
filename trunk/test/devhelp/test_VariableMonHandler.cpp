#include "d3d9pch.h" 

#include <ce/dxut_wonly/dxut_wonly.h>



using namespace std;
#include <gb/macro.h>

#include <gb/color/color.h>
using  namespace gb::color;
 
//#define GB_D3DX9

#include <gb/graphics/d3d9/auto_include_libr.h>
#include <gb/macro.h>

#include <gb/fmath/fmath.h>

//#include"gbd3d9.h"

class myclass
{
public:

	bool  m_bool ;
	BOOL  m_bool32 ;
	float m_float  ;
	float m_float_add  ;
	int m_int;
	unsigned int m_uint;
	Color4f m_color;

  myclass()
  {
	 m_bool = false;
	 m_bool32 = 0;
	 m_float = 0.0f;
	 m_float_add = 0.0f;
	 m_int=0;
	 m_uint=0;
	 m_color.setWhite();
  }

};

static myclass g_myclass;


#include  <gb/devhelp/VariableMonHandler.h> 
gb::devhelp::VariableMonHandler g_mon("g_mon"); // mon object

 ID3DXFont* g_pfont = NULL;


//--------------------------------------------------------------------------------------
// Rejects any devices that aren't acceptable by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, 
								 D3DFORMAT AdapterFormat, 
								 D3DFORMAT BackBufferFormat, 
								 bool bWindowed, 
								 void* pUserContext )
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
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, 
								   const D3DCAPS9* pCaps, 
								   void* pUserContext )
{
	return true;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_MANAGED resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, 
								const D3DSURFACE_DESC* pBackBufferSurfaceDesc, 
								void* pUserContext )
{
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_DEFAULT resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
							   const D3DSURFACE_DESC* pBackBufferSurfaceDesc, 
							   void* pUserContext )
{
	GB_SAFE_REL(g_pfont)
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{

}

//=======================================
HRESULT RenderText(IDirect3DDevice9* pdevice)
{
	HRESULT hr =0;

   // check crate text
	if(NULL ==g_pfont)
	{
		// create font
	 hr |= D3DXCreateFontA( pdevice, 14, 0, FW_BOLD, 1, 
			FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
			  "Courier New" , &g_pfont ) ;

	}

	if FAILED(hr)
	{
		return hr;
	}


	static std::string str;
	str = "";
 	g_mon.make_mon_string(str);

	RECT rec;
	SetRect(&rec, 10, 10, 1000, 1000);
	hr |= g_pfont->DrawTextA(NULL, str.c_str(), -1, &rec, DT_LEFT, 0xffffffff );

 
	//

	// 




	return hr;
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


	   hr |=RenderText(pd3dDevice);

		V( pd3dDevice->EndScene() );
	}
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, 
						 bool* pbNoFurtherProcessing, void* pUserContext )
{
	g_mon.msgProc( hWnd, uMsg, wParam, lParam );

	return 0;
}

void  CALLBACK  OnKeyb( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
 if(!bKeyDown) return ;
   return;


 switch(nChar)
 {

 case VK_UP:
	 {
 	  g_mon.handlekey_up();
	 }
	 break;

 case VK_DOWN:
	 {
 	   g_mon.handlekey_down();
	 }
	 break;

 case VK_LEFT:
	 {
 	  g_mon.handlekey_left();
	 }
	 break;

 case VK_RIGHT:
	 {
    g_mon.handlekey_right();
	 }
	 break;





 }


}


//--------------------------------------------------------------------------------------
// Release resources created in the OnResetDevice callback here 
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{
	GB_SAFE_REL(g_pfont)
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
	GB_SAFE_REL(g_pfont)
}



//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
int main(int argc,  char* argv[])
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif


 
  g_mon.add_bool  ("m_bool   ", &g_myclass.m_bool  );
  g_mon.add_bool32("m_bool32 ",  (long*)&g_myclass.m_bool32 );
  g_mon.add_int   ("m_int    ", &g_myclass.m_int,   1, -10, 10 );
  g_mon.add_uint  ("m_uint   ", &g_myclass.m_uint,   1, 5, 10 );

  g_mon.add_float ("m_float  ",  &g_myclass.m_float, 2.0f, 0.01f, -1000.0f, 1000.0f );
  g_mon.add_float ("m_float_add  ", &g_myclass.m_float_add,
	  1.0f, 0.01f, 
	  0.0f,  1.0f);


  // add color
  /*
  g_mon.add_float("  m_color::red   ",   &g_myclass.m_color.r);
  g_mon.add_float("  m_color::green ", &g_myclass.m_color.g);
  g_mon.add_float("  m_color::blue  ",   &g_myclass.m_color.b);
  g_mon.add_float("  m_color::alpha ",   &g_myclass.m_color.a);
  */

 


	// Set the callback functions
	DXUTSetCallbackDeviceCreated( OnCreateDevice );
	DXUTSetCallbackDeviceReset( OnResetDevice );
	DXUTSetCallbackDeviceLost( OnLostDevice );
	DXUTSetCallbackDeviceDestroyed( OnDestroyDevice );
	DXUTSetCallbackMsgProc( MsgProc );
	DXUTSetCallbackFrameRender( OnFrameRender );
	DXUTSetCallbackFrameMove( OnFrameMove );
	DXUTSetCallbackKeyboard(OnKeyb);



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


