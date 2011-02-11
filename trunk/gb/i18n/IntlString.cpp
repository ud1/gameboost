/* \file IntlString.cpp
 * \brief Класс многоязычной строки и хранилище строк
 * \author Дмитрий Литовченко kvakvs@yandex.ru
*/
#include "pch.h"

#include <gb/i18n/IntlString.h>

namespace gb
{
	namespace i18n
	{


LangCode		IntlStringGroup::m_globalLanguage;
IStringSource	* IntlStringGroup::m_stringSource;


void IntlStringGroup::setLanguage( const LangCode & l_code )
{
	m_globalLanguage = l_code;
}


std::string IntlStringGroup::get( const std::string & code )
{
	if (m_loadedLanguage.empty()) {
		_reload();
	}

	code_string_map_t::iterator i;

	// попробовать точное совпадение ${KEY}.${LANG}${COUNTRY}
	i = m_strings.find( code + m_loadedLanguage.getUppercaseSearchSuffix() );
	if (i != m_strings.end()) return i->second;

	// попробовать совпадение по языку ${KEY}.${LANG}
	if (! m_loadedLanguage.emptyCountry()) {
		i = m_strings.find( code + m_loadedLanguage.getLangUppercaseSearchSuffix() );
		if (i != m_strings.end()) return i->second;
	}

	// попробовать совпадение по ключу ${KEY}
	i = m_strings.find( code );
	if (i != m_strings.end()) return i->second;

	return "";
}



void IntlStringGroup::_reload()
{
	m_strings.clear();
	m_stringSource->loadString( m_strings, m_guid, m_globalLanguage );
}



void IntlStringGroup::setStringSource( IStringSource * src )
{
	m_stringSource = src;
}



	} // namespace i18n
} // namespace gb
