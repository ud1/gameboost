

#pragma once

#include "console.h"
#include "filefunc.h"
#include "Path.h"
#include "winappl.h"

#ifdef GB_LIB
	#ifndef _LIB_GB_SYS
		#ifdef _DEBUG
			  #pragma comment(lib , "gb_sys_d.lib")
		#else
			  #pragma comment(lib , "gb_sys.lib")
		#endif 
	#endif
#endif


namespace gb
{
  namespace system
  {

	  //-------------------------------------------------------

 
	
	  //-------------------------------------------------------
  }
}


// end file