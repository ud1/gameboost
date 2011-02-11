#pragma once
/*! \file String.h
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 *	Мягкая обёртка вокруг boost/algorithm/string.hpp с возможностью реализации собственных
 *	алгоритмов без подключения библиотеки Boost
 */

#include <gb/Config.h>

#if GB_ALLOW_BOOST_LIBRARY
#include <boost/algorithm/string.hpp>
#endif

#include <list>
#include <set>
#include <vector>
#include <string>


namespace gb
{
	namespace str {
		
		
		
std::string toUtf8( const std::wstring & wide_str );
std::wstring toWide( const std::string & utf8_str );

// Boost запрещён, стоянка велосипедов открывается здесь
#if ! GB_ALLOW_BOOST_LIBRARY

//! Привести к верхнему регистру на месте
void toUpper( std::string & v );

//! Вернуть копию, приведённую к верхнему регистру
std::string toUpperCopy( const std::string & v );

//! Привести к нижнему регистру на месте
void toLower( std::string & v );

//! Вернуть копию, приведённую к нижнему регистру
std::string toLowerCopy( const std::string & v );

//! Обрезать пробелы и табуляции слева, на месте
void trimLeft( std::string & v );

//! Обрезать пробелы и табуляции слева, вернуть исправленную копию
std::string trimLeftCopy( const std::string & v );

//! Обрезать пробелы и табуляции справа, на месте
void trimRight( std::string & v );

//! Обрезать пробелы и табуляции справа, вернуть исправленную копию
std::string trimRightCopy( const std::string & v );

//! Обрезать пробелы и табуляции слева и справа, на месте
void trim( std::string & v );

//! Обрезать пробелы и табуляции слева и справа, вернуть исправленную копию
std::string trimCopy( const std::string & v );

//-------------------------------------------------------------------------
// Предикаты для использования в функциях поиска, или в обычных условиях
//-------------------------------------------------------------------------

//! Начинается ли строка text с фрагмента search?
bool startsWith( const std::string & text, const std::string & search );
//! Начинается ли строка text с фрагмента search? (без учёта регистра)
bool iStartsWith( const std::string & text, const std::string & search );

//! Завершается ли строка text фрагментом search?
bool endsWith( const std::string & text, const std::string & search );
//! Завершается ли строка text фрагментом search? (без учёта регистра)
bool iEndsWith( const std::string & text, const std::string & search );

//! Содержит ли строка text фрагмент search?
bool contains( const std::string & text, const std::string & search );
//! Содержит ли строка text фрагмент search? (без учёта регистра)
bool iContains( const std::string & text, const std::string & search );

//! Равны ли строки друг другу
//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
inline bool equals( const std::string & a, const std::string & b ) {
	return a == b;
}
//! Равны ли строки друг другу без учёта регистра?
//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
bool iEquals( const std::string & a, const std::string & b );

//
//
//

//! Разбить строку value на слова по символам указанным в split_charset, результат
//! сложить в destination
void split( std::vector <std::string> & destination, const std::string & value, const std::string & split_charset );
void split( std::list <std::string> & destination, const std::string & value, const std::string & split_charset );
void split( std::set <std::string> & destination, const std::string & value, const std::string & split_charset );

//! Заменить первое вхождение search в строку input новым текстом replace
void replaceFirst( std::string & input, const std::string & search, const std::string & replace );
//! Заменить первое вхождение search в строку input новым текстом replace, вернуть исправленную копию
std::string replaceFirstCopy( const std::string & input, const std::string & search, const std::string & replace );
//! Заменить первое вхождение search в строку input новым текстом replace, без учёта регистра
void iReplaceFirst( std::string & input, const std::string & search, const std::string & replace );
//! Заменить первое вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
std::string iReplaceFirstCopy( const std::string & input, const std::string & search, const std::string & replace );
		
//! Удалить первое вхождение search в строку input
void eraseFirst( std::string & input, const std::string & search );
//! Удалить первое вхождение search в строку input, вернуть исправленную копию
std::string eraseFirstCopy( const std::string & input, const std::string & search );
//! Удалить первое вхождение search в строку input, без учёта регистра
void iEraseFirst( std::string & input, const std::string & search );
//! Удалить первое вхождение search в строку input, без учёта регистра, вернуть исправленную копию
std::string iEraseFirstCopy( const std::string & input, const std::string & search );

//! Заменить последнее вхождение search в строку input новым текстом replace
void replaceLast( std::string & input, const std::string & search, const std::string & replace );
//! Заменить последнее вхождение search в строку input новым текстом replace, вернуть исправленную копию
std::string replaceLastCopy( const std::string & input, const std::string & search, const std::string & replace );
//! Заменить последнее вхождение search в строку input новым текстом replace, без учёта регистра
void iReplaceLast( std::string & input, const std::string & search, const std::string & replace );
//! Заменить последнее вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
std::string iReplaceLastCopy( const std::string & input, const std::string & search, const std::string & replace );

//! Удалить последнее вхождение search в строку input
void eraseLast( std::string & input, const std::string & search );
//! Удалить последнее вхождение search в строку input, вернуть исправленную копию
std::string eraseLastCopy( const std::string & input, const std::string & search );
//! Удалить последнее вхождение search в строку input, без учёта регистра
void iEraseLast( std::string & input, const std::string & search );
//! Удалить последнее вхождение search в строку input, без учёта регистра, вернуть исправленную копию
std::string iEraseLastCopy( const std::string & input, const std::string & search );

//! Заменить N-е вхождение search в строку input новым текстом replace
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
void replaceNth( std::string & input, const std::string & search, int32_t n, const std::string & replace );
//! Заменить N-e вхождение search в строку input новым текстом replace, вернуть исправленную копию
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
std::string replaceNthCopy( const std::string & input, const std::string & search, int32_t n, const std::string & replace );
//! Заменить N-e вхождение search в строку input новым текстом replace, без учёта регистра
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
void iReplaceNth( std::string & input, const std::string & search, int32_t n, const std::string & replace );
//! Заменить N-e вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
std::string iReplaceNthCopy( const std::string & input, const std::string & search, int32_t n, const std::string & replace );

//! Удалить N-e вхождение search в строку input
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
void eraseNth( std::string & input, const std::string & search, int32_t n );
//! Удалить N-e вхождение search в строку input, вернуть исправленную копию
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
std::string eraseNthCopy( const  std::string & input, const std::string & search, int32_t n );
//! Удалить N-e вхождение search в строку input, без учёта регистра
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
void iEraseNth( std::string & input, const std::string & search, int32_t n );
//! Удалить N-e вхождение search в строку input, без учёта регистра, вернуть исправленную копию
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
std::string iEraseNthCopy( const std::string & input, const std::string & search, int32_t n );

//! Заменить каждое вхождение search в строку input новым текстом replace
void replaceAll( std::string & input, const std::string & search, const std::string & replace );
//! Заменить каждое вхождение search в строку input новым текстом replace, вернуть исправленную копию
std::string replaceAllCopy( const std::string & input, const std::string & search, const std::string & replace );
//! Заменить каждое вхождение search в строку input новым текстом replace, без учёта регистра
void iReplaceAll( std::string & input, const std::string & search, const std::string & replace );
//! Заменить каждое вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
std::string iReplaceAllCopy( const std::string & input, const std::string & search, const std::string & replace );

//! Удалить каждое вхождение search в строку input
void eraseAll( std::string & input, const std::string & search );
//! Удалить каждое вхождение search в строку input, вернуть исправленную копию
std::string eraseAllCopy( const std::string & input, const std::string & search );
//! Удалить каждое вхождение search в строку input, без учёта регистра
void iEraseAll( std::string & input, const std::string & search );
//! Удалить каждое вхождение search в строку input, без учёта регистра, вернуть исправленную копию
std::string iEraseAllCopy( const std::string & input, const std::string & search );

//! Заменить первые N символов строки input новым текстом replace
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
void replaceHead( std::string & input, int32_t n, const std::string & replace );
//! Заменить первые N символов строки input новым текстом replace, вернуть исправленную копию
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
std::string replaceHeadCopy( const std::string & input, int32_t n, const std::string & replace );
//! Заменить последние N символов строки input новым текстом replace
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
void replaceTail( std::string & input, int32_t n, const std::string & replace );
//! Заменить последние N символов строки input новым текстом replace, вернуть исправленную копию
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
std::string replaceTailCopy( const std::string & input, int32_t n, const std::string & replace );
		
//! Удалить первые N символов строки
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
void eraseHead( std::string & input, int32_t n );
//! Удалить первые N символов строки, вернуть исправленную копию
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
std::string eraseHeadCopy( const std::string & input, int32_t n );
//! Удалить последние N символов строки
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
void eraseTail( std::string & input, int32_t n );
//! Удалить последние N символов строки, вернуть исправленную копию
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
std::string eraseTailCopy( const std::string & input, int32_t n );


#else

//! Привести к верхнему регистру на месте
inline void toUpper( std::string & v )
{
	boost::algorithm::to_upper( v );
}

//! Вернуть копию, приведённую к верхнему регистру
inline std::string toUpperCopy( const std::string & v )
{
	return boost::algorithm::to_upper_copy( v );
}

//! Привести к нижнему регистру на месте
inline void toLower( std::string & v )
{
	boost::algorithm::to_lower( v );
}

//! Вернуть копию, приведённую к нижнему регистру
inline std::string toLowerCopy( const std::string & v )
{
	return boost::algorithm::to_lower_copy( v );
}

//! Обрезать пробелы и табуляции слева, на месте
inline void trimLeft( std::string & v )
{
	boost::algorithm::trim_left( v );
}

//! Обрезать пробелы и табуляции слева, вернуть исправленную копию
inline std::string trimLeftCopy( const std::string & v )
{
	return boost::algorithm::trim_left_copy( v );
}

//! Обрезать пробелы и табуляции справа, на месте
inline void trimRight( std::string & v )
{
	boost::algorithm::trim_right( v );
}

//! Обрезать пробелы и табуляции справа, вернуть исправленную копию
inline std::string trimRightCopy( const std::string & v )
{
	return boost::algorithm::trim_right_copy( v );
}

//! Обрезать пробелы и табуляции слева и справа, на месте
inline void trim( std::string & v )
{
	boost::algorithm::trim( v );
}

//! Обрезать пробелы и табуляции слева и справа, вернуть исправленную копию
inline std::string trimCopy( const std::string & v )
{
	return boost::algorithm::trim_copy( v );
}

//-------------------------------------------------------------------------
// Предикаты для использования в функциях поиска, или в обычных условиях
//-------------------------------------------------------------------------

//! Начинается ли строка text с фрагмента search?
inline bool startsWith( const std::string & text, const std::string & search )
{
	return boost::algorithm::starts_with( text, search );
}
//! Начинается ли строка text с фрагмента search? (без учёта регистра)
inline bool iStartsWith( const std::string & text, const std::string & search )
{
	return boost::algorithm::istarts_with( text, search );
}

//! Завершается ли строка text фрагментом search?
inline bool endsWith( const std::string & text, const std::string & search )
{
	return boost::algorithm::ends_with( text, search );
}
//! Завершается ли строка text фрагментом search? (без учёта регистра)
inline bool iEndsWith( const std::string & text, const std::string & search )
{
	return boost::algorithm::iends_with( text, search );
}

//! Содержит ли строка text фрагмент search?
inline bool contains( const std::string & text, const std::string & search )
{
	return boost::algorithm::contains( text, search );
}
//! Содержит ли строка text фрагмент search? (без учёта регистра)
inline bool iContains( const std::string & text, const std::string & search )
{
	return boost::algorithm::icontains( text, search );
}

//! Равны ли строки друг другу
//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
inline bool equals( const std::string & a, const std::string & b )
{
	return a == b;
}
//! Равны ли строки друг другу без учёта регистра?
//! (не имеет смысла в простом условии, но полезно, как предикат для поиска)
inline bool iEquals( const std::string & a, const std::string & b )
{
	return boost::algorithm::iequals( a, b );
}

//
//
//

//! Разбить строку value на слова по символам указанным в split_charset, результат
//! сложить в destination
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

		
		
//! Заменить первое вхождение search в строку input новым текстом replace
inline void replaceFirst( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::replace_first( input, search, replace );
}
//! Заменить первое вхождение search в строку input новым текстом replace, вернуть исправленную копию
inline std::string replaceFirstCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::replace_first_copy( input, search, replace );
}
//! Заменить первое вхождение search в строку input новым текстом replace, без учёта регистра
inline void iReplaceFirst( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::ireplace_first( input, search, replace );
}
//! Заменить первое вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
inline std::string iReplaceFirstCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::ireplace_first_copy( input, search, replace );
}
		
