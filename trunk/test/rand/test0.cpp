//* test random 

#include "pch.h"
#include <stdio.h> 
#include <stdlib.h>
 
#include "gb/rand/rand.h"

//==============================================================
void print_int(const char* promt, const int32_t val)
{
	printf("%s:  %i \n", promt , val );
};

//==============================================================
void print_bool(  const bool val)
{
	if(val)
	{
	 printf("  true \n"   );
	}
	else
	{
	 printf("  false \n"   );
	};
	
};

//=======================================================
void print_float( const float f )
{
 printf(" %f\n" , f );
};

void print_stdstr(const std::string& s) 
{
  printf( "%s\n" , s.c_str()  );
};



//==============================================================
void print_div() 
{
   printf("%s\n", "===============================================");
};

//==============================================================
void test_randomBool() 
{
 print_div() ;
 printf("%s\n", "       test_randomBool  ");

 for(int c=0; c<100; c++)
 print_bool( gb::rand::randomBool() );
 







  print_div() ;
  //===========================================================

};

//====================================================
void test_randomMax()
{
 print_div();
  printf("%s\n", "       test_randomMax  ");


  int32_t nval = 0;

   nval = gb::rand::randomMax(1);
   print_int("gb::rand::randomMax(1)", nval );
   Sleep(1);

   nval = gb::rand::randomMax(1);
   print_int("gb::rand::randomMax(1)", nval );
    Sleep(1);

   nval = gb::rand::randomMax(1);
   print_int("gb::rand::randomMax(1)", nval );
     Sleep(1);

   nval = gb::rand::randomMax(1);
   print_int("gb::rand::randomMax(1)", nval );
    Sleep(1);

   nval = gb::rand::randomMax(1);
   print_int("gb::rand::randomMax(1)", nval );
    Sleep(1);

   nval = gb::rand::randomMax(1);
   print_int("gb::rand::randomMax(1)", nval );
     Sleep(1);

   nval = gb::rand::randomMax(1);
   print_int("gb::rand::randomMax(1)", nval );
    Sleep(1);


  print_div() ;
  //===========================================================


   nval = gb::rand::randomMax(10);
   print_int("gb::rand::randomMax(10)", nval );
   Sleep(1);

   nval = gb::rand::randomMax(10);
   print_int("gb::rand::randomMax(10)", nval );
   Sleep(1);

   nval = gb::rand::randomMax(10);
   print_int("gb::rand::randomMax(10)", nval );
   Sleep(1);

   nval = gb::rand::randomMax(10);
   print_int("gb::rand::randomMax(10)", nval );
   Sleep(1);

   nval = gb::rand::randomMax(10);
   print_int("gb::rand::randomMax(10)", nval );
   Sleep(1);


  print_div() ;
  //===========================================================
 
    nval = gb::rand::randomMax(100);
   print_int("gb::rand::randomMax(100)", nval );
    Sleep(1);

    nval = gb::rand::randomMax(100);
   print_int("gb::rand::randomMax(100)", nval );
    Sleep(1);

    nval = gb::rand::randomMax(100);
   print_int("gb::rand::randomMax(100)", nval );
    Sleep(1);

     nval = gb::rand::randomMax(100);
   print_int("gb::rand::randomMax(100)", nval );
    Sleep(1);

     nval = gb::rand::randomMax(100);
   print_int("gb::rand::randomMax(100)", nval );
    Sleep(1);

   print_div() ;
   //======================================================


  
  print_div() ;
  //===========================================================
 
    nval = gb::rand::randomMax(1000000);
   print_int("gb::rand::randomMax(1000000)", nval );
    Sleep(1);

    nval = gb::rand::randomMax(1000000);
   print_int("gb::rand::randomMax(1000000)", nval );
    Sleep(1);

    nval = gb::rand::randomMax(1000000);
   print_int("gb::rand::randomMax(1000000)", nval );
    Sleep(1);

     nval = gb::rand::randomMax(1000000);
   print_int("gb::rand::randomMax(1000000)", nval );
    Sleep(1);

     nval = gb::rand::randomMax(1000000);
   print_int("gb::rand::randomMax(1000000)", nval );
    Sleep(1);

   print_div() ;
   //======================================================
 
};

//==================================================
void test_randomMinMax() 
{
 print_div();
  printf("%s\n", "       test_randomMinMax  ");

  print_int( "randomMinMax( 0 , 10 )",  gb::rand::randomMinMax( 0 , 10 )  );
  print_int( "randomMinMax( 0 , 10 )",  gb::rand::randomMinMax( 0 , 10 )  );
  print_int( "randomMinMax( 0 , 10 )",  gb::rand::randomMinMax( 0 , 10 )  );
  print_int( "randomMinMax( 0 , 10 )",  gb::rand::randomMinMax( 0 , 10 )  );

  print_div();

  print_int( "randomMinMax( 10 , 100 )",  gb::rand::randomMinMax( 10 , 100 )  );
  print_int( "randomMinMax( 10 , 100 )",  gb::rand::randomMinMax( 10 , 100 )  );
  print_int( "randomMinMax( 10 , 100 )",  gb::rand::randomMinMax( 10 , 100 )  );
  print_int( "randomMinMax( 10 , 100 )",  gb::rand::randomMinMax( 10 , 100 )  );

   print_div();

  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  ); 
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );
  print_int( "randomMinMax( 900 , 1000 )",  gb::rand::randomMinMax( 900 , 1000 )  );

 print_div();
};

//================================================================
void test_randomUnsFloatBetween01()
{
 print_div();
  printf("%s\n", "       test_randomUnsFloatBetween01  ");

  for(int c=0; c<20; c++)
  {
  print_float( gb::rand::randomUnsFloatBetween01() );  
  }
 

 print_div();

};

//===============================================
void test_randomSignFloat1()
{
  print_div();
  printf("%s\n", "       test_randomSignFloat1  ");

  for(int c=0; c<30; c++)
  {
  print_float( gb::rand::randomSignFloat1() );  
  }


  print_div();
};




//==================================================
void test_randomStr()
{
   print_div();
  printf("%s\n", "       test_randomStr  ");


	std::string s;

 for(int c=0; c<10; c++)
 {
    gb::rand::randomStr(s, 'a', 'z', 12 )  ;
	print_stdstr(s);
 };

 printf("\n");

 for(int c=0; c<10; c++)
 {
    gb::rand::randomStr(s, '0', '9', 6 )  ;
	print_stdstr(s);
 };


   print_div();
};


//============================================
void test_randomCstr()
{
    print_div();
  printf("%s\n", "       test_randomStr  ");

  char buffer[32];

  for(int c=0; c<20; c++)
  {
	gb::rand::randomCstr(buffer , 32, 'A', 'Z', 16 ); 
   printf( "%s\n" , buffer );
  };

     print_div();
};
 

//================================================================
int  main(int argc,  char* argv[])
{
  printf("%s" , "START APPLICATION ..... \n\n " );


	test_randomBool();
   test_randomMax();
   test_randomMinMax();
   test_randomUnsFloatBetween01();
   test_randomSignFloat1();
   test_randomStr();
   test_randomCstr();


    printf("\n");
  system("pause");
	return 0;
}

