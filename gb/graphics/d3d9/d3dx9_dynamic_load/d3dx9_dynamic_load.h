/** \file
 \brief ƒинамическа€ загрузка/ использование DLL   библиотеки D3DX9


  \author kscvet777

  \todo поправить функцию  checkExistsDll на поиск в директории приложени€.

*/

#if ( defined(WIN32) && defined(GB_D3D9) )

#pragma once

#include <gb/graphics/d3d9/api_decl.h>

#include <d3dx9.h>

#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load_pfunc_decl.h>

#include <stdlib.h>

#include <string>
#include <vector>
#include <stdexcept>


namespace  gb
{

namespace  graphics
{

namespace  d3d9
{

//!  \brief ƒинамическа€ загрузка/ использование DLL   библиотеки D3DX9 .
namespace d3dx9_dynamic_load
{



	//d3dx9_undef   = 0 ,

	//d3dx9_24,
	//d3dx9_25,
	//d3dx9_26,
	//d3dx9_27,
	//d3dx9_28,
	//d3dx9_29,
	//d3dx9_30,
	//d3dx9_31,
	//d3dx9_32,
	//d3dx9_33,
	//d3dx9_34,
	//d3dx9_ ....,
 
 
  
  //-------------------------------------------------------------------------

//! \brief   ѕолучить файл d3dx dll по номеру версии   
void  makeD3DX9dllFilename_by_version(std::string& strOut, unsigned int vers, bool bDebugV=false)
{
  strOut = "";
  strOut += "d3dx9";
  
  if(bDebugV)
  {
    strOut += "d";
  }

  strOut += "_";
  
  char buf [32];
  sprintf( buf , "%02i" , vers );
  strOut += buf;
  strOut += ".dll";

  // temp mon
  if(vers<10)
  {
   int _stop =0;
  }
 
}





bool checkDllExistsA (const char* fname)   
{    
    return ::GetFileAttributesA(fname) != DWORD(-1);
}
 
bool checkExistsDll(const char* sDllFilename)
{
   std::string sfullpath ;
   char bufsysdir[MAX_PATH];
 
  if(! ::GetSystemDirectoryA(bufsysdir, MAX_PATH ))
  {
   throw (std::runtime_error("system error"));
  }
  
  sfullpath = bufsysdir;
  sfullpath += '\\';
  sfullpath += sDllFilename;
  
  if( checkDllExistsA(sfullpath.c_str() ) )
  {
    return true;
  
  }  
 
   return false;
}
 
 // получить самую последнюю версию установленой библиотеки.
bool getInstaledD3DXlastVersion(unsigned int* piOutVers)
 {
   *piOutVers  =0;
 
  std::string fname;
  for(unsigned int cvers=45; cvers>0; cvers--)
  {
    makeD3DX9dllFilename_by_version(fname , cvers);
	  if( checkExistsDll( fname.c_str() ) )
	  {
	   *piOutVers = cvers;
	   return true;
	  }

  } 
 
    return false;
 }


void print_d3dx9_dll_info()
{
	std::string str;
  for( int c=50; c>=0; c-- )
  {
	makeD3DX9dllFilename_by_version( str, ( unsigned int )c  );
	if(  checkExistsDll (str.c_str() ) )
	{
	
	  printf( str.c_str() );
	  printf("\n");
	}

  
  }




   printf("\n   END. \n");
}


 //  получит все инсталированые версии d3dx dll в системе.
bool getInstaledD3DXallVersion(std::vector<unsigned int>& versions)
 {
   bool result = false;
	versions.clear();
 
  std::string fname;
  for(unsigned int cvers=45; cvers>0; cvers--)
  {
    makeD3DX9dllFilename_by_version(fname , cvers);
	  if( checkExistsDll( fname.c_str() ) )
	  {
	    versions.push_back(cvers);
	   result =  true;
	  }

  } 
 
    return  result;
 }



 




HMODULE loadDllLastVersion(unsigned int* piOutVers )
{
 
	if(piOutVers) *piOutVers = 0;
   if( !getInstaledD3DXlastVersion( piOutVers ) )
   {
   
     return 0;
   }
   
   std::string dllfname;
   makeD3DX9dllFilename_by_version(dllfname, *piOutVers );
   
   HMODULE hm = 0 ;
   hm = ::LoadLibraryA(dllfname.c_str() );
   if(hm)
   {
    /// error load.  none
   }

   return hm;
}  
 

class CD3DX9_Dll_Loader {
public:
	CD3DX9_Dll_Loader() throw()
	{
		m_versDll = 0;
		m_hmDLL = 0;

		m_hmDLL = loadDllLastVersion( &m_versDll );
		if(m_versDll == 0)
		{
			throw ( std::runtime_error("Error load d3dx9 dll !") );
		}

	}

    virtual ~CD3DX9_Dll_Loader()
	{
	   if(m_hmDLL)
	   {
		   ::FreeLibrary(m_hmDLL);
		   m_hmDLL = 0;
	   }

		m_versDll = 0;
	}



//-------------------------------------------------------------------------

#define DEF_TEMP_ERR_HANDLE   throw_error( 0 );

	BOOL _D3DXCheckVersion( UINT D3DSDKVersion, UINT D3DXSDKVersion)
	{
		if( !m_fnc.m_TFunc_D3DXCheckVersion ) 
		{
			DEF_TEMP_ERR_HANDLE
		}

		return m_fnc.m_TFunc_D3DXCheckVersion(D3DSDKVersion, D3DXSDKVersion );
	}

