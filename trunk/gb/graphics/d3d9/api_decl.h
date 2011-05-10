/** \file 
 \brief  декларация макроса экспорта/импорта для испольхзования DLL.
 Спецификация экспорта функций  для gb::graphic::d3d9 .



 \author ksacvet777
*/

#pragma once


#ifdef GB_D3D9_DLL

#ifdef GB_D3D9_DLL_EXPORTS
  #define GB_D3D9_API __declspec(dllexport)
#else
  #define GB_D3D9_API __declspec(dllimport)
#endif

#else

#define	 GB_D3D9_API

#endif // #ifdef GB_D3D9_DLL


// end file