//! Удалить первое вхождение search в строку input
inline void eraseFirst( std::string & input, const std::string & search )
{
	boost::algorithm::erase_first( input, search );
}
//! Удалить первое вхождение search в строку input, вернуть исправленную копию
inline std::string eraseFirstCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::erase_first_copy( input, search );
}
//! Удалить первое вхождение search в строку input, без учёта регистра
inline void iEraseFirst( std::string & input, const std::string & search )
{
	boost::algorithm::ierase_first( input, search );
}
//! Удалить первое вхождение search в строку input, без учёта регистра, вернуть исправленную копию
inline std::string iEraseFirstCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::ierase_first_copy( input, search );
}

//! Заменить последнее вхождение search в строку input новым текстом replace
inline void replaceLast( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::replace_last( input, search, replace );
}
//! Заменить последнее вхождение search в строку input новым текстом replace, вернуть исправленную копию
inline std::string replaceLastCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::replace_last_copy( input, search, replace );
}
//! Заменить последнее вхождение search в строку input новым текстом replace, без учёта регистра
inline void iReplaceLast( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::ireplace_last( input, search, replace );
}
//! Заменить последнее вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
inline std::string iReplaceLastCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::ireplace_last_copy( input, search, replace );
}

//! Удалить последнее вхождение search в строку input
inline void eraseLast( std::string & input, const std::string & search )
{
	boost::algorithm::erase_last( input, search );
}
//! Удалить последнее вхождение search в строку input, вернуть исправленную копию
inline std::string eraseLastCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::erase_last_copy( input, search );
}
//! Удалить последнее вхождение search в строку input, без учёта регистра
inline void iEraseLast( std::string & input, const std::string & search )
{
	boost::algorithm::ierase_last( input, search );
}
//! Удалить последнее вхождение search в строку input, без учёта регистра, вернуть исправленную копию
inline std::string iEraseLastCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::ierase_last_copy( input, search );
}

