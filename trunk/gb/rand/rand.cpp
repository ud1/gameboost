/** \file rand.сpp
* \brief Получение случайных значений. Реализация.
*
*
*
*/

    // temp inc  for vs
#include "stdafx.h"
 
   // temp exclude
//#include "pch.h"

#include <gb\rand\rand.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//=============================================================
//      инициализация рандома
//=============================================================
static void __initRandom() 
{
	static bool sbFirstcall=true; 
	if(!sbFirstcall)  return; 
	sbFirstcall=false; 

	::srand( (uint32_t) time(NULL));	
};

//=========================================================================
bool gb::rand::randomBool()
{
   if(randomMax(1) )
   {
	 return true;
   }
  
   return false;
};


//=========================================================================
float gb::rand::randomSignFloat1() 
{
 
   return (randomUnsFloatBetween01() - 0.5f) * 2.0f;

}

//=========================================================================
float gb::rand::randomUnsFloatBetween01() 
{
	static bool sbFirstCall = true;
	static int32_t stime;

	if(sbFirstCall) { 
		sbFirstCall = false; 

		stime=  (int32_t)(time(NULL)/2);  
		srand(stime);  
	}


	return  (float) ::rand() /  (float)RAND_MAX   ;
}


//=========================================================================
int32_t  gb::rand::randomMax(int32_t nmax) 
{
	__initRandom();
	return  (int32_t)(   ( (float) ::rand() / (float)RAND_MAX  )  * (float)nmax +  0.5f );  
}

//=========================================================================
int32_t  gb::rand::randomMinMax(int32_t nmin , int32_t nmax) 
{
	__initRandom();
	return  gb::rand::randomMax(  nmax - nmin ) + nmin;
}

//=========================================================================
bool gb::rand::randomStr(std::string& sOut, char chrMin, char chrMax, const int nLenght)
{
  if( (chrMin == '\0') || (chrMax == '\0') || (chrMin > chrMax) )
  {
   // invalid params
	  return false;
  };


 sOut = "";

 if(nLenght == 0) return true;

 sOut.reserve(nLenght + 1);
  for(int c=0; c<nLenght; c++)
  {
	  char nchar = (char)(  gb::rand::randomMinMax( (int)chrMin , (int)chrMax )  );
	  sOut += nchar;
  };

  return true;
};
 
//====================================================================
void gb::rand::randomCstr(char* pdest, int ndestlen, char chrMin, char chrMax, const int nLenght)
{
   if(NULL == pdest) return ;
	*pdest = '\0';

   int num = nLenght;
   if( num > ndestlen-1 )
   {
    num = ndestlen-1;
   }
 
  for(int c=0; c<num; c++)
  {
	  char nchar = (char)(  gb::rand::randomMinMax( (int)chrMin , (int)chrMax )  );
	 *(pdest + c) = nchar;
  };

 // zero last
  *(pdest + num) = '\0';


};

 


// end file