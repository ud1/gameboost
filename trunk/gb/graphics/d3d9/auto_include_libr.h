/** \file 
 \brief  Заголовок для подключения  всех статических  библиотек необходимых 
 для запуска d3d9-приложения.

  \author ksacvet777
 
 */
 
#pragma once


// library d3d9

#pragma comment( lib, "dxguid.lib" )

// library d3dx9
#ifdef GB_D3DX9

  #include <d3dx9.h>
 
	#if defined(DEBUG) || defined(_DEBUG)
	      #pragma comment( lib, "d3dx9d.lib" )
	#else
	      #pragma comment( lib, "d3dx9.lib" )
	#endif
#endif

 // library d3d9
#pragma comment( lib, "d3d9.lib" )



#include <dxerr.h>
#pragma comment( lib, "dxerr.lib" )

 // library win32 
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )
#include <mmsystem.h>
#include <mmreg.h>


// library gameboost d3d9 

#ifndef _LIB_GB_D3D9
	#ifdef _DEBUG
		#pragma comment( lib , "gb_d3d9_d.lib" )
	#else
		#pragma comment( lib , "gb_d3d9.lib" )
	#endif
#endif


// end file