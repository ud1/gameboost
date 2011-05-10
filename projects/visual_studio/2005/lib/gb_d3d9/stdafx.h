// pch for gb_d3d9

#include  <TCHAR.h>


#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>

#include <d3d9.h>

#pragma warning (disable:4995)

//#include <gb/graphics/d3d9/auto_include_libr.h>


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

#include <gb/math/math.h>

#include <boost/algorithm/string.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

// end file