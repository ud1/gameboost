/*! \file String.h
  \brief Строковые функции, алгоритмы , типы. <br>
 	Мягкая обёртка вокруг boost/algorithm/string.hpp с возможностью реализации собственных
  	алгоритмов без подключения библиотеки Boost

	<br>
	<br>

 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 *	   && ksacvet777
 */


#pragma once
#define __GB_STR_H__

#include <gb/Config.h>
#include <gb/base/Types.h>

#if GB_ALLOW_BOOST_LIBRARY
#include <boost/algorithm/string.hpp>
#endif


#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <string>
#include <cctype>
#include <vector>
#include <list>
#include <set>

#include <cstring>
#include <string>
#include <cstdio>

#include <gb/Config.h>
#include <gb/base/Types.h>

/************* 
#ifdef WIN32
#include <windows.h> 
#endif
#*************/

#if GB_ALLOW_BOOST_LIBRARY
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#endif

#ifndef _LIB_GB_STR
	#ifdef _DEBUG
		#pragma comment(lib , "gb_str_d.lib")
	#else
		#pragma comment(lib , "gb_str.lib")
	#endif
#endif



#pragma warning(push)
#pragma warning( disable : 4290 )

namespace gb
{

    //! \brief Операции со строками , символами.
	namespace str {
		
//-------------------------------------------------------------------------

		
std::string toUtf8( const std::wstring & wide_str );
std::wstring toWide( const std::string & utf8_str );

//! \brief Раскодирует один Unicode символ из потока байтов UTF8
//! \returns возвращает его длину в результате функции и код в out_result
uint32_t decodeUtf8Character( uint32_t & out_result, const char * utf8 );

uint32_t uint32FromHex (const std::string & s);
uint64_t uint64FromHex (const std::string & s);



// Boost запрещён, стоянка велосипедов открывается здесь
#if ! GB_ALLOW_BOOST_LIBRARY

//! \brief  Привести к верхнему регистру на месте
void toUpper( std::string & v );

//! \brief  Вернуть копию, приведённую к верхнему регистру
std::string toUpperCopy( const std::string & v );

//! \brief  Привести к нижнему регистру на месте
void toLower( std::string & v );

//! \brief  Вернуть копию, приведённую к нижнему регистру
std::string toLowerCopy( const std::string & v );

//! \brief  Обрезать пробелы и табуляции слева, на месте
void trimLeft( std::string & v );

//! \brief  Обрезать пробелы и табуляции слева, вернуть исправленную копию
std::string trimLeftCopy( const std::string & v );

//! \brief  Обрезать пробелы и табуляции справа, на месте
void trimRight( std::string & v );

//! \brief  Обрезать пробелы и табуляции справа, вернуть исправленную копию
std::string trimRightCopy( const std::string & v );

//! \brief  Обрезать пробелы и табуляции слева и справа, на месте
void trim( std::string & v );

//! \brief  Обрезать пробелы и табуляции слева и справа, вернуть исправленную копию
std::string trimCopy( const std::string & v );

//-------------------------------------------------------------------------
// Предикаты для использования в функциях поиска, или в обычных условиях
//-------------------------------------------------------------------------

//! \brief  Начинается ли строка text с фрагмента search?
bool startsWith( const std::string & text, const std::string & search );

//! \brief  Начинается ли строка text с фрагмента search? (без учёта регистра)
bool iStartsWith( const std::string & text, const std::string & search );

//! \brief  Завершается ли строка text фрагментом search?
bool endsWith( const std::string & text, const std::string & search );

//! \brief  Завершается ли строка text фрагментом search? (без учёта регистра)
bool iEndsWith( const std::string & text, const std::string & search );

//! Содержит ли строка text фрагмент search?
bool contains( const std::string & text, const std::string & search );
//! \brief  Содержит ли строка text фрагмент search? (без учёта регистра)
bool iContains( const std::string & text, const std::string & search );

//! \brief  Равны ли строки друг другу
//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
inline bool equals( const std::string & a, const std::string & b ) {
	return a == b;
}
//! \brief  Равны ли строки друг другу без учёта регистра?
//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
bool iEquals( const std::string & a, const std::string & b );

//
//
//

/** \brief  Разбить строку value на слова по символам указанным в split_charset, результат
 сложить в destination  */
void split( std::vector <std::string> & destination, const std::string & value, const std::string & split_charset );
void split( std::list <std::string> & destination, const std::string & value, const std::string & split_charset );
void split( std::set <std::string> & destination, const std::string & value, const std::string & split_charset );

//! \brief  Заменить первое вхождение search в строку input новым текстом replace
void replaceFirst( std::string & input, const std::string & search, const std::string & replace );

//! \brief  Заменить первое вхождение search в строку input новым текстом replace, вернуть исправленную копию
std::string replaceFirstCopy( const std::string & input, const std::string & search, const std::string & replace );

//!  \brief Заменить первое вхождение search в строку input новым текстом replace, без учёта регистра
void iReplaceFirst( std::string & input, const std::string & search, const std::string & replace );

//!  \brief Заменить первое вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
std::string iReplaceFirstCopy( const std::string & input, const std::string & search, const std::string & replace );
		
//!  \brief Удалить первое вхождение search в строку input
void eraseFirst( std::string & input, const std::string & search );

//!  \brief Удалить первое вхождение search в строку input, вернуть исправленную копию
std::string eraseFirstCopy( const std::string & input, const std::string & search );

//!  \brief Удалить первое вхождение search в строку input, без учёта регистра
void iEraseFirst( std::string & input, const std::string & search );

//!  \brief Удалить первое вхождение search в строку input, без учёта регистра, вернуть исправленную копию
std::string iEraseFirstCopy( const std::string & input, const std::string & search );

//!  \brief Заменить последнее вхождение search в строку input новым текстом replace
void replaceLast( std::string & input, const std::string & search, const std::string & replace );

//!  \brief Заменить последнее вхождение search в строку input новым текстом replace, вернуть исправленную копию
std::string replaceLastCopy( const std::string & input, const std::string & search, const std::string & replace );

//!  \brief Заменить последнее вхождение search в строку input новым текстом replace, без учёта регистра
void iReplaceLast( std::string & input, const std::string & search, const std::string & replace );

//!  \brief Заменить последнее вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
std::string iReplaceLastCopy( const std::string & input, const std::string & search, const std::string & replace );

//!  \brief Удалить последнее вхождение search в строку input
void eraseLast( std::string & input, const std::string & search );

//!  \brief Удалить последнее вхождение search в строку input, вернуть исправленную копию
std::string eraseLastCopy( const std::string & input, const std::string & search );

//!  \brief Удалить последнее вхождение search в строку input, без учёта регистра
void iEraseLast( std::string & input, const std::string & search );

//!  \brief Удалить последнее вхождение search в строку input, без учёта регистра, вернуть исправленную копию
std::string iEraseLastCopy( const std::string & input, const std::string & search );

/**  \brief Заменить N-е вхождение search в строку input новым текстом replace
    Отсчёт с нуля. Отрицательные N считаются с конца строки   */
void replaceNth( std::string & input, const std::string & search, int32_t n, const std::string & replace );

//!  \brief  Заменить N-e вхождение search в строку input новым текстом replace, вернуть исправленную копию
   Отсчёт с нуля. Отрицательные N считаются с конца строки	*/
std::string replaceNthCopy( const std::string & input, const std::string & search, int32_t n, const std::string & replace );

