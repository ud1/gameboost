/* \file I18n.h
 * \brief Запланированный модуль: Поддержка японского, европейского текста, разбивка на слова, строки
 * \author Дмитрий Литовченко kvakvs@yandex.ru
*/
namespace gb
{
	namespace i18n
	{

// Таблица соответствия стран и языков локалям http://www.science.co.il/language/locale-codes.asp

//! Код языка, содержит 2 буквы языка, и 2 буквы страны, подобно DirectX FOURCC
//! Два старших байта - код языка, два младших - нули или код страны
class LangCode
{
protected:
	//! Код языка и страны 'EN\0\0', 'RU\0\0' или 'ENUS', 'ENGB', 'RURU', 'RUUA' и проч.
	uint32_t	code;

public:
	//! На входе локаль в формате "en", или "en_US"
	LangCode( const char * locale );

	inline bool matchExact( uint32_t other_code ) 
	{
		return (code == other_code);
	}

	//! Сравнивает только языки, и только если в нашем языке страна 0x0000
	//! С помощью этой функции можно, например, для Британского Английского (ENGB)
	//! подобрать значение из общего Английского перевода (EN\0\0).
	inline bool matchLang( uint32_t other_code ) 
	{
		return (
			(code & 0xFFFF0000) == (other_code & 0xFFFF0000)
			&& ( ! (uint16_t)code )
			);
	}
};


	} // namespace gb
} // namespace i18n
