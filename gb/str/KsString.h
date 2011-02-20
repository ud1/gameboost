/** \file KsString.h
 * \brief Строки и сопутствующие типы.
 * Класс на основе STL и BOOST
 * \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
 * \author Reviewer/imported by: kvakvs (kvakvs@yandex.ru)
 */
#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <string>
#include <cctype>
#include <vector>
#include <list>

#include <gb/Config.h>
#include <gb/base/Types.h>
#include <gb/str/KsDefines.h>


#if GB_ALLOW_BOOST_LIBRARY
	#include <boost/algorithm/string.hpp>
	#include <boost/tokenizer.hpp>
	#include <boost/lexical_cast.hpp>
#endif

#pragma warning( push )
#pragma warning( disable : 4996 )


namespace gb {
	namespace str {

static const char CSTR_ZERO[]    = "0";
static const char CSTR_ONE[]     = "1";
static const char CSTR_TWO[]     = "2";
 
#ifdef GB_ALLOW_BOOST_LIBRARY

template <typename T>
/** \brief Каст из строкового представления в другое */
bool strTo(KS_OUT T& outVal,  const std::string& s)
{
	if( !s.length() ) return false;
	try { outVal = boost::lexical_cast<T>(s); }
	catch( boost::bad_lexical_cast &) {  return false; 	}	return true;
}


template<typename T>
/** \brief Каст из строкового вектора vSrc в тип T и положить результат кастования в vOut
Если при кастокании ошибка, то выполняется выход с возвратом false. Если каст всех значений
успешен вернёт true  */
bool strVectorTo(KS_OUT std::vector<T>& vOut,  const std::vector<std::string>& vSrc)
{

	for(size_t c=0; c<vSrc.size(); c++)
	{
		T val;

		try
		{
			const std::string& src = vSrc[c];
			val  = boost::lexical_cast<T>( src );

		}
		catch( boost::bad_lexical_cast &)
		{
			return false;
		}

		vOut.push_back(val);

	} // for


	return true;
}

#endif // #ifdef GB_ALLOW_BOOST_LIBRARY


/** \brief Заполнение вектора по строке делёной символом конца строки  \n */
void splitLines(KS_OUT std::vector<std::string>& vOut, const std::string& s) ;

/** \brief сделать все символы в верхнем регистре. Строка должна завершаться нулём */
void cstrToUpper(char* buf) ;

/** \brief сделать все символы в нижнем регистре. Строка должна завершаться нулём */
void cstrToLower(char* buf) ;

/** \brief  Выполняет перевод буквеных символов в верхний(если bUpReg=true) или нижний(если bUpReg=false)
строки в NULL-терминированом буфере buff. <BR> Русские буквы переводятся в соответствии  с кодировкой cr1251
\param buff - [in] Исходный буфер подлежащий конвертации
\param bUpReg - [in]  Установить true если требуется перевод в верхний регистр или false для нижнего   */
void changeCase1251(char* buff, bool bUpReg);

/** \brief Поиск индексов вхождения символа chToBeSearch в строке src
с позиции  nStartIndex */
//==============================================
bool searchCharPos(KS_OUT std::vector<int32_t>& vPosOut, const std::string& src,
	KS_IN char chToBeSearch, KS_IN int32_t nStartIndex);


/** \brief Печать информации о строке на консоль. */
void printStrInfo(const std::string& s);

// void StrUt_BoostMakeLowerCase(std::string& s);
// void StrUt_BoostMakeUpperCase(std::string& s);

void replaceChar(std::string& s, const char chSymb, const char chNewSymb);

// void StrUt_BoostEraseAll(std::string& s, const std::string& s_erased);

bool loadStrFromFileA (KS_OUT std::string& s,  const char* fname);
bool saveStrToFileA   (KS_IN  std::string& s,  const char* fname);

bool loadStrFromFileW (KS_OUT std::string& s,  const wchar_t* fname);
bool saveStrToFileW   (KS_IN std::string& s,   const wchar_t* fname);

// void StrUt_Boost_replace_first_copy(std::string& s, const std::string& s_tobe_relp, const std::string& snew);
// void StrUt_Boost_replace_last_copy(std::string& s, const std::string& s_tobe_relp, const std::string& snew);

#pragma message ("KS777 ПОПРАВИТЬ"  __FILE__)
/** \brief Сравнение буферов без учёта регистра   НЕ ПРОВЕРЯЛАСЬ !!! */
bool iCompareCstr(const char* src1, const char* src2, uint32_t nMax );

/** \brief  удалить из текста  все C++ комментарии, Если  chRepl != 0,<br>
то закомментированый текст будет заменён этим символом	 <br>
(табы, пробелы и переносы строк не меняются)  */
void preprocessCppComments(KS_OUT std::string& sDest, const std::string& sSrc, KS_IN_OPTIONAL char chRepl=0 );

/** \brief  удалить из текста  все C++ комментарии.  */
void preprocessCppComments(KS_INOUT std::string& s, KS_IN_OPTIONAL char chRepl=0);



/** \brief Поиск индекса вхождения   символа. Минус один если не найден */
int32_t findChar(const std::string& s, const char symb, const int32_t nStartPos);

/** \brief Поиск подстроки между символами <br>
nPosition - с какой позиции и в нём же и результат индекса (позиция завершающего символа)  */
bool findSubstringBetween( 
		KS_OUT std::string& sResult, const std::string& s,
		const char chBegin,  
		const char chEnd,
		KS_INOUT int32_t& nPosition );

/** \brief Разрезать строку по указаному символу chDiv <br>
bClearResVecBefore - очистить или нет результирующий вектор vResult перед операцией   */
void ksSplit(KS_OUT std::vector<std::string>& vResult, const std::string& src,
	const char chDiv,    bool bClearResVecBefore=true );


#if GB_ALLOW_BOOST_LIBRARY
/** \brief Разрезать строку по токенам sTokens */
void splitTokens( KS_OUT std::vector<std::string>& vResult,
	const std::string& src, const std::string& sTokens );
#endif

/** \brief Разрезать строку по кол-ву указаному в pOffsets и  nOffsLen */
void sliceByOffsets(KS_OUT std::vector<std::string>& vResult, const std::string& src,
	const uint32_t* pOffsets, const int32_t nOffsLen) ;

/** \brief Разрезать строку src между индексами nStartPos && nStopPos
по токену  chToken   */
bool sliceBetweenIndices(KS_OUT std::vector<std::string>& vOut,
	const std::string& src,
	KS_IN char  chToken,
	KS_IN int32_t nStartPos, KS_IN int32_t nStopPos);


/** \brief Проверка на соответствие символа chr любому из szAny  */
bool isAnyOf(const char chr, const std::string& sAny) ;

/** \brief Выполнить поиск в строке src любого символа содержащегося  в sAny
с позиции posit . Если найден то вернёт true и в posit индекс вхождения  */
bool findAnyOf(const std::string& src, KS_INOUT int32_t& posit, const std::string& sAny ) ;

/** \brief Выполнить поиск в строке src с позиции posit поиск
первого символа в диапазоне chBegin ... chEnd  (включительно) .
Если найден то вернёт true и в posit индекс вхождения */
bool findAnyOfBetween(const std::string& src, KS_INOUT int32_t& posit, KS_IN char chBegin, KS_IN char chEnd);



/** \brief  Замена любого символа sAny   в строке src
на новый символ chNewSymb или удаление если chNewSymb == ноль. Результат в sOut  */
void replaceAnyChar(KS_OUT std::string& sOut, const std::string &src, const std::string& sAny, const char chNewSymb);
void replaceAnyChar(KS_INOUT std::string &s, const std::string& sAny, const char chNewSymb) ;


 

/** \brief Проверка строчки на открывающий xml/html таг    */
bool check_OpenXmlTag(KS_OUT std::string& sOutTag, 
	const std::string& src);
	
/** \brief Проверка строчки на открывающий xml/html таг по индексу     */
bool check_OpenXmlTag_pos(KS_OUT std::string& sOutTag, 
	const std::string& src,
	KS_INOUT int32_t& posit);

/** \brief Проверка строчки на закрывающий xml/html таг     */
bool check_CloseXmlTag(KS_OUT std::string& sOutTag,
	const std::string& src);

/** \brief Проверка строчки на закрывающий xml/html таг  по индексу    */
bool check_CloseXmlTag_pos(KS_OUT std::string& sOutTag,
	const std::string& src,
	KS_INOUT int32_t& posit);
	
	
 

/** \brief Удаление символов начиная с "//" (с++ однострочный комментарий) */
void skipCppOnelineComment(KS_OUT std::string& dest,
	KS_IN std::string& src );

/** \brief Удаление символов начиная с "//" (с++ однострочный комментарий) */
void skipCppOnelineComment(KS_INOUT std::string& s);


void intArrayToStr(KS_OUT std::string& sOut,
	const int32_t* pArray,  
	const int32_t nArrayLen,
	const char* szBegin, 
	const char* szEnd,
	const char* szSeparator );


void intArrayToStr(KS_OUT std::string& sOut,
	const std::vector<int32_t>& vArray,
	const char* szBegin, 
	const char* szEnd,
	const char* szSeparator );


bool intArrayFromStr(
	KS_OUT int32_t* pBufOut, 
	KS_IN int32_t nBufLen,
	KS_IN std::string& src, 
	KS_IN char chBegin, 
	KS_IN char chEnd,
	KS_IN char chSeparator, 
	KS_OUT_OPTIONAL int32_t* pOutNumReaded = NULL  );


bool intArrayFromStr(
	KS_OUT std::vector<int32_t>& vOut, 
	KS_IN std::string& src,
	KS_IN char chBegin, 
	KS_IN char chEnd, 
	KS_IN char chSeparator );


/** \brief  найти следующий символ не равный символам sSkipAnySymbols
в строке src со стартовой позиции nStartPosit. Если найден вернёт true
и в nOutFoundPosit позиция найденого символа */
bool findNextSkipAny(KS_OUT int32_t& nOutFoundPosit, KS_IN std::string& src,
	KS_IN int32_t nStartPosit,
	KS_IN std::string& sSkipAnySymbols );


/** \brief Удаление всех символов sAny из строки src с начала и с конца ДО ТОГО как
встретится символ не входящий в sAny. Результат в sOut  .Если других символов
помимо sAny в строке нет вернёт false. */
bool removeAnyFromBeginAndEnd(KS_OUT std::string& sOut, KS_IN std::string& src, KS_IN std::string& sAny);

bool removeAnyFromBeginAndEnd( KS_INOUT std::string& s , KS_IN std::string& sAny) ;

/** \brief Аналог StrUt_RemoveAnyFromBeginAndEnd для вектора строк */
void removeAnyFromBeginAndEnd_Vec(KS_INOUT std::vector<std::string>& v,
	KS_IN std::string& sAny);


/** \brief Построение текстового массива в строку sOut*/
void strArrayToStr(KS_OUT std::string& sOut, ///< результат.
	KS_IN std::vector<std::string> vecStr, ///< строки массива.
	KS_IN char chBegin,  ///< начальный символ или ноль если не нужен.
	KS_IN char chEnd,    ///< конечный символ или ноль если не нужен.
	KS_IN char chSeparator, ///< разделитель пунктов массива.
	bool bAddSpace   ///< добавить или нет пробел.
	);


/** \brief  Обратная StrUt_WriteStringArrayToStr. Чтение строкового массива из src */
bool strArrayFromStr( KS_OUT std::vector<std::string>& vOut,///<
	KS_IN std::string& src,///<
	KS_IN char chBegin, ///< токен начальный символ
	KS_IN char chEnd, ///< токен конечный символ
	KS_IN char chSeparator, ///< токен разделитель
	KS_IN std::string& sRemoveBeginAndEndAny ///< для удалени начальных и конечных символов или пустая строка если нет
	);


/** \brief Разрезать строку src в вектор vOut по индексам в vIndexes.
В vIndexes должны быть корректные индексы (каждый должен  быть больше 
предидущего и меньше следующего. 
Каждый не должен превышать длину src  и не должен быть отрицательным) */
bool sliceStrByIndices(std::vector<std::string>& vOut,  
	const std::string& src, 
	const std::vector<uint32_t>& vIndexes );


/** \brief Удалить из vInp все пустые строки, а непустые поместить в vOut */
void copyStringsSkipEmpty(std::vector<std::string>& vOut, std::vector<std::string>& vInp);


/** \brief Корректировак строки (добавление слеша (\) перед кавычкой ) */
//bool StrUt_CorrectStrBySpecSymbols_Add(_out std::string& sOut, _in std::string& src);





//
//  inline functions
//


/** \brief Проверка является ли символ цифровым */
inline bool isDigit(char symb) {
	return ( (symb>='0') && (symb<='9') );
}

/** \brief Проверка является ли символ англоязычным символом в ВЕРХНЕМ регистре. */
inline bool isLatinLetterUpper(char symb) {
	if (  (symb>='A') && (symb<='Z') ) return true;
	return false;
}

/** \brief Проверка является ли символ англоязычным символом в НИЖНЕМ регистре. */
inline bool isLatinLetterLower(char symb) {
	if (  (symb>='a') && (symb<='z') ) return true;
	return false;
}

/** \brief Проверка является ли символ англоязычным символом */
inline bool isLatinLetter(char symb) {
	return ( isLatinLetterUpper(symb) || isLatinLetterLower(symb) );
}

/** \brief Является ли символ математическим */
inline bool isMathOperator(char symb) {
	return ( (symb == '+') || (symb == '-') || (symb == '*') || (symb == '/')  );
}

/** \brief Присоединяет символ к строке. */
inline void appendChar(char* buf, const char s) {
	int32_t iblen = (int32_t)strlen(buf);
	*(buf + iblen) = s;
}

/** \brief Поиск символа новой строки . <br>
 \param
 src - указывает на первый символ в буфере.  
 pos - текущая позиция. */
bool findNextLinePos(const char* src, int32_t& pos) ;



 

/** \brief  make string:  "<tag>" */
inline std::string StrUt_MakeOpenXmlTag(const std::string& sTag) {
	std::string  res  = "<";
	res += sTag;
	res += ">";
	return res;
}

/** \brief  make string:  "</tag>" */
inline std::string StrUt_MakeCloseXmlTag(const std::string& sTag) {
	std::string  res  = "</";
	res += sTag;
	res += ">";
	return res;
}

inline bool StrUt_CheckSymbolMayBeOpen(KS_IN char symb) {
	if( symb == '(' ) return true;
	if( symb == '{' ) return true;
	if( symb == '[' ) return true;
	if( symb == '<' ) return true;

	return false;
}

inline bool StrUt_CheckSymbolMayBeClose(KS_IN char symb) {
	if( symb == ')' ) return true;
	if( symb == '}' ) return true;
	if( symb == ']' ) return true;
	if( symb == '>' ) return true;

	return false;
}

inline bool StrUt_SymbMayBeSeparator(KS_IN char symb) {
	if( symb == ',' ) return true;
	if( symb == ';' ) return true;

	return false;
}
 




/** \brief Класс от std::string  с расширеной функциональностью  */
class KsString : public std::string {
public:
	KsString() {}
	KsString(const char* s) {  assign(s); }
	KsString(const std::string& s) {  assign(s.c_str() ); }


