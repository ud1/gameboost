/** \file

 \brief  функции создания эффектов.

 \author ksacvet777

*/

#if ( defined(WIN32) && defined(__D3DX9_H__) )

#pragma once

#include <gb/graphics/d3d9/auto_include_libr.h>

#include <d3dx9.h>
#include <string>

#include <gb/graphics/d3d9/d3dx9_dynamic_load/d3dx9_dynamic_load.h>
using   gb::graphics::d3d9::d3dx9_dynamic_load::CD3DX9_Dll_Loader;


namespace gb
{

namespace graphics
{

namespace d3d9
{

//! \brief Специфика для d3d9 шейдеров формата fx , интерфейса ID3DXEffect
namespace fx
{
	//------------------------------------------------------------------------



	

	//! \brief Опции создания эффекта.
	struct CreateEffectOptions
	{
		DWORD dwFlags;
		ID3DXEffectPool* pPool;
		const D3DXMACRO* macro;
		ID3DXInclude* include; 
		const char* pSkipConstants;

		/** \brief В конструкторе только константы, остальное в ноль/NULL.
		               Заполнить поля при необходимости.  */
		CreateEffectOptions(const D3DXMACRO* pmacro, const char* _pSkipConstants ) 
			: macro(pmacro), pSkipConstants(_pSkipConstants) 
		{
			dwFlags=0;
			pPool=NULL;
			macro=NULL;
			include=NULL;
			pSkipConstants=NULL;
		}

	};
 
	//! \brief  Создать эффекта из текста.
	inline HRESULT createEffectFromText(
		ID3DXEffect** ppOut,
		CD3DX9_Dll_Loader* pD3DXdllLoader,
		IDirect3DDevice9* pdevice,
		const char* effectText,
		std::string& strError,
		const CreateEffectOptions* pOpt,
		bool bThrowMsgBoxIfError
		)

	{
		HRESULT hr =S_OK;
 
		strError = "";
		const UINT LEN = (UINT)strlen(effectText);
		ID3DXBuffer* pCompilationErrors = NULL;
		hr |= pD3DXdllLoader->D3DXCreateEffectEx(pdevice,(LPCVOID)effectText, LEN,
			pOpt->macro, 
			pOpt->include, 
			pOpt->pSkipConstants, 
			pOpt->dwFlags, 
			pOpt->pPool,
			ppOut, &pCompilationErrors  );

		if FAILED(hr)
		{
			if(pCompilationErrors)
			{
				char* data = new  char[pCompilationErrors->GetBufferSize()+2];
				memcpy(
					data, 
					pCompilationErrors->GetBufferPointer(), 
					pCompilationErrors->GetBufferSize() );
				data[pCompilationErrors->GetBufferSize()+1] = '\0';
				strError = data;
				delete [] data;
			  pCompilationErrors->Release();
			  pCompilationErrors = NULL;
			}
			else
			{
				strError = "";
			}

			if(bThrowMsgBoxIfError)
			{
				std::string strTextError = "Compilation error: \n";
				strTextError += strError;
				MessageBoxA(0, strTextError.c_str(), "Create effect error", MB_OK|MB_ICONERROR|MB_TASKMODAL|MB_TOPMOST );
			}

		}

		return hr;
	}






	//------------------------------------------------------------------------
}
}
}
}


#endif
// end file