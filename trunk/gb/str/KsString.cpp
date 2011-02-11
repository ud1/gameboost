/* \file KsStringUtils.h
* \brief Строки и сопутствующие типы.
* Класс на основе STL и BOOST
* \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
*/

#include "pch.h"

#include <gb/str/KsString.h>
#include <gb/str/KsUtils.h>

#if GB_ALLOW_BOOST_LIBRARY
	#include <boost/algorithm/string.hpp>
	#include <boost/tokenizer.hpp>
	#include <boost/lexical_cast.hpp>
#endif // GB_ALLOW_BOOST_LIBRARY

#include <stdlib.h>

#include <assert.h>

#pragma warning( push )
#pragma warning( disable : 4996 )


namespace gb {
	namespace str {


void splitLines(
	KS_OUT std::vector<std::string>& vOut, 
	const std::string& s) 
{
	std::string temp;
	if(s.length() == 0) return ;

	for(int c=0; c<(int)s.length(); c++) {
		char ch = s[c];
		if(ch == '\n') {
			if( temp.length() ) {
				vOut.push_back(temp);
				temp = "";
			}
			continue;
		}
		temp = temp + ch;
	}

	if( temp.length() ) {
		vOut.push_back(temp);
		temp = "";
	}


}

//======================================================
void cstrToUpper(char* buf) {
	int c=0;
	while(1)
	{
		if(  *(buf + c) == 0 ) return ;

		*(buf + c) = toupper( *(buf + c) );

		c++;
	}
}

//======================================================
void cstrToLower(char* buf) {
	int c=0;
	while(1)
	{
		if(  *(buf + c) == 0 ) return ;

		*(buf + c) = tolower( *(buf + c) );

		c++;
	}

}

//======================================================
void printStrInfo(const std::string& s) {

	printf("\n--------\n");
	printf("sizeof= %u\n",  sizeof( s ) );
	printf("lenght= %u\n", s.length() );
	printf("capacity= %u\n", s.capacity() );
	printf("max_size= %u\n", s.max_size() );
	printf("--------\n");

}

//============================================
void StrUt_BoostMakeLowerCase(std::string& s) {

	boost::to_lower(s); 
}

//======================================================
void StrUt_BoostMakeUpperCase(std::string& s) {

	boost::to_upper(s); 
}

//============================================
void replaceChar(std::string& s, const char chSymb, const char shNewSymb) {

	const size_t SRC_LEN = s.length();

	if( 0 == SRC_LEN  ) return;

	for(size_t c=0; c<SRC_LEN; c++) {
		if( s[c] == chSymb  )
		{
			s[c] = shNewSymb;
			continue;
		}

	}

}

//=====================================================
// void StrUt_BoostEraseAll(std::string& s, const std::string& s_erased) {
// 
// 	boost::erase_all(  s,  s_erased ); 
// 
// }

//==============================================
bool loadStrFromFileA(std::string& s,   const char* fname)  {
	s = "";
	FILE* file = fopen(fname, "r");
	if(!file) return false;

	static char ss[2048];
	ss[0]=0;
	while( fgets( ss, 1024,  file ) > 0 ) {
		s.append(ss);
		ss[0] = 0;
	}

	if( ss[0] ) {
		s.append(ss);
	}

	fclose(file);
	return true;
}

//======================================================
bool saveStrToFileA(KS_IN std::string& s,  const char* fname)  
{
	FILE* file = fopen(fname, "w");
	if(!file) return false;
	size_t swrtd = fputs( s.c_str(), file );
	fflush(file);
	fclose(file);
	return true;
}

//===================================================================
bool loadStrFromFileW(KS_OUT std::string& s, const wchar_t* fname)
{
	s = "";
	FILE* file = _wfopen(fname, L"r");
	if(!file) return false;

	static char ss[2048];
	ss[0]=0;
	while( fgets( ss, 1024,  file ) > 0 ) {
		s.append(ss);
		ss[0] = 0;
	}

	if( ss[0] ) {
		s.append(ss);
	}

	fclose(file);
	return true;	
}

//==========================================================
bool saveStrToFileW(KS_IN std::string& s, const wchar_t* fname)
{
	FILE* file = _wfopen(fname, L"w");
	if(!file) return false;
	size_t swrtd = fputs( s.c_str(), file );
	fflush(file);
	fclose(file);
	return true;	

}


#if GB_ALLOW_BOOST_LIBRARY
void StrUt_Boost_replace_first_copy(std::string& s, const std::string& s_tobe_relp, const std::string& snew) {
	s = boost::ireplace_first_copy( s, s_tobe_relp, snew );
}

//============================================================
void StrUt_Boost_replace_last_copy(std::string& s, const std::string& s_tobe_relp, const std::string& snew) {
	s = boost::ireplace_last_copy( s, s_tobe_relp, snew );
}
#endif

//=============================================================
bool iCompareCstr(const char* src1, 
	const char* src2 ) 
{
	int c=0;
	while(1) {
		char ch1 = tolower( *(src1 + c) );
		char ch2 = tolower( *(src2 + c) );

		if(ch1 != ch2) {
			return false;
		}

		if(  (ch1 == 0) || (ch2 == 0) ) {
			return true;
		}

		c++;
	}

	return false;
}

//======================================================
void preprocessCppComments(KS_INOUT std::string& s,
	KS_IN_OPTIONAL char chRepl) 
{
	std::string temp = s;
	preprocessCppComments(temp, s, chRepl );
	s = temp;
}

//=======================================================
void preprocessCppComments(KS_OUT std::string& sDest, 
	const std::string& sSrc,
	KS_IN_OPTIONAL char chRepl) 
{
	sDest = "";
	const int SRCLEN = (int)sSrc.length();

	bool bNowOneLineComment = false; // in one line comment
	bool bNowMultiLineComment = false; // in multi line comment

	for(int c=0; c<SRCLEN; c++) {
		char ch = sSrc[c];

		if( c == SRCLEN-1) {
			// last

			char tmp = sSrc[c+1];
			int _end =0;
		}


		if(bNowMultiLineComment) {
			if( (ch == '*') && ( sSrc[c+1] == '/' ) )
			{
				// multi comment end
				bNowMultiLineComment=false;
				c++;

				if(chRepl)
				{
					sDest += chRepl;
					sDest += chRepl;
				}

				continue;
			}

		}

		if(bNowOneLineComment) {
			if( ch == '\n' ) {
				// end one line comment
				bNowOneLineComment=false;

				if(chRepl)
				{
					sDest +=  '\n';
				}


				continue;

			}	

		}


		if(ch == '/') {
			if( sSrc[c+1] == '/' ) {
				// begin one line comment
				bNowOneLineComment=true;
				c++;

				if(chRepl)
				{
					sDest +=  chRepl;
					sDest +=  chRepl;
				}


				continue;

			}

			if( sSrc[c+1] == '*' ) {
				bNowMultiLineComment=true;
				c++;

				if(chRepl)
				{
					sDest +=  chRepl;
					sDest +=  chRepl;
				}



				continue;			
			}


		}// if(ch == '/')


		if ( bNowOneLineComment || bNowMultiLineComment )
		{

			if(chRepl)
			{
				if(ch == '\t') { sDest += '\t'; }
				else 
					if(ch == '\n') { sDest += '\n'; } 
					else   if(ch == ' ')  { sDest += ' '; } 

					else
						sDest +=  chRepl;

			}



			continue;  
		}

		sDest += ch;



	} // for


}

//====================================================
int findChar(const std::string& s,
	const char symb,
	const int nStartPos) 
{
	const int SRCLEN = (int)s.length();
	if(SRCLEN == 0) return -1;

	if(nStartPos > SRCLEN-1) return -1;

	for(int c=nStartPos; c<SRCLEN; c++) {
		char ch = s[c];
		if(ch == symb)
		{
			return c;
		}


	}

	return  -1;
}

//================================================
bool findSubstringBetween( KS_OUT std::string& sResult , 
	const std::string& s, 
	const char chBegin, 
	const char chEnd, 
	KS_INOUT int& nPosition ) 
{
	sResult = "";
	const int SRCLEN = (int )s.length();
	if(SRCLEN == 0) return false;

	int nFoundBegin = -1;// pos where begin 
	int nFoundEnd = -1; // pos where end

	for(int c=nPosition; c<SRCLEN; c++) {
		char curr = s[c];
		if(curr == chBegin)
		{
			if(nFoundBegin > 0) {
				nPosition = c;
				return false;
			}
			nFoundBegin=c;
			continue;			 
		}

		if(curr == chEnd)
		{
			if( nFoundEnd > 0 ) {
				nPosition = c;
				return false;
			}

			nFoundEnd	= c;

			if( (nFoundBegin>0) && (nFoundEnd>0) ) {
				// search OK !
				nPosition = c;
				return true;

			}

		}


		if( (nFoundBegin >= 0) && (nFoundEnd <0)  ) {
			sResult += curr; 

		}



	}// for


	if( (nFoundBegin<0) || (nFoundEnd<0) ) {
		return false;
	}


	return  true;	
}

//====================================================
void ksSplit(KS_OUT std::vector<std::string>& vResult, 
	const std::string& src, const char chDiv, 
	bool bClearResVecBefore ) 
{

	if(bClearResVecBefore) {
		vResult.clear();
	}

	const int SRCLEN = (int)src.length();
	if(SRCLEN == 0) return;

	std::string temp = "";

	for(int c=0; c<SRCLEN; c++)	 {
		char curr = src[c];

		if(curr == chDiv) {

			if(temp.length() ) {
				vResult.push_back(temp);	
				temp = "";	
			}

			continue;
		}

		temp += curr;

	} // for

	if(temp.length() ) {
		vResult.push_back(temp);	

	}

}

//=======================================================
#if GB_ALLOW_BOOST_LIBRARY
void splitTokens( KS_OUT std::vector<std::string>& vResult,
	const std::string& src, 
	const std::string& sTokens)
{

	typedef boost::tokenizer<boost::char_separator<char> > 	tokenizer;
	boost::char_separator<char> sep( sTokens.c_str() );
	tokenizer tokens(src, sep);

	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
	{
		vResult.push_back(*tok_iter);
	}

}
#endif

//=======================================================
void sliceByOffsets(
	KS_OUT std::vector<std::string>& vResult,
	const std::string& src, 
	const unsigned int* pOffsets, 
	const int nOffsLen ) 
{
	using namespace std;
	using namespace boost;

	offset_separator f(pOffsets, pOffsets +  nOffsLen );
	tokenizer<offset_separator> tok( src, f );
	for(tokenizer<offset_separator>::iterator beg=tok.begin(); beg!=tok.end();++beg){
		vResult.push_back( *beg ); 
	}


}

//===================================================
bool isAnyOf(const char chr, 
	const std::string& sAny) 
{
	const int SANYLEN = (int)sAny.length();
	if( SANYLEN == 0 ) return false;

	for(int c=0; c<SANYLEN; c++) {
		const char curr =  sAny[c];
		if( chr == curr) return true;

	}

	return false;
}

//============================================
bool findAnyOf(const std::string& src,
	KS_INOUT int& posit,
	const std::string& sAny ) 
{
	if(sAny.length() == 0) return false;
	const int SRCLEN = (int)src.length();

	for(int c = posit; c<SRCLEN; c++) {
		const char curr = src[c];
		if(curr == 0) return false;

		for(int c_any=0; c_any<(int)sAny.length(); c_any++)
		{
			if( sAny[c_any] == curr )
			{
				posit = c;
				return true;
			}

		}

	}	

	return false;
}

//============================================
bool findAnyOfBetween(const std::string& src,
	KS_INOUT int& posit,
	KS_IN char chBegin,
	KS_IN char chEnd) 
{

	while(1)
	{
		const char curr = src[posit];


		if( (curr >= chBegin) && (curr <= chEnd)  )
		{

			return true;
		}

		if(curr == 0) return false;

		posit++;
	}


	return false;	
}

//=============================================
void replaceAnyChar(KS_OUT std::string& sOut,
	const std::string &src, 
	const std::string& sAny,
	const char chNewSymb) {
		sOut = "";
		if( sAny.length() == 0 )	 return ;

		const int NSRCLEN = (int)src.length();
		if(NSRCLEN == 0) return ;

		if(sAny.length() == 0) return;

		const int NANYLEN = (int)sAny.length(); 

		bool bAnyFound = false; ///< found  or not
		for(int c=0; c<NSRCLEN; c++) {
			bAnyFound = false;

			for(int c_sAny=0; c_sAny<NANYLEN; c_sAny++ )
			{
				if( src[c] == sAny[c_sAny] ) 
				{
					bAnyFound=true;
					break;
				}
				else
				{

				}

			} // for c_any


			if(bAnyFound )
			{
				if(chNewSymb) {
					sOut += chNewSymb;
				}
				else 
				{    

				}


			}
			else
			{
				sOut += src[c];

			}

			bAnyFound = false;

		} // for c

}

//=========================================================
void replaceAnyChar(KS_INOUT std::string &s, 
	const std::string& sAny, const char chNewSymb) {
		std::string temp = s;
		s = "";
		replaceAnyChar( s , temp, sAny,  chNewSymb);

}

//=========================================================

// 2010.12.20

//=========================================================
#if 0
bool StrUt_Check_OpenXmlTag(KS_OUT std::string& sOutTag, 
	const std::string& src ) {
		sOutTag = "";
		if( src.length  () < 3 ) return false;
		if( src[0] != '<' ) return false;

		if(  src[src.length()-1] != '>' ) return false;

		for(int c=1; c<(int)src.length()-1; c++) {
			if( StrUt_CheckSymbolEngLiteral(src[c]) || src[c] == '_'  ) {
				sOutTag += src[c];
			}
			else
			{
				return false;
			}

		} 


		return true;
}

//===================================================
bool StrUt_Check_OpenXmlTag_pos(KS_OUT std::string& sOutTag, 
	const std::string& src, KS_INOUT int& posit )
{
	sOutTag = "";
	if( src.length()-posit < 3 ) return false;
	if( src[posit] != '<' ) return false;

	posit+= 1;

	while( posit <= (int)src.length() ) {
		if( src[posit] == '>' )
		{
			if(sOutTag.length() )
			{
				return true;
			}
			else
			{
				return  false;
			}

		}

		if( StrUt_CheckSymbolEngLiteral(src[posit]) || src[posit] == '_'  ) {
			sOutTag += src[posit];
		}
		else
		{
			return false;
		}

		posit++;
	} 


	if(sOutTag.length() )
	{
		return true;
	}

	return false;
}

//=====================================================
bool StrUt_Check_CloseXmlTag(KS_OUT std::string& sOutTag, 
	const std::string& src ) {
		sOutTag = "";
		if( src.length() < 4 ) return false;
		if( src[0] != '<' ) return false;
		if( src[1] != '/' ) return false; 

		if(  src[src.length()-1] != '>' ) return false;

		for(int c=2; c<(int)src.length()-1; c++) {
			if(StrUt_CheckSymbolEngLiteral(src[c]) || src[c] == '_'  ) {
				sOutTag += src[c];
			}
			else
			{
				return false;
			}

		} 


		return true;
}

//===========================================================
bool StrUt_Check_CloseXmlTag_pos(KS_OUT std::string& sOutTag, 
	const std::string& src, KS_INOUT int& posit )
{
	sOutTag = "";
	if( src.length()-posit < 3 ) return false;
	if( src[posit] != '<' ) return false;
	if( src[posit+1] != '/' ) return false;

	posit+= 2;

	while( posit <= (int)src.length() ) {
		if( src[posit] == '>' )
		{
			if(sOutTag.length() )
			{
				return true;
			}
			else
			{
				return  false;
			}

		}

		if( StrUt_CheckSymbolEngLiteral(src[posit]) || src[posit] == '_'  ) {
			sOutTag += src[posit];
		}
		else
		{
			return false;
		}

		posit++;
	} 


	if(sOutTag.length() )
	{
		return true;
	}

	return false;
}
#endif //0

//=========================================================================
void skipCppOnelineComment(KS_OUT std::string& dest, KS_IN std::string& src ) 
{
	dest = "";
	for(size_t c=0; c<src.length(); c++)
	{
		if( (src[c] == '/' ) && ( src[c+1] == '/' ) )   {
			// comment found !
			return;
		}

		dest += src[c];
	}


}

//===========================================
void skipCppOnelineComment(KS_INOUT std::string& s)
{
	std::string temp = s;
	s = "";
	skipCppOnelineComment(  s ,  temp );


}



//=========================================================
//              2010.12.24
//=========================================================

void intArrayToStr(KS_OUT std::string& sOut, 
	const int* pArray,  const int nArrayLen,
	const char* szBegin, const char* szEnd, 
	const char* szSeparator )
{

	if(szBegin)
	{
		sOut += szBegin;
	}



	for(int c=0; c<nArrayLen; c++)
	{
		sOut += gb::util::Formater::intToCstr( *(pArray + c) );

		if(c != nArrayLen-1)
		{
			sOut +=  szSeparator;
		}

	}


	if(szEnd)
	{
		sOut += szEnd;
	}


}



//===========================================
bool intArrayFromStr(KS_OUT int* pBufOut, KS_IN int nBufLen, 
	KS_IN std::string& src, 
	KS_IN char chBegin, KS_IN char chEnd, 
	KS_IN char chSeparator, KS_OUT_OPTIONAL int* pOutNumReaded  )
{


	const int NSRCLEN = (int)src.length();
	if(NSRCLEN == 0) return false;

	bool bFoundBegin = false;
	bool bFoundEnd   = false;

	std::string sDigit;

	int numParsedValues = 0; 

	if(pOutNumReaded)
	{
		*pOutNumReaded = 0;
	}

	for(int c=0; c<NSRCLEN; c++)
	{
		char curr = src[c];
		// check tab .. empty ....
		if( (curr==' ') || (curr=='\t') || (curr=='\r') )
		{
			continue;
		}

		if( bFoundBegin && bFoundEnd )
		{
			if(pOutNumReaded) 
			{
				*pOutNumReaded = numParsedValues;
			} 

			return true;
		}


		if( !bFoundBegin ) {
			// scan begin token
			if(curr == chBegin) {
				bFoundBegin = true;
				continue;
			}
		}

		if(bFoundBegin ) 
		{
			// scan next end digit token
			for(int j=0; j<(j+c+NSRCLEN); j++)
			{
				curr = src[c + j];

				// check tab .. empty ....
				if( (curr==' ') || (curr=='\t') || (curr=='\r') )
				{
					continue;
				}


				if(curr == chEnd)
					bFoundEnd = true;

				if( (curr == chSeparator) || (curr == chEnd) )
				{
					// found separator !

					// cast
					int val = -1;
					try 
					{
						val=  boost::lexical_cast<int>(sDigit);
					}
					catch(boost::bad_lexical_cast &  )
					{
						// error 
						if(pOutNumReaded)
						{
							*pOutNumReaded = numParsedValues;
						}

						return false;
					}


					// cast ok !
					if(numParsedValues < nBufLen)
					{

						*( pBufOut + numParsedValues )  = val;
						numParsedValues++;
						sDigit = "";
						c += j;
						break;
					}
					else
					{
						// buffer is full . return
						if(pOutNumReaded)
						{
							*pOutNumReaded = numParsedValues;
						}
					}

				}// if(curr == chSeparator)

				sDigit += curr;

			}// for




		}// for




	} // for

	if(pOutNumReaded)
	{
		*pOutNumReaded = numParsedValues;
	}

	return true;

}

//===========================================
bool intArrayFromStr(KS_OUT std::vector<int>& vOut, KS_IN std::string& src, 
	KS_IN char chBegin, KS_IN char chEnd, KS_IN char chSeparator ) 
{

	const int NSRCLEN = (int)src.length();
	if(NSRCLEN == 0) return false;

	bool bFoundBegin = false;
	bool bFoundEnd   = false;

	std::string sDigit;

	for(int c=0; c<NSRCLEN; c++)
	{
		char curr = src[c];
		// check tab .. empty ....
		if( (curr==' ') || (curr=='\t') || (curr=='\r') )
		{
			continue;
		}

		if( bFoundBegin && bFoundEnd )
		{
			return true;
		}


		if( !bFoundBegin ) {
			// scan begin token
			if(curr == chBegin) {
				bFoundBegin = true;
				continue;
			}
		}

		if(bFoundBegin ) 
		{
			// scan next end digit token
			for(int j=0; j<(j+c+NSRCLEN); j++)
			{
				curr = src[c + j];

				// check tab .. empty ....
				if( (curr==' ') || (curr=='\t') || (curr=='\r') )
				{
					continue;
				}


				if(curr == chEnd)
					bFoundEnd = true;

				if( (curr == chSeparator) || (curr == chEnd) )
				{
					// found separator !

					// cast
					int val = -1;
					try 
					{
						val=  boost::lexical_cast<int>(sDigit);
					}
					catch(boost::bad_lexical_cast &  )
					{
						// error 
						return false;
					}

					// cast ok !
					vOut.push_back(val);
					sDigit = "";
					c += j;
					break;

				}// if(curr == chSeparator)

				sDigit += curr;

			}// for




		}// for




	} // for

	return true;
}


//==================================================
bool sliceBetweenIndices(KS_OUT std::vector<std::string>& vOut,
	const std::string& src, 
	KS_IN char  chToken, 
	KS_IN int nStartPos, KS_IN int nStopPos) 
{
	// check args
	if(nStartPos >= nStopPos)
		return false;

	// string values
	std::string sClump;
	sClump.resize( nStopPos - nStartPos + 1 );
	sClump = "";

	//  extract str
	for(int c = nStartPos; c<nStopPos; c++ )
	{
		sClump += src[c];
	}

	typedef boost::tokenizer<boost::char_separator<char> >  tokenizer;

	char szToken[2];
	szToken[0] = chToken;
	szToken[1] = 0;


	boost::char_separator<char> sep(  szToken  );
	tokenizer tokens(src, sep);

	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
	{
		vOut.push_back(*tok_iter);
	}

	return true;
}

//=================================================
bool findNextSkipAny(KS_OUT int& nOutFoundPosit, KS_IN std::string& src, 
	KS_IN int nStartPosit, 
	KS_IN std::string& sSkipAnySymbols )
{
	nOutFoundPosit =   -1;
	const int NSRCLEN = (int)src.length();

	if( (NSRCLEN - nStartPosit) <= 0  )
	{
		return false;

	}

	bool bFoundAny = false;

	for(int c=nStartPosit; c<NSRCLEN; c++)
	{
		char curr = src[c];

		// check terminated
		if(curr == 0)
		{
			return false;
		}

		bFoundAny = false;

		for(int j=0; j<(int)sSkipAnySymbols.length(); j++)
		{
			char chCmp = sSkipAnySymbols[j];

			if(chCmp == curr)
			{
				// continue search
				bFoundAny =  true;
				break;
			}



		} // for


		if(bFoundAny)
		{
			continue;
		}
		else
		{
			// found ok !
			nOutFoundPosit = c;
			return true;
		}


	} // for


	// not found

	return false;
}

//================================================
bool removeAnyFromBeginAndEnd(KS_OUT std::string& sOut,
	KS_IN std::string& src,
	KS_IN std::string& sAny)
{

	int nFoundPosFromBegin =  -1;
	int nFoundPosFromEnd   =  -1;

	// search begin pos
	for(int c=0; c<(int)src.length(); c++)
	{
		char curr = src[c];

		bool bFoundAny = false;
		for(int j=0; j<(int)sAny.length(); j++)
		{
			if( curr == sAny[j] )
			{
				bFoundAny = true;
				break;

			}


		}// for j


		if(!bFoundAny)
		{
			// found !
			nFoundPosFromBegin = c;
			break;
		}


	} // for





	// search end pos
	for(int c=(int)src.length()-1; c>=0; c--)
	{
		char curr = src[c];

		bool bFoundAny = false;
		for(int j=0; j<(int)sAny.length(); j++)
		{
			if( curr == sAny[j] )
			{
				bFoundAny = true;
				break;

			}


		}// for j


		if(!bFoundAny)
		{
			// found !
			nFoundPosFromEnd = c;
			break;
		}


	} // for


	// make result
	//

	// check not found
	if(  ( nFoundPosFromBegin < 0 ) && ( nFoundPosFromEnd   <  0) )
	{
		// not found
		return false;
	}

	// correct found pos
	if(nFoundPosFromBegin == -1)
	{
		nFoundPosFromBegin = 0;
	}

	if(nFoundPosFromEnd == -1)
	{
		nFoundPosFromEnd = (int)src.length()-1;
	}

	// make string
	for(int c= nFoundPosFromBegin; c<=nFoundPosFromEnd; c++)
	{
		sOut += src[c];

	}

	return true;
}

//=================================================
void removeAnyFromBeginAndEnd_Vec(
	KS_INOUT std::vector<std::string>& v,
	KS_IN std::string& sAny)
{

	std::string temp;
	for(int c=0; c<(int)v.size(); c++)
	{
		temp = "";
		removeAnyFromBeginAndEnd(temp, v[c], sAny );
		v[c] = temp;


	}

}

//============================================
void strArrayToStr(KS_OUT std::string& sOut,
	KS_IN std::vector<std::string> vecStr, 
	KS_IN char chBegin, KS_IN char chEnd,
	KS_IN char chSeparator, bool bAddSpace   )
{

	if(chBegin)
	{
		sOut += chBegin;
		if(bAddSpace) sOut += ' ';
	}


	for(int c=0; c<(int)vecStr.size(); c++)
	{
		sOut += vecStr[c];


		if(c != vecStr.size()-1)
		{
			sOut += chSeparator;
			if(bAddSpace) sOut += ' ';

		}


	} // for



	if(chEnd)
	{
		if(bAddSpace) sOut += ' ';
		sOut += chEnd;

	}


}

//======================================================
bool strArrayFromStr(
	KS_OUT std::vector<std::string>& vOut,
	KS_IN std::string& src,
	KS_IN char chBegin, 
	KS_IN char chEnd, 
	KS_IN char chSeparator, 
	KS_IN std::string& sRemoveBeginAndEndAny )
{

	std::string sArray;
	int nPos = 0;

	if(!findSubstringBetween(sArray, src, chBegin, chEnd, nPos ) )
	{

		return false;
	}


	ksSplit(vOut, sArray, chSeparator);
	removeAnyFromBeginAndEnd_Vec(vOut, sRemoveBeginAndEndAny );


	return true;
}

//==================================================
void changeCase1251(char* buff, bool bUpReg) {

	int c = 0;  
	unsigned char ch = 0;

	while(true) 
	{
		ch = *(buff + c);
		if (ch==0) break;

		if (bUpReg)
		{
			// english
			if ((ch >= 97) && (ch <= 122)) {  //  a  z  
				*(buff + c) = (   *(buff + c) - 32  );
				continue;
			}

			// russ
			if ((ch >= 224) && (ch <= 255)) {  //  пїЅ  пїЅ  
				*(buff + c) = (   *(buff + c) - 32  );
				continue;
			}
		}
		else
		{
			// english
			if ((ch >= 0x41) && (ch <= 0x5A)) {  //  A  Z  
				*(buff + c) = (   *(buff + c) + 32  );
				continue;
			}

			// russ
			if ((ch >= 192) && (ch <= 223)) {  //  пїЅ  пїЅ  
				*(buff + c) = (   *(buff + c) + 32  );
				continue;
			}

		}

		c++;	
	}


}


//=========================================================
bool searchCharPos(KS_OUT std::vector<int> vPosOut,
	const std::string& src,
	KS_IN char chToBeSearch, KS_IN int nStartIndex)
{
	vPosOut.clear();

	const int NSRCLEN = (int)src.length();
	if(nStartIndex >= NSRCLEN) return false;

	for(int c=nStartIndex; c<NSRCLEN; c++)
	{
		const char curr =  src[c];
		if( curr ==  chToBeSearch) {
			vPosOut.push_back( c );
		}


	}

	if(vPosOut.empty() ) return false;


	return true;
}



//=================================================
//bool StrUt_CorrectStrBySpecSymbols(_out std::string& sOut, _in std::string& src) 
//{
//	 sOut = "";
//    if(src.length() == 0)
//		  return true;
//
//	for(int c=0; c<src.length(); c++ )
//	{
//       char curr = src[c];
//	   if(curr == '\"')
//	   {
//         sOut  += '\\';
//
//	   }
//
//
//
//      // end check
//	  sOut += curr;
//
//	}
//
//
//   return true;
//}



//====================================================
bool sliceStrByIndices(std::vector<std::string>& vOut,  
	const std::string& src, 
	const std::vector<unsigned int>& vIndexes )
{

	/**********
	пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

	int _tmain(int argc, _TCHAR* argv[])
	{
	std::string src = "The simpler but less flexible way is to include glew.h and glew.c into your project. On Windows, you also";

	std::vector<unsigned int> vind;
	vind.push_back(0);
	vind.push_back(5);
	vind.push_back(11);
	vind.push_back(19);
	vind.push_back(33);


	std::vector<std::string> vres;
	bool bres = SLiceExx(vres, src, vind);



	return 0;
	}

	***********/




	// check valid vector indexes
	if(vIndexes.size() == 0) return false;


	for(int c=0; c<(int)vIndexes.size(); c++)
	{
		// ckeck bound
		if( vIndexes[c] >= src.length() )
		{
			// index error
			return false;
		}

		if(c==0) {
			// first
			continue;
		}

		if( c==vIndexes.size()-1 )
		{
			// last
			break;
		}

		if(  vIndexes[c] >= vIndexes[c+1] )   return false;
		if(  vIndexes[c] <= vIndexes[c-1] )   return false;




	}


	// slice
	vOut.clear();
	std::string str = "";
	for(int c=0; c<(int)vIndexes.size()-1; c++)
	{
		for(int j=vIndexes[c]; j<(int)vIndexes[c+1]; j++)
		{
			str += src[j];

		}

		//   puts("vOut.push_back(str);   \n");
		vOut.push_back(str);
		str = "";

	}




	// puts("End func \n");
	return true;	
}

//=========================================================
void copyStringsSkipEmpty(std::vector<std::string>& vOut, 
	std::vector<std::string>& vInp) 
{

	/***************
	пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ

	int _tmain(int argc, _TCHAR* argv[])
	{
	std::vector<std::string> vs;
	vs.push_back("hgfghgh");
	vs.push_back("");
	vs.push_back("gdfgdfg");
	vs.push_back("");
	vs.push_back("vcxxcv");

	std::vector<std::string> vout;

	copyStringsSkipEmpty(vout, vs);


	return 0;
	} 
	********************/



	vOut.clear();

	for(size_t c=0; c<vInp.size(); c++)
	{
		if( vInp.at(c).length() == 0 ) {
			continue;
		}

		vOut.push_back( vInp[c] );

	}

}


//======================================================




//
//======================================================
// KsString::
//======================================================

void KsString::make_lowercase() {
	const size_t SRC_LEN =  length();
	if( 0 == SRC_LEN  ) return;
	char symb;
	for(size_t c=0; c<SRC_LEN; c++) {
		symb = at(c);
		symb = toupper_ex(symb);
		at(c) = symb;
	}
}



void KsString::make_upercase() {
	const size_t SRC_LEN =  length();
	if( 0 == SRC_LEN  ) return;
	char symb;
	for(size_t c=0; c<SRC_LEN; c++) {
		symb = at(c);
		symb = tolower_ex(symb);
		at(c) = symb;
	}
}


void  KsString::remove_symbols( const char symb ) {
	static std::string ss;
	const size_t SRC_LEN = length();
	if( 0 == SRC_LEN  ) return;

	ss =   c_str();
	assign(""); //  s = "";

	for(size_t c=0; c<SRC_LEN; c++) {
		if( ss[c] == symb  ) 
			continue;
		*this +=  ss[c]  ;

	}

}


void  KsString::replace_symbols( const char symb, const char new_symb ) {
	const size_t SRC_LEN = length();
	if( 0 == SRC_LEN  ) return;

	for(size_t c=0; c<SRC_LEN; c++) {
		if( at(c) == symb  )
		{
			at(c) = new_symb;
		}
	}
}





//======================================================
// StringsVector::
//======================================================

unsigned int StringsVector::get_total_numsymbols() const {
	if( empty() )  return 0;
	unsigned int res =0;
	for(size_t c=0; c<size(); c++) {
		const std::string& scurr = at(c);
		res += (unsigned int)scurr.length();
	}
	return res;
}

//==========================================================
bool StringsVector::save_to_file_a(const char* fname, bool bEndLineAfterItem ) const {
	FILE* file = fopen(fname, "w");
	if(!file) return false;

	for(size_t c=0; c<size(); c++) {
		const std::string& scurr = at(c);
		size_t wrted = fputs( scurr.c_str(), file );
		if(bEndLineAfterItem) 
		{
			if( c != size()-1 ) {
				// not last
				wrted = fputs("\n", file );
			} 
		}
	}

	fflush(file);
	fclose(file);
	return true;
}


//==========================================================
bool StringsVector::load_from_file_a(const char* fname, bool bRemoveEndLineOnEnd ) {
	clear();
	FILE* file = fopen(fname, "r");
	if(!file) return false;

	// ????		//
	//	assert(false);

	static const int SS_LEN = 256;
	static char ss[SS_LEN];
	ss[0]=0;

	static std::string stemp = "";
	int rres = 1;
	while( 1 ) {
		ss[0]=0;
		const char* ccres = fgets(  ss, SS_LEN,  file );
		if((  ccres == NULL) && (ss[0]==0)   ) 
		{   // end
			break;
		}
		else
			if(ccres == (const char*)EOF)
			{
				break;
			}
			else
				if(ccres)
				{
					if(bRemoveEndLineOnEnd) 
					{
						const size_t sslen = strlen(ss);
						if( *(ss + sslen-1) == '\n'  )
						{
							*(ss + sslen-1) = 0;
						}
					}
					add(ss);
				}

	}


	fclose(file);
	return true;
}

//==========================================================
	} // namespace str
} // namespace gb

#pragma warning( pop )
