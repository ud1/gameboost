//* прогонка ksstring.h
//  Недоделано немного...  заеб...ся ((  поправка в ближ. время.

#include "pch.h"

#include "gb/str/KsString.h" 


 namespace  ss = gb::str;

typedef  std::vector<std::string>  VSTR ;
typedef  std::vector<int32_t>      VINT;

//-----------------------------------------------------------------


#define         CCOL_WHITE  0x07  
#define         CCOL_RED    0x0C 
#define         CCOL_GREEN  0x0A  
#define         CCOL_BLUE   0x01 

#define     CCOL_BLUESKY	0x0B
#define     CCOL_PINK       0x0D
#define     CCOL_YELLOW     0x0E

#define     CCOL_GROW       0x08

//---------------------------------------------------------------

inline int SetConsoleColor(BYTE color = 0x07) {
	HANDLE hStdout;  
	hStdout = GetStdHandle( STD_OUTPUT_HANDLE ); 
	if ( hStdout == INVALID_HANDLE_VALUE )  {  return -1; 	} 
	WORD attr =   FOREGROUND_INTENSITY | ( (WORD)color) ;//  FOREGROUND_RED|FOREGROUND_INTENSITY 
	if (! SetConsoleTextAttribute(hStdout, attr ) )  {   return  -1;  	}; 
   return 0;
};


inline int SetConsoleColorW(WORD color = 0x0007) 
{  
	HANDLE hStdout;  
	hStdout = GetStdHandle( STD_OUTPUT_HANDLE ); 
	if ( hStdout == INVALID_HANDLE_VALUE )  {  return -1; 	} 
	if (! SetConsoleTextAttribute(hStdout, color ) )  {   return  -1;  	}; 
	return 0;
};

inline int cc_white()  {  return SetConsoleColor(CCOL_WHITE);  };
inline int cc_red  ()  {  return SetConsoleColor(CCOL_RED);  };
inline int cc_green()  {  return SetConsoleColor(CCOL_GREEN);  };
inline int cc_blue ()  {  return SetConsoleColor(CCOL_BLUE);  };
inline int cc_glow ()  {  return SetConsoleColor(CCOL_GROW);  };
inline int cc_pink ()  {  return SetConsoleColor(CCOL_PINK);  };
inline int cc_yellow() {  return SetConsoleColor(CCOL_YELLOW);  };



void print_float(float val, const char* promt = NULL)
{   
	 cc_white();
	if(promt)
	{
		printf("\n%s : " , promt );
	};

	printf( "%f\n" , val );
	 cc_white();
}

void print_int(int val, const char* promt = NULL) 
{  
 	cc_white();

	 if(promt)
	{
		printf("\n%s : " , promt );
	};

	printf( "%i\n" , val );
 	cc_white();
}

void prints(const char * s , const char* promt = NULL) 
{  
	cc_white();

   	if(promt)
	{
		printf("\n%s : " , promt );
	};


	printf("%s\n" , s); 
	cc_white();

};

void printm(const char* m)
{
	cc_yellow();

	printf("\n%s  \n" , m);

  cc_white();
};

void print_func(const char* funcname)
{
 cc_green();
  printf("\n  -   FUNCTION: %s  \n" , funcname );
  cc_white();
};

#define PRINTFUNC   print_func(  __FUNCTION__ );

void print_endfunc() 
{ 
	cc_glow();
	printf("\n-----------------------------------------------------\n"); 
    cc_white();
};

void print_vec_str(const VSTR& v , const char* promt = NULL )
{
   cc_pink();

   if(promt)
   {
	   printf("\ns : " , promt);
   
   };


  if(v.empty() )
  {
	 cc_red();
    printf("vector <string> is empty !\n");
	 cc_white();
    return ;
  }

  	cc_pink();

  for(size_t c=0; c<v.size(); c++)
  {
   printf("     %s\n", v[c].c_str() );
  }

  	cc_white();

  print_endfunc();
};

void print_vec_int(const VINT& v, const char* promt = NULL )
{
  cc_pink();

  if(promt)
  {
	   printf("\ns : " , promt);
  };


  if(v.empty() )
  {
  printf("vector <int> is empty !\n");
  cc_white();
  return ;
  }

  cc_pink();

	char digit[32];
  for(size_t c=0; c<v.size(); c++)
  {
	  const int NLEN = sprintf(digit , "%i", v[c] );
	  digit[NLEN] = 0;
   printf("     %s\n",  digit );
  }

  cc_white();

    print_endfunc();
};

