/** \file
 \brief integer color types
*/

#pragma once

#include "..\base\Types.h"
#include "color_functions.h"
#include "color3.h"
#include "color4.h"




namespace gb
{

 namespace color
 {
 
 



	 /** \brief  Целочисленый 3-х байтовый цвет  без альфа-компоненты .   */
	 //struct color_rgb24_s
	 //{ 
	 //  uint8_t r, g, b; 
	 //};
	 typedef color3<uint8_t> color_rgb_s;




	 /** \brief Целочисленый 4-х байтовый  цвет.   */
	 typedef uint32_t    uicolor32_t;   

 
 
 
 }
}
