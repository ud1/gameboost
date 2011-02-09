/*! \file String.h
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 *	Мягкая обёртка вокруг boost/algorithm/string.hpp с возможностью реализации собственных
 *	алгоритмов без подключения библиотеки Boost
 */
#include "pch.h"

#include "base/String.h"

#include <utfcpp/checked.h>
#include <utfcpp/unchecked.h>

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


	} // namespace str
} // namespace gb

#undef GB_PRERESERVE_STRINGS
