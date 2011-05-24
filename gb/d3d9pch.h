// d3d9pch.h

#pragma once

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
#include <gb/graphics/d3d9/auto_include_libr.h>


// end file