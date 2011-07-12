/** \file
 \brief трёхкомпонентный цвет по RGB
*/

#pragma once

#include "..\base\Types.h"
//#include "color_functions.h"
#include "color4.h"


#include <string>
#include <float.h>
#include <math.h>

#include <assert.h>

 #pragma message("  убрать print. заменить на <<  "  __FILE__ )


namespace gb
{

 namespace color
 {

	 template <typename T>
	 struct color3
	 {
		 T   r, g, b;

		 color3()
		 {
			 r = g = b = T();
		 }


	 };



 
 
 }
}