//! Заменить N-е вхождение search в строку input новым текстом replace
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
inline void replaceNth( std::string & input, const std::string & search, int32_t n, const std::string & replace )
{
	boost::algorithm::replace_nth( input, search, n, replace );
}
//! Заменить N-e вхождение search в строку input новым текстом replace, вернуть исправленную копию
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
inline std::string replaceNthCopy( const std::string & input, const std::string & search, int32_t n, const std::string & replace )
{
	return boost::algorithm::replace_nth_copy( input, search, n, replace );
}
//! Заменить N-e вхождение search в строку input новым текстом replace, без учёта регистра
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
inline void iReplaceNth( std::string & input, const std::string & search, int32_t n, const std::string & replace )
{
	boost::algorithm::ireplace_nth( input, search, n, replace );
}
//! Заменить N-e вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
inline std::string iReplaceNthCopy( const std::string & input, const std::string & search, int32_t n, const std::string & replace )
{
	return boost::algorithm::ireplace_nth_copy( input, search, n, replace );
}

//! Удалить N-e вхождение search в строку input
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
inline void eraseNth( std::string & input, const std::string & search, int32_t n )
{
	boost::algorithm::erase_nth( input, search, n );
}
//! Удалить N-e вхождение search в строку input, вернуть исправленную копию
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
inline std::string eraseNthCopy( const  std::string & input, const std::string & search, int32_t n )
{
	return boost::algorithm::erase_nth_copy( input, search, n );
}
//! Удалить N-e вхождение search в строку input, без учёта регистра
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
inline void iEraseNth( std::string & input, const std::string & search, int32_t n )
{
	boost::algorithm::ierase_nth( input, search, n );
}
//! Удалить N-e вхождение search в строку input, без учёта регистра, вернуть исправленную копию
//! Отсчёт с нуля. Отрицательные N считаются с конца строки
inline std::string iEraseNthCopy( const std::string & input, const std::string & search, int32_t n )
{
	return boost::algorithm::ierase_nth_copy( input, search, n );
}

