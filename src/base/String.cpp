/*! \file String.h
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 *	Мягкая обёртка вокруг boost/algorithm/string.hpp с возможностью реализации собственных
 *	алгоритмов без подключения библиотеки Boost
 */
#include "pch.h"

#include "base/String.h"

#include <utfcpp/checked.h>
#include <utfcpp/unchecked.h>

#include <cctype>
#include <mbstring.h>

// предварительно растягивать длину строк при конверсиях (теоретически ускоряет работу)
#define GB_PRERESERVE_STRINGS 1

namespace gb
{
	namespace str
	{


std::string toUtf8( const std::wstring & wide_str )
{
	std::string utf8_str;
#if GB_PRERESERVE_STRINGS
	// пессимистический прогноз все символы будут 2 байта
	utf8_str.reserve( wide_str.length() * 2 );
#endif
	utf8::utf16to8 (wide_str.begin(), wide_str.end(), std::back_inserter(utf8_str));
	return utf8_str;
}


std::wstring toWide( const std::string & utf8_str )
{
	std::wstring wide_str;
#if GB_PRERESERVE_STRINGS
	// пессимистический прогноз все символы 1 байт
	wide_str.reserve( utf8_str.length() );
#endif
	utf8::utf8to16 (utf8_str.begin(), utf8_str.end(), std::back_inserter(wide_str));
	return wide_str;
}


#if ! GB_ALLOW_BOOST_LIBRARY
void toUpper( std::string & v )
{
#ifdef _WIN32
	v = toUpperCopy(v);
#else
	// Делаем морду валенком, как будто так и надо, и работаем только с ASCII
	for( size_t i = 0; i < v.size(); ++i ) v[i] = std::toupper( v[i] );
#endif
}
#endif


#if ! GB_ALLOW_BOOST_LIBRARY
std::string toUpperCopy( const std::string & v )
{
#ifdef _WIN32
	// TODO: вынести это куда-то глобально
	static _locale_t utf8Locale = _create_locale( LC_ALL, "en_US.UTF8" );
	// TODO: Не самый оптимальный вариант с копированием символов
	std::auto_ptr <uint8_t> tmp( new uint8_t [v.length()+1] );
	_mbscpy_s( tmp.get(), v.length()+1, (const uint8_t *)v.c_str() );
	_mbsupr_s_l( tmp.get(), v.length()+1, utf8Locale );
	return std::string( (const char *)tmp.get(), v.length() );
#else
	std::string upper_v;
	upper_v.resize (v);
	// Делаем морду валенком, как будто так и надо, и работаем только с ASCII
	for( size_t i = 0; i < v.size(); ++i ) upper_v[i] = std::toupper( v[i] );
	return upper_v;
#endif
}
#endif



#if ! GB_ALLOW_BOOST_LIBRARY
void toLower( std::string & v )
{
#ifdef _WIN32
	v = toLowerCopy(v);
#else
	std::string lower_v;
	lower_v.resize (v);
	// Делаем морду валенком, как будто так и надо, и работаем только с ASCII
	for( size_t i = 0; i < v.size(); ++i ) lower_v[i] = std::tolower( v[i] );
	return lower_v;
#endif
}
#endif


#if ! GB_ALLOW_BOOST_LIBRARY
std::string toLowerCopy( const std::string & v )
{
#ifdef _WIN32
	// TODO: вынести это куда-то глобально
	static _locale_t utf8Locale = _create_locale( LC_ALL, "en_US.UTF8" );
	// TODO: Не самый оптимальный вариант с копированием символов
	std::auto_ptr <uint8_t> tmp( new uint8_t [v.length()+1] );
	_mbscpy_s( tmp.get(), v.length()+1, (const uint8_t *)v.c_str() );
	_mbslwr_s_l( tmp.get(), v.length()+1, utf8Locale );
	return std::string( (const char *)tmp.get(), v.length() );
#else
#endif
}
#endif


#if ! GB_ALLOW_BOOST_LIBRARY
bool startsWith( const std::string & text, const std::string & search )
{
	return text.substr( 0, search.length() ) == search;
}
#endif



	} // namespace str
} // namespace gb

#undef GB_PRERESERVE_STRINGS
