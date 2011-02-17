
#include <gb/i18n/Japanese.h>
#include <gb/str/String.h>

namespace gb {
	namespace i18n {


void CJapaneseTools::SplitLines( std::list <std::string> & result, const std::string & text )
{
	result.clear();
	gb::str::split (result, text, "\n\r");
}



void CJapaneseTools::SplitWords( std::list <std::string> & result, const std::string & text )
{
	result.clear();

	const char * start_ptr = text.c_str();
	size_t count;
	const char * word_start = start_ptr;

	const char * current_ptr = start_ptr;
	uint32_t current_char = 0;
	ECharacterClass current_class = CLASS_NONE;
	
	const char * previous_ptr = start_ptr;
	uint32_t previous_char;
	ECharacterClass previous_class;

	while (* current_ptr)
	{
		previous_char = current_char;
		previous_class = current_class;

		count = gb::str::decodeUtf8Character (current_char, current_ptr);
		current_class = _Classify (current_char);

		bool allow_wordbreak = (previous_class != CLASS_DIGIT && current_class == CLASS_DIGIT)
			// символ пунктуации, последний в серии подобных
			|| (previous_class == CLASS_WORD_END && current_class != CLASS_WORD_END)
			// открывающая японская квадратная скобка『
			|| current_char == 0x300E
			// смена хираганы
			|| (previous_class == CLASS_HIRAGANA && (
				current_class == CLASS_KATAKANA 
				|| current_class == CLASS_KANJI
				|| current_class == CLASS_SOMETHING_ELSE))
			// смена катаканы
			|| (previous_class == CLASS_KATAKANA && (
				current_class == CLASS_HIRAGANA 
				|| current_class == CLASS_KANJI
				|| current_class == CLASS_SOMETHING_ELSE))
			// смена канджи
			|| (previous_class == CLASS_KANJI && (
				current_class == CLASS_HIRAGANA 
				|| current_class == CLASS_KATAKANA
				|| current_class == CLASS_SOMETHING_ELSE));
		
		// 1.Punctuations (、as a comma, 。as a period) can’t be the line head.
		if (previous_class == CLASS_UNBREAKABLE_DASH
			|| current_class == CLASS_UNBREAKABLE_DASH)
		{
			allow_wordbreak = false;
		}

		if (allow_wordbreak)
		{
			std::string word (word_start, current_ptr - word_start);
			result.push_back (word);
			
			word_start += word.length();
		}

		previous_ptr = current_ptr;
		current_ptr += count;
	}

	std::string word (word_start, current_ptr - word_start);
	if (! word.empty())
	{
		result.push_back (word);
	}
}



CJapaneseTools::ECharacterClass CJapaneseTools::_Classify (uint32_t c)
{
	//lower case or extending (～ or ー) character in any form
	if (c == 0xFF5E || c == 0x30FC)
	{
		return CLASS_UNBREAKABLE_DASH;
	}

	// 2009 - ２００９
	if (c >= '0' && c <= '9'	// обычные цифры
		|| c >= 0xFF10 && c <= 0xFF19) // японские широкие цифры
	{
		return CLASS_DIGIT;
	}

	// 1.Punctuations (、as a comma, 。as a period) can’t be the line head.
	// (This applies to special characters such as exclamation mark (!) and question mark (?), … etc.)
	if (c == 0x3002 // japanese hollow dot .
		|| c == 0x3001 // japanese comma ,
		|| c == 0x30FB  // japanese solid dot .
		|| c == 0x2026	// japanese ellipsis ...
		|| c == 0xFF01 // japanese exclamation mark !
		|| c == 0xFF1F // japanese question mark ?
		|| c == '.'		// ASCII dot
		|| c == ' '		// ASCII space
		|| c == ','	// ASCII comma
		|| c == 0x300F	// japanese closing square bracket 』
		)
	{
		return CLASS_WORD_END;
	}

	//------------------------------------------------------------------------------------------------

	if (c >= 0x3040 && c < 0x30A0)
	{
		return CLASS_HIRAGANA;
	}

	if (c >= 0x30A0 && c < 0x3100 // обычная катакана
		|| c >= 0xFF65 && c <= 0xFF9F // узкая катакана
		)
	{
		return CLASS_KATAKANA;
	}

	if (c >= 0x4E9C && c <= 0x7464)
	{
		return CLASS_KANJI;
	}

	//------------------------------------------------------------------------------------------------

	return CLASS_SOMETHING_ELSE;
}


	} // namespace gb
} // namespace i18n