//! Заменить каждое вхождение search в строку input новым текстом replace
inline void replaceAll( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::replace_all( input, search, replace );
}
//! Заменить каждое вхождение search в строку input новым текстом replace, вернуть исправленную копию
inline std::string replaceAllCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::replace_all_copy( input, search, replace );
}
//! Заменить каждое вхождение search в строку input новым текстом replace, без учёта регистра
inline void iReplaceAll( std::string & input, const std::string & search, const std::string & replace )
{
	boost::algorithm::ireplace_all( input, search, replace );
}
//! Заменить каждое вхождение search в строку input новым текстом replace, без учёта регистра, вернуть исправленную копию
inline std::string iReplaceAllCopy( const std::string & input, const std::string & search, const std::string & replace )
{
	return boost::algorithm::ireplace_all_copy( input, search, replace );
}

//! Удалить каждое вхождение search в строку input
inline void eraseAll( std::string & input, const std::string & search )
{
	boost::algorithm::erase_all( input, search );
}
//! Удалить каждое вхождение search в строку input, вернуть исправленную копию
inline std::string eraseAllCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::erase_all_copy( input, search );
}
//! Удалить каждое вхождение search в строку input, без учёта регистра
inline void iEraseAll( std::string & input, const std::string & search )
{
	boost::algorithm::ierase_all( input, search );
}
//! Удалить каждое вхождение search в строку input, без учёта регистра, вернуть исправленную копию
inline std::string iEraseAllCopy( const std::string & input, const std::string & search )
{
	return boost::algorithm::ierase_all_copy( input, search );
}

