/** \file  color.h
* \brief Цвет. Сопутствующие типы,  классы, функции.
* 
* \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586 
*

*
 \todo  Добавить 
 \todo Добавить каст для GLColor  GLFloat  D3DCOLOR  DWORD 
 \todo Переделать макросы на функции
 \todo  print поменять на cout <<

*   
*/

/******************************************************************

STORY:

--- Поправлен кодстайл.. Прочие незначительные поправки улучшающие читаемость .
--- поправлены методы классов. Некоторая коррекция.
--- обёрнуто макрозащитой GB_COLOR
--- функции:  uicolor32_t  rgba_to_argb(uicolor32_t val);  uicolor32_t  argb_to_rgba(uicolor32_t val)


******************************************************************/

//#ifdef GB_COLOR	// макрозащита ( СНЯТА ! )

#pragma once

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

#include <gb\base\Types.h>
 

namespace gb
{

     /** \brief Цвет и цветовые операции . */
     namespace color
     {



/** \brief float-цвет в виде структуры. 
   Для выполнения операций использовать  статические методы класса Color4f.  */
struct color4f_s {
    float r, g, b, a;
};
 

/** \brief Целочисленый 4-х байтовый  цвет.   */
typedef uint32_t    uicolor32_t;   
 

/** \brief  Обозначение целочисленого 4-х компонентного  цвета по байтам.   */
struct color_rgba_s { 
    uint8_t r, g, b, a; 
};


/** \brief  Целочисленый 3-х байтовый цвет  без альфа-компоненты .   */
struct color_rgb24_s  { 
    uint8_t r, g, b; 
};


/** \brief  Мононхромное значение  1 байт . */
typedef uint8_t   color_mono_8b_t;


/** \brief  Мононхромное значение из 2-х байт .  */
struct color_mono16b_s {
	  union 
	  {
		struct { uint8_t _1, _0 ; };
		uint8_t bytes[2];
		unsigned short ush;
	  };
};


//
//  цветовые макросы
//


/**  \brief  Макрос построения цвета по байтам. Альфа первая.   */
#define MAKECOLOR_ARGB(a,r,g,b) (( uicolor32_t)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

/**  Макрос построения цвета по байтам. Альфа последняя  */
#define MAKECOLOR_RGBA(r,g,b,a)   MAKECOLOR_ARGB(a,r,g,b)

/**  \brief Макрос построения цвета color_rgb24_s  по трём элементам    */
#define MAKECOLOR_RGB(r,g,b)  (( color_rgb24_s)( (((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)) )

/**  \brief Макрос построения целочисленого цвета по компонентам float (0.0f ... 1.0f)  */
#define MAKECOLOR_FLOAT_RGBA(r,g,b,a) \  MAKECOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))


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
inline void colorSwapRG(uicolor32_t& color) 
{
   register uint8_t n_g = (uint8_t)(color >> 16); 
   register uint8_t n_r = (uint8_t)(color >> 8); 
  color = (color | 0x00FFFF00) ^ 0x00FFFF00 ;
  color |= ((uicolor32_t)n_g << 8);
  color |= ((uicolor32_t)n_r << 16);
};



/** \brief  Обмен компонентов R и B . */
inline void   colorSwapRB(uicolor32_t& color) 
{
  register uint8_t n_B = (uint8_t)(color >> 16); 
  register uint8_t n_R = (uint8_t)(color ); 

  color  =  (color | 0x00FF00FF) ^ 0x00FF00FF ;
  color |= (uicolor32_t)n_B;
  color |= ((uicolor32_t)n_R << 16);
};

 

/** \brief Обмен компонентов G и B .  */
inline void colorSwapGB(uicolor32_t&  color) 
{
   register uint8_t _g  = (uint8_t) ( color >> 8 );
   register uint8_t _b  = (uint8_t) ( color  );

  color = (color | 0x0000FFFF) ^ 0x0000FFFF ;
  color |= ( (uicolor32_t)_g << 0);
  color |= ( (uicolor32_t)_b << 8);  
};



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
 
 
inline uint8_t   colorExtractA( uicolor32_t color ) {  return (uint8_t)(color >> 24);   };
inline uint8_t   colorExtractR( uicolor32_t color ) {  return (uint8_t)(color >> 16);   };
inline uint8_t   colorExtractG( uicolor32_t color ) {  return (uint8_t)(color >> 8);    };
inline uint8_t   colorExtractB( uicolor32_t color ) {  return (uint8_t)color;           };
 

//
// Выделение компоненты цвета   как float
//


 
inline float   colorExtractAf( uicolor32_t col ) {  return ( ( (float)colorExtractA(col) ) / 255.0f );  };
inline float   colorExtractRf( uicolor32_t col ) {  return ( ( (float)colorExtractR(col) ) / 255.0f );  };
inline float   colorExtractGf( uicolor32_t col ) {  return ( ( (float)colorExtractG(col) ) / 255.0f );  };
inline float   colorExtractBf( uicolor32_t col ) {  return ( ( (float)colorExtractB(col) ) / 255.0f );  };
 

//
// Установка компоненты цвета
//

 

inline void   colorSetA( uicolor32_t& col, uint8_t a ) { col |= 0xFF000000;	col ^= 0xFF000000; col |=(uicolor32_t)(a << 24); };
inline void   colorSetR( uicolor32_t& col, uint8_t r ) { col |= 0x00FF0000; col ^= 0x00FF0000; col |=(uicolor32_t)(r << 16); };
inline void   colorSetG( uicolor32_t& col, uint8_t g ) { col |= 0x0000FF00; col ^= 0x0000FF00; col |=(uicolor32_t)(g <<  8); };
inline void   colorSetB( uicolor32_t& col, uint8_t b ) { col |= 0x000000FF; col ^= 0x000000FF; col |=(uicolor32_t)(b);       };

 


//
// Установка компоненты цвета  по float
//

 
inline void   colorSetAf( uicolor32_t& color, float a ) { colorSetA( color, (uint8_t)( a * 255.0f ) );  };
inline void   colorSetRf( uicolor32_t& color, float r ) { colorSetR( color, (uint8_t)( r * 255.0f ) );  };
inline void   colorSetGf( uicolor32_t& color, float g ) { colorSetG( color, (uint8_t)( g * 255.0f ) );  };
inline void   colorSetBf( uicolor32_t& color, float b ) { colorSetB( color, (uint8_t)( b * 255.0f ) );  };
 




//
//  Обмен цветовых компонентов.
//

inline void  colorRgb24_SwapRG( color_rgb24_s& color ) { register uint8_t temp; temp = color.r; color.r=color.g; color.g=temp;  };
inline void  colorRgb24_SwapRB( color_rgb24_s& color ) { register uint8_t temp; temp = color.r; color.r=color.b; color.b=temp;  };
inline void  colorRgb24_SwapGB( color_rgb24_s& color ) { register uint8_t temp; temp = color.g; color.g=color.b; color.b=temp;  };


/** \brief Конвертация uicolor32_t в color_rgb24_s.  */
inline color_rgb24_s   colorRgbFromUiColor (uicolor32_t color) { register color_rgb24_s res; res.r=(color >> 16); res.g=(color>>8); res.b=(color); return res;  };
   
//--------------------------------------------------------

struct ObjectColotType_e
{
	enum e
	{
		UNDEFINED = 0,  ///< не определено