   /**  \brief  Заменить N-e вхождение search в строку input новым текстом replace, без учёта регистра
     Отсчёт с нуля. Отрицательные N считаются с конца строки  */
void iReplaceNth( std::string & input, const std::string & search, int32_t n, const std::string & replace );
/**  \brief  Заменить N-e вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
    Отсчёт с нуля. Отрицательные N считаются с конца строки  */
std::string iReplaceNthCopy( const std::string & input, const std::string & search, int32_t n, const std::string & replace );

/**  \brief  Удалить N-e вхождение search в строку input
     Отсчёт с нуля. Отрицательные N считаются с конца строки */
void eraseNth( std::string & input, const std::string & search, int32_t n );

/**  \brief  Удалить N-e вхождение search в строку input, вернуть исправленную копию
       Отсчёт с нуля. Отрицательные N считаются с конца строки */
std::string eraseNthCopy( const  std::string & input, const std::string & search, int32_t n );

/**  \brief  Удалить N-e вхождение search в строку input, без учёта регистра
     Отсчёт с нуля. Отрицательные N считаются с конца строки  */
void iEraseNth( std::string & input, const std::string & search, int32_t n );

/**  \brief  Удалить N-e вхождение search в строку input, без учёта регистра, вернуть исправленную копию
    Отсчёт с нуля. Отрицательные N считаются с конца строки  */
std::string iEraseNthCopy( const std::string & input, const std::string & search, int32_t n );

//!  \brief  Заменить каждое вхождение search в строку input новым текстом replace
void replaceAll( std::string & input, const std::string & search, const std::string & replace );

//!  \brief Заменить каждое вхождение search в строку input новым текстом replace, вернуть исправленную копию
std::string replaceAllCopy( const std::string & input, const std::string & search, const std::string & replace );

//!  \brief Заменить каждое вхождение search в строку input новым текстом replace, без учёта регистра
void iReplaceAll( std::string & input, const std::string & search, const std::string & replace );

//!  \brief Заменить каждое вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
std::string iReplaceAllCopy( const std::string & input, const std::string & search, const std::string & replace );

//!  \brief Удалить каждое вхождение search в строку input
void eraseAll( std::string & input, const std::string & search );

//!  \brief Удалить каждое вхождение search в строку input, вернуть исправленную копию
std::string eraseAllCopy( const std::string & input, const std::string & search );

//!  \brief Удалить каждое вхождение search в строку input, без учёта регистра
void iEraseAll( std::string & input, const std::string & search );

//!  \brief Удалить каждое вхождение search в строку input, без учёта регистра, вернуть исправленную копию
std::string iEraseAllCopy( const std::string & input, const std::string & search );

/**  \brief Заменить первые N символов строки input новым текстом replace
    Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
void replaceHead( std::string & input, int32_t n, const std::string & replace );

/**  \brief  Заменить первые N символов строки input новым текстом replace, вернуть исправленную копию
 Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
std::string replaceHeadCopy( const std::string & input, int32_t n, const std::string & replace );

/**  \brief  Заменить последние N символов строки input новым текстом replace
   Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
void replaceTail( std::string & input, int32_t n, const std::string & replace );

/**  \brief  Заменить последние N символов строки input новым текстом replace, вернуть исправленную копию
 Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
std::string replaceTailCopy( const std::string & input, int32_t n, const std::string & replace );
		
/**  \brief  Удалить первые N символов строки
  Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))*/
void eraseHead( std::string & input, int32_t n );

/** \brief  Удалить первые N символов строки, вернуть исправленную копию
  Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))*/
std::string eraseHeadCopy( const std::string & input, int32_t n );

/**  \brief  Удалить последние N символов строки
 Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
void eraseTail( std::string & input, int32_t n );

/**  \brief  Удалить последние N символов строки, вернуть исправленную копию
  Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))*/
std::string eraseTailCopy( const std::string & input, int32_t n );



#else   // окончание без буста. Далее с бустом.


//!  \brief  Привести к верхнему регистру на месте
inline void toUpper( std::string & v )
{
	boost::algorithm::to_upper( v );
}


//!  \brief Вернуть копию, приведённую к верхнему регистру
inline std::string toUpperCopy( const std::string & v )
{
	return boost::algorithm::to_upper_copy( v );
}

//!  \brief Привести к нижнему регистру на месте
inline void toLower( std::string & v )
{
	boost::algorithm::to_lower( v );
}



//!  \brief Вернуть копию, приведённую к нижнему регистру
inline std::string toLowerCopy( const std::string & v )
{
	return boost::algorithm::to_lower_copy( v );
}

//!  \brief Обрезать пробелы и табуляции слева, на месте
inline void trimLeft( std::string & v )
{
	boost::algorithm::trim_left( v );
}

//!  \brief Обрезать пробелы и табуляции слева, вернуть исправленную копию
inline std::string trimLeftCopy( const std::string & v )
{
	return boost::algorithm::trim_left_copy( v );
}

//!  \brief Обрезать пробелы и табуляции справа, на месте
inline void trimRight( std::string & v )
{
	boost::algorithm::trim_right( v );
}

//!  \brief Обрезать пробелы и табуляции справа, вернуть исправленную копию
inline std::string trimRightCopy( const std::string & v )
{
	return boost::algorithm::trim_right_copy( v );
}

//!  \brief Обрезать пробелы и табуляции слева и справа, на месте
inline void trim( std::string & v )
{
	boost::algorithm::trim( v );
}

//!  \brief Обрезать пробелы и табуляции слева и справа, вернуть исправленную копию
inline std::string trimCopy( const std::string & v )
{
	return boost::algorithm::trim_copy( v );
}



//-------------------------------------------------------------------------
// Предикаты для использования в функциях поиска, или в обычных условиях
//-------------------------------------------------------------------------

//!  \brief Начинается ли строка text с фрагмента search?
inline bool startsWith( const std::string & text, const std::string & search )
{
	return boost::algorithm::starts_with( text, search );
}
//!  \brief Начинается ли строка text с фрагмента search? (без учёта регистра)
inline bool iStartsWith( const std::string & text, const std::string & search )
{
	return boost::algorithm::istarts_with( text, search );
}

//!  \brief Завершается ли строка text фрагментом search?
inline bool endsWith( const std::string & text, const std::string & search )
{
	return boost::algorithm::ends_with( text, search );
}
//!  \brief Завершается ли строка text фрагментом search? (без учёта регистра)
inline bool iEndsWith( const std::string & text, const std::string & search )
{
	return boost::algorithm::iends_with( text, search );
}

//!  \brief Содержит ли строка text фрагмент search?
inline bool contains( const std::string & text, const std::string & search )
{
	return boost::algorithm::contains( text, search );
}
//!  \brief Содержит ли строка text фрагмент search? (без учёта регистра)
inline bool iContains( const std::string & text, const std::string & search )
{
	return boost::algorithm::icontains( text, search );
}

/**  \brief Равны ли строки друг другу
 (не имеет смысла в простом условии, но полезно, как предикат для поиска) */
inline bool equals( const std::string & a, const std::string & b )
{
	return a == b;
}
/** Равны ли строки друг другу без учёта регистра?
   (не имеет смысла в простом условии, но полезно, как предикат для поиска) */
inline bool iEquals( const std::string & a, const std::string & b )
{
	return boost::algorithm::iequals( a, b );
}


//
//
//

/**  \brief  Разбить строку value на слова по символам указанным в split_charset, 
результат  сложить в destination  */
inline void split( std::vector <std::string> & destination, const std::string & value, const std::string & split_charset )
{
	boost::algorithm::split( destination, value, boost::algorithm::is_any_of( split_charset ) );
}

inline void split( std::list <std::string> & destination, const std::string & value, const std::string & split_charset )
{
	boost::algorithm::split( destination, value, boost::algorithm::is_any_of( split_charset ) );
}

inline void split( std::set <std::string> & destination, const std::string & value, const std::string & split_charset )
{
	boost::algorithm::split( destination, value, boost::algorithm::is_any_of( split_charset ) );
}

		
		
//!  \brief Заменить первое вхождение search в строку input новым текстом replace
inline void replaceFirst( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::replace_first( input, search, replace );
}

//!  \brief Заменить первое вхождение search в строку input новым текстом replace, вернуть исправленную копию
inline std::string replaceFirstCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::replace_first_copy( input, search, replace );
}

//!  \brief Заменить первое вхождение search в строку input новым текстом replace, без учёта регистра
inline void iReplaceFirst( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::ireplace_first( input, search, replace );
}

//!  \brief Заменить первое вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
inline std::string iReplaceFirstCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::ireplace_first_copy( input, search, replace );
}
		