	void operator = (const char* s) {
		assign(s);
	}
	void operator += (const char* s) {
		append(s);
	}

	void operator += (float f) {
		int32_t pos=0;
		static char ss[12]; ss[0]=0;
		pos += sprintf(ss+pos, "%f", f);
		*this += ss;
	}

	void operator += (int32_t i) {
		int32_t pos=0;
		static char ss[12]; ss[0]=0;
		pos += sprintf(ss+pos, "%i", i);
		*this += ss;
	}

	void operator += (bool b) {
		int32_t pos=0;
		static char ss[12]; ss[0]=0;
		if(b) pos+= sprintf(ss+pos, "true");
		else  pos+= sprintf(ss+pos, "false");
		*this += ss;
	}

	void operator += (char _ch) {
		push_back(_ch);
	}

	/** \brief Добавить символ конца строки.  */
	void appendLF() { append("\n"); }

	static char toUpperCh(char _ch) {
		return std::toupper(_ch);
	}

	static char toLowerCh(char _ch) {
		return std::tolower(_ch);
	}

	/** \brief Печать на консоль. */
	void print(bool bEndl = true) const {
		printf( c_str() );
		if(bEndl) printf("\n");
	}

	/** \brief Печать информации о строке на консоль. */
	void printStrInfo() const {
		gb::str::printStrInfo( *this );
	}

