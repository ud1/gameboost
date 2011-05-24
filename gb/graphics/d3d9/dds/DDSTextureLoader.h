/** \file
 \brief Извелчённый из одного из примеровзагрузчик текстур dds формата 
   без использовани  библиотеки D3DX9.  С некоторыми модификациями. <br>
  <hr>
 Functions for loading a DDS texture without using D3DX
  Copyright (c) Microsoft Corporation. All rights reserved.

  <br><br>

  \todo  сделать загрузку объёмных текстур
  \todo  сделать загрузку кубических текстур

*/
 

//#include <ddraw.h>
#include <dxgitype.h>
#include <d3d9.h>

#include <gb/graphics/d3d9/api_decl.h>

 


//! \brief Опции расширенного создания текстуры из dds файла  для передачи в CreateDDSTextureFromFile
class CreateDDSOptions {
public:

	UINT mipLevels;
	DWORD usage;
	D3DFORMAT format;
	D3DPOOL  pool;

   //! \brief   Конструктор заполняет по умолчанию.
   CreateDDSOptions()
   {
	  mipLevels = 0;
	  usage     = 0;
	  format = D3DFMT_UNKNOWN;
	  pool   = D3DPOOL_DEFAULT;
   }
};



GB_D3D9_API HRESULT CreateDDSTextureFromFileA( LPDIRECT3DDEVICE9 pDev,  
								  CHAR* szFileName,
								  IDirect3DTexture9** ppTex,
								  const CreateDDSOptions* pOpt);







GB_D3D9_API HRESULT CreateDDSTextureFromFileW( LPDIRECT3DDEVICE9 pDev, 
										   WCHAR* szFileName, 
										   IDirect3DTexture9** ppTex,
										   const CreateDDSOptions* pOpt);
 
