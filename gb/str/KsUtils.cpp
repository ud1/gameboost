/*! \file  KsUtils.cpp
 * \brief Разнообразные классы , типы для разных задач 
 * \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
 * \author Reviewer/imported by: kvakvs (kvakvs@yandex.ru)
 */


 
#include <gb/str/KsUtils.h>
 
#include <ostream>
#include <iostream>

#pragma warning (push)
#pragma warning (disable : 4996)
#pragma warning (disable : 4290)

 
#ifdef _WIN32
//=====================================================
float gb::util::getCurrHeightPrecTime( ) 
{
   LARGE_INTEGER tm, freq;   
   QueryPerformanceCounter(&tm);
   QueryPerformanceFrequency(&freq);
	  return   (   ( (float)tm.QuadPart ) / ( (float)freq.QuadPart )   );
};

//=====================================================
int gb::util::getCursorWindowPosition(HWND hwnd, POINT* pout) 
{
  BOOL res = ::GetCursorPos(pout);
	 res &= ::ScreenToClient(hwnd, pout);
 if(res) return 0;
	return  -1;
};
#endif



//====================================================

 

#pragma warning(pop)

// end file