//!  \brief Удалить первое вхождение search в строку input
inline void eraseFirst( std::string & input, const std::string & search )
{
	boost::algorithm::erase_first( input, search );
}

//!  \brief Удалить первое вхождение search в строку input, вернуть исправленную копию
inline std::string eraseFirstCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::erase_first_copy( input, search );
}

//! Удалить первое вхождение search в строку input, без учёта регистра
inline void iEraseFirst( std::string & input, const std::string & search )
{
	boost::algorithm::ierase_first( input, search );
}

/**  \brief Удалить первое вхождение search в строку input, без учёта регистра, 
  вернуть исправленную копию  */
inline std::string iEraseFirstCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::ierase_first_copy( input, search );
}

//!  \brief Заменить последнее вхождение search в строку input новым текстом replace
inline void replaceLast( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::replace_last( input, search, replace );
}

//!  \brief Заменить последнее вхождение search в строку input новым текстом replace, вернуть исправленную копию
inline std::string replaceLastCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::replace_last_copy( input, search, replace );
}

//!  \brief Заменить последнее вхождение search в строку input новым текстом replace, без учёта регистра
inline void iReplaceLast( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::ireplace_last( input, search, replace );
}

//!  \brief Заменить последнее вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
inline std::string iReplaceLastCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::ireplace_last_copy( input, search, replace );
}