		AMBIENT, 
		DIFFUSE,
		SPECULAR,
		EMISSIVE 

	};

	//! перечисление в строку. Вернёт пустую строку, если _enum некорректно.
	std::string e_tostr(e _enum)
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
	bool e_fromstr(e& outval, const char* str)
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





//--------------------------------------------------------


/**  \brief   Класс  Трёхкомпонентный стандартный цвет по float . */
class Color3f {
public:
  union 
  {
    struct {   float r, g, b;  };
    float floats[3];
  };

  inline Color3f() {};
  inline Color3f(const Color3f& col)           { r=col.r;   g=col.g;   b=col.b;   };
  inline Color3f(const Color3f* col)           { r=col->r;  g=col->g;  b=col->b;  };
  inline Color3f(float _r, float _g, float _b) { r=_r;      g=_g;      b=_b;      };

  inline Color3f(const color4f_s& col )         { r=col.r;   g=col.g;   b=col.b;   };

  inline Color3f& set(float _r, float _g, float _b) { r=_r; g=_g; b=_b;  return *this;  };

  /** \brief Проверка каждого на ноль. */
  inline bool empty() const { return (r==0.0f) && (g==0.0f) && (b==0.0f); };
  /** \brief обнулить */
  inline void setzero() { r=g=b=0.0f; };

  /** \brief Установить как белый цвет */
  inline Color3f& setWhite( ) { r=g=b=1.0f;  return *this; };
  /** \brief Установить как чёрный цвет */
  inline Color3f& setBlack( ) { r=g=b=0.0f;   return *this; };
  /** \brief  масштабирование . Изменение яркости. */
  inline Color3f& scale(float f) { r*=f; g*=f; b*=f;  return *this; };


  /** \brief Отсечение значений в пределах 0.0 ... 1.0  */
  inline Color3f& saturate() {
    if(r>1.0f) r=1.0f;   if(r<0.0f) r=0.0f;
    if(g>1.0f) g=1.0f;   if(g<0.0f) g=0.0f; 
    if(b>1.0f) b=1.0f;   if(b<0.0f) b=0.0f; 
	return *this;
  };

 
  inline bool compare(const Color3f& c) const { return (r==c.r) && (g==c.g) && (b==c.b) ; };

  inline Color3f& operator = (const uicolor32_t col) 
  {
	  r = colorExtractRf(col);
	  g = colorExtractGf(col);
	  b = colorExtractBf(col); 
	   return *this;
  };

  inline Color3f& operator = (const color_rgb24_s col) 
  {
	  r = ( (float)col.r ) / 255.0f ;
	  g = ( (float)col.g ) / 255.0f ;
	  b = ( (float)col.b ) / 255.0f ;
	   return *this;
  };

  inline bool operator == (const Color3f& c) const  { return (r==c.r) && (g==c.g) && (b==c.b);  };
  inline bool operator != (const Color3f& c) const  { return (r!=c.r) && (g!=c.g) && (b!=c.b);  };

  inline Color3f& operator *= (const Color3f& c)        { r*=c.r; g*=c.g;  b*=c.b;   return *this;  };
  inline Color3f& operator *= (float f)                 { r*=f;   g*=f;    b*=f;     return *this;  };
  inline Color3f& operator += (const Color3f& c)        { r+=c.r; g+=c.g;  b+=c.b;   return *this;  };
  inline Color3f& operator += (float f)                 { r+=f;   g+=f;    b+=f;     return *this;  };

  inline Color3f operator *  (const Color3f& c) const  { Color3f res(r*c.r, g*c.g, b*c.b );   return res;  };
  inline Color3f operator *  (float f)   const         { Color3f res(r*f,   g*f,   b*f   );   return res;  };
  inline Color3f operator +  (const Color3f& c) const  { Color3f res(r+c.r, g+c.g, b+c.b );   return res;  };
  inline Color3f operator +  (float f) const           { Color3f res(r+f,   g+f,   b+f   );   return res;  };


    #pragma warning (push)
      #pragma warning (disable : 4996)


    /** \brief Конвертация в строку.  Разделитель:  пробел */
    std::string tostr() const 
	{
		 std::string r;
         char ss[32];
         ss[0] = 0;
         sprintf(ss, "%f  %f  %f", r, g, b );
		 r = ss;
         return r;
    };

    /** \brief   Чтение значений из строки разд. пробелами  */
	inline bool fromstr(const std::string&  s) 
	{
      const int SCRES = sscanf(s.c_str(), "%f  %f  %f", &r, &g, &b );
       if( SCRES != 3  ) return false;
        return true;
    };


     #pragma warning (pop)

	/** \brief печать значений на консоль */
    inline void print() const { printf( "%f  %f  %f", r, g, b);  };
 

};
// end class


//-----------------------------------------------------------------------


/**  \brief   Класс  Четырёхкомпонентный стандартный цвет по float . */
class Color4f {
public:
  union 
    {
    struct {   float r, g, b, a;  };
    float floats[4];
    };  

    inline Color4f() {};
    inline Color4f(const Color4f* color) {r=color->r; g=color->g; b=color->b; a=color->a; };
    inline Color4f(const Color4f& col) { r=col.r; g=col.g; b=col.b; a=col.a;  };  
    inline Color4f(float _r, float _g, float _b) {r=_r; g=_g; b=_b; a=1.0f; };   
    inline Color4f(float _r, float _g, float _b, float _a) {r=_r; g=_g; b=_b; a=_a; }; 

  /** \brief Конструктор по байтам ( 0->0.0f   ,  255->1.0f ) */
  inline Color4f( uint8_t _r,  uint8_t _g,  uint8_t _b,  uint8_t _a ) 
  {
	  r=(float)_r/255.5f; 
	  g=(float)_g/255.0f; 
	  b=(float)_b/255.0f; 
	  a=(float)_a/255.0f; 
  }

 
 // inline void set   (const Color4f* cSrc)   {r=cSrc->r;  g=cSrc->g;  b=cSrc->b;  a=cSrc->a;  };
  //inline void set_to(Color4f* cDest) const  {cDest->r=r; cDest->g=g; cDest->b=b; cDest->a=a; };

  /** \brief  проверка  каждый компонент ноль */
  inline bool empty() const { return (r==0.0f) && (g==0.0f) && (b==0.0f) && (a==0.0f); };
  /** \brief  занулить каждый компонент. */
  inline void setzero() { r=g=b=a=0.0f; };

    /** \brief установка значений из байт с переводом в float формат (0.0f ... 1.0f)  */
  inline Color4f& set_bytes(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) 
  { 
	  r=(float)_r/255.5f; 
	  g=(float)_g/255.0f; 
	  b=(float)_b/255.0f;
	  a=(float)_a/255.0f; 
	   return *this;
  }
 
