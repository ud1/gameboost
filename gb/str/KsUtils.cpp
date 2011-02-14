/*! \file  KsUtils.cpp
 * \brief –азнообразные классы , типы дл€ разных задач 
 * \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586
 * \author Reviewer/imported by: kvakvs (kvakvs@yandex.ru)
 */

#include "stdafx.h"
//#include "pch.h"


#include <gb/str/KsUtils.h>
//#include "ksut_inc_c.h"

#include <ostream>
#include <iostream>

#pragma warning (push)
#pragma warning (disable : 4996)
#pragma warning (disable : 4290)

namespace gb {
	namespace util {


//=========================================================
const char*  Formater::boolToCstr(bool b) {
	static char ss[8];
	if(b) { strcpy(ss, "true"); } else { strcpy(ss, "false"); }
	return ss;
}

const char*  Formater::boolToUppercaseCstr(bool b) {
	static char ss[8];
	if(b) { strcpy(ss, "TRUE"); } else { strcpy(ss, "FALSE"); }
	return ss;
}

//=========================================================
const char* Formater::floatToCstr(float f) {
	static char buff[32];
	int32_t cnt = sprintf(buff, "%f", f );
	buff[cnt ] = 0;
	return buff;
}

//=========================================================
const char* Formater::intToCstr(int32_t i) {
	static char buff[32];
	sprintf(buff, "%i", i );
	return buff;  
}

//=========================================================
const char* Formater::uintToCstr(uint32_t val) {
	static char ss[16];
	ss[0] = 0;
	sprintf(ss, "%u", val );
	return ss;	
}

//=========================================================
const char* Formater::intToHex(int32_t i) {
	static char buff[32];
	sprintf(buff, "%.8X", i );
	return buff;
}

//=========================================================
const char* Formater::intToCppHex(int32_t i) {
	static char dig[10];
	static char res[32];

	sprintf(dig, "%.8X", i );
	strcpy(res, "0x");
	strcat(res, dig);
	return res;
} 


//=========================================================
const char* Formater::pointerToCstr(const void* p) {
	static char buf[16]; 
	buf[0]=0;

#pragma  warning(push)
#pragma  warning(disable : 4311)
	DWORD dw = (DWORD)p;
#pragma  warning(pop)

	strcpy(buf, "0x");
	static char sdigit[16];
	_itoa((int32_t)dw, sdigit, 12); 
	strcat(buf, sdigit);
	int32_t c =0;
	while( *(buf + c) != 0)
	{
		*(buf + c) = toupper(*(buf + c));  
		c++;
	}
	return buf;	
}


#ifdef _WIN32
uint32_t Formater::hwndAsUint(const HWND hwnd)
{
	uint32_t res = 0;
#pragma  warning(push)
#pragma  warning(disable : 4311)
	res = (uint32_t)hwnd;
#pragma  warning(pop)

	return res;
}
#endif



//=========================================================
#ifdef _WIN32

void Formater::print_bits(  DWORD value) {

	const int32_t SHIFT = 8 * sizeof( unsigned ) - 1;
	const unsigned MASK = 1 << SHIFT;

	for ( int32_t i = 1; i <= SHIFT + 1; i++ ) 
	{
		std::cout << ( value & MASK ? '1' : '0' );
		value <<= 1;

		if ( i % 8 == 0 )
			std::cout << ' ';
	}
	std::cout << std::endl;
}

//=========================================================
const char* Formater::byteToCStrAsBin(BYTE u) {
	static char ss[32];
	ss[0]=0;
	int32_t t; 
	for(t=128; t>0; t = t/2) 
		if(u & t)  strcat(ss, "1 "); 
		else strcat(ss, "0 ");
		return ss;
}

//=========================================================
void Formater::printByteAsBin(BYTE u) { 
	printf("%s\n",  byteToCStrAsBin(u) ); 
}



//=========================================================
const char* Formater::dwordToBinStr(DWORD dwArg) {
	static char ss[64]; ss[0]=0;

	// 3
	if( dwArg & 0x80000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x40000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x20000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x10000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	if( dwArg & 0x08000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x04000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x02000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x01000000 ) { strcat(ss, "1  "); } else { strcat(ss, "0  ");  }

	// 2
	if( dwArg & 0x00800000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00400000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00200000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00100000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	if( dwArg & 0x00080000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00040000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00020000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00010000 ) { strcat(ss, "1   "); } else { strcat(ss, "0   ");  }


	// 1
	if( dwArg & 0x00008000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00004000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00002000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00001000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	if( dwArg & 0x00000800 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000400 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000200 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000100 ) { strcat(ss, "1 "); } else { strcat(ss, "0 ");  }// 0


	// 0

	if( dwArg & 0x00000080 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000040 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000020 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000010 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	if( dwArg & 0x00000008 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000004 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000002 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( dwArg & 0x00000001 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	return ss;
}

//=========================================================
void Formater::printDwordAsBinCstr(const DWORD dw) {
	printf("%s\n", dwordToBinStr(dw) );
}


//==========================================================
DWORD Formater::UintFromBinCstr(const char* _s, int32_t nlen ) throw( std::runtime_error& ) {
	DWORD res=0; 
	if(-1 == nlen) nlen = (int32_t)strlen(_s);

	int32_t ibcount =0;
	for(int32_t c=nlen-1; c>=0; c--) {
		if( ( *(_s + c) == ' ')  ||  ( *(_s + c) == '\t' )   ) 
			continue;

		if( *(_s + c) == '1'    ) {
			res |= ( 1 << ibcount );
			ibcount++;
			continue;
		}


		if( *(_s + c) == '0'    ) {
			ibcount++;
			continue;
		}


		//throw(   c  -1 );
		throw( std::runtime_error("Error data") );

		return res;

	}

	return res;
}
 
//====================================================
const char* Formater::dwordToStr(const DWORD dw,  bool bAsHex ) 
{

	static char ss[32];
	ss[0] =0;

	if(bAsHex)
	{
		strcat(ss, "0x");
		sprintf(ss + 2, "%X", dw);
	}
	else
	{
		sprintf(ss, "%u", dw);
	}


	return ss;


}

//=========================================================================
bool Formater::dwordFromStr(KS_OUT DWORD* pdwOut, const char* s) 
{

	const int32_t NSLRN = (int32_t)strlen(s);
	if(NSLRN < 3)
	{
		// not hex
		const int32_t NSCANRES = sscanf(s, "%u", pdwOut);

		if(NSCANRES != 1) return false;
		return true; 

	}

	if( (*(s) == '0') && ( *(s+1) == 'x' ) ) {
		// hex
		const int32_t NSCANRES = sscanf(s+2, "%X", pdwOut);

		if(NSCANRES != 1) return false;
		return true; 

	}
	else
	{
		// not hex
		const int32_t NSCANRES = sscanf(s, "%u", pdwOut);

		if(NSCANRES != 1) return false;
		return true; 

	}




	/*  OLD CODE
	unsigned long nval =  0;
	const int32_t NSCANRES = sscanf(s, "%u", &nval);
	dw = (DWORD)nval;

	if(NSCANRES != 1) return false;
	return true;
	*/
}

//====================================================================
bool Formater::dwordFromStr_ref(KS_OUT DWORD& dw, const char* s) 
{
	DWORD val = 0-1;

	bool bres = dwordFromStr(&val, s);
	if(!bres) return bres;

	dw = val;

	return true;
}

#endif


//====================================================

	} // namespace util
} // namespace gb
 

#pragma warning(pop)

// end file