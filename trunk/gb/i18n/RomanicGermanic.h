/* \file RomanicGermanic.inl.h
* \brief Запланированный субмодуль: Поддержка романо-германского текста (европейские языки, русский), разбивка на слова, строки
* \author Дмитрий Литовченко kvakvs@yandex.ru
*/
#pragma once

#include <list>
#include <string>

namespace gb {
	namespace i18n {

//! Инструменты для романо-германских языков - английский, немецкий, французский
class CRomanicGermanicTools
{
public:
	//! Разбить по строкам
	static void SplitLines (std::list <std::string> & result, const std::string & text);

	//! Разбить по словам
	static void SplitWords (std::list <std::string> & result, const std::string & text);

	//! Требуется пробел между словами
	inline static bool SpaceBetweenWords() { return true; }



#ifdef EELOCALE_EN
	static inline const char * CurrentLang() { return "EN"; }
#endif
#ifdef EELOCALE_RU
	static inline const char * CurrentLang() { return "RU"; }
#endif
#ifdef EELOCALE_DE
	static inline const char * CurrentLang() { return "DE"; }
#endif
#ifdef EELOCALE_ES
	static inline const char * CurrentLang() { return "ES"; }
#endif
#ifdef EELOCALE_FR
	static inline const char * CurrentLang() { return "FR"; }
#endif
};

	} // namespace gb
} // namespace i18n
