// Пример использования  d3d9::draw
//
 
#include <ce/dxut_wonly/dxut_wonly.h>

#include <gb/math/math.h>
using namespace gb::math::base;

#include <gb/graphics/d3d9/draw.h>
using namespace gb::graphics::d3d9::draw;

#pragma comment(lib , "netapi32.lib")

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
	return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice,
						  double fTime, float fElapsedTime, 
						  void* pUserContext )
{


}

 

//! Сохраняет и восстанавливает состояние девайса
class VGSaveRestoreDataD3D9 {
public:

	DWORD fvf;
	D3DMATERIAL9 material;
	D3DMATRIX wMatrix;
	IDirect3DBaseTexture9 *texture0;
	DWORD rsPointSize;
	DWORD rsZENABLE;
	DWORD rsZWRITEENABLE;
	DWORD rsALPHABLENDENABLE;
	DWORD rsFillMode;

	IDirect3DVertexShader9 *pIVSH;
	IDirect3DPixelShader9 *pIPSH;

	VGSaveRestoreDataD3D9() {};


	//=========================================================================
	HRESULT  SaveDeviceData(IDirect3DDevice9 *pdevice, 
		const D3DCOLORVALUE* newColor, 
		int pointSize, 
		IDirect3DTexture9 *newTxtr)
	{
		HRESULT hr = S_OK;
		D3DMATERIAL9 newMat;

		assert(pdevice);

		hr |= pdevice->GetFVF(&fvf);
		hr |= pdevice->GetMaterial(&material);
		if (newColor)
		{
			newMat.Diffuse.r = newColor->r;
			newMat.Diffuse.g = newColor->g;
			newMat.Diffuse.b = newColor->b;
			newMat.Diffuse.a = newColor->a;

			newMat.Emissive.r = newColor->r;
			newMat.Emissive.g = newColor->g;
			newMat.Emissive.b = newColor->b;
			newMat.Emissive.a = newColor->a;

		};

		hr |= pdevice->SetMaterial(&newMat);
		hr |= pdevice->GetTransform(D3DTS_WORLD, &wMatrix);
		hr |= pdevice->GetTexture(0, &texture0);
		hr |= pdevice->SetTexture(0, newTxtr);


		// OLD >>	hr |= m_pdevice->GetRenderState( D3DRS_POINTSIZE, &rsPointSize );
		hr |= pdevice->GetRenderState(D3DRS_POINTSIZE, &rsPointSize);

		hr |= pdevice->GetRenderState(D3DRS_ZENABLE, &rsZENABLE);
		hr |= pdevice->GetRenderState(D3DRS_ZWRITEENABLE, &rsZWRITEENABLE);


		 float fpsize = pointSize;
 		hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*) &fpsize) );

		hr |= pdevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &rsALPHABLENDENABLE);
		hr |= pdevice->GetRenderState(D3DRS_FILLMODE, &rsFillMode);

		hr |= pdevice->GetVertexShader(&pIVSH);
		hr |= pdevice->GetPixelShader(&pIPSH);

		return hr;
	};

	//======================================================================
	HRESULT  RestoreDeviceData(IDirect3DDevice9 *pdevice)
	{
		HRESULT hr = S_OK;
		hr |= pdevice->SetFVF(fvf);
		hr |= pdevice->SetMaterial(&material);
		hr |= pdevice->SetTransform(D3DTS_WORLD, &wMatrix);
		hr |= pdevice->SetTexture(0, texture0);

		if (texture0)
		{
			texture0->Release();
			texture0 = NULL;
		};

		hr |= pdevice->SetRenderState(D3DRS_ZENABLE, rsZENABLE);
		hr |= pdevice->SetRenderState(D3DRS_ZWRITEENABLE, rsZWRITEENABLE);
		hr |= pdevice->SetRenderState(D3DRS_POINTSIZE, rsPointSize);
		hr |= pdevice->SetRenderState(D3DRS_ALPHABLENDENABLE, rsALPHABLENDENABLE);
		hr |= pdevice->SetRenderState(D3DRS_FILLMODE, rsFillMode);

		hr |= pdevice->SetVertexShader(pIVSH);

		if (pIVSH)
		{
			pIVSH->Release();
			pIVSH = NULL;
		};

		hr |= pdevice->SetPixelShader(pIPSH);
		if (pIVSH)
		{
			pIPSH->Release();
			pIPSH = NULL;
		};


		return hr;
	};






};  static VGSaveRestoreDataD3D9  g_dd;
// end class



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


// 0 draw screen point
		D3DCOLORVALUE color_pnt = { 1.0f, 1.0f, 0.0f, 1.0f };
		hr |= DrawScreenPoint( pd3dDevice, color_pnt, 268, 348, 4 ); 


		RECT rect;
		::SetRect(&rect, 100, 100, 200, 200 );
		D3DCOLORVALUE color = { 1.0f, 1.0f, 1.0f, 1.0f };
		// 1
	//	hr |= DrawScreenQuad(pd3dDevice, rect,  color );

    // 2
	//	hr |= DrawFullScreenQuad(pd3dDevice, color);

		//   screen points
		gb::math::base::vec2_s varr [4];
		varr[0] = vec2_s( 20 , 20  );
		varr[1] = vec2_s( 120 , 120  );
		varr[2] = vec2_s( 220 , 220);
		varr[3] = vec2_s( 320 , 320  );

		hr |= DrawScreenPoints(pd3dDevice, color, varr[0], 4, 8 );

// screen lines
    D3DCOLORVALUE color_lines = { 1.0f, 0.0f, 0.0f, 1.0f };

	 varr[0] = vec2_s( 20 , 20  );
	 varr[1] = vec2_s( 120 , 120  );
	 varr[2] = vec2_s( 220 , 220);
	 varr[3] = vec2_s( 320 , 320  );


  hr |=DrawScreenLines(pd3dDevice , color_lines, varr[0],4  );

  // screen circle
    D3DCOLORVALUE color_circle = { 0.0f, 1.0f, 0.0f, 1.0f };
	 varr[0] = vec2_s(156, 265);
  hr |= DrawScreenCircle(pd3dDevice, color_circle, varr[0].x , varr[0].y , 100.0f );


// draw screen rect
  hr |= DrawScreenRect(pd3dDevice, color_circle, 84, 45, 135, 165 );


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
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
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


