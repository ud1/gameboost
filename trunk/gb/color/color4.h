
#pragma once

#include "..\base\Types.h"
//#include "color_functions.h"
#include "color3.h"

#include <stdio.h>
#include <stdlib.h>

#include <float.h>
#include <math.h>
#include <string>

#include <assert.h>




namespace gb
{

 namespace color
 {
 

	 template <typename T>
	 struct color4
	 {
		 T   r, g, b, a;

		 color4()
		 {
			 r = g = b = a = T();
		 }



	 };


  





 
 
 }
}
