/** \file   formater.cpp
*
*
*   \author ksacvet777 (ksacvet777@mail.ru) ICQ: #262849586

 \todo УДАЛИТЬ FORMATER  В ФУНКЦИИ  gb::str::
*
*/

#include <gb/str/formater.h>

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

 
#pragma warning(push)
#pragma warning( disable : 4996 )


//=========================================================
bool  gb::str::Formater::byteToCStrAsBin(char* pDest, int32_t ndestlen, uint8_t value)
{
	try 
	{
	  char ss[64];
	ss[0]=0;

	int32_t t; 

	for(t=128; t>0; t = t/2) 
		if(value & t)  strcat(ss, "1"); 
		else strcat(ss, "0");

	// copy
	strncpy(pDest ,  ss, ndestlen );
 
	}
	catch(...)
	{
	  return false;
	}

  return true;
}

//=========================================================
void gb::str::Formater::printByteAsBin( uint8_t value ) 
{ 
	char buf[64];

   byteToCStrAsBin(buf, 64, value );
	printf("%s\n",  buf  ); 
}

 

//=========================================================
void gb::str::Formater::printUint32AsBin(  uint32_t value) 
{

	const int32_t SHIFT = 8 * sizeof( uint32_t ) - 1;
	const unsigned int MASK = 1 << SHIFT;

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
bool gb::str::Formater::uintToBinCstr(char* pDest, int32_t ndestlen, uint32_t value)
//const char * uintToBinCstr(uint32_t dwArg) 
{
	try 
	{

	  char ss[64]; 
	  ss[0]=0;

	// 3
	if( value & 0x80000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x40000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x20000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x10000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	if( value & 0x08000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x04000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x02000000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x01000000 ) { strcat(ss, "1  "); } else { strcat(ss, "0  ");  }

	// 2
	if( value & 0x00800000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00400000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00200000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00100000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	if( value & 0x00080000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00040000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00020000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00010000 ) { strcat(ss, "1   "); } else { strcat(ss, "0   ");  }


	// 1
	if( value & 0x00008000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00004000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00002000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00001000 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	if( value & 0x00000800 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000400 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000200 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000100 ) { strcat(ss, "1 "); } else { strcat(ss, "0 ");  }// 0


	// 0

	if( value & 0x00000080 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000040 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000020 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000010 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	if( value & 0x00000008 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000004 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000002 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }
	if( value & 0x00000001 ) { strcat(ss, "1"); } else { strcat(ss, "0");  }

	//copy
	strncpy(pDest , ss, ndestlen);


	}
	catch(...)
	{
	  return false;
	}


	return true;
}

//=====================================================================
bool gb::str::Formater::intToBinCstr(char* pDest, int32_t ndestlen, 
											    uint32_t value) 
{
	 return uintToBinCstr(pDest , ndestlen , value );
};


//===================================================================
std::string gb::str::Formater::uintToBinStr( uint32_t value)
{
	std::string s;
	char buf[32];

	if( !uintToBinCstr(buf, 32, value ) ) return s;

    s = buf;

    return s;
};

//===================================================================
std::string gb::str::Formater::intToBinStr( uint32_t value)
{
	std::string s;
	char buf[32];

	if( !intToBinCstr(buf, 32, value ) ) return s;

    s = buf;

    return s;
};
 

//==========================================================
uint32_t gb::str::Formater::uintFromBinCstr(const char* _s, int32_t nlen ) throw() 
	// throw() - наличие throw() в объявлении функции и наличие throw в коде даёт варнинг компилятора
	// std::runtime_error& ) 
{
	uint32_t res=0; 
	if(-1 == nlen) nlen = (int32_t)strlen(_s);

	int32_t ibcount =0;
	for(int32_t c=nlen-1; c>=0; c--) 
	{
		if( ( *(_s + c) == ' ')  ||  ( *(_s + c) == '\t' )   ) 
			continue;

		if( *(_s + c) == '1'    ) 
		{
			res |= ( 1 << ibcount );
			ibcount++;
			continue;
		}


		if( *(_s + c) == '0'    )
		{
			ibcount++;
			continue;
		}


		//throw(   c  -1 );
// WARNING
// 		gb\str\formater.cpp(219): warning C4297: 'gb::str::Formater::uintFromBinCstr' : function assumed not to throw an exception but does
//           __declspec(nothrow) or throw() was specified on the function
		throw( std::runtime_error( "Formater::uintFromBinStr: Data error" ) );

		return res;

	}

	return res;
}
  

//==================================================================
bool gb::str::Formater::floatFromCstr( KS_OUT float* out_val, const char* s )
{
	try {
		const int32_t NSCANRES = sscanf(s, "%f", out_val);	
		if(NSCANRES != 1) return false;

	}
	catch(...)
	{
	  return false;
	}

  return true;
};

//==================================================================
bool gb::str::Formater::floatFromCstr(KS_OUT float& out_val, const char* s) 
{
		try {

		float value = -1.0f;
		if( floatFromCstr(&value, s) == false ) 
			  return false;

		out_val = value;
	}
	catch(...)
	{
	  return false;
	}

  return true;	
}

//=========================================================
static void  __Unsafe_boolToCstr(char* pDest, int32_t ndestlen, bool  value)
{
	*pDest = '\0';
	if(value) 
	{ 
		strncpy(pDest, "true",  ndestlen); 
	} 
	else 
	{ 
		strncpy(pDest, "false",  ndestlen); 
	}

};


//=========================================================
bool gb::str::Formater::boolToCstr(char* pDest, int32_t ndestlen, bool  value) 
{
  bool bres = false;
	try {
    __Unsafe_boolToCstr(pDest, ndestlen, value);
	}
	catch(...)
	{
	  return false;
	}

	return true;
}

//=========================================================
std::string gb::str::Formater::boolToStr(bool  value) 
{
   static std::string s;
	char buf[32];
	if(!boolToCstr(buf, 32, value) ) return  s;

  s = buf;
  return s;
};


//=========================================================
static bool __Unsafe_boolToUppercaseCstr(char* pDest, int32_t ndestlen, bool value)
{
	bool  res = gb::str::Formater::boolToCstr(pDest, ndestlen, value );
  if( !res ) return res;

  // set up case
  int c =0;
  while(true)
  {
     if( *(pDest + c) == '\0' ) return res;
    *(pDest + c) = toupper( *(pDest + c)  );
  
  c++;
  };

	return   res;
}


//========================================================
bool gb::str::Formater::intFromCstr(KS_OUT int32_t* out_val, const char* s) 
{
	// NEW

	try 
	{

	const int32_t NSLRN = (int32_t)strlen(s);
	if(NSLRN < 3)
	{
		// not hex
		const int32_t NSCANRES = sscanf(s, "%u", out_val);

		if(NSCANRES != 1) return false;
		return true; 

	}

	if( (*(s) == '0') && ( ( *(s+1) == 'x' ) || *(s+1) == 'X'  ) ) 
	{
		// hex
		const int32_t NSCANRES = sscanf(s+2, "%X", out_val);

		if(NSCANRES != 1) return false;
		return true; 

	}
	else
	{
		// not hex
		const int32_t NSCANRES = sscanf(s, "%i", out_val);

		if(NSCANRES != 1) return false;
		return true; 

	}

	}
	catch(...)
	{
	 return false;
	}

  return true;
}

//========================================================
bool gb::str::Formater::intFromCstr(KS_OUT int32_t& val, const char* s) 
{
		int32_t value = -1;
		if( intFromCstr(&value, s) == false ) return false;

		val = value;
		return true;
}



//=========================================================
bool gb::str::Formater::boolToUppercaseCstr(char* pDest, int32_t ndestlen, bool value)
{
   bool res = false;
	try {
		res = __Unsafe_boolToUppercaseCstr(pDest, ndestlen, value);
	}
	catch(...)
	{
	 return false;
	}
  return true;
}

//====================================================
std::string gb::str::Formater::boolToUppercaseStr( bool value )
{
	std::string s;
  char buf[32];

  if( !boolToUppercaseCstr(buf, 32, value) ) return s;

  s = buf;
 return s;
};


//=========================================================================
bool gb::str::Formater::uintFromCstr(KS_OUT uint32_t* pdwOut, const char* s) 
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


}

//====================================================================
bool gb::str::Formater::uintFromCstr(KS_OUT uint32_t& dw, const char* s) 
{
	uint32_t val = 0-1;

	bool bres = uintFromCstr(&val, s);
	if(!bres) return bres;

	dw = val;

	return true;
}

/*
//=========================================================
bool gb::str::Formater::uintFromCstring(KS_OUT uint32_t& val, const char* s) 
{
		uint32_t nval = -1;
		const int32_t NSCANRES = sscanf(s, "%u", &nval);
		val = nval;

		if(NSCANRES != 1) return false;
		return true;
};
 */

//=========================================================
bool gb::str::Formater::floatToCstr(char* pDest, int32_t ndestlen, float value)
{
	try 
	{
    char bufdigit[32];
	bufdigit[0] = '\0';
	const int32_t NCOUNT = sprintf(bufdigit, "%f", value );

	 strncpy(pDest , bufdigit, ndestlen);

	}
	catch(...)
	{
	   return false;
	}

	return true;
};

//=============================================================
std::string  gb::str::Formater::floatToStr(float value)
{
 std::string s;
 char buf[32];

 if( !floatToCstr(buf, 32, value) ) return s;

	 s = buf;
  return s;
};

//=============================================================
bool gb::str::Formater::intToCstr(char* pDest, int32_t ndestlen,  
										 int32_t value, 
										 bool bAsCppHex)
{
	// NEW
	try {

		char buffer_digit[32];
		buffer_digit[0] = 0;

		if(bAsCppHex)
		{
		 sprintf(buffer_digit, "0x%.8X", value );
		}
		else
		{
		 sprintf(buffer_digit, "%i", value );
		};

		strncpy(pDest, buffer_digit, ndestlen);
        
	}
	catch(...)
	{
	  return false;
	}

  return true;
};

//================================================================
bool gb::str::Formater::uintToCstr(char* pDest, int32_t ndestlen, 
								   uint32_t value, bool bAsCppHex)
{
  // NEW 
	try {

		char buffer_digit[32];
		buffer_digit[0] = 0;

		if(bAsCppHex)
		{
		 sprintf(buffer_digit, "0x%.8X", value );
		}
		else
		{
		 sprintf(buffer_digit, "%u", value );
		};

		strncpy(pDest, buffer_digit, ndestlen);
        
	}
	catch(...)
	{
	  return false;
	}

   return true;
};

//=============================================
std::string gb::str::Formater::intToStr  ( int32_t value, bool bAsCppHex)
{
  std::string s;
  char buf[32];

   if( !intToCstr(buf, 32, value, bAsCppHex) )  return s;

  s = buf;
  return s;
};


//=============================================
std::string gb::str::Formater::uintToStr ( uint32_t value, bool bAsCppHex)
{
  std::string s;
  char buf[32];

   if( !uintToCstr(buf, 32, value , bAsCppHex) )  return s;

  s = buf;
  return s;
};

/*
//=========================================================
const char* gb::str::Formater::intToCstr(int32_t i) {
	static char buff[32];
	sprintf(buff, "%i", i );
	return buff;  
};
*/


/*
//=========================================================
const char* gb::str::Formater::uintToCstr(uint32_t val) 
{
	static char ss[16];
	ss[0] = 0;
	sprintf(ss, "%u", val );
	return ss;	
};
*/

//=========================================================
bool gb::str::Formater::intToHex(char* pDest, int32_t ndestlen, int32_t value) 
{
	try 
	{
	static char buff[32];
	sprintf(buff, "%.8X", value );

	strncpy(pDest, buff, ndestlen);

	}
	catch(...)
	{
	  return false;
	}
   return true;
}

//=========================================================
bool gb::str::Formater::intToCppHex(char* pDest, int32_t ndestlen, int32_t value) 
{
   try 
   {
	  char dig[16];
	  dig[0] = '\0';

	sprintf(dig, "0x%.8X", value );
	 
    strncpy( pDest , dig , ndestlen );

   }
   catch(...)
   {
    return false;
   };

	return  true;
} 


//=========================================================
bool gb::str::Formater::pointerToCstr(char* pDest, int32_t ndestlen, const void* p)
{
#pragma  warning(push)
#pragma  warning(disable : 4311)

	try 
	{
 
	char  buf[32]; 
	buf[0]=0;
	//sprintf(buf, "0x%.8X", value );
	

	if( sizeof(void*) == 4 )
	{
	  // 32
      sprintf(buf, "%d", (unsigned long)p );
	}
	else
	{
	  // 64
      sprintf(buf, "%ld", (unsigned long long)p );
	}

	//int c=0;
	//while( *(buf + c) != 0)
	//{
	//	*(buf + c) = toupper(*(buf + c));  
	//	c++;

	//	if(c>100)
	//	{
	//	 // infin loop ?????
	//	}
	//}
 	

	// copy to dest
	strncpy(pDest , buf , ndestlen );

    }
	catch(...) 
	{
	 return false;
	}

	return true;
	#pragma  warning(pop)

}


//=========================================================================
//===					   WIN32 spec								  =====
//=========================================================================

#ifdef _WIN32

//===========================================
uint32_t gb::str::Formater::hwndAsUint(const HWND hwnd)
{
	uint32_t res = 0;
#pragma  warning(push)
#pragma  warning(disable : 4311)
	res = (uint32_t)hwnd;
#pragma  warning(pop)

	return res;
}

#endif   // #ifdef _WIN32


// end formater impl

#pragma warning(pop)

// end file