	/** \brief  . */
	void toLower();

	/** \brief  . */
	void toUpper();

	/** \brief  . */
	void  eraseChar( const char symb );

	/** \brief  . */
	void replaceChar( const char symb, const char new_symb ) ;



	/** \brief Сброс строки в файл. */
	// TODO: Не компилится
	// 	bool save_string_to_file_a(const char* fname) const {
	// 		 StrUt_SaveStrToFileA(*this, fname );
	// 	}

	/** \brief Загрузка строки из файла . */
	bool loadStrFromFileA(const char* fname)  {
		return gb::str::loadStrFromFileA(*this, fname );
	}



	/** \brief Обратный вызов для поиска. */
	typedef bool (* found_func_t )( void* pUserParam, const int32_t _at, int32_t nCountFound);

	/** \brief Поиск с обратным вызовом . */
	bool findWithCallback(const char* srch, found_func_t func, void* pUserParam ) const {
		bool res = false;
		const int32_t nSrcLen = (int32_t)length();
		if(nSrcLen==0) return false;

		const int32_t nsrchLen = (int32_t)strlen(srch);
		if(nsrchLen==0) return false;

		int32_t nCountFound =0;
		for(int32_t c=0; c< nSrcLen; c++) {
			int32_t numSuss =0;
			if( compareChars( c_str() + c, srch, nsrchLen , numSuss   )  ) {
				nCountFound++;
				if( func(pUserParam, c, nCountFound)==false ) {
					return true;
				}
			}

			c+= numSuss;
		}

		return true;
	}

