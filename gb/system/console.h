/** \file
 \brief  Связаное с консолью вывода  .

  \todo добавить соотв . функции для других платформ.
*/

#pragma once

namespace gb 
{

namespace system
{

//!  \brief  Связаное с консолью вывода  .
namespace console
{

//------------------------------------------------------------

#ifdef WIN32  //  windows spec

 

#define     GB_SYS_CCOL_WHITE  0x07  
#define     GB_SYS_CCOL_RED    0x0C 
#define     GB_SYS_CCOL_GREEN  0x0A  
#define     GB_SYS_CCOL_BLUE   0x01 

#define     GB_SYS_CCOL_BLUESKY	0x0B
#define     GB_SYS_CCOL_PINK       0x0D
#define     GB_SYS_CCOL_YELLOW     0x0E

#define     GB_SYS_CCOL_GROW       0x08

/** \brief Установить цвет вывода текста консоли. <br>
 Старший хекс - цвет фона,  младший - цвет текста.
 \code
 ЦВЕТА:

 0x02 - зелёный   
 0x03 - голубой  
 0x04 - красный
 0x05 - розовый   
 0x06 - жёлтый    
 0x09 - голубой   
 

 FOREGROUND_BLUE      0x0001 // text color contains blue.
 FOREGROUND_GREEN     0x0002 // text color contains green.
 FOREGROUND_RED       0x0004 // text color contains red.
 FOREGROUND_INTENSITY 0x0008 // text color is intensified.
 BACKGROUND_BLUE      0x0010 // background color contains blue.
 BACKGROUND_GREEN     0x0020 // background color contains green.
 BACKGROUND_RED       0x0040 // background color contains red.
 BACKGROUND_INTENSITY 0x0080 // background color is intensified.  

 \endcode  */
inline int setTextColorB(BYTE color = 0x07) 
{
	HANDLE hStdout;  hStdout = GetStdHandle( STD_OUTPUT_HANDLE ); 
	if ( hStdout == INVALID_HANDLE_VALUE )  
	{  
		return -1; 	
	} 
	
	// FOREGROUND_RED|FOREGROUND_INTENSITY 
	WORD attr =   FOREGROUND_INTENSITY | ( (WORD)color) ;
	if ( !SetConsoleTextAttribute(hStdout, attr ) )  
	{   
		return  -1;  	
	}

   return 0;
}

inline int setTextColor(WORD color = 0x0007) 
{  
	HANDLE hStdout;  hStdout = GetStdHandle( STD_OUTPUT_HANDLE ); 
	if ( hStdout == INVALID_HANDLE_VALUE )  {  return -1; 	} 
	if (! SetConsoleTextAttribute(hStdout, color ) )  {   return  -1;  	}; 
	return 0;
}

inline int setTextColorWhite()  {  return setTextColorB(GB_SYS_CCOL_WHITE);  }
inline int setTextColorRed  ()  {  return setTextColorB(GB_SYS_CCOL_RED);  }
inline int setTextColorGreen()  {  return setTextColorB(GB_SYS_CCOL_GREEN);  }
inline int setTextColorBlue ()  {  return setTextColorB(GB_SYS_CCOL_BLUE);  }
inline int setTextColorGlow ()  {  return setTextColorB(GB_SYS_CCOL_GROW);  }
inline int setTextColorPink ()  {  return setTextColorB(GB_SYS_CCOL_PINK);  }
inline int setTextColorYellow() {  return setTextColorB(GB_SYS_CCOL_YELLOW);  }



#endif // WIN32	 spec



//------------------------------------------------------------

}
}
}

// end file