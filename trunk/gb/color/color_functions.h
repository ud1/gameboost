/** \file
 \brief цветовые функции
*/

#pragma once

#include "..\base\Types.h"

#include "color.h"
#include "color_integer.h"
#include "color_def.h"


#include <float.h>
#include <math.h>
#include <string>

#include <assert.h>

//#include "color.h"
//#include "color3.h"
//#include "color4.h"
#include "color_def.h"

namespace gb
{

 namespace color
 {
 
 
//
//  цветовые макросы
//


/**  \brief   Построение цвета по байтам. Альфа первая.   */
inline color32_t make_color_argb( uint8_t a, uint8_t r, uint8_t g, uint8_t b )
{
//#define MAKECOLOR_ARGB(a,r,g,b) 
	//(( uicolor32_t)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
 color32_t res =  ( (a&0xff)<<24 ) | ( (r&0xff)<<16 ) | ( (g&0xff)<<8 ) |  (b&0xff);
 return res;
}


/**   \brief  Построение цвета по байтам. Альфа последняя  */
inline color32_t make_color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a )
{
//#define MAKECOLOR_RGBA(r,g,b,a)   
	// MAKECOLOR_ARGB(a,r,g,b)
 return make_color_argb(a,r,g,b);
}


/*
/ **  \brief   Построение цвета color_rgb24_s  по трём элементам  //  * /
inline color_rgb24_s  make_rgb(uint8_t r, uint8_t g, uint8_t b)
{
//#define MAKECOLOR_RGB(r,g,b)  
// (( color_rgb24_s)( (((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)) )
   color_rgb24_s res = ( (r&0xff)<<16 ) | ( (g&0xff)<<8 ) | ( b&0xff ) ;
   return res;
}
 */


/**  \brief   Построение целочисленого цвета по компонентам float (0.0f ... 1.0f)  */
inline color32_t make_rgba(float r, float g, float b, float a)
{
//#define MAKECOLOR_FLOAT_RGBA(r,g,b,a) \  
	// MAKECOLOR_RGBA((uint32_t)((r)*255.f),(uint32_t)((g)*255.f),(uint32_t)((b)*255.f),(uint32_t)((a)*255.f))
	return make_color_rgba(
		(uint8_t)(r*255.f),(uint8_t) (g*255.f),	(uint8_t)(b*255.f),	(uint8_t)(a*255.f)	
		);
}




#ifdef _D3D9_H_

// 
//	 D3DCOLOR   имеет порядок байт:  a r g b  
// 


//! \brief  Преобразовать стандартный целочисленый D3DCOLOR цвет . 
inline D3DCOLORVALUE make_d3dcolorvalue( D3DCOLOR col )
{
	D3DCOLORVALUE res;

	const float k = 1.0f / 255.0f;

	res.r = k * (float)((col << 8 ) >> 24);
	res.g = k * (float)((col << 16) >> 24);
	res.b = k * (float)((col << 24) >> 24);
	res.a = k * (float)( col >> 24);

	return res;
}

#endif    // _D3D9_H_


/** \brief  Обмен компонентов R и G . */
inline void colorSwapRG(color32_t& color) 
{
	register uint8_t n_g = (uint8_t)(color >> 16); 
	register uint8_t n_r = (uint8_t)(color >> 8); 
	
	color = (color | 0x00FFFF00) ^ 0x00FFFF00 ;
	color |= ((color32_t)n_g << 8);
	color |= ((color32_t)n_r << 16);
}



/** \brief  Обмен компонентов R и B . */
inline void   colorSwapRB(color32_t& color) 
{
	register uint8_t n_B = (uint8_t)(color >> 16); 
	register uint8_t n_R = (uint8_t)(color ); 

	color  =  (color | 0x00FF00FF) ^ 0x00FF00FF ;
	color |= (color32_t)n_B;
	color |= ((color32_t)n_R << 16);
}

 

/** \brief Обмен компонентов G и B .  */
inline void colorSwapGB(color32_t&  color) 
{
	register uint8_t _g  = (uint8_t) ( color >> 8 );
	register uint8_t _b  = (uint8_t) ( color  );

	color = (color | 0x0000FFFF) ^ 0x0000FFFF ;
	color |= ( (color32_t)_g << 0);
	color |= ( (color32_t)_b << 8);  
}



//! \brief  Конвертация 4-х байтового цвета	 порядка RGBA в порядок ARGB
inline  uint32_t   rgba_to_argb( uint32_t val )
{
	return ( (val>>8) | (val<<24)  );
}
							    


//! \brief	 Конвертация 4-х байтового  цвета  порядка ARGB в порядок RGBA 
inline uint32_t   argb_to_rgba( uint32_t val )
{
	return ( (val<<8) | (val>>24) );
}




//
// Выделение компоненты цвета
//
 
 
inline uint8_t   colorExtractA( color32_t color ) 
{  
	return (uint8_t)(color >> 24);   
}

inline uint8_t   colorExtractR( color32_t color ) 
{  
	return (uint8_t)(color >> 16);   
}

inline uint8_t   colorExtractG( color32_t color ) 
{  
	return (uint8_t)(color >> 8);    
}

inline uint8_t   colorExtractB( color32_t color ) 
{  
	return (uint8_t)color;           
}
 

//
// Выделение компоненты цвета   как float
//


 
inline float   colorExtractAf( color32_t col ) 
{  
	return ( ( (float)colorExtractA(col) ) / 255.0f ); 
}

inline float   colorExtractRf( color32_t col ) 
{  
	return ( ( (float)colorExtractR(col) ) / 255.0f );  
}

inline float   colorExtractGf( color32_t col ) 
{  
	return ( ( (float)colorExtractG(col) ) / 255.0f );  
}

inline float   colorExtractBf( color32_t col ) 
{  
	return ( ( (float)colorExtractB(col) ) / 255.0f );  
}


//
// Установка компоненты цвета
//

 

inline void   colorSetA( color32_t& col, uint8_t a ) { col |= 0xFF000000;	col ^= 0xFF000000; col |=(color32_t)(a << 24); };
inline void   colorSetR( color32_t& col, uint8_t r ) { col |= 0x00FF0000; col ^= 0x00FF0000; col |=(color32_t)(r << 16); };
inline void   colorSetG( color32_t& col, uint8_t g ) { col |= 0x0000FF00; col ^= 0x0000FF00; col |=(color32_t)(g <<  8); };
inline void   colorSetB( color32_t& col, uint8_t b ) { col |= 0x000000FF; col ^= 0x000000FF; col |=(color32_t)(b);       };

 


//
// Установка компоненты цвета  по float
//

 
inline void   colorSetAf( color32_t& color, float a ) { colorSetA( color, (uint8_t)( a * 255.0f ) );  };
inline void   colorSetRf( color32_t& color, float r ) { colorSetR( color, (uint8_t)( r * 255.0f ) );  };
inline void   colorSetGf( color32_t& color, float g ) { colorSetG( color, (uint8_t)( g * 255.0f ) );  };
inline void   colorSetBf( color32_t& color, float b ) { colorSetB( color, (uint8_t)( b * 255.0f ) );  };
 




//
//  Обмен цветовых компонентов.
//

inline void  colorRgb24_SwapRG( color_rgb_s& color ) 
{ 
	register uint8_t temp; 
	temp = color.r; 
	color.r=color.g;
	color.g=temp;  
}

inline void  colorRgb24_SwapRB( color_rgb_s& color ) 
{ 
	register uint8_t temp; 
	temp = color.r; 
	color.r=color.b; 
	color.b=temp;  
}

inline void  colorRgb24_SwapGB( color_rgb_s& color )
{ 
	register uint8_t temp; 
	temp = color.g; 
	color.g=color.b; 
	color.b=temp;  
}


/** \brief Конвертация uicolor32_t в color_rgb24_s.  */
color_rgb24_s   color_rgb_fFrom_uicolor (color32_t   color) 
{ 
	color_rgb_s res; 
	res.r=(color >> 16); 
	res.g=(color>>8); 
	res.b=(color); 
	return res;  
}
   
 
 
 
 }
}