  /** \brief Построение цвета  из целочисленого 4-x  байтового цвета.  */
  inline void operator =  (const uicolor32_t val) 
  {
     a =  (float)  (val >> 24)         / 255.0f;
     r =  (float)( (val << 8 ) >> 24 ) / 255.0f;
     g =  (float)( (val << 16) >> 24 ) / 255.0f;
     b =  (float)( (val << 24) >> 24 ) / 255.0f;
  }

  /** \brief Установить белый цвет  */
  inline Color4f& setWhite(float _a=1.0f) {r=g=b=1.0f; a=_a;  return *this; };
  /** \brief Установить чёрный цвет  */
  inline Color4f& setBlack(float _a=1.0f) {r=g=b=0.0f; a=_a;  return *this; };

  inline operator    uicolor32_t() const   
  { 
	  return 
		        (uicolor32_t)( ((uicolor32_t)(a * 255.0f) << 24 ) 
		  |   ( (uicolor32_t)(r * 255.0f) << 16 ) 
		  |   ( (uicolor32_t)(g * 255.0f) << 8 )  
		  |   ( (uicolor32_t)(b * 255.0f) ) ) ;  
  };

 

  inline void  operator = (const color_rgba_s& color) 
  { 
	  r=  ( (float)color.r ) / 255.0f; 
      g=  ( (float)color.g ) / 255.0f; 
      b=  ( (float)color.b ) / 255.0f; 
      a=  ( (float)color.a ) / 255.0f;  
  };

  inline operator color_rgba_s() const   
  {  
	    color_rgba_s res;   
	  res.r=(uint8_t)(r * 255.0f); 
	  res.g=(uint8_t)(g * 255.0f); 
	  res.b=(uint8_t)(b * 255.0f); 
	  res.a=(uint8_t)(a * 255.0f); 
	  return res;  
  };

  inline void  operator = (const color_rgb24_s color)    
  { 
	  r=((float)color.r) / 255.0f;      
      g=((float)color.g) / 255.0f;     
	  b=((float)color.b) / 255.0f;  
  };

  inline  operator color_rgb24_s() const   
  { 
	  color_rgb24_s res;   
      res.r=  (uint8_t)(r * 255.0f); 
	  res.g=  (uint8_t)(g * 255.0f); 
	  res.b=  (uint8_t)(b * 255.0f);  
      return res; 
  };

  /** \brief сложение  */
  inline Color4f& add(const Color4f& color)     
  {
	  r+=color.r; 
	  g+=color.g; 
	  b+=color.b; 
	  a+=color.a;
	   return *this;
  };

  /** \brief сложение только rgb. альфа не изменятеся.  */
  inline Color4f& addRGB(const Color4f& color)  
  {
	  r+=color.r; 
	  g+=color.g; 
	  b+=color.b;
	  return *this;
  };

  /** \brief Вычитание  */
  inline Color4f& sub(const Color4f& color)     
  {
	  r-=color.r; 
	  g-=color.g; 
	  b-=color.b; 
	  a-=color.a; 
	  return *this;
  };

  /** \brief Вычитание только rgb. альфа не изменятеся.   */
  inline Color4f& subRGB(const Color4f& color)  
  {
	  r-=color.r; 
	  g-=color.g; 
	  b-=color.b; 
	  return *this;
  };

  /** \brief Масштабирование   */
  inline Color4f& scale(float s)                
  {
	  r*=s; 
	  g*=s; 
	  b*=s; 
	  a*=s; 
	  return *this;
  };

  /** \brief Масштабирование только rgb. альфа не изменятеся.    */
  inline Color4f& scaleRGB(float s)             
  {
	  r*=s; 
	  g*=s; 
	  b*=s; 
	  return *this;
  };

  /** \brief  установить по  c1 и c2 по  линейной  интерполяции. */
  inline Color4f& setLerp(const Color4f& c1, const Color4f& c2, float k) 
  {
    r  = c1.r + k * (c2.r - c1.r);
    g  = c1.g + k * (c2.g - c1.g);
    b  = c1.b + k * (c2.b - c1.b);
    a  = c1.a + k * (c2.a - c1.a);
	return *this;
  };

  /** \brief  установить: линейная интерполяция между this и color. */
  inline Color4f& setLerp(const Color4f& color, float k) 
  {
    r = color.r + k * ( r - color.r);
    g = color.g + k * ( g - color.g);
    b = color.b + k * ( b - color.b);
    a = color.a + k * ( a - color.a);
	 return *this;
  };


   /** \brief изменить насыщенность . Альфа игнорируется. */
  inline Color4f& setAdjustSaturation(const Color4f& cSrc, float s)  
  {
       const float grey  = cSrc.r * 0.2125f  +  cSrc.g * 0.7154f  +  cSrc.b * 0.0721f;
    r  = grey + s * (cSrc.r - grey);
    g  = grey + s * (cSrc.g - grey);
    b  = grey + s * (cSrc.b - grey);
	return *this;
  };


   /** \brief изменить насыщенность */
  inline Color4f& adjustSaturation( float s )  
  {
     const float grey  =  r * 0.2125f +  g * 0.7154f +  b * 0.0721f;
    r  = grey + s * ( r - grey );
    g  = grey + s * ( g - grey );
    b  = grey + s * ( b - grey );
	 return *this;
  };

  /** \brief Масштабирование цвета. Изменение яркости. */
  inline Color4f& modulate(const Color4f& color) 
  {
    r *= color.r;
    g *= color.g; 
    b *= color.b; 
    a *= color.a; 
	return *this;
  };

  /** \brief Масштабирование цвета. Изменение яркости. */
  inline Color4f& modulate(const Color3f& color) 
  {
    r *= color.r;
    g *= color.g; 
    b *= color.b; 
	return *this;
  };


  /** \brief   Негатив. */
  inline Color4f& negative(bool bIncludeAlpha=true) 
  {
   r = 1.0f - r;
   g = 1.0f - g;
   b = 1.0f - b;
   if(bIncludeAlpha) a = 1.0f - a;
     return *this;
  }

  inline Color4f getNegatived() const 
  {
    Color4f res(*this);
	res.negative();
    return res;
  }

  /** \brief  Установить  негативный. */
  inline Color4f& setNegative(const Color4f& color) 
  {
    r = 1.0f - color.r;
    g = 1.0f - color.g;
    b = 1.0f - color.b;
    a = 1.0f - color.a; 
	 return *this;
  };
 

  /** \brief получить негативный цвет */
  inline Color4f getNegative() const 
  {
	  Color4f res(this); 
	  res.negative();
	  return res;  
  };

  /** \brief изменить контраст */
  inline Color4f& adjustContrast(float s) 
  {
    r = 0.5f + s * ( r - 0.5f);
    g = 0.5f + s * ( g - 0.5f);
    b = 0.5f + s * ( b - 0.5f);
	return *this;
  };


  /** \brief получить цвет с изменённым контрастом */
  inline Color4f getAdjustContrast(float s) const 
  {
     Color4f res(*this);
     res.adjustContrast(s);
     return res;
  };


