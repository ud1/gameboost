#include "d3d9pch.h"

#if ( defined(WIN32) && defined(_D3D9_H_) )

#include <gb/graphics/d3d9/draw/draw.h>
#include "internal.h"

#include <gb/graphics/d3d9/d3dFont.h>
#include <gb/macro.h>
#include <stdexcept>
#include <assert.h>


#pragma warning (disable : 4297)
#pragma warning (disable : 4996)


namespace gb 
{
namespace graphics 
{
namespace d3d9 
{
namespace draw
{

//====================================================================

 //GB_D3D9_API	 D3dFont(IDirect3DDevice9* pd3dDevice,  const WCHAR* strFontName, DWORD dwHeight, DWORD dwFlags=0L );
D3dFont* g_pFont_normal = NULL;
D3dFont* g_pFont_big = NULL;
D3dFont* g_pFont_small = NULL;



//=========================================
static void __onRelease(void* pUserData)
{
   GB_SAFE_DEL_OBJ(g_pFont_normal);
   GB_SAFE_DEL_OBJ(g_pFont_big); 
   GB_SAFE_DEL_OBJ(g_pFont_small);
 

//   assert(false);
}

//===========================================
static void __check_firstcall() throw()
{
   static bool stb_firstcall = true;
   if(!stb_firstcall)
   {
	  return ;
   }

    stb_firstcall = false;

	if( !__registerOnReleaseDataProc(__onRelease, NULL) )
	{
		static const char CSTR_ERROR [] = " Error register proc";
		assert(false && CSTR_ERROR);
		throw std::runtime_error( CSTR_ERROR );
	}


}

//====================================================================
HRESULT __ckeck_CreateNormalFont(IDirect3DDevice9* pdevice)
{
	if(g_pFont_normal)
	{
		return S_OK;
	}

	try 
	{
     g_pFont_normal = new D3dFont( pdevice, L"Courier New", 11, 0);
	}
	catch(...)
	{
		assert(false && " create font exception! ");
		return E_FAIL;
	}

	return  S_OK;
}

//====================================================================
GB_D3D9_API HRESULT DrawStr(IDirect3DDevice9* pdevice, 
							int x, int y, 
							const char* str, D3DCOLOR color)
{
	HRESULT hr =S_OK;
	__check_firstcall();

   __ckeck_CreateNormalFont(pdevice);

  hr |= g_pFont_normal->DrawTextA(x,y,color, str, 0);


	return hr;
};

//====================================================================
GB_D3D9_API HRESULT DrawStrFormat(
								  IDirect3DDevice9* pdevice, 
								  int x, int y, 
								  D3DCOLOR color, 
								  const char *_Format, ...
								  ) 
{
   __check_firstcall();

	static char ss[8192];
	ss[0] = 0;

	va_list ap;
	va_start(ap, _Format);
	vsprintf(ss, _Format, ap);
	va_end(ap);

	HRESULT hr =0;
	  hr |= DrawStr(pdevice, x,y, ss, color);


   return hr;
};

//===================================================================
GB_D3D9_API HRESULT DrawStrEx(
							  IDirect3DDevice9* pdevice,
							  int x, 
							  int y,
							  FontSize_e::e fontSize,
							  const char* str, 
							  D3DCOLOR color
							  )
{
	__check_firstcall();
	HRESULT hr =0;

   D3dFont* pfont = NULL;

	switch(fontSize)
	{
	case FontSize_e::NORMAL:
		{
		   hr |= __ckeck_CreateNormalFont(pdevice);
		   if FAILED(hr)  return hr;
		   hr |= g_pFont_normal->DrawTextA(x,y,color, str, 0);


		}
		break;

	case FontSize_e::BIG:
		{
			if( !g_pFont_big )
			{
			  g_pFont_big = new D3dFont( pdevice, L"Courier New", 18, GB_D3D9_FONT_D3DFONT_BOLD);
			}
		    
		   hr |= g_pFont_big->DrawTextA(x,y,color, str, 0);
		}
		break;

	case FontSize_e::SMALL:
		{
			if( !g_pFont_small )
			{
				g_pFont_small = new D3dFont( pdevice, L"Arial", 7, 0);
			}

			hr |= g_pFont_small->DrawTextA(x,y,color, str, 0);

		}
		break;



	default:
		{
			// unknow font size
			assert(false && "unknow font size");
			return E_FAIL;
		}

	}



	return hr;
}


//====================================================================

}
}
}
}

#endif
// end file