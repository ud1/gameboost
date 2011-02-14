/** \file  formater.h
*  \brief Класс форматирования базовых типов из/в строки/строку.
*
*
*   \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*
*  - Перенос в пространство имён str
*  - Удалены почти все зависимости от типов windows
*  - Поправлен код стиль.
*
*
*/

#pragma once

#include <gb/base/Types.h>
#include <gb/Config.h>
#include <gb/str/KsDefines.h>


namespace gb {

	namespace str {




	/** \brief Класс статических методов форматирования базовых типов из/в строки/строку. <br> 
		 Содержит так же несколько прочих функций . */
	class Formater {
	public:

	/** \brief Преобразование bool в строку */
	static const char* boolToCstr(bool b) ;

	/** \brief Преобразование BOOL в строку */
	static const char* boolToUppercaseCstr(bool b) ;

	/** \brief Преобразование float в строку */
	static const char* floatToCstr(float f) ;

	static bool floatFromCstr( KS_OUT float* val, const char* s ) ;
	static bool floatFromCstr(KS_OUT float& val, const char* s) ;

	/** \brief Преобразование  знакового целого в строку  */
	static const char* intToCstr(int32_t i) ;

	/** \brief Преобразование  знакового целого из строки. Если неверное значение вернёт false  */
	static bool intFromCstr(KS_OUT int32_t* val, const char* s) ;

	static bool intFromCstr(KS_OUT int32_t& val, const char* s) ;

	/** \brief Преобразование  беззнакового целого в строку  */
	static const char* uintToCstr(uint32_t val) ;

	static bool uintFromCstring(KS_OUT uint32_t& val, const char* s);

	/** \brief Преобразование  целого в строку  в шестнадцатеричном виде   */
	static const char* intToHex(int32_t i) ;
	/** \brief Преобразование  целого в строку  в шестнадцатеричном виде с префиксом "0x" */
	static const char* intToCppHex(int32_t i) ; 

	/** \brief  Перевод указателя в виде hex-строки  в буфер buff  с символами в верхнем регистре.  <BR>
	    Буфер должен быть длиной не менее 11 . Пример результата = 0xA23A98FC  */
	static const char* pointerToCstr(const void* p) ;
	
	/** \brief Получение побитовой строки из байта . */
	static const char* byteToCStrAsBin(uint8_t u) ;

	/** \brief Преобразование uint32_t в двоичное представление. */
	static const char* uintToBinCstr(uint32_t dwArg) ;

    /** \brief Преобразование uint32_t в cстроковое  представление. Если bAsHex==true то в шестнадцатеричном виде. */
	static const char* uintToCstr(const uint32_t dw, bool bAsHex=false) ;

	/** \brief можно передать например  0xAF33. то есть первые символы 0x считается как в hex . */
	static bool uintFromCstr(KS_OUT uint32_t* pdwOut, const char* s) ;
	static bool uintFromCstr(KS_OUT uint32_t& dw,     const char* s) ;

	/** \brief Преобразование в uint из строки содержащей цифру в двоичном виде. */
	static uint32_t uintFromBinCstr(const char* _s, int32_t nlen= -1) throw(); 

	/** \brief побитовая печать на консоль двойного слова uint32_t */
	static void print_bits(  uint32_t value) ;

	/** \brief Печать uint32_t значения в двоичном виде на консоль */
	static void printDwordAsBin(const uint32_t dw) ;
	/** \brief печать  байта  в двоичном представлении на консоль . */
	static void printByteAsBin(uint8_t u) ;
	


#ifdef _WIN32
	/** \brief Хэндл окна в строку */
	static uint32_t hwndAsUint(const HWND hwnd) ;
#endif

 
 

    };
    // end class
	
	
	
	}
	// end namespace str

}
// end namespace gb






// end file