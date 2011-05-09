// Пример использования dxut_wonly
//
//#include "stdafx.h"
 

#include <ce/dxut_wonly/dxut_wonly.h>
//#include <ce/LDrw/CubeMapEnvirRender.h>

#include <gb/graphics/d3d9/d3d9.h>
#include <gb/math/math.h>

#include <gb/devhelp/devcamera.h>
#include <gb/base/Constants.h>
#include <gb/macro.h>

 
#include  <gb/graphics/d3d9/render/render.h>
#include  <gb/graphics/d3d9/d3dFont.h>

using namespace  gb::graphics::d3d9;
using namespace  gb::graphics::d3d9::render;


//=====================================================

 IDirect3DTexture9* g_pTexture = NULL;
 D3dFont*  g_pFont= NULL;

 gb::devhelp::ModelViewerCamera g_ModelViewerCamera;
 
 bool b_lost;

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
 

 hr |= D3DXCreateTextureFromFileA(pd3dDevice, "z:\\!!MYCODE\\ce\\exp\\font\\texture.tga", &g_pTexture);


 g_pFont = new  D3dFont(pd3dDevice, L"Arial", 13);

	   


	return  hr;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_DEFAULT resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
							   const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{

	g_ModelViewerCamera.setProjParams( GBC_PI/4.0f , 
	      (float) ( pBackBufferSurfaceDesc->Width)  /   ( (float) pBackBufferSurfaceDesc->Height ) , 
		0.1f,  1000.0f    );

	g_ModelViewerCamera.setWindow( pBackBufferSurfaceDesc->Width , pBackBufferSurfaceDesc->Height  );
	 
	return S_OK;
}

float g_elapsed ;

//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
	g_elapsed  =   fElapsedTime;
	g_ModelViewerCamera.frameMove(fElapsedTime);

}



 
   static IRenderBitmapFont*  g_pIRenderBitmapFont = NULL;



   // temp !  временно    для заполнения табл  тест для разработки.
   static void __FillArrRect(IRenderBitmapFont::CharDescrTableAnsi* prec)
   {
	   // SetRect( prec + 0     ,   0  ,  0  ,  14  ,  14   ); 
 

	   SetRect( &prec->table[48].recTexture      , 134, 3 ,134+10, 17+3);	  // 0
	   SetRect( &prec->table[49].recTexture      , 144 ,3 ,144+11, 17+3 );	  // 1
	   SetRect( &prec->table[50].recTexture      ,  155, 3 ,155+10, 17+3  ); 
	   SetRect( &prec->table[51].recTexture     ,   165, 3 ,165+11, 17+3   ); 
	   SetRect( &prec->table[52].recTexture     ,   176, 3 ,176+11 ,17+3 );	// 4
	   SetRect( &prec->table[53].recTexture     ,   187, 3 ,187+11 ,17+3  );  


	   SetRect( &prec->table[54].recTexture  ,  198 ,3 ,198+10 ,17+3  ); 
	   SetRect( &prec->table[55].recTexture  ,  208, 3 ,208+10, 17+3  ); 
	   SetRect( &prec->table[56].recTexture   ,  218 ,3 ,218+10 ,17+3  ); 
	   SetRect( &prec->table[57].recTexture  ,  228 ,3 ,228+10 ,17+3  ); 
 

	   //  SetRect( prec + 126     ,   0  ,  0  ,  14  ,  14   ); 
   }


HRESULT __DrawSampleTexturedText2(IDirect3DDevice9* pdevice)
{
	HRESULT hr =0; 
	const char* str = "0123456";
 const int SYMB_SIZE = 16;

   static IRenderBitmapFont::CharDescrTableAnsi table;

    
   {
	   static bool stb_firstcall =  true;
	   if(stb_firstcall)
	   {
		   stb_firstcall = false;
		   __FillArrRect(&table);


	   }

   }

	if(!g_pIRenderBitmapFont)
	{
		//hr |= CreateRenderBitmapFontInterface(&g_pIRenderBitmapFont, pdevice, g_pTexture, table);
 	hr |= CreateRenderBitmapFontInterfaceFromXmlFileA(&g_pIRenderBitmapFont, pdevice, g_pTexture, 
		"z:\\!!MYCODE\\ce\\exp\\font\\font.xml");

   

	IRenderBitmapFont::DrawOptions dopt =  g_pIRenderBitmapFont->getDrawOptions();
	//dopt.nBetweenSymbols = 0;
	dopt.nSymbolsWidth = dopt.nSymbolsWidth = 12;
	g_pIRenderBitmapFont->setDrawOptions(dopt);

	}


	hr |= g_pIRenderBitmapFont->DrawStr(50, 50, "const char_t* xml_node::child_value() const;");// "01230123") ;
	// hr |= g_RenderBitmalFont.draw( pdevice, g_pTexture, str,  10, 10, SYMB_SIZE, SYMB_SIZE, 0, 0  );



  return hr;
}

