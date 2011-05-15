//  тест для класса Formater
//


/********************* stdafx.h **************************

#pragma once

#define WIN32_LEAN_AND_MEAN	
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <string.h>
#include <string> 
#include <stdexcept>

*******************************************/


//#pragma  message("ВЕРНУТЬ ПРЕКОМП ХЕДЕР"  __FILE__ )
#include "pch.h"
//#include "stdafx.h"


//#pragma  message("ВЕРНУТЬ ПРАВИЛЬНЫЙ ПУТЬ"  __FILE__ ) 
#include "gb/str/ksutils.h"
#include "gb/str/formater.h"
//#include "z:\\!!GB_TOADD\\new_formater\\formater.h"
//#include <windows.h>

#pragma region INTERNAL

typedef   gb::str::Formater   F;

//================================
void printfunc( const char* funcname )
{
	printf("\n\n%s%s%s\n" , "--------------", funcname, "---------------------");

};


#define PRINT_FUNC printfunc(__FUNCTION__);

void print_str(const char* s, const char* promt = NULL)
{
	if(promt)
	{
		printf("\n%s : " , promt );
	};

	printf( "%s\n" , s );
 
};

void printmsg(const char* m) {
   printf("%s\n" , m);
};

void print_float(float val, const char* promt = NULL)
{   
 
	if(promt)
	{
		printf("\n%s : " , promt );
	};

	printf( "%f\n" , val );
 
}

void print_int(int val, const char* promt = NULL) 
{  
 	 if(promt)
	{
		printf("\n%s : " , promt );
	};

	printf( "%i\n" , val );
 
}

void print_bool(bool val, const char* promt = NULL) 
{  
 	if(promt)
	{
		printf("\n%s : " , promt );
	};

	if(val)
	{
		printf( " true\n" );
	}
	else
	{
		printf( " false\n" );
	};
 
}

#pragma endregion INTERNAL

//=========================================================================
void test_00_boolToCstr()
{
	PRINT_FUNC
	char buffer[32];
	F::boolToCstr(buffer, 31, true);
  print_str(buffer, "result by arg true");

	F::boolToCstr(buffer, 31,  false);
    print_str(buffer, "result by arg false");
};

//=========================================================================
void test_01_boolToUppercaseCstr()
{
	PRINT_FUNC
	char buffer[32];
	F::boolToUppercaseCstr(buffer, 31, true);
  print_str(buffer, "result by arg true");

	F::boolToUppercaseCstr(buffer, 31,  false);
    print_str(buffer, "result by arg false");

};

//=========================================================================
void test_02_floatToCstr()
{
 	PRINT_FUNC
	char buffer[32]; 

	float fval = 1.123456f;
  print_float(fval , "input arg is");
	F::floatToCstr(buffer, 31, fval);
	print_str(buffer,  "Result");
 


};

//=========================================================================
void test_021_floatFromCstr()
{
 	PRINT_FUNC
	  const char* src = "2.487875"; 
	print_str(src, "Input arg  to be read");

	float val = 0.0f;
	if( F::floatFromCstr(val, src) )
	{
	 print_str("Result SUCCES !");
	 print_float(val, "value after read" );
	}
	else
	{
	 print_str("Result FAILED !");	
	}


};

//=========================================================================
void test_03_intToCstr()
{
 	PRINT_FUNC
		char buffer[32];

	const int32_t val = 4687645;
	print_int(val, "Input arg to be convert to str");

	F::intToCstr(buffer, 31, val , false );
	print_str(buffer, "after convert no hex" );

	F::intToCstr(buffer, 31, val , true );
	print_str(buffer, "after convert AS CPP HEX" );

};

//=========================================================================
void test_04_intFromCstr()
{
  PRINT_FUNC
	  const char* sint = "6647447";
  print_str(sint, "Input str" );

  int32_t val = 0;
    if(F::intFromCstr(val , sint) )
	{
	   print_int(val,  "Read OK. Result");
	}
	else
	{
	  print_int(val,  "Read FAILED. Result");
	};

	printf("\n\n    Covert from c++ hex");
	const char* shex = "0x300";
	print_str(shex , "Input string" );

    if(F::intFromCstr(val , sint) )
	{
	   print_int(val,  "Read OK. Result");
	}
	else
	{
	  print_int(val,  "Read FAILED. Result");
	};



};