//! Заменить первые N символов строки input новым текстом replace
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
inline void replaceHead( std::string & input, int32_t n, const std::string & replace )
{
	boost::algorithm::replace_head( input, n, replace );
}
//! Заменить первые N символов строки input новым текстом replace, вернуть исправленную копию
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
inline std::string replaceHeadCopy( const std::string & input, int32_t n, const std::string & replace )
{
	return boost::algorithm::replace_head_copy( input, n, replace );
}
//! Заменить последние N символов строки input новым текстом replace
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
inline void replaceTail( std::string & input, int32_t n, const std::string & replace )
{
	boost::algorithm::replace_tail( input, n, replace );
}
//! Заменить последние N символов строки input новым текстом replace, вернуть исправленную копию
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
inline std::string replaceTailCopy( const std::string & input, int32_t n, const std::string & replace )
{
	return boost::algorithm::replace_tail_copy( input, n, replace );
}
		
//! Удалить первые N символов строки
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
inline void eraseHead( std::string & input, int32_t n  )
{
	boost::algorithm::erase_head( input, n );
}
//! Удалить первые N символов строки, вернуть исправленную копию
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
inline std::string eraseHeadCopy( const std::string & input, int32_t n )
{
	return boost::algorithm::erase_head_copy( input, n );
}
//! Удалить последние N символов строки
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
inline void eraseTail( std::string & input, int32_t n )
{
	boost::algorithm::erase_tail( input, n );
}
//! Удалить последние N символов строки, вернуть исправленную копию
//! Отсчёт с нуля. Для отрицательных N длина считается как (input.length() - abs(N))
inline std::string eraseTailCopy( const std::string & input, int32_t n )
{
	return boost::algorithm::erase_tail_copy( input, n );
}

#endif // GB_ALLOW_BOOST_LIBRARY



	} // namespace str
} // namespace gb