HRESULT __DrawSampleTexturedText(IDirect3DDevice9* pdevice)
{
	HRESULT hr =0;
    

	//=========================================================

	static ID3DXSprite* pSpr = NULL;
	if(!pSpr)
	{
   hr |= D3DXCreateSprite(pdevice, &pSpr);



	}


   const char* str = "0123456789";


	hr |= pSpr->Begin( D3DXSPRITE_ALPHABLEND  );


 D3DXVECTOR3  center = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
 D3DXVECTOR3  position = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

 static RECT rarr[256];
 memset(rarr, 0, sizeof(rarr) );
	//__FillArrRect(&rarr);


	const int NLEN = (int)strlen(str);
	for(int c=0; c<NLEN; c++)	
	{
		char chr =	str[c];
		RECT rect = rarr[ (unsigned int)chr ];
	// SetRect(&rect,  0  , 0 ,  24 , 24  );

 
	hr |= pSpr-> Draw( g_pTexture, &rect, &center, &position, 0-1 );


		position.x +=  rect.right - rect.left ;
	}

	hr |= pSpr->End();

 

	return hr;
}



//=========================================================================
HRESULT  DrawScreenQuad( IDirect3DDevice9* pdevice,  
						const RECT& rect, 
						const D3DCOLORVALUE& color )
{
	HRESULT hr = 0;

	if ( pdevice == NULL )
	{
		return E_FAIL;
	}

#define D3DFVF_SCREENQUAD (D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE )
	struct SCREENQUADVERT
	{
		float x, y, z, rhw;   D3DCOLOR color; FLOAT u, v;
	};

	static SCREENQUADVERT screenQuadVertices[] = 
	{
		{
			10.0f, 0.0f, 1.0f, 1.0f,  0xffffffff, 0.0f, 0.0f, 
		}

		, 
		{
			300.0f, 0.0f, 1.0f, 1.0f, 0xffffffff,  1.0f, 0.0f, 
		}

		, 
		{
			300.0f, 400.0f, 1.0f, 1.0f,  0xffffffff, 1.0f, 1.0f, 
		}

		, 

		{
			10.0f, 0.0f, 1.0f, 1.0f,  0xffffffff, 0.0f, 0.0f, 
		}

		, 
		{
			300.0f, 400.0f, 1.0f, 1.0f,  0xffffffff, 1.0f, 1.0f, 
		}

		, 
		{
			10.0f, 400.0f, 1.0f, 1.0f,  0xffffffff, 0.0f, 1.0f, 
		}

		, 

	};

	screenQuadVertices[0].x = ( float )rect.left;
	screenQuadVertices[0].y = ( float )rect.top;
	screenQuadVertices[1].x = ( float )rect.right;
	screenQuadVertices[1].y = ( float )rect.top;
	screenQuadVertices[2].x = ( float )rect.right;
	screenQuadVertices[2].y = ( float )rect.bottom;

	screenQuadVertices[3].x = ( float )rect.left;
	screenQuadVertices[3].y = ( float )rect.top;
	screenQuadVertices[4].x = ( float )rect.right;
	screenQuadVertices[4].y = ( float )rect.bottom;
	screenQuadVertices[5].x = ( float )rect.left;
	screenQuadVertices[5].y = ( float )rect.bottom;

	for(int c=0; c<6; c++)
	{
		screenQuadVertices[c].color = D3DCOLOR_COLORVALUE( color.r, color.g, color.b, color.a );
	}

	DWORD dwOldFvf;
	hr |= pdevice->GetFVF(&dwOldFvf);
	hr |= pdevice->SetFVF( D3DFVF_SCREENQUAD );  
	hr |= pdevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, 2, ( void* )screenQuadVertices, sizeof( SCREENQUADVERT ) );


	hr |= pdevice->SetFVF( dwOldFvf );
#undef D3DFVF_SCREENQUAD
	return hr;
};



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


 


	 const  mat44_s mView = g_ModelViewerCamera.getViewMatrix() ;
	 const  mat44_s mProj = g_ModelViewerCamera.getProjMatrix() ;
      
	    mat44_s mViewproj = mView * mProj;
	 // temp !
	// mViewproj.transpone();


	 const mat44_s mWOrld = g_ModelViewerCamera.getWorldMatrix();
	 mat44_s  mWVP = mWOrld * mViewproj;
 
 
	  //hr |= __DrawSampleTexturedText(pd3dDevice);
	 hr |= __DrawSampleTexturedText2(pd3dDevice);

 
	 if(b_lost)
	 {
		 int _end = 0;

	 }

	 char buf[32];
	 sprintf(buf, "%f", g_elapsed);
	 hr |= g_pFont->DrawTextA(50, 300, 0-1, buf);


		V( pd3dDevice->EndScene() );
	}


	b_lost = false;
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

  b_lost = true;
   GB_SAFE_DEL_OBJ(g_pIRenderBitmapFont)

}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{

  GB_SAFE_DEL_OBJ(g_pIRenderBitmapFont)
	GB_SAFE_REL(g_pTexture)
	GB_SAFE_DEL_OBJ(g_pFont)

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


