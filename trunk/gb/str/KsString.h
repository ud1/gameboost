/** \file KsString.h
 * \brief Класс на основе STL и BOOST
 * \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
 * \author Reviewer/imported by: kvakvs (kvakvs@yandex.ru)
 
 \todo привести к правилам кода
 \todo сделать функции с декларатором импорта/экспорта
 
 */
 
#pragma once

#ifndef __GB_STR_H__
#error Не включайте этот файл отдельно. Включайте String.h
#endif

#pragma warning( push )
#pragma warning( disable : 4996 )


namespace gb {


	namespace str {


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


	inline operator std::string& () { return *this; }
	inline operator const std::string& () const { return *this; }



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
		gb::str::printStrInfo ( *this );
	}

	/** \brief  Перевести в нижний регистр. */
	void toLower();

	/** \brief  Перевести в верхний регистр. */
	void toUpper();

	/** \brief  стереть символ symp из строки. */
	void  eraseChar( const char symb );

	/** \brief  Заменить символ symb новым символом new_symb. */
	void replaceChar( const char symb, const char new_symb ) ;



//#ifdef WIN32
	/** \brief Сброс строки в файл. */
	 	bool save_string_to_file_a(const char* fname) const 
		{
	 		 saveStrToFileA(*this, fname );
	 	}
//#endif

	/** \brief Загрузка строки из файла . */
	bool loadStrFromFileA(const char* fname)  
	{
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
