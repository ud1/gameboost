// d3d9pch.h

#pragma once

#pragma warning(disable : 4995)

#ifndef STRICT
#define STRICT
#endif

#define WINVER 0x0500

// If app hasn't choosen, set to work with Windows 98, Windows Me, Windows 2000, Windows XP and beyond
#ifndef WINVER
#define WINVER         0x0410
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410 
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0500 
#endif	


#include <d3d9.h>

#ifdef GB_D3DX9
  #include <d3dx9.h>
#endif

#pragma warning( disable : 4996 )

#include <gb/graphics/d3d9/auto_include_libr.h>
#include <gb/graphics/d3d9/api_decl.h>


#include <gb/macro.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <lm.h>

#include <algorithm>
#include <string>
#include <iterator>
#include <vector>
#include <list>
#include <stdexcept>

#include <assert.h>

#include <typeinfo.h>


// end file