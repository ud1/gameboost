

#pragma once

#include "color3.h"
#include "color4.h"


// dsadsс  

namespace gb
{

	namespace color
	{







		//typedef  color_rgb24_s    color_rgb_s;




		/** \brief float-цвет в виде структуры. 
		Для выполнения операций использовать  статические методы класса Color4f.  */
		//struct color4f_s : public color4<float>
		//{
		//float r, g, b, a;
		//};
		// typedef  color4<float>  color4f_s;  




		/** \brief  Обозначение целочисленого 4-х компонентного  цвета по байтам.   */
		//struct color_rgba_s 
		//{ 
		//  uint8_t r, g, b, a; 
		//};
		typedef color4<uint8_t> color_rgba_s; 





	}
}