  /** \brief Отсечение значений в пределах 0.0 ... 1.0  */
  inline Color4f saturate() {
    if(r>1.0f) r=1.0f;   if(r<0.0f) r=0.0f;
    if(g>1.0f) g=1.0f;   if(g<0.0f) g=0.0f; 
    if(b>1.0f) b=1.0f;   if(b<0.0f) b=0.0f;
    if(a>1.0f) a=1.0f;   if(a<0.0f) a=0.0f; 
	return *this;
  };

  /** \brief Получить сатурированый цвет из this . */
  inline Color4f getSaturated() const 
  { 
	  Color4f res(*this); 
	  res.saturate(); 
	  return res;  
  };

  /** \brief Установить как средний цвет между this и col  . */
  inline Color4f& setAverage(const Color4f& col) 
  {
    r = (r+col.r) / 2.0f;
    g = (g+col.g) / 2.0f;
    b = (b+col.b) / 2.0f;
    a = (a+col.a) / 2.0f;
	  return *this;
  };

  /** \brief Установить как средний цвет между  c1 и с2 . */
  inline Color4f& setAverage( const Color4f& c1 , const Color4f& c2 ) 
  {
    r = (c2.r+c1.r) / 2.0f;
    g = (c2.g+c1.g) / 2.0f;
    b = (c2.b+c1.b) / 2.0f;
    a = (c2.a+c1.a) / 2.0f;
	 return *this;
  };

  /** \brief Получить как средний цвет между this и col  . */
  inline Color4f getAveraged(const Color4f& col) const
  {
    Color4f res;
    res.setAverage(*this , col);
    return res;
  };

  inline  operator float*()                { return &r; };
  inline  operator const float*() const    { return &r; };

 // inline const float* getFloats() const    { return &r; };
 // inline int size()                        { return sizeof(float) * 4; };

  inline void operator = (const Color4f& color) 
  { 
    r=color.r; 
	g=color.g; 
	b=color.b; 
	a=color.a;  
  };
 
  inline void operator = (const color4f_s& color) 
  { 
    r=color.r; 
	g=color.g; 
	b=color.b; 
	a=color.a;  
  };
 
  inline bool operator == (const Color4f& c) const { return (r==c.r) && (g==c.g) && (b==c.b) && (a==c.a);  };
  inline bool operator != (const Color4f& c) const { return (r!=c.r) && (g!=c.g) && (b!=c.b) && (a!=c.a);  };
 
  inline Color4f& operator *= (const float s)    { r*=s; b*=s; g*=s; a*=s; return *this; };
  inline Color4f& operator *= (const Color4f& c) { r*=c.r; b*=c.b; g*=c.g; a*=c.a; return *this; };

  inline Color4f& operator /= (const float s)    { r/=s; b/=s; g/=s; a/=s; return *this; };
  inline Color4f& operator /= (const Color4f& c) { r/=c.r; b/=c.b; g/=c.g; a/=c.a; return *this; };

  inline Color4f& operator += (const float s)    { r+=s; b+=s; g+=s; a+=s; return *this; };
  inline Color4f& operator += (const Color4f& c) { r+=c.r; b+=c.b; g+=c.g; a+=c.a; return *this; };

  inline Color4f& operator -= (const float s)    { r-=s; b-=s; g-=s; a-=s; return *this; };
  inline Color4f& operator -= (const Color4f& c) { r-=c.r; b-=c.b; g-=c.g; a-=c.a; return *this; };

  inline Color4f  operator + (const Color4f& color) const  
  { 
     Color4f res;
     res.r=r+color.r; 
	 res.g=g+color.g; 
	 res.b=b+color.b; 
	 res.a=a+color.a;  
     return res;   
  };

  inline Color4f  operator + (const float f) const  
  { 
     Color4f res;
     res.r=r+f; 
	 res.g=g+f; 
	 res.b=b+f; 
	 res.a=a+f;  
     return res;   
  };


  inline Color4f   operator - (const Color4f& color) const  
  { 
     Color4f res;
     res.r=r-color.r; 
	 res.g=g-color.g; 
	 res.b=b-color.b; 
	 res.a=a-color.a;  
     return res;   
  };

  inline Color4f   operator - (const float f) const  
  { 
     Color4f res;
     res.r=r-f; 
	 res.g=g-f; 
	 res.b=b-f; 
	 res.a=a-f;  
     return res;   
  };


  Color4f   operator / (const Color4f& color) const  
  { 
     Color4f res;
     res.r = r / color.r; 
	 res.g = g / color.g; 
	 res.b = b / color.b; 
	 res.a = a / color.a;  
     return res;   
  };

  Color4f   operator / (const float f) const  
  { 
     Color4f res;
     res.r = r / f; 
	 res.g = g / f; 
	 res.b = b / f; 
	 res.a = a / f;  
     return res;   
  };


  Color4f   operator * (const Color4f& color) const  
  { 
     Color4f res;
     res.r = r*color.r; 
	 res.g = g*color.g; 
	 res.b = b*color.b; 
	 res.a = a*color.a;  
     return res;   
  };

  Color4f   operator * (const float f) const  
  { 
     Color4f res;
     res.r = r*f; 
	 res.g = g*f; 
	 res.b = b*f; 
	 res.a = a*f;  
     return res;   
  };





    #pragma warning(push)
      #pragma warning (disable : 4996)


    /** \brief Конвертация в строку.  Разделитель:  пробел */
    const char* tostr() const {
       static char ss[32];
       ss[0] = 0;
         sprintf(ss, "%f  %f  %f  %f", r, g, b, a );
            return ss;
    };

    /** \brief   Чтение значений из строки разд. пробелами  */
    bool fromstr(const char*  s) {
      const int SCRES = sscanf(s, "%f  %f  %f  %f", &r, &g, &b, &a );
       if( SCRES != 4  ) return false;
        return true;
    };


     #pragma warning(pop)



#ifdef _D3D9_H_
  inline void operator = (const D3DCOLORVALUE& val) { r=val.r; g=val.g; b=val.b; a=val.a; }
  inline operator const D3DCOLORVALUE*() const { return (D3DCOLORVALUE*)&r; }
  inline operator       D3DCOLORVALUE () const { D3DCOLORVALUE res;  res.a=a; res.r=r; res.g=g; res.b=b; return res; }
#endif   // GB_D3D9

#ifdef __D3DX9MATH_H__
  inline void operator = (const D3DXCOLOR& c) {r=c.r; g=c.g; b=c.b; a=c.a; }
  inline operator const D3DXCOLOR*() const { return (D3DXCOLOR*)&r; }
  inline operator       D3DXCOLOR () const { return D3DXCOLOR(r,g,b,a); }
#endif


}; 
// end class Color4f

//-------------------------------------------------------------------------


