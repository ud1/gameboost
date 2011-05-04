/** \file dataconv.h
 \brief Конвертация из строки/в строку типов D3D9 
*
*
*
*
  \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586

  \TODO  Добавить функции для D3DTEXTURESTAGESTATETYPE, фильтрации


*/

#if ( defined(GB_D3D9) && defined(WIN32) )

#pragma once
#define __GB_D3D9_DATACONV_H__

#include <gb/graphics/d3d9/common.h>

#include <string.h>
#include <string>


namespace gb 
{
   namespace graphics 
   {
      namespace d3d9 
	  {
	     //! \brief Конвертация из строки/в строку типов D3D9  
	     namespace dataconv
		 {

//-------------------------------------------------------------------------		 
		 
/** \brief Получение строки по указаному формату. 
    Если format некорректный, то вернёт пустую строку  */
GB_D3D9_API std::string  D3DFORMAT_tostr( const D3DFORMAT format);

/** \brief   формат fOut из  строки str. Вернёт false если строка некорректна */ 
GB_D3D9_API bool  D3DFORMAT_fromstr(D3DFORMAT& fOut,  const std::string& str);		 

	
/** \brief Значение D3DRESOURCETYPE  в строку.
      Если val некорректное, то вернёт пустую строку  */
GB_D3D9_API std::string D3DRESOURCETYPE_tostr(const D3DRESOURCETYPE val);

/** \brief Тип D3DRESOURCETYPE из  строки str. Вернёт false если строка некорректна */ 
GB_D3D9_API bool D3DRESOURCETYPE_fromstr( D3DRESOURCETYPE&  rOut, const std::string& str);


/** \brief Значение D3DRENDERSTATETYPE в строку. 
       Если val некорректное, то вернёт пустую строку  */
GB_D3D9_API std::string D3DRENDERSTATETYPE_tostr(const D3DRENDERSTATETYPE val);

/** \brief Тип D3DRENDERSTATETYPE из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API bool D3DRENDERSTATETYPE_fromstr(  D3DRENDERSTATETYPE& val, std::string& str);


/** \brief Значение D3DPOOL (val) в строку.
        Если val некорректное, то вернёт пустую строку   */
GB_D3D9_API std::string D3DPOOL_tostr(const D3DPOOL val);

/** \brief Тип D3DRENDERSTATETYPE из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API bool D3DPOOL_fromstr( D3DPOOL& val, const  std::string& str);

/** \brief Значение D3DFILLMODE (val) в строку.
        Если val некорректное, то вернёт пустую строку   */
GB_D3D9_API std::string D3DFILLMODE_tostr(const D3DFILLMODE val); 

/** \brief Тип D3DFILLMODE из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API bool  D3DFILLMODE_fromstr( D3DFILLMODE& valOut, const std::string& str);
		 

/** \brief Значение D3DSHADEMODE (val) в строку.
        Если val некорректное, то вернёт пустую строку   */
GB_D3D9_API  std::string  D3DSHADEMODE_tostr(const D3DSHADEMODE val); 

/** \brief Тип D3DFILLMODE из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API bool  D3DSHADEMODE_fromstr( D3DSHADEMODE& valOut, const  std::string& str); 


/** \brief Значение D3DBLEND (val) в строку.
        Если val некорректное, то вернёт пустую строку   */
GB_D3D9_API  std::string D3DBLEND_tostr(const D3DBLEND   val) ;

/** \brief Тип D3DBLEND из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API bool D3DBLEND_fromstr(D3DBLEND& valOut,  const std::string& str);


/** \brief Значение D3DCULL (val) в строку.
        Если val некорректное, то вернёт пустую строку   */
GB_D3D9_API  std::string D3DCULL_tostr(const D3DCULL val);

/** \brief Тип D3DCULL из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API  bool  D3DCULL_fromstr(D3DCULL& valOut, const std::string& str);



/** \brief Значение D3DCMPFUNC (val) в строку.
        Если val некорректное, то вернёт пустую строку   */
GB_D3D9_API std::string  D3DCMPFUNC_tostr( const D3DCMPFUNC val );

/** \brief Тип D3DCULL из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API bool  D3DCMPFUNC_fromstr ( D3DCMPFUNC& valOut, const std::string& str );



/** \brief Значение D3DFOGMODE (val) в строку.
        Если val некорректное, то вернёт пустую строку   */
GB_D3D9_API std::string  D3DFOGMODE_tostr(const D3DFOGMODE val);


/** \brief Тип D3DFOGMODE из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API bool D3DFOGMODE_fromstr(  D3DFOGMODE& valOut, const std::string& str);


/** \brief Значение D3DSTENCILOP (val) в строку.
        Если val некорректное, то вернёт пустую строку   */
GB_D3D9_API  std::string  D3DSTENCILOP_tostr(const D3DSTENCILOP val); 

/** \brief Тип D3DFOGMODE из  строки str. Вернёт false если строка некорректна  */
GB_D3D9_API bool D3DSTENCILOP_fromstr( D3DSTENCILOP& valOut, const std::string& str);










		 
//-------------------------------------------------------------------------		 

	     } // end ns dataconv

      } // end ns d3d9

   } // end ns graphics

} // end ns gb

#endif
// end file