//!  \brief Удалить последнее вхождение search в строку input
inline void eraseLast( std::string & input, const std::string & search )
{
	boost::algorithm::erase_last( input, search );
}

//!  \brief Удалить последнее вхождение search в строку input, вернуть исправленную копию
inline std::string eraseLastCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::erase_last_copy( input, search );
}

//!  \brief Удалить последнее вхождение search в строку input, без учёта регистра
inline void iEraseLast( std::string & input, const std::string & search )
{
	boost::algorithm::ierase_last( input, search );
}

//!  \brief Удалить последнее вхождение search в строку input, без учёта регистра, вернуть исправленную копию
inline std::string iEraseLastCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::ierase_last_copy( input, search );
}


/**  \brief Заменить N-е вхождение search в строку input новым текстом replace
   Отсчёт с нуля. Отрицательные N считаются с конца строки */
inline void replaceNth( std::string & input, const std::string & search, int32_t n, const std::string & replace )
{
	boost::algorithm::replace_nth( input, search, n, replace );
}

/**  \brief  Заменить N-e вхождение search в строку input новым текстом replace, 
      вернуть исправленную копию Отсчёт с нуля. 
      Отрицательные N считаются с конца строки  */
inline std::string replaceNthCopy( const std::string & input, const std::string & search, int32_t n, const std::string & replace )
{
	return boost::algorithm::replace_nth_copy( input, search, n, replace );
}

/**  \brief Заменить N-e вхождение search в строку input новым текстом replace, 
      без учёта регистра.  Отсчёт с нуля. Отрицательные N считаются с конца строки   */
inline void iReplaceNth( std::string & input, const std::string & search, int32_t n, const std::string & replace )
{
	boost::algorithm::ireplace_nth( input, search, n, replace );
}

/** \brief Заменить N-e вхождение search в строку input новым текстом replace, 
    без учёта регистра, вернуть исправленную копию  .
  Отсчёт с нуля. Отрицательные N считаются с конца строки */
inline std::string iReplaceNthCopy( const std::string & input, const std::string & search, int32_t n, const std::string & replace )
{
	return boost::algorithm::ireplace_nth_copy( input, search, n, replace );
}

/** \brief Удалить N-e вхождение search в строку input
    Отсчёт с нуля. Отрицательные N считаются с конца строки  */
inline void eraseNth( std::string & input, const std::string & search, int32_t n )
{
	boost::algorithm::erase_nth( input, search, n );
}

/** \brief Удалить N-e вхождение search в строку input, вернуть исправленную копию
    Отсчёт с нуля. Отрицательные N считаются с конца строки  */
inline std::string eraseNthCopy( const  std::string & input, const std::string & search, int32_t n )
{
	return boost::algorithm::erase_nth_copy( input, search, n );
}

/** \brief  Удалить N-e вхождение search в строку input, без учёта регистра
   Отсчёт с нуля. Отрицательные N считаются с конца строки  */
inline void iEraseNth( std::string & input, const std::string & search, int32_t n )
{
	boost::algorithm::ierase_nth( input, search, n );
}

/** \brief Удалить N-e вхождение search в строку input, без учёта регистра, вернуть исправленную копию
   Отсчёт с нуля. Отрицательные N считаются с конца строки  */
inline std::string iEraseNthCopy( const std::string & input, const std::string & search, int32_t n )
{
	return boost::algorithm::ierase_nth_copy( input, search, n );
}

//! \brief Заменить каждое вхождение search в строку input новым текстом replace
inline void replaceAll( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::replace_all( input, search, replace );
}

//! \brief Заменить каждое вхождение search в строку input новым текстом replace, вернуть исправленную копию
inline std::string replaceAllCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::replace_all_copy( input, search, replace );
}

//! \brief Заменить каждое вхождение search в строку input новым текстом replace, без учёта регистра
inline void iReplaceAll( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::ireplace_all( input, search, replace );
}

//! \brief Заменить каждое вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
inline std::string iReplaceAllCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::ireplace_all_copy( input, search, replace );
}

//! \brief Удалить каждое вхождение search в строку input
inline void eraseAll( std::string & input, const std::string & search )
{
	boost::algorithm::erase_all( input, search );
}

//! \brief Удалить каждое вхождение search в строку input, вернуть исправленную копию
inline std::string eraseAllCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::erase_all_copy( input, search );
}

//! \brief Удалить каждое вхождение search в строку input, без учёта регистра
inline void iEraseAll( std::string & input, const std::string & search )
{
	boost::algorithm::ierase_all( input, search );
}