//=========================================================================
void test_05_uintToCstr()
{
PRINT_FUNC
		char buffer[32];

	const uint32_t val = 765466;
	print_int(val, "Input arg to be convert to str");

	F::uintToCstr(buffer, 31, val , false );
	print_str(buffer, "after convert no hex" );

	F::uintToCstr(buffer, 31, val , true );
	print_str(buffer, "after convert AS CPP HEX" );



};

//=========================================================================
void test_06_uintFromCstring ()
{
PRINT_FUNC
 const char* sintdgt = "868668";
 const char* sinthex = "0x00f0";

 uint32_t val = 0;


   printf("\nRead from str digit format \n");
   print_str(sintdgt, "Input arg" );
 if( F::uintFromCstr(val, sintdgt) )
 {
   print_int(val , "Read ok");
 }
 else
 {
   print_int(val , "Read failed"); 
 };

   printf("\nRead from str hex format \n");
      print_str(sinthex, "Input arg" );
 if( F::uintFromCstr(val, sinthex) )
 {
   print_int(val , "Read ok");
 }
 else
 {
   print_int(val , "Read failed"); 
 };



};

//=========================================================================
void test_07_intToHex ()
{
 PRINT_FUNC
	 char buffer[32];


 int32_t val = 255; 
 print_int(val , "input arg");
	 F::intToHex(buffer, 31 ,  val);
 print_str(buffer, "result" );

};

//=========================================================================
void test_08_intToCppHex()
{
 PRINT_FUNC
	 char buffer[32];


 int32_t val = 255; 
 print_int(val , "input arg");
	 F::intToCppHex(buffer,  31 , val);
 print_str(buffer, "result" );
};

//=========================================================================
void test_09_pointerToCstr ()
{
	PRINT_FUNC
	       int32_t  ilocal = 4546;
	static int32_t  istatic = 6466;

	void* pLocal = (void*)&ilocal;
	void* pStatic  = (void*)&istatic;

	char buffer[32];

	F::pointerToCstr(buffer, 31, pLocal);
	print_str(buffer, "Address local variable    ");

	F::pointerToCstr(buffer, 31,  pStatic);
    print_str(buffer, "Address  static variable  ");
};

//=========================================================================
void test_10_byteToCStrAsBin()
{
	PRINT_FUNC
	char buffer[32] ;

	uint8_t val = 0xff;
   print_int((int)val , "Inp arg");

   F::byteToCStrAsBin(buffer , 31, val );
   print_str(buffer , " Result" );
	 


};

//=========================================================================
void test_11_uintToBinCstr ()
{
	PRINT_FUNC

};

//=========================================================================
void test_12_uintToCstr()
{
	PRINT_FUNC

};


//=========================================================================
void test_13_uintFromCstr ()
{
	PRINT_FUNC

};



//=========================================================================
void test_14_uintFromBinCstr()
{
	PRINT_FUNC

};


//=========================================================================
void test_15_printByteAsBin()
{
	PRINT_FUNC
		F::printByteAsBin(0xaa);
};


//=========================================================================
void test_16_printUint32AsBin()
{
  	PRINT_FUNC
		F::printUint32AsBin(0xa87b6823);

};
 
//=========================================================================
void test_18_hwndAsUint()
{
   HWND hw = (HWND)0x563434;
    uint32_t val  = F::hwndAsUint(hw);


};

  

//==================================================
int main(int argc, char* argv[])
{
   test_00_boolToCstr();
test_01_boolToUppercaseCstr();

test_02_floatToCstr();
test_021_floatFromCstr();

test_03_intToCstr();
test_04_intFromCstr();

test_05_uintToCstr();

test_06_uintFromCstring();

test_07_intToHex();

test_08_intToCppHex();

test_09_pointerToCstr();

test_10_byteToCStrAsBin();


  system("pause");
	return 0;
}