bool __ExtractFilePathA(char* lpBuffer, const char* lpFilePath)
{
	for (unsigned i = (unsigned) strlen (lpFilePath)-1; i > 0; i--) {
		if (lpFilePath [i] == '\\') {
			memcpy (lpBuffer, lpFilePath, i+1);
			lpBuffer [i+1] = '\0';
			return true;
		}
	}

	return false;
};



 
//=========================================================================
void test_00_strTo()
{
   PRINTFUNC

	   printm("Конвертируем из строчки в float");
	float fval = 0.0f;
	if( !gb::str::strTo( fval , "2132.5645" ) )
	{
	 prints( " failed convert");
	}
	else
	{
	  prints( " succes convert");
	};

	print_float(fval);

	//-------------------------------------------------------

  	int ival = 0;
	if( !gb::str::strTo( ival , "2355" ) )
	{
	 prints( " failed convert");
	}
	else
	{
	  prints( " succes convert");
	};

	print_int(ival);

	//------------------------------------------------


  print_endfunc();
};

//=========================================================================
void test_01_strVectorTo() 
{
	PRINTFUNC

	std::vector< float > vfloats;
	std::vector< std::string >    vsrc;
	vsrc.push_back("0.0");
	vsrc.push_back("-100.890");
	vsrc.push_back("78.7575");
	vsrc.push_back("+34.65475");


	if( !gb::str::strVectorTo(vfloats , vsrc ) )
	{
	prints("failed convert");	
	}
	else
	{
	prints("succes convert");

		for(size_t c=0 ;c<vfloats.size(); c++)
		{
		  print_float( vfloats[c]  );
		};


	};

 
  print_endfunc();
};

//=========================================================================
void test_02_splitLines() 
{
	PRINTFUNC

		printm("Разрежем строку  по переносу строки");
	std::string s= "В славном городе Керчи \n\
				   Хуем рубят кирпичи";
	prints(s.c_str() , "исходная строка");
	 

	   VSTR  vs;
	ss::splitLines(vs, s );
	 print_vec_str(vs, "разбитая строка" );
 
  print_endfunc();
};

//=========================================================================
void test_03_cstrToUpper() 
{
	PRINTFUNC

	char buffer[256];
	strcpy(buffer, "Samle String");
 prints(buffer );

	ss::cstrToUpper(buffer);
   prints(buffer );

  print_endfunc();
};


//=========================================================================
void test_04_cstrToLower() 
{
	PRINTFUNC

 	char buffer[256];
	strcpy(buffer, "Samle String");
 prints(buffer );
	ss::cstrToLower(buffer);
   prints(buffer );
 

  print_endfunc();
};

//=========================================================================
void test_05_changeCase1251() 
{
	PRINTFUNC

	char buffer[256];
	strcpy(buffer , "Жили были Дед да Баба" );
	 prints(  buffer );

	 ss::changeCase1251(  buffer , true  );
	 prints(  buffer );

 	 ss::changeCase1251(  buffer , false  );
	 prints(  buffer );


  print_endfunc();
};

//=========================================================================
void test_06_searchCharPos() 
{
	PRINTFUNC

  VINT vint;
  std::string src = "C++ standard consists of two parts: the core language and the C++ Standard Library";
	if(!ss::searchCharPos(vint, src, 'c', 0 ) )
	{
	  prints(" not found !");

	}
	else
	{
	  prints("found !");
	  print_vec_int(vint);

	}; 

  print_endfunc();
};

//=========================================================================
void test_07_printStrInfo() 
{
	PRINTFUNC
	std::string s = "my string";
	prints(s.c_str() );
	ss::printStrInfo(s);

  print_endfunc();
};

//=========================================================================
void test_08_replaceChar() 
{
	PRINTFUNC

	std::string s = "C++ is one of the most popular programming languages";
	prints(s.c_str() );
	ss::replaceChar(s , 'o', 'x' );
 	prints(s.c_str() );

  print_endfunc();
};

