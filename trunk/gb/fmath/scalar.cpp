﻿
//#include "pch.h"
#include "d3d9pch.h"

//#include "stdafx.h"


#include <gb/fmath/fmath.h>
#include <stdlib.h>
#include <time.h>


namespace gb 
{
namespace fmath
{
namespace scalar
{

//=====================================================================	
	
	//int round(float f) 
	//{
	//	 if(f == 0.0f) return 0;
	//	register int res = (int)f;

	//	register float ffmod = fmod(f, 1.0f);
	//	if( f > 0.0f ) {
	//		if(ffmod > 0.5f) { res++; return res;  };
	//		return res;
	//		} 
	//	if(f < 0.0f){
	//		if(ffmod < -0.5f) { res--; return res;  };
	//		return res;
	//		}
	//	return res;
	//};	
	

//=====================================================================

	//=================================================================
	float random() 
	{
		static bool sbFirstCall = true;
		static int stime;

		if(sbFirstCall) { 
			sbFirstCall = false; 

			stime=  (int32_t)(time(NULL)/2);  
			srand(stime);  
		}


		return  (float) ::rand() /  (float)RAND_MAX   ;
	}

	
	
//=====================================================================	
	
}
// end namespace
}
// end namespace
}
// end namespace

// end file