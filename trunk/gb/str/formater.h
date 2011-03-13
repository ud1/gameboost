/** \file  formater.h
*  \brief Класс форматирования базовых типов из/в строки/строку.
*
*
*   \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*
*  - Перенос в пространство имён str
*  - Удалены почти все зависимости от типов windows
*  - Поправлен код стиль.
*  - Поправлено под многопоточку. Удалено использование стат. буферов.

 \todo УДАЛИТЬ FORMATER  В ФУНКЦИИ  gb::str::
*
*/

#pragma once

#include <gb/base/Types.h>
#include <gb/Config.h>
#include <gb/str/KsDefines.h>

#include <cstring>
#include <string>
#include <cstdio>

#ifdef WIN32
#include <windows.h> 
#endif


namespace gb {

	namespace str {




	/** \brief Класс статических методов форматирования базовых типов из/в строки/строку. <br> 
		 Содержит так же несколько прочих функций . */
	class Formater {
	public:

	/** \brief Преобразование bool в строку в буфер pDest размером ndestlen */
	static bool boolToCstr( char* pDest, int32_t ndestlen, bool  value );
	static std::string boolToStr( bool  value );

	/** \brief Преобразование value в строку в верхнем регистре 
	       в буфер pDest размером ndestlen */
	static bool boolToUppercaseCstr( char* pDest, int32_t ndestlen, bool value );
	static std::string boolToUppercaseStr( bool value );

	/** \brief Преобразование float в строку в буфер pDest размером ndestlen */
	static bool floatToCstr(char* pDest, int32_t ndestlen, float value);
    static std::string  floatToStr(float value);

	static bool floatFromCstr( KS_OUT  float* out_val,  const char* s ) ;
	static bool floatFromCstr( KS_OUT  float& out_val,  const char* s ) ;

	/** \brief Преобразование  знакового целого в строку . Если bAsCppHex true,  тогда конвертирует в HEX в стиль c++  */
	static bool intToCstr(char* pDest, int32_t ndestlen,  int32_t value, bool bAsCppHex);
	/** \brief Преобразование  беззнакового целого в строку   Если bAsCppHex true,  тогда конвертирует в HEX в стиль c++  */
	static bool uintToCstr(char* pDest, int32_t ndestlen, uint32_t value, bool bAsCppHex);

	static std::string intToStr  ( int32_t value, bool bAsCppHex);
	static std::string uintToStr ( uint32_t value, bool bAsCppHex);


	/** \brief Преобразование  знакового целого из строки. 
	  
	        Если неверное значение или исключение, то вернёт false. Можно передавать число d HEX-c++. Например 0x5faf43   */
	static bool intFromCstr(KS_OUT int32_t* out_val, const char* s) ;
	/** \brief Преобразование  знакового целого из строки. Если неверное значение или исключение, то вернёт false.  
	    Можно передавать число d HEX-c++. Например 0x5faf43  */
	static bool intFromCstr(KS_OUT int32_t& out_val, const char* s) ;

	/** \brief  Аналог intFromCstr  для  unsigned int    */
	static bool uintFromCstr(KS_OUT uint32_t* out_val, const char* s) ;
	static bool uintFromCstr(KS_OUT uint32_t& out_val, const char* s) ;
 

	/** \brief Преобразование  целого в строку  в шестнадцатеричном виде   */
	static bool intToHex(char* pDest, int32_t ndestlen, int32_t value) ;
	/** \brief Преобразование  целого в строку  в шестнадцатеричном виде с префиксом "0x" */
	static bool intToCppHex(char* pDest, int32_t ndestlen, int32_t value) ; 

	/** \brief  Перевод указателя в виде hex-строки  в буфер buff  с символами в верхнем регистре.  <BR>
	    Буфер должен быть длиной не менее 11 . Пример результата = 0xA23A98FC  */
	static bool pointerToCstr(char* pDest, int32_t ndestlen, const void* p) ;
	
	/** \brief Получение побитовой строки из байта . */
	static bool  byteToCStrAsBin(char* pDest, int32_t ndestlen, uint8_t value);

	/** \brief Преобразование uint32_t в двоичное представление. */
	static bool uintToBinCstr(char* pDest, int32_t ndestlen, uint32_t value);
	/** \brief Преобразование  int32_t в двоичное представление. */
    static bool intToBinCstr(char* pDest, int32_t ndestlen, uint32_t value);
    /** \brief Преобразование uint32_t в двоичное представление. */
	static std::string uintToBinStr( uint32_t value);
    /** \brief Преобразование int32_t в двоичное представление. */
    static std::string intToBinStr( uint32_t value);


	/** \brief Преобразование в uint из строки содержащей цифру в двоичном виде. */
	static uint32_t uintFromBinCstr(const char* _s, int32_t nlen= -1)  throw();

	/** \brief побитовая печать на консоль двойного слова uint32_t */
	static void printUint32AsBin(  uint32_t value) ;
 
	/** \brief печать  байта  в двоичном представлении на консоль . */
	static void printByteAsBin(uint8_t value) ;
	

#if defined (_WIN32)

	/** \brief  Хэндл окна в строку */
	static uint32_t hwndAsUint(const HWND hwnd) ;

#endif

 
 
    };
    // end class
	
	
	}
	// end namespace str

}
// end namespace gb

// end file