//=========================================================================
void test_09_loadStrFromFileA() 
{
	PRINTFUNC

   char buffer[300];
   buffer[0] = 0;

   __ExtractFilePathA(buffer , __FILE__);
    strcat(buffer , "sample_load.txt");


	std::string s= "";
	prints("String before load:   ");
	prints(s.c_str() );

 


	if( ss::loadStrFromFileA(s, buffer ))
	{
	 prints("Error load file");
	}
	else
	{
	 prints(" Load text file succes");
	 prints("String after load:   ");
	prints(s.c_str() );

	};

  print_endfunc();
};

//=========================================================================
void test_10_saveStrToFileA() 
{
  PRINTFUNC

   char buffer[300];
   buffer[0] = 0;

   __ExtractFilePathA(buffer , __FILE__);
    strcat(buffer , "sample_save.txt"); 


	std::string s = "";

	s += "Близорукий гинеколог\n";
	s += "Все равно, что пес.\n";
	s += "У того и у другого\n";
	s += "Вечно мокрый нос\n"  ;

	if( !ss::saveStrToFileA(s, buffer ) )
	{
	 prints(" fail save to file");
	
	}
	else
	{
	  prints(" succes save to file");
	};

 

  print_endfunc();
};

//=========================================================================
void test_11_loadStrFromFileW() 
{
	PRINTFUNC

  // none   TODO: add

  print_endfunc();
};

//=========================================================================
void test_12_saveStrToFileW() 
{
  // none  TODO: add

  print_endfunc();
};



//=========================================================================
void test_13_iCompareCstr() 
{
	PRINTFUNC

  char buf1[200];
  char buf2[200];


    //-------------- 1   --------------------
   strcpy(buf1, "xxxx");
   strcpy(buf2, "xxxx");

	if( ss::iCompareCstr( buf1 , buf2, 4 ) )
	{
	  prints("buffers equals");

	}
	else
	{
	  prints("buffers not equals");	

	};


    //-------------- 2  --------------------
   strcat(buf1, "XXXX");
   strcat(buf2, "xxxx");

	if( ss::iCompareCstr( buf1 , buf2, 4 ) )
	{
	  prints("buffers equals");

	}
	else
	{
	  prints("buffers not equals");	

	};


    //-------------- 3  --------------------
   strcat(buf1, "xxxx");
   strcat(buf2, "XXXX");

	if( ss::iCompareCstr( buf1 , buf2, 4 ) )
	{
	  prints("buffers equals");

	}
	else
	{
	  prints("buffers not equals");	

	};

     //-------------- 4  --------------------
   strcat(buf1, "XXXX");
   strcat(buf2, "XXXX");

	if( ss::iCompareCstr( buf1 , buf2, 4 ) )
	{
	  prints("buffers equals");

	}
	else
	{
	  prints("buffers not equals");	

	};


  print_endfunc();
};

//=========================================================================
void test_14_preprocessCppComments() 
{
	PRINTFUNC

	std::string s = " int a=0;\n";
   s+= "// comment line\n";
   s+= "a++; //  incr value\n";
   s+= " /* comment\n";
   s+= " dfsf ds dsf  \n";
   s+= " end comment  */\n";
   s+= "a = 34;\n";
   s+= "/* aa it comment  */  a+= 45;\n";

   prints("STRING BEFORE PREPROCESS COMMENT");
   prints(s.c_str() );



   prints("STRING AFTER PREPROCESS COMMENT");
   prints(s.c_str() );

  print_endfunc();
};

//=========================================================================
void test_15_preprocessCppComments() 
{
	PRINTFUNC
  // none

  print_endfunc();
};

//=========================================================================
void test_17_findChar() 
{
	PRINTFUNC

	std::string s = "Наша таня, типа, плачет – \
Уронила, типа, мячик.	\
Нет бы ей прикинуть, дуре –	  \
Не утонет он, в натуре. ";

	prints( "Str bef" );
	prints(s.c_str() );

  const int32_t nIndexFound = ss::findChar(s, 'я' , 0);
  print_int(nIndexFound);

  print_endfunc();
};

//=========================================================================
void test_19_findSubstringBetween() 
{
	PRINTFUNC

	std::string s = "xxxxxx";
	std::string sres;

	int32_t npos = 0;
	if(!ss::findSubstringBetween(sres , s, '[', ']' , npos  ) )
	{
	 prints("find fail");
	}
	else
	{
	 prints("find ok");
	 print_int(npos);

	};



  print_endfunc();
};

