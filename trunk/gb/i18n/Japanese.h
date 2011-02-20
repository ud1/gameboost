/* \file Japanese.inl.h
* \brief Запланированный субмодуль: Поддержка японского текста, разбивка на слова, строки
* \author Дмитрий Литовченко kvakvs@yandex.ru
*/
#pragma once

#include <list>
#include <string>

#include <gb/base/Types.h>

namespace gb {
	namespace i18n {

//! Инструменты для японского
class CJapaneseTools
{
protected:
	typedef enum
	{
		CLASS_NONE,
		CLASS_SOMETHING_ELSE,     // все прочие символы, не перечисленные здесь
		CLASS_DIGIT,
		CLASS_LATIN,
		CLASS_HIRAGANA,
		CLASS_KATAKANA,
		CLASS_KANJI,
		CLASS_UNBREAKABLE_DASH, // символ неразрывного тире или тильды
		CLASS_WORD_END,       // символ пунктуации пригодный для разбивки слова
		CLASS_LINE_END,       // символ пригодный для разбивки строки
	} ECharacterClass;

public:
	//! Разбить по строкам
	static void SplitLines (std::list <std::string> & result, const std::string & text);

	//! Разбить по словам
	static void SplitWords (std::list <std::string> & result, const std::string & text);

	//! Требуется пробел между словами
	inline static bool SpaceBetweenWords() { return false; }

	static inline const char * CurrentLang() { return "JP"; }

protected:
	//! Распознать японский символ причислить к одной из групп
	static ECharacterClass _Classify (uint32_t c);
};


	} // namespace gb
} // namespace i18n
