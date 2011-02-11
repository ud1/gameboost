/* \file IntlString.h
 * \brief Класс многоязычной строки и хранилище строк
 * \author Дмитрий Литовченко kvakvs@yandex.ru
*/
#pragma once

#include <gb/Config.h>
#include <gb/base/Guid.h>
#include <gb/i18n/I18n.h>

#include <map>
#include <string>

namespace gb
{
	namespace i18n
	{

 /* Подразумевается схема хранения строк - словарь словарей:
 *	StringSource = словарь {gb::base::Guid StrGuid: IntlStringMap}
 *	IntlStringMap = словарь {std::string StringCode: std::string Value}
 *	StringCode - текстовый код плюс необязательный код языка, например:
 *	{"ONCLICK": "text1", "ONCLICK.EN": "text2", "ONCLICK.ENGB": "text3" }
 *	Поиск переводов производится от полного код+язык+страна, затем код+язык, затем просто код,
 *	затем отдаётся пустая строка
 */
typedef std::map <std::string, std::string> code_string_map_t;

/*! \class StringCollection
 * Коллекция строк - абстрактный класс, служащий источником строк для IntlString
 * Пользователю этого модуля предлагается реализовать пару абстрактных функций, через которые
 * IntlString сможет выбирать из вашей базы данных или хранилища варианты переводов
 */
class IStringSource
{
public:
	//! Задача функции - загрузить по ключу guid, и языку lang_code словарь сообщений
	//! и заполнить ими result
	virtual void loadString( code_string_map_t & result, const gb::base::StringGuid & guid, const LangCode & lang_code ) = 0;
};



/*! \class IntlStringGroup
 * Группа строк с поддержкой нескольких языков, связанная с одним Guid. Например - привязанные
 * к слою сцены или сцене текстовые сообщения и скрипты.
 * Текущий язык запоминается в m_lang и в m_strings загружаются все связанные с этим Guid и языком строки.
 * Если вызвать глоб. функцию setLanguage() то все используемые строки перезагрузят из хранилища новый язык.
 */
class IntlStringGroup
{
private:
	static LangCode		m_globalLanguage;
	static IStringSource * m_stringSource;

	LangCode				m_loadedLanguage;
	gb::base::StringGuid	m_guid;

	/*! IntlStringMap = словарь {std::string StringCode: std::string Value}
	 *	StringCode - текстовый код плюс необязательный код языка, например:
	 *	{"ONCLICK": "text1", "ONCLICK.EN": "text2", "ONCLICK.ENGB": "text3" }
	 */
	code_string_map_t	m_strings;

public:
	IntlStringGroup( const gb::base::StringGuid & guid ): m_guid(guid)
	{
	}

	static void setLanguage( const LangCode & l_code );
	static void setStringSource( IStringSource * src );

	/*! Поиск переводов производится от полного код+язык+страна, затем код+язык, затем просто код,
	 *	затем отдаётся пустая строка
	 */
	std::string get( const std::string & code );

private:
	void _reload();
};



	} // namespace i18n
} // namespace gb
