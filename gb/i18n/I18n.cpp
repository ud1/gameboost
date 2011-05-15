/* \file I18n.h
 * \brief Запланированный модуль: Поддержка японского, европейского текста, разбивка на слова, строки
 * \author Дмитрий Литовченко kvakvs@yandex.ru
*/
#include <gb/i18n/I18n.h>

#include <cctype>

namespace gb
{
	namespace i18n
	{


LangCode::LangCode( const std::string & locale )
{
	if (locale.length() == 2)
	{
		this->m_code = ((uint32_t)std::toupper( locale[0] ) << 24)
			| ((uint32_t)std::toupper( locale[1] ) << 16);
	}
	if (locale.length() == 5 & locale[2] == '_')
	{
		this->m_code = ((uint32_t)std::toupper( locale[0] ) << 24)
			| ((uint32_t)std::toupper( locale[1] ) << 16)
			| ((uint32_t)std::toupper( locale[3] ) << 8)
			| (uint32_t)std::toupper( locale[4] );
	}
	
	this->m_code = 0;
}


const char * LangCode::getUppercaseSearchSuffix()
{
	static char suffix[6];
	suffix[0] = '.';
	suffix[1] = (char)(m_code >> 24);
	suffix[2] = (char)(m_code >> 16);
	suffix[3] = (char)(m_code >> 8);
	suffix[4] = (char)m_code;
	suffix[5] = '\x00';
	return suffix;
}


const char * LangCode::getLangUppercaseSearchSuffix()
{
	static char suffix[4];
	suffix[0] = '.';
	suffix[1] = (char)(m_code >> 24);
	suffix[2] = (char)(m_code >> 16);
	suffix[3] = '\x00';
	return suffix;
}


	} // namespace gb
} // namespace i18n
