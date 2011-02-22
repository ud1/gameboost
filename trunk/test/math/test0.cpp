// test math
//

//#pragma message("KS777: NEED COMMENTED"  __FILE__ )
//#include "stdafx.h"

#include <windows.h>

//#include "z:\\!!GB_TOADD\\math\\base.h"
//#include "z:\\!!GB_TOADD\\math\\scalar.h"

#include <gb/math/scalar.h>
#include <gb/math/base.h>


//#include "D3dx9math.h"

namespace gm = gb::math;
namespace gmb = gb::math::base;
namespace gms = gb::math::scalar;


//inline  int new_round(float f)
//{
//    // float -> integer cast uses truncation (i.e. round to zero), 
//	//according to C standard; offset the value to convert 
//	//round-to-zero to round-to-nearest
//    return (int)(f + (f > 0 ? 0.5f : -0.5f));
//}
// 

//=========================================================================
void test_round() {
	printf("test round\n");

 printf("--------gb::math::scalar::round----------\n");
 for(int c=-10; c<=10; c++)
 {
  float  finp = ((float)c) *0.2f   ;
  int nr = gb::math::scalar::round(finp);
  printf("Input: %f    out: %i  \n", finp , nr);
 }

  // new_round
 printf("--------gb::math::scalar::roundAsm----------\n");

 for(int c=-10; c<=10; c++)
 {
  float  finp = ((float)c) *0.2f   ;
  int nr =  gb::math::scalar::roundAsm(finp);
  printf("Input: %f    out: %i  \n", finp , nr);
 }



};

 //=======================================================================
int main( int argc,  char* argv[] )
{
   test_round();


	float  val  = 5.5345f;
	float vsin, vcos;
	gb::math::scalar::sincos(val, vsin , vcos);


	// round
	int nval = gb::math::scalar::round(5353.6457f); 
	nval = gb::math::scalar::roundAsm( 5353.6457f );





  system("pause");
	return 0;
}

