/*! \file String.h
 *	\author Дмитрий Литовченко kvakvs@yandex.ru
 *	Мягкая обёртка вокруг boost/algorithm/string.hpp с возможностью реализации собственных
 *	алгоритмов без подключения библиотеки Boost
 */
 
 //#include "pch.h"
//#include "d3d9pch.h"

#include <gb/str/String.h>

#include <utfcpp/checked.h>
#include <utfcpp/unchecked.h>


#include <sstream>
#include <cctype>
//#include <mbstring.h>

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

uint32_t decodeUtf8Character( uint32_t & out_result, const char * utf8 )
{
	unsigned char c = utf8[0];
	out_result = L'?';

	if(c < 0x80)		// 1-byte code
	{
		out_result = c;
		return 1;
	}
	else if(c < 0xC0)     // invalid
	{
		return 1;
	}
	else if(c < 0xE0)	// 2-byte code
	{
		out_result =  (c & 0x1F) << 6;
		c = utf8[1];
		out_result |= (c & 0x3F);
		return 2;
	}
	else if(c < 0xF0)     // 3-byte code
	{
		out_result =  (c & 0x0F) << 12;
		c = utf8[1];
		out_result |= (c & 0x3F) <<  6;
		c = utf8[2];
		out_result |= (c & 0x3F);
		return 3;
	}
	else if(c < 0xF8)     // 4-byte code
	{
		// make sure wchar_t is large enough to hold it
		//if(std::numeric_limits<wchar_t>::max() > 0xFFFF)
		{
			out_result =  (c & 0x07) << 18;
			c = utf8[1];
			out_result |= (c & 0x3F) << 12;
			c = utf8[2];
			out_result |= (c & 0x3F) <<  6;
			c = utf8[3];
			out_result |= (c & 0x3F);
			return 4;
		}
	}
	return 1;
}

uint32_t uint32FromHex (const std::string & s)
{
	std::istringstream stream(s);
	uint32_t result;
	stream >> std::hex >> result;
	if (stream.fail()) return 0;
	return result;
}

uint64_t uint64FromHex (const std::string & s)
{
	std::istringstream stream(s);
	uint64_t result;
	stream >> std::hex >> result;
	if (stream.fail()) return 0;
	return result;
}



#if ! GB_ALLOW_BOOST_LIBRARY
void toUpper( std::string & v )
{
// #ifdef _WIN32
// 	v = toUpperCopy(v);
// #else
	// Делаем морду валенком, как будто так и надо, и работаем только с ASCII
	for( size_t i = 0; i < v.size(); ++i ) v[i] = std::toupper( v[i] );
// #endif
}
#endif


#if ! GB_ALLOW_BOOST_LIBRARY
std::string toUpperCopy( const std::string & v )
{
// #ifdef _WIN32
// 	// TODO: вынести это куда-то глобально
// 	static _locale_t utf8Locale = _create_locale( LC_ALL, "en_US.UTF8" );
// 	// TODO: Не самый оптимальный вариант с копированием символов
// 	std::auto_ptr <uint8_t> tmp( new uint8_t [v.length()+1] );
// 	_mbscpy_s( tmp.get(), v.length()+1, (const uint8_t *)v.c_str() );
// 	_mbsupr_s_l( tmp.get(), v.length()+1, utf8Locale );
// 	return std::string( (const char *)tmp.get(), v.length() );
// #else
	std::string upper_v;
	upper_v.resize (v);
	// Делаем морду валенком, как будто так и надо, и работаем только с ASCII
	for( size_t i = 0; i < v.size(); ++i ) upper_v[i] = std::toupper( v[i] );
	return upper_v;
// #endif
}
#endif



#if ! GB_ALLOW_BOOST_LIBRARY
void toLower( std::string & v )
{
// #ifdef _WIN32
// 	v = toLowerCopy(v);
// #else
	std::string lower_v;
	lower_v.resize (v);
	// Делаем морду валенком, как будто так и надо, и работаем только с ASCII
	for( size_t i = 0; i < v.size(); ++i ) lower_v[i] = std::tolower( v[i] );
	return lower_v;
// #endif
}
#endif


#if ! GB_ALLOW_BOOST_LIBRARY
std::string toLowerCopy( const std::string & v )
{
// #ifdef _WIN32
// 	// TODO: вынести это куда-то глобально
// 	static _locale_t utf8Locale = _create_locale( LC_ALL, "en_US.UTF8" );
// 	// TODO: Не самый оптимальный вариант с копированием символов
// 	std::auto_ptr <uint8_t> tmp( new uint8_t [v.length()+1] );
// 	_mbscpy_s( tmp.get(), v.length()+1, (const uint8_t *)v.c_str() );
// 	_mbslwr_s_l( tmp.get(), v.length()+1, utf8Locale );
// 	return std::string( (const char *)tmp.get(), v.length() );
// #else
	std::string s( v );
	toLower( s );
	return s;
// #endif
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