	static bool compareChars(const char* a1, const char* a2, const int32_t num, int32_t& numSuss) {
		for(int32_t c=0; c< num; c++) {
			if(  *(a1+c) != *(a2+c)  )
				return false;
			numSuss++;
		}
		return true;
	}


	///////////////////////////////
	//	BOOST EXCENTION
	///////////////////////////////


	//void boost_to_upper() {  StrUt_BoostMakeUpperCase(*this);   }
	//void boost_to_lower() {	 StrUt_BoostMakeLowerCase(*this);  	}

	// 	void boost_replace_first_copy(const std::string& s_tobe_relp, const std::string& snew) {
	// 	    StrUt_Boost_replace_first_copy(*this, s_tobe_relp, snew );
	// 	}
	// 
	// 	void boost_replace_last_copy(const std::string& s_tobe_relp, const std::string& snew) {
	// 	    StrUt_Boost_replace_last_copy(*this, s_tobe_relp, snew );
	// 	}

	// 	void  boost_trim_before() {
	// 	 	  boost::trim(*this);
	// 	}

	// 	void boost_erase_all( const std::string& s_erased ) {
	// 		StrUt_BoostEraseAll( *this,  s_erased );
	// 	}



};
// end class



/** \brief Класс от  std::vector для Str с расширеной функциональностью . */
class KsStringVector : public std::vector< gb::str::KsString > {   // std::string> {
public:
	KsStringVector() {}

	/** \brief Печать полного текста. */
	void print(bool bInline=false) const {
		if( empty() ) return  ;
		for(size_t c=0; c<size(); c++) {
			const std::string&  s = at(c);
			printf("%s", s.c_str() );
			if(!bInline) {
				printf("\n");
			}
		}
	}

	/** \brief Добавить новую строку. */
	size_t appendStr(const std::string& s) {
		std::string ls = s;
		push_back(ls);
		return size();
	}

	/** \brief Добавить новую строку. */
	size_t appendStr(const char* s) {
		std::string ls = s;
		push_back(ls);
		return size();
	}

	/** \brief Добавить новую строку. */
	size_t appendStr(const KsString & s ) {
		push_back( s);
		return size();
	}

	/** \brief Подсчёт и возвврат кол-ва всех символов . */
	uint32_t countTotalLength() const;
	
	/** \brief Сбрасывает полный текст в файл. */
	bool saveToFileA(const char* fname, bool bEndLineAfterItem=true) const ;
	
	/** \brief Загружает новый текст из файла. Каждая строка-новый итем вектора. */
	bool loadFromFileA(const char* fname, bool bRemoveEndLineOnEnd=true);
};
// end class


	} // namespace str
} // namespace gb

#pragma warning( pop )