//=========================================================================
void test_20_ksSplit() 
{
	PRINTFUNC

	VSTR vres;
	std::string s  = "Ох и дал бы я пизды\
Тем кто выдумал винды!";
	 prints(s.c_str() );


	ss::ksSplit(vres , s , ' ', true );

	 print_vec_str( vres );


  print_endfunc();
};

//=========================================================================
void test_21_splitTokens() 
{
	PRINTFUNC

 	VSTR vres;
	std::string s = "Наташа  - Ржевскому с улыбкой: \
-Ах, я  бы стать хотела рыбкой!\
Поручик ей в ответ:  -Однако,\
По мне так лучше станьте раком.";  

	prints( s.c_str() );

	ss::splitTokens(vres , s, " :.,");

  	print_vec_str(vres);

  print_endfunc();
};

//=========================================================================
void test_22_sliceByOffsets() 
{
	PRINTFUNC

  	VSTR vres;
	std::string s = "-Любишь, Вась?\n\
-Да.\n\
-Женишься, Вась?\n\
-Нет.\n\
-Слазь.\n";  

	prints( s.c_str() );

	uint32_t noffsets[4];
	noffsets[0] = 2;
	noffsets[1] = 8;
	noffsets[2] = 13;
	noffsets[3] = 16;

	ss::sliceByOffsets(vres , s , noffsets, 4 ); 


  	print_vec_str(vres);
 

  print_endfunc();
};


//=========================================================================
void test_23_sliceBetweenIndices() 
{
	PRINTFUNC

  	VSTR vres;
	std::string s = " пацан в автобусе встал на ногу старушке.\n\
-Пардон, бабуля!\n\
-О, юноша, Вы говорите по-французски?\n\
-   Да, а хули!\n";

	prints(s.c_str() );

#pragma message("TODO "  __FILE__ )

	if( 
		! (0) //  ss::sliceBetweenIndices(vres, s, 'а' 0, 4 ) 
		)
	{
	  prints( "slice failed" );
	}
	else
	{
	  prints( "slice succes" );
	};
  
   print_vec_str(vres);


  print_endfunc();
};

//=========================================================================
void test_24_isAnyOf() 
{
	PRINTFUNC

	const std::string s  = "-Наташа, не потрахаться ли нам?\n\
-Поручик, Вы такой наглец и хам!\n\
-Что? Это означает - «я не дам»?\n\
-Дам, но, однако, Вы  наглец и хам.\n";

	if(  ss::isAnyOf( 'z', s ) )
	{
	  prints("true");
	}
	else
	{
	  prints("false");
	};


  

  print_endfunc();
};

//=========================================================================
void test_25_findAnyOf() 
{
	PRINTFUNC

	const std::string s = "    \t  abcd";


	int32_t  npos = 0;
	if( ss::findAnyOf( s, npos , "abcd" ) )
	{
	  prints("Find ok");
	  print_int(npos);

	}
	else
	{
	 prints("Find failed");
	};

  print_endfunc();
};

//=========================================================================
void test_26_findAnyOfBetween() 
{
	PRINTFUNC

	std::string s = "Ближе <х..я> родни нет";
	prints(s.c_str() );

	int32_t npos = 0;

	if( ss::findAnyOfBetween( s, npos , '<', '>' ) )
	{
	  prints("Find succes");
	  print_int(npos);
	}
	else
	{
	  prints("Find failed");
     };

  print_endfunc();
};

//=========================================================================
void test_27_replaceAnyChar() 
{
	PRINTFUNC

	std::string s= "Надо иметь сметку - ебать жену, но не забывать и соседку!";
	prints(s.c_str() );

	ss::replaceAnyChar(s , "е", '@' ); 

	 prints(s.c_str() );


  print_endfunc();
};

//=========================================================================
void test_28_replaceAnyChar() 
{
	PRINTFUNC

	std::string s= "Надо иметь сметку - ебать жену, но не забывать и соседку!";
	prints(s.c_str() );

	ss::replaceAnyChar(	s, "еж", '%' );
	prints(s.c_str() );

  print_endfunc();
};

