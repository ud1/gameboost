﻿#include "d3d9pch.h"

#include <Windows.h>
#include <mmsystem.h>

#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 



//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL; // Buffer to hold vertices
LPDIRECT3DTEXTURE9      g_pTexture   = NULL; // Our texture

// A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position; // The position
	D3DCOLOR    color;    // The color
#ifndef SHOW_HOW_TO_USE_TCI
	FLOAT       tu, tv;   // The texture coordinates
#endif
};

// Our custom FVF, which describes our custom vertex structure
#ifdef SHOW_HOW_TO_USE_TCI
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#else
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#endif



//------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//----------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
	// Create the D3D object.
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	// Turn off culling
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	// Turn off D3D lighting
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// Turn on the zbuffer
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	return S_OK;
}

#include <gb/graphics/d3d9/dds/DDSTextureLoader.h>   
using namespace gb::graphics::d3d9::dds;

//#include "DDSTextureLoader.h"


#include <gb/graphics/d3d9/draw/draw.h>
void test_getdraw_sampletexture(IDirect3DDevice9* pdevice)
{
	IDirect3DTexture9* ptext = gb::graphics::d3d9::draw::getSampleDebugTexture(pdevice);



   int _stop =0;
}



//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Create the textures and vertex buffers
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
  HRESULT hr =0;

    CreateDDSOptions opt;

 // hr |= D3DXCreateTextureFromFile( g_pd3dDevice,  "banana.bmp", &g_pTexture );
    hr |= CreateDDSTextureFromFileW( g_pd3dDevice, 
 L"c:\\Microsoft DirectX SDK (February 2007)\\Samples\\Media\\misc\\cellceiling.dds",
 &g_pTexture, &opt );

		if(	 FAILED(  hr  )	)
		{
			return  hr;
		}





	// Create the vertex buffer.
	if( FAILED( g_pd3dDevice->CreateVertexBuffer( 50*2*sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
	{
		return E_FAIL;
	}

	// Fill the vertex buffer. We are setting the tu and tv texture
	// coordinates, which range from 0.0 to 1.0
	CUSTOMVERTEX* pVertices;
	if( FAILED( g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
		return E_FAIL;
	for( DWORD i=0; i<50; i++ )
	{
		FLOAT theta = (2*D3DX_PI*i)/(50-1);

		pVertices[2*i+0].position = D3DXVECTOR3( sinf(theta),-1.0f, cosf(theta) );
		pVertices[2*i+0].color    = 0xffffffff;
#ifndef SHOW_HOW_TO_USE_TCI
		pVertices[2*i+0].tu       = ((FLOAT)i)/(50-1);
		pVertices[2*i+0].tv       = 1.0f;
#endif

		pVertices[2*i+1].position = D3DXVECTOR3( sinf(theta), 1.0f, cosf(theta) );
		pVertices[2*i+1].color    = 0xff808080;
#ifndef SHOW_HOW_TO_USE_TCI
		pVertices[2*i+1].tu       = ((FLOAT)i)/(50-1);
		pVertices[2*i+1].tv       = 0.0f;
#endif
	}
	g_pVB->Unlock();

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if( g_pTexture != NULL )
		g_pTexture->Release();

	if( g_pVB != NULL )
		g_pVB->Release();

	if( g_pd3dDevice != NULL )
		g_pd3dDevice->Release();

	if( g_pD3D != NULL )
		g_pD3D->Release();
}



//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixRotationX( &matWorld, timeGetTime()/1000.0f );
	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
	g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	// Clear the backbuffer and the zbuffer
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
	   // temp
		test_getdraw_sampletexture(g_pd3dDevice);


		// Setup the world, view, and projection matrices
		SetupMatrices();

		// Setup our texture. Using textures introduces the texture stage states,
		// which govern how textures get blended together (in the case of multiple
		// textures) and lighting information. In this case, we are modulating
		// (blending) our texture with the diffuse color of the vertices.
		g_pd3dDevice->SetTexture( 0, g_pTexture );
		g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

#ifdef SHOW_HOW_TO_USE_TCI
		// Note: to use D3D texture coordinate generation, use the stage state
		// D3DTSS_TEXCOORDINDEX, as shown below. In this example, we are using
		// the position of the vertex in camera space (D3DTSS_TCI_CAMERASPACEPOSITION)
		// to generate texture coordinates. Camera space is the vertex position
		// multiplied by the World and View matrices.  The tex coord index (TCI)  
		// parameters are passed into a texture transform, which is a 4x4 matrix  
		// which transforms the x,y,z TCI coordinates into tu, tv texture coordinates.

		// In this example, the texture matrix is setup to transform the input
		// camera space coordinates (all of R^3) to projection space (-1,+1) 
		// and finally to texture space (0,1).
		//    CameraSpace.xyzw = (input vertex position) * (WorldView)
		//    ProjSpace.xyzw = CameraSpace.xyzw * Projection           //move to -1 to 1
		//    TexSpace.xyzw = ProjSpace.xyzw * ( 0.5, -0.5, 1.0, 1.0 ) //scale to -0.5 to 0.5 (flip y)
		//    TexSpace.xyzw += ( 0.5, 0.5, 0.0, 0.0 )                  //shift to 0 to 1

		// Setting D3DTSS_TEXTURETRANSFORMFLAGS to D3DTTFF_COUNT4 | D3DTTFF_PROJECTED
		// tells D3D to divide the input texture coordinates by the 4th (w) component.
		// This divide is necessary when performing a perspective projection since
		// the TexSpace.xy coordinates prior to the homogeneous divide are not actually 
		// in the 0 to 1 range.
		D3DXMATRIXA16 mTextureTransform;
		D3DXMATRIXA16 mProj;
		D3DXMATRIXA16 mTrans;
		D3DXMATRIXA16 mScale;

		g_pd3dDevice->GetTransform( D3DTS_PROJECTION, &mProj );
		D3DXMatrixTranslation( &mTrans, 0.5f, 0.5f, 0.0f );
		D3DXMatrixScaling( &mScale, 0.5f, -0.5f, 1.0f );
		mTextureTransform = mProj * mScale * mTrans;

		g_pd3dDevice->SetTransform( D3DTS_TEXTURE0, &mTextureTransform );
		g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT4 | D3DTTFF_PROJECTED );
		g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );
#endif

		// Render the vertex buffer contents
		g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
		g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2*50-2 );

		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
//INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
int main()
{
	// Register the window class
	WNDCLASSEXW wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL };
	RegisterClassExW( &wc );

	// Create the application's window
	HWND hWnd = CreateWindowW( L"D3D Tutorial", L"D3D Tutorial 05: Textures",
		WS_OVERLAPPEDWINDOW, 10, 10, 800, 600,
		NULL, NULL, wc.hInstance, NULL );

	// Initialize Direct3D
	if( SUCCEEDED( InitD3D( hWnd ) ) )
	{
		// Create the scene geometry
		if( SUCCEEDED( InitGeometry() ) )
		{
			// Show the window
			ShowWindow( hWnd, SW_SHOWDEFAULT );
			UpdateWindow( hWnd );

			// Enter the message loop
			MSG msg;
			ZeroMemory( &msg, sizeof(msg) );
			while( msg.message!=WM_QUIT )
			{
				if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
				else
					Render();
			}
		}
	}

	UnregisterClassW( L"D3D Tutorial", wc.hInstance );
	return 0;
}



