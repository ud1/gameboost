




#include <gb/math/math.h>
#include <d3dx9math.h>

#include <stdio.h>

using namespace gb::math;
using namespace gb::math::base;

#pragma warning(disable : 4305)

 

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib" )
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

//===============================================
void print_func(const char* funcname)
{
	printf("\n****************** %s ***********************\n" , funcname );
}


#define PRINTFUNC  print_func(__FUNCTION__);




void test_ccw()
{
	float res1 = 0.0f;
	{
	D3DXVECTOR2 v1 = D3DXVECTOR2( 0.4f , 0.25f   );
	D3DXVECTOR2 v2 = D3DXVECTOR2( 0.855f , -0.35f   );

	   res1 =  D3DXVec2CCW(	 &v1 , &v2  );
	}

   	vec2_s v1 = vec2_s( 0.4f , 0.25f   );
	vec2_s v2 = vec2_s( 0.855f , -0.35f    );
 
	 float res2 = v1.ccw(v2);

  printf("\n%f       %f\n\n",  res1 , res2 );


}




int main()
{
  printf("\n  >> begin appl >>>  \n\n");


   test_ccw();







	printf(" \n\n  ######################   end program   ##################### \n");
	system("pause");
	return 0;
}