

#include "stdafx.h"
//#include "pch.h"

//#include "z:\\!!GB_TOADD\\math\\scalar.h"
#include <gb/math/scalar.h>

namespace gb 
{
  namespace math
  {
    namespace scalar
	{
	
	//=============================================================
	int round(float f) 
	{
		 if(f == 0.0f) return 0;
		register int res = (int)f;

		register float ffmod = fmod(f, 1.0f);
		if( f > 0.0f ) {
			if(ffmod > 0.5f) { res++; return res;  };
			return res;
			} 
		if(f < 0.0f){
			if(ffmod < -0.5f) { res--; return res;  };
			return res;
			}
		return res;
	};	
	
	
	
	
	
	}
  }
}
// end file