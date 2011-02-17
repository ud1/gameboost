

#include <gb/i18n/RomanicGermanic.h>
#include <gb/str/String.h>

namespace gb {
	namespace i18n {


// разбить на строки
void CRomanicGermanicTools::SplitLines( std::list <std::string> & result, const std::string & text )
{
	result.clear();
	gb::str::split (result, text, "\n\r");
}



void CRomanicGermanicTools::SplitWords( std::list <std::string> & result, const std::string & text )
{
	result.clear();

	std::string t (text);
	gb::str::trim (t);
	gb::str::split (result, t, " ");
}

	} // namespace gb
} // namespace i18n
