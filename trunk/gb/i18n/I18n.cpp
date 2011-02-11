/* \file I18n.h
 * \brief Запланированный модуль: Поддержка японского, европейского текста, разбивка на слова, строки
 * \author Дмитрий Литовченко kvakvs@yandex.ru
*/
#include "pch.h"
#include <gb/i18n/I18n.h>

#include <cctype>

namespace gb
{
	namespace i18n
	{


LangCode::LangCode( const char * locale )
{
	size_t l_len = strlen( locale ) ;

	if (l_len == 2)
	{
		this->code = ((uint32_t)std::toupper( locale[0] ) << 24)
			| ((uint32_t)std::toupper( locale[1] ) << 16);
	}
	if (l_len == 5 & locale[2] == '_')
	{
		this->code = ((uint32_t)std::toupper( locale[0] ) << 24)
			| ((uint32_t)std::toupper( locale[1] ) << 16)
			| ((uint32_t)std::toupper( locale[3] ) << 8)
			| (uint32_t)std::toupper( locale[4] );
	}
	
	this->code = 0;
}


	} // namespace gb
} // namespace i18n
