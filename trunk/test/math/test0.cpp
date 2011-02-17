// test math
//

#include "stdafx.h"
#include <windows.h>

//#include "z:\\!!GB_TOADD\\math\\base.h"
//#include "z:\\!!GB_TOADD\\math\\scalar.h"

#include <gb/math/scalar.h>
#include <gb/math/base.h>


//#include "D3dx9math.h"

 //=======================================================================
int _tmain(int argc, _TCHAR* argv[])
{
	int val = gb::math::scalar::round(5353.6457f); 
	val = gb::math::scalar::roundAsm( 5353.6457f );


	return 0;
}