//=========================================================================
void test_29_check_OpenXmlTag() 
{
	PRINTFUNC

	std::string src = "<abs>";
	 prints(src.c_str() );
	std::string stag;


	 if(ss::check_OpenXmlTag(stag , src) )
	 {
	  prints(  "   yes. may be open" );
	 }
	 else
	 {
	   prints(  "   no." );
	 };



  print_endfunc();
};

//=========================================================================
void test_30_check_OpenXmlTag_pos() 
{
	PRINTFUNC

	std::string s = "data string <begin> value";
	std::string sout;
	int32_t npos = 0;

	if( ss::check_CloseXmlTag_pos(sout, s, npos ) )
	{
	 prints("yes");
	 print_int(npos);
	}
	else
	{
	 prints("no");
	};
  

  print_endfunc();
};


 
//=========================================================================
void test_31_check_CloseXmlTag() 
{
 PRINTFUNC 

  print_endfunc();
};

//=========================================================================
void test_32_check_CloseXmlTag_pos() 
{
 PRINTFUNC

  print_endfunc();
};

//=========================================================================
void test_33_skipCppOnelineComment() 
{
 PRINTFUNC 

  print_endfunc();
};

//=========================================================================
void test_34_skipCppOnelineComment2() 
{
 PRINTFUNC 

  print_endfunc();
};

//=========================================================================
void test_35_intArrayToStr() 
{
 PRINTFUNC

  print_endfunc();
};

//=========================================================================
void test_36_intArrayToStr2() 
{
  PRINTFUNC

  print_endfunc();
};

//=========================================================================
void test_37_intArrayFromStr() 
{
 PRINTFUNC

  print_endfunc();
};

//=========================================================================
void test_38_intArrayFromStr2() 
{
 PRINTFUNC 

  print_endfunc();
};

//=========================================================================
void test_39_findNextSkipAny() 
{
 PRINTFUNC 

  print_endfunc();
};

//=========================================================================
void test_40_removeAnyFromBeginAndEnd() 
{
 PRINTFUNC 

  print_endfunc();
};

//=========================================================================
void test_41_removeAnyFromBeginAndEnd() 
{
  PRINTFUNC

  print_endfunc();
};

//=========================================================================
void test_42_removeAnyFromBeginAndEnd_Vec() 
{
  PRINTFUNC

  print_endfunc();
};

//=========================================================================
void test_43_strArrayToStr() 
{
 PRINTFUNC 

  print_endfunc();
};


//=========================================================================
void test_44_strArrayFromStr() 
{
  PRINTFUNC

  print_endfunc();
};

//=========================================================================
void test_45_sliceStrByIndices() 
{
 PRINTFUNC 

  print_endfunc();
};

//=========================================================================
void test_46_copyStringsSkipEmpty() 
{
 PRINTFUNC 

  print_endfunc();
};


//=========================================================================
void test_47_findNextLinePos() 
{
  PRINTFUNC

  print_endfunc();
};
  




//=========================================================================
//  =========================   MAIN  ==================================
//=========================================================================
int main()
{
  setlocale(LC_ALL, "Russian");

  test_00_strTo();
  test_01_strVectorTo();

   test_02_splitLines();  
	   test_03_cstrToUpper();  
	   test_04_cstrToLower();

   test_05_changeCase1251();  
   test_06_searchCharPos (); 
   test_07_printStrInfo ();
   test_08_replaceChar   ();
   test_09_loadStrFromFileA ();
   test_10_saveStrToFileA (); 
   test_11_loadStrFromFileW	();
	test_12_saveStrToFileW (); 
	test_13_iCompareCstr (); 
	test_14_preprocessCppComments  ();


 test_15_preprocessCppComments (); 
 test_17_findChar (); 
 test_19_findSubstringBetween  ();
 test_20_ksSplit (); 
 test_21_splitTokens (); 
 test_22_sliceByOffsets  ();
 test_23_sliceBetweenIndices  ();
  test_24_isAnyOf   ();
  test_25_findAnyOf ();  
  test_26_findAnyOfBetween (); 
  test_27_replaceAnyChar ();
  test_28_replaceAnyChar (); 
  test_29_check_OpenXmlTag (); 
  test_30_check_OpenXmlTag_pos();




  system("pause");
  return 0;
};