    //! \brief  Дочернее пространство от gb::color.  Цветовые константы.
    namespace color_const 
	{

//-------------------------------------------------------------------------
//                   COLOR CONST	 color4f_s
//-------------------------------------------------------------------------


static const color4f_s  COLOR4F_WHITE                 = { 1.0f,       1.0f,       1.0f,       1.0f };
static const color4f_s  COLOR4F_BLACK                 = { 0.0f,       0.0f,       0.0f,       1.0f };
static const color4f_s  COLOR4F_DIMGRAY               = { 0.329412f,  0.329412f,  0.329412f,  1.0f };
static const color4f_s  COLOR4F_GRAY                  = { 0.752941f,  0.752941f,  0.752941f,  1.0f };
static const color4f_s  COLOR4F_LIGHTGRAY             = { 0.658824f,  0.658824f,  0.658824f,  1.0f };
static const color4f_s  COLOR4F_AQUAMARINE            = { 0.439216f,  0.858824f,  0.576471f,  1.0f };
static const color4f_s  COLOR4F_BLUEVIOLET            = { 0.62352f,   0.372549f,  0.623529f,  1.0f };
static const color4f_s  COLOR4F_BROWN                 = { 0.647059f,  0.164706f,  0.164706f,  1.0f };
static const color4f_s  COLOR4F_CADETBLUE             = { 0.372549f,  0.623529f,  0.623529f,  1.0f };
static const color4f_s  COLOR4F_CORAL                 = { 1.0f,       0.498039f,  0.0f,       1.0f };
static const color4f_s  COLOR4F_CORNFLOWERBLUE        = { 0.258824f,  0.258824f,  0.435294f,  1.0f };
static const color4f_s  COLOR4F_DARKGREEN             = { 0.184314f,  0.309804f,  0.184314f,  1.0f };
static const color4f_s  COLOR4F_DARKOLIVEGREEN        = { 0.309804f,  0.309804f,  0.184314f,  1.0f };
static const color4f_s  COLOR4F_DARKORCHID            = { 0.6f,       0.196078f,  0.8f,       1.0f };
static const color4f_s  COLOR4F_DARKSLATEBLUE         = { 0.419608f,  0.137255f,  0.556863f,  1.0f };
static const color4f_s  COLOR4F_DARKSLATEGRAY         = { 0.184314f,  0.309804f,  0.309804f,  1.0f };
static const color4f_s  COLOR4F_DARKSLATEGREY         = { 0.184314f,  0.309804f,  0.309804f,  1.0f };
static const color4f_s  COLOR4F_DARKTURQUOISE         = { 0.439216f,  0.576471f,  0.858824f,  1.0f };
static const color4f_s  COLOR4F_FIREBRICK             = { 0.556863f,  0.137255f,  0.137255f,  1.0f };
static const color4f_s  COLOR4F_FORESTGREEN           = { 0.137255f,  0.556863f,  0.137255f,  1.0f };
static const color4f_s  COLOR4F_GOLD                  = { 0.8f,       0.498039f,  0.196078f,  1.0f };
static const color4f_s  COLOR4F_GOLDENROD             = { 0.858824f,  0.858824f,  0.439216f,  1.0f };
static const color4f_s  COLOR4F_GREENYELLOW           = { 0.576471f,  0.858824f,  0.439216f,  1.0f };
static const color4f_s  COLOR4F_INDIAN                = { 0.309804f,  0.184314f,  0.184314f,  1.0f };
static const color4f_s  COLOR4F_KHAKI                 = { 0.623529f,  0.623529f,  0.372549f,  1.0f };
static const color4f_s  COLOR4F_LIGHTBLUE             = { 0.74902f,   0.847059f,  0.847059f,  1.0f };
static const color4f_s  COLOR4F_LIGHTSTEELBLUE        = { 0.560784f,  0.560784f,  0.737255f,  1.0f };
static const color4f_s  COLOR4F_LIMEGREEN             = { 0.196078f,  0.8f,       0.196078f,  1.0f };
static const color4f_s  COLOR4F_MAROON                = { 0.556863f,  0.137255f,  0.419608f,  1.0f };
static const color4f_s  COLOR4F_MEDIUMAQUAMARINE      = { 0.196078f,  0.8f,       0.6f,       1.0f };
static const color4f_s  COLOR4F_MEDIUMBLUE            = { 0.196078f,  0.196078f,  0.8f,       1.0f };
static const color4f_s  COLOR4F_MEDIUMFORESTGREEN     = { 0.419608f,  0.556863f,  0.137255f,  1.0f };
static const color4f_s  COLOR4F_MEDIUMGOLDENROD       = { 0.917647f,  0.917647f,  0.678431f,  1.0f };
static const color4f_s  COLOR4F_MEDIUMORCHID          = { 0.576471f,  0.439216f,  0.858824f,  1.0f };
static const color4f_s  COLOR4F_MEDIUMSEAGREEN        = { 0.258824f,  0.435294f,  0.258824f,  1.0f };
static const color4f_s  COLOR4F_MEDIUMSLATEBLUE       = { 0.498039f,  0.0f,       1.0f,       1.0f };
static const color4f_s  COLOR4F_MEDIUMSPRINGGREEN     = { 0.498039f,  1.0f,       0.0f,       1.0f };
static const color4f_s  COLOR4F_MEDIUMTURQUOISE       = { 0.439216f,  0.858824f,  0.858824f,  1.0f };
static const color4f_s  COLOR4F_MEDIUMVIOLET          = { 0.858824f,  0.439216f,  0.576471f,  1.0f };
static const color4f_s  COLOR4F_MIDNIGHTBLUE          = { 0.184314f,  0.184314f,  0.309804f,  1.0f };
static const color4f_s  COLOR4F_NAVY                  = { 0.137255f,  0.137255f,  0.556863f,  1.0f };
static const color4f_s  COLOR4F_NAVYBLUE              = { 0.137255f,  0.137255f,  0.556863f,  1.0f };
static const color4f_s  COLOR4F_ORANGE                = { 1.0f,       0.5f,       0.0f,       1.0f };
static const color4f_s  COLOR4F_ORANGERED             = { 1.0f,       0.25f,      0.0f,       1.0f };
static const color4f_s  COLOR4F_ORCHID                = { 0.858824f,  0.439216f,  0.858824f,  1.0f };
static const color4f_s  COLOR4F_PALEGREEN             = { 0.560784f,  0.737255f,  0.560784f,  1.0f };
static const color4f_s  COLOR4F_PINK                  = { 0.737255f,  0.560784f,  0.560784f,  1.0f };
static const color4f_s  COLOR4F_PLUM                  = { 0.917647f,  0.678431f,  0.917647f,  1.0f };
static const color4f_s  COLOR4F_SALMON                = { 0.435294f,  0.258824f,  0.258824f,  1.0f };
static const color4f_s  COLOR4F_SEAGREEN              = { 0.137255f,  0.556863f,  0.419608f,  1.0f };
static const color4f_s  COLOR4F_SIENNA                = { 0.556863f,  0.419608f,  0.137255f,  1.0f };
static const color4f_s  COLOR4F_SKYBLUE               = { 0.196078f,  0.6f,       0.8f,       1.0f };
static const color4f_s  COLOR4F_SLATEBLUE             = { 0.0f,       0.498039f,  1.0f,       1.0f };
static const color4f_s  COLOR4F_SPRINGGREEN           = { 0.0f,       1.0f,       0.498039f,  1.0f };
static const color4f_s  COLOR4F_STEELBLUE             = { 0.137255f,  0.419608f,  0.556863f,  1.0f };
static const color4f_s  COLOR4F_TAN                   = { 0.858824f,  0.576471f,  0.439216f,  1.0f };
static const color4f_s  COLOR4F_THISTLE               = { 0.847059f,  0.74902f,   0.847059f,  1.0f };
static const color4f_s  COLOR4F_TURQUOISE             = { 0.678431f,  0.917647f,  0.917647f,  1.0f };
static const color4f_s  COLOR4F_VIOLET                = { 0.309804f,  0.184314f,  0.309804f,  1.0f };
static const color4f_s  COLOR4F_VIOLETRED             = { 0.8f,       0.196078f,  0.6f,       1.0f };
static const color4f_s  COLOR4F_WHEAT                 = { 0.847059f,  0.847059f,  0.74902f,   1.0f };
static const color4f_s  COLOR4F_YELLOWGREEN           = { 0.6f,       0.8f,       0.196078f,  1.0f };
static const color4f_s  COLOR4F_SUMMERSKY             = { 0.22f,      0.69f,      0.87f,      1.0f };
static const color4f_s  COLOR4F_RICHBLUE              = { 0.35f,      0.35f,      0.67f,      1.0f };
static const color4f_s  COLOR4F_BRASS                 = { 0.71f,      0.65f,      0.26f,      1.0f };
static const color4f_s  COLOR4F_COPPER                = { 0.72f,      0.45f,      0.20f,      1.0f };
static const color4f_s  COLOR4F_BRONZE                = { 0.55f,      0.47f,      0.14f,      1.0f };
static const color4f_s  COLOR4F_BRONZE2               = { 0.65f,      0.49f,      0.24f,      1.0f };
static const color4f_s  COLOR4F_SILVER                = { 0.90f,      0.91f,      0.98f,      1.0f };
static const color4f_s  COLOR4F_BRIGHTGOLD            = { 0.85f,      0.85f,      0.10f,      1.0f };
static const color4f_s  COLOR4F_OLDGOLD               = { 0.81f,      0.71f,      0.23f,      1.0f };
static const color4f_s  COLOR4F_FELDSPAR              = { 0.82f,      0.57f,      0.46f,      1.0f };
static const color4f_s  COLOR4F_QUARTZ                = { 0.85f,      0.85f,      0.95f,      1.0f };
static const color4f_s  COLOR4F_NEONPINK              = { 1.00f,      0.43f,      0.78f,      1.0f };
static const color4f_s  COLOR4F_DARKPURPLE            = { 0.53f,      0.12f,      0.47f,      1.0f };
static const color4f_s  COLOR4F_NEONBLUE              = { 0.30f,      0.30f,      1.00f,      1.0f };
static const color4f_s  COLOR4F_COOLCOPPER            = { 0.85f,      0.53f,      0.10f,      1.0f };
static const color4f_s  COLOR4F_MANDARINORANGE        = { 0.89f,      0.47f,      0.20f,      1.0f };
static const color4f_s  COLOR4F_LIGHTWOOD             = { 0.91f,      0.76f,      0.65f,      1.0f };
static const color4f_s  COLOR4F_MEDIUMWOOD            = { 0.65f,      0.50f,      0.39f,      1.0f };
static const color4f_s  COLOR4F_DARKWOOD              = { 0.52f,      0.37f,      0.26f,      1.0f };
static const color4f_s  COLOR4F_SPICYPINK             = { 1.00f,      0.11f,      0.68f,      1.0f };
static const color4f_s  COLOR4F_SEMISWEETCHOC         = { 0.42f,      0.26f,      0.15f,      1.0f };
static const color4f_s  COLOR4F_BAKERSCHOC            = { 0.36f,      0.20f,      0.09f,      1.0f };
static const color4f_s  COLOR4F_FLESH                 = { 0.96f,      0.80f,      0.69f,      1.0f };
static const color4f_s  COLOR4F_NEWTAN                = { 0.92f,      0.78f,      0.62f,      1.0f };
static const color4f_s  COLOR4F_NEWMIDNIGHTBLUE       = { 0.00f,      0.00f,      0.61f,      1.0f };
static const color4f_s  COLOR4F_VERYDARKBROWN         = { 0.35f,      0.16f,      0.14f,      1.0f };
static const color4f_s  COLOR4F_DARKBROWN             = { 0.36f,      0.25f,      0.20f,      1.0f };
static const color4f_s  COLOR4F_DARKTAN               = { 0.59f,      0.41f,      0.31f,      1.0f };
static const color4f_s  COLOR4F_GREENCOPPER           = { 0.32f,      0.49f,      0.46f,      1.0f };
static const color4f_s  COLOR4F_DKGREENCOPPER         = { 0.29f,      0.46f,      0.43f,      1.0f };
static const color4f_s  COLOR4F_DUSTYROSE             = { 0.52f,      0.39f,      0.39f,      1.0f };
static const color4f_s  COLOR4F_HUNTERSGREEN          = { 0.13f,      0.37f,      0.31f,      1.0f };
static const color4f_s  COLOR4F_SCARLET               = { 0.55f,      0.09f,      0.09f,      1.0f };
static const color4f_s  COLOR4F_MEDIUMPURPLE          = { 0.73f,      0.16f,      0.96f,      1.0f };
static const color4f_s  COLOR4F_LIGHTPURPLE           = { 0.87f,      0.58f,      0.98f,      1.0f };
static const color4f_s  COLOR4F_VERYLIGHTPURPLE       = { 0.94f,      0.81f,      0.99f,      1.0f };
static const color4f_s  COLOR4F_GREEN                 = { 0.0f,       0.5f,       0.0f,       1.0f };
static const color4f_s  COLOR4F_OLIVE                 = { 0.5f,       0.5f,       1.0f,       1.0f };
static const color4f_s  COLOR4F_PURPLE                = { 1.0f,       0.0f,       1.0f,       1.0f };
static const color4f_s  COLOR4F_TEAL                  = { 0.0f,       0.5f,       0.5f,       1.0f };
static const color4f_s  COLOR4F_RED                   = { 1.0f,       0.0f,       0.0f,       1.0f };
static const color4f_s  COLOR4F_LIME                  = { 0.0f,       1.0f,       0.0f,       1.0f };
static const color4f_s  COLOR4F_YELLOW                = { 1.0f,       1.0f,       0.0f,       1.0f };
static const color4f_s  COLOR4F_BLUE                  = { 0.0f,       0.0f,       1.0f,       1.0f };
static const color4f_s  COLOR4F_FUCHSIA               = { 1.0f,       0.0f,       1.0f,       1.0f };
static const color4f_s  COLOR4F_AQUA                  = { 0.0f,       1.0f,       1.0f,       1.0f };



//-------------------------------------------------------------------------
//                   COLOR CONST	 uicolor32_t
//-------------------------------------------------------------------------

static const uicolor32_t      CUICOLOR_ALICEBLUE        = 0xFFF0F8FF;
static const uicolor32_t      CUICOLOR_ANTIQUEWHITE     = 0xFFFAEBD7;
static const uicolor32_t      CUICOLOR_AQUA             = 0xFF00FFFF;
static const uicolor32_t      CUICOLOR_AQUAMARINE       = 0xFF7FFFD4;
static const uicolor32_t      CUICOLOR_AZURE            = 0xFFF0FFFF;
static const uicolor32_t      CUICOLOR_BEIGE            = 0xFFF5F5DC;
static const uicolor32_t      CUICOLOR_BISQUE           = 0xFFFFE4C4;
static const uicolor32_t      CUICOLOR_BLACK            = 0xFF000000;
static const uicolor32_t      CUICOLOR_BLANCHEDALMOND   = 0xFFFFEBCD;
static const uicolor32_t      CUICOLOR_BLUE             = 0xFF0000FF;
static const uicolor32_t      CUICOLOR_BLUEVIOLET       = 0xFF8A2BE2;
static const uicolor32_t      CUICOLOR_BROWN            = 0xFFA52A2A;
static const uicolor32_t      CUICOLOR_BURLYWOOD        = 0xFFDEB887;
static const uicolor32_t      CUICOLOR_CADETBLUE        = 0xFF5F9EA0;
static const uicolor32_t      CUICOLOR_CHARTREUSE       = 0xFF7FFF00;
static const uicolor32_t      CUICOLOR_CHOCOLATE        = 0xFFD2691E;
static const uicolor32_t      CUICOLOR_CORAL            = 0xFFFF7F50;
static const uicolor32_t      CUICOLOR_CORNFLOWERBLUE   = 0xFF6495ED;
static const uicolor32_t      CUICOLOR_CORNSILK         = 0xFFFFF8DC;
static const uicolor32_t      CUICOLOR_CRIMSON          = 0xFFDC143C;
static const uicolor32_t      CUICOLOR_CYAN             = 0xFF00FFFF;
static const uicolor32_t      CUICOLOR_DARKBLUE         = 0xFF00008B;
static const uicolor32_t      CUICOLOR_DARKCYAN         = 0xFF008B8B;
static const uicolor32_t      CUICOLOR_DARKGOLDENROD    = 0xFFB8860B;
static const uicolor32_t      CUICOLOR_DARKGRAY         = 0xFFA9A9A9;
static const uicolor32_t      CUICOLOR_DARKGREEN        = 0xFF006400;
static const uicolor32_t      CUICOLOR_DARKKHAKI        = 0xFFBDB76B;
static const uicolor32_t      CUICOLOR_DARKMAGENTA      = 0xFF8B008B;
static const uicolor32_t      CUICOLOR_DARKOLIVEGREEN   = 0xFF556B2F;
static const uicolor32_t      CUICOLOR_DARKORANGE       = 0xFFFF8C00;
static const uicolor32_t      CUICOLOR_DARKORCHID       = 0xFF9932CC;
static const uicolor32_t      CUICOLOR_DARKRED          = 0xFF8B0000;
static const uicolor32_t      CUICOLOR_DARKSALMON       = 0xFFE9967A;
static const uicolor32_t      CUICOLOR_DARKSEAGREEN     = 0xFF8FBC8B;
static const uicolor32_t      CUICOLOR_DARKSLATEBLUE    = 0xFF483D8B;
static const uicolor32_t      CUICOLOR_DARKSLATEGRAY    = 0xFF2F4F4F;
static const uicolor32_t      CUICOLOR_DARKTURQUOISE    = 0xFF00CED1;
static const uicolor32_t      CUICOLOR_DARKVIOLET       = 0xFF9400D3;
static const uicolor32_t      CUICOLOR_DEEPPINK         = 0xFFFF1493;
static const uicolor32_t      CUICOLOR_DEEPSKYBLUE      = 0xFF00BFFF;
static const uicolor32_t      CUICOLOR_DIMGRAY          = 0xFF696969;
static const uicolor32_t      CUICOLOR_DODGERBLUE       = 0xFF1E90FF;
static const uicolor32_t      CUICOLOR_FIREBRICK        = 0xFFB22222;
static const uicolor32_t      CUICOLOR_FLORALWHITE      = 0xFFFFFAF0;
static const uicolor32_t      CUICOLOR_FORESTGREEN      = 0xFF228B22;
static const uicolor32_t      CUICOLOR_FUCHSIA          = 0xFFFF00FF;
static const uicolor32_t      CUICOLOR_GAINSBORO        = 0xFFDCDCDC;
static const uicolor32_t      CUICOLOR_GHOSTWHITE       = 0xFFF8F8FF;
static const uicolor32_t      CUICOLOR_GOLD             = 0xFFFFD700;
static const uicolor32_t      CUICOLOR_GOLDENROD        = 0xFFDAA520;
static const uicolor32_t      CUICOLOR_GRAY             = 0xFF808080;
static const uicolor32_t      CUICOLOR_GREEN            = 0xFF008000;
static const uicolor32_t      CUICOLOR_GREENYELLOW      = 0xFFADFF2F;
static const uicolor32_t      CUICOLOR_GROW             = 0xFF808080;
static const uicolor32_t      CUICOLOR_HONEYDEW         = 0xFFF0FFF0;
static const uicolor32_t      CUICOLOR_HOTPINK          = 0xFFFF69B4;
static const uicolor32_t      CUICOLOR_INDIANRED        = 0xFFCD5C5C;
static const uicolor32_t      CUICOLOR_INDIGO           = 0xFF4B0082;
static const uicolor32_t      CUICOLOR_IVORY            = 0xFFFFFFF0;
static const uicolor32_t      CUICOLOR_KHAKI            = 0xFFF0E68C;
static const uicolor32_t      CUICOLOR_LAVENDER         = 0xFFE6E6FA;
static const uicolor32_t      CUICOLOR_LAVENDERBLUSH    = 0xFFFFF0F5;
static const uicolor32_t      CUICOLOR_LAWNGREEN        = 0xFF7CFC00;
static const uicolor32_t      CUICOLOR_LEMONCHIFFON     = 0xFFFFFACD;
static const uicolor32_t      CUICOLOR_LIGHTBLUE        = 0xFFADD8E6;
static const uicolor32_t      CUICOLOR_LIGHTCORAL       = 0xFFF08080;
static const uicolor32_t      CUICOLOR_LIGHTCYAN        = 0xFFE0FFFF;
static const uicolor32_t      CUICOLOR_LIGHTGOLDENRODYELLOW = 0xFFFAFAD2;
static const uicolor32_t      CUICOLOR_LIGHTGRAY        = 0xFFD3D3D3;
static const uicolor32_t      CUICOLOR_LIGHTGREEN       = 0xFF90EE90;
static const uicolor32_t      CUICOLOR_LIGHTPINK        = 0xFFFFB6C1;
static const uicolor32_t      CUICOLOR_LIGHTSALMON      = 0xFFFFA07A;
static const uicolor32_t      CUICOLOR_LIGHTSEAGREEN    = 0xFF20B2AA;
static const uicolor32_t      CUICOLOR_LIGHTSKYBLUE     = 0xFF87CEFA;
static const uicolor32_t      CUICOLOR_LIGHTSLATEGRAY   = 0xFF778899;
static const uicolor32_t      CUICOLOR_LIGHTSTEELBLUE   = 0xFFB0C4DE;
static const uicolor32_t      CUICOLOR_LIGHTYELLOW      = 0xFFFFFFE0;
static const uicolor32_t      CUICOLOR_LIME             = 0xFF00FF00;
static const uicolor32_t      CUICOLOR_LIMEGREEN        = 0xFF32CD32;
static const uicolor32_t      CUICOLOR_LINEN            = 0xFFFAF0E6;
static const uicolor32_t      CUICOLOR_MAGENTA          = 0xFFFF00FF;
static const uicolor32_t      CUICOLOR_MAROON           = 0xFF800000;
static const uicolor32_t      CUICOLOR_MEDIUMAQUAMARINE     = 0xFF66CDAA;
static const uicolor32_t      CUICOLOR_MEDIUMBLUE           = 0xFF0000CD;
static const uicolor32_t      CUICOLOR_MEDIUMORCHID         = 0xFFBA55D3;
static const uicolor32_t      CUICOLOR_MEDIUMPURPLE         = 0xFF9370DB;
static const uicolor32_t      CUICOLOR_MEDIUMSEAGREEN       = 0xFF3CB371;
static const uicolor32_t      CUICOLOR_MEDIUMSLATEBLUE      = 0xFF7B68EE;
static const uicolor32_t      CUICOLOR_MEDIUMSPRINGGREEN    = 0xFF00FA9A;
static const uicolor32_t      CUICOLOR_MEDIUMTURQUOISE      = 0xFF48D1CC;
static const uicolor32_t      CUICOLOR_MEDIUMVIOLETRED      = 0xFFC71585;
static const uicolor32_t      CUICOLOR_MIDNIGHTBLUE         = 0xFF191970;
static const uicolor32_t      CUICOLOR_MINTCREAM        = 0xFFF5FFFA;
static const uicolor32_t      CUICOLOR_MISTYROSE        = 0xFFFFE4E1;
static const uicolor32_t      CUICOLOR_MOCCASIN         = 0xFFFFE4B5;
static const uicolor32_t      CUICOLOR_NAVAJOWHITE      = 0xFFFFDEAD;
static const uicolor32_t      CUICOLOR_NAVY             = 0xFF000080;
static const uicolor32_t      CUICOLOR_OLDLACE          = 0xFFFDF5E6;
static const uicolor32_t      CUICOLOR_OLIVE            = 0xFF808000;
static const uicolor32_t      CUICOLOR_OLIVEDRAB        = 0xFF6B8E23;
static const uicolor32_t      CUICOLOR_ORANGE           = 0xFFFFA500;
static const uicolor32_t      CUICOLOR_ORANGERED        = 0xFFFF4500;
static const uicolor32_t      CUICOLOR_ORCHID           = 0xFFDA70D6;
static const uicolor32_t      CUICOLOR_PALEGOLDENR      = 0xFFEEE8AA;
static const uicolor32_t      CUICOLOR_PALEGREEN        = 0xFF98FB98;
static const uicolor32_t      CUICOLOR_PALETURQUOI      = 0xFFAFEEEE;
static const uicolor32_t      CUICOLOR_PALEVIOLETR      = 0xFFDB7093;
static const uicolor32_t      CUICOLOR_PAPAYAWHIP       = 0xFFFFEFD5;
static const uicolor32_t      CUICOLOR_PEACHPUFF        = 0xFFFFDAB9;
static const uicolor32_t      CUICOLOR_PERU             = 0xFFCD853F;
static const uicolor32_t      CUICOLOR_PINK             = 0xFFFFC0CB;
static const uicolor32_t      CUICOLOR_PLUM             = 0xFFDDA0DD;
static const uicolor32_t      CUICOLOR_POWDERBLUE       = 0xFFB0E0E6;
static const uicolor32_t      CUICOLOR_PURPLE           = 0xFF800080;
static const uicolor32_t      CUICOLOR_RED              = 0xFFFF0000;
static const uicolor32_t      CUICOLOR_ROSYBROWN        = 0xFFBC8F8F;
static const uicolor32_t      CUICOLOR_ROYALBLUE        = 0xFF4169E1;
static const uicolor32_t      CUICOLOR_SADDLEBROWN      = 0xFF8B4513;
static const uicolor32_t      CUICOLOR_SALMON           = 0xFFFA8072;
static const uicolor32_t      CUICOLOR_SANDYBROWN       = 0xFFF4A460;
static const uicolor32_t      CUICOLOR_SEAGREEN         = 0xFF2E8B57;
static const uicolor32_t      CUICOLOR_SEASHELL         = 0xFFFFF5EE;
static const uicolor32_t      CUICOLOR_SIENNA           = 0xFFA0522D;
static const uicolor32_t      CUICOLOR_SILVER           = 0xFFC0C0C0;
static const uicolor32_t      CUICOLOR_SKYBLUE          = 0xFF87CEEB;
static const uicolor32_t      CUICOLOR_SLATEBLUE        = 0xFF6A5ACD;
static const uicolor32_t      CUICOLOR_SLATEGRAY        = 0xFF708090;
static const uicolor32_t      CUICOLOR_SNOW             = 0xFFFFFAFA;
static const uicolor32_t      CUICOLOR_SPRINGGREEN      = 0xFF00FF7F;
static const uicolor32_t      CUICOLOR_STEELBLUE        = 0xFF4682B4;
static const uicolor32_t      CUICOLOR_TAN              = 0xFFD2B48C;
static const uicolor32_t      CUICOLOR_TEAL             = 0xFF008080;
static const uicolor32_t      CUICOLOR_THISTLE          = 0xFFD8BFD8;
static const uicolor32_t      CUICOLOR_TOMATO           = 0xFFFF6347;
static const uicolor32_t      CUICOLOR_TRANSPARENT      = 0x00FFFFFF;
static const uicolor32_t      CUICOLOR_TURQUOISE        = 0xFF40E0D0;
static const uicolor32_t      CUICOLOR_VIOLET           = 0xFFEE82EE;
static const uicolor32_t      CUICOLOR_WHEAT            = 0xFFF5DEB3;
static const uicolor32_t      CUICOLOR_WHITE            = 0xFFFFFFFF;
static const uicolor32_t      CUICOLOR_WHITESMOKE       = 0xFFF5F5F5;
static const uicolor32_t      CUICOLOR_YELLOW           = 0xFFFFFF00;
static const uicolor32_t      CUICOLOR_YELLOWGREEN      = 0xFF9ACD32;


       } 
	   // end namespace color_const

     }
     // end namespace color

}
// end namespace gb


// #endif // #ifdef GB_COLOR   // макрозащита

// end file