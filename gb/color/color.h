/** \file  color.h
* \brief Цвет. Сопутствующие типы,  классы, функции.
* 
* \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586 
*

*

 \todo Добавить каст для GLColor  GLFloat  D3DCOLOR  DWORD 
 \todo Переделать макросы на функции
 \todo  print поменять на cout <<

  
*/

#pragma once

#include "..\base\Types.h"

#include <stdio.h>
#include <stdlib.h>

//#include <cfloat>
//#include <cmath>
#include <float.h>
#include <math.h>

//#include <cassert>
#include <assert.h>
#include <string.h>
#include <string>


 

namespace gb
{

     /** \brief Цвет и цветовые операции . */
     namespace color
     {
	 
	 


	 



 

/** \brief Целочисленый 4-х байтовый  цвет.   */
typedef uint32_t    uicolor32_t;   
 






/** \brief  Мононхромное значение  1 байт . */
typedef uint8_t   color_mono_8b_t;


/** \brief  Мононхромное значение из 2-х байт .  */
struct color_mono16b_s 
{
	  union 
	  {
		struct { uint8_t _1, _0 ; };
		uint8_t bytes[2];
		unsigned short ush;
	  };
};


//--------------------------------------------------------

struct ObjectColotType_e
{
	enum e
	{
		UNDEFINED = 0,  ///< не определено


		AMBIENT   = (200 + 1), 
		DIFFUSE   = (200 + 2),
		SPECULAR  = (200 + 3),
		EMISSIVE  = (200 + 4),


		UNUSED_DACLARED_LAST, ///< не используется . Декларировать последним
		UNUSED_FROCE32 = 0xff000000  ///< не используется. Для выравнивания по 4 байтам

	};

	//! перечисление в строку. Вернёт пустую строку, если _enum некорректно.
	std::string tostr(e _enum)
	{
		std::string res;
		switch(_enum)
		{
		case AMBIENT:
			{
			res = "AMBIENT";
			}
			break;

		case DIFFUSE:
			{
			res = "DIFFUSE";
			}
			break;

		case SPECULAR:
			{
			 res = "SPECULAR";
			}
			break;

		case EMISSIVE:
			{
			 res = "EMISSIVE";
			}
			break;

		default:
			{
			}	    
		}

		return res;
	}

	//! перечисление из строки. Вернёт false, если строка некорректна
	bool fromstr(e& outval, const char* str)
	{
		outval = UNDEFINED;
		std::string s = str;
		for(size_t c=0; c<s.length(); c++)
		{
			s[c] = toupper( s[c] );
		}

		if("AMBIENT" == s)
		{
			outval =  AMBIENT;
			return true;
		}

		if("DIFFUSE" == s)
		{
			outval =  DIFFUSE;
			return true;
		}

		if("SPECULAR" == s)
		{
			outval =  SPECULAR;
			return true;
		}

		if("EMISSIVE" == s)
		{
			outval =  EMISSIVE;
			return true;
		}

	  return false;
	}
};

 
//-------------------------------------------------------------------------
 

     }
     // end namespace color

}
// end namespace gb

#include "color_functions.h"
#include "color3.h"
#include "color4.h"
#include "color_integer.h"

 

// end file