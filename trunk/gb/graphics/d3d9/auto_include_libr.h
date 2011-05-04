/** \file 
 \brief  Заголовок для подключения  всех статических  библиотек необходимых для запуска d3d9-приложения

  \author xx
 
 */
 
#pragma once


// library
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )

#ifdef GB_D3DX9

  #include <d3dx9.h>
  #include <D3dx9core.h>
  #include <D3dx9math.h>
  #include <D3dx9shape.h>

	#if defined(DEBUG) || defined(_DEBUG)
	      #pragma comment( lib, "d3dx9d.lib" )
	#else
	      #pragma comment( lib, "d3dx9.lib" )
	#endif
#endif

 
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )

#include <dxerr.h>
#include <mmsystem.h>
#include <mmreg.h>


// end file