//! \brief Удалить каждое вхождение search в строку input, без учёта регистра, вернуть исправленную копию
inline std::string iEraseAllCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::ierase_all_copy( input, search );
}

/** \brief Заменить первые N символов строки input новым текстом replace
  Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
inline void replaceHead( std::string & input, int32_t n, const std::string & replace )
{
	boost::algorithm::replace_head( input, n, replace );
}

/** \brief  Заменить первые N символов строки input новым текстом replace, 
   вернуть исправленную копию .
   Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))  */
inline std::string replaceHeadCopy( const std::string & input, int32_t n, const std::string & replace )
{
	return boost::algorithm::replace_head_copy( input, n, replace );
}

/** \brief Заменить последние N символов строки input новым текстом replace
   Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
inline void replaceTail( std::string & input, int32_t n, const std::string & replace )
{
	boost::algorithm::replace_tail( input, n, replace );
}

/** \brief Заменить последние N символов строки input новым текстом replace, 
   вернуть исправленную копию/ Отсчёт с нуля. 
   Для отрицательных N длина считается как (input.length() - abs(N))  */
inline std::string replaceTailCopy( const std::string & input, int32_t n, const std::string & replace )
{
	return boost::algorithm::replace_tail_copy( input, n, replace );
}
		
/** \brief  Удалить первые N символов строки
   Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
inline void eraseHead( std::string & input, int32_t n  )
{
	boost::algorithm::erase_head( input, n );
}

/** \brief Удалить первые N символов строки, вернуть исправленную копию
    Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
inline std::string eraseHeadCopy( const std::string & input, int32_t n )
{
	return boost::algorithm::erase_head_copy( input, n );
}

/** Удалить последние N символов строки
   Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
inline void eraseTail( std::string & input, int32_t n )
{
	boost::algorithm::erase_tail( input, n );
}

/** \brief  Удалить последние N символов строки, вернуть исправленную копию
  Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N)) */
inline std::string eraseTailCopy( const std::string & input, int32_t n )
{
	return boost::algorithm::erase_tail_copy( input, n );
}

#endif // GB_ALLOW_BOOST_LIBRARY




/* in */
#define KS_IN   const

/* out */
#define KS_OUT   

/* in-out */
#define KS_INOUT   

/* in optional */
#define KS_IN_OPTIONAL	 const

/* out optional */
#define KS_OUT_OPTIONAL    


static const char CSTR_ZERO []     = "0";
static const char CSTR_ONE  []     = "1";
static const char CSTR_TWO  []     = "2";




#ifdef GB_ALLOW_BOOST_LIBRARY

template <typename T>
/** \brief Каст из строкового представления в другое */
bool strTo(KS_OUT T& outVal,  const std::string& s)
{
	if( !s.length() ) return false;
	try { outVal = boost::lexical_cast<T>(s); }
	catch( boost::bad_lexical_cast &) {  return false; 	}	return true;
}


template<typename T>
/** \brief Каст из строкового вектора vSrc в тип T и положить результат кастования в vOut
Если при кастокании ошибка, то выполняется выход с возвратом false. Если каст всех значений
успешен вернёт true  */
bool strVectorTo(KS_OUT std::vector<T>& vOut,  const std::vector<std::string>& vSrc)
{

	for(size_t c=0; c<vSrc.size(); c++)
	{
		T val;

		try
		{
			const std::string& src = vSrc[c];
			val  = boost::lexical_cast<T>( src );

		}
		catch( boost::bad_lexical_cast &)
		{
			return false;
		}

		vOut.push_back(val);

	} // for


	return true;
}

#endif // #ifdef GB_ALLOW_BOOST_LIBRARY


//-------------------------------------------------------------------------
//    ks string functions   author: ksacvet777
//-------------------------------------------------------------------------



/** \brief Заполнение вектора по строке делёной символом конца строки  '\n' */
void splitLines(KS_OUT std::vector<std::string>& vOut, const std::string& s) ;

/** \brief сделать все символы в верхнем регистре. Строка должна завершаться нулём */
void cstrToUpper(char* buf) ;

/** \brief сделать все символы в нижнем регистре. Строка должна завершаться нулём */
void cstrToLower(char* buf) ;

/** \brief  Выполняет перевод буквеных символов в верхний(если bUpReg=true) или нижний(если bUpReg=false)
строки в NULL-терминированом буфере buff. <BR> Русские буквы переводятся в соответствии  с кодировкой cr1251
\param buff - [in] Исходный буфер подлежащий конвертации
\param bUpReg - [in]  Установить true если требуется перевод в верхний регистр или false для нижнего   */
void changeCase1251(char* buff, bool bUpReg);

/** \brief    Поиск индексов вхождения символа chToBeSearch в строке src
              с позиции  nStartIndex */
bool searchCharPos(KS_OUT std::vector<int32_t>& vPosOut, const std::string& src,
				   KS_IN char chToBeSearch, KS_IN int32_t nStartIndex);


/** \brief Печать информации о строке на консоль. */
void printStrInfo(const std::string& s);
 
void replaceChar(std::string& s, const char chSymb, const char chNewSymb);

// void StrUt_BoostEraseAll(std::string& s, const std::string& s_erased);

bool loadStrFromFileA (KS_OUT std::string& s,  const char* fname);
bool saveStrToFileA   (KS_IN  std::string& s,  const char* fname);