	HRESULT _D3DXCreateBuffer( DWORD NumBytes,    LPD3DXBUFFER * ppBuffer )
	{
		if( !m_fnc.m_TFunc_D3DXCreateBuffer )
		{
		  DEF_TEMP_ERR_HANDLE
		}

		return  m_fnc.m_TFunc_D3DXCreateBuffer(NumBytes, ppBuffer );
	};

	HRESULT __D3DXCreateFontA(LPDIRECT3DDEVICE9 pDevice,	INT Height,	UINT Width,	UINT Weight, UINT MipLevels,
		BOOL Italic, DWORD CharSet,	DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily,
		const CHAR* pFacename,	LPD3DXFONT * ppFont	)
	{
				if( !m_fnc.m_TFunc_D3DXCreateFontA )
				{
				  DEF_TEMP_ERR_HANDLE
				}

		return	m_fnc.m_TFunc_D3DXCreateFontA (pDevice,	  Height,	Width,	Weight, MipLevels,
			Italic,   CharSet,	  OutputPrecision,   Quality,   PitchAndFamily,
			pFacename, ppFont	);
	};



	HRESULT __D3DXCreateFontW(LPDIRECT3DDEVICE9 pDevice,	INT Height,	UINT Width,	UINT Weight, UINT MipLevels,
		BOOL Italic, DWORD CharSet,	DWORD OutputPrecision, DWORD Quality, DWORD PitchAndFamily,
		const WCHAR* pFacename,	LPD3DXFONT * ppFont	)
	{
				if( !m_fnc.m_TFunc_D3DXCreateFontW )
				{
					DEF_TEMP_ERR_HANDLE
				}

		return	m_fnc.m_TFunc_D3DXCreateFontW (pDevice,	  Height,	Width,	Weight, MipLevels,
			Italic,   CharSet,	  OutputPrecision,   Quality,   PitchAndFamily,
			pFacename, ppFont	);
	};


	HRESULT __D3DXCreateFontIndirectA( LPDIRECT3DDEVICE9 pDevice, CONST D3DXFONT_DESCA* pDesc, LPD3DXFONT * ppFont )
	{
		  if( !m_fnc.m_TFunc_D3DXCreateFontIndirectA )
		  {
			 DEF_TEMP_ERR_HANDLE
		  }

	   return  m_fnc.m_TFunc_D3DXCreateFontIndirectA( pDevice,   pDesc,  ppFont);
	};


	HRESULT __D3DXCreateFontIndirectW( LPDIRECT3DDEVICE9 pDevice, CONST D3DXFONT_DESCW * pDesc, LPD3DXFONT * ppFont )
	{
		if( !m_fnc.m_TFunc_D3DXCreateFontIndirectW )
		{
			DEF_TEMP_ERR_HANDLE
		}

		return  m_fnc.m_TFunc_D3DXCreateFontIndirectW( pDevice,   pDesc,  ppFont);
	};


	HRESULT __D3DXCreateLine(	LPDIRECT3DDEVICE9 pDevice, LPD3DXLINE* ppLine)
	{
		if(!m_fnc.m_TFunc_D3DXCreateLine)
		{
			DEF_TEMP_ERR_HANDLE
		}

		return m_fnc.m_TFunc_D3DXCreateLine(  pDevice,  ppLine  );
	};


	HRESULT __D3DXCreateRenderToEnvMap(	LPDIRECT3DDEVICE9 pDevice, 	UINT Size,	UINT MipLevels,	 D3DFORMAT Format,
		BOOL DepthStencil, D3DFORMAT DepthStencilFormat, ID3DXRenderToEnvMap** ppRenderToEnvMap	)
	{
		if(!m_fnc.m_TFunc_D3DXCreateRenderToEnvMap)
		{
			DEF_TEMP_ERR_HANDLE
		}

		return m_fnc.m_TFunc_D3DXCreateRenderToEnvMap( pDevice,   Size,	  MipLevels,  Format,
			  DepthStencil,   DepthStencilFormat,   ppRenderToEnvMap);
	};



	HRESULT D3DXCreateRenderToSurface(LPDIRECT3DDEVICE9 pDevice,	UINT Width,	UINT Height,
		D3DFORMAT Format, BOOL DepthStencil, D3DFORMAT DepthStencilFormat,
		LPD3DXRENDERTOSURFACE * ppRenderToSurface   )
	{
		if(!m_fnc.m_TFunc_D3DXCreateRenderToSurface)
		{
			DEF_TEMP_ERR_HANDLE
		}

		return m_fnc.m_TFunc_D3DXCreateRenderToSurface( pDevice, Width,	  Height,
			  Format,   DepthStencil,   DepthStencilFormat, ppRenderToSurface   );
	};


	HRESULT __D3DXCreateSprite(	LPDIRECT3DDEVICE9 pDevice,	LPD3DXSPRITE * ppSprite	)
	{
		if(!m_fnc.m_TFunc_D3DXCreateSprite)
		{
			DEF_TEMP_ERR_HANDLE
		}
		return m_fnc.m_TFunc_D3DXCreateSprite(pDevice,	ppSprite	);
	};



























//-------------------------------------------------------------------------


	Functions m_fnc;

protected:

    void throw_error(int code)
	{
		assert(false);
		if(code == 0)
		{

		}
		throw std::runtime_error("Null pointer !");
	};


	HMODULE m_hmDLL;
	unsigned int m_versDll;

};
 
 

}
// end namespace d3dx9_dynamic_load

}
// end namespace d3d9

}
// end namespace graphics

}
// end namespace gb




#endif // #if ( defined(WIN32) && defined(GB_D3D9) )

// end file