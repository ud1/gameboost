#include <gb/math/math.h>

#include <stdio.h>

#define DXV  D3DXVECTOR3
#define GBV  gb::math::base::vec3_s
 
using namespace gb::math;
using namespace gb::math::base;

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx9d.lib" )
#else
#pragma comment( lib, "d3dx9.lib" )
#endif

void print_vectors(const D3DXVECTOR3& dxv, const gb::math::base::vec3_s& gbv)
{
  printf("\n----------------\n");
  printf("%f  %f  %f" ,  dxv.x , dxv.y ,  dxv.z );
  printf("\n----------------\n");
  gbv.print();
 
}

//===============================================
void print_func(const char* funcname)
{
	printf("\n****************** %s ***********************\n" , funcname );
}


#define PRINTFUNC  print_func(__FUNCTION__);


//==================================
void test_cross()
{
	PRINTFUNC
  DXV   dxvres ;
  GBV  gbvres ;
 
 

// d3dx
 D3DXVec3Cross( &dxvres,
   &D3DXVECTOR3(  1.454f , 2.455f , 1.975f   ),
   &D3DXVECTOR3(  2.4588f , -1.488f , 4.566f  )
	 );

// gb
GBV gbv1 = vec3_s(  1.454f , 2.455f , 1.975f    );

gbvres = gbv1.cross(   vec3_s( 2.4588f , -1.488f , 4.566f  )    );


 print_vectors( dxvres , gbvres );
}



//=============================================================
int main()
{
  test_cross();



 printf(" \n\n  ######################   end program   ##################### \n");
  system("pause");
 return 0;
};