bool loadStrFromFileW (KS_OUT std::string& s,  const wchar_t* fname);
bool saveStrToFileW   (KS_IN std::string& s,   const wchar_t* fname);
 
//#pragma message ("KS777 ПОПРАВИТЬ"  __FILE__)
//# 
/** \brief Сравнение буферов без учёта регистра   НЕ ПРОВЕРЯЛАСЬ !!! */
bool iCompareCstr(const char* src1, const char* src2, uint32_t nMax );

/** \brief  удалить из текста  все C++ комментарии. <br> 
	Если  chRepl != 0, то закомментированый текст будет заменён этим символом	 <br>
	(табы, пробелы и переносы строк не меняются)  */
void preprocessCppComments(KS_OUT std::string& sDest, const std::string& sSrc, KS_IN_OPTIONAL char chRepl=0 );

/** \brief  удалить из текста  все C++ комментарии. Подробнее смотреть в одноимённой функции выше  */
void preprocessCppComments(KS_INOUT std::string& s, KS_IN_OPTIONAL char chRepl=0);



/** \brief Поиск индекса вхождения   символа. Минус один если не найден */
int32_t findChar(const std::string& s, const char symb, const int32_t nStartPos);

/** \brief Поиск подстроки между символами <br>
	nPosition - с какой позиции и в нём же 
	и результат индекса (позиция завершающего символа)  */
bool findSubstringBetween( 
						  KS_OUT std::string& sResult, const std::string& s,
						  const char chBegin,  
						  const char chEnd,
						  KS_INOUT int32_t& nPosition );

/** \brief Разрезать строку по указаному символу chDiv <br>
    bClearResVecBefore - очистить или нет результирующий вектор vResult перед операцией   */
void ksSplit(KS_OUT std::vector<std::string>& vResult, const std::string& src,
			 const char chDiv,    bool bClearResVecBefore=true );


#if GB_ALLOW_BOOST_LIBRARY
/** \brief Разрезать строку по токенам sTokens */
void splitTokens( KS_OUT std::vector<std::string>& vResult,
				 const std::string& src, const std::string& sTokens );
#endif

/** \brief Разрезать строку по кол-ву указаному в pOffsets и  nOffsLen */
void sliceByOffsets(KS_OUT std::vector<std::string>& vResult, const std::string& src,
					const uint32_t* pOffsets, const int32_t nOffsLen) ;

/** \brief Разрезать строку src между индексами nStartPos && nStopPos
по токену  chToken   */
bool sliceBetweenIndices(KS_OUT std::vector<std::string>& vOut,
						 const std::string& src,
						 KS_IN char  chToken,
						 KS_IN int32_t nStartPos, KS_IN int32_t nStopPos);


/** \brief Проверка на соответствие символа chr любому из szAny  */
bool isAnyOf(const char chr, const std::string& sAny) ;

/** \brief Выполнить поиск в строке src любого символа содержащегося  в sAny
с позиции posit . Если найден то вернёт true и в posit индекс вхождения  */
bool findAnyOf(const std::string& src, KS_INOUT int32_t& posit, const std::string& sAny ) ;

/** \brief Выполнить поиск в строке src с позиции posit поиск
первого символа в диапазоне chBegin ... chEnd  (включительно) .
Если найден то вернёт true и в posit индекс вхождения */
bool findAnyOfBetween(const std::string& src, KS_INOUT int32_t& posit, KS_IN char chBegin, KS_IN char chEnd);



/** \brief  Замена любого символа sAny   в строке src
на новый символ chNewSymb или удаление если chNewSymb == ноль. Результат в sOut  */
void replaceAnyChar(KS_OUT std::string& sOut, const std::string &src, const std::string& sAny, const char chNewSymb);
void replaceAnyChar(KS_INOUT std::string &s, const std::string& sAny, const char chNewSymb) ;




/** \brief Проверка строчки на открывающий xml/html таг    */
bool check_OpenXmlTag(KS_OUT std::string& sOutTag, const std::string& src);

/** \brief Проверка строчки на открывающий xml/html таг по индексу     */
bool check_OpenXmlTag_pos(KS_OUT std::string& sOutTag, 
						  const std::string& src,
						  KS_INOUT int32_t& posit);

/** \brief Проверка строчки на закрывающий xml/html таг     */
bool check_CloseXmlTag(KS_OUT std::string& sOutTag,	const std::string& src);

/** \brief Проверка строчки на закрывающий xml/html таг  по индексу    */
bool check_CloseXmlTag_pos(KS_OUT std::string& sOutTag,
						   const std::string& src,
						   KS_INOUT int32_t& posit);




/** \brief Удаление символов начиная с "//" (с++ однострочный комментарий) */
void skipCppOnelineComment(KS_OUT std::string& dest,	KS_IN std::string& src );

/** \brief Удаление символов начиная с "//" (с++ однострочный комментарий) */
void skipCppOnelineComment(KS_INOUT std::string& s);


void intArrayToStr(KS_OUT std::string& sOut,
				   const int32_t* pArray,  
				   const int32_t nArrayLen,
				   const char* szBegin, 
				   const char* szEnd,
				   const char* szSeparator );


void intArrayToStr(KS_OUT std::string& sOut,
				   const std::vector<int32_t>& vArray,
				   const char* szBegin, 
				   const char* szEnd,
				   const char* szSeparator );


bool intArrayFromStr(
					 KS_OUT int32_t* pBufOut, 
					 KS_IN int32_t nBufLen,
					 KS_IN std::string& src, 
					 KS_IN char chBegin, 
					 KS_IN char chEnd,
					 KS_IN char chSeparator, 
					 KS_OUT_OPTIONAL int32_t* pOutNumReaded = NULL  );


