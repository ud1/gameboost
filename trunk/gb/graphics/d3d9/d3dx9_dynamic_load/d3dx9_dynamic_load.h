/** \file
 \brief Динамическая загрузка/ использование DLL   библиотеки D3DX9


  \author kscvet777

  \todo поправить функцию  checkExistsDll на поиск в директории приложения.
  \todo убрать DEF_TEMP_ERR_HANDLE

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

#include <assert.h>


namespace  gb
{

namespace  graphics
{

namespace  d3d9
{

//!  \brief Динамическая загрузка/ использование DLL   библиотеки D3DX9 .
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

  
  
//! \brief   Получить файл d3dx dll по номеру версии   
GB_D3D9_API void  makeD3DX9dllFilename_by_version(std::string& strOut, unsigned int vers, bool bDebugV=false) ;



//! \brief  ПРоверить существует ли dll? bIncludeExeDir - проверить или не тдиректорию где приложение 
GB_D3D9_API bool checkDllExistsA (const char* fname, bool bIncludeExeDir) ;
 
//!  \brief  УБРАТЬ !
GB_D3D9_API bool checkExistsDll(const char* sDllFilename) ;
 
//! \brief получить самую последнюю версию установленой библиотеки.
GB_D3D9_API bool getInstaledD3DXlastVersion(unsigned int* piOutVers) ;


//! \brief вывод  на консоль информации об обнаруженых в системе d3dx9 dll .
GB_D3D9_API void print_d3dx9_dll_info() ;


//! \brief  получит все инсталированые версии d3dx dll в системе.
GB_D3D9_API bool getInstaledD3DXallVersion(std::vector<unsigned int>& versions) ;

 

/**  \brief Загрузаить новейшую версию d3dx9 dll обнаруженную в системе.  Вернёт хэндл загр. длл.
  Еслит ошибка вернёт ноль.  piOutVers - версия, которая была загружена.       */
GB_D3D9_API HMODULE loadDllLastVersion(unsigned int* piOutVers ); 
 

//! \brief  Загрузчик d3dx9 dll  . Так же использование d3dx9  через него. 
class CD3DX9_Dll_Loader {
public:

    /** \brief Конструктор выполняет загрузку новейшей версии d3dx9 dll , 
	обнаруженой в системе.  Если ничего не найдено  бросает исключение.  */
	CD3DX9_Dll_Loader() throw()
	{
		m_versDll = 0;
		m_hmDLL = 0;

		m_hmDLL = loadDllLastVersion( &m_versDll );
		if(m_versDll == 0)
		{
			throw ( std::runtime_error("Error load d3dx9 dll !") );
		}

		int nres = m_fnc.GetProcAddr(m_hmDLL);

		if( nres<0 )
		{
			throw ( std::runtime_error("Invalid operation") );
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
	
	//! \brief  Получить версию загруженой d3dx9 dll .
	unsigned int  getLoadedD3DX9dll_version() const 
	{
	  return m_versDll;
	}



//-------------------------------------------------------------------------


	//! temp!  времянка  убрать !!!!!
#define DEF_TEMP_ERR_HANDLE   throw_error( "Operation error" );


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