bool intArrayFromStr(
					 KS_OUT std::vector<int32_t>& vOut, 
					 KS_IN std::string& src,
					 KS_IN char chBegin, 
					 KS_IN char chEnd, 
					 KS_IN char chSeparator );


/** \brief  найти следующий символ не равный символам sSkipAnySymbols
в строке src со стартовой позиции nStartPosit. Если найден вернёт true
и в nOutFoundPosit позиция найденого символа */
bool findNextSkipAny(KS_OUT int32_t& nOutFoundPosit, KS_IN std::string& src,
					 KS_IN int32_t nStartPosit,
					 KS_IN std::string& sSkipAnySymbols );


/** \brief Удаление всех символов sAny из строки src с начала и с конца ДО ТОГО как
встретится символ не входящий в sAny. Результат в sOut  .Если других символов
помимо sAny в строке нет вернёт false. */
bool removeAnyFromBeginAndEnd(KS_OUT std::string& sOut, KS_IN std::string& src, KS_IN std::string& sAny);

bool removeAnyFromBeginAndEnd( KS_INOUT std::string& s , KS_IN std::string& sAny) ;

/** \brief Аналог StrUt_RemoveAnyFromBeginAndEnd для вектора строк */
void removeAnyFromBeginAndEnd_Vec(KS_INOUT std::vector<std::string>& v,
								  KS_IN std::string& sAny);


/** \brief Построение текстового массива в строку sOut*/
void strArrayToStr(KS_OUT std::string& sOut, ///< результат.
				   KS_IN std::vector<std::string> vecStr, ///< строки массива.
				   KS_IN char chBegin,  ///< начальный символ или ноль если не нужен.
				   KS_IN char chEnd,    ///< конечный символ или ноль если не нужен.
				   KS_IN char chSeparator, ///< разделитель пунктов массива.
				   bool bAddSpace   ///< добавить или нет пробел.
				   );


/** \brief  Обратная StrUt_WriteStringArrayToStr. Чтение строкового массива из src */
bool strArrayFromStr( KS_OUT std::vector<std::string>& vOut,///<
					 KS_IN std::string& src,///<
					 KS_IN char chBegin, ///< токен начальный символ
					 KS_IN char chEnd, ///< токен конечный символ
					 KS_IN char chSeparator, ///< токен разделитель
					 KS_IN std::string& sRemoveBeginAndEndAny ///< для удалени начальных и конечных символов или пустая строка если нет
					 );


/** \brief Разрезать строку src в вектор vOut по индексам в vIndexes.
	В vIndexes должны быть корректные индексы (каждый должен  быть больше 
	предидущего и меньше следующего. 
	Каждый не должен превышать длину src ) */
bool sliceStrByIndices(std::vector<std::string>& vOut,  
					   const std::string& src, 
					   const std::vector<uint32_t>& vIndexes );


/** \brief Удалить из vInp все пустые строки, а непустые поместить в vOut */
void copyStringsSkipEmpty(std::vector<std::string>& vOut, std::vector<std::string>& vInp);


/** \brief Корректировак строки (добавление слеша (\) перед кавычкой ) */
//bool StrUt_CorrectStrBySpecSymbols_Add(_out std::string& sOut, _in std::string& src);





//---------------------------------------------------------------------
//                     INLINE    FUNCTIONS
//---------------------------------------------------------------------


/** \brief Проверка является ли символ цифровым */
inline bool isDigit(char symb) 
{
	return ( (symb>='0') && (symb<='9') );
}

/** \brief Проверка является ли символ англоязычным символом в ВЕРХНЕМ регистре. */
inline bool isLatinLetterUpper(char symb) 
{
	if (  (symb>='A') && (symb<='Z') ) return true;
	return false;
}

/** \brief Проверка является ли символ англоязычным символом в НИЖНЕМ регистре. */
inline bool isLatinLetterLower(char symb) 
{
	if (  (symb>='a') && (symb<='z') ) return true;
	return false;
}

/** \brief Проверка является ли символ англоязычным символом */
inline bool isLatinLetter(char symb) 
{
	return ( isLatinLetterUpper(symb) || isLatinLetterLower(symb) );
}

/** \brief Является ли символ математическим */
inline bool isMathOperator(char symb) 
{
	return ( (symb == '+') || (symb == '-') || (symb == '*') || (symb == '/')  );
}

/** \brief Присоединяет символ к строке. */
inline void appendChar(char* buf, const char s) 
{
	int32_t iblen = (int32_t)strlen(buf);
	*(buf + iblen) = s;
}

/** \brief Поиск символа новой строки . <br>
	\param
	src - указывает на первый символ в буфере.  
	pos - текущая позиция. */
bool findNextLinePos(const char* src, int32_t& pos) ;


//! \brief Структура для поиска индексов (позиций) вхождения символа в строку. Для функции searchChars.
struct CharsPos_t {

	char charToBeSearsh; ///< символ , который требуется найти

	CharsPos_t(const char chrs): charToBeSearsh(chrs) {}
	CharsPos_t(const CharsPos_t& chs) : charToBeSearsh(chs.charToBeSearsh), vecFoundIndexes(chs.vecFoundIndexes) {}

	std::vector<int> vecFoundIndexes; ///< вектор индексов вхождения символа chToBeSearsh
};

//! \brief поиск в строке src с позиции nStartIndex символов в векторе vchpos  
bool searchChars( std::vector<CharsPos_t>& vchpos, 
				  const char* src,
				  //const std::string& src, 
				  int nStartIndex
				  );



/** \brief  make string:  "<tag>" */
inline std::string makeOpenXmlTag
(const std::string& sTag) {
	std::string  res  = "<";
	res += sTag;
	res += ">";
	return res;
}

/** \brief  make string:  "</tag>" */
inline std::string makeCloseXmlTag(const std::string& sTag) 
{
	std::string  res  = "</";
	res += sTag;
	res += ">";
	return res;
}

inline bool checkSymbolMayBeOpen(KS_IN char symb) 
{
	if( symb == '(' ) return true;
	if( symb == '{' ) return true;
	if( symb == '[' ) return true;
	if( symb == '<' ) return true;

	return false;
}

inline bool checkSymbolMayBeClose(  char symb) 
{
	if( symb == ')' ) return true;
	if( symb == '}' ) return true;
	if( symb == ']' ) return true;
	if( symb == '>' ) return true;

	return false;
}

inline bool checkSymbMayBeSeparator(  char symb) 
{
	if( symb == ',' ) return true;
	if( symb == ';' ) return true;

	return false;
}


//---------------------------------------------------------------------
//         Format    functions
//---------------------------------------------------------------------


/** \brief Преобразование bool в строку в буфер pDest размером ndestlen */
bool boolToCstr( char* pDest, int32_t ndestlen, bool  value );
std::string boolToStr( bool  value );

/** \brief Преобразование value в строку в верхнем регистре 
в буфер pDest размером ndestlen */
bool boolToUppercaseCstr( char* pDest, int32_t ndestlen, bool value );
std::string boolToUppercaseStr( bool value );

/** \brief Преобразование float в строку в буфер pDest размером ndestlen */
bool floatToCstr(char* pDest, int32_t ndestlen, float value);
std::string  floatToStr(float value);

bool floatFromCstr( KS_OUT  float* out_val,  const char* s ) ;
bool floatFromCstr( KS_OUT  float& out_val,  const char* s ) ;

/** \brief Преобразование  знакового целого в строку . Если bAsCppHex true,  тогда конвертирует в HEX в стиль c++  */
bool intToCstr(char* pDest, int32_t ndestlen,  int32_t value, bool bAsCppHex);
/** \brief Преобразование  беззнакового целого в строку   Если bAsCppHex true,  тогда конвертирует в HEX в стиль c++  */
bool uintToCstr(char* pDest, int32_t ndestlen, uint32_t value, bool bAsCppHex);

std::string intToStr  ( int32_t value, bool bAsCppHex);
std::string uintToStr ( uint32_t value, bool bAsCppHex);


/** \brief Преобразование  знакового целого из строки. 

Если неверное значение или исключение, то вернёт false. Можно передавать число d HEX-c++. Например 0x5faf43   */
bool intFromCstr(KS_OUT int32_t* out_val, const char* s) ;
/** \brief Преобразование  знакового целого из строки. Если неверное значение или исключение, то вернёт false.  
Можно передавать число d HEX-c++. Например 0x5faf43  */
bool intFromCstr(KS_OUT int32_t& out_val, const char* s) ;

/** \brief  Аналог intFromCstr  для  unsigned int    */
bool uintFromCstr(KS_OUT uint32_t* out_val, const char* s) ;
bool uintFromCstr(KS_OUT uint32_t& out_val, const char* s) ;


/** \brief Преобразование  целого в строку  в шестнадцатеричном виде   */
bool intToHex(char* pDest, int32_t ndestlen, int32_t value) ;
/** \brief Преобразование  целого в строку  в шестнадцатеричном виде с префиксом "0x" */
bool intToCppHex(char* pDest, int32_t ndestlen, int32_t value) ; 

/** \brief  Перевод указателя в виде hex-строки  в буфер buff  с символами в верхнем регистре.  <BR>
Буфер должен быть длиной не менее 11 . Пример результата = 0xA23A98FC  */
bool pointerToCstr(char* pDest, int32_t ndestlen, const void* p) ;

/** \brief Получение побитовой строки из байта . */
bool  byteToCStrAsBin(char* pDest, int32_t ndestlen, uint8_t value);

/** \brief Преобразование uint32_t в двоичное представление. */
bool uintToBinCstr(char* pDest, int32_t ndestlen, uint32_t value);
/** \brief Преобразование  int32_t в двоичное представление. */
bool intToBinCstr(char* pDest, int32_t ndestlen, uint32_t value);
/** \brief Преобразование uint32_t в двоичное представление. */
std::string uintToBinStr( uint32_t value);
/** \brief Преобразование int32_t в двоичное представление. */
std::string intToBinStr( uint32_t value);


/** \brief Преобразование в uint из строки содержащей цифру в двоичном виде. */
uint32_t uintFromBinCstr(const char* _s, int32_t nlen= -1)  throw(std::runtime_error&);

/** \brief побитовая печать на консоль двойного слова uint32_t */
void printUint32AsBin(  uint32_t value) ;

/** \brief печать  байта  в двоичном представлении на консоль . */
void printByteAsBin(uint8_t value) ;


#if defined (_WIN32)
/** \brief  Хэндл окна в строку */
uint32_t hwndAsUint(const HWND hwnd) ;
#endif


//---------------------------------------------------------------------

	} // namespace str
} // namespace gb



#include <gb/str/KsString.h>



#pragma warning